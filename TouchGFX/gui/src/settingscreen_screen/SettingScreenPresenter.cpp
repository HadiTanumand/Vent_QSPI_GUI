#include <gui/settingscreen_screen/SettingScreenView.hpp>
#include <gui/settingscreen_screen/SettingScreenPresenter.hpp>

SettingScreenPresenter::SettingScreenPresenter(SettingScreenView& v)
    : view(v)
{

}

void SettingScreenPresenter::activate()
{
	view.getPrevPageName(model->getPrevPageName());
}

void SettingScreenPresenter::deactivate()
{

}
