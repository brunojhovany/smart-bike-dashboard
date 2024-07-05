#include "AccuWeather.h"

forecast::forecast(String LocalizedName, time_t EpochTime, String WeatherText, int WeatherIcon, float Temperature, String Headline, float MinTemperature, float MaxTemperature, String DayIconPhrase, int DayIcon, String NightIconPhrase, int NightIcon)
{
    this->LocalizedName = LocalizedName;
    this->EpochTime = EpochTime;
    this->WeatherText = WeatherText;
    this->WeatherIcon = WeatherIcon;
    this->Temperature = Temperature;
    this->Headline = Headline;
    this->MinTemperature = MinTemperature;
    this->MaxTemperature = MaxTemperature;
    this->DayIconPhrase = DayIconPhrase;
    this->DayIcon = DayIcon;
    this->NightIconPhrase = NightIconPhrase;
    this->NightIcon = NightIcon;
}

forecast::forecast()
{   
    this->LocalizedName = "";
    this->EpochTime = time(nullptr);
    this->WeatherText = "";
    this->WeatherIcon = 0;
    this->Temperature = 0;
    this->Headline = "";
    this->MinTemperature = 0;
    this->MaxTemperature = 0;
    this->DayIconPhrase = "";
    this->DayIcon = 0;
    this->NightIconPhrase = "";
    this->NightIcon = 0;
}

DynamicJsonDocument forecast::toJson()
{
    DynamicJsonDocument doc(2048);
    doc["LocalizedName"] = this->LocalizedName;
    doc["EpochTime"] = this->EpochTime;
    doc["WeatherText"] = this->WeatherText;
    doc["WeatherIcon"] = this->WeatherIcon;
    doc["Temperature"] = this->Temperature;
    doc["Headline"] = this->Headline;
    doc["MinTemperature"] = this->MinTemperature;
    doc["MaxTemperature"] = this->MaxTemperature;
    doc["DayIconPhrase"] = this->DayIconPhrase;
    doc["DayIcon"] = this->DayIcon;
    doc["NightIconPhrase"] = this->NightIconPhrase;
    doc["NightIcon"] = this->NightIcon;
    return doc;
}

AccuWeather::AccuWeather(const char *apiKey)
{
    this->apiKey = apiKey;
    this->locationKey = "";
    this->apiHost = "http://dataservice.accuweather.com";
    this->DailyForecast = forecast();
}

void AccuWeather::setGPSLocation(float latitude, float longitude)
{
    this->latitude = latitude;
    this->longitude = longitude;
}

String AccuWeather::createRequestURL(char *apiResoorce)
{
    String url = this->apiHost;
    url += apiResoorce;
    url += "?apikey=";
    url += apiKey;
    return url;
}

DynamicJsonDocument AccuWeather::getJsonDocument(String urlResource)
{
    HTTPClient http;
    http.begin(urlResource);
    int httpCode = http.GET();

    DynamicJsonDocument doc(2048);
    if (httpCode > 0)
    {
        deserializeJson(doc, http.getString());
    }
    else
    {
        Serial.printf("Error on HTTP request: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    return doc;
}

// Search for the location key of the current location based on the GPS coordinates
void AccuWeather::getWeather()
{
    String url = createRequestURL("/locations/v1/cities/geoposition/search");
    url += "&q=";
    url += String(latitude, 6) + "," + String(longitude, 6);
    Serial.println(url);
    DynamicJsonDocument doc = getJsonDocument(url);
    if (!doc.isNull())
    {
        this->locationKey = doc["Key"].as<String>();
        this->DailyForecast.LocalizedName = doc["LocalizedName"].as<String>();
    }
    else
    {
        this->locationKey = "Error parsing JSON";
    }
}

// Get the current temperature based on the location key of the current location
void AccuWeather::getCondition()
{
    // http://dataservice.accuweather.com/currentconditions/v1/{locationKey}
    getWeather();
    // parsing location key to get the current condition
    char *apiEndpoint = "/currentconditions/v1/";
    size_t totalLength = strlen(apiEndpoint) + this->locationKey.length() + 1; // +1 para el carácter nulo
    char *fullApiPath = new char[totalLength];
    strcpy(fullApiPath, apiEndpoint);
    strcat(fullApiPath, this->locationKey.c_str());
    String url = createRequestURL(fullApiPath);
    Serial.println(this->locationKey);
    Serial.println(url);
    DynamicJsonDocument doc = getJsonDocument(url);
    // convert dynamic json document to string
    if (!doc.isNull())
    {   
        this->DailyForecast.EpochTime = time(nullptr);
        this->DailyForecast.WeatherText = doc[0]["WeatherText"].as<String>();
        this->DailyForecast.WeatherIcon = doc[0]["WeatherIcon"].as<int>();
        this->DailyForecast.Temperature = doc[0]["Temperature"]["Metric"]["Value"].as<float>(); 
    }
    else
    {
        Serial.println("Error parsing JSON or missing keys");
    }

    // Liberar la memoria asignada dinámicamente
    delete[] fullApiPath;
    getForecast();
}

void AccuWeather::getForecast() {
    // http://dataservice.accuweather.com/forecasts/v1/daily/1day/{locationKey}
    char *apiEndpoint = "/forecasts/v1/daily/1day/";
    size_t totalLength = strlen(apiEndpoint) + this->locationKey.length() + 1; // +1 para el carácter nulo
    char *fullApiPath = new char[totalLength];
    strcpy(fullApiPath, apiEndpoint);
    strcat(fullApiPath, this->locationKey.c_str());
    String url = createRequestURL(fullApiPath);
    Serial.println(url);
    DynamicJsonDocument doc = getJsonDocument(url);

    if (!doc.isNull() && doc.containsKey("Headline") && doc["DailyForecasts"].size() > 0) {
        this->DailyForecast.Headline = doc["Headline"]["Text"].as<String>();
        this->DailyForecast.MinTemperature = doc["DailyForecasts"][0]["Temperature"]["Minimum"]["Value"].as<float>();
        this->DailyForecast.MaxTemperature = doc["DailyForecasts"][0]["Temperature"]["Maximum"]["Value"].as<float>();
        this->DailyForecast.DayIconPhrase = doc["DailyForecasts"][0]["Day"]["IconPhrase"].as<String>();
        this->DailyForecast.DayIcon = doc["DailyForecasts"][0]["Day"]["Icon"].as<int>();
        this->DailyForecast.NightIconPhrase = doc["DailyForecasts"][0]["Night"]["IconPhrase"].as<String>();
        this->DailyForecast.NightIcon = doc["DailyForecasts"][0]["Night"]["Icon"].as<int>();

        Serial.println("Forecast successfully updated:");
        Serial.println(this->DailyForecast.Headline);
        Serial.println(this->DailyForecast.MinTemperature);
        Serial.println(this->DailyForecast.MaxTemperature);
    } else {
        Serial.println("Error parsing JSON or missing keys");
    }

    delete[] fullApiPath;
}

