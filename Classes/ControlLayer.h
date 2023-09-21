#include "cocos2d.h"

//class Joypad;
class Joypad2;
class KbdController;

class ControlLayer : public cocos2d::Layer {
public:
    CREATE_FUNC(ControlLayer);
    bool init() override;

private:
    void _addJoypad2();
    void _addKbdController();

    //Joypad* _joypad = nullptr;
    Joypad2* _joypad2 = nullptr;
    KbdController* _kbd_ctrler = nullptr;
};