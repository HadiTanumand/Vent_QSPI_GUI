#ifndef SCREENVIEW_HPP
#define SCREENVIEW_HPP

#include <gui_generated/screen_screen/screenViewBase.hpp>
#include <gui/screen_screen/screenPresenter.hpp>
#include <touchgfx/Texts.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "main.h"
#include "quadspi.h"
#include "W25Q256FV_QSPI.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_it.h"
#include "buzzer.h"
#include <stdio.h>

class screenView : public screenViewBase
{
public:
	screenView();
	virtual ~screenView() {}
	virtual void setupScreen();
	virtual void tearDownScreen();
	virtual void handleTickEvent();
	virtual void ClickMonitorButton();
	float getPatientType();
	float getMaskType();
	float getCircuitType();
//	virtual void ClickVT();
//	virtual void ClickRR();
//	virtual void ClickTi();
//	virtual void ClickFlow();
//	virtual void ClickFiO2();
//	virtual void ClickSensitivity();
//	virtual void ClickPEEP();
//	virtual void ClickPControl();
//	virtual void ClickTrigger();
//	virtual void ClickRiseTime();
//	virtual void ClickPS();
//	virtual void ClickCyclingOff();
//	virtual void ClickCPAP();
	void updateDate();
	void UpdateButtonBarValues();
	void handleMainScreen();
	void ClickSettingButton();
	void updateIdealWeightParameter();
	void showAlert();
	void click_yesAlert();
	void click_patientInfo();
	void updateConfigsWildCards();
	void click_cancelAlert();
	void sendConfig();
	virtual void ClickStartVent();
	virtual void ClickStopVent();
	virtual void click_confirm();
	virtual void ClickRiseTime();
	virtual void ClickVT();
	virtual void ClickRR();
	virtual void ClickTi();
	virtual void ClickFlow();
	virtual void ClickFiO2();
	virtual void ClickSensitivity();
	virtual void ClickPEEP();
	virtual void ClickPControl();
	virtual void ClickTrigger();
	virtual void ClickPS();
	virtual void ClickCPAP();
	virtual void ClickIE();
	virtual void disableMainChoose();
	virtual void handleTrigger();
	virtual void handleRisetime();
	virtual void handleSens();
	virtual void handlePsupp();
	virtual void handleCPAP();
	virtual void handleFlow();
	virtual void handleTi();
	virtual void handleFiO2();
	virtual void handleIE();
	virtual void handleVT();
	virtual void handlePIP();
	virtual void handleRR();
	virtual void handlePEEP();
	virtual void handleAlert();
	
protected:
	int tickCounter;
	uint8_t h;
	uint8_t m;
	float mode_int; // between 1 and 9 => 1:CMV-VCV, 2:CMV-PCV, 3:AC-VCV, 4:AC-PCV, 5:SIMV_VCV, 6:SIMV_PCV, 7:PSV, 8:CPAP, 9:BiPAP
	char date[11];
	
	char trendDates[40][16];
	uint32_t TrendCurrAddr; // current address of the QSPI
	short int trendBuffCounter; // number of times buffer should send data to QSPI
	uint8_t patientNum; // 1 to 40
	uint8_t patientNumShowTrend; // 1 to 40
	uint32_t trendSizes[40]; //store size of each trend file
	uint8_t monitorState=0; // 0=> waves, 1=> .., 2=> ..

	enum State {INIT_AGE, INIT_CIRCUIT, LEARN, MAIN, VENT_SETTING, PATIENT_INFO, NEW_PATIENT, TRENDS_SCREEN, BACKUP, BACKUP_MODE, BACKUP_MODESCREEN,
		BACKUP_APNEA,	SETTING, PEEP, PEEP_CONF, PIP, PIP_CONF, PCONTROL_CONF, PCONTROLMAX_CONF, RR, RR_CONF, VT,	VT_CONF, IE, IE_CONF, FIO2, FIO2_MIN, FIO2_MAX, LEAK_MAX, LOWPEEP,
		FIO2_CONF, TI, TI_CONF, TIMAX_CONF, TIMIN_CONF, FLOW, TIINSPPAUSE_CONF, SENS, SENS_CONF, RISETIME, RISETIME_CONF,PSUPP, PSUPP_CONF, PSMAX_CONF, TRIGGER, FLOWSHAPE, FLOWSHAPE_CONF,
		TRIGGER_CONF, CPAP, CPAP_CONF, SVT_CONF, CYCLING_OFF,	CYCLING_OFF_CONF, MODE, AGE, WEIGHT, AUDIO, BRIGHTNESS, DEVICE, DEVICEINFO, DAY, MONTH,
		YEAR, WEEK, MINUTES, HOURS, ALARM, LANGUAGE, RR_MAX, RR_MIN, PRESSURE_MAX, PRESSURE_MIN,	VTI_MAX, VTE_MAX,	VTI_MIN, VTE_MIN, MVI_MAX, MVE_MAX,
		MVI_MIN, MVE_MIN, FIO2_ALARM, APNEA_ALARM, APNEA_ALARM_VAL, MASK_OR_NOT, MASKS, BACKUP_PEEP, BACKUP_TI, BACKUP_VT, BACKUP_FLOWSHAPE,
		BACKUP_PCONTROL, BACKUP_RR, BACKUP_RISETIME, ACTIVE_ALARMS, SPO2_MIN, SPO2_MAX, ALARM_NEXTPAGE, CIRCUIT_ALARM, PULSERATE_MAX, PULSERATE_MIN,
		OBSTRUCTION_ALARM, VENTSTOPED_ALARM, IPAPMAX_CONF, IPAP_CONF, EPAP_CONF, APNEA_DETECTION, ALERT
	};
	State state;
	State lastState;
	
	enum Alarms {
		NONE=0, LOW_P_H=4, OBSTRUCTION=5, HIGH_P_H=6, HIGH_P_M=41, HIGH_RR_H=17, LOW_RR_H=16, HIGH_MVI_H=10, LOW_MVI_H=9, HIGH_MVE_H=11, LOW_MVE_H=8, HIGH_VTI_H=15,
		HIGH_VTE_H=13, CRITIC_LOWBAT_H=26, BATT_INOPERABLE_H=29, HIGH_PEEP_M=43, LOW_PEEP_M=42
	};
	Alarms alarms;
	
	enum LastButton {
		STOPVENT_BUTTON = 1, LOCK_BUTTON = 2, UNLOCK_BUTTON = 3, WEIGHT_BUTTON = 4, CIRCUITSETTING_BUTTON = 5, CPR_BUTTON = 6
	};
	LastButton lastButton;
	
};

#endif // SCREENVIEW_HPP
