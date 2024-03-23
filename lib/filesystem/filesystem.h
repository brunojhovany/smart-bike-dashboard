#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <Arduino.h>

String readFile(const char *path);
bool writeFile(const char *path, const char *message);
#endif