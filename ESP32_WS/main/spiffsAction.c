#include "spiffsAction.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
static const char *SPIFFS_TAG = "SPIFFS";

void init_spiffs() {
  esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs", // Đường dẫn gốc của SPIFFS
      .partition_label = NULL,
      .max_files = 5, // Số lượng tệp tối đa có thể mở cùng một lúc
      .format_if_mount_failed = true};

  // Khởi tạo SPIFFS
  esp_err_t ret = esp_vfs_spiffs_register(&conf);

  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      ESP_LOGE(SPIFFS_TAG, "Failed to mount or format filesystem");
    } else if (ret == ESP_ERR_NOT_FOUND) {
      ESP_LOGE(SPIFFS_TAG, "Failed to find SPIFFS partition");
    } else {
      ESP_LOGE(SPIFFS_TAG, "Failed to initialize SPIFFS (%s)",
               esp_err_to_name(ret));
    }
    return;
  }
  ESP_LOGI(SPIFFS_TAG, "SPIFFS initialized successfully");

  size_t total = 0, used = 0;
  esp_spiffs_info(conf.partition_label, &total, &used);
  ESP_LOGI(SPIFFS_TAG, "Partition size: total: %d, used: %d", total, used);
}
#define MAX_FILE_SIZE 1024

char *read_file_from_spiffs(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    file = fopen(filename, "w");
    fclose(file);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (file_size <= 0 || file_size >= MAX_FILE_SIZE) {
    ESP_LOGE(SPIFFS_TAG, "Invalid file size '%ld' for file '%s'", file_size,
             filename);
    fclose(file);
    return NULL;
  }

  char *file_content = (char *)malloc(file_size + 1);
  if (file_content == NULL) {
    ESP_LOGE(SPIFFS_TAG, "Failed to allocate memory for file content '%s'",
             filename);
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(file_content, 1, file_size, file);
  fclose(file);

  if (bytes_read != file_size) {
    ESP_LOGE(SPIFFS_TAG, "Error reading file '%s'", filename);
    free(file_content);
    return NULL;
  }

  file_content[bytes_read] = '\0';

  return file_content;
}

esp_err_t write_file_to_spiffs(const char *filename, const char *content) {
  // Mở tệp từ SPIFFS để ghi
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    ESP_LOGE(SPIFFS_TAG, "Failed to open file '%s' for writing", filename);
    return ESP_FAIL;
  }

  // Ghi nội dung vào tệp
  size_t bytes_written = fwrite(content, 1, strlen(content), file);
  fclose(file);

  if (bytes_written != strlen(content)) {
    ESP_LOGE(SPIFFS_TAG, "Failed to write all content to file '%s'", filename);
    return ESP_FAIL;
  }

  ESP_LOGI(SPIFFS_TAG, "Content successfully written to file '%s'", filename);
  vTaskDelay(pdMS_TO_TICKS(1));

  return ESP_OK;
}

// esp_err_t delete_file_from_spiffs(const char *filename) {
//   // Xóa tệp từ SPIFFS
//   if (unlink(filename) != 0) {
//     ESP_LOGE(SPIFFS_TAG, "Failed to delete file '%s'", filename);
//     return ESP_FAIL;
//   }

//   ESP_LOGI(SPIFFS_TAG, "File '%s' successfully deleted", filename);
//   return ESP_OK;
// }