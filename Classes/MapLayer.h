#pragma once

#include "cocos2d.h"
#include "Block.h"
#include "PlayerTank.h"

#include <string>

class TankBase;

class MapLayer : public cocos2d::LayerColor {
public:
    bool init() override;

    static MapLayer* getInstance();            // �õ���ͼͼ��ʵ��

    void loadLevelData(short stage);           // ����ָ���ؿ�������

    Block* getCamp();                          // �õ���Ӫ
    PlayerTank* getPlayer1();                  // �õ����1
    const std::string& getMapData();           // �õ���ͼ����
    cocos2d::Vector<Block*>& getAllBlocks();   // �õ����з���

    void addPlayer();                          // ������
    void addEnemies();                         // ��ӵ���

private:
    CREATE_FUNC(MapLayer);                     // ��������

    void __addSpriteFrameCache();              // ���ؾ���֡����

    cocos2d::Vector<Block*> blocks;            // �������з���
    cocos2d::Vector<PlayerTank*> players;      // �������̹��
    cocos2d::Vector<TankBase*> enemies;        // ����з�̹��

    std::string data;                          // ��ͼ����
};