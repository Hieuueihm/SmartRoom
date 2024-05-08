#include "fileAction.h"
#include "spiffsAction.h"
static const char *FILE_TAG = "file action";

int read_file() {
  char *ssid_content, *password_content, *topic_content;
  ssid_content = read_file_from_spiffs("/spiffs/ssid.txt");
  password_content = read_file_from_spiffs("/spiffs/password.txt");
  topic_content = read_file_from_spiffs("/spiffs/topic.txt");

  // delete_file_from_spiffs("/spiffs/foo.txt");
  if (ssid_content == NULL || password_content == NULL ||
      topic_content == NULL) {
    return 1;
  }
  return 0;
}
void lists_file() {
  DIR *d;
  struct dirent *dir;
  d = opendir("/spiffs");
  printf("\nList of files in the directory:\n");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      ESP_LOGI(FILE_TAG, "%s", dir->d_name);
    }
    closedir(d);
  }
}