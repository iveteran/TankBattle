#pragma once

#include "cocos2d.h"
#include "Block.h"
#include "TankBase.h"

class TankBase;

class MapLayer : public cocos2d::LayerColor {
public:
	bool init() override;

	static MapLayer* getInstance();            // �õ���ͼͼ��ʵ��

	void loadLevelData(int stage);             // ����ָ���ؿ�������

	TankBase* getPlayer1();                    // �õ����1
	Block* getCamp();                          // �õ���Ӫ
	cocos2d::Vector<Block*>& getAllBlocks();   // �õ����з���

	void addPlayer();                          // ������
	void addEnemies();                         // ��ӵ���

private:
	CREATE_FUNC(MapLayer);                     // ��������

	void __addSpriteFrameCache();              // ���ؾ��黺��
	cocos2d::Vector<Block*> blocks;            // �������з���
	cocos2d::Vector<TankBase*> players;        // �������̹��
	cocos2d::Vector<TankBase*> enemies;        // ����з�̹��
};