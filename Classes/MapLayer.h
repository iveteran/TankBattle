#pragma once

#include "cocos2d.h"
#include "Block.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

#include <string>

class TankBase;

class MapLayer : public cocos2d::LayerColor {
public:
    bool init() override;

    static MapLayer* getInstance();                 // 得到地图图层实例

    void loadLevelData(short stage);                // 加载指定关卡的数据

    Block* getCamp();                               // 得到大本营
    PlayerTank* getPlayer1();                       // 得到玩家1
    const std::string& getMapData();                // 得到地图数据
    cocos2d::Vector<Block*>& getAllBlocks();        // 得到所有方块
    cocos2d::Vector<EnemyTank*>& getEnemies();      // 得到敌方坦克
    cocos2d::Vector<PlayerTank*>& getPlayers();     // 得到玩家坦克

    void enableAutoAddEnemies(bool b = true);       // 启用自动添加敌人
    void enableAutoControlEnemies(bool b = true);   // 启用自动控制敌人

    PlayerTank* addPlayer();                        // 添加玩家
    void addEnemies();                              // 添加敌人

    void resetMap();                                // 清理工作

    unsigned char remainTank = ENEMIES_COUNT;       // 剩余未出生的敌方坦克
    bool isCampOk = true;                           // 大本营是否完好

private:
    CREATE_FUNC(MapLayer);                          // 单例对象

    void _addSpriteFrameCache();                   // 加载精灵帧缓存
    void _addEnemy(float x, float y);              // 添加一辆敌方坦克

    void autoAddEnemies(float);                     // 自动添加敌人
    void autoControlEnemiesDirection(float);        // 自动控制敌人方向
    void autoControlEnemiesShoot(float);            // 自动控制敌人发射子弹

    cocos2d::Vector<Block*> _blocks;                 // 管理所有方块
    cocos2d::Vector<PlayerTank*> _players;           // 管理玩家坦克
    cocos2d::Vector<EnemyTank*> _enemies;            // 管理敌方坦克

    std::string _data;                               // 地图数据
};
