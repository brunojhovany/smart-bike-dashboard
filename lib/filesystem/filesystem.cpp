#include <FS.h>
#include "LittleFS.h"
#include <filesystem.h>


String readFile(const char *path) {
  if (LittleFS.begin()) {
    fs::File file = LittleFS.open(path, "r");
    if (!file) {
      return "Error opening file";
    }
    String content = "";
    while (file.available()) {
      content += (char)file.read();
    }
    file.close();
    LittleFS.end();
    return content;
  } else {
    return "Error mounting FS";
  }
}

bool writeFile(const char *path, const char *message) {
  Serial.printf("message: %s\n", message);
  if (LittleFS.begin()) {
    fs::File file = LittleFS.open(path, "w");
    if (!file) {
      return false;
    }
    if (file.print(message)) {
      return true;
    } else {
      return false;
    }
    file.close();
    LittleFS.end();
  } else {
    return false;
  }
}