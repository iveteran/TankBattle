#include "Bullet.h"
#include "Common.h"
#include "MapLayer.h"
#include "PlayerBullet.h"

#include "AudioEngine.h"

USING_NS_CC;

bool Bullet::init() {
    if (!Sprite::init()) {
        return false;
    }

    this->setVisible(false);

    return true;
}

void Bullet::startMove() {
    this->schedule(CC_SCHEDULE_SELECTOR(Bullet::__autoMove), 0.008f);
}

void Bullet::__stopMove() {
    this->unschedule(CC_SCHEDULE_SELECTOR(Bullet::__autoMove));
}

void Bullet::setDir(Dir d) {
    dir = d;
}

void Bullet::setLevel(BulletLevel lev) {
    level = lev;
}

void Bullet::addSpriteFrameCache() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    // �ӵ�
    auto* bullet_l = Sprite::create("images/bullet/bullet-0.png")->getSpriteFrame();
    auto* bullet_u = Sprite::create("images/bullet/bullet-1.png")->getSpriteFrame();
    auto* bullet_r = Sprite::create("images/bullet/bullet-2.png")->getSpriteFrame();
    auto* bullet_d = Sprite::create("images/bullet/bullet-3.png")->getSpriteFrame();

    bullet_l->getTexture()->setAliasTexParameters();
    bullet_u->getTexture()->setAliasTexParameters();
    bullet_r->getTexture()->setAliasTexParameters();
    bullet_d->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(bullet_l, "bullet_l");
    spriteFrameCache->addSpriteFrame(bullet_u, "bullet_u");
    spriteFrameCache->addSpriteFrame(bullet_r, "bullet_r");
    spriteFrameCache->addSpriteFrame(bullet_d, "bullet_d");

    // �ӵ���ը
    auto* bumb_0 = Sprite::create("images/bullet/bumb0.png")->getSpriteFrame();
    auto* bumb_1 = Sprite::create("images/bullet/bumb1.png")->getSpriteFrame();
    auto* bumb_2 = Sprite::create("images/bullet/bumb2.png")->getSpriteFrame();

    bumb_0->getTexture()->setAliasTexParameters();
    bumb_1->getTexture()->setAliasTexParameters();
    bumb_2->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(bumb_0, "bumb_0");
    spriteFrameCache->addSpriteFrame(bumb_1, "bumb_1");
    spriteFrameCache->addSpriteFrame(bumb_2, "bumb_2");
}

void Bullet::__showEffect() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    auto mapLayer = MapLayer::getInstance();

    auto animation = Animation::createWithSpriteFrames({
        spriteFrameCache->getSpriteFrameByName("bumb_0"),
        spriteFrameCache->getSpriteFrameByName("bumb_1"),
        spriteFrameCache->getSpriteFrameByName("bumb_2")
                                                       },
                                                       0.05f);

    auto effect = Sprite::create();
    mapLayer->addChild(effect);
    effect->setPosition(this->getPosition());

    effect->runAction(Sequence::create(
        Animate::create(animation),
        CallFunc::create([=]() {
        mapLayer->removeChild(effect);
    }),
        nullptr)
    );
}

void Bullet::__autoMove(float t) {
    // 1. �ƶ�ʱ���͵�ͼ��Ե����ײ
    // 2. �ƶ�ʱ���ͷ������ײ
    // 3. �ƶ�ʱ����̹�˵���ײ
    // 4. �ƶ�ʱ�����ӵ�����ײ

    auto position = this->getPosition();
    auto step = 1;
    if (level >= 1) {
        step = 2;
    }

    // ��������ƶ�
    switch (dir) {
    case Dir::LEFT:
        this->setPositionX(position.x - step);
        break;
    case Dir::UP:
        this->setPositionY(position.y + step);
        break;
    case Dir::RIGHT:
        this->setPositionX(position.x + step);
        break;
    case Dir::DOWN:
        this->setPositionY(position.y - step);
        break;
    default:
        break;
    }

    // ���������ײ:
    // <1> �����ӵ�
    // <2.1> ����ǵ��ˣ�����˵�Ѫ
    // <2.2> ����Ƿ��飬�򷽿鱻�ݻ�(������ҵȼ�)
    // <2.3> �����ǽ�ڣ���ʲô������
    // <3> չʾ�ӵ���ײ��Ч
    // <4> ֹͣ�Զ��ƶ�
    if (__isBlockIntersection() || __isMapIntersection()) {
        this->setVisible(false);
        this->__showEffect();
        this->__stopMove();
    } else if (__isTankIntersection() || __isBulletIntersection()) {
        this->setVisible(false);
        this->__stopMove();
    }

}

bool Bullet::__isMapIntersection() {
    auto position = this->getPosition();
    if (position.x - BULLET_SIZE / 2 < 0
        || position.y + BULLET_SIZE / 2 > CENTER_HEIGHT
        || position.x + BULLET_SIZE / 2 > CENTER_WIDTH
        || position.y - BULLET_SIZE / 2 < 0) {

        if (dynamic_cast<PlayerBullet*>(this))
            AudioEngine::play2d("music/bin.mp3");
        return true;
    }
    return false;
}

bool Bullet::__isBlockIntersection() {
    // �õ����з���λ��
    auto& blocks = MapLayer::getInstance()->getAllBlocks();
    auto box = getBoundingBox();
    auto count = 0;

    for (auto it = blocks.begin(); it != blocks.end(); ) {
        auto block = (*it);
        // �����ϰ���
        if (block->getCategory() == BlockCategory::OBSTACLE
            && box.intersectsRect(block->getBoundingBox())) {
            if (block->getType() == BlockType::WALL) {
                // ����ǽ
                auto result =
                    dynamic_cast<BlockWall*>(block)->destory(this->dir, box);

                if (result.first) {
                    // ������ײ
                    count++;
                    if (result.second) {
                        // ������ײ�ұ��ݻ�
                        block->removeFromParent();
                        it = blocks.erase(it);
                    } else {
                        ++it;
                    }
                } else {
                    ++it;
                }


            } else if (block->getType() == BlockType::STONE) {
                // ����ʯͷ
                if (level >= 2) {
                    count++;
                    block->removeFromParent();
                    it = blocks.erase(it);
                } else {
                    if (dynamic_cast<PlayerBullet*>(this))
                        AudioEngine::play2d("music/bin.mp3");

                    count++;
                    ++it;
                }
            } else {
                // ������Ӫ
                AudioEngine::play2d("music/camp_bomb.mp3");
                MapLayer::getInstance()->getCamp()->setTexture(
                    SpriteFrameCache::getInstance()->getSpriteFrameByName("camp_1")->getTexture());
                MapLayer::getInstance()->isCampOk = false;
                count++;
                ++it;
            }

        } else {
            // û�������ϰ���
            ++it;
        }
    }

    return count;
}
