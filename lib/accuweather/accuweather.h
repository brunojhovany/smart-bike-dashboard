#ifndef ACCUWEATHER_H
#define ACCUWEATHER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

struct forecast
{   String LocalizedName;
    time_t EpochTime;
    String WeatherText;
    int WeatherIcon;
    float Temperature;

    String Headline;
    float MinTemperature;
    float MaxTemperature;
    String DayIconPhrase;
    int DayIcon;
    String NightIconPhrase;
    int NightIcon;

    forecast(String LocalizedName, time_t EpochTime, String WeatherText, int WeatherIcon, float Temperature, String Headline, float MinTemperature, float MaxTemperature, String DayIconPhrase, int DayIcon, String NightIconPhrase, int NightIcon);
    forecast();
    DynamicJsonDocument toJson();
};

class AccuWeather
{
public:
    AccuWeather(const char *apiKey);
    void setGPSLocation(float latitude, float longitude);
    void getWeather();
    void getCondition();
    void getForecast();
    forecast DailyForecast;

private:
    const char *apiHost;
    const char *apiKey;
    String locationKey;
    float latitude;
    float longitude;
    String createRequestURL(char *apiResource);
    DynamicJsonDocument getJsonDocument(String urlResource);
};

#endif
