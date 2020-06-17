#include "Common.h"

#include "MapLayer.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Block.h"
#include "RandomUtil.h"

#include <string>

USING_NS_CC;

static MapLayer* _mapLayer = nullptr;

bool MapLayer::init() {
    if (!cocos2d::LayerColor::init()) {
        return false;
    }

    // ���ñ�����ɫΪ��ɫ
    this->initWithColor(Color4B(0, 0, 0, 255));

    // ���ؾ���֡����
    __addSpriteFrameCache();

    return true;
}

MapLayer* MapLayer::getInstance() {
    if (!_mapLayer) {
        _mapLayer = MapLayer::create();
        _mapLayer->retain();
    }

    return _mapLayer;
}

void MapLayer::__addSpriteFrameCache() {
    // ����
    Block::addSpriteFrameCache();

    // �ӵ�
    Bullet::addSpriteFrameCache();

    // ̹��
    TankBase::addSpriteFrameCache();
    PlayerTank::loadFrameAnimation();
    EnemyTank::loadFrameAnimation();
}

void MapLayer::__addEnemy(float x, float y) {
    for (const auto& player : players) {
        if (player->getBoundingBox().containsPoint({ x, y }))
            return;
    }

    for (const auto& enemy : enemies) {
        if (enemy->getBoundingBox().containsPoint({ x, y }))
            return;
    }

    auto enemyTank = EnemyTank::create();
    this->addChild(enemyTank);
    enemyTank->setPosition(x, y);

    auto bullets = enemyTank->getAllBullets();
    for (auto bullet : bullets) {
        this->addChild(bullet);
    }

    enemies.pushBack(enemyTank);
    remainTank--;
}

void MapLayer::autoAddEnemies(float) {
    addEnemies();
}

void MapLayer::autoControlEnemiesDirection(float) {
    for (auto enemy : enemies) {
        enemy->changeDirection();
    }
}

void MapLayer::autoControlEnemiesShoot(float) {
    for (auto enemy : enemies) {
        enemy->shoot();
    }
}

void MapLayer::addPlayer() {
    auto player = PlayerTank::create();
    this->addChild(player);
    player->setPosition(PLAYER1_START_X, PLAYER1_START_Y);

    auto bullets = player->getAllBullets();
    for (auto& bullet : bullets) {
        this->addChild(bullet, 100);
    }

    players.pushBack(player);
}

void MapLayer::addEnemies() {
    // ��ʼʱ���3��̹��
    if (remainTank == ENEMIES_COUNT) {
        __addEnemy(ENEMY1_STAR_X, ENEMY1_STAR_Y);
        __addEnemy(ENEMY2_STAR_X, ENEMY2_STAR_Y);
        __addEnemy(ENEMY3_STAR_X, ENEMY3_STAR_Y);
    } else {
        if (remainTank == 0) return;

        // ��̹������С��6��ʱ
        if (enemies.size() < 6) {
            // ������һ��
            switch (RandomUtil::random(0, 2)) {
            case 0:
                __addEnemy(ENEMY1_STAR_X, ENEMY1_STAR_Y);
                break;
            case 1:
                __addEnemy(ENEMY2_STAR_X, ENEMY2_STAR_Y);
                break;
            case 2:
                __addEnemy(ENEMY3_STAR_X, ENEMY3_STAR_Y);
                break;
            default:
                break;
            }
        }
    }
}

void MapLayer::resetMap() {
    blocks.clear();
    data.clear();
    enemies.clear();
    players.clear();
    this->cleanup();
    this->removeAllChildrenWithCleanup(true);
    this->remainTank = ENEMIES_COUNT;
    this->isCampOk = true;
}

void MapLayer::loadLevelData(short stage) {
    // ������
    resetMap();

    // ����Ӵ�Ӫ
    auto camp = BlockCamp::create();
    this->addChild(camp);
    camp->setPosition(CAMP_X, CAMP_Y);
    blocks.pushBack(camp);

    // Ȼ�������������
    std::string filename = "maps/" + std::to_string(stage) + ".txt";
    data = FileUtils::getInstance()->getStringFromFile(filename);

    int index = 0;

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            char c = data[index++];
            if (c == '\r') {
                j--;
                index++;
                continue;
            }
            // ���쾫��
            Block* block = nullptr;

            // ������ͬ���͵ķ���
            if (c == '3') {
                block = BlockWall::create();
            } else if (c == '5') {
                block = BlockStone::create();
            } else if (c == '1') {
                block = BlockForest::create();
            } else if (c == '4') {
                block = BlockRiver::create();
            } else if (c == '2') {
                block = BlockIce::create();
            }

            if (block) {
                // ��������ӵ�ͼ��
                if (block->getType() == BlockType::FOREST) {
                    this->addChild(block, 101);
                } else {
                    this->addChild(block);
                }

                // ���þ�����ͼ���ϵ�λ��
                block->setAnchorPoint(Vec2(0, 0));
                block->setPosition(Vec2((float)j * BLOCK_SIZE, (float)(25 - i) * BLOCK_SIZE));

                // �洢vector
                blocks.pushBack(block);
            }

        }
    }
}

PlayerTank* MapLayer::getPlayer1() {
    if (players.size() > 0)
        return players.at(0);
    return nullptr;
}

Block* MapLayer::getCamp() {
    return blocks.at(0);
}

cocos2d::Vector<Block*>& MapLayer::getAllBlocks() {
    return blocks;
}

cocos2d::Vector<EnemyTank*>& MapLayer::getEnemies() {
    return enemies;
}

cocos2d::Vector<PlayerTank*>& MapLayer::getPlayers() {
    return players;
}

void MapLayer::enableAutoAddEnemies(bool b) {
    if (b) {
        // ÿ��6�����һ������
        this->schedule(CC_SCHEDULE_SELECTOR(MapLayer::autoAddEnemies), 6.0f);
    } else {
        this->unschedule(CC_SCHEDULE_SELECTOR(MapLayer::autoAddEnemies));
    }
}

void MapLayer::enableAutoControlEnemies(bool b) {
    if (b) {
        this->schedule(CC_SCHEDULE_SELECTOR(MapLayer::autoControlEnemiesDirection), 0.1f);
        this->schedule(CC_SCHEDULE_SELECTOR(MapLayer::autoControlEnemiesShoot), 0.5f);
    } else {
        this->unschedule(CC_SCHEDULE_SELECTOR(MapLayer::autoControlEnemiesDirection));
        this->unschedule(CC_SCHEDULE_SELECTOR(MapLayer::autoControlEnemiesShoot));
    }
}

const std::string& MapLayer::getMapData() {
    return data;
}
