#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <gps.h>
#include <LittleFSHandler.h>
#include <ArduinoJson.h>
#include <stdexcept>

// #define RXD2 16 // esp32-dev-kit
// #define TXD2 17 // esp32-dev-kit

// #define RXD2 44  // esp32-anano
// #define TXD2 43  // esp32-anano

/*
 * @file gps.cpp
 * @brief GPS class
 * @version 1.0
 * @date 2021-04-21
 * @param UTC_offset: UTC offset in hours
 * @param Odometerfile_Path: path to odometer file
 * @param RXD2: RX pin of GPS
 * @param TXD2: TX pin of GPS
 */
GPS::GPS(int UTC_offset, const char *Odometerfile_Path, const int RXD2, const int TXD2) : neogps(1)
{
  // initialize variables
  this->UTC_offset = UTC_offset;
  this->RXD2 = RXD2;
  this->TXD2 = TXD2;
  this->filesystemhandler = LittleFSHandler();

  // initialize GPS
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
  this->Odometerfile_Path = Odometerfile_Path;
  String odometer_str = this->filesystemhandler.ReadFile(this->Odometerfile_Path);
  if (odometer_str == "")
  {
    throw std::runtime_error("GPS: Failed to read file, using default configuration");
  }
  DeserializationError error = deserializeJson(dashboard_config, odometer_str);
  if (error)
  {
    throw std::runtime_error("GPS: Failed to deserialize json, using default configuration");
  }
  // asing odometer value to odometer variable
  this->odometer = this->dashboard_config["odometer"].as<float>();
#ifdef DEBUG
  Serial.println("GPS initialized");
  Serial.println("Loading odometer from file");
  Serial.println("odometer: " + String(this->odometer));
#endif
  this->setup_done = true;
  this->saveOdometer = 0;
}

void GPS::update()
{
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (neogps.available() > 0)
    {
      gps.encode(neogps.read());
    }
  }
}

float GPS::getLatitude()
{
  return gps.location.lat();
}

float GPS::getLongitude()
{
  return gps.location.lng();
}

float GPS::getAltitude()
{
  return gps.altitude.meters();
}

float GPS::getSpeed()
{
  // get max speed
  float current_speed = gps.speed.kmph();
  if (current_speed > max_speed)
  {
    this->max_speed = current_speed;
  }
  // get avg speed from last 10 seconds
  // check if array is full
  if (speed_array[9] != 0)
  {
    // drop first speed
    for (int i = 0; i < 9; i++)
    {
      speed_array[i] = speed_array[i + 1];
    }
    // add new speed
    speed_array[9] = current_speed;
  }
  else
  {
    // add new speed
    for (int i = 0; i < 10; i++)
    {
      if (speed_array[i] == 0)
      {
        speed_array[i] = current_speed;
        break;
      }
    }
  }
  // calculate avg speed
  float sum = 0;
  for (int i = 0; i < 10; i++)
  {
    sum += speed_array[i];
  }
  this->avg_speed = sum / 10;

  return gps.speed.kmph();
}

void GPS::calculateDistance()
{                                 // Calculate time since last update in hours
                                  // Calculate time since last update in hours
  float deltaTime = 1.0 / 3600.0; // 1 second in hours

  // Calculate distance travelled using speed and time
  float currentSpeed = gps.speed.kmph();
  float distance = currentSpeed * deltaTime;

  // Update odometer and total distance
  this->odometer += distance;
  this->distance += distance; // Actualiza también this->distance

// Print debug information
#ifdef DEBUG
  Serial.println("New odometer: " + String(this->odometer));
  Serial.println("Distance since last update: " + String(distance));
  Serial.println("Total distance: " + String(this->distance));
#endif

  // Save odometer to file
  if (this->saveOdometer == 30)
  {
    try
    {
      // update odometer in dashboard_config json object and save it to file
      this->dashboard_config["odometer"] = this->odometer;
      // serialize json object to string
      String odometer_str;
      serializeJson(this->dashboard_config, odometer_str);
      // write string to file
      this->filesystemhandler.WriteFile(this->Odometerfile_Path, odometer_str.c_str());
      this->saveOdometer = 0;
    }
    catch (const std::exception &e)
    {
      Serial.println(e.what());
    }
  }
  this->saveOdometer++;
}

float GPS::getCourse()
{
  return gps.course.deg();
}

int GPS::getSatellites()
{
  return gps.satellites.value();
}

String GPS::getDate()
{
  return String(gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year());
}

void GPS::getTime(String &time, String &am_pm)
{
  int hour = this->gps.time.hour();
  int minute = this->gps.time.minute();
  // ajust time to local time
  hour = hour + UTC_offset;
  if (hour < 0)
  {
    hour = 24 + hour;
  }
  // convert hour to 12 hour format
  if (hour > 11)
  {
    am_pm = "PM";
    time = String(hour - 12) + ":" + String(minute);
  }
  else
  {
    am_pm = "AM";
    time = String(hour) + ":" + String(minute);
  }
}
