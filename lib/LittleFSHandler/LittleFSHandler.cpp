#include <FS.h>
#include "LittleFS.h"
#include <LittleFSHandler.h>
#include <stdexcept>

LittleFSHandler::LittleFSHandler()
{
  if (!LittleFS.begin())
  {
    throw std::runtime_error("Failed to mount LittleFS");
  }
}

String LittleFSHandler::ReadFile(const char *path)
{
  fs::File file = LittleFS.open(path, FILE_READ);
  if (!file)
  {
    throw std::runtime_error(std::string("Failed to open file for reading: ") + path); // Fix the constructor argument
  }
  String content = "";
  while (file.available())
  {
    content += (char)file.read();
  }
  file.close();
  return content;
}

void LittleFSHandler::WriteFile(const char *path, const char *message)
{
  fs::File file = LittleFS.open(path, FILE_WRITE);
  if (!file)
  {
    throw std::runtime_error(std::string("Failed to open file for writing: ") + path); // Fix the constructor argument
  }
  if (!file.print(message))
  {
    file.close();
    throw std::runtime_error("Failed to write to file: " + std::string(path)); // Fix the constructor argument
  }
  file.close();
}