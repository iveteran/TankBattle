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

    static MapLayer* getInstance();                 // �õ���ͼͼ��ʵ��

    void loadLevelData(short stage);                // ����ָ���ؿ�������

    Block* getCamp();                               // �õ���Ӫ
    PlayerTank* getPlayer1();                       // �õ����1
    const std::string& getMapData();                // �õ���ͼ����
    cocos2d::Vector<Block*>& getAllBlocks();        // �õ����з���
    cocos2d::Vector<EnemyTank*>& getEnemies();      // �õ��з�̹��
    cocos2d::Vector<PlayerTank*>& getPlayers();     // �õ����̹��

    void enableAutoAddEnemies(bool b = true);       // �����Զ���ӵ���
    void enableAutoControlEnemies(bool b = true);   // �����Զ����Ƶ���

    void addPlayer();                               // ������
    void addEnemies();                              // ��ӵ���

    void resetMap();                                   // ������

    unsigned char remainTank = ENEMIES_COUNT;       // ʣ��δ�����ĵз�̹��

private:
    CREATE_FUNC(MapLayer);                          // ��������

    void __addSpriteFrameCache();                   // ���ؾ���֡����
    void __addEnemy(float x, float y);              // ���һ���з�̹��

    void autoAddEnemies(float);                     // �Զ���ӵ���
    void autoControlEnemiesDirection(float);        // �Զ����Ƶ��˷���
    void autoControlEnemiesShoot(float);            // �Զ����Ƶ��˷����ӵ�

    cocos2d::Vector<Block*> blocks;                 // �������з���
    cocos2d::Vector<PlayerTank*> players;           // �������̹��
    cocos2d::Vector<EnemyTank*> enemies;            // ����з�̹��

    std::string data;                               // ��ͼ����
};