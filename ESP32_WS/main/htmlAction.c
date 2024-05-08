#include "htmlAction.h"
#include "esp_http_server.h"
#include "spiffsAction.h"
#include <cJSON.h>

static const char *TAG = "html action";
static httpd_handle_t server = NULL;

extern const uint8_t index_html_start[] asm("_binary_index_html_start");
extern const uint8_t index_html_end[] asm("_binary_index_html_end");

static esp_err_t home_get_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");
  httpd_resp_send(req, (const char *)index_html_start,
                  index_html_end - index_html_start);
  return ESP_OK;
}

static char ssid[32];
static char password[64];
static char topic[64];

static esp_err_t data_from_user_post_handler(httpd_req_t *req) {
  char buf[1024];
  int ret, remaining = req->content_len;

  while (remaining > 0) {
    if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0) {
      if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
        httpd_resp_send_408(req);
      }
      return ESP_FAIL;
    }
    remaining -= ret;
    buf[ret] = '\0';

    cJSON *root = cJSON_Parse(buf);
    if (root == NULL) {
      httpd_resp_send_500(req);
      return ESP_FAIL;
    }

    cJSON *ssid_json = cJSON_GetObjectItem(root, "ssid");
    cJSON *password_json = cJSON_GetObjectItem(root, "password");
    cJSON *topic_json = cJSON_GetObjectItem(root, "topic");
    if (!ssid_json || !password_json || !topic_json ||
        !cJSON_IsString(ssid_json) || !cJSON_IsString(password_json) ||
        !cJSON_IsString(topic_json)) {
      cJSON_Delete(root);
      http_404_error_handler(req, HTTPD_404_NOT_FOUND);
      return ESP_FAIL;
    }

    char *ssid = ssid_json->valuestring;
    char *password = password_json->valuestring;
    char *topic = topic_json->valuestring;
    ESP_LOGI(TAG, "%s - %s - %s", ssid, password, topic);
    esp_err_t ssidStatus, passwordStatus, topicStatus;
    ssidStatus = write_file_to_spiffs("/spiffs/ssid.txt", ssid);
    passwordStatus = write_file_to_spiffs("/spiffs/password.txt", password);
    topicStatus = write_file_to_spiffs("/spiffs/topic.txt", topic);

    httpd_resp_send(req, "Data received!", HTTPD_RESP_USE_STRLEN);
    cJSON_Delete(root);

    if (ssidStatus == ESP_OK && passwordStatus == ESP_OK &&
        topicStatus == ESP_OK) {
      char *ssid_content, *password_content, *topic_content;

      ssid_content = read_file_from_spiffs("/spiffs/ssid.txt");
      if (ssid_content != NULL) {
        // Xử lý dữ liệu SSID
        printf("ssid: %s\n", ssid_content);
      }

      password_content = read_file_from_spiffs("/spiffs/password.txt");
      if (password_content != NULL) {
        // Xử lý dữ liệu mật khẩu
        printf("pass: %s\n", password_content);
      }

      topic_content = read_file_from_spiffs("/spiffs/topic.txt");
      if (topic_content != NULL) {
        printf("topic: %s\n", topic_content);

        // Xử lý dữ liệu chủ đề
      }

      ESP_LOGI(TAG, "test state");
      stop_webserver(server);
    }
  }

  return ESP_OK;
}

// static esp_err_t data_from_user_post_handler(httpd_req_t *req) {
//   char buffer[1024];
//   httpd_req_recv(req, buffer, sizeof(buffer));
//   ESP_LOGI(TAG, "DATA: %s\n", buffer);

//   httpd_resp_send_chunk(req, NULL, 0);
//   return ESP_OK;
// }
static const httpd_uri_t home = {.uri = "/home",
                                 .method = HTTP_GET,
                                 .handler = home_get_handler,
                                 /* Let's pass response string in user
                                  * context to demonstrate it's usage */
                                 .user_ctx = NULL};

static const httpd_uri_t data_from_user = {.uri = "/submit",
                                           .method = HTTP_POST,
                                           .handler =
                                               data_from_user_post_handler,
                                           .user_ctx = NULL};
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err) {
  if (strcmp("/home", req->uri) == 0) {
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/home URI is not available");
    /* Return ESP_OK to keep underlying socket open */
    return ESP_OK;
  }
  /* For any other URI send 404 and close socket */
  httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
  return ESP_FAIL;
}
httpd_handle_t start_webserver(void) {
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.lru_purge_enable = true;

  // Start the httpd server
  ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
  if (httpd_start(&server, &config) == ESP_OK) {
    // Set URI handlers
    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &home);
    httpd_register_uri_handler(server, &data_from_user);

    httpd_register_err_handler(server, HTTPD_404_NOT_FOUND,
                               http_404_error_handler);

  } else {
    ESP_LOGI(TAG, "Error starting server!");
  }
  return server;
}
esp_err_t stop_webserver(httpd_handle_t server) {
  // Stop the httpd server
  esp_err_t ret = httpd_stop(server);
  // if (ret != ESP_OK) {
  //   return ret;
  // }

  // Khởi động lại ESP32
  esp_restart();

  return ESP_OK;
  ;
}

void disconnect_handler(void *arg, esp_event_base_t event_base,
                        int32_t event_id, void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server) {
    ESP_LOGI(TAG, "Stopping webserver");
    if (stop_webserver(*server) == ESP_OK) {
      *server = NULL;
    } else {
      ESP_LOGE(TAG, "Failed to stop http server");
    }
  }
}

void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id,
                     void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server == NULL) {
    ESP_LOGI(TAG, "Starting webserver");
    *server = start_webserver();
  }
}
