#include <gui/settingscreen_screen/SettingScreenView.hpp>

SettingScreenView::SettingScreenView()
{

}

void SettingScreenView::setupScreen()
{
    SettingScreenViewBase::setupScreen();
}

void SettingScreenView::tearDownScreen()
{
    SettingScreenViewBase::tearDownScreen();
}
void SettingScreenView::getPrevPageName(char pageName)
{
	Unicode::snprintf(textArea12Buffer, TEXTAREA12_SIZE , "%c", pageName);
	textArea12.setWildcard1(textArea12Buffer);
	textArea12.invalidate();
}