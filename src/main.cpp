#include <AsyncFsWebServer.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include <Ticker.h>
#include <gps.h>

#include "WiFi.h"
#include <FS.h>
#include <LittleFS.h>

/*Don't forget to set Sketchbook location in File/Preferencesto the path of your UI project (the parent foder of this INO file)*/

/*Change to your screen resolution*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

// static const uint16_t relay = 26;
// static const int pin_boot = 0;

lv_indev_t *button_indev;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

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
  // get time from start
  uint32_t time = millis() / 1000;
  // calculate hours
  uint32_t hours = time / 3600;
  // calculate minutes
  uint32_t minutes = (time % 3600) / 60;
  // calculate seconds
  uint32_t seconds = (time % 3600) % 60;

  // set label text
  lv_label_set_text(ui_Label_Arrival_Time_Number1, (String(hours) + ":" + String(minutes) + ":" + String(seconds)).c_str());
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

// int btn_read() {
//   int btn_id = 1; /*No press*/
//   // Serial.println(digitalRead(pin_boot));
//   if (digitalRead(pin_boot) == KEY_PRESSED_STATE) {
//     btn_id = 0;
//   }
//   return btn_id;
// }

// void changeMenu(lv_indev_drv_t *drv, lv_indev_data_t *data) {
//   static uint32_t last_btn = 0;      /*Store the last pressed button*/
//   int btn_pr = btn_read();           /*Get the ID (0,1,2...) of the pressed button*/
//   if (btn_pr >= 0) {                 /*Is there a button press? (E.g. -1 indicated no button was pressed)*/
//     last_btn = btn_pr;               /*Save the ID of the pressed button*/
//     data->state = LV_INDEV_STATE_PR; /*Set the pressed state*/
//   } else {
//     data->state = LV_INDEV_STATE_REL; /*Set the released state*/
//   }

//   data->btn_id = last_btn; /*Save the last button*/

//   // return false;                    /*No buffering now so no more data read*/
// }

void setSpeed(int speed, lv_anim_enable_t anim, int max_speed = 0, int avg_speed = 0)
{
  lv_slider_set_value(ui_Slider_Speed, speed, anim);
  lv_label_set_text(ui_Speed_Number_1, String(lv_slider_get_value(ui_Slider_Speed)).c_str());
  lv_label_set_text(ui_Speed_Number_2, String(lv_slider_get_value(ui_Slider_Speed)).c_str());

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
      Serial.println("No GPS data");
      // hide Gps icon
      lv_obj_add_flag(ui_ICN_GPS_Alert, LV_OBJ_FLAG_HIDDEN);
      setSpeed(0, LV_ANIM_ON);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

static void splashScreen(void *arg)
{
  lv_scr_load_anim(ui_Driving, LV_SCR_LOAD_ANIM_MOVE_LEFT, 400, 2000, true);
}

Ticker periodicTicker;
void setup()
{
  Serial.begin(115200); /* prepare for possible serial debug */
  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  tft.init();           /* TFT init */
  tft.setRotation(3);   /* Landscape orientation, flipped */
  tft.invertDisplay(0); /* Do not invert display */

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

  // clean screen with black color
  lv_obj_t *scr = lv_disp_get_scr_act(NULL);

  periodicTicker.attach(1, timeManager);

  gps = new GPS(-6, "/odometer.txt", 44, 43);
  // load odometer from gps instance and append km to label
  int odometer = (int)gps->odometer;
  lv_label_set_text(ui_Label_ODO_Number, String(odometer).c_str());
  xTaskCreate(GPSUpdate, "GPSUpdate", 10000, NULL, 1, NULL);

  // sutup control button for change menu
  // static lv_indev_drv_t indev_drv2;
  // lv_indev_drv_init(&indev_drv2);
  // indev_drv2.type = LV_INDEV_TYPE_BUTTON;
  // indev_drv2.read_cb = changeMenu;
  // button_indev = lv_indev_drv_register(&indev_drv2);

  // static lv_point_t points_array[] = { { 205, 225 } };
  // lv_indev_set_button_points(button_indev, points_array);

  // Serial.println(xPortGetCoreID());
  // config splash screen timer and start -------------------------------------
  esp_timer_create_args_t splashScreenTimerArgs = {
      .callback = &splashScreen,
      .arg = NULL,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "splash_timer"};

  esp_timer_handle_t splash_timer;
  esp_timer_create(&splashScreenTimerArgs, &splash_timer);
  esp_timer_start_once(splash_timer, 5000);
  // end splash screen timer --------------------------------------------------

  // setup wifi ---------------------------------------------------------------
  Serial.println("Conectando a la red WiFi");
  WiFi.begin("STARLINK", "7qwKFGkj7x6H35");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  lv_label_set_text(ui_Label_ETA1, WiFi.localIP().toString().c_str());
  // end wifi setup -----------------------------------------------------------

  // setup web server ---------------------------------------------------------
  // AsyncWebServer server(80);
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
  //   request->send(200, "plain/text", "Server alredy running");

  // });
  // server.begin();
  // end web server setup -----------------------------------------------------

  Serial.println("Motorcycle Dashboard v0.1.0");
  Serial.println("Setup done");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}