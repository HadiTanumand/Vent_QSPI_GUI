#include <gui/screen_screen/screenView.hpp>
#include <gui/screen_screen/screenPresenter.hpp>


screenPresenter::screenPresenter(screenView& v)
    : view(v)
{

}

void screenPresenter::activate()
{
	
}

void screenPresenter::deactivate()
{

}
void screenPresenter::savePrevPageName(char pageName)
{
	model->savePrevPageName(pageName);
}
void screenPresenter::SetMonitorStateInModel(float monitorState)
{
	model->SetMonitorStateInModel(monitorState);
}
void screenPresenter::setCircuitType(float circuitType)
{
	model->setCircuitType(circuitType);
}
void screenPresenter::setMaskType(float maskState)
{
	model->setMaskType(maskState);
}
float screenPresenter::getPatientType()
{
	return model->getPatientType();
}
float screenPresenter::getMaskType()
{
	return model->getMaskType();
}
float screenPresenter::getCircuitType()
{
	return model->getCircuitType();
}
