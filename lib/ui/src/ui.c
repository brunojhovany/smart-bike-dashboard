// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Futuristic_Ebike

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void Particle1_Animation(lv_obj_t * TargetObject, int delay);
void Particle2_Animation(lv_obj_t * TargetObject, int delay);
void Particle3_Animation(lv_obj_t * TargetObject, int delay);
void Fash_Animation(lv_obj_t * TargetObject, int delay);
void Wave1_Animation(lv_obj_t * TargetObject, int delay);
void Wave2_Animation(lv_obj_t * TargetObject, int delay);
void Off_Animation(lv_obj_t * TargetObject, int delay);
void On_Animation(lv_obj_t * TargetObject, int delay);


// SCREEN: ui_Welcome
void ui_Welcome_screen_init(void);
lv_obj_t * ui_Welcome;
lv_obj_t * ui_BajajLogo;


// SCREEN: ui_Driving
void ui_Driving_screen_init(void);
lv_obj_t * ui_Driving;
lv_obj_t * ui_Speed_Number_2;
lv_obj_t * ui_Speed_Number_1;
lv_obj_t * ui_Label_Speed;
lv_obj_t * ui_Label_kmh1;
lv_obj_t * ui_Slider_Speed;
lv_obj_t * ui_Group_Speedometer;
lv_obj_t * ui_Label_Number1;
lv_obj_t * ui_Label_Number2;
lv_obj_t * ui_Label_Number3;
lv_obj_t * ui_Label_Number4;
lv_obj_t * ui_Label_Number5;
lv_obj_t * ui_Group_Header;
lv_obj_t * ui_Label_Time;
lv_obj_t * ui_Labe_AM_PM;
lv_obj_t * ui_Label_Temp;
lv_obj_t * ui_Label_Celsius;
lv_obj_t * ui_ICN_Oil_Alert;
lv_obj_t * ui_ICN_GPS_Alert;
lv_obj_t * ui_ICN_Service_Alert;
lv_obj_t * ui_Group_Footer;
lv_obj_t * ui_Button_Group;
lv_obj_t * ui_BTN_Driving;
void ui_event_BTN_BGDriving(lv_event_t * e);
lv_obj_t * ui_BTN_BGDriving;
lv_obj_t * ui_ICN_Driving;
lv_obj_t * ui_BTN_Service;
void ui_event_BTN_BGService(lv_event_t * e);
lv_obj_t * ui_BTN_BGService;
lv_obj_t * ui_ICN_Chck_Ngn;
lv_obj_t * ui_BTN_Notifications;
void ui_event_BTN_BGAlert(lv_event_t * e);
lv_obj_t * ui_BTN_BGAlert;
lv_obj_t * ui_ICN_Alert;
lv_obj_t * ui_Group_Driving;
lv_obj_t * ui_Group_Content;
lv_obj_t * ui_Group_ODO;
lv_obj_t * ui_LabeL_ODO;
lv_obj_t * ui_Label_ODO_Number;
lv_obj_t * ui_Label_ETA_Number;
lv_obj_t * ui_Group_Trip;
lv_obj_t * ui_Label_Trip;
lv_obj_t * ui_Label_Trip_Number;
lv_obj_t * ui_Label_km2;
lv_obj_t * ui_Group_Max_Speed;
lv_obj_t * ui_Label_Max_Speed;
lv_obj_t * ui_Label_Max_Speed_Number;
lv_obj_t * ui_Label_kmh2;
lv_obj_t * ui_Group_AVG_Speed;
lv_obj_t * ui_Label_AVG_Speed;
lv_obj_t * ui_Label_AVG_Speed_Number;
lv_obj_t * ui_Label_kmh3;
lv_obj_t * ui_Group_ETA;
lv_obj_t * ui_Label_ETA;
lv_obj_t * ui_Label_ETA1;
lv_obj_t * ui_Group_Time;
lv_obj_t * ui_Label_Time1;
lv_obj_t * ui_Label_Arrival_Time_Number1;
lv_obj_t * ui_Group_Title;
lv_obj_t * ui_Title_BG;
lv_obj_t * ui_Label_Driving_Information;
lv_obj_t * ui_Group_Service;
lv_obj_t * ui_Group_Title1;
lv_obj_t * ui_Title_BG1;
lv_obj_t * ui_Service;
lv_obj_t * ui_Group_Service_Content;
lv_obj_t * ui_Group_Service_Alert;
lv_obj_t * ui_ICN_Wrench;
lv_obj_t * ui_Label_Service_Alert;
lv_obj_t * ui_Label_Alert_Service_Number;
lv_obj_t * ui_Label_Alert_Service_KM;
lv_obj_t * ui_Group_Oil_Alert;
lv_obj_t * ui_ICN_Oil;
lv_obj_t * ui_Label_Oil_Alert;
lv_obj_t * ui_Label_Alert_Oil_Number;
lv_obj_t * ui_Label_Alert_Oil__KM;
lv_obj_t * ui_Group_Oil_Alert1;
lv_obj_t * ui_ICN_Oil1;
lv_obj_t * ui_Label_Temp_Alert;
lv_obj_t * ui_Label_Alert_Temp_Number;
lv_obj_t * ui_Group_Wheather;
lv_obj_t * ui_Group_Title2;
lv_obj_t * ui_Title_BG2;
lv_obj_t * ui_Notifications;
lv_obj_t * ui_Group_weather_info;
lv_obj_t * ui_Group_Service_Alert1;
lv_obj_t * ui_ICN_Weather;
lv_obj_t * ui_Label_Weather_Tmp_Number;
lv_obj_t * ui_Label_Weather_Current_Condition;
lv_obj_t * ui_Label_Weather_unit;
lv_obj_t * ui_Label_Weather_location;
lv_obj_t * ui_Group_Service_Alert2;
lv_obj_t * ui_ICN_Weather1;
lv_obj_t * ui_Label_Weather_Day;
lv_obj_t * ui_Label_Weather_Minimum;
lv_obj_t * ui_Label_Weather_Unit1;
lv_obj_t * ui_Label_Weather_Day_Condition;
lv_obj_t * ui_Group_Service_Alert3;
lv_obj_t * ui_ICN_Weather2;
lv_obj_t * ui_Label_Weather_Maximum;
lv_obj_t * ui_Label_Weather_Night;
lv_obj_t * ui_Label_Weather_Unit2;
lv_obj_t * ui_Label_Weather_Night_Condition;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_weather_icon_[40] = {&ui_img_weather_icons_weather_icon_1_png, &ui_img_weather_icons_weather_icon_11_png, &ui_img_weather_icons_weather_icon_12_png, &ui_img_weather_icons_weather_icon_2_png, &ui_img_weather_icons_weather_icon_13_png, &ui_img_weather_icons_weather_icon_3_png, &ui_img_weather_icons_weather_icon_14_png, &ui_img_weather_icons_weather_icon_4_png, &ui_img_weather_icons_weather_icon_15_png, &ui_img_weather_icons_weather_icon_5_png, &ui_img_weather_icons_weather_icon_16_png, &ui_img_weather_icons_weather_icon_6_png, &ui_img_weather_icons_weather_icon_17_png, &ui_img_weather_icons_weather_icon_7_png, &ui_img_weather_icons_weather_icon_18_png, &ui_img_weather_icons_weather_icon_8_png, &ui_img_weather_icons_weather_icon_19_png, &ui_img_weather_icons_weather_icon_20_png, &ui_img_weather_icons_weather_icon_21_png, &ui_img_weather_icons_weather_icon_22_png, &ui_img_weather_icons_weather_icon_23_png, &ui_img_weather_icons_weather_icon_24_png, &ui_img_weather_icons_weather_icon_25_png, &ui_img_weather_icons_weather_icon_26_png, &ui_img_weather_icons_weather_icon_29_png, &ui_img_weather_icons_weather_icon_30_png, &ui_img_weather_icons_weather_icon_31_png, &ui_img_weather_icons_weather_icon_32_png, &ui_img_weather_icons_weather_icon_33_png, &ui_img_weather_icons_weather_icon_34_png, &ui_img_weather_icons_weather_icon_35_png, &ui_img_weather_icons_weather_icon_36_png, &ui_img_weather_icons_weather_icon_37_png, &ui_img_weather_icons_weather_icon_38_png, &ui_img_weather_icons_weather_icon_39_png, &ui_img_weather_icons_weather_icon_40_png, &ui_img_weather_icons_weather_icon_41_png, &ui_img_weather_icons_weather_icon_42_png, &ui_img_weather_icons_weather_icon_43_png, &ui_img_weather_icons_weather_icon_44_png};
const lv_img_dsc_t * ui_imgset_particle_[3] = {&ui_img_particle_1_png, &ui_img_particle_2_png, &ui_img_particle_3_png};
const lv_img_dsc_t * ui_imgset_water_[2] = {&ui_img_water_1_png, &ui_img_water_2_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void Particle1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 19800);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Particle2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 7920);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void Particle3_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 3960);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 0, -120);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void Fash_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 100);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 1200);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Wave1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 7000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 103);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Wave2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 5000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, -103);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void Off_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 600);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 255, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);

}
void On_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);
    ui_anim_user_data_t * PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_1_user_data->target = TargetObject;
    PropertyAnimation_1_user_data->val = -1;
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 600);
    lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_1, 100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_1, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_1);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_BTN_BGDriving(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_BTN_BGDriving, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BTN_BGService, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BTN_BGAlert, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Group_Wheather, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Service, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Driving, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        On_Animation(ui_Group_Driving, 0);
        _ui_state_modify(ui_BTN_BGDriving, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_BTN_BGService, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BGAlert, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }
}
void ui_event_BTN_BGService(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_BTN_BGService, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BTN_Driving, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BTN_BGAlert, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Group_Driving, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Service, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_Group_Wheather, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if(event_code == LV_EVENT_CLICKED) {
        On_Animation(ui_Group_Service, 0);
        _ui_state_modify(ui_BTN_BGAlert, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BGService, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_BTN_BGDriving, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }
}
void ui_event_BTN_BGAlert(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_BTN_BGAlert, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_BTN_BGService, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_BTN_BGDriving, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_Group_Wheather, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_Group_Service, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_Group_Driving, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
    if(event_code == LV_EVENT_CLICKED) {
        On_Animation(ui_Group_Wheather, 0);
        _ui_state_modify(ui_BTN_BGDriving, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BGService, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_BTN_BGAlert, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_Welcome_screen_init();
    ui_Driving_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Welcome);
}
