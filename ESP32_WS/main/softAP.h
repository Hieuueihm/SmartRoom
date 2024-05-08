#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <string.h>

#include "lwip/err.h"
#include "lwip/sys.h"

/* The examples use WiFi configuration that you can set via project
   configuration menu.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define AP_SSID "ESP"
#define AP_PASSOWRD "12345678"
#define AP_CHANNEL 1
#define AP_CONN 3

#define EXAMPLE_ESP_WIFI_SSID AP_SSID
#define EXAMPLE_ESP_WIFI_PASS AP_PASSOWRD
#define EXAMPLE_ESP_WIFI_CHANNEL AP_CHANNEL
#define EXAMPLE_MAX_STA_CONN AP_CONN

void wifi_init_softap(void);
