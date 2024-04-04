#include <gui/screen_screen/screenView.hpp>
#include <touchgfx/Color.hpp>

using namespace std;

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern QSPI_HandleTypeDef hqspi;
extern int16_t key1;
extern int16_t encoderCounter;
extern uint8_t flagvent;
extern uint8_t pressKey;
extern uint8_t alarmType_intval; // hight=3, medium=2, low=1, 0 off
extern int freq_sound;
extern int audio_sound;
extern RTC_HandleTypeDef hrtc;
extern RTC_TimeTypeDef RTC_Time;
extern RTC_DateTypeDef RTC_Date;


extern uint8_t isAlerting;
extern uint32_t flag;
extern uint32_t record;
extern float flag_startVent;
extern float lockScreen_intval; // 0:off, 1:on
extern float CPR_intval;// 0:off, 1:on
extern int isLockChanged;
extern int isCPRChanged;
extern float manualBreath_intval;
extern float silent_intval;

extern float RR_real;
extern float Ti_real;
extern float Te_real;
extern float VT_real;
extern float VTi_real;
extern float VTe_real;
extern float flow_real;
extern float TiInspPause_real;
extern float FiO2_real;
extern float LeakExp_real;
extern float pressure_real;
extern float pip_real; 
extern float peep_real;
extern float PIF_real;
extern float IPP_real;
extern float CMPL_real;
extern float AVP_real;
extern float Patm_real;
extern float leak_real;
extern float MVe_real;
extern float MVi_real;
extern float Res_real;
extern float alarm_real[6];
extern float bat_real;
extern float PEF_real;
extern float RSBI_real;
extern float SPO2_real;
extern float SpontTrig_real;
extern float SpontCycle_real;
extern float circuitDis_real;
extern float pulseRate_real;
extern float obstruction_real;
extern float check_data;
extern float measureBattTime_real;
extern float externalDC_real;

extern float old_check_data;
extern float fault_recieve; // 0 no fault // 1 fault in recieve

//extern uint8_t rx_buffer[700];

extern uint8_t tx_data[700];
uint8_t tx_config[700] = "conf";

uint16_t vent_lastHours[1];	  // store ventilation last time in QSPI32 
uint16_t vent_hours[1] = {0};  // store ventilation time in QSPI 
uint8_t vent_minutes[1] = {0}; // store ventilation time in QSPI 
uint8_t trend_alarm[30] = {0}; // store Alarms in QSPI 
uint32_t startAlarmPointer[1]; // store Alarms Pointer in QSPI 
uint8_t trend_data[2006] = {0}; // store Data in QSPI 
uint32_t startDataPointer[1]; // store Data Pointer in QSPI 
uint8_t trend_listAlarms[10][30];


uint16_t tmp;
int graphPIndex = 0;
int maskType_intval=-1; // 1:vented, 2:non-vented
int circuitType_intval=0; // 1:valve, 2:leak
float patientType_intval=1; // 1:adult, 2:pediatric
float interfaceType_intval = 0; // 1:mask, 2:invasive
float RR_alarm_maxVal = 30;
float RR_alarm_minVal = 10;
float pressure_alarm_maxVal = 60;
float MVi_alarm_maxVal = 20;
float MVi_alarm_minVal = 4;
float MVe_alarm_maxVal = 20;
float MVe_alarm_minVal = 4;
float FiO2_alarm_maxIntVal = 60;
float FiO2_alarm_minIntVal = 21;
float Leak_alarm_maxIntVal = 4;
float SPO2_alarm_maxIntVal = 145;
float SPO2_alarm_minIntVal = 60;
float backupMode_intval = 0;
bool isLowPEEP_alarm = false; // 0 ,1
bool isVentStoped_alarm = false; // 0 ,1
bool isFiO2Fake_alarm = false; // 0 ,1
bool isExtraBackup = false;
float pressure_alarm_minVal = 10;
float vti_alarm_maxVal = 1000;
float vti_alarm_minVal = 100;
float vte_alarm_maxVal = 800;
float vte_alarm_minVal = 200;
float apnea_alarmIntval = 30;
float apnea_backupIntval = 50;
float apneaDetection_intval = 1;
float PEEP_intval;
float EPAP_intval;
float IPAP_intval;
float IPAPMax_intval;
float backup_PEEP_intval;
float PEEP_tmp_intval;
float PControl_intval;
float PControlMax_intval;
float backup_PControl_intval;
float PControl_tmp_intval;
float RR_intval; 
float backup_RR_intval; 
float RR_tmp_intval;
float VT_intval; 
float backup_VT_intval; 
float VT_tmp_intval;
float IE_intval; 
float SafetyVT_tmp_intval;
float Ti_intval;
float Ti_max_intval;
float Ti_min_intval;
float backup_Ti_intval;
float Ti_tmp_intval;
float CPAP_intval;
float CPAP_tmp_intval;
float TiInspPause_intval;
float TiInspPause_tmp_intval;
float flowShape_intval; 
float backup_flowShape_intval; 
float flowShape_tmp_intval;
float riseTime_intval;
float backup_riseTime_intval;
float riseTime_tmp_intval;
float trigger_intval; // 0-> flow _ 1-> pressure
float trigger_tmp_intval;
float Psupp_intval;
float PSMax_intval;
float Psupp_tmp_intval;
float sens_intval;
float sens_tmp_intval;
float cyclingOff_intval;
float cyclingOff_tmp_intval;
float weight_intval;
float weight_tmp_intval;
float spo2_maxVal = 95;
float spo2_minVal = 88;
float pulseRate_maxIntVal = 120;
float pulseRate_minIntVal = 70;
float circuitDis_intval = 75;
float obstruction_intval = -1;
float safetyVT_intval = 150;
float PIF_maxVal = 105;
float PIF_minVal = 70;
float FiO2_intval;
float FiO2_tmp_intval;
uint8_t previousAlarms[6] = {0};
uint8_t newAlarms[6] = {0};
	
// static uint8_t turn=0;
bool isStartTrending = false;
bool isArabic = false;
bool isLoading = false;
bool modeFlag = false;
bool isAlarmTrend = true;
bool isAlarmChanged = false;
bool isCircuitSetting = false;
bool isAutoScale = true;
bool isConfigTransferd = false;
//item positions ----
int graphVPosx;
int graphVPosy;
int graphLineVPosx;
int graphLineVPosy;
int graphPPosx;
int graphPPosy;
int graphLinePPosx;
int graphLinePPosy;
int graphFPosx;
int graphFPosy;
int graphLineFPosx;
int graphLineFPosy;
int mainPosx1=549;
int mainPosx2=672;
int mainPosy1=194;
int mainPosy2=280;
int mainPosy3=366;
int settingPosx1=25; // 180 between them
int settingPosx2=205;
int settingPosx3=385; 
int settingPosx4=565;
int settingPosy1=190; // 120 between them
int settingPosy2=310;
int settingPosy3=430;
// ---- end positions
TextAreaWithOneWildcard* dataModeVector[4];
TextAreaWithOneWildcard* alarmsContentVector[10];
Unicode::UnicodeChar dataMode_buffers[4][10];
Unicode::UnicodeChar alarmsContent_buffers[10][25];
TextAreaWithOneWildcard* alarmsIndexesVector[10];
Unicode::UnicodeChar alarmsIndex_buffers[10][6];
TextAreaWithTwoWildcards* dataTimeVector[4];
TextAreaWithTwoWildcards* alarmsTimeVector[10];
Unicode::UnicodeChar dataTime_buffers1[4][12];
Unicode::UnicodeChar dataTime_buffers2[4][8];
Unicode::UnicodeChar alarmsTime_buffers1[10][12];
Unicode::UnicodeChar alarmsTime_buffers2[10][8];
uint8_t alarmMute_counter = 0;
int start_counter = 0;
uint16_t alarmCount=0;
uint16_t dataCount=0;
uint32_t qspiAddr32 = 32 * 1024 * 1024;
uint32_t qspiAddr30 = 30 * 1024 * 1024;
uint32_t qspiAddr20 = 20 * 1024 * 1024;
uint32_t qspiAddr25 = 25 * 1024 * 1024;
int8_t trndFileClickedNumber; // 10 file maximum -> 0 - 10
uint32_t trendShowSteps = 0;
uint32_t trendShowSteps_tmp = -1;
int trendDataCounter = 0; // 0-2006
bool isMemoryFree = true;
uint8_t trendAlarmValues[10000][30]; // total alarms 10000 and each 30 Bytes
uint8_t trendDataValues[4][2006]; // just load the 4 new values to show(all the qspi data trends is too much) 2006= 2k data + 10 time + 1 config
uint32_t pointerVentHours = qspiAddr32 - 3 * 4096; // start point for ventHours
uint32_t pointerAlarmTrends = qspiAddr32 - 80 * 4096;
uint32_t pointerDataTrends = qspiAddr20;
uint32_t pointerStartAlarmPointer = qspiAddr32 - 81 * 4096;
uint32_t pointerStartDataPointer = qspiAddr30;

screenView::screenView()
{
	
}
void screenView::setupScreen()
{
	//handle state
	state = MAIN;
	//patientType
	patientType_intval = getPatientType();
	if(patientType_intval == 0)
	{
		adult_image.setVisible(false);
		adult_image.invalidate();
		child_image.setVisible(true);
		child_image.invalidate();
	}
	else
	{
		child_image.setVisible(false);
		child_image.invalidate();
		adult_image.setVisible(true);
		adult_image.invalidate();
	}
	//maskType
	interfaceType_intval = getMaskType();
	if(interfaceType_intval == 0)
	{
		image_mask_bar.setVisible(false);
		image_mask_bar.invalidate();
		image_invasive_bar.setVisible(true);
		image_invasive_bar.invalidate();
	}
	else
	{
		image_mask_bar.setVisible(true);
		image_mask_bar.invalidate();
		image_invasive_bar.setVisible(false);
		image_invasive_bar.invalidate();
	}
	//circuitType
	circuitType_intval = getCircuitType();
	if(circuitType_intval == 0)
	{
		image_singleLeakCircuit.setVisible(false);
		image_singleLeakCircuit.invalidate();
		image_singleCircuit.setVisible(true);
		image_singleCircuit.invalidate();
	}
	else
	{
		image_singleLeakCircuit.setVisible(true);
		image_singleLeakCircuit.invalidate();
		image_singleCircuit.setVisible(false);
		image_singleCircuit.invalidate();
	}
	mode_int = 1;
	updateDate();
	
	graphVPosx = graph_v.getX();	
	graphVPosy = graph_v.getY();
	graphLineVPosx = container_graphVLines.getX();
	graphLineVPosy = container_graphVLines.getY();
	graphPPosx = graph_p.getX();
	graphPPosy = graph_p.getY();
	graphLinePPosx = container_graphPLines.getX();
	graphLinePPosy = container_graphPLines.getY();
	graphFPosx = graph_flow.getX();
	graphFPosy = graph_flow.getY();
	graphLineFPosx = container_graphFLines.getX();
	graphLineFPosy = container_graphFLines.getY();
}
void screenView::ClickSettingButton()
{
	SettingButton.executeAction();
}

void screenView::tearDownScreen()
{
	screenViewBase::tearDownScreen();
}

void screenView::handleTickEvent()
{	
	// actions in 1 s
	tickCounter++;
	if(tickCounter % 60 == 0){
		UpdateButtonBarValues();
				// check lock & CPR
		if(isLockChanged==1)
		{
			isLockChanged=0;
			if(image_unlock_bar.isVisible())
				lastButton = UNLOCK_BUTTON;
			else 
				lastButton = LOCK_BUTTON;
			showAlert();
		}
		else if(isCPRChanged==1)
		{
			isCPRChanged=0;
			lastButton = CPR_BUTTON;
			showAlert();
		}
	}
	
	//actions in 2 S
	if(tickCounter % 120 == 0)
	{
		//handle battery progress
				batteryProgress.setValue(bat_real);
		if(bat_real<25 && externalDC_real==0)
		{
			batteryProgress.setColor(Color::getColorFromRGB(255, 0, 0)); // red
			batteryProgress.invalidate();
		}
		else 
		{
			batteryProgress.setColor(Color::getColorFromRGB(0, 255, 0)); // green
			batteryProgress.invalidate();
		}
	}

	// check state
	if (state == MAIN)
			handleMainScreen();
	else if (state == PEEP)
		handlePEEP();
	else if (state == PIP)
		handlePIP();
	else if (state == RR)
		handleRR();
	else if (state == VT)
		handleVT();
	else if (state == IE)
		handleIE();
	else if (state == FIO2)
		handleFiO2();
	else if (state == TI)
		handleTi();
	else if (state == CPAP)
		handleCPAP();
	else if (state == FLOW)
		handleFlow();
	else if (state == SENS)
		handleSens();
	else if (state == RISETIME)
		handleRisetime();
	else if (state == TRIGGER)
		handleTrigger();
		else if (state == ALERT)
		handleAlert();
}
void screenView::ClickMonitorButton()
{
		//state monitor plus && monitorState in model change
	monitorState = (monitorState+1) % 4;
	presenter->SetMonitorStateInModel(monitorState);
	
}
void screenView::updateDate()
{
	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BIN);

	h = RTC_Time.Hours;
	m = RTC_Time.Minutes;
	digitalClock_setting.setTime24Hour(h, m, 2);
	digitalClock_setting.invalidate();

	date[0] = (char)(RTC_Date.Date / 10) + 48;
	date[1] = (RTC_Date.Date % 10) + 48;
	date[2] = ' ';

	uint8_t month = (RTC_Date.Month / 10 * 10) + (RTC_Date.Month % 10);

	switch (month)
	{
	case 1:
	{
		date[3] = 'J';
		date[4] = 'a';
		date[5] = 'n';
		break;
	}
	case 2:
	{
		date[3] = 'F';
		date[4] = 'e';
		date[5] = 'b';
		break;
	}
	case 3:
	{
		date[3] = 'M';
		date[4] = 'a';
		date[5] = 'r';
		break;
	}
	case 4:
	{
		date[3] = 'A';
		date[4] = 'p';
		date[5] = 'r';
		break;
	}
	case 5:
	{
		date[3] = 'M';
		date[4] = 'a';
		date[5] = 'y';
		break;
	}
	case 6:
	{
		date[3] = 'J';
		date[4] = 'u';
		date[5] = 'n';
		break;
	}
	case 7:
	{
		date[3] = 'J';
		date[4] = 'u';
		date[5] = 'l';
		break;
	}
	case 8:
	{
		date[3] = 'A';
		date[4] = 'u';
		date[5] = 'g';
		break;
	}
	case 9:
	{
		date[3] = 'S';
		date[4] = 'e';
		date[5] = 'p';
		break;
	}
	case 10:
	{
		date[3] = 'O';
		date[4] = 'c';
		date[5] = 't';
		break;
	}
	case 11:
	{
		date[3] = 'N';
		date[4] = 'o';
		date[5] = 'v';
		break;
	}
	case 12:
	{
		date[3] = 'D';
		date[4] = 'e';
		date[5] = 'c';
		break;
	}
	}

	date[6] = ' ';
	date[7] = '2';
	date[8] = '0';
	date[9] = (char)(RTC_Date.Year / 10) + 48;
	date[10] = (char)(RTC_Date.Year % 10) + 48;

	Unicode::strncpy(DateTxtBuffer, date, DATETXT_SIZE);
	DateTxt.resizeToCurrentText();
	DateTxt.invalidate();

	// for date setting
	char d[2] = {0};
	d[0] = date[0];
	d[1] = date[1];
	Unicode::strncpy(day_settingBuffer, d, 2);
	DateTxt.resizeToCurrentText();
	day_setting.invalidate();
	char m[4] = {0};
	m[0] = date[3];
	m[1] = date[4];
	m[2] = date[5];
	m[3] = ' ';
	Unicode::strncpy(month_settingBuffer, m, 4);
	DateTxt.resizeToCurrentText();
	month_setting.invalidate();
	char y[4] = {0};
	y[0] = date[7];
	y[1] = date[8];
	y[2] = date[9];
	y[3] = date[10];
	Unicode::strncpy(year_settingBuffer, y, 4);
	DateTxt.resizeToCurrentText();
	year_setting.invalidate();
}
void screenView::UpdateButtonBarValues()
{
		// set bar values
		Unicode::snprintf(RR_barBuffer, RR_BAR_SIZE, "%d", (int)RR_real);
		RR_bar.setWildcard1(RR_barBuffer);
		RR_bar.invalidate();
		Unicode::snprintfFloat(PEEP_barBuffer, PEEP_BAR_SIZE, "%.1f", peep_real);
		PEEP_bar.setWildcard1(PEEP_barBuffer);
		PEEP_bar.invalidate();
		Unicode::snprintfFloat(PIP_barBuffer, PIP_BAR_SIZE, "%.1f", pip_real);
		PIP_bar.setWildcard1(PIP_barBuffer);
		PIP_bar.invalidate();
		Unicode::snprintf(VTi_barBuffer, VTI_BAR_SIZE, "%d", (int)VTi_real);
		VTi_bar.setWildcard1(VTi_barBuffer);
		VTi_bar.resizeToCurrentTextWithAlignment();
		VTi_bar.invalidate();
		Unicode::snprintf(VTe_barBuffer, VTE_BAR_SIZE, "%d", (int)VTe_real);
		VTe_bar.setWildcard1(VTe_barBuffer);
		VTe_bar.resizeToCurrentTextWithAlignment();
		VTe_bar.invalidate();
		Unicode::snprintfFloat(Ti_barBuffer, TI_BAR_SIZE, "%.1f", Ti_real);
		Ti_bar.setWildcard1(Ti_barBuffer);
		Ti_bar.invalidate();
		Unicode::snprintf(FiO2_barBuffer, FIO2_BAR_SIZE, "%d", (int)FiO2_real);
		FiO2_bar.setWildcard1(FiO2_barBuffer);
		FiO2_bar.invalidate();
		Unicode::snprintf(Flow_barBuffer, FLOW_BAR_SIZE, "%d", (int)flow_real);
		Flow_bar.setWildcard1(Flow_barBuffer);
		Flow_bar.invalidate();
		//-----------------
}
void screenView::handleMainScreen()
{
	h = RTC_Time.Hours;
	m = RTC_Time.Minutes;

	// check big values
	if (VT_val_big.isVisible())
		ClickVT();
	if (RR_val_big.isVisible())
		ClickRR();
	if (Ti_val_big.isVisible())
		ClickTi();
	if (flow_val_big.isVisible())
		ClickFlow();
	if (FiO2_val_big.isVisible())
		ClickFiO2();
	if (sensivity_val_big.isVisible())
		ClickSensitivity();
	if (PEEP_val_big.isVisible())
		ClickPEEP();
	if (PControl_val_big.isVisible())
		ClickPControl();
	if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
		ClickTrigger();
	if (riseTime_val_big.isVisible())
		ClickRiseTime();
	if (PS_val_big.isVisible())
		ClickPS();
	if (CPAP_val_big.isVisible())
		ClickCPAP();

	switch (monitorState)
	{
	case 0:
	{
		// v and p
		if (graph_v.getY() != graphVPosy || graph_v.getX() != graphVPosx || !graph_p.isVisible())
		{
			if(isArabic)
			{
				txt_mode.setVisible(false);
				txt_mode.invalidate();
				arb_txt_mode.setVisible(true);
				arb_txt_mode.invalidate();
			}
			else
			{
				txt_mode.setVisible(true);
				txt_mode.invalidate();
				arb_txt_mode.setVisible(false);
				arb_txt_mode.invalidate();
			}
			modeTxt_val.setVisible(true);
			modeTxt_val.invalidate();
			
			if(flag_startVent==1)
			{
				if(isArabic)
				{
					arb_pauseButton.setVisible(true);
					arb_pauseButton.invalidate();	
				}
				else
				{
					pauseButton.setVisible(true);
					pauseButton.invalidate();	
				}
			}
			else
			{
				if(isArabic)
				{
					arb_startButton.setVisible(true);
					arb_startButton.invalidate();	
				}
				else
				{
					startButton.setVisible(true);
					startButton.invalidate();	
				}
			}
			
			container_monitoringDatas.setVisible(false);
			container_monitoringDatas.invalidate();

			graph_v.setX(graphVPosx);
			graph_v.setY(graphVPosy);
			graph_v.setVisible(true);
			container_graphVLines.setVisible(true);
			container_graphVLines.setXY(graphLineVPosx, graphLineVPosy);
			container_graphVLines.invalidate();
			graph_v.invalidate();
			
			
			graph_p.setVisible(true);
			graph_p.setY(graphPPosy);
			container_graphPLines.setVisible(true);
			container_graphPLines.setXY(graphLinePPosx, graphLinePPosy);
			container_graphPLines.invalidate();
			graph_p.invalidate();
			
			graph_flow.setVisible(false);
			graph_flow.setY(graphPPosy);
			container_graphFLines.setVisible(false);
			container_graphFLines.setXY(graphLineFPosx, graphLineFPosy);
			container_graphFLines.invalidate();
			graph_flow.invalidate();

			configuration_button.setVisible(true);
			configuration_button.invalidate();
			
			container_pressureMonitor.setVisible(false);
			container_pressureMonitor.invalidate();

			
			container_mainScreen.setVisible(false);
			container_mainScreen.invalidate();
			container_mainScreen.setVisible(true);
			container_mainScreen.invalidate();
		}
		break;
	}
	case 1:
	{
		// flow and p
		if (graph_flow.getY() != graph_v.getY() || !graph_p.isVisible())
		{
			graph_v.setVisible(false);
			graph_v.invalidate();
			container_graphVLines.setVisible(false);
			container_graphVLines.invalidate();
			
			graph_flow.setX(graphFPosx);
			graph_flow.setY(graphVPosy); //v is higher
			graph_flow.setVisible(true);
			container_graphFLines.setVisible(true);
			container_graphFLines.setXY(graphLineFPosx, graphLineVPosy + graphLineFPosy-graphFPosy+3);
			container_graphFLines.invalidate();
			graph_flow.invalidate();
			
			graph_p.setVisible(true);
			graph_p.setY(graphPPosy);
			container_graphPLines.setVisible(true);
			container_graphPLines.setXY(graphLinePPosx, graphLinePPosy);
			container_graphPLines.invalidate();
			graph_p.invalidate();
			
			
			container_mainScreen.setVisible(false);
			container_mainScreen.invalidate();
			container_mainScreen.setVisible(true);
			container_mainScreen.invalidate();
		}
		break;
	}
	case 2:
	{
		// v and flow and p bar
		if (!container_pressureMonitor.isVisible())
		{
			//	graph_v.setVisible(false);
			graph_v.moveTo(graphVPosx + 10, graphVPosy); // x=mainPosy2 y=34
			graph_v.setVisible(true);
			container_graphVLines.setVisible(true);
			container_graphVLines.setXY(graphLineVPosx + 10, graphLineVPosy);
			container_graphVLines.invalidate();
			graph_v.invalidate();
			//				graph_flow.setVisible(false);
			graph_flow.moveTo(graphFPosx + 10, graphFPosy); // xmainPosy2, y173
			graph_flow.setVisible(true);
			container_graphFLines.setVisible(true);
			container_graphFLines.setXY(graphLineFPosx + 10, graphLineFPosy);
			container_graphFLines.invalidate();
			graph_flow.invalidate();

			graph_p.setVisible(false);
			container_graphPLines.setVisible(false);
			container_graphPLines.invalidate();
			graph_p.invalidate();
			
			PEEP_lineVal.setY(352 - (peep_real * 5.33)+5); 
			Unicode::snprintfFloat(PEEP_lineValBuffer, PEEP_LINEVAL_SIZE, "%.1f", peep_real);
			PEEP_lineVal.setWildcard1(PEEP_lineValBuffer);
			PEEP_lineVal.invalidate();
			PIP_lineVal.setY(351.5 - (pip_real * 5.33)+5);
			Unicode::snprintfFloat(PIP_lineValBuffer, PIP_LINEVAL_SIZE, "%.1f", pip_real);
			PIP_lineVal.setWildcard1(PIP_lineValBuffer);
			PIP_lineVal.invalidate();
			
			PEEP_line.setY(352 - (peep_real * 5.33)); // default is y=351 => 0 in P_progress
			PIP_line.setY(351.5 - (pip_real * 5.33));	// default is y=351 => 0 in P_progress
			
			container_pressureMonitor.setVisible(true);
			container_pressureMonitor.invalidate();
			
			configuration_button.setVisible(true);
			configuration_button.invalidate();
		}
		break;
	}
	case 3:
	{
		if (!container_monitoringDatas.isVisible())
		{
			container_monitoringDatas.setVisible(true);
			container_monitoringDatas.invalidate();
			configuration_button.setVisible(false);
			configuration_button.invalidate();
			
			RR_container.setVisible(false);
			RR_container.invalidate();
			VT_container.setVisible(false);
			VT_container.invalidate();
			Ti_container.setVisible(false);
			Ti_container.invalidate();
			FiO2_container.setVisible(false);
			FiO2_container.invalidate();
			PEEP_container.setVisible(false);
			PEEP_container.invalidate();
			PControl_container.setVisible(false);
			PControl_container.invalidate();
			flow_container.setVisible(false);
			flow_container.invalidate();
			riseTime_container.setVisible(false);
			riseTime_container.invalidate();
			IE_container.setVisible(false);
			IE_container.invalidate();
			trigger_container.setVisible(false);
			trigger_container.invalidate();
			PS_container.setVisible(false);
			PS_container.invalidate();
			sensitivity_container.setVisible(false);
			sensitivity_container.invalidate();
			cyclingOff_container.setVisible(false);
			cyclingOff_container.invalidate();
			
			arb_txt_mode.setVisible(false);
			arb_txt_mode.invalidate();
			txt_mode.setVisible(false);
			txt_mode.invalidate();
			modeTxt_val.setVisible(false);
			modeTxt_val.invalidate();
			arb_startButton.setVisible(false);
			arb_startButton.invalidate();
			arb_pauseButton.setVisible(false);
			arb_pauseButton.invalidate();
			startButton.setVisible(false);
			startButton.invalidate();
			pauseButton.setVisible(false);
			pauseButton.invalidate();
			confirm_button.setVisible(false);
			confirm_button.invalidate();
			confirm_arbButton.setVisible(false);
			confirm_arbButton.invalidate();
			
			graph_v.setVisible(false);
			container_graphVLines.setVisible(false);
			container_graphVLines.invalidate();
			graph_v.invalidate();

			graph_flow.setVisible(false);
			container_graphFLines.setVisible(false);
			container_graphFLines.invalidate();
			graph_flow.invalidate();

			container_pressureMonitor.setVisible(false);
			container_pressureMonitor.invalidate();
		}

		
		if(tickCounter % 30 == 0) // show 2 times/second
		{
			
			// set monitor values
			Unicode::snprintfFloat(RR_monitoringtxtBuffer, RR_MONITORINGTXT_SIZE, "%.1f", RR_real);
			RR_monitoringtxt.setWildcard1(RR_monitoringtxtBuffer);
			RR_monitoringtxt.invalidate();
			Unicode::snprintfFloat(PEEP_monitoringtxtBuffer, PEEP_MONITORINGTXT_SIZE, "%.1f", peep_real);
			PEEP_monitoringtxt.setWildcard1(PEEP_monitoringtxtBuffer);
			PEEP_monitoringtxt.invalidate();
			Unicode::snprintfFloat(PIP_monitoringtxtBuffer, PIP_MONITORINGTXT_SIZE, "%.1f", pip_real);
			PIP_monitoringtxt.setWildcard1(PIP_monitoringtxtBuffer);
			PIP_monitoringtxt.invalidate();
			Unicode::snprintf(VTi_monitoringtxtBuffer, VTI_MONITORINGTXT_SIZE, "%d", (int)VTi_real);
			VTi_monitoringtxt.setWildcard1(VTi_monitoringtxtBuffer);
			VTi_monitoringtxt.invalidate();
			Unicode::snprintf(VTe_monitoringtxtBuffer, VTE_MONITORINGTXT_SIZE, "%d", (int)VTe_real);
			VTe_monitoringtxt.setWildcard1(VTe_monitoringtxtBuffer);
			VTe_monitoringtxt.invalidate();
			Unicode::snprintfFloat(Ti_monitoringtxtBuffer, TI_MONITORINGTXT_SIZE, "%.1f", Ti_real);
			Ti_monitoringtxt.setWildcard1(Ti_monitoringtxtBuffer);
			Ti_monitoringtxt.invalidate();
			Unicode::snprintfFloat(Te_monitoringtxtBuffer, TE_MONITORINGTXT_SIZE, "%.1f", Te_real);
			Te_monitoringtxt.setWildcard1(Te_monitoringtxtBuffer);
			Te_monitoringtxt.invalidate();
			Unicode::snprintfFloat(PIF_monitoringtxtBuffer, PIF_MONITORINGTXT_SIZE, "%.1f", PIF_real);
			PIF_monitoringtxt.setWildcard1(PIF_monitoringtxtBuffer);
			PIF_monitoringtxt.invalidate();
			Unicode::snprintfFloat(MVi_monitoringtxtBuffer, MVI_MONITORINGTXT_SIZE, "%.1f", MVi_real);
			MVi_monitoringtxt.setWildcard1(MVi_monitoringtxtBuffer);
			MVi_monitoringtxt.invalidate();
			Unicode::snprintfFloat(MVe_monitoringtxtBuffer, MVE_MONITORINGTXT_SIZE, "%.1f", MVe_real);
			MVe_monitoringtxt.setWildcard1(MVe_monitoringtxtBuffer);
			MVe_monitoringtxt.invalidate();
			Unicode::snprintfFloat(AVP_monitoringtxtBuffer, AVP_MONITORINGTXT_SIZE, "%.1f", AVP_real);
			AVP_monitoringtxt.setWildcard1(AVP_monitoringtxtBuffer);
			AVP_monitoringtxt.invalidate();
			Unicode::snprintfFloat(LEAK_monitoringtxtBuffer, LEAK_MONITORINGTXT_SIZE, "%.1f", leak_real);
			LEAK_monitoringtxt.setWildcard1(LEAK_monitoringtxtBuffer);
			LEAK_monitoringtxt.invalidate();
			Unicode::snprintfFloat(IE_monitoringtxtBuffer1, IE_MONITORINGTXTBUFFER1_SIZE, "%.1f", Ti_real);
			IE_monitoringtxt.setWildcard1(IE_monitoringtxtBuffer1);
			Unicode::snprintfFloat(IE_monitoringtxtBuffer2, IE_MONITORINGTXTBUFFER2_SIZE, "%.1f", Te_real);
			IE_monitoringtxt.setWildcard2(IE_monitoringtxtBuffer2);
			IE_monitoringtxt.invalidate();
			Unicode::snprintfFloat(CMPL_monitoringtxtBuffer, CMPL_MONITORINGTXT_SIZE, "%.1f", CMPL_real);
			CMPL_monitoringtxt.setWildcard1(CMPL_monitoringtxtBuffer);
			CMPL_monitoringtxt.invalidate();
			Unicode::snprintfFloat(FIO2_monitoringtxtBuffer, FIO2_MONITORINGTXT_SIZE, "%.1f", FiO2_real);
			FIO2_monitoringtxt.setWildcard1(FIO2_monitoringtxtBuffer);
			FIO2_monitoringtxt.invalidate();
			Unicode::snprintfFloat(IPP_monitoringtxtBuffer, IPP_MONITORINGTXT_SIZE, "%.1f", IPP_real);
			IPP_monitoringtxt.setWildcard1(IPP_monitoringtxtBuffer);
			IPP_monitoringtxt.invalidate();
			Unicode::snprintfFloat(Res_monitoringtxtBuffer, RES_MONITORINGTXT_SIZE, "%.1f", Res_real);
			Res_monitoringtxt.setWildcard1(Res_monitoringtxtBuffer);
			Res_monitoringtxt.invalidate();
			Unicode::snprintf(Patm_monitoringtxtBuffer, PATM_MONITORINGTXT_SIZE, "%d", (int)Patm_real);
			Patm_monitoringtxt.setWildcard1(Patm_monitoringtxtBuffer);
			Patm_monitoringtxt.invalidate();
			Unicode::snprintfFloat(PEF_monitoringtxtBuffer, PEF_MONITORINGTXT_SIZE, "%.1f", PEF_real);
			PEF_monitoringtxt.setWildcard1(PEF_monitoringtxtBuffer);
			PEF_monitoringtxt.invalidate();
			Unicode::snprintf(RSBI_monitoringtxtBuffer, RSBI_MONITORINGTXT_SIZE, "%d", (int)RSBI_real)
				;
			RSBI_monitoringtxt.setWildcard1(RSBI_monitoringtxtBuffer);
			RSBI_monitoringtxt.invalidate();
			Unicode::snprintf(SpontTrig_monitoringtxtBuffer, SPONTTRIG_MONITORINGTXT_SIZE, "%d", (int)SpontTrig_real);
			SpontTrig_monitoringtxt.setWildcard1(SpontTrig_monitoringtxtBuffer);
			SpontTrig_monitoringtxt.invalidate();
			Unicode::snprintf(SpontCylce_monitoringtxtBuffer, SPONTCYLCE_MONITORINGTXT_SIZE, "%d", (int)SpontCycle_real);
			SpontCylce_monitoringtxt.setWildcard1(SpontCylce_monitoringtxtBuffer);
			SpontCylce_monitoringtxt.invalidate();
			Unicode::snprintf(SPO2_monitoringtxtBuffer, SPO2_MONITORINGTXT_SIZE, "%d", (int)SPO2_real);
			SPO2_monitoringtxt.setWildcard1(SPO2_monitoringtxtBuffer);
			SPO2_monitoringtxt.invalidate();
			Unicode::snprintf(PulseRate_monitoringtxtBuffer, PULSERATE_MONITORINGTXT_SIZE, "%d", (int)pulseRate_real);
			PulseRate_monitoringtxt.setWildcard1(PulseRate_monitoringtxtBuffer);
			PulseRate_monitoringtxt.invalidate();
		}
		break;
	}
	}
	if (monitorState == 3)
	{
		if (key1 == 0)
		{
			pressKey = 0;
			if (choose_startPause.isVisible())
			{
				choose_startPause.setVisible(false);
				choose_startPause.invalidate();
			}
			if (choose_setting.isVisible())
			{
				choose_setting.setVisible(false);
				choose_setting.invalidate();
			}
			if (choose_monitor.isVisible())
			{
				choose_monitor.setVisible(false);
				choose_monitor.invalidate();
			}
			if (choose_FiO2.isVisible())
			{
				choose_FiO2.setVisible(false);
				choose_FiO2.invalidate();
			}
			if (choose_IE.isVisible())
			{
				choose_IE.setVisible(false);
				choose_IE.invalidate();
			}
			if (choose_PEEP.isVisible())
			{
				choose_PEEP.setVisible(false);
				choose_PEEP.invalidate();
			}
			if (choose_PIP.isVisible())
			{
				choose_PIP.setVisible(false);
				choose_PIP.invalidate();
			}
			if (choose_VT.isVisible())
			{
				choose_VT.setVisible(false);
				choose_VT.invalidate();
			}
			if (choose_RR.isVisible())
			{
				choose_RR.setVisible(false);
				choose_RR.invalidate();
			}
			if (choose_Ti.isVisible())
			{
				choose_Ti.setVisible(false);
				choose_Ti.invalidate();
			}
			if (choose_flow.isVisible())
			{
				choose_flow.setVisible(false);
				choose_flow.invalidate();
			}
			if (choose_cyclingOff.isVisible())
			{
				choose_cyclingOff.setVisible(false);
				choose_cyclingOff.invalidate();
			}
			if (choose_trigger.isVisible())
			{
				choose_trigger.setVisible(false);
				choose_trigger.invalidate();
			}
			if (choose_sensitivity.isVisible())
			{
				choose_sensitivity.setVisible(false);
				choose_sensitivity.invalidate();
			}
			if (choose_PS.isVisible())
			{
				choose_PS.setVisible(false);
				choose_PS.invalidate();
			}
			if (choose_riseTime.isVisible())
			{
				choose_riseTime.setVisible(false);
				choose_riseTime.invalidate();
			}
		}
		else if (key1 == 1)
		{
			if (choose_startPause.isVisible())
			{
				choose_startPause.setVisible(false);
				choose_startPause.invalidate();
			}
			if (!choose_setting.isVisible())
			{
				choose_setting.setVisible(true);
				choose_setting.invalidate();
			}
			if (choose_monitor.isVisible())
			{
				choose_monitor.setVisible(false);
				choose_monitor.invalidate();
			}
			if (choose_FiO2.isVisible())
			{
				choose_FiO2.setVisible(false);
				choose_FiO2.invalidate();
			}
			if (choose_IE.isVisible())
			{
				choose_IE.setVisible(false);
				choose_IE.invalidate();
			}
			if (choose_PEEP.isVisible())
			{
				choose_PEEP.setVisible(false);
				choose_PEEP.invalidate();
			}
			if (choose_PIP.isVisible())
			{
				choose_PIP.setVisible(false);
				choose_PIP.invalidate();
			}
			if (choose_VT.isVisible())
			{
				choose_VT.setVisible(false);
				choose_VT.invalidate();
			}
			if (choose_RR.isVisible())
			{
				choose_RR.setVisible(false);
				choose_RR.invalidate();
			}
			if (choose_Ti.isVisible())
			{
				choose_Ti.setVisible(false);
				choose_Ti.invalidate();
			}
			if (choose_flow.isVisible())
			{
				choose_flow.setVisible(false);
				choose_flow.invalidate();
			}
			if (choose_cyclingOff.isVisible())
			{
				choose_cyclingOff.setVisible(false);
				choose_cyclingOff.invalidate();
			}
			if (choose_trigger.isVisible())
			{
				choose_trigger.setVisible(false);
				choose_trigger.invalidate();
			}
			if (choose_sensitivity.isVisible())
			{
				choose_sensitivity.setVisible(false);
				choose_sensitivity.invalidate();
			}
			if (choose_PS.isVisible())
			{
				choose_PS.setVisible(false);
				choose_PS.invalidate();
			}
			if (choose_riseTime.isVisible())
			{
				choose_riseTime.setVisible(false);
				choose_riseTime.invalidate();
			}
			if (pressKey == 1)
			{
				pressKey=0;
				ClickSettingButton();
				// code for setting
			}
		}
		else if (key1 == 2)
		{
			if (choose_startPause.isVisible())
			{
				choose_startPause.setVisible(false);
				choose_startPause.invalidate();
			}
			if (choose_setting.isVisible())
			{
				choose_setting.setVisible(false);
				choose_setting.invalidate();
			}
			if (!choose_monitor.isVisible())
			{
				choose_monitor.setVisible(true);
				choose_monitor.invalidate();
			}
			if (choose_FiO2.isVisible())
			{
				choose_FiO2.setVisible(false);
				choose_FiO2.invalidate();
			}
			if (choose_IE.isVisible())
			{
				choose_IE.setVisible(false);
				choose_IE.invalidate();
			}
			if (choose_PEEP.isVisible())
			{
				choose_PEEP.setVisible(false);
				choose_PEEP.invalidate();
			}
			if (choose_PIP.isVisible())
			{
				choose_PIP.setVisible(false);
				choose_PIP.invalidate();
			}
			if (choose_VT.isVisible())
			{
				choose_VT.setVisible(false);
				choose_VT.invalidate();
			}
			if (choose_RR.isVisible())
			{
				choose_RR.setVisible(false);
				choose_RR.invalidate();
			}
			if (choose_Ti.isVisible())
			{
				choose_Ti.setVisible(false);
				choose_Ti.invalidate();
			}
			if (choose_flow.isVisible())
			{
				choose_flow.setVisible(false);
				choose_flow.invalidate();
			}
			if (choose_cyclingOff.isVisible())
			{
				choose_cyclingOff.setVisible(false);
				choose_cyclingOff.invalidate();
			}
			if (choose_trigger.isVisible())
			{
				choose_trigger.setVisible(false);
				choose_trigger.invalidate();
			}
			if (choose_sensitivity.isVisible())
			{
				choose_sensitivity.setVisible(false);
				choose_sensitivity.invalidate();
			}
			if (choose_PS.isVisible())
			{
				choose_PS.setVisible(false);
				choose_PS.invalidate();
			}
			if (choose_riseTime.isVisible())
			{
				choose_riseTime.setVisible(false);
				choose_riseTime.invalidate();
			}
			if (pressKey == 1)
			{
				// code for monitor
				pressKey = 0;
				ClickMonitorButton();
			}
		}
		else if(key1 > 2)
		{
			key1=0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
		}
		else if(key1 < 0)
		{
			key1=2;
			encoderCounter = 8 + 1;
			__HAL_TIM_SET_COUNTER(&htim3, 9);
		}
	}
	else
	{
		if (mode_int == 1) // cmv_vcv
		{
			if (!VT_container.isVisible() || VT_container.getX() != mainPosx1 || VT_container.getY() != mainPosy1)
			{
				VT_container.setVisible(true);
				VT_container.setXY(mainPosx1, mainPosy1);
				VT_container.invalidate();
				choose_VT.setXY(mainPosx1+5, mainPosy1+4);
				choose_VT.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx2 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx2, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx2+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx2 || PEEP_container.getY() != mainPosy2)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx2, mainPosy2);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx2+5, mainPosy2+4);
				choose_PEEP.invalidate();
			}
			if (!FiO2_container.isVisible() || FiO2_container.getX() != mainPosx1 || FiO2_container.getY() != mainPosy3)
			{
				FiO2_container.setVisible(true);
				FiO2_container.setXY(mainPosx1, mainPosy3);
				FiO2_container.invalidate();
				choose_FiO2.setXY(mainPosx1 + 5, mainPosy3+4);
				choose_FiO2.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (PControl_container.isVisible())
			{
				PControl_container.setVisible(false);
				PControl_container.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx1 || Ti_container.getY() != mainPosy2)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx1, mainPosy2);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx1+5, mainPosy2+4);
				choose_Ti.invalidate();
			}
			if (trigger_container.isVisible())
			{
				trigger_container.setVisible(false);
				trigger_container.invalidate();
			}
			if (sensitivity_container.isVisible())
			{
				sensitivity_container.setVisible(false);
				sensitivity_container.invalidate();
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(false);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (!choose_VT.isVisible())
				{
					choose_VT.setVisible(true);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for VT
					ClickVT();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickTi();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickPEEP();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (!choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(true);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickFiO2();
				}
			}
			else if (key1 == 10)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 10)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 10;
				encoderCounter = key1*4 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, encoderCounter);
			}
		}
		else if (mode_int == 2) // cmv_pcv
		{
			if (VT_container.isVisible())
			{
				VT_container.setVisible(false);
				VT_container.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx1 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx1, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx1 +5, mainPosy1 +4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx1 || PEEP_container.getY() != mainPosy2)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx1, mainPosy2);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx1 +5, mainPosy2+4);
				choose_PEEP.invalidate();
			}
			if (!FiO2_container.isVisible() || FiO2_container.getX() != mainPosx1 || FiO2_container.getY() != mainPosy3)
			{
				FiO2_container.setVisible(true);
				FiO2_container.setXY(mainPosx1, mainPosy3);
				FiO2_container.invalidate();
				choose_FiO2.setXY(mainPosx1+5, mainPosy3 +4);
				choose_FiO2.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (!PControl_container.isVisible() || PControl_container.getX() != mainPosx2 || PControl_container.getY() != mainPosy2)
			{
				PControl_container.setVisible(true);
				PControl_container.setXY(mainPosx2, mainPosy2);
				PControl_container.invalidate();
				choose_PIP.setXY(mainPosx2+5, mainPosy2+4);
				choose_PIP.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx2 || Ti_container.getY() != mainPosy1)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx2, mainPosy1);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx2+5, mainPosy1+4);
				choose_Ti.invalidate();
			}
			if (trigger_container.isVisible())
			{
				trigger_container.setVisible(false);
				trigger_container.invalidate();
			}
			if (sensitivity_container.isVisible())
			{
				sensitivity_container.setVisible(false);
				sensitivity_container.invalidate();
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(false);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for Ti
					ClickTi();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PEEP
					ClickPEEP();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (!choose_PIP.isVisible())
				{
					choose_PIP.setVisible(true);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PIP
					ClickPControl();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (!choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(true);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for FiO2
					ClickFiO2();
				}
			}

			else if (key1 == 10)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 10)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 10;
				encoderCounter = key1*4 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, encoderCounter);
			}
		}
		else if (mode_int == 3) // ac_vcv
		{
			if (!VT_container.isVisible() || VT_container.getX() != mainPosx1 || VT_container.getY() != mainPosy1)
			{
				VT_container.setVisible(true);
				VT_container.setXY(mainPosx1, mainPosy1);
				VT_container.invalidate();
				choose_VT.setXY(mainPosx1+5, mainPosy1+4);
				choose_VT.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx2 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx2, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx2+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (PEEP_container.isVisible())
			{
				PEEP_container.setVisible(false);
				PEEP_container.invalidate();
			}
			if (!FiO2_container.isVisible() || FiO2_container.getX() != mainPosx2 || FiO2_container.getY() != mainPosy3)
			{
				FiO2_container.setVisible(true);
				FiO2_container.setXY(mainPosx2, mainPosy3);
				FiO2_container.invalidate();
				choose_FiO2.setXY(mainPosx2+5, mainPosy3+4);
				choose_FiO2.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (PControl_container.isVisible())
			{
				PControl_container.setVisible(false);
				PControl_container.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx1 || Ti_container.getY() != mainPosy2)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx1, mainPosy2);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx1+5, mainPosy2+4);
				choose_Ti.invalidate();
			}
			if (!trigger_container.isVisible() || trigger_container.getX() != mainPosx2 || trigger_container.getY() != mainPosy2)
			{
				trigger_container.setVisible(true);
				trigger_container.setXY(mainPosx2, mainPosy2);
				trigger_container.invalidate();
				choose_trigger.setXY(mainPosx2+5, mainPosy2+4);
				choose_trigger.invalidate();
			}
			if (!sensitivity_container.isVisible() || sensitivity_container.getX() != mainPosx1 || sensitivity_container.getY() != mainPosy3)
			{
				sensitivity_container.setVisible(true);
				sensitivity_container.setXY(mainPosx1, mainPosy3);
				sensitivity_container.invalidate();
				choose_sensitivity.setXY(mainPosx1+5, mainPosy3+4);
				choose_sensitivity.invalidate();
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(false);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (!choose_VT.isVisible())
				{
					choose_VT.setVisible(true);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for VT
					ClickVT();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickTi();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (!choose_trigger.isVisible())
				{
					choose_trigger.setVisible(true);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickTrigger();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (!choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(true);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSensitivity();
				}
			}
			else if (key1 == 10)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (!choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(true);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickFiO2();
				}
			}
			else if (key1 == 11)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 11)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 11;
				encoderCounter = 44 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 44 + 1);
			}
		}
		else if (mode_int == 4) // ac_pcv
		{ 
			if (VT_container.isVisible())
			{
				VT_container.setVisible(false);
				VT_container.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx1 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx1, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx1+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx1 || PEEP_container.getY() != mainPosy2)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx1, mainPosy2);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx1+5, mainPosy2+4);
				choose_PEEP.invalidate();
			}
			if (FiO2_container.isVisible())
			{
				FiO2_container.setVisible(true);
				FiO2_container.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (!PControl_container.isVisible() || PControl_container.getX() != mainPosx2 || PControl_container.getY() != mainPosy2)
			{
				PControl_container.setVisible(true);
				PControl_container.setXY(mainPosx2, mainPosy2);
				PControl_container.invalidate();
				choose_PIP.setXY(mainPosx2+5, mainPosy2+4);
				choose_PIP.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx2 || Ti_container.getY() != mainPosy1)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx2, mainPosy1);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx2+5, mainPosy1+4);
				choose_Ti.invalidate();
			}
			if (!trigger_container.isVisible() || trigger_container.getX() != mainPosx1 || trigger_container.getY() != mainPosy3)
			{
				trigger_container.setVisible(true);
				trigger_container.setXY(mainPosx1, mainPosy3);
				trigger_container.invalidate();
				choose_trigger.setXY(mainPosx1+5, mainPosy3+4);
				choose_trigger.invalidate();
			}
			if (!sensitivity_container.isVisible() || sensitivity_container.getX() != mainPosx2 || sensitivity_container.getY() != mainPosy3)
			{
				sensitivity_container.setVisible(true);
				sensitivity_container.setXY(mainPosx2, mainPosy3);
				sensitivity_container.invalidate();
				choose_sensitivity.setXY(mainPosx2+5, mainPosy3+4);
				choose_sensitivity.invalidate();
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(true);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for Ti
					ClickTi();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PEEP
					ClickPEEP();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (!choose_PIP.isVisible())
				{
					choose_PIP.setVisible(true);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PIP
					ClickPControl();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (!choose_trigger.isVisible())
				{
					choose_trigger.setVisible(true);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for trigger
					ClickTrigger();
				}
			}
			else if (key1 == 10)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (!choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(true);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for sens
					ClickSensitivity();
				}
			}
			else if (key1 == 11)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 11)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 11;
				encoderCounter = 44 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 44 + 1);
			}
		}
		else if (mode_int == 5) // simv_vcv
		{
			if (!VT_container.isVisible() || VT_container.getX() != mainPosx1 || VT_container.getY() != mainPosy1)
			{
				VT_container.setVisible(true);
				VT_container.setXY(mainPosx1, mainPosy1);
				VT_container.invalidate();
				choose_VT.setXY(mainPosx1+5, mainPosy1+4);
				choose_VT.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx2 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx2, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx2+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx1 || PEEP_container.getY() != mainPosy3)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx1, mainPosy3);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx1+5, mainPosy3+4);
				choose_PEEP.invalidate();
			}
			if (FiO2_container.isVisible())
			{
				FiO2_container.setVisible(false);
				FiO2_container.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx1 || Ti_container.getY() != mainPosy2)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx1, mainPosy2);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx1+5, mainPosy2+4);
				choose_Ti.invalidate();
			}
			if (trigger_container.isVisible())
			{
				trigger_container.setVisible(false);
				trigger_container.invalidate();
			}
			if (sensitivity_container.isVisible())
			{
				sensitivity_container.setVisible(false);
				sensitivity_container.invalidate();
			}
			if (!PS_container.isVisible() || PS_container.getX() != mainPosx2 || PS_container.getY() != mainPosy3)
			{
				PS_container.setVisible(true);
				PS_container.setXY(mainPosx2, mainPosy3);
				PS_container.invalidate();
				choose_PS.setXY(mainPosx2+5, mainPosy3+4);
				choose_PS.invalidate();
			}
			if (!riseTime_container.isVisible() || riseTime_container.getX()!= mainPosx2 || riseTime_container.getY()!= mainPosy2)
			{
				riseTime_container.setVisible(true);
				riseTime_container.setXY(mainPosx2, mainPosy2);
				riseTime_container.invalidate();
				choose_riseTime.setXY(mainPosx2+5, mainPosy2+4);
				choose_riseTime.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
				if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (!choose_VT.isVisible())
				{
					choose_VT.setVisible(true);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for VT
					ClickVT();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for Ti
					ClickTi();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (!choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(true);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					//ClickriseTime();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PEEP
					ClickPEEP();
				}
			}
			else if (key1 == 10)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (!choose_PS.isVisible())
				{
					choose_PS.setVisible(true);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for Psupp
					//ClickPsupp();
				}
			}
			else if (key1 == 11)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 11)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 10;
				encoderCounter = 40 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 40 + 1);
			}
		}
		else if (mode_int == 6) // simv_pcv
		{
			if (VT_container.isVisible())
			{
				VT_container.setVisible(false);
				VT_container.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx1 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx1, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx1+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx1 || PEEP_container.getY() != mainPosy2)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx1, mainPosy2);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx1+5, mainPosy2+4);
				choose_PEEP.invalidate();
			}
			if (FiO2_container.isVisible())
			{
				FiO2_container.setVisible(true);
				FiO2_container.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (!PControl_container.isVisible() || PControl_container.getX() != mainPosx2 || PControl_container.getY() != mainPosy2)
			{
				PControl_container.setVisible(true);
				PControl_container.setXY(mainPosx2, mainPosy2);
				PControl_container.invalidate();
				choose_PIP.setXY(mainPosx2+5, mainPosy2+4);
				choose_PIP.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx2 || Ti_container.getY() != mainPosy1)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx2, mainPosy1);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx2+5, mainPosy1+4);
				choose_Ti.invalidate();
			}
			if (!trigger_container.isVisible() || trigger_container.getX() != mainPosx1 || trigger_container.getY() != mainPosy3)
			{
				trigger_container.setVisible(true);
				trigger_container.setXY(mainPosx1, mainPosy3);
				trigger_container.invalidate();
				choose_trigger.setXY(mainPosx1+5, mainPosy3+4);
				choose_trigger.invalidate();
			}
			if (!sensitivity_container.isVisible() || sensitivity_container.getX() != mainPosx2 || sensitivity_container.getY() != mainPosy3)
			{
				sensitivity_container.setVisible(true);
				sensitivity_container.setXY(mainPosx2, mainPosy3);
				sensitivity_container.invalidate();
				choose_sensitivity.setXY(mainPosx2+5, mainPosy3+4);
				choose_sensitivity.invalidate();
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(true);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for Ti
					ClickTi();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PEEP
					ClickPEEP();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (!choose_PIP.isVisible())
				{
					choose_PIP.setVisible(true);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PIP
					ClickPControl();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (!choose_trigger.isVisible())
				{
					choose_trigger.setVisible(true);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for trigger
					ClickTrigger();
				}
			}
			else if (key1 == 10)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (!choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(true);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for sense
					ClickSensitivity();
				}
			}
			else if (key1 == 11)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 11)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 11;
				encoderCounter = 44 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 44 + 1);
			}
		}
		else if (mode_int == 7) // psv
		{
			if (VT_container.isVisible())
			{
				VT_container.setVisible(false);
				VT_container.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx2 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx2, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx2+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx1 || PEEP_container.getY() != mainPosy2)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx1, mainPosy2);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx1+5, mainPosy2+4);
				choose_PEEP.invalidate();
			}
			if (FiO2_container.isVisible())
			{
				FiO2_container.setVisible(false);
				FiO2_container.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (Ti_container.isVisible())
			{
				Ti_container.setVisible(false);
				Ti_container.invalidate();
			}
			if (!trigger_container.isVisible() || trigger_container.getX() != mainPosx1 || trigger_container.getY() != mainPosy3)
			{
				trigger_container.setVisible(true);
				trigger_container.setXY(mainPosx1, mainPosy3);
				trigger_container.invalidate();
				choose_trigger.setXY(mainPosx1+5, mainPosy3+4);
				choose_trigger.invalidate();
			}
			if (!sensitivity_container.isVisible() || sensitivity_container.getX() != mainPosx2 || sensitivity_container.getY() != mainPosy3)
			{
				sensitivity_container.setVisible(true);
				sensitivity_container.setXY(mainPosx2, mainPosy3);
				sensitivity_container.invalidate();
				choose_sensitivity.setXY(mainPosx2+5, mainPosy3+4);
				choose_sensitivity.invalidate();
			}
			if (!PS_container.isVisible() || PS_container.getX() != mainPosx1 || PS_container.getY() != mainPosy1)
			{
				PS_container.setVisible(true);
				PS_container.setXY(mainPosx1, mainPosy1);
				PS_container.invalidate();
				choose_PS.setXY(mainPosx1+5, mainPosy1+4);
				choose_PS.invalidate();
			}
			if (!riseTime_container.isVisible() || riseTime_container.getX() != mainPosx2 || riseTime_container.getY() != mainPosy2)
			{
				riseTime_container.setVisible(true);
				riseTime_container.setXY(mainPosx2, mainPosy2);
				riseTime_container.invalidate();
				choose_riseTime.setXY(mainPosx2+5, mainPosy2+4);
				choose_riseTime.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (!choose_PS.isVisible())
				{
					choose_PS.setVisible(true);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					//ClickPsupp();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickRR();
				}
			}
			
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickPEEP();
				}
			}
			
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (!choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(true);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					//ClickriseTime();
				}
			}
			
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (!choose_trigger.isVisible())
				{
					choose_trigger.setVisible(true);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickTrigger();
				}
			}
			else if (key1 == 10)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (!choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(true);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSensitivity();
				}
			}
			else if (key1 == 11)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 11)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 11;
				encoderCounter = 44 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 44 + 1);
			}
		}
		else if (mode_int == 8) // cpap
		{
			if (VT_container.isVisible())
			{
				VT_container.setVisible(false);
				VT_container.invalidate();
			}
			if (RR_container.isVisible())
			{
				RR_container.setVisible(false);
				RR_container.invalidate();
			}
			if (PEEP_container.isVisible())
			{
				PEEP_container.setVisible(false);
				PEEP_container.invalidate();
			}
			if (!FiO2_container.isVisible() || FiO2_container.getX() != mainPosx2 || FiO2_container.getY() != mainPosy2)
			{
				FiO2_container.setVisible(true);
				FiO2_container.setXY(mainPosx2, mainPosy2);
				FiO2_container.invalidate();
				choose_FiO2.setXY(mainPosx2+5, mainPosy2+4);
				choose_FiO2.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (PControl_container.isVisible())
			{
				PControl_container.setVisible(false);
				PControl_container.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (Ti_container.isVisible())
			{
				Ti_container.setVisible(false);
				Ti_container.invalidate();
			}
			if (!trigger_container.isVisible() || trigger_container.getX()!= mainPosx1 || trigger_container.getY()!= mainPosy2)
			{
				trigger_container.setVisible(true);
				trigger_container.setXY(mainPosx1, mainPosy2);
				trigger_container.invalidate();
				choose_trigger.setXY(mainPosx1+5, mainPosy2+4);
				choose_trigger.invalidate();
			}
			if (!sensitivity_container.isVisible() || sensitivity_container.getX()!= mainPosx2 || sensitivity_container.getY() != mainPosy1)
			{
				sensitivity_container.setVisible(true);
				sensitivity_container.setXY(mainPosx2, mainPosy1);
				sensitivity_container.invalidate();
				choose_sensitivity.setXY(mainPosx2+5, mainPosy1+4);
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(false);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (!CPAP_container.isVisible() || CPAP_container.getX()!= mainPosx1 || CPAP_container.getY()!= mainPosy1)
			{
				CPAP_container.setVisible(true);
				CPAP_container.setXY(mainPosx1, mainPosy1);
				CPAP_container.invalidate();
				choose_CPAP.setXY(mainPosx1+5, mainPosy1+4);
				choose_CPAP.invalidate();
			}
			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (!choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(true);
					choose_CPAP.invalidate();
				}
				if (pressKey == 1)
				{
					ClickCPAP();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (!choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(true);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSensitivity();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (!choose_trigger.isVisible())
				{
					choose_trigger.setVisible(true);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickTrigger();
				}
			}
			
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (!choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(true);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickFiO2();
				}
			}
			else if (key1 == 9)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_CPAP.isVisible())
				{
					choose_CPAP.setVisible(false);
					choose_CPAP.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 9)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 9;
				encoderCounter = key1*4 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, encoderCounter);
			}
		}
		else if (mode_int == 9) // bipap
		{
			if (VT_container.isVisible())
			{
				VT_container.setVisible(false);
				VT_container.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx1, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx1+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx1 || PEEP_container.getY() != mainPosy2)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx1, mainPosy2);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx1+5, mainPosy2+4);
				choose_PEEP.invalidate();
			}
			if (!FiO2_container.isVisible() || FiO2_container.getX() != mainPosx1 || FiO2_container.getY() != mainPosy3)
			{
				FiO2_container.setVisible(true);
				FiO2_container.setXY(mainPosx1, mainPosy3);
				FiO2_container.invalidate();
				choose_FiO2.setXY(mainPosx1+5, mainPosy3+4);
				choose_FiO2.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (!PControl_container.isVisible() || PControl_container.getX() != mainPosx2 || PControl_container.getY() != mainPosy2)
			{
				PControl_container.setVisible(true);
				PControl_container.setXY(mainPosx2, mainPosy2);
				PControl_container.invalidate();
				choose_PIP.setXY(mainPosx2+5, mainPosy2+4);
				choose_PIP.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx2 || Ti_container.getY() != mainPosy1)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx2, mainPosy1);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx2+5, mainPosy1+4);
				choose_Ti.invalidate();
			}
			if (trigger_container.isVisible())
			{
				trigger_container.setVisible(false);
				trigger_container.invalidate();
			}
			if (sensitivity_container.isVisible())
			{
				sensitivity_container.setVisible(false);
				sensitivity_container.invalidate();
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(false);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}
			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for Ti
					ClickTi();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PEEP
					ClickPEEP();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (!choose_PIP.isVisible())
				{
					choose_PIP.setVisible(true);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for PIP
					ClickPControl();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (!choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(true);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for FiO2
					ClickFiO2();
				}
			}

			else if (key1 == 10)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//Clickconfirm();
					}
				}
			}
			else if (key1 > 10)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 9;
				encoderCounter = 36 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 36 + 1);
			}
		}
		else if (mode_int == 10) // CPR
		{
			if (!VT_container.isVisible() || VT_container.getX() != mainPosx1 || VT_container.getY() != mainPosy1)
			{
				VT_container.setVisible(true);
				VT_container.setXY(mainPosx1, mainPosy1);
				VT_container.invalidate();
				choose_VT.setXY(mainPosx1+5, mainPosy1+4);
				choose_VT.invalidate();
			}
			if (!RR_container.isVisible() || RR_container.getX() != mainPosx2 || RR_container.getY() != mainPosy1)
			{
				RR_container.setVisible(true);
				RR_container.setXY(mainPosx2, mainPosy1);
				RR_container.invalidate();
				choose_RR.setXY(mainPosx2+5, mainPosy1+4);
				choose_RR.invalidate();
			}
			if (!PEEP_container.isVisible() || PEEP_container.getX() != mainPosx2 || PEEP_container.getY() != mainPosy2)
			{
				PEEP_container.setVisible(true);
				PEEP_container.setXY(mainPosx2, mainPosy2);
				PEEP_container.invalidate();
				choose_PEEP.setXY(mainPosx2+5, mainPosy2+4);
				choose_PEEP.invalidate();
			}
			if (!FiO2_container.isVisible() || FiO2_container.getX() != mainPosx1 || FiO2_container.getY() != mainPosy3)
			{
				FiO2_container.setVisible(true);
				FiO2_container.setXY(mainPosx1, mainPosy3);
				FiO2_container.invalidate();
				choose_FiO2.setXY(mainPosx1+5, mainPosy3+4);
				choose_FiO2.invalidate();
			}
			if (flow_container.isVisible())
			{
				flow_container.setVisible(false);
				flow_container.invalidate();
			}
			if (PControl_container.isVisible())
			{
				PControl_container.setVisible(false);
				PControl_container.invalidate();
			}
			if (IE_container.isVisible())
			{
				IE_container.setVisible(false);
				IE_container.invalidate();
			}
			if (!Ti_container.isVisible() || Ti_container.getX() != mainPosx1 || Ti_container.getY() != mainPosy2)
			{
				Ti_container.setVisible(true);
				Ti_container.setXY(mainPosx1, mainPosy2);
				Ti_container.invalidate();
				choose_Ti.setXY(mainPosx1+5, mainPosy2+4);
				choose_Ti.invalidate();
			}
			if (trigger_container.isVisible())
			{
				trigger_container.setVisible(false);
				trigger_container.invalidate();
			}
			if (sensitivity_container.isVisible())
			{
				sensitivity_container.setVisible(false);
				sensitivity_container.invalidate();
			}
			if (PS_container.isVisible())
			{
				PS_container.setVisible(false);
				PS_container.invalidate();
			}
			if (riseTime_container.isVisible())
			{
				riseTime_container.setVisible(false);
				riseTime_container.invalidate();
			}
			if (cyclingOff_container.isVisible())
			{
				cyclingOff_container.setVisible(false);
				cyclingOff_container.invalidate();
			}
			if (CPAP_container.isVisible())
			{
				CPAP_container.setVisible(false);
				CPAP_container.invalidate();
			}

			if (key1 == 0)
			{
				pressKey = 0;
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
			}
			else if (key1 == 1)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (!choose_setting.isVisible())
				{
					choose_setting.setVisible(true);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickSettingButton();
					// code for setting
				}
			}
			else if (key1 == 2)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (!choose_monitor.isVisible())
				{
					choose_monitor.setVisible(true);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for monitor
					pressKey = 0;
					ClickMonitorButton();
				}
			}
			else if (key1 == 3)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickautoscaleButton();
				}
			}
			else if (key1 == 4)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (!choose_configuration.isVisible())
				{
					choose_configuration.setVisible(true);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					//ClickConfigurationButton();
				}
			}
			
			else if (key1 == 5)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (!choose_VT.isVisible())
				{
					choose_VT.setVisible(true);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for VT
					ClickVT();
				}
			}
			else if (key1 == 6)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (!choose_RR.isVisible())
				{
					choose_RR.setVisible(true);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					// code for RR
					ClickRR();
				}
			}
			else if (key1 == 7)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (!choose_Ti.isVisible())
				{
					choose_Ti.setVisible(true);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickTi();
				}
			}
			else if (key1 == 8)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (!choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(true);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickPEEP();
				}
			}
			else if (key1 == 9)
			{
				if (choose_startPause.isVisible())
				{
					choose_startPause.setVisible(false);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (!choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(true);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					ClickFiO2();
				}
			}
			else if (key1 == 10)
			{
				if (!choose_startPause.isVisible())
				{
					choose_startPause.setVisible(true);
					choose_startPause.invalidate();
				}
				if (choose_setting.isVisible())
				{
					choose_setting.setVisible(false);
					choose_setting.invalidate();
				}
				if (choose_monitor.isVisible())
				{
					choose_monitor.setVisible(false);
					choose_monitor.invalidate();
				}
				if (choose_configuration.isVisible())
				{
					choose_configuration.setVisible(false);
					choose_configuration.invalidate();
				}
				if (choose_FiO2.isVisible())
				{
					choose_FiO2.setVisible(false);
					choose_FiO2.invalidate();
				}
				if (choose_IE.isVisible())
				{
					choose_IE.setVisible(false);
					choose_IE.invalidate();
				}
				if (choose_PEEP.isVisible())
				{
					choose_PEEP.setVisible(false);
					choose_PEEP.invalidate();
				}
				if (choose_PIP.isVisible())
				{
					choose_PIP.setVisible(false);
					choose_PIP.invalidate();
				}
				if (choose_VT.isVisible())
				{
					choose_VT.setVisible(false);
					choose_VT.invalidate();
				}
				if (choose_RR.isVisible())
				{
					choose_RR.setVisible(false);
					choose_RR.invalidate();
				}
				if (choose_Ti.isVisible())
				{
					choose_Ti.setVisible(false);
					choose_Ti.invalidate();
				}
				if (choose_flow.isVisible())
				{
					choose_flow.setVisible(false);
					choose_flow.invalidate();
				}
				if (choose_cyclingOff.isVisible())
				{
					choose_cyclingOff.setVisible(false);
					choose_cyclingOff.invalidate();
				}
				if (choose_trigger.isVisible())
				{
					choose_trigger.setVisible(false);
					choose_trigger.invalidate();
				}
				if (choose_sensitivity.isVisible())
				{
					choose_sensitivity.setVisible(false);
					choose_sensitivity.invalidate();
				}
				if (choose_PS.isVisible())
				{
					choose_PS.setVisible(false);
					choose_PS.invalidate();
				}
				if (choose_riseTime.isVisible())
				{
					choose_riseTime.setVisible(false);
					choose_riseTime.invalidate();
				}
				if (pressKey == 1)
				{
					pressKey = 0;
					if (startButton.isVisible() || arb_startButton.isVisible())
					{
						// code for start ventilating
						flag_startVent = 1;
						startButton.executeAction();
					}
					else if (pauseButton.isVisible() || arb_pauseButton.isVisible())
					{
						flag_startVent = 0;
						pauseButton.executeAction();
					}
					else if (!pauseButton.isVisible() && !startButton.isVisible() && !arb_pauseButton.isVisible() && !arb_startButton.isVisible())
					{
						// code for confirming values
						//ClickConfirm();
					}
				}
			}
			else if (key1 > 10)
			{
				key1 = 0;
				encoderCounter = 0;
				__HAL_TIM_SET_COUNTER(&htim3, 0);
			}
			else if (key1 < 0)
			{
				key1 = 9;
				encoderCounter = 36 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 36 + 1);
			}
		}
		
	}
}
float screenView::getPatientType()
{
	return presenter->getPatientType();
}
float screenView::getMaskType()
{
	return presenter->getMaskType();
}
float screenView::getCircuitType()
{
	return presenter->getCircuitType();
}
void screenView::showAlert()
{
	isAlerting = 1;
	container_alert.setVisible(true);
	container_alert.invalidate();
	
	if(lastButton == WEIGHT_BUTTON)
	{
		if(isArabic)
		{
			alertMessage_arbConfigs.setVisible(true);
			alertMessage_arbConfigs.invalidate();
			
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
		}
		else
		{
			alertMessage_configs.setVisible(true);
			alertMessage_configs.invalidate();
			
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
		}
	}
	else if(lastButton == UNLOCK_BUTTON)
	{
		// it is going to be changed to locked
		if(isArabic)
		{
			alertMessage_arbLock.setVisible(true);
			alertMessage_arbLock.invalidate();
			
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
		}
		else
		{
			alertMessage_lock.setVisible(true);
			alertMessage_lock.invalidate();
			
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
		}
	}
	else if(lastButton == LOCK_BUTTON)
	{
		// it is going to be changed to Unlocked
		lockScreen_intval = 0;
		if(isArabic)
		{
			alertMessage_arbUnlock.setVisible(true);
			alertMessage_arbUnlock.invalidate();
			
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
		}
		else
		{
			alertMessage_unlock.setVisible(true);
			alertMessage_unlock.invalidate();
			
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
		}
	}	
	else if(lastButton == STOPVENT_BUTTON)
	{
		if(isArabic)
		{
			alertMessage_arbStopVent.setVisible(true);
			alertMessage_arbStopVent.invalidate();
			
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
		}
		else
		{
			alertMessage_stopVent.setVisible(true);
			alertMessage_stopVent.invalidate();
			
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
		}
	}
	else if(lastButton == CIRCUITSETTING_BUTTON)
	{
		if(isArabic)
		{
			alertMessage_arbStopVent.setVisible(true);
			alertMessage_arbStopVent.invalidate();
			
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
		}
		else
		{
			alertMessage_stopVent.setVisible(true);
			alertMessage_stopVent.invalidate();
			
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
		}
	}
	else if(lastButton == CPR_BUTTON)
	{
		if(isArabic)
		{
			alertMessage_arbCPR.setVisible(true);
			alertMessage_arbCPR.invalidate();
			
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
		}
		else
		{
			alertMessage_CPR.setVisible(true);
			alertMessage_CPR.invalidate();
			
			alertMessage_stopVent.setVisible(false);
			alertMessage_stopVent.invalidate();
			alertMessage_unlock.setVisible(false);
			alertMessage_unlock.invalidate();
			alertMessage_configs.setVisible(false);
			alertMessage_configs.invalidate();
			alertMessage_arbConfigs.setVisible(false);
			alertMessage_arbConfigs.invalidate();
			alertMessage_arbLock.setVisible(false);
			alertMessage_arbLock.invalidate();
			alertMessage_arbUnlock.setVisible(false);
			alertMessage_arbUnlock.invalidate();
			alertMessage_arbStopVent.setVisible(false);
			alertMessage_arbStopVent.invalidate();
			alertMessage_lock.setVisible(false);
			alertMessage_lock.invalidate();
		}
	}
	state = ALERT;
}
void screenView::click_yesAlert()
{
	isAlerting = 0;
	container_alert.setVisible(false);
	container_alert.invalidate();
	
	if(lastButton == WEIGHT_BUTTON)
	{
		weight_intval = weight_tmp_intval;
		
		Unicode::snprintf(weight_valBuffer, WEIGHT_VAL_SIZE, "%d", (int)weight_tmp_intval);
		weight_val.setWildcard1(weight_valBuffer);
		weight_val.invalidate();
		
		updateIdealWeightParameter();
		isLoading = true;
		click_patientInfo();
	}
	else if(lastButton == LOCK_BUTTON)
	{
		lockScreen_intval = 0;
		if(image_lock_bar.isVisible())
		{
			image_lock_bar.setVisible(false);
			image_lock_bar.invalidate();	
			image_unlock_bar.setVisible(true);
			image_unlock_bar.invalidate();	
		}
	}
	else if(lastButton == UNLOCK_BUTTON)
	{
		lockScreen_intval = 1;
		if(!image_lock_bar.isVisible())
		{
			image_lock_bar.setVisible(true);
			image_lock_bar.invalidate();	
			image_unlock_bar.setVisible(false);
			image_unlock_bar.invalidate();	
		}
	}
	else if(lastButton == STOPVENT_BUTTON)
	{
		flag_startVent = 0;
		arb_pauseButton.setVisible(false);
		arb_pauseButton.invalidate();
		pauseButton.setVisible(false);
		pauseButton.invalidate();
		if(isArabic)
		{
			arb_startButton.setVisible(true);
			arb_startButton.invalidate();
		}
		else
		{			
			startButton.setVisible(true);
			startButton.invalidate();
		}
		sendConfig();
	}
	
	else if(lastButton == CIRCUITSETTING_BUTTON)
	{
		// stop ventilating 
		flag_startVent = 0;
		arb_pauseButton.setVisible(false);
		arb_pauseButton.invalidate();
		pauseButton.setVisible(false);
		pauseButton.invalidate();
		if(isArabic)
		{
			arb_startButton.setVisible(true);
			arb_startButton.invalidate();
		}
		else
		{
			startButton.setVisible(true);
			startButton.invalidate();
		}
		sendConfig();
		
		// go to circuit setting		
		pressKey = 0;
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		//isCircuitSetting = true;
		container_initializeScreen.setVisible(true);
		container_initializeScreen.invalidate();
		container_initializeAge.setVisible(true);
		container_initializeAge.invalidate();
		container_settingScreen.setVisible(false);
		container_settingScreen.invalidate();
		container_mainScreen.setVisible(false);
		container_mainScreen.invalidate();
		state = INIT_AGE;
	}
	else if(lastButton == CPR_BUTTON)
	{
		//CPR_intval = 1;
		mode_int = 10; //CPR mode
		CPR_big_txt.setVisible(true);
		CPR_big_txt.invalidate();
		ClickStartVent();
	}
	state = lastState;
}
void screenView::click_cancelAlert()
{
	isAlerting = 0;
	container_alert.setVisible(false);
	container_alert.invalidate();
	if(lastButton == WEIGHT_BUTTON)
	{ 
		click_patientInfo();
		weight_tmp_intval = weight_intval;
		Unicode::snprintf(weight_valBuffer, WEIGHT_VAL_SIZE, "%d", (int)weight_tmp_intval);
		weight_val.setWildcard1(weight_valBuffer);
		weight_val.invalidate();
		
		RR_tmp_intval = RR_intval;
		VT_tmp_intval = VT_intval;
		PEEP_tmp_intval = PEEP_intval;
		PControl_tmp_intval = PControl_intval;
		Ti_tmp_intval = Ti_intval;
		FiO2_tmp_intval = FiO2_intval;
	}
	else if(lastButton == LOCK_BUTTON)
	{
		lockScreen_intval = 1;
	}
	else if(lastButton == STOPVENT_BUTTON)
	{
		lockScreen_intval = 0;
	}
	state = lastState;
}
void screenView::updateIdealWeightParameter()
{
	int idealWeight = weight_intval;
	
	PEEP_intval = 5;
	FiO2_intval = 21;
	
	if(idealWeight <= 5)
	{
		RR_intval = 35;
		VT_intval = 50;
		PControl_intval = 15;
	}
	else if(idealWeight <= 10)
	{
		RR_intval = 30;
		VT_intval = 70;
		PControl_intval = 15;
	}
	else if(idealWeight <= 15)
	{
		RR_intval = 23;
		VT_intval = 100;
		PControl_intval = 15;
	}
	else if(idealWeight <= 20)
	{
		RR_intval = 20;
		VT_intval = 120;
		PControl_intval = 20;
	}
	else if(idealWeight <= 30)
	{
		RR_intval = 18;
		VT_intval = 180;
		PControl_intval = 20;
	}
	else if(idealWeight <= 40)
	{
		RR_intval = 16;
		VT_intval = 240;
		PControl_intval = 20;
	}
	else if(idealWeight <= 50)
	{
		RR_intval = 14;
		VT_intval = 300;
		PControl_intval = 20;
	}
	else if(idealWeight <= 60)
	{
		RR_intval = 12;
		VT_intval = 360;
		PControl_intval = 20;
	}
	else
	{
		RR_intval = 12;
		VT_intval = 450;
		PControl_intval = 20;
	}
	
	Ti_intval = 60/RR_intval/3; // 1/3 of time for Ti and the rest and 2/3 is for Te (I/E:1/2)
	updateConfigsWildCards();
}
void screenView::click_patientInfo()
{
	pressKey = 0;
	key1 = 0;
	encoderCounter = 0;
	tmp = 0;
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	
	container_patientInfoSetting.setVisible(true);
	container_patientInfoSetting.invalidate();
	container_settingScreen.setVisible(false);
	container_settingScreen.invalidate();
	Unicode::snprintf(weight_valBuffer, WEIGHT_VAL_SIZE, "%d", (int)weight_intval);
	weight_val.setWildcard1(weight_valBuffer);
	weight_val.invalidate();
	state = PATIENT_INFO;
}
void screenView::updateConfigsWildCards()
{
	Unicode::snprintf(VT_valBuffer, VT_VAL_SIZE, "%d", (int)VT_intval);
	VT_val.setWildcard1(VT_valBuffer);
	VT_val.invalidate();
	Unicode::snprintf(RR_valBuffer, RR_VAL_SIZE, "%d", (int)RR_intval);
	RR_val.setWildcard1(RR_valBuffer);
	RR_val.invalidate();
	Unicode::snprintf(PEEP_valBuffer, PEEP_VAL_SIZE, "%d", (int)PEEP_intval);
	PEEP_val.setWildcard1(PEEP_valBuffer);
	PEEP_val.invalidate();
	Unicode::snprintf(PControl_valBuffer, PCONTROL_VAL_SIZE, "%d", (int)PControl_intval);
	PControl_val.setWildcard1(PControl_valBuffer);
	PControl_val.invalidate();
	Unicode::snprintf(FiO2_valBuffer, FIO2_VAL_SIZE, "%d", (int)FiO2_intval);
	FiO2_val.setWildcard1(FiO2_valBuffer);
	FiO2_val.invalidate();
	Unicode::snprintf(riseTime_valBuffer, RISETIME_VAL_SIZE, "%d", (int)riseTime_intval);
	riseTime_val.setWildcard1(riseTime_valBuffer);
	riseTime_val.invalidate();
	Unicode::snprintf(PS_valBuffer, PS_VAL_SIZE, "%d", (int)Psupp_intval);
	PS_val.setWildcard1(PS_valBuffer);
	PS_val.invalidate();
	Unicode::snprintfFloat(sensivity_valBuffer, SENSIVITY_VAL_SIZE, "%.1f", sens_intval);
	sensivity_val.setWildcard1(sensivity_valBuffer);
	sensivity_val.invalidate();
	Unicode::snprintfFloat(Ti_valBuffer, TI_VAL_SIZE, "%.1f", Ti_intval);
	Ti_val.setWildcard1(Ti_valBuffer);
	Ti_val.invalidate();
	Unicode::snprintf(cyclingOff_valBuffer, CYCLINGOFF_VAL_SIZE, "%d", (int)cyclingOff_intval);
	cyclingOff_val.setWildcard1(cyclingOff_valBuffer);
	cyclingOff_val.invalidate();
	
	
	trigger_intval = 1;// test for trigger unit
	
	if (trigger_intval == 0) // flow trigger
	{
		trigger_val_flow.setVisible(true);
		trigger_val_flow.invalidate();
		trigger_val_pressure.setVisible(false);
		trigger_val_pressure.invalidate();
		lpmtxt_sens.setVisible(true);
		lpmtxt_sens.invalidate();
		cmh2otxt_sens.setVisible(false);
		cmh2otxt_sens.invalidate();
	}
	else if (trigger_intval == 1)
	{
		trigger_val_flow.setVisible(false);
		trigger_val_flow.invalidate();
		trigger_val_pressure.setVisible(true);
		trigger_val_pressure.invalidate();

		lpmtxt_sens.setVisible(false);
		lpmtxt_sens.invalidate();
		cmh2otxt_sens.setVisible(true);
		cmh2otxt_sens.invalidate();
	}
}
void screenView::sendConfig()
{
	isConfigTransferd = true;
	float val;
	
	// fill tx_data
	strcpy((char*)tx_config, "conf");
	strcpy((char*)tx_config+4, "run");
	
	memcpy(tx_config+7, &flag_startVent, sizeof(float)); // 0-1
	
	strcpy((char*)tx_config+11, "mod");
	memcpy(tx_config+14, &mode_int, sizeof(float));
	
	strcpy((char*)tx_config+18, "rrh:");
	memcpy(tx_config+21, &RR_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+25, "rr:");
	memcpy(tx_config+28, &RR_intval, sizeof(float));
	
	strcpy((char*)tx_config+32, "rrl:");
	memcpy(tx_config+35, &RR_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+39, "peh");
	memcpy(tx_config+42, &pressure_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+46, "pep");
	memcpy(tx_config+49, &PEEP_intval, sizeof(float));
	
	strcpy((char*)tx_config+53, "pel");
	memcpy(tx_config+56, &pressure_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+60, "pih");
	memcpy(tx_config+63, &pressure_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+67, "fis");
	memcpy(tx_config+70, &FiO2_intval, sizeof(float));
	
	strcpy((char*)tx_config+74, "pil");
	memcpy(tx_config+77, &pressure_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+81, "prh");
	memcpy(tx_config+84, &pressure_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+88, "prl");
	memcpy(tx_config+91, &pressure_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+95, "vih");
	memcpy(tx_config+98, &vti_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+102, "vi:");
	memcpy(tx_config+105, &VT_intval, sizeof(float));
	
	strcpy((char*)tx_config+109, "vil");
	memcpy(tx_config+112, &vti_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+116, "veh");
	memcpy(tx_config+119, &vte_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+123, "vel");
	memcpy(tx_config+126, &vte_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+130, "meh");
	memcpy(tx_config+133, &MVe_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+137, "mel");
	memcpy(tx_config+140, &MVe_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+144, "mih");
	memcpy(tx_config+147, &MVi_alarm_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+151, "mil");
	memcpy(tx_config+154, &MVi_alarm_minVal, sizeof(float));
	
	strcpy((char*)tx_config+158, "apn");
	memcpy(tx_config+161, &apnea_backupIntval, sizeof(float));
	
	strcpy((char*)tx_config+165, "sph");
	memcpy(tx_config+168, &spo2_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+172, "spl");
	memcpy(tx_config+175, &spo2_minVal, sizeof(float));
	
	strcpy((char*)tx_config+179, "hrh");
	memcpy(tx_config+182, &pulseRate_maxIntVal, sizeof(float));
	
	strcpy((char*)tx_config+186, "hrl");
	memcpy(tx_config+189, &pulseRate_minIntVal, sizeof(float));
	
	strcpy((char*)tx_config+193, "fih");
	memcpy(tx_config+196, &FiO2_alarm_maxIntVal, sizeof(float));
	
	strcpy((char*)tx_config+200, "fil");
	memcpy(tx_config+203, &FiO2_alarm_minIntVal, sizeof(float));
	
	strcpy((char*)tx_config+207, "ti:");
	memcpy(tx_config+210, &Ti_intval, sizeof(float));
	
	strcpy((char*)tx_config+214, "fsh");
	memcpy(tx_config+217, &flowShape_intval, sizeof(float));
	
	strcpy((char*)tx_config+221, "tgp");
	memcpy(tx_config+224, &sens_intval, sizeof(float));
	
	strcpy((char*)tx_config+228, "pct");
	memcpy(tx_config+231, &PControl_intval, sizeof(float));
	
	strcpy((char*)tx_config+235, "rti");
	memcpy(tx_config+238, &riseTime_intval, sizeof(float));
	
	strcpy((char*)tx_config+242, "wkg");
	memcpy(tx_config+245, &weight_intval, sizeof(float));
	
//	strcpy((char*)tx_config+249, "svl");
//	memcpy(tx_config+252, &safetyVT_intval, sizeof(float));
	
	strcpy((char*)tx_config+256, "ps:");
	memcpy(tx_config+259, &Psupp_intval, sizeof(float));
	
	strcpy((char*)tx_config+263, "cyc");
	memcpy(tx_config+266, &cyclingOff_intval, sizeof(float));
	
	strcpy((char*)tx_config+270, "pfh");
	memcpy(tx_config+273, &PIF_maxVal, sizeof(float));
	
	strcpy((char*)tx_config+277, "pfl");
	memcpy(tx_config+280, &PIF_minVal, sizeof(float));
	
	strcpy((char*)tx_config+284, "tpf");
	memcpy(tx_config+287, &trigger_intval, sizeof(float));
	
	strcpy((char*)tx_config+291, "tin");
	memcpy(tx_config+294, &Ti_min_intval, sizeof(float));
	
	strcpy((char*)tx_config+298, "tix");
	memcpy(tx_config+301, &Ti_max_intval, sizeof(float));
	
	strcpy((char*)tx_config+305, "eps");
	memcpy(tx_config+308, &EPAP_intval, sizeof(float));
	
	strcpy((char*)tx_config+312, "ips");
	memcpy(tx_config+315, &IPAP_intval, sizeof(float));
	
	strcpy((char*)tx_config+319, "cps");
	memcpy(tx_config+322, &CPAP_intval, sizeof(float));
	
	strcpy((char*)tx_config+326, "crd");
	memcpy(tx_config+329, &circuitDis_intval, sizeof(float));
	
	strcpy((char*)tx_config+333, "hil");
	memcpy(tx_config+336, &Leak_alarm_maxIntVal, sizeof(float));
	
	val = (float)circuitType_intval;
	strcpy((char*)tx_config+340, "crt");
	memcpy(tx_config+343, &val, sizeof(float));
	
	strcpy((char*)tx_config+347, "ift");
	memcpy(tx_config+350, &interfaceType_intval, sizeof(float)); 
	
	strcpy((char*)tx_config+354, "obs");
	memcpy(tx_config+357, &obstruction_intval, sizeof(float)); 
	
	strcpy((char*)tx_config+361, "apr");
	memcpy(tx_config+364, &backupMode_intval, sizeof(float));
	
	strcpy((char*)tx_config+368, "apd");
	memcpy(tx_config+371, &apneaDetection_intval, sizeof(float));
	
	strcpy((char*)tx_config+375, "bvt");
	memcpy(tx_config+378, &backup_VT_intval, sizeof(float));
	
	strcpy((char*)tx_config+382, "bti");
	memcpy(tx_config+385, &backup_Ti_intval, sizeof(float));
	
	strcpy((char*)tx_config+389, "brr");
	memcpy(tx_config+392, &backup_RR_intval, sizeof(float));
	
	strcpy((char*)tx_config+396, "bpe");
	memcpy(tx_config+399, &backup_PEEP_intval, sizeof(float));
	
	strcpy((char*)tx_config+403, "bsh");
	memcpy(tx_config+406, &backup_flowShape_intval, sizeof(float));
	
	strcpy((char*)tx_config+410, "bpc");
	memcpy(tx_config+413, &backup_PControl_intval, sizeof(float));
	
	strcpy((char*)tx_config+417, "brt");
	memcpy(tx_config+420, &backup_riseTime_intval, sizeof(float));
	
	strcpy((char*)tx_config+424, "svt");
	memcpy(tx_config+427, &safetyVT_intval, sizeof(float));
	
	strcpy((char*)tx_config+431, "psm");
	memcpy(tx_config+434, &PSMax_intval, sizeof(float));
	
	strcpy((char*)tx_config+438, "pcm");
	memcpy(tx_config+441, &PControlMax_intval, sizeof(float));
	
	strcpy((char*)tx_config+445, "ipm");
	memcpy(tx_config+448, &IPAPMax_intval, sizeof(float));
	
	val = (float)maskType_intval;
	strcpy((char*)tx_config+452, "mst");
	memcpy(tx_config+455, &val, sizeof(float));
	
	val = (float)patientType_intval;
	strcpy((char*)tx_config+459, "ptt");
	memcpy(tx_config+462, &val, sizeof(float));
	
	strcpy((char*)tx_config+466, "Tpu");
	memcpy(tx_config+469, &TiInspPause_intval, sizeof(float));
	
	
	strcpy((char*)tx_config+473, "Mnb");
	memcpy(tx_config+476, &manualBreath_intval, sizeof(float));
	manualBreath_intval = 0;
	
	// send tx_data
	HAL_SPI_Transmit(&hspi2,tx_config,700,10);
	isConfigTransferd = false;
}
void screenView::ClickStartVent()
{
		graph_v.clear();
		graph_flow.clear();
		graph_p.clear();
		
		flag_startVent = 1;
		if(isArabic)
		{
			arb_pauseButton.setVisible(true);
			arb_pauseButton.invalidate();
		}
		else
		{
			pauseButton.setVisible(true);
			pauseButton.invalidate();
		}
		arb_startButton.setVisible(false);
		arb_startButton.invalidate();
		startButton.setVisible(false);
		startButton.invalidate();
		
		sendConfig();
}

void screenView::ClickRiseTime()
{
		pressKey = 0;
		disableMainChoose();

		if (!riseTime_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			riseTime_val.setVisible(false);
			riseTime_val.invalidate();
			riseTime_val_big.setVisible(true);
			riseTime_val_big.invalidate();
			riseTime_tmp_intval = riseTime_intval;
			Unicode::snprintf(riseTime_val_bigBuffer, RISETIME_VAL_BIG_SIZE, "%d", (int)riseTime_tmp_intval);
			riseTime_val_big.setWildcard1(riseTime_val_bigBuffer);
			riseTime_val_big.invalidate();
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = RISETIME;
		}
		else if (riseTime_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			riseTime_val_big.setVisible(false);
			riseTime_val_big.invalidate();
			riseTime_val.setVisible(true);
			riseTime_val.invalidate();
			Unicode::snprintf(riseTime_valBuffer, RISETIME_VAL_SIZE, "%d", (int)riseTime_tmp_intval);
			riseTime_val.setWildcard1(riseTime_valBuffer);
			riseTime_val.invalidate();
			state = MAIN;
		}
}
void screenView::ClickPEEP()
{
		pressKey = 0;
		disableMainChoose();

		if (!PEEP_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			PEEP_val.setVisible(false);
			PEEP_val.invalidate();
			PEEP_val_big.setVisible(true);
			PEEP_val_big.invalidate();
			
			PEEP_tmp_intval = PEEP_intval;
			if(PEEP_tmp_intval == -1)
			{
				Unicode::strncpy(PEEP_val_bigBuffer, "Off", 3);
				PEEP_val_big.setWildcard1(PEEP_val_bigBuffer);
				PEEP_val_big.resizeToCurrentText();
				PEEP_val_big.invalidate();
			}
			else
			{
				Unicode::snprintf(PEEP_val_bigBuffer, PEEP_VAL_BIG_SIZE, "%d", (int)PEEP_tmp_intval);
				PEEP_val_big.setWildcard1(PEEP_val_bigBuffer);
				PEEP_val_big.invalidate();
			}
			if(isArabic)
			{
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = PEEP;
		}
		else if (PEEP_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			PEEP_val_big.setVisible(false);
			PEEP_val_big.invalidate();
			PEEP_val.setVisible(true);
			PEEP_val.invalidate();
			
			PEEP_intval = PEEP_tmp_intval;
			if(PEEP_tmp_intval == -1)
			{
				Unicode::strncpy(PEEP_valBuffer, "Off", 3);
				PEEP_val.setWildcard1(PEEP_valBuffer);
				PEEP_val.resizeToCurrentText();
				PEEP_val.invalidate();
			}
			else
			{
				Unicode::snprintf(PEEP_valBuffer, PEEP_VAL_SIZE, "%d", (int)PEEP_tmp_intval);
				PEEP_val.setWildcard1(PEEP_valBuffer);
				PEEP_val.invalidate();
			}
			
			state = MAIN;
		}
}
void screenView::ClickPControl()
{
		pressKey = 0;
		disableMainChoose();

		if (!PControl_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			PControl_val.setVisible(false);
			PControl_val.invalidate();
			PControl_val_big.setVisible(true);
			PControl_val_big.invalidate();
			// PControl_tmp_intval = PControl_intval;
			Unicode::snprintf(PControl_val_bigBuffer, PCONTROL_VAL_BIG_SIZE, "%d", (int)PControl_tmp_intval);
			PControl_val_big.setWildcard1(PControl_val_bigBuffer);
			PControl_val_big.invalidate();
			
			if(isArabic)
			{
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = PIP;
		}
		else if (PControl_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			PControl_val_big.setVisible(false);
			PControl_val_big.invalidate();
			Unicode::snprintf(PControl_valBuffer, PCONTROL_VAL_SIZE, "%d", (int)PControl_tmp_intval);
			PControl_val.setWildcard1(PControl_valBuffer);
			PControl_val.setVisible(true);
			PControl_val.invalidate();
			
//			PIP_line.setVisible(false);
//			PIP_line.invalidate();
//			PIP_line.setY(351 - (PControl_tmp_intval * 5.33));
//			PIP_line.setVisible(true);
//			PIP_line.invalidate();
			//		pip = PControl_tmp_intval;
			state = MAIN;
		}
}
void screenView::ClickVT()
{
		pressKey = 0;
		disableMainChoose();

		if (!VT_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			VT_val.setVisible(false);
			VT_val.invalidate();
			VT_val_big.setVisible(true);
			VT_val_big.invalidate();
			// VT_tmp_intval = VT_intval;
			Unicode::snprintf(VT_val_bigBuffer, VT_VAL_BIG_SIZE, "%d", (int)VT_tmp_intval);
			VT_val_big.setWildcard1(VT_val_bigBuffer);
			VT_val_big.invalidate();
			
			if(isArabic)
			{
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = VT;
		}
		else if (VT_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			VT_val_big.setVisible(false);
			VT_val_big.invalidate();
			VT_val.setVisible(true);
			VT_val.invalidate();
			Unicode::snprintf(VT_valBuffer, VT_VAL_SIZE, "%d", (int)VT_tmp_intval);
			VT_val.setWildcard1(VT_valBuffer);
			VT_val.invalidate();
			
			//		volume_ramp = VT_tmp_intval;
			state = MAIN;
		}
}
void screenView::ClickIE()
{
		pressKey = 0;
		disableMainChoose();

		if (!container_IEVal_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			container_IEVal.setVisible(false);
			container_IEVal.invalidate();
			container_IEVal_big.setVisible(true);
			container_IEVal_big.invalidate();
			// SafetyVT_tmp_intval = IE_intval;
			Unicode::snprintf(IE_val_bigBuffer, IE_VAL_BIG_SIZE, "%d", (int)SafetyVT_tmp_intval);
			IE_val_big.setWildcard1(IE_val_bigBuffer);
			IE_val_big.invalidate();
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = IE;
		}
		else if (container_IEVal_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			container_IEVal_big.setVisible(false);
			container_IEVal_big.invalidate();
			container_IEVal.setVisible(true);
			container_IEVal.invalidate();
			Unicode::snprintf(IE_valBuffer, IE_VAL_SIZE, "%d", (int)SafetyVT_tmp_intval);
			IE_val.setWildcard1(IE_valBuffer);
			IE_val.invalidate();
			
			//		I_E = SafetyVT_tmp_intval;
			state = MAIN;
		}
}

void screenView::ClickRR()
{
		pressKey = 0;
		disableMainChoose();

		if (!RR_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			RR_val.setVisible(false);
			RR_val.invalidate();
			RR_val_big.setVisible(true);
			RR_val_big.invalidate();
			RR_tmp_intval = RR_intval;
			
			if(RR_tmp_intval == 0)
			{
				Unicode::strncpy(RR_val_bigBuffer, "Off", 3);
				RR_val_big.setWildcard1(RR_val_bigBuffer);
				RR_val_big.resizeToCurrentText();
				RR_val_big.invalidate();
			}
			else
			{
				Unicode::snprintf(RR_val_bigBuffer, RR_VAL_BIG_SIZE, "%d", (int)RR_tmp_intval);
				RR_val_big.setWildcard1(RR_val_bigBuffer);
				RR_val_big.invalidate();
			}
			
			if(isArabic)
			{
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = RR;
		}
		else if (RR_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			RR_val_big.setVisible(false);
			RR_val_big.invalidate();
			RR_val.setVisible(true);
			RR_val.invalidate();
			if(RR_tmp_intval == 0)
			{
				Unicode::strncpy(RR_valBuffer, "Off", 3);
				RR_val.setWildcard1(RR_valBuffer);
				RR_val.resizeToCurrentText();
				RR_val.invalidate();
			}
			else
			{
				Unicode::snprintf(RR_valBuffer, RR_VAL_SIZE, "%d", (int)RR_tmp_intval);
				RR_val.setWildcard1(RR_valBuffer);
				RR_val.invalidate();
			}			
			
			state = MAIN;
		}
}

void screenView::ClickFiO2()
{
	if(!isFiO2Fake_alarm)
	{
		pressKey = 0;
		return;
	}
		pressKey = 0;
		disableMainChoose();

		if (!FiO2_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			else if (CPAP_val_big.isVisible())
				ClickCPAP();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			FiO2_val.setVisible(false);
			FiO2_val.invalidate();
			FiO2_val_big.setVisible(true);
			FiO2_val_big.invalidate();
			FiO2_tmp_intval = FiO2_intval;
			Unicode::snprintf(FiO2_val_bigBuffer, FIO2_VAL_BIG_SIZE, "%d", (int)FiO2_tmp_intval);
			FiO2_val_big.setWildcard1(FiO2_val_bigBuffer);
			FiO2_val_big.invalidate();
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = FIO2;
		}
		else if (FiO2_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			FiO2_val_big.setVisible(false);
			FiO2_val_big.invalidate();
			FiO2_val.setVisible(true);
			FiO2_val.invalidate();
			Unicode::snprintf(FiO2_valBuffer, FIO2_VAL_SIZE, "%d", (int)FiO2_tmp_intval);
			FiO2_val.setWildcard1(FiO2_valBuffer);
			FiO2_val.invalidate();
			
			FiO2_intval = FiO2_tmp_intval; // have no real fio2 for now
			state = MAIN;
		}
}
void screenView::ClickTi()
{
		pressKey = 0;
		disableMainChoose();

		if (!Ti_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			if (PControl_val_big.isVisible())
				ClickPControl();
			if (VT_val_big.isVisible())
				ClickVT();
			if (container_IEVal_big.isVisible())
				ClickIE();
			if (RR_val_big.isVisible())
				ClickRR();
			if (FiO2_val_big.isVisible())
				ClickFiO2();
			if (flow_val_big.isVisible())
				ClickFlow();
			if (PS_val_big.isVisible())
				ClickPS();
			if (riseTime_val_big.isVisible())
				ClickRiseTime();
			if (sensivity_val_big.isVisible())
				ClickSensitivity();
			if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			Ti_val.setVisible(false);
			Ti_val.invalidate();
			Ti_val_big.setVisible(true);
			Ti_val_big.invalidate();
			// Ti_tmp_intval = Ti_intval;
			Unicode::snprintfFloat(Ti_val_bigBuffer, TI_VAL_BIG_SIZE, "%.1f", Ti_tmp_intval);
			Ti_val_big.setWildcard1(Ti_val_bigBuffer);
			Ti_val_big.invalidate();
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = TI;
		}
		else if (Ti_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			Ti_val_big.setVisible(false);
			Ti_val_big.invalidate();
			Ti_val.setVisible(true);
			Ti_val.invalidate();
			Unicode::snprintfFloat(Ti_valBuffer, TI_VAL_SIZE, "%.1f", Ti_tmp_intval);
			Ti_val.setWildcard1(Ti_valBuffer);
			Ti_val.invalidate();
			state = MAIN;
		}
}

void screenView::ClickFlow()
{
		pressKey = 0;
		disableMainChoose();

		if (!flow_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			flow_val.setVisible(false);
			flow_val.invalidate();
			flow_val_big.setVisible(true);
			flow_val_big.invalidate();
			Unicode::snprintf(flow_val_bigBuffer, FLOW_VAL_BIG_SIZE, "%d", (int)TiInspPause_tmp_intval);
			flow_val_big.setWildcard1(flow_val_bigBuffer);
			flow_val_big.invalidate();
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = FLOW;
		}
		else if (flow_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			flow_val_big.setVisible(false);
			flow_val_big.invalidate();
			flow_val.setVisible(true);
			flow_val.invalidate();
			Unicode::snprintf(flow_valBuffer, FLOW_VAL_SIZE, "%d", (int)TiInspPause_tmp_intval);
			flow_val.setWildcard1(flow_valBuffer);
			flow_val.invalidate();
			state = MAIN;
		}
}
void screenView::ClickPS()
{
		pressKey = 0;
		disableMainChoose();

		if (!PS_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			PS_val.setVisible(false);
			PS_val.invalidate();
			PS_val_big.setVisible(true);
			PS_val_big.invalidate();

			Unicode::snprintf(PS_val_bigBuffer, PS_VAL_BIG_SIZE, "%d", (int)Psupp_tmp_intval);
			PS_val_big.setWildcard1(PS_val_bigBuffer);
			PS_val_big.invalidate();
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = PSUPP;
		}
		else if (PS_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			PS_val_big.setVisible(false);
			PS_val_big.invalidate();
			PS_val.setVisible(true);
			PS_val.invalidate();
			Unicode::snprintf(PS_valBuffer, PS_VAL_SIZE, "%d", (int)Psupp_tmp_intval);
			PS_val.setWildcard1(PS_valBuffer);
			PS_val.invalidate();
			state = MAIN;
		}
}

void screenView::ClickSensitivity()
{
		pressKey = 0;
		disableMainChoose();

		if (!sensivity_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			else if (CPAP_val_big.isVisible())
				ClickCPAP();
			
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			sensivity_val.setVisible(false);
			sensivity_val.invalidate();
			sensivity_val_big.setVisible(true);
			sensivity_val_big.invalidate();
			sens_tmp_intval = sens_intval;
			if(sens_intval == -1)
			{
				Unicode::strncpy(sensivity_val_bigBuffer, "Off", 3);
				sensivity_val_big.setWildcard1(sensivity_val_bigBuffer);
				sensivity_val_big.resizeToCurrentText();
				sensivity_val_big.invalidate();
			}
			else
			{
				Unicode::snprintfFloat(sensivity_val_bigBuffer, SENSIVITY_VAL_BIG_SIZE, "%.1f", sens_tmp_intval);
				sensivity_val_big.setWildcard1(sensivity_val_bigBuffer);
				sensivity_val_big.invalidate();
			}
			
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = SENS;
		}
		else if (sensivity_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			sensivity_val_big.setVisible(false);
			sensivity_val_big.invalidate();
			sensivity_val.setVisible(true);
			sensivity_val.invalidate();
			sens_intval = sens_tmp_intval;
			if(sens_intval == -1)
			{
				Unicode::strncpy(sensivity_valBuffer, "Off", 3);
				sensivity_val.setWildcard1(sensivity_valBuffer);
				sensivity_val.resizeToCurrentText();
				sensivity_val.invalidate();
			}
			else
			{
				Unicode::snprintfFloat(sensivity_valBuffer, SENSIVITY_VAL_SIZE, "%.1f", sens_tmp_intval);
				sensivity_val.setWildcard1(sensivity_valBuffer);
				sensivity_val.invalidate();
			}
			
			state = MAIN;
		}
}

void screenView::ClickTrigger()
{
		pressKey = 0;
		disableMainChoose();

		if (!trigger_val_flow_big.isVisible() && !trigger_val_pressure_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (PS_val_big.isVisible())
				ClickPS();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			else if (CPAP_val_big.isVisible())
				ClickCPAP();

			pressKey = 0;
			if (trigger_val_flow.isVisible())
			{
				key1 = 0;
				encoderCounter = 0 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 0 + 1);
				trigger_val_flow.setVisible(false);
				trigger_val_flow.invalidate();
				trigger_val_flow_big.setVisible(true);
				trigger_val_flow_big.invalidate();
				trigger_tmp_intval = 0;
			}
			else if (trigger_val_pressure.isVisible())
			{
				key1 = 1;
				encoderCounter = 4 + 1;
				__HAL_TIM_SET_COUNTER(&htim3, 4 + 1);
				trigger_val_pressure.setVisible(false);
				trigger_val_pressure.invalidate();
				trigger_val_pressure_big.setVisible(true);
				trigger_val_pressure_big.invalidate();
				trigger_tmp_intval = 1;
			}
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = TRIGGER;
		}
		else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			if (trigger_val_flow_big.isVisible())
			{
				trigger_val_flow.setVisible(true);
				trigger_val_flow.invalidate();
				trigger_val_flow_big.setVisible(false);
				trigger_val_flow_big.invalidate();
				trigger_tmp_intval = 0;
			}
			else if (trigger_val_pressure_big.isVisible())
			{
				trigger_val_pressure.setVisible(true);
				trigger_val_pressure.invalidate();
				trigger_val_pressure_big.setVisible(false);
				trigger_val_pressure_big.invalidate();
				trigger_tmp_intval = 1;
			}
			state = MAIN;
		}
}
void screenView::ClickCPAP()
{
		pressKey = 0;
		disableMainChoose();

		if (!CPAP_val_big.isVisible())
		{
			if (PEEP_val_big.isVisible())
				ClickPEEP();
			else if (PControl_val_big.isVisible())
				ClickPControl();
			else if (VT_val_big.isVisible())
				ClickVT();
			else if (container_IEVal_big.isVisible())
				ClickIE();
			else if (RR_val_big.isVisible())
				ClickRR();
			else if (FiO2_val_big.isVisible())
				ClickFiO2();
			else if (Ti_val_big.isVisible())
				ClickTi();
			else if (flow_val_big.isVisible())
				ClickFlow();
			else if (riseTime_val_big.isVisible())
				ClickRiseTime();
			else if (sensivity_val_big.isVisible())
				ClickSensitivity();
			else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
				ClickTrigger();
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			CPAP_val.setVisible(false);
			CPAP_val.invalidate();
			CPAP_val_big.setVisible(true);
			CPAP_val_big.invalidate();

			Unicode::snprintf(CPAP_val_bigBuffer, CPAP_VAL_BIG_SIZE, "%d", (int)CPAP_tmp_intval);
			CPAP_val_big.setWildcard1(CPAP_val_bigBuffer);
			CPAP_val_big.invalidate();
			if(isArabic)
			{
				confirm_button.setVisible(false);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(true);
				confirm_arbButton.invalidate();
				arb_startButton.setVisible(false);
				arb_startButton.invalidate();
				arb_pauseButton.setVisible(false);
				arb_pauseButton.invalidate();
			}
			else
			{
				confirm_button.setVisible(true);
				confirm_button.invalidate();
				confirm_arbButton.setVisible(false);
				confirm_arbButton.invalidate();
				startButton.setVisible(false);
				startButton.invalidate();
				pauseButton.setVisible(false);
				pauseButton.invalidate();
			}
			state = CPAP;
		}
		else if (CPAP_val_big.isVisible())
		{
			pressKey = 0;
			tmp = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			CPAP_val_big.setVisible(false);
			CPAP_val_big.invalidate();
			CPAP_val.setVisible(true);
			CPAP_val.invalidate();
			Unicode::snprintf(CPAP_valBuffer, CPAP_VAL_SIZE, "%d", (int)CPAP_tmp_intval);
			CPAP_val.setWildcard1(CPAP_valBuffer);
			CPAP_val.invalidate();
			state = MAIN;
		}
}

void screenView::disableMainChoose()
{
	if (choose_startPause.isVisible())
	{
		choose_startPause.setVisible(false);
		choose_startPause.invalidate();
	}
	else if (choose_setting.isVisible())
	{
		choose_setting.setVisible(false);
		choose_setting.invalidate();
	}
	else if (choose_monitor.isVisible())
	{
		choose_monitor.setVisible(false);
		choose_monitor.invalidate();
	}
	else if (choose_FiO2.isVisible())
	{
		choose_FiO2.setVisible(false);
		choose_FiO2.invalidate();
	}
	else if (choose_IE.isVisible())
	{
		choose_IE.setVisible(false);
		choose_IE.invalidate();
	}
	else if (choose_PEEP.isVisible())
	{
		choose_PEEP.setVisible(false);
		choose_PEEP.invalidate();
	}
	else if (choose_PIP.isVisible())
	{
		choose_PIP.setVisible(false);
		choose_PIP.invalidate();
	}
	else if (choose_VT.isVisible())
	{
		choose_VT.setVisible(false);
		choose_VT.invalidate();
	}
	else if (choose_RR.isVisible())
	{
		choose_RR.setVisible(false);
		choose_RR.invalidate();
	}
	else if (choose_flow.isVisible())
	{
		choose_flow.setVisible(false);
		choose_flow.invalidate();
	}
	else if (choose_Ti.isVisible())
	{
		choose_Ti.setVisible(false);
		choose_Ti.invalidate();
	}
	else if (choose_trigger.isVisible())
	{
		choose_trigger.setVisible(false);
		choose_trigger.invalidate();
	}
	else if (choose_riseTime.isVisible())
	{
		choose_riseTime.setVisible(false);
		choose_riseTime.invalidate();
	}
	else if (choose_cyclingOff.isVisible())
	{
		choose_cyclingOff.setVisible(false);
		choose_cyclingOff.invalidate();
	}
	else if (choose_sensitivity.isVisible())
	{
		choose_sensitivity.setVisible(false);
		choose_sensitivity.invalidate();
	}
	else if (choose_PS.isVisible())
	{
		choose_PS.setVisible(false);
		choose_PS.invalidate();
	}
}
void screenView::ClickStopVent()
{
		click_confirm();
		
		lastState = MAIN;
		lastButton = STOPVENT_BUTTON;
		showAlert();
} 
void screenView::click_confirm()
{
		pressKey = 0;
		disableMainChoose();

		// handle uncomfimed big blue variables
		if (PEEP_val_big.isVisible())
			ClickPEEP();
		else if (PControl_val_big.isVisible())
			ClickPControl();
		else if (VT_val_big.isVisible())
			ClickVT();
		else if (container_IEVal_big.isVisible())
			ClickIE();
		else if (RR_val_big.isVisible())
			ClickRR();
		else if (FiO2_val_big.isVisible())
			ClickFiO2();
		else if (flow_val_big.isVisible())
			ClickFlow();
		else if (sensivity_val_big.isVisible())
			ClickSensitivity();
		else if (Ti_val_big.isVisible())
			ClickTi();
		else if (riseTime_val_big.isVisible())
			ClickRiseTime();
		else if (trigger_val_flow_big.isVisible() || trigger_val_pressure_big.isVisible())
			ClickTrigger();
		else if (PS_val_big.isVisible())
			ClickPS();

		confirm_button.setVisible(false);
		confirm_button.invalidate();
		confirm_arbButton.setVisible(false);
		confirm_arbButton.invalidate();
		if (flag_startVent == 0)
		{
			if(isArabic)
			{
				arb_startButton.setVisible(true);
				arb_startButton.invalidate();
			}
			else
			{
				startButton.setVisible(true);
				startButton.invalidate();
			}
		}
		else
		{
			if(isArabic)
			{
				arb_pauseButton.setVisible(true);
				arb_pauseButton.invalidate();
			}
			else
			{
				pauseButton.setVisible(true);
				pauseButton.invalidate();
			}
		}

		PEEP_intval = PEEP_tmp_intval;
		PControl_intval = PControl_tmp_intval;
		RR_intval = RR_tmp_intval;
		VT_intval = VT_tmp_intval;
		IE_intval = SafetyVT_tmp_intval;
		FiO2_intval = FiO2_tmp_intval;
		TiInspPause_intval = TiInspPause_tmp_intval;
		sens_intval = sens_tmp_intval;
		Ti_intval = Ti_tmp_intval;
		riseTime_intval = riseTime_tmp_intval;
		Psupp_intval = Psupp_tmp_intval;
		trigger_intval = trigger_tmp_intval;
		updateConfigsWildCards();
		sendConfig();
}
void screenView::handlePEEP()
{
	if (key1 != tmp)
	{
		if(PEEP_tmp_intval == -1 && (PEEP_tmp_intval + (float)(key1 - tmp)) > -1) PEEP_tmp_intval = 3;
		else if(PEEP_tmp_intval == 3 && (PEEP_tmp_intval + (float)(key1 - tmp)) < 3) PEEP_tmp_intval = -1;
		else PEEP_tmp_intval = PEEP_tmp_intval + (float)(key1 - tmp);
		
		if (PEEP_tmp_intval > 20)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			PEEP_tmp_intval = -1;
		}
		else if (PEEP_tmp_intval < -1)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			PEEP_tmp_intval = 20;
		}
		if(PEEP_tmp_intval == -1)
		{
			Unicode::strncpy(PEEP_val_bigBuffer, "Off", 3);
			PEEP_val_big.setWildcard1(PEEP_val_bigBuffer);
			PEEP_val_big.resizeToCurrentText();
			PEEP_val_big.invalidate();
		}
		else
		{
			Unicode::snprintf(PEEP_val_bigBuffer, PEEP_VAL_BIG_SIZE, "%d", (int)PEEP_tmp_intval);
			PEEP_val_big.setWildcard1(PEEP_val_bigBuffer);
			PEEP_val_big.invalidate();
		}
		
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		ClickPEEP();
	}
}
void screenView::handleRR()
{
	if (key1 != tmp)
	{
		float tmpval;
		if(RR_tmp_intval == 0 && (RR_tmp_intval + (float)(key1 - tmp)) > 0) tmpval = patientType_intval==1? 2:5;
		else if(patientType_intval==1 && RR_tmp_intval == 2 && (RR_tmp_intval + (float)(key1 - tmp)) < 2) tmpval = 0;
		else if(patientType_intval==2 && RR_tmp_intval == 5 && (RR_tmp_intval + (float)(key1 - tmp)) < 5) tmpval = 0;
		else tmpval = RR_tmp_intval + (float)(key1 - tmp);
		
		if ((tmpval>80&&patientType_intval==1) || (tmpval>50&&patientType_intval==2))
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			tmpval = 0;
			if (((60 / tmpval) - Ti_tmp_intval) / Ti_tmp_intval < 10 && ((60 / tmpval) - Ti_tmp_intval) / Ti_tmp_intval > 0 && Ti_tmp_intval / ((60 / tmpval) - Ti_tmp_intval) < 10 && Ti_tmp_intval / ((60 / tmpval) - Ti_tmp_intval) > 0)
			{
				RR_tmp_intval = tmpval;
			}
			else
			{
				tmpval = RR_tmp_intval = patientType_intval==1? 80:50;
			}
		}
		else if (tmpval < 0)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			tmpval = patientType_intval==1 ? 80:50;
			if (((60 / tmpval) - Ti_tmp_intval) / Ti_tmp_intval < 10 && ((60 / tmpval) - Ti_tmp_intval) / Ti_tmp_intval > 0 && Ti_tmp_intval / ((60 / tmpval) - Ti_tmp_intval) < 10 && Ti_tmp_intval / ((60 / tmpval) - Ti_tmp_intval) > 0)
			{
				RR_tmp_intval = tmpval;
			}
			else
			{
				RR_tmp_intval = tmpval = 0;
			}
		}
		else if (((60 / tmpval) - Ti_tmp_intval) / Ti_tmp_intval < 10 && ((60 / tmpval) - Ti_tmp_intval) / Ti_tmp_intval > 0 && Ti_tmp_intval / ((60 / tmpval) - Ti_tmp_intval) < 10 && Ti_tmp_intval / ((60 / tmpval) - Ti_tmp_intval) > 0)
			RR_tmp_intval = tmpval;
		
		if(RR_tmp_intval == 0)
		{
			Unicode::strncpy(RR_val_bigBuffer, "Off", 3);
			RR_val_big.setWildcard1(RR_val_bigBuffer);
			RR_val_big.resizeToCurrentText();
			RR_val_big.invalidate();				
		}
		else
		{
			Unicode::snprintf(RR_val_bigBuffer, RR_VAL_BIG_SIZE, "%d", (int)RR_tmp_intval);
			RR_val_big.setWildcard1(RR_val_bigBuffer);
			RR_val_big.invalidate();	
		}
		

		// change related things like: MV, Te, IE (in hint box)
		Unicode::snprintfFloat(MV_hint_valBuffer, MV_HINT_VAL_SIZE, "%.2f", ((float)VT_intval / 1000) * RR_tmp_intval);
		MV_hint_val.setWildcard1(MV_hint_valBuffer);
		MV_hint_val.invalidate();
		float i = 0;
		float e = 0;
		if (Ti_tmp_intval <= (60 / RR_tmp_intval) - Ti_tmp_intval)
		{
			i = 1;
			e = ((60 / RR_tmp_intval) - Ti_tmp_intval) / Ti_tmp_intval;
		}
		else
		{
			i = Ti_tmp_intval / ((60 / RR_tmp_intval) - Ti_tmp_intval);
			e = 1;
		}
		Unicode::snprintfFloat(Te_hint_valBuffer, TE_HINT_VAL_SIZE, "%.2f", ((60 / RR_tmp_intval) - Ti_tmp_intval));
		Te_hint_val.setWildcard1(Te_hint_valBuffer);
		Te_hint_val.invalidate();
		Unicode::snprintfFloat(IE_hint_valBuffer1, IE_HINT_VALBUFFER1_SIZE, "%.1f", i);
		IE_hint_val.setWildcard1(IE_hint_valBuffer1);
		IE_hint_val.invalidate();
		Unicode::snprintfFloat(IE_hint_valBuffer2, IE_HINT_VALBUFFER2_SIZE, "%.1f", e);
		IE_hint_val.setWildcard2(IE_hint_valBuffer2);
		IE_hint_val.invalidate();

		
		
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		tmp = key1 = 0;
		encoderCounter = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickRR();
	}
}
void screenView::handlePIP()
{
	if (key1 != tmp)
	{
		PControl_tmp_intval = PControl_tmp_intval + (float)(key1 - tmp);
		if (PControl_tmp_intval > 60)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			PControl_tmp_intval = PEEP_tmp_intval + 1;
		}
		else if (PControl_tmp_intval < PEEP_tmp_intval + 1)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			PControl_tmp_intval = 60;
		}
		Unicode::snprintf(PControl_val_bigBuffer, PCONTROL_VAL_BIG_SIZE, "%d", (int)PControl_tmp_intval);
		PControl_val_big.setWildcard1(PControl_val_bigBuffer);
		PControl_val_big.invalidate();
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		ClickPControl();
	}
}
void screenView::handleVT()
{
	if (key1 != tmp)
	{
		VT_tmp_intval = VT_tmp_intval + (key1 - tmp) * 10;
		if ((VT_tmp_intval > 2500 && patientType_intval==1) || (VT_tmp_intval > 350 && patientType_intval==2))
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			VT_tmp_intval = patientType_intval==1? 100:50;
		}
		else if ((VT_tmp_intval < 100 && patientType_intval==1) || (VT_tmp_intval < 50 && patientType_intval==2))
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			VT_tmp_intval = patientType_intval==1? 2500:350;
		}
		Unicode::snprintf(VT_val_bigBuffer, VT_VAL_BIG_SIZE, "%d", (int)VT_tmp_intval);
		VT_val_big.setWildcard1(VT_val_bigBuffer);
		VT_val_big.invalidate();
		// change related things like: MV, Te, IE (in hint box)
		Unicode::snprintfFloat(MV_hint_valBuffer, MV_HINT_VAL_SIZE, "%.2f", ((float)VT_intval / 1000) * RR_tmp_intval);
		MV_hint_val.setWildcard1(MV_hint_valBuffer);
		MV_hint_val.invalidate();
		float i = 0;
		float e = 0;
		if (Ti_tmp_intval <= (60 / RR_tmp_intval) - Ti_tmp_intval)
		{
			i = 1;
			e = ((60 / RR_tmp_intval) - Ti_tmp_intval) / Ti_tmp_intval;
		}
		else
		{
			i = Ti_tmp_intval / ((60 / RR_tmp_intval) - Ti_tmp_intval);
			e = 1;
		}
		Unicode::snprintfFloat(Te_hint_valBuffer, TE_HINT_VAL_SIZE, "%.2f", ((60 / RR_tmp_intval) - Ti_tmp_intval));
		Te_hint_val.setWildcard1(Te_hint_valBuffer);
		Te_hint_val.invalidate();
		Unicode::snprintfFloat(IE_hint_valBuffer1, IE_HINT_VALBUFFER1_SIZE, "%.1f", i);
		IE_hint_val.setWildcard1(IE_hint_valBuffer1);
		IE_hint_val.invalidate();
		Unicode::snprintfFloat(IE_hint_valBuffer2, IE_HINT_VALBUFFER2_SIZE, "%.1f", e);
		IE_hint_val.setWildcard2(IE_hint_valBuffer2);
		IE_hint_val.invalidate();

		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickVT();
	}
}
void screenView::handleIE()
{
	if (key1 != tmp)
	{
		SafetyVT_tmp_intval = SafetyVT_tmp_intval + (float)(key1 - tmp);
		if (SafetyVT_tmp_intval > 4)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			SafetyVT_tmp_intval = 1;
		}
		else if (SafetyVT_tmp_intval < 1)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			SafetyVT_tmp_intval = 4;
		}
		Unicode::snprintf(IE_val_bigBuffer, IE_VAL_BIG_SIZE, "%d", (int)SafetyVT_tmp_intval);
		IE_val_big.setWildcard1(IE_val_bigBuffer);
		IE_val_big.invalidate();
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickIE();
	}
}
void screenView::handleFiO2()
{
	if(!isFiO2Fake_alarm) 
	{
		pressKey = 0;
		return;
	}
	
	if (key1 != tmp)
	{
		FiO2_tmp_intval = FiO2_tmp_intval + (key1 - tmp);
		if (FiO2_tmp_intval > 100)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			FiO2_tmp_intval = 21;
		}
		else if (FiO2_tmp_intval < 21)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			FiO2_tmp_intval = 100;
		}
		Unicode::snprintf(FiO2_val_bigBuffer, FIO2_VAL_BIG_SIZE, "%d", (int)FiO2_tmp_intval);
		FiO2_val_big.setWildcard1(FiO2_val_bigBuffer);
		FiO2_val_big.invalidate();
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickFiO2();
	}
}
void screenView::handleTi()
{
	if (key1 != tmp)
	{
		float tmpval = Ti_tmp_intval + (float)(key1 - tmp) * 0.1;
		if (tmpval > 5)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			tmpval = 0.1;
			if (((60 / RR_tmp_intval) - tmpval) / tmpval < 10 && ((60 / RR_tmp_intval) - tmpval) / tmpval > 0 && tmpval / ((60 / RR_tmp_intval) - tmpval) < 10 && tmpval / ((60 / RR_tmp_intval) - tmpval) > 0)
			{
				Ti_tmp_intval = tmpval;
			}
			else
			{
				Ti_tmp_intval = tmpval = 5;
			}
		}
		else if (tmpval < 0.1)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			tmpval = 5;
			if (((60 / RR_tmp_intval) - tmpval) / tmpval < 10 && ((60 / RR_tmp_intval) - tmpval) / tmpval > 0 && tmpval / ((60 / RR_tmp_intval) - tmpval) < 10 && tmpval / ((60 / RR_tmp_intval) - tmpval) > 0)
			{
				Ti_tmp_intval = tmpval;
			}
			else
			{
				Ti_tmp_intval = tmpval = 0.1;
			}
		}
		else if (((60 / RR_tmp_intval) - tmpval) / tmpval < 10 && ((60 / RR_tmp_intval) - tmpval) / tmpval > 0 && tmpval / ((60 / RR_tmp_intval) - tmpval) < 10 && tmpval / ((60 / RR_tmp_intval) - tmpval) > 0)
			Ti_tmp_intval = tmpval;
		
		Unicode::snprintfFloat(Ti_val_bigBuffer, TI_VAL_BIG_SIZE, "%.1f", Ti_tmp_intval);
		Ti_val_big.setWildcard1(Ti_val_bigBuffer);
		Ti_val_big.invalidate();
		// change related things like: MV, Te, IE (in hint box)
		Unicode::snprintfFloat(MV_hint_valBuffer, MV_HINT_VAL_SIZE, "%.2f", ((float)VT_intval / 1000) * RR_tmp_intval);
		MV_hint_val.setWildcard1(MV_hint_valBuffer);
		MV_hint_val.invalidate();
		float i = 0;
		float e = 0;
		if (Ti_tmp_intval <= (60 / RR_tmp_intval) - Ti_tmp_intval)
		{
			i = 1;
			e = ((60 / RR_tmp_intval) - Ti_tmp_intval) / Ti_tmp_intval;
		}
		else
		{
			i = Ti_tmp_intval / ((60 / RR_tmp_intval) - Ti_tmp_intval);
			e = 1;
		}
		Unicode::snprintfFloat(Te_hint_valBuffer, TE_HINT_VAL_SIZE, "%.2f", ((60 / RR_tmp_intval) - Ti_tmp_intval));
		Te_hint_val.setWildcard1(Te_hint_valBuffer);
		Te_hint_val.invalidate();
		Unicode::snprintfFloat(IE_hint_valBuffer1, IE_HINT_VALBUFFER1_SIZE, "%.1f", i);
		IE_hint_val.setWildcard1(IE_hint_valBuffer1);
		IE_hint_val.invalidate();
		Unicode::snprintfFloat(IE_hint_valBuffer2, IE_HINT_VALBUFFER2_SIZE, "%.1f", e);
		IE_hint_val.setWildcard2(IE_hint_valBuffer2);
		IE_hint_val.invalidate();

		__HAL_TIM_SET_COUNTER(&htim3, 0);
		tmp = key1 = 0;
		encoderCounter = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickTi();
	}
}
void screenView::handleFlow()
{
	if (key1 != tmp)
	{
		TiInspPause_tmp_intval = TiInspPause_tmp_intval + (float)(key1 - tmp);
		if (TiInspPause_tmp_intval > 120)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			TiInspPause_tmp_intval = 10;
		}
		else if (TiInspPause_tmp_intval < 10)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			TiInspPause_tmp_intval = 120;
		}
		Unicode::snprintf(flow_val_bigBuffer, FLOW_VAL_BIG_SIZE, "%d", (int)TiInspPause_tmp_intval);
		flow_val_big.setWildcard1(flow_val_bigBuffer);
		flow_val_big.invalidate();
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickFlow();
	}
}
void screenView::handleCPAP()
{
	if (key1 != tmp)
	{
		CPAP_tmp_intval = CPAP_tmp_intval + (float)(key1 - tmp);
		if (CPAP_tmp_intval > 30)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			CPAP_tmp_intval= 0;
		}
		else if (CPAP_tmp_intval< 0)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			CPAP_tmp_intval= 30;
		}
		Unicode::snprintf(CPAP_val_bigBuffer, CPAP_VAL_BIG_SIZE, "%d", (int)CPAP_tmp_intval);
		CPAP_val_big.setWildcard1(CPAP_val_bigBuffer);
		CPAP_val_big.invalidate();
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickCPAP();
	}
}
void screenView::handlePsupp()
{
	if (key1 != tmp)
	{
		Psupp_tmp_intval = Psupp_tmp_intval + (float)(key1 - tmp);
		if (Psupp_tmp_intval > 35)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			Psupp_tmp_intval = 0;
		}
		else if (Psupp_tmp_intval < 0)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			Psupp_tmp_intval = 35;
		}
		Unicode::snprintf(PS_val_bigBuffer, PS_VAL_BIG_SIZE, "%d", (int)Psupp_tmp_intval);
		PS_val_big.setWildcard1(PS_val_bigBuffer);
		PS_val_big.invalidate();
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickPS();
	}
}
void screenView::handleSens()
{
	if (key1 != tmp)
	{
		if(sens_tmp_intval == -1 && (sens_tmp_intval + ((float)(key1 - tmp)) * 0.1) > -1) sens_tmp_intval = 0.5;
		else if(sens_tmp_intval == 0.5 && (sens_tmp_intval + ((float)(key1 - tmp)) * 0.1) < 0.5) sens_tmp_intval = -1;
		else sens_tmp_intval = sens_tmp_intval + ((float)(key1 - tmp)) * 0.1;
		
		if (sens_tmp_intval > 15)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			sens_tmp_intval = -1;
		}
		else if (sens_tmp_intval < -1)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			sens_tmp_intval = 15;
		}
		if(sens_tmp_intval == -1)
		{
			Unicode::strncpy(sensivity_val_bigBuffer, "Off", 3);
			sensivity_val_big.setWildcard1(sensivity_val_bigBuffer);
			sensivity_val_big.resizeToCurrentText();
			sensivity_val_big.invalidate();
		}
		else
		{
			Unicode::snprintfFloat(sensivity_val_bigBuffer, SENSIVITY_VAL_BIG_SIZE, "%.1f", sens_tmp_intval);
			sensivity_val_big.setWildcard1(sensivity_val_bigBuffer);
			sensivity_val_big.invalidate();
		}

		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickSensitivity();
	}
}
void screenView::handleRisetime()
{
	if (key1 != tmp)
	{
		riseTime_tmp_intval = riseTime_tmp_intval + (float)(key1 - tmp) * 50;
		if (riseTime_tmp_intval > 900)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			riseTime_tmp_intval = 200;
		}
		else if (riseTime_tmp_intval < 200)
		{
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			key1 = 0;
			encoderCounter = 0;
			tmp = 0;
			riseTime_tmp_intval = 900;
		}
		Unicode::snprintf(riseTime_val_bigBuffer, RISETIME_VAL_BIG_SIZE, "%d", (int)riseTime_tmp_intval);
		riseTime_val_big.setWildcard1(riseTime_val_bigBuffer);
		riseTime_val_big.invalidate();
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		key1 = 0;
		encoderCounter = 0;
		tmp = 0;
	}
	if (pressKey == 1)
	{
		// save and exit
		ClickRiseTime();
	}
}
void screenView::handleTrigger()
{
	if (key1 == 0)
	{
//		if (!trigger_val_flow_big.isVisible())
//		{
//			trigger_val_flow.setVisible(false);
//			trigger_val_flow.invalidate();
//			trigger_val_flow_big.setVisible(true);
//			trigger_val_flow_big.invalidate();
//		}
//		if (trigger_val_pressure_big.isVisible())
//		{
//			trigger_val_pressure_big.setVisible(false);
//			trigger_val_pressure_big.invalidate();
//		}
//		if (pressKey == 1)
//		{
//			ClickTrigger();
//		}
	}
	else if (key1 == 1)
	{
		if (trigger_val_flow_big.isVisible())
		{
			trigger_val_flow_big.setVisible(false);
			trigger_val_flow_big.invalidate();
		}
		if (!trigger_val_pressure_big.isVisible())
		{
			trigger_val_pressure.setVisible(false);
			trigger_val_pressure.invalidate();
			trigger_val_pressure_big.setVisible(true);
			trigger_val_pressure_big.invalidate();
		}
		if (pressKey == 1)
		{
			ClickTrigger();
		}
	}
	// key1 values change for always being in "Pressure"
	else if (key1 > 1)
	{
		key1 = 1;
		encoderCounter = key1*4 + 1;
		__HAL_TIM_SET_COUNTER(&htim3, encoderCounter);
	}
	else if (key1 < 1)
	{
		key1 = 1;
		encoderCounter = 4 + 1;
		__HAL_TIM_SET_COUNTER(&htim3, 4 + 1);
	}
}
void screenView::handleAlert()
{
	if (key1 == 0)
	{
		pressKey = 0;
		if (choose_cancelAlertScreen.isVisible())
		{
			choose_cancelAlertScreen.setVisible(false);
			choose_cancelAlertScreen.invalidate();
		}
		if (choose_yesAlertScreen.isVisible())
		{
			choose_yesAlertScreen.setVisible(false);
			choose_yesAlertScreen.invalidate();
		}
	}
	else if (key1 == 1)
	{
		if (!choose_cancelAlertScreen.isVisible())
		{
			choose_cancelAlertScreen.setVisible(true);
			choose_cancelAlertScreen.invalidate();
		}
		if (choose_yesAlertScreen.isVisible())
		{
			choose_yesAlertScreen.setVisible(false);
			choose_yesAlertScreen.invalidate();
		}
		if (pressKey == 1)
		{
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			click_cancelAlert();
		}
	}
	else if (key1 == 2)
	{
		if (choose_cancelAlertScreen.isVisible())
		{
			choose_cancelAlertScreen.setVisible(false);
			choose_cancelAlertScreen.invalidate();
		}
		if (!choose_yesAlertScreen.isVisible())
		{
			choose_yesAlertScreen.setVisible(true);
			choose_yesAlertScreen.invalidate();
		}
		if (pressKey == 1)
		{
			pressKey = 0;
			key1 = 0;
			encoderCounter = 0;
			__HAL_TIM_SET_COUNTER(&htim3, 0);
			click_yesAlert();
		}
	}
	else if (key1 > 2)
	{
		key1 = 0;
		encoderCounter = 0;
		__HAL_TIM_SET_COUNTER(&htim3, 0);
	}
	else if (key1 < 0)
	{
		key1 = 2;
		encoderCounter = 8+1;
		__HAL_TIM_SET_COUNTER(&htim3, 8+1);
	}
}








