#include <AsyncFsWebServer.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <Ticker.h>
#include <gps.h>

#include "WiFi.h"
#include <FS.h>
#include <LittleFS.h>
#include <models.h>
#include <TimeLib.h>

#include "AccuWeather.h"

/*Don't forget to set Sketchbook location in File/Preferencesto the path of your UI project (the parent foder of this INO file)*/

/*Change to your screen resolution*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

AsyncFsWebServer server(80, LittleFS, "WebServer");
bool captiveRun = false;

AccuWeather weather("");
Ticker weatherTicker;
Ticker alertTicker;

bool startFilesystem()
{
  if (LittleFS.begin())
  {
    server.printFileList(LittleFS, "/", 1);
    return true;
  }
  else
  {
    Serial.println("ERROR on mounting filesystem. It will be formatted!");
    LittleFS.format();
    ESP.restart();
  }
  return false;
}

// static const uint16_t relay = 26;
static const int pin_boot = 0;                // GPIO0
static uint32_t btn_positon = 0;              // for manage button press and change menu
static bool btn_menu_already_pressed = false; // for manage button press and change menu

// static const uint16_t relay = 26;
lv_indev_t *button_indev;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(screenHeight, screenWidth); /* TFT instance */

// Relays
#define RELAY1 27

// GPS config
GPS *gps;

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing  for  LittlevGL*/
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

esp_err_t event_handler(void *ctx, system_event_t *event)
{
  return ESP_OK;
}

// function to manage time transcurred from start and set to label arrival time in format hh:mm:ss
void timeManager()
{
  const time_t local = time(nullptr);
  lv_label_set_text(ui_Label_Arrival_Time_Number1, (String(hour(local)) + ":" + String(minute(local)) + ":" + String(second(local))).c_str());
}

// void controlRelay() {
//   // get relay state
//   bool relayState = digitalRead(relay);
//   // set relay state
//   digitalWrite(relay, !relayState);
//   // set label text
//   lv_img_set_src(ui_ICN_Lock, &ui_img_icn_ok_png);
//   lv_label_set_text(ui_Label_Driving_Information, relayState ? "OFF" : "ON");
// }

/* Pressed state GPIO value */
#define KEY_PRESSED_STATE 0

int btn_read()
{
  int btn_id = 1; /*No press*/
  if (digitalRead(pin_boot) == KEY_PRESSED_STATE)
  {
    btn_id = 0;
  }
  return btn_id;
}

void ManageAlerts()
{
  if (gps->dashboard_config["oil_alert"].as<bool>())
  {
    lv_obj_clear_flag(ui_ICN_Oil_Alert, LV_OBJ_FLAG_HIDDEN);
  }
  if (gps->dashboard_config["oil_service"].as<float>() <= gps->odometer)
  {
    lv_obj_clear_flag(ui_ICN_Oil_Alert, LV_OBJ_FLAG_HIDDEN);
    gps->dashboard_config["oil_alert"] = true;
  }

  if (gps->dashboard_config["service_alert"].as<bool>())
  {
    lv_obj_clear_flag(ui_ICN_Service_Alert, LV_OBJ_FLAG_HIDDEN);
  }
  if (gps->dashboard_config["next_service"].as<float>() <= gps->odometer)
  {
    lv_obj_clear_flag(ui_ICN_Service_Alert, LV_OBJ_FLAG_HIDDEN);
    gps->dashboard_config["service_alert"] = true;
  }

  lv_label_set_text(ui_Label_Alert_Oil_Number, String(gps->dashboard_config["oil_service"].as<float>()).c_str());
  lv_label_set_text(ui_Label_Alert_Service_Number, String(gps->dashboard_config["next_service"].as<float>()).c_str());
}

