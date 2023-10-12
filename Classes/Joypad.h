#ifndef _JOYPAD_H_
#define _JOYPAD_H_
// 虚拟手柄控制层

#include "cocos2d.h"

using namespace cocos2d;

class Player;

class Joypad : public Layer
{
public:
    CREATE_FUNC(Joypad)
    static Joypad* getInstance();

    virtual bool init();
    void setPlayer(const Player* player);

private:
    Player* _player1 = nullptr;
};

#endif // _JOYPAD_H_
