#include "esp_event.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "esp_tls.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>


httpd_handle_t start_webserver(void);
esp_err_t stop_webserver(httpd_handle_t server);

void disconnect_handler(void *arg, esp_event_base_t event_base,
                        int32_t event_id, void *event_data);
void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id,
                     void *event_data);
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err);