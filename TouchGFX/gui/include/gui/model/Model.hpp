#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
		void savePrevPageName(char pageName);
		void SetMonitorStateInModel(int MonitorState);
		int GetMonitorStateInModel();
		char getPrevPageName();
		
		
		//Get Functions
		float getPatientType();
		float getCircuitType();
		float getMaskType();
		float getEPAP();
		float getIPAP();
		float getRR();
		float getVT();
		float getFiO2();
		float getTi();
		float getSens();
		float getSafetyVT();
		float getTrigger();
		float getTiInspPause();
		float getPControl();
		float getPEEP();
		float getPS();
		float getRiseTime();
		float getCyclingOff();
		float getFlowShape();
		float getCPAP();
		float getTiMin();
		float getTiMax();
		float getPSMax();
		float getPControlMax();
		float getIPAPMax();
		
		
		// Set Functions
		void setPatientTypeState(float patientTypeState);
		void setCircuitType(float circuitTypestate);
		void setMaskType(float maskTypeState);
		void setEPAP(float EPAP);
		void setIPAP(float IPAP);
		void setRR(float RR);
		void setVT(float VT);
		void setFiO2(float FiO2);
		void setTi(float Ti);
		void setSens(float Sens);
		void setSafetyVT(float SafetyVT);
		void setTrigger(float Trigger);
		void setTiInspPause(float TiInspPause);
		void setPControl(float PControl);
		void setPEEP(float PEEP);
		void setPS(float PS);
		void setRiseTime(float RiseTime);
		void setCyclingOff(float CyclingOff);
		void setFlowShape(float FlowShape);
		void setCPAP(float CPAP);
		void setTiMin(float TiMin);
		void setTiMax(float TiMax);
		void setPSMax(float PSMax);
		void setPControlMax(float PControlMax);
		void setIPAPMax(float IPAPMax);
protected:
    ModelListener* modelListener;
		char pageNameInModel;
		int MonitorStateInModel;
		float patientType = 1;
		float circuitType = 0;
		float maskType = 0;
		float EPAP = 0;
		float IPAP = 0;
		float RR = 0;
		float VT = 0;
		float FiO2 = 0;
		float Ti = 0;
		float Sens = 0;
		float SafetyVT = 0;
		float Trigger = 0;
		float TiInspPause = 0;
		float PControl = 0;
		float PEEP = 0;
		float PS = 0;
		float RiseTime = 0;
		float CyclingOff = 0;
		float FlowShape = 0;
		float CPAP = 0;
		float TiMin = 0;
		float TiMax = 0;
		float PSMax = 0;
		float PControlMax = 0;
		float IPAPMax = 0;
		
		
};

#endif // MODEL_HPP
