#pragma once

#include "cocos2d.h"
#include "Common.h"
#include <map>

class MapLayer;

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    static void addSpriteFrameCache();
    void updateInformationArea(bool first = false);                // �����Ҳ���Ϣ����

    static GameScene* create(int stage = 1) {
        auto* pRet = new(std::nothrow) GameScene();
        if (pRet) {
            if (stage == 0 || stage == 12 || stage == 14 || stage == 16 || stage == 30)
                stage++; // ��ͼ����������
            pRet->stage = stage;
            if (pRet->init()) {
                pRet->autorelease();
                return pRet;
            }
        }

        delete pRet;
        pRet = nullptr;

        return nullptr;
    }

    short stage = 1;                                          // ��ǰ�ؿ�

private:
    MapLayer* map = nullptr;                                  // �����ͼ
    std::map<
        cocos2d::EventKeyboard::KeyCode, Dir> table;          // ��λ�����

    void __showLoadAnimate();                                 // չʾ����ؿ�����
    void __initMapLayer();                                    // ��ʼ����ͼ����
    void __enableKeyListener();                               // �������̼�����
    void __addTouchButton();                                  // ��Ӵ�����ť
    void __checkGameStatus(float);                            // �����Ϸ״̬
    void __gameover(float);                                   // ��Ϸ��������
};

