#pragma once

#include "cocos2d.h"

class Player;
class ControlLayer;
class MapLayer;
class Camp;

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    ~GameScene();
    bool init() override;

    static void initSpriteFrameCache();
    void updateInformationArea(bool first = false);  // 更新右侧信息区域

    Player* getPlayer1() const { return _player1; }
    ControlLayer* getControlLayer() const { return _ctrlLayer; }
    MapLayer* getMapLayer() const { return _map; }

    static GameScene* create(int stage = 1) {
        auto* pRet = new(std::nothrow) GameScene();
        if (pRet) {
            if (stage == 0 || stage == 12 || stage == 14 || stage == 16 || stage == 30)
                stage++; // 地图数据有问题
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

    short stage = 1;                                          // 当前关卡

private:
    ControlLayer* _ctrlLayer = nullptr;                      // 游戏控制、信息和状态显示
    MapLayer* _map = nullptr;                                // 管理地图
    Player* _player1 = nullptr;

    void _printGameInfo();
    void _showLoadAnimate();                                 // 展示载入关卡动画
    void _initMapLayer();                                    // 初始化地图数据
    void _initControlLayer();
    void _checkGameStatus(float);                            // 检查游戏状态
    void _gameover(float);                                   // 游戏结束动画
};

inline Player* GET_PLAYER1() {
    auto gameScene = dynamic_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene());
    return gameScene != nullptr ? gameScene->getPlayer1() : nullptr;
}

inline ControlLayer* GET_CONTROL_LAYER() {
    auto gameScene = dynamic_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene());
    return gameScene != nullptr ? gameScene->getControlLayer() : nullptr;
}

inline MapLayer* GET_MAP_LAYER() {
    auto gameScene = dynamic_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene());
    return gameScene != nullptr ? gameScene->getMapLayer() : nullptr;
}