void SetWeatherIcon(lv_obj_t *ui_Resource, int icon = 1)
{
  switch (icon)
  {
  case 1:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_1_png);
    break;
  case 2:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_2_png);
    break;
  case 3:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_3_png);
    break;
  case 4:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_4_png);
    break;
  case 5:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_5_png);
    break;
  case 6:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_6_png);
    break;
  case 7:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_7_png);
    break;
  case 8:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_8_png);
    break;
  case 11:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_11_png);
    break;
  case 12:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_12_png);
    break;
  case 13:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_13_png);
    break;
  case 14:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_14_png);
    break;
  case 15:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_15_png);
    break;
  case 16:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_16_png);
    break;
  case 17:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_17_png);
    break;
  case 18:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_18_png);
    break;
  case 19:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_19_png);
    break;
  case 20:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_20_png);
    break;
  case 21:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_21_png);
    break;
  case 22:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_22_png);
    break;
  case 23:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_23_png);
    break;
  case 24:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_24_png);
    break;
  case 25:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_25_png);
    break;
  case 26:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_26_png);
    break;
  case 29:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_29_png);
    break;
  case 30:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_30_png);
    break;
  case 31:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_31_png);
    break;
  case 32:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_32_png);
    break;
  case 33:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_33_png);
    break;
  case 34:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_34_png);
    break;
  case 35:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_35_png);
    break;
  case 36:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_36_png);
    break;
  case 37:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_37_png);
    break;
  case 38:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_38_png);
    break;
  case 39:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_39_png);
    break;
  case 40:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_40_png);
    break;
  case 41:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_41_png);
    break;
  case 42:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_42_png);
    break;
  case 43:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_43_png);
    break;
  case 44:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_44_png);
    break;

  default:
    lv_img_set_src(ui_Resource, &ui_img_weather_icons_weather_icon_1_png);
    break;
  }
}

void checkWeatherFile()
{
  // check if exist weather.json file and load it to weather.DailyForecast
  if (LittleFS.exists("/weather.json"))
  {
    File file = LittleFS.open("/weather.json", "r");
    if (!file)
    {
      Serial.println("Error al abrir el archivo JSON");
      return;
    }
    DynamicJsonDocument weatherData(file.size());
    deserializeJson(weatherData, file);
    file.close();
    weather.DailyForecast.LocalizedName = weatherData["LocalizedName"].as<String>();
    weather.DailyForecast.EpochTime = weatherData["EpochTime"].as<time_t>();
    weather.DailyForecast.WeatherText = weatherData["WeatherText"].as<String>();
    weather.DailyForecast.WeatherIcon = weatherData["WeatherIcon"].as<int>();
    weather.DailyForecast.Temperature = weatherData["Temperature"].as<float>();
    weather.DailyForecast.Headline = weatherData["Headline"].as<String>();
    weather.DailyForecast.MinTemperature = weatherData["MinTemperature"].as<float>();
    weather.DailyForecast.MaxTemperature = weatherData["MaxTemperature"].as<float>();
    weather.DailyForecast.DayIconPhrase = weatherData["DayIconPhrase"].as<String>();
    weather.DailyForecast.DayIcon = weatherData["DayIcon"].as<int>();
    weather.DailyForecast.NightIconPhrase = weatherData["NightIconPhrase"].as<String>();
    weather.DailyForecast.NightIcon = weatherData["NightIcon"].as<int>();
  }
  else
  {
    weather.getCondition();
  }
  if (gps->gps.location.isValid())
  {
    weather.setGPSLocation(gps->getLatitude(), gps->getLongitude());
    // validate if weather data is updated every 1 hour or 3600 seconds but epoch time is in ISO 8601 format
    // so we need to convert it to epoch time
    time_t now = time(nullptr);
    time_t epochTime = now + 3600;
    if (epochTime > weather.DailyForecast.EpochTime)
    {
      weather.getCondition();
    }
  }
}
void LoadWeather()
{
  checkWeatherFile();
  // only use integer part of the temperature
  String tmp = String((int)weather.DailyForecast.Temperature);
  lv_label_set_text(ui_Label_Temp, tmp.c_str());
  lv_label_set_text(ui_Label_Weather_Tmp_Number, tmp.c_str());
  // Obtiene el texto del clima actual
  lv_label_set_text(ui_Label_Weather_Current_Condition, weather.DailyForecast.WeatherText.c_str());
  // Obtiene el icono del clima actual
  SetWeatherIcon(ui_ICN_Weather, weather.DailyForecast.WeatherIcon);
  lv_label_set_text(ui_Label_Weather_location, weather.DailyForecast.LocalizedName.c_str());

  // Obtiene el pronóstico diario
  int minTmp = (int)weather.DailyForecast.MinTemperature;
  minTmp = (minTmp - 32) * 5 / 9;
  lv_label_set_text(ui_Label_Weather_Maximum, String(minTmp).c_str());
  // Obtiene la temperatura máxima
  int maxTmp = (int)weather.DailyForecast.MaxTemperature;
  maxTmp = (maxTmp - 32) * 5 / 9;
  lv_label_set_text(ui_Label_Weather_Minimum, String(maxTmp).c_str());
  // Obtiene el texto del pronóstico
  lv_label_set_text(ui_Label_Weather_Day_Condition, weather.DailyForecast.DayIconPhrase.c_str());
  // Obtiene el icono del pronóstico
  SetWeatherIcon(ui_ICN_Weather1, weather.DailyForecast.DayIcon);
  // Obtiene el texto del pronóstico nocturno
  lv_label_set_text(ui_Label_Weather_Night_Condition, weather.DailyForecast.NightIconPhrase.c_str());
  // Obtiene el icono del pronóstico nocturno
  SetWeatherIcon(ui_ICN_Weather2, weather.DailyForecast.NightIcon);
}

void changeMenu(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
  int btn_pr = btn_read(); /*Get the ID (0,1,2...) of the pressed button*/
  if (btn_pr == 0 and btn_menu_already_pressed == false)
  {
    if (btn_positon < 2)
    {
      btn_positon++;
    }
    else
    {
      btn_positon = 0;
    }
    data->state = LV_INDEV_STATE_PR; /*Set the pressed state*/
    data->btn_id = btn_positon;      /*Set the button ID*/
    btn_menu_already_pressed = true;
  }
  else if (btn_pr == 1 and btn_menu_already_pressed == true)
  {
    data->state = LV_INDEV_STATE_REL; /*Set the released state*/
    btn_menu_already_pressed = false;
  }
}

void setSpeed(int speed, lv_anim_enable_t anim, int max_speed = 0, int avg_speed = 0)
{
  lv_slider_set_value(ui_Slider_Speed, speed, anim);
  lv_label_set_text(ui_Speed_Number_1, String(lv_slider_get_value(ui_Slider_Speed)).c_str());
  lv_label_set_text(ui_Speed_Number_2, String(lv_slider_get_value(ui_Slider_Speed)).c_str());
#ifdef DEBUG
  Serial.println("Speed: " + String(speed));
  Serial.println("Max Speed: " + String(max_speed));
  Serial.println("Avg Speed: " + String(avg_speed));
#endif

  if (max_speed != 0)
  {
    lv_label_set_text(ui_Label_Max_Speed_Number, String(max_speed).c_str());
  }
  if (avg_speed != 0)
  {
    lv_label_set_text(ui_Label_AVG_Speed_Number, String(avg_speed).c_str());
  }
}

