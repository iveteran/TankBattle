#pragma once

#include "cocos2d.h"
#include "Block.h"
#include "TankBase.h"

#include <string>

class TankBase;

class MapLayer : public cocos2d::LayerColor {
public:
	bool init() override;

	static MapLayer* getInstance();            // �õ���ͼͼ��ʵ��

	void loadLevelData(short stage);           // ����ָ���ؿ�������

	TankBase* getPlayer1();                    // �õ����1
	Block* getCamp();                          // �õ���Ӫ
	cocos2d::Vector<Block*>& getAllBlocks();   // �õ����з���
	const std::string& getMapData();           // �õ���ͼ����

	void addPlayer();                          // ������
	void addEnemies();                         // ��ӵ���

private:
	CREATE_FUNC(MapLayer);                     // ��������

	void __addSpriteFrameCache();              // ���ؾ��黺��
	void __addNavigation();                    // ���Ӵ����������ܣ�������
	cocos2d::Vector<Block*> blocks;            // �������з���
	cocos2d::Vector<TankBase*> players;        // �������̹��
	cocos2d::Vector<TankBase*> enemies;        // ����з�̹��
	std::string data;                          // ��ͼ����
};