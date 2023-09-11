#include "TankBase.h"
#include "Common.h"
#include "MapLayer.h"
#include "Bullet.h"
#include "Block.h"

#include "AudioEngine.h"

USING_NS_CC;

bool TankBase::init() {
    if (!Sprite::init()) {
        return false;
    }

    _initBullets();

    return true;
}

void TankBase::playAnimate() {
    if (!canMove) {
        return;
    }

    this->runAction(RepeatForever::create(_getAnimations()[int(_dir)].at(_level)));
}

void TankBase::stopAnimate() {
    if (!canMove) {
        return;
    }

    this->stopAllActions();
}

void TankBase::_autoMove(float /*t*/) {
    if (!canMove) {
        return;
    }
    // 1. 移动时检测和地图边缘的碰撞
    // 2. 移动时检测和方块的碰撞
    // 3. 移动时检测和坦克的碰撞

    auto position = this->getPosition();
    auto step = 1.0f + _level * 0.2f;
    if (dynamic_cast<EnemyTank*>(this))
        step = 1.0f;

    // 假设可以移动
    switch (_dir) {
    case Direction::LEFT:
        this->setPositionX(position.x - step);
        break;
    case Direction::UP:
        this->setPositionY(position.y + step);
        break;
    case Direction::RIGHT:
        this->setPositionX(position.x + step);
        break;
    case Direction::DOWN:
        this->setPositionY(position.y - step);
        break;
    default:
        break;
    }

    _moveDistance += int(step);

    // 如果产生碰撞，则回到移动之前的位置
    if (_isBlockIntersection() || _isMapIntersection() || _isTankIntersection()) {
        this->setPosition(position);

        // 敌方坦克碰撞后可以改变方向
        _moveDistance = 100;
    }
}

void TankBase::_adjustPosition() {
    this->setPositionX(_adjustNumber(int(this->getPositionX())));
    this->setPositionY(_adjustNumber(int(this->getPositionY())));
}

float TankBase::_adjustNumber(int number) {
    if (number % 8 != 0) {
        for (int offset = 1; offset < 8; offset++) {
            if ((number + offset) % 8 == 0) {
                return float(number + offset);
            }

            if ((number - offset) % 8 == 0) {
                return float(number - offset);
            }
        }
    }

    return float(number);
}

bool TankBase::_isMapIntersection() {
    auto position = this->getPosition();
    return position.x - TANK_SIZE / 2.0f < 0
        || position.y + TANK_SIZE / 2.0f > CENTER_HEIGHT
        || position.x + TANK_SIZE / 2.0f > CENTER_WIDTH
        || position.y - TANK_SIZE / 2.0f < 0;
}

bool TankBase::_isBlockIntersection() {
    // 得到所有方块位置
    auto& blocks = MapLayer::getInstance()->getAllBlocks();
    auto box = getBoundingBox();
    for (auto& block : blocks) {
        auto category = block->getCategory();
        if (category == BlockCategory::OBSTACLE || category == BlockCategory::RIVER) {
            auto other = block->getBoundingBox();
            if (box.myIntersectsRect(other)) {
                return true;
            }
        }
    }
    return false;
}

void TankBase::startMove() {
    if (!_isMove) {
        if (dynamic_cast<PlayerTank*>(this))
            _musicId = AudioEngine::play2d("music/player_move.mp3");
        this->schedule(CC_SCHEDULE_SELECTOR(TankBase::_autoMove), 0.02f);
        _isMove = true;
    }
}

void TankBase::stopMove() {
    this->unschedule(CC_SCHEDULE_SELECTOR(TankBase::_autoMove));
    AudioEngine::stop(_musicId);
    _isMove = false;
}

void TankBase::birth(std::string afterStart) {
    if (dynamic_cast<PlayerTank*>(this))
        _level = 0;
    canMove = false;
    this->stopAllActions();
    this->setPosition(PLAYER1_START_X, PLAYER1_START_Y);

    auto spriteFrameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteFrames;
    for (int i = 0; i < 4 * 2; i++) {
        std::string n = std::to_string(i % 4);
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName("star_" + n);
        spriteFrames.pushBack(spriteFrame);
    }

    // 星星动画
    auto animation = Animation::createWithSpriteFrames(spriteFrames, 0.2f);
    auto animate = Animate::create(animation);

    this->runAction(Sequence::create(
        animate,
        CallFunc::create([=]() {
        this->initWithSpriteFrameName(afterStart);
        canMove = true;
        if (dynamic_cast<PlayerTank*>(this))
            this->beInvincible(3);
    }),
        nullptr
        ));
}

void TankBase::beInvincible(int time) {
    _isInvincible = true;
    auto ring = Sprite::create();
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteFrames;
    for (int i = 0; i < 2 * time * 5; i++) {
        std::string n = std::to_string(i % 2);
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName("ring_" + n);
        spriteFrames.pushBack(spriteFrame);
    }
    auto animation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
    auto animate = Animate::create(animation);
    this->addChild(ring);
    ring->setPosition(this->getContentSize() / 2);
    ring->runAction(Sequence::create(
        animate,
        CallFunc::create([=]() {
        ring->removeFromParent();
        _isInvincible = false;
    })
        , nullptr
        ));
}

void TankBase::disBlood() {
    if (_isInvincible)
        return;

    auto spriteFrameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteFrames;

    for (int i = 0; i != 5; i++) {
        std::string n = std::to_string(i);
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName("blast_" + n);
        spriteFrames.pushBack(spriteFrame);
    }

    // TODO 每次死亡都重新构造动画
    auto blastAnimation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
    auto blastanimate = Animate::create(blastAnimation);

    // 播放动画
    auto node = Sprite::create();
    MapLayer::getInstance()->addChild(node);
    node->setPosition(this->getPosition());
    node->runAction(Sequence::create(blastanimate,
                                     CallFunc::create([node] {node->removeFromParentAndCleanup(true); }),
                                     nullptr));
    if (--_blood == 0) {
        // 播放音效
        AudioEngine::play2d("music/enemy-bomb.mp3");

        // 移除该坦克
        auto& enemies = MapLayer::getInstance()->getEnemies();
        enemies.eraseObject(dynamic_cast<EnemyTank*>(this));
        this->removeFromParentAndCleanup(true);
    }
}

void TankBase::addSpriteFrameCache() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    // 坦克爆炸帧动画
    auto* blast_0 = Sprite::create("images/blast/0.png")->getSpriteFrame();
    auto* blast_1 = Sprite::create("images/blast/1.png")->getSpriteFrame();
    auto* blast_2 = Sprite::create("images/blast/2.png")->getSpriteFrame();
    auto* blast_3 = Sprite::create("images/blast/3.png")->getSpriteFrame();
    auto* blast_4 = Sprite::create("images/blast/4.png")->getSpriteFrame();

    blast_0->getTexture()->setAliasTexParameters();
    blast_1->getTexture()->setAliasTexParameters();
    blast_2->getTexture()->setAliasTexParameters();
    blast_3->getTexture()->setAliasTexParameters();
    blast_4->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(blast_0, "blast_0");
    spriteFrameCache->addSpriteFrame(blast_1, "blast_1");
    spriteFrameCache->addSpriteFrame(blast_2, "blast_2");
    spriteFrameCache->addSpriteFrame(blast_3, "blast_3");
    spriteFrameCache->addSpriteFrame(blast_4, "blast_4");

    // 坦克出生前的星星帧动画
    auto star_0 = Sprite::create("images/star0.png")->getSpriteFrame();
    auto star_1 = Sprite::create("images/star1.png")->getSpriteFrame();
    auto star_2 = Sprite::create("images/star2.png")->getSpriteFrame();
    auto star_3 = Sprite::create("images/star3.png")->getSpriteFrame();

    star_0->getTexture()->setAliasTexParameters();
    star_1->getTexture()->setAliasTexParameters();
    star_2->getTexture()->setAliasTexParameters();
    star_3->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(star_0, "star_0");
    spriteFrameCache->addSpriteFrame(star_1, "star_1");
    spriteFrameCache->addSpriteFrame(star_2, "star_2");
    spriteFrameCache->addSpriteFrame(star_3, "star_3");

    // 坦克保护环帧动画
    auto ring_0 = Sprite::create("images/ring0.png")->getSpriteFrame();
    auto ring_1 = Sprite::create("images/ring1.png")->getSpriteFrame();

    ring_0->getTexture()->setAliasTexParameters();
    ring_1->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(ring_0, "ring_0");
    spriteFrameCache->addSpriteFrame(ring_1, "ring_1");
}

void TankBase::shoot() {
    if (!canMove) {
        return;
    }

    auto bullet = _bullets.at(0);
    if (!bullet->isVisible()) {
        _shoot(bullet);
    }
}

cocos2d::Vector<Bullet*>& TankBase::getAllBullets() {
    return _bullets;
}

Bullet* TankBase::getBullet1() {
    return _bullets.at(0);
}

void TankBase::_shoot(Bullet* bullet) {
    if (dynamic_cast<PlayerTank*>(this))
        AudioEngine::play2d("music/shoot.mp3");
    auto position = this->getPosition();
    switch (_dir) {
    case Direction::LEFT:
        bullet->setSpriteFrame("bullet_l");
        bullet->setPosition(position.x - TANK_SIZE / 2.0f, position.y);
        break;
    case Direction::UP:
        bullet->setSpriteFrame("bullet_u");
        bullet->setPosition(position.x, position.y + TANK_SIZE / 2.0f);
        break;
    case Direction::RIGHT:
        bullet->setSpriteFrame("bullet_r");
        bullet->setPosition(position.x + TANK_SIZE / 2.0f, position.y);
        break;
    case Direction::DOWN:
        bullet->setSpriteFrame("bullet_d");
        bullet->setPosition(position.x, position.y - TANK_SIZE / 2.0f);
        break;
    default:
        break;
    }

    bullet->setDirection(_dir);
    bullet->setVisible(true);
    bullet->startMove();
}
