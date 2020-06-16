#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;

    CREATE_FUNC(MenuScene);

private:
    cocos2d::Sprite* background;                                      // ����ͼƬ
    cocos2d::Sprite* selector;                                        // �˵�ѡ����
    bool isSelectorInit;

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,        // �����ƶ����
                      cocos2d::Event* event);
    bool onTouch(cocos2d::Touch* touch, cocos2d::Event*);             // �����ƶ����


    void __initBackground();
    void __initSelector();

    cocos2d::Animate* __getAnimFrames();                              // ѡ����֡����
};
