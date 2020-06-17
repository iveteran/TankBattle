#include "Common.h"

#include "PlayerTank.h"
#include "MapLayer.h"
#include "PlayerBullet.h"
#include "AudioEngine.h"

USING_NS_CC;

cocos2d::Vector<cocos2d::Animate*> PlayerTank::animations[4]{};

bool PlayerTank::init() {
    if (!TankBase::init()) {
        return false;
    }

    // ��ҳ���ʱѪ��Ϊ3
    blood = 3;

    // չʾ��������
    birth("player1_1_" + std::to_string(level));

    // ��ҳ���ʱ��������
    dir = Dir::UP;

    return true;
}

void PlayerTank::setDir(Dir d) {
    if (!canMove) return;

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

void PlayerTank::__initBullets() {
    // ������ӵ�������ӵ�
    auto bullet1 = PlayerBullet::create();
    auto bullet2 = PlayerBullet::create();
    bullets.pushBack(bullet1);
    bullets.pushBack(bullet2);
}

void PlayerTank::loadFrameAnimation() {
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

            player1_1->getTexture()->setAliasTexParameters();
            player1_2->getTexture()->setAliasTexParameters();

            // ��ӵ�����
            spriteFrameCache->addSpriteFrame(player1_1, "player1_" + d + "_" + lev);

            // ����
            animations[j].pushBack(Animate::create(player1));
        }
    }
}

const cocos2d::Vector<cocos2d::Animate*>* PlayerTank::__getAnimations() {
    return animations;
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

void PlayerTank::setBeControl(bool b) {
    beControl = b;
}

bool PlayerTank::isBeControl() {
    return beControl;
}

void PlayerTank::disBlood() {
    if (isInvincible)
        return;

    auto spriteFrameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteFrames;

    for (int i = 0; i != 5; i++) {
        std::string n = std::to_string(i);
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName("blast_" + n);
        spriteFrames.pushBack(spriteFrame);
    }

    // TODO ÿ�����������¹��춯��
    auto blastAnimation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
    auto blastanimate = Animate::create(blastAnimation);

    // ������Ч
    AudioEngine::play2d("music/enemy-bomb.mp3");

    if (--blood == 0) {
        // �Ƴ���̹��
        auto& players = MapLayer::getInstance()->getPlayers();
        players.eraseObject(this);

        // ���Ŷ���
        this->runAction(
            Sequence::create(
                blastanimate,
                CallFunc::create([this] {
            this->removeFromParentAndCleanup(true);
        }),
                nullptr
            ));
    } else {
        // ���Ŷ���
        this->runAction(
            Sequence::create(
                blastanimate,
                CallFunc::create([this] {
            // �ص�������
            birth("player1_" + std::to_string((int)dir) + "_" + std::to_string(level));
        }),
                nullptr
            ));
    }
}
