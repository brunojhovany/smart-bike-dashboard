#include <ArduinoJson.h>
#include "models.h"

namespace models
{

    dashboard_config::dashboard_config(float odometer, int next_service, int oil_service, bool oil_alert, bool service_alert)
    {
        this->odometer = odometer;
        this->next_service = next_service;
        this->oil_service = oil_service;
        this->oil_alert = oil_alert;
        this->service_alert = service_alert;
    }

    dashboard_config::dashboard_config()
    {
        this->odometer = 0;
        this->next_service = 0;
        this->oil_service = 0;
        this->oil_alert = false;
        this->service_alert = false;
    }

    DynamicJsonDocument dashboard_config::toJson()
    {
        DynamicJsonDocument doc(1024);
        doc["odometer"] = this->odometer;
        doc["next_service"] = this->next_service;
        doc["oil_service"] = this->oil_service;
        doc["oil_alert"] = this->oil_alert;
        doc["service_alert"] = this->service_alert;
        return doc;
    }
} // namespace models

