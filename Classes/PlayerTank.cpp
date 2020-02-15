#include "Common.h"

#include "PlayerTank.h"
#include "TankBase.h"

#include "cocos2d.h"

USING_NS_CC;

bool PlayerTank::init() {
	if (!TankBase::init()) {
		return false;
	}

	dir = Dir::UP;

	return true;
}

void PlayerTank::setDir(Dir d) {
	if (d == dir) {
		return;
	}

	dir = d;

	// ���ı䷽��ʱ�����������Ϊ��ӽ���8�ı���
	__adjustPosition();

	// ����ͼƬ
	switch (dir) {
	case Dir::LEFT:
		this->setSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName("player1_left"));
		break;
	case Dir::UP:
		this->setSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName("player1_up"));
		break;
	case Dir::RIGHT:
		this->setSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName("player1_right"));
		break;
	case Dir::DOWN:
		this->setSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName("player1_down"));
		break;
	default:
		break;
	}
}

void PlayerTank::__initSpriteFrameCache() {
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	Rect tankRect(0, 0, TANK_SIZE, TANK_SIZE);

	// 1��̹��
	auto player1Left_1 = SpriteFrame::create("images/player1_tank/m0-0-1.png", tankRect);
	auto player1Left_2 = SpriteFrame::create("images/player1_tank/m0-0-2.png", tankRect);
	auto player1Left = Animation::createWithSpriteFrames({ player1Left_1, player1Left_2 }, 0.05f);
	animations.pushBack(Animate::create(player1Left));

	auto player1Up_1 = SpriteFrame::create("images/player1_tank/m0-1-1.png", tankRect);
	auto player1Up_2 = SpriteFrame::create("images/player1_tank/m0-1-2.png", tankRect);
	auto player1Up = Animation::createWithSpriteFrames({ player1Up_1, player1Up_2 }, 0.05f);
	animations.pushBack(Animate::create(player1Up));

	auto player1Right_1 = SpriteFrame::create("images/player1_tank/m0-2-1.png", tankRect);
	auto player1Right_2 = SpriteFrame::create("images/player1_tank/m0-2-2.png", tankRect);
	auto player1Right = Animation::createWithSpriteFrames({ player1Right_1, player1Right_2 }, 0.05f);
	animations.pushBack(Animate::create(player1Right));

	auto player1Down_1 = SpriteFrame::create("images/player1_tank/m0-3-1.png", tankRect);
	auto player1Down_2 = SpriteFrame::create("images/player1_tank/m0-3-2.png", tankRect);
	auto player1Down = Animation::createWithSpriteFrames({ player1Down_1, player1Down_2 }, 0.05f);
	animations.pushBack(Animate::create(player1Down));

	spriteFrameCache->addSpriteFrame(player1Left_1, "player1_left");
	spriteFrameCache->addSpriteFrame(player1Up_1, "player1_up");
	spriteFrameCache->addSpriteFrame(player1Right_1, "player1_right");
	spriteFrameCache->addSpriteFrame(player1Down_1, "player1_down");

	// 2��̹��

	// 3��̹��

	// 4��̹��

	this->initWithSpriteFrameName("player1_up");
}
