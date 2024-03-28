#include <ArduinoJson.h>

namespace models {

    struct dashboard_config
    {
        float odometer;
        int next_service;
        int oil_service;
        bool oil_alert;
        bool service_alert;

        dashboard_config(float odometer, int next_service, int oil_service, bool oil_alert, bool service_alert);

        dashboard_config();

        DynamicJsonDocument toJson();
    };
} // namespace models