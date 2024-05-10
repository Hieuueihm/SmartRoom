#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include <esp_log.h>
#include <nvs_flash.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "driver/gpio.h"
#include "fileAction.h"
#include "htmlAction.h"
#include "mqttAction.h"
#include "softAP.h"
#include "spiffsAction.h"
#include "stationMode.h"

static const char *TAG = "main";

#define LED_GPIO 2
void init_led() {
  esp_rom_gpio_pad_select_gpio(LED_GPIO);
  gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_level(LED_GPIO, 0);
}
void led_on() { gpio_set_level(LED_GPIO, 1); }
void led_off() { gpio_set_level(LED_GPIO, 0); }

void station_mode() {

  char *ssid_content, *password_content, *topic_content;

  ssid_content = read_file_from_spiffs("/spiffs/ssid.txt");
  password_content = read_file_from_spiffs("/spiffs/password.txt");
  topic_content = read_file_from_spiffs("/spiffs/topic.txt");
  if (ssid_content != NULL) {
    // Xử lý dữ liệu SSID
    printf("ssid: %s\n", ssid_content);
  }

  if (password_content != NULL) {
    // Xử lý dữ liệu mật khẩu
    printf("pass: %s\n", password_content);
  }

  if (topic_content != NULL) {
    printf("topic: %s\n", topic_content);

    // Xử lý dữ liệu chủ đề
  }

  esp_err_t status = wifi_init_sta(ssid_content, password_content);
  if (status == ESP_OK) {
    led_on();
    vTaskDelay(pdMS_TO_TICKS(3000));
    led_off();
  }
  return;
}
esp_err_t reset_file() {
  esp_err_t ssidStatus, passwordStatus, topicStatus;
  ssidStatus = write_file_to_spiffs("/spiffs/ssid.txt", "");
  passwordStatus = write_file_to_spiffs("/spiffs/password.txt", "");
  topicStatus = write_file_to_spiffs("/spiffs/topic.txt", "");

  return ESP_OK;
}

void app_main(void) {
  init_spiffs();
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
      ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  init_led();
  // reset_file();
  // int file_status = read_file();
  int file_status = 0;
  if (file_status == 1) {
    led_on();
    ESP_LOGI(TAG, "file is empty");
    wifi_init_softap();
    lists_file();

    start_webserver();

  } else {
    ESP_LOGI(TAG, "file is not empty");
    // station_mode();
    wifi_init_sta("Tiem Giat", "14141414");
    mqtt_app_start();
  }
}