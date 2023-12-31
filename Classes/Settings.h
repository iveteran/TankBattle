#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "PopupLayer.h"

USING_NS_CC;

namespace cocos2d::ui {
    class TabControl;
}
using namespace cocos2d::ui;
 
class Settings : public PopupLayer {
public:
    CREATE_FUNC(Settings);

    virtual bool init() override;
    bool init(int width, int height, const Color3B& bgColor, int bgOpacity);
     
protected:
    void createPlayerSettingsPanel(int index, const char* title);
    void createServerSettingsPanel(int index, const char* title);
    void createScriptsManagementPanel(int index, const char* title);

    void createSettingsTabs(int numTabs);
    void addSettingsTab(int index, const char* title, Layout* panel);

private:
    TabControl* _tabs = nullptr;

    //GeneralSettings* generalSettings = nullptr;
    //ServerSettings* serverSettings = nullptr;
    //ScriptManagement* scriptManagement = nullptr;
};

#endif // _SETTINGS_H_
