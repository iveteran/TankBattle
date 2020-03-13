#include "Common.h"

#include "PlayerTank.h"
#include "TankBase.h"
#include "MapLayer.h"

#include "cocos2d.h"

USING_NS_CC;

bool PlayerTank::init() {
	if (!TankBase::init()) {
		return false;
	}

	dir = Dir::UP;
	level = 1;

	startAnimate("player1_1_" + std::to_string(level));

	return true;
}

void PlayerTank::setDir(Dir d) {
	if (d == dir) {
		return;
	}

	dir = d;

	// ���ı䷽��ʱ�����������Ϊ��ӽ���8�ı���
	__adjustPosition();

	std::string name = "player1_" + std::to_string((int)dir) + "_"
		+ std::to_string(level);

	// ����ͼƬ
	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
}

void PlayerTank::__initSpriteFrameCache() {
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	Rect tankRect(0, 0, TANK_SIZE, TANK_SIZE);

	// �ܹ�4���ȼ�
	for (int i = 0; i < 4; i++) {
		std::string lev = std::to_string(i);
		// �ܹ�4������
		for (int j = 0; j < 4; j++) {
			std::string d = std::to_string(j);
			auto player1_1 = SpriteFrame::create("images/player1_tank/m" + lev + "-" + d + "-1.png", tankRect);
			auto player1_2 = SpriteFrame::create("images/player1_tank/m" + lev + "-" + d + "-2.png", tankRect);
			auto player1 = Animation::createWithSpriteFrames({ player1_1, player1_2 }, 0.05f);

			// ��ӵ�����
			spriteFrameCache->addSpriteFrame(player1_1, "player1_" + d + "_" + lev);

			// ����
			animations[j].pushBack(Animate::create(player1));
		}
	}

}

void PlayerTank::__initBullets() {
	TankBase::__initBullets();
	auto bullet2 = Bullet::create();
	bullets.pushBack(bullet2);
}

void PlayerTank::shoot() {
	if (!canMove) {
		return;
	}

	auto bullet1 = bullets.at(0);
	auto bullet2 = bullets.at(1);

	if (!bullet1->isVisible() && !bullet2->isVisible()) {
		bullet1->setLevel(level);
		__shoot(bullet1);
	} else if (bullet1->isVisible() && bullet2->isVisible()) {
		// ʲô������
	} else if (level >= 2) {
		// ��ʱ�ɷ�����ö�ӵ�
		if (bullet1->isVisible()) {
			bullet2->setLevel(level);
			__shoot(bullet2);
		} else {
			bullet1->setLevel(level);
			__shoot(bullet1);
		}
	}
}
