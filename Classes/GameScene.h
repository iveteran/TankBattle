#pragma once

#include "cocos2d.h"

class MapLayer;

class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	bool init() override;
	
	CREATE_FUNC(GameScene);

private:
	MapLayer* map;                                // �����ͼ

	void __showLoadAnimate();                     // չʾ����ؿ�����
	void __initMapLayer();                        // ��ʼ����ͼ����
	void __enableKeyListener();                   // �������̼�����

	short stage = 1;                              // ��ǰ�ؿ�
};