// void *pvParameters
void GPSUpdate(void *pvParameters)
{
  while (1)
  {
    gps->update();
    if (gps->gps.location.isValid() == 1)
    {
      // un hide Gps icon
      lv_obj_clear_flag(ui_ICN_GPS_Alert, LV_OBJ_FLAG_HIDDEN);

      int speed = (int)gps->getSpeed();
      setSpeed(speed, LV_ANIM_ON, (int)gps->max_speed, (int)gps->avg_speed);

      // get UTC time from gps and set to label
      String time, am_pm;
      gps->getTime(time, am_pm);
      // set time to label
      lv_label_set_text(ui_Label_Time, time.c_str());
      // set AM/PM to label
      lv_label_set_text(ui_Labe_AM_PM, am_pm.c_str());

      // call function to calculate distance
      gps->calculateDistance();

      // get odometer from gps instance and append km to label
      int odometer = (int)gps->odometer;
      lv_label_set_text(ui_Label_ODO_Number, String(odometer).c_str());

      // get distance from gps instance and append km to label
      int distance = (int)gps->distance;
      lv_label_set_text(ui_Label_Trip_Number, String(distance).c_str());
    }
    else
    {
// print to seria no gps data
#ifdef DEBUG
      Serial.println("No GPS data");
      // print defualt values
      Serial.println("Odomerter: " + gps->dashboard_config["odometer"].as<String>());
      Serial.println("Odometer file: " + String(gps->Odometerfile_Path));
#endif
      // hide Gps icon
      lv_obj_add_flag(ui_ICN_GPS_Alert, LV_OBJ_FLAG_HIDDEN);
      setSpeed(0, LV_ANIM_ON);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void splashScreen(void *arg)
{
  lv_scr_load_anim(ui_Driving, LV_SCR_LOAD_ANIM_MOVE_LEFT, 2200, 3000, true);
}

Ticker periodicTicker;
void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */
  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  tft.init();                /* TFT init */
  tft.setRotation(3);        /* Landscape orientation, flipped */
  tft.invertDisplay(0);      /* Do not invert display */
  tft.fillScreen(TFT_BLACK); /* Clear screen */

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
  ui_init(); /*Initialize the user interface*/

  periodicTicker.attach(1, timeManager);
  // setup gps instance and set initial values ---------------------------------
  gps = new GPS(-6, "/dashboard_config.json", 44, 43);
  while (!gps->setup_done)
  {
    delay(1000);
    Serial.print(".");
  }
  // load odometer from gps instance and append km to label
  int odometer = (int)gps->odometer;
  lv_label_set_text(ui_Label_ODO_Number, String(odometer).c_str());
  TaskHandle_t GPSUpdateTask;
  xTaskCreate(GPSUpdate, "GPSUpdate", 10000, NULL, 1, &GPSUpdateTask);
  // end gps setup ------------------------------------------------------------

  // sutup control button for change menu
  static lv_indev_drv_t indev_drv2;
  lv_indev_drv_init(&indev_drv2);
  indev_drv2.type = LV_INDEV_TYPE_BUTTON;
  indev_drv2.read_cb = changeMenu;
  button_indev = lv_indev_drv_register(&indev_drv2);
  static lv_point_t points_array[] = {{156, 225}, {228, 225}, {294, 225}};
  lv_indev_set_button_points(button_indev, points_array);

  // config splash screen timer and start -------------------------------------
  esp_timer_create_args_t splashScreenTimerArgs = {
      .callback = &splashScreen,
      .arg = NULL,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "splash_timer"};

  esp_timer_handle_t splash_timer;
  esp_timer_create(&splashScreenTimerArgs, &splash_timer);
  esp_timer_start_once(splash_timer, 1000);
  // end splash screen timer --------------------------------------------------

  // setup web server ---------------------------------------------------------
  startFilesystem();
  IPAddress myIP = server.startWiFi(15000);
  if (!myIP)
  {
    Serial.println("\n\nNo WiFi connection, start AP and Captive Portal\n");
    myIP = WiFi.softAPIP();
    Serial.print("My IP 1 ");
    Serial.println(myIP.toString());
    server.startCaptivePortal("smart bike", "osvaldomb", "/setup");
    myIP = WiFi.softAPIP();
    Serial.print("\nMy IP 2 ");
    Serial.println(myIP.toString());
    captiveRun = true;
  }

  // Set a custom /setup page title
  server.setSetupPageTitle("Configuracion del punto de acceso");
  server.setFirmwareVersion("v0.1.0");
  server.enableFsCodeEditor();

  lv_label_set_text(ui_Label_ETA1, WiFi.localIP().toString().c_str());
  server.on("/dbsetup", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });

  server.on("/dbdata", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    // load dashboard config file and send it to the client as application/json
    File file = LittleFS.open("/dashboard_config.json", "r");
    if (!file)
    {
      request->send(500, "application/json", F("{\"error\": \"Error al abrir el archivo JSON\"}"));
      return;
    }
    request->send(LittleFS, "/dashboard_config.json", "application/json"); });
  // need to pass the task handle to the lambda function
  server.on("/dbsetupp", HTTP_POST, [GPSUpdateTask](AsyncWebServerRequest *request)
            {
    // Manejar el formulario
    if (request->hasArg("odometer") && request->hasArg("next_service") && request->hasArg("oil_service"))
    {
      // Obtener los valores del formulario
      String odometer = request->arg("odometer");
      String nextService = request->arg("next_service");
      String oilService = request->arg("oil_service");
      String oilAlert = request->arg("oil_alert");
      String serviceAlert = request->arg("service_alert");
      bool oilAlertBool = false;
      bool serviceAlertBool = false;
      if (oilAlert == "true")
      {
        oilAlertBool = true;
      }
      if (serviceAlert == "true")
      {
        serviceAlertBool = true;
      }

      // from models namespace dashboard_config struct
      models::dashboard_config dashboardConfig(odometer.toFloat(), nextService.toInt(), oilService.toInt(), oilAlertBool, serviceAlertBool);
      // Crear un objeto JSON
      DynamicJsonDocument json_value = dashboardConfig.toJson();
#ifdef DEBUG
      Serial.println("raw values:");
      Serial.println("Odometer: " + odometer);
      Serial.println("Next Service: " + nextService);
      Serial.println("Oil Service: " + oilService);
      Serial.println("Oil Alert: " + oilAlert);
      Serial.println("Service Alert: " + serviceAlert);
      Serial.println("JSON:");
      serializeJsonPretty(json_value, Serial);
#endif

      // Abrir el archivo JSON en modo de escritura
      File file = LittleFS.open("/dashboard_config.json", "w");
      if (!file)
      {
        request->send(500, "text/plain", "Error al abrir el archivo JSON");
        return;
      }

      // Serializar el objeto JSON y escribirlo en el archivo
      if (serializeJson(json_value, file) == 0)
      {
        request->send(500, "text/plain", "Error al escribir en el archivo JSON");
      }

      vTaskDelete(GPSUpdateTask);
      // Cerrar el archivo
      file.close();

      // Enviar respuesta exitosa
      request->send(LittleFS, "/success.html", "text/html");
      delay(1000);
      ESP.restart();
    }
    else
    {
      request->send(400, "text/plain", "Parámetros faltantes en el formulario");
    } });
  // end web server setup -----------------------------------------------------

  Serial.println("Motorcycle Dashboard v0.1.0");
  Serial.println("Setup done");

  // Start server
  server.init();
  Serial.print(F("Async ESP Web Server started on IP Address: "));
  Serial.println(myIP);
  Serial.println(F(
      "Open /setup page to configure optional parameters.\n"
      "Open /edit page to view, edit or upload example or your custom webserver source files."));

  // weather setup ------------------------------------------------------------
  gps->getLatitude();
  gps->getLongitude();
  if (gps->gps.location.isValid())
  {
    weather.setGPSLocation(gps->getLatitude(), gps->getLongitude());
  }
  else
  {
    // load default location
    weather.setGPSLocation(16.349622, -94.481765);
  }
  LoadWeather(); // need this to load weather data on start
  weatherTicker.attach(3600, LoadWeather);
  // end weather setup --------------------------------------------------------
  ManageAlerts(); // need this to load alerts on start
  alertTicker.attach(30, ManageAlerts);
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}