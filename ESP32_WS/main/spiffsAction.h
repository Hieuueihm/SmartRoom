#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_spiffs.h"
#include "esp_system.h"

#include <string.h>

void init_spiffs();
char *read_file_from_spiffs(const char *filename);

esp_err_t write_file_to_spiffs(const char *filename, const char *content);
// esp_err_t delete_file_from_spiffs(const char *filename);