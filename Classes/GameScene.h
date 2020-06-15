#pragma once

#include "cocos2d.h"
#include "Common.h"
#include <map>

class MapLayer;

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    CREATE_FUNC(GameScene);

private:
    MapLayer* map;                                            // �����ͼ
    std::map<
        cocos2d::EventKeyboard::KeyCode, Dir> table;          // ��λ�����

    void __showLoadAnimate();                                 // չʾ����ؿ�����
    void __initMapLayer();                                    // ��ʼ����ͼ����
    void __enableKeyListener();                               // �������̼�����
    void __addTouchButton();                                  // ��Ӵ�����ť

    short stage = 1;                                          // ��ǰ�ؿ�
};

