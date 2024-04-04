#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}
void Model::savePrevPageName(char pageName)
{
	pageNameInModel = pageName;
}
void Model::SetMonitorStateInModel(int MonitorState)
{
	MonitorStateInModel = MonitorState ;
}
int Model::GetMonitorStateInModel()
{
	return MonitorStateInModel;
}
char Model::getPrevPageName()
{
	return pageNameInModel;
}


// Get Functions
float Model::getPatientType()
{
		return patientType;
}
float Model::getCircuitType()
{
		return circuitType;
}
float Model::getMaskType()
{
		return maskType;
}

float Model::getEPAP(){return EPAP;}
float Model::getIPAP(){return IPAP;}
float Model::getRR(){return RR;}
float Model::getVT(){return VT;}
float Model::getFiO2(){return FiO2;}
float Model::getTi(){return Ti;}
float Model::getSens(){return Sens;}
float Model::getSafetyVT(){return SafetyVT;}
float Model::getTrigger(){return Trigger;}
float Model::getTiInspPause(){return TiInspPause;}
float Model::getPControl(){return PControl;}
float Model::getPEEP(){return PEEP;}
float Model::getPS(){return PS;}
float Model::getRiseTime(){return RiseTime;}
float Model::getCyclingOff(){return CyclingOff;}
float Model::getFlowShape(){return FlowShape;}
float Model::getCPAP(){return CPAP;}
float Model::getTiMin(){return TiMin;}
float Model::getTiMax(){return TiMax;}
float Model::getPSMax (){return PSMax;}
float Model::getPControlMax(){return PControlMax;}
float Model::getIPAPMax() {return IPAPMax;}

// Set Functions
void Model::setPatientTypeState(float patientTypeState)
{
	patientType = patientTypeState;
}
void Model::setCircuitType(float circuitTypestate)
{
	circuitType = circuitTypestate;
}
void Model::setMaskType(float maskTypeState)
{
	maskType = maskTypeState;
}
void Model::setEPAP(float value){EPAP = value;}
void Model::setIPAP(float value){IPAP= value;}
void Model::setRR(float value){RR= value;}
void Model::setVT(float value){VT= value;}
void Model::setFiO2(float value){FiO2= value;}
void Model::setTi(float value){Ti= value;}
void Model::setSens(float value){Sens= value;}
void Model::setSafetyVT(float value){SafetyVT= value;}
void Model::setTrigger(float value){Trigger= value;}
void Model::setTiInspPause(float value){TiInspPause= value;}
void Model::setPControl(float value){PControl= value;}
void Model::setPEEP(float value){PEEP= value;}
void Model::setPS(float value){PS= value;}
void Model::setRiseTime(float value){RiseTime= value;}
void Model::setCyclingOff(float value){CyclingOff= value;}
void Model::setFlowShape(float value){FlowShape= value;}
void Model::setCPAP(float value){CPAP= value;}
void Model::setTiMin(float value){TiMin= value;}
void Model::setTiMax(float value){TiMax= value;}
void Model::setPSMax(float value){PSMax= value;}
void Model::setPControlMax(float value){PControlMax= value;}
void Model::setIPAPMax(float value) {IPAPMax= value;}