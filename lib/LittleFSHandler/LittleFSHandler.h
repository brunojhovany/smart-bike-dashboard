#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <Arduino.h>

class LittleFSHandler
{
public:
    LittleFSHandler();
    String ReadFile(const char* path);
    void WriteFile(const char* path, const char* message);
};
#endif