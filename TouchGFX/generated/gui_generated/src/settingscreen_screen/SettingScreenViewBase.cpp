/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/settingscreen_screen/SettingScreenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


SettingScreenViewBase::SettingScreenViewBase() :
    buttonCallback(this, &SettingScreenViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 800, 600);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    container_settingScreen.setPosition(0, 0, 800, 606);

    BG_setting.setPosition(0, 0, 800, 606);
    BG_setting.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_settingScreen.add(BG_setting);

    BackToMainButton.setXY(28, 47);
    BackToMainButton.setBitmaps(touchgfx::Bitmap(BITMAP_BACKBUTTON_BIGGER_ID), touchgfx::Bitmap(BITMAP_BACKBUTTON_BIGGER_ID));
    BackToMainButton.setAction(buttonCallback);
    container_settingScreen.add(BackToMainButton);

    alarmButton.setXY(108, 259);
    alarmButton.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_2_ID), touchgfx::Bitmap(BITMAP_BUTTON_2_PRESSED_ID));
    container_settingScreen.add(alarmButton);

    text_alarms.setXY(137, 288);
    text_alarms.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    text_alarms.setLinespacing(0);
    Unicode::snprintf(text_alarmsBuffer, TEXT_ALARMS_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_NAWN).getText());
    text_alarms.setWildcard(text_alarmsBuffer);
    text_alarms.resizeToCurrentText();
    text_alarms.setTypedText(touchgfx::TypedText(T___SINGLEUSE_3XVI));
    container_settingScreen.add(text_alarms);

    arb_text_alarms.setXY(167, 283);
    arb_text_alarms.setVisible(false);
    arb_text_alarms.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    arb_text_alarms.setLinespacing(0);
    arb_text_alarms.setTypedText(touchgfx::TypedText(T___SINGLEUSE_JYH3));
    container_settingScreen.add(arb_text_alarms);

    deviceButton.setXY(338, 259);
    deviceButton.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_2_ID), touchgfx::Bitmap(BITMAP_BUTTON_2_PRESSED_ID));
    container_settingScreen.add(deviceButton);

    text_deviceS.setXY(359, 273);
    text_deviceS.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    text_deviceS.setLinespacing(0);
    touchgfx::Unicode::snprintf(text_deviceSBuffer1, TEXT_DEVICESBUFFER1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_QN30).getText());
    text_deviceS.setWildcard1(text_deviceSBuffer1);
    touchgfx::Unicode::snprintf(text_deviceSBuffer2, TEXT_DEVICESBUFFER2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_P9RC).getText());
    text_deviceS.setWildcard2(text_deviceSBuffer2);
    text_deviceS.resizeToCurrentText();
    text_deviceS.setTypedText(touchgfx::TypedText(T___SINGLEUSE_J2V0));
    container_settingScreen.add(text_deviceS);

    arb_text_deviceS.setXY(373, 261);
    arb_text_deviceS.setVisible(false);
    arb_text_deviceS.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    arb_text_deviceS.setLinespacing(0);
    arb_text_deviceS.setTypedText(touchgfx::TypedText(T___SINGLEUSE_SA2Y));
    container_settingScreen.add(arb_text_deviceS);

    PatientInfoButton.setXY(338, 125);
    PatientInfoButton.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_2_ID), touchgfx::Bitmap(BITMAP_BUTTON_2_PRESSED_ID));
    container_settingScreen.add(PatientInfoButton);

    text_patientInfo.setXY(366, 141);
    text_patientInfo.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    text_patientInfo.setLinespacing(0);
    text_patientInfo.setTypedText(touchgfx::TypedText(T___SINGLEUSE_A75X));
    container_settingScreen.add(text_patientInfo);

    arb_text_patientInfo.setXY(372, 127);
    arb_text_patientInfo.setVisible(false);
    arb_text_patientInfo.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    arb_text_patientInfo.setLinespacing(0);
    arb_text_patientInfo.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WZOK));
    container_settingScreen.add(arb_text_patientInfo);

    choose_backSetting.setXY(39, 59);
    choose_backSetting.setVisible(false);
    choose_backSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSEBACK_ID));
    container_settingScreen.add(choose_backSetting);

    ventSettingButton.setXY(108, 125);
    ventSettingButton.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_2_ID), touchgfx::Bitmap(BITMAP_BUTTON_2_PRESSED_ID));
    container_settingScreen.add(ventSettingButton);

    text_ventSetting.setXY(110, 141);
    text_ventSetting.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    text_ventSetting.setLinespacing(0);
    text_ventSetting.setTypedText(touchgfx::TypedText(T___SINGLEUSE_JPNA));
    container_settingScreen.add(text_ventSetting);

    arb_text_ventSetting.setXY(139, 127);
    arb_text_ventSetting.setVisible(false);
    arb_text_ventSetting.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    arb_text_ventSetting.setLinespacing(0);
    arb_text_ventSetting.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Y6EO));
    container_settingScreen.add(arb_text_ventSetting);

    trendsButton.setXY(568, 125);
    trendsButton.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_2_ID), touchgfx::Bitmap(BITMAP_BUTTON_2_PRESSED_ID));
    container_settingScreen.add(trendsButton);

    text_trends.setXY(599, 154);
    text_trends.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    text_trends.setLinespacing(0);
    Unicode::snprintf(text_trendsBuffer, TEXT_TRENDS_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_56E5).getText());
    text_trends.setWildcard(text_trendsBuffer);
    text_trends.resizeToCurrentText();
    text_trends.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WHJW));
    container_settingScreen.add(text_trends);

    arb_text_trends.setXY(609, 151);
    arb_text_trends.setVisible(false);
    arb_text_trends.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    arb_text_trends.setLinespacing(0);
    arb_text_trends.setTypedText(touchgfx::TypedText(T___SINGLEUSE_BEB3));
    container_settingScreen.add(arb_text_trends);

    deviceInfoButton.setXY(568, 259);
    deviceInfoButton.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_2_ID), touchgfx::Bitmap(BITMAP_BUTTON_2_PRESSED_ID));
    container_settingScreen.add(deviceInfoButton);

    text_deviceInfo.setXY(599, 273);
    text_deviceInfo.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    text_deviceInfo.setLinespacing(0);
    text_deviceInfo.setTypedText(touchgfx::TypedText(T___SINGLEUSE_GT0M));
    container_settingScreen.add(text_deviceInfo);

    arb_text_deviceInfo.setXY(574, 283);
    arb_text_deviceInfo.setVisible(false);
    arb_text_deviceInfo.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    arb_text_deviceInfo.setLinespacing(0);
    arb_text_deviceInfo.setTypedText(touchgfx::TypedText(T___SINGLEUSE_I7NL));
    container_settingScreen.add(arb_text_deviceInfo);

    circuitSettingButton.setXY(108, 389);
    circuitSettingButton.setBitmaps(touchgfx::Bitmap(BITMAP_BUTTON_2_ID), touchgfx::Bitmap(BITMAP_BUTTON_2_PRESSED_ID));
    container_settingScreen.add(circuitSettingButton);

    text_circuitSetting.setXY(128, 404);
    text_circuitSetting.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    text_circuitSetting.setLinespacing(0);
    text_circuitSetting.setTypedText(touchgfx::TypedText(T___SINGLEUSE_2UGU));
    container_settingScreen.add(text_circuitSetting);

    arb_text_circuitSetting.setXY(122, 415);
    arb_text_circuitSetting.setVisible(false);
    arb_text_circuitSetting.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    arb_text_circuitSetting.setLinespacing(0);
    arb_text_circuitSetting.setTypedText(touchgfx::TypedText(T___SINGLEUSE_NKRA));
    container_settingScreen.add(arb_text_circuitSetting);

    choose_deviceSetting.setXY(337, 259);
    choose_deviceSetting.setVisible(false);
    choose_deviceSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSE3_ID));
    container_settingScreen.add(choose_deviceSetting);

    choose_circuitSetting.setXY(107, 389);
    choose_circuitSetting.setVisible(false);
    choose_circuitSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSE3_ID));
    container_settingScreen.add(choose_circuitSetting);

    choose_deviceInfoSetting.setXY(567, 260);
    choose_deviceInfoSetting.setVisible(false);
    choose_deviceInfoSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSE3_ID));
    container_settingScreen.add(choose_deviceInfoSetting);

    choose_alarmSetting.setXY(107, 259);
    choose_alarmSetting.setVisible(false);
    choose_alarmSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSE3_ID));
    container_settingScreen.add(choose_alarmSetting);

    choose_trendSetting.setXY(567, 125);
    choose_trendSetting.setVisible(false);
    choose_trendSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSE3_ID));
    container_settingScreen.add(choose_trendSetting);

    choose_patientInfoSetting.setXY(337, 125);
    choose_patientInfoSetting.setVisible(false);
    choose_patientInfoSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSE3_ID));
    container_settingScreen.add(choose_patientInfoSetting);

    choose_ventilationSetting.setXY(107, 125);
    choose_ventilationSetting.setVisible(false);
    choose_ventilationSetting.setBitmap(touchgfx::Bitmap(BITMAP_CHOOSE3_ID));
    container_settingScreen.add(choose_ventilationSetting);

    container_bottomBar.setPosition(0, 544, 800, 57);

    bg_bottomBar.setPosition(0, 0, 800, 56);
    bg_bottomBar.setColor(touchgfx::Color::getColorFromRGB(46, 46, 46));
    container_bottomBar.add(bg_bottomBar);

    box8.setPosition(97, 0, 5, 50);
    box8.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_bottomBar.add(box8);

    box8_1.setPosition(198, 0, 5, 50);
    box8_1.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_bottomBar.add(box8_1);

    box8_1_1.setPosition(288, 0, 5, 50);
    box8_1_1.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_bottomBar.add(box8_1_1);

    box8_1_2.setPosition(402, 0, 5, 50);
    box8_1_2.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_bottomBar.add(box8_1_2);

    box8_1_1_1.setPosition(502, 0, 5, 50);
    box8_1_1_1.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_bottomBar.add(box8_1_1_1);

    box8_1_1_2.setPosition(598, 0, 5, 50);
    box8_1_1_2.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_bottomBar.add(box8_1_1_2);

    box8_1_2_1.setPosition(698, 0, 5, 50);
    box8_1_2_1.setColor(touchgfx::Color::getColorFromRGB(23, 23, 23));
    container_bottomBar.add(box8_1_2_1);

    VTi_bar.setXY(23, 17);
    VTi_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    VTi_bar.setLinespacing(0);
    Unicode::snprintf(VTi_barBuffer, VTI_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_8MOC).getText());
    VTi_bar.setWildcard(VTi_barBuffer);
    VTi_bar.resizeToCurrentText();
    VTi_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_1S2O));
    container_bottomBar.add(VTi_bar);

    textArea11.setXY(34, -4);
    textArea11.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11.setLinespacing(0);
    textArea11.setTypedText(touchgfx::TypedText(T___SINGLEUSE_GFHM));
    container_bottomBar.add(textArea11);

    RR_bar.setXY(228, 17);
    RR_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    RR_bar.setLinespacing(0);
    Unicode::snprintf(RR_barBuffer, RR_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_45CZ).getText());
    RR_bar.setWildcard(RR_barBuffer);
    RR_bar.resizeToCurrentText();
    RR_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_WJIO));
    container_bottomBar.add(RR_bar);

    textArea11_1.setXY(233, -4);
    textArea11_1.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11_1.setLinespacing(0);
    textArea11_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Q2HB));
    container_bottomBar.add(textArea11_1);

    PEEP_bar.setXY(320, 17);
    PEEP_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    PEEP_bar.setLinespacing(0);
    Unicode::snprintf(PEEP_barBuffer, PEEP_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_BDPT).getText());
    PEEP_bar.setWildcard(PEEP_barBuffer);
    PEEP_bar.resizeToCurrentText();
    PEEP_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_XA3I));
    container_bottomBar.add(PEEP_bar);

    textArea11_2.setXY(326, -4);
    textArea11_2.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11_2.setLinespacing(0);
    textArea11_2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_5E8J));
    container_bottomBar.add(textArea11_2);

    PIP_bar.setXY(426, 17);
    PIP_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    PIP_bar.setLinespacing(0);
    Unicode::snprintf(PIP_barBuffer, PIP_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_UK6F).getText());
    PIP_bar.setWildcard(PIP_barBuffer);
    PIP_bar.resizeToCurrentText();
    PIP_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_HK6M));
    container_bottomBar.add(PIP_bar);

    textArea11_3.setXY(438, -4);
    textArea11_3.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11_3.setLinespacing(0);
    textArea11_3.setTypedText(touchgfx::TypedText(T___SINGLEUSE_QAP6));
    container_bottomBar.add(textArea11_3);

    Flow_bar.setXY(635, 17);
    Flow_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Flow_bar.setLinespacing(0);
    Unicode::snprintf(Flow_barBuffer, FLOW_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_H8D9).getText());
    Flow_bar.setWildcard(Flow_barBuffer);
    Flow_bar.resizeToCurrentText();
    Flow_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_96K2));
    container_bottomBar.add(Flow_bar);

    textArea11_4.setXY(630, -4);
    textArea11_4.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11_4.setLinespacing(0);
    textArea11_4.setTypedText(touchgfx::TypedText(T___SINGLEUSE_K018));
    container_bottomBar.add(textArea11_4);

    Ti_bar.setXY(525, 17);
    Ti_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Ti_bar.setLinespacing(0);
    Unicode::snprintf(Ti_barBuffer, TI_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_0XRS).getText());
    Ti_bar.setWildcard(Ti_barBuffer);
    Ti_bar.resizeToCurrentText();
    Ti_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_SGBC));
    container_bottomBar.add(Ti_bar);

    textArea11_5.setXY(542, -4);
    textArea11_5.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11_5.setLinespacing(0);
    textArea11_5.setTypedText(touchgfx::TypedText(T___SINGLEUSE_K9GT));
    container_bottomBar.add(textArea11_5);

    FiO2_bar.setXY(735, 17);
    FiO2_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    FiO2_bar.setLinespacing(0);
    Unicode::snprintf(FiO2_barBuffer, FIO2_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_6CVW).getText());
    FiO2_bar.setWildcard(FiO2_barBuffer);
    FiO2_bar.resizeToCurrentText();
    FiO2_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8ZEF));
    container_bottomBar.add(FiO2_bar);

    textArea11_6.setXY(730, -4);
    textArea11_6.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11_6.setLinespacing(0);
    textArea11_6.setTypedText(touchgfx::TypedText(T___SINGLEUSE_U6IF));
    container_bottomBar.add(textArea11_6);

    VTe_bar.setXY(125, 17);
    VTe_bar.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    VTe_bar.setLinespacing(0);
    Unicode::snprintf(VTe_barBuffer, VTE_BAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_A98R).getText());
    VTe_bar.setWildcard(VTe_barBuffer);
    VTe_bar.resizeToCurrentText();
    VTe_bar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_3WM6));
    container_bottomBar.add(VTe_bar);

    textArea11_7.setXY(135, -4);
    textArea11_7.setColor(touchgfx::Color::getColorFromRGB(235, 235, 235));
    textArea11_7.setLinespacing(0);
    textArea11_7.setTypedText(touchgfx::TypedText(T___SINGLEUSE_T84O));
    container_bottomBar.add(textArea11_7);

    container_topBar.setPosition(0, -2, 800, 52);

    batteryProgress.setXY(719, 18);
    batteryProgress.setProgressIndicatorPosition(2, 2, 50, 16);
    batteryProgress.setRange(0, 100);
    batteryProgress.setDirection(touchgfx::AbstractDirectionProgress::LEFT);
    batteryProgress.setBackground(touchgfx::Bitmap(BITMAP_BATTERY_LEFT_ID));
    batteryProgress.setColor(touchgfx::Color::getColorFromRGB(11, 219, 0));
    batteryProgress.setValue(50);
    container_topBar.add(batteryProgress);

    charging_image.setXY(775, 17);
    charging_image.setVisible(false);
    charging_image.setBitmap(touchgfx::Bitmap(BITMAP_BOLTWHITE_ID));
    container_topBar.add(charging_image);

    adult_image.setXY(666, 14);
    adult_image.setBitmap(touchgfx::Bitmap(BITMAP_ADULT_2_ID));
    container_topBar.add(adult_image);

    child_image.setXY(665, 14);
    child_image.setVisible(false);
    child_image.setBitmap(touchgfx::Bitmap(BITMAP_CHILD_ID));
    container_topBar.add(child_image);

    alarm_value_topBar.setXY(317, 17);
    alarm_value_topBar.setColor(touchgfx::Color::getColorFromRGB(194, 194, 194));
    alarm_value_topBar.setLinespacing(0);
    Unicode::snprintf(alarm_value_topBarBuffer, ALARM_VALUE_TOPBAR_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_T7W9).getText());
    alarm_value_topBar.setWildcard(alarm_value_topBarBuffer);
    alarm_value_topBar.resizeToCurrentText();
    alarm_value_topBar.setTypedText(touchgfx::TypedText(T___SINGLEUSE_J3P3));
    container_topBar.add(alarm_value_topBar);

    DateTxt.setXY(19, 15);
    DateTxt.setColor(touchgfx::Color::getColorFromRGB(214, 214, 214));
    DateTxt.setLinespacing(0);
    Unicode::snprintf(DateTxtBuffer, DATETXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_47CI).getText());
    DateTxt.setWildcard(DateTxtBuffer);
    DateTxt.resizeToCurrentText();
    DateTxt.setTypedText(touchgfx::TypedText(T___SINGLEUSE_Z03R));
    container_topBar.add(DateTxt);

    image_singleLeakCircuit.setXY(630, 14);
    image_singleLeakCircuit.setBitmap(touchgfx::Bitmap(BITMAP_SINGLELEAK_SMALL_ID));
    container_topBar.add(image_singleLeakCircuit);

    image_singleCircuit.setXY(632, 14);
    image_singleCircuit.setVisible(false);
    image_singleCircuit.setBitmap(touchgfx::Bitmap(BITMAP_SINGLECIRCUITSMALL_ID));
    container_topBar.add(image_singleCircuit);

    image_invasive_bar.setXY(598, 14);
    image_invasive_bar.setVisible(false);
    image_invasive_bar.setBitmap(touchgfx::Bitmap(BITMAP_INVASIVE_SMALL_ID));
    container_topBar.add(image_invasive_bar);

    image_mask_bar.setXY(595, 14);
    image_mask_bar.setBitmap(touchgfx::Bitmap(BITMAP_MASK_SMALL_ID));
    container_topBar.add(image_mask_bar);

    alarm_imageYellow_bar.setXY(288, 18);
    alarm_imageYellow_bar.setVisible(false);
    alarm_imageYellow_bar.setBitmap(touchgfx::Bitmap(BITMAP_ALARM_YELLOW_ID));
    container_topBar.add(alarm_imageYellow_bar);

    alarm_imageRed_bar.setXY(289, 17);
    alarm_imageRed_bar.setVisible(false);
    alarm_imageRed_bar.setBitmap(touchgfx::Bitmap(BITMAP_ALARM_RED_ID));
    container_topBar.add(alarm_imageRed_bar);

    alarm_image_bar.setXY(289, 17);
    alarm_image_bar.setBitmap(touchgfx::Bitmap(BITMAP_ALARM_ID));
    container_topBar.add(alarm_image_bar);

    activeAlarms_button.setXY(285, 12);
    activeAlarms_button.setBitmaps(touchgfx::Bitmap(BITMAP_ACTIVEALARMBUTTON_ID), touchgfx::Bitmap(BITMAP_ACTIVEALARMBUTTON_ID));
    container_topBar.add(activeAlarms_button);

    image_mute_bar.setXY(213, 14);
    image_mute_bar.setVisible(false);
    image_mute_bar.setBitmap(touchgfx::Bitmap(BITMAP_SILENT_ID));
    container_topBar.add(image_mute_bar);

    mute_val.setXY(237, 17);
    mute_val.setVisible(false);
    mute_val.setColor(touchgfx::Color::getColorFromRGB(237, 213, 0));
    mute_val.setLinespacing(0);
    Unicode::snprintf(mute_valBuffer, MUTE_VAL_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_75JD).getText());
    mute_val.setWildcard(mute_valBuffer);
    mute_val.resizeToCurrentText();
    mute_val.setTypedText(touchgfx::TypedText(T___SINGLEUSE_FENV));
    container_topBar.add(mute_val);

    image_lock_bar.setXY(546, 14);
    image_lock_bar.setVisible(false);
    image_lock_bar.setBitmap(touchgfx::Bitmap(BITMAP_LOCK_ID));
    container_topBar.add(image_lock_bar);

    image_unlock_bar.setXY(546, 14);
    image_unlock_bar.setBitmap(touchgfx::Bitmap(BITMAP_UNLOCK_ID));
    container_topBar.add(image_unlock_bar);

    line1_1.setPosition(-4, 45, 809, 10);
    line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(46, 46, 46));
    line1_1.setPainter(line1_1Painter);
    line1_1.setStart(5, 5);
    line1_1.setEnd(802.4f, 5.0f);
    line1_1.setLineWidth(2);
    line1_1.setLineEndingStyle(touchgfx::Line::SQUARE_CAP_ENDING);
    container_topBar.add(line1_1);

    textArea12.setXY(338, 425);
    textArea12.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea12.setLinespacing(0);
    Unicode::snprintf(textArea12Buffer, TEXTAREA12_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_VCAM).getText());
    textArea12.setWildcard(textArea12Buffer);
    textArea12.resizeToCurrentText();
    textArea12.setTypedText(touchgfx::TypedText(T___SINGLEUSE_U3A4));

    add(__background);
    add(container_settingScreen);
    add(container_bottomBar);
    add(container_topBar);
    add(textArea12);
}

void SettingScreenViewBase::setupScreen()
{

}

void SettingScreenViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &BackToMainButton)
    {
        //ClickBackToMainButton
        //When BackToMainButton clicked change screen to screen
        //Go to screen with no screen transition
        application().gotoscreenScreenNoTransition();
    }
}