#include "Common.h"

#include "EnemyTank.h"
#include "EnemyBullet.h"
#include "RandomUtil.h"
#include "MapLayer.h"

USING_NS_CC;

cocos2d::Vector<cocos2d::Animate*> EnemyTank::animations[4]{};

bool EnemyTank::init() {
    if (!TankBase::init()) {
        return false;
    }

    // ���ѡ��һ������
    level = RandomUtil::random(0, 3);

    // �����ƶ�
    startMove();

    // չʾ��������
    birth("enemy_" + std::to_string(int(dir)) + "_" + std::to_string(level));

    return true;
}

void EnemyTank::setDir(Dir d) {
    if (d == dir) {
        return;
    }

    dir = d;

    // ���ı䷽��ʱ�����������Ϊ��ӽ���8�ı���
    __adjustPosition();

    std::string name = "enemy_" + std::to_string((int)dir) + "_"
        + std::to_string(level);

    // ����ͼƬ
    this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
}

void EnemyTank::loadFrameAnimation() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    Rect tankRect(0, 0, TANK_SIZE, TANK_SIZE);

    // �ܹ�4���ȼ�
    for (int i = 0; i < 4; i++) {
        std::string lev = std::to_string(i);
        // �ܹ�4������
        for (int j = 0; j < 4; j++) {
            std::string d = std::to_string(j);
            auto enemy_1 = SpriteFrame::create("images/enemy_tank/normal_tank/" + std::to_string(i + 1) + "-" + std::to_string(j + 1) + "-1.png", tankRect);
            auto enemy_2 = SpriteFrame::create("images/enemy_tank/normal_tank/" + std::to_string(i + 1) + "-" + std::to_string(j + 1) + "-2.png", tankRect);
            auto enemy = Animation::createWithSpriteFrames({ enemy_1, enemy_2 }, 0.05f);

            enemy_1->getTexture()->setAliasTexParameters();
            enemy_2->getTexture()->setAliasTexParameters();

            // ��ӵ�����
            spriteFrameCache->addSpriteFrame(enemy_1, "enemy_" + d + "_" + lev);

            // ����
            animations[j].pushBack(Animate::create(enemy));
        }
    }
}

void EnemyTank::changeDirection() {
    if (moveDistance >= MAX_MOVE_DISTANCE) {
        canChangeDir = true;
    }

    if (!canChangeDir) return;

    moveDistance = 0;
    canChangeDir = false;

    /*if (target == AttacTarget::CAMP) {
        if (RandomUtil::random(1, 10) <= 4) {
            auto camp = MapLayer::getInstance()->getCamp();
            if (this->getPositionX() > camp->getPositionX()) {
                setDir(Dir::LEFT);
            } else {
                setDir(Dir::RIGHT);
            }
        } else {
            setDir(Dir::DOWN);
        }
    }*/

    auto select = RandomUtil::random(1, 10);

    this->stopAnimate();
    if (select <= 4) {
        setDir(Dir::DOWN);
    } else if (select <= 6) {
        setDir(Dir::UP);
    } else if (select <= 8) {
        setDir(Dir::LEFT);
    } else {
        setDir(Dir::RIGHT);
    }
    this->playAnimate();
}

void EnemyTank::disBlood() {
    TankBase::disBlood();
}

void EnemyTank::__initBullets() {
    auto bullet = EnemyBullet::create();
    bullets.pushBack(bullet);
}

const cocos2d::Vector<cocos2d::Animate*>* EnemyTank::__getAnimations() {
    return animations;
}

bool EnemyTank::__isTankIntersection() {
    auto players = MapLayer::getInstance()->getPlayers();
    for (auto player : players) {
        if (this->getBoundingBox().myIntersectsRect(player->getBoundingBox())) {
            return true;
        }
    }

    auto buddies = MapLayer::getInstance()->getEnemies();
    for (auto buddy : buddies) {
        if (buddy != this && this->getBoundingBox().myIntersectsRect(buddy->getBoundingBox())) {
            return true;
        }
    }

    return false;
}
