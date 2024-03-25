/**
*  @file gps.h 
*
*/


#include <TinyGPS++.h>
#include <LittleFSHandler.h>
#include <ArduinoJson.h>

#ifndef GPS_H
#define GPS_H

#include <Arduino.h>


class GPS {
private:
  float speed_array[10];
  int UTC_offset;
  int saveOdometer;
  int RXD2;
  int TXD2;

public:
  TinyGPSPlus gps;
  HardwareSerial neogps;
  LittleFSHandler filesystemhandler;
  double max_speed = 0;
  double avg_speed = 0;
  float odometer;
  float distance = 0;
  const char *Odometerfile_Path;
  bool setup_done = false;
  StaticJsonDocument<200> dashboard_config;

  GPS(int UTC_offset, const char *Odometerfile_Path, const int RXD2, const int TXD2);

  void update();
  float getLatitude();
  float getLongitude();
  float getAltitude();
  float getSpeed();
  void calculateDistance();
  float getCourse();
  int getSatellites();
  String getDate();
  void getTime(String &time, String &am_pm);
};

#endif