#include "Common.h"

#include "MapLayer.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Block.h"

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
    // TODO
    auto enemy = EnemyTank::create();
    this->addChild(enemy);
    enemy->setPosition(PLAYER2_START_X, PLAYER2_START_Y);

    auto bullets = enemy->getAllBullets();
    for (auto bullet : bullets) {
        this->addChild(bullet);
    }

    enemies.pushBack(enemy);
}

void MapLayer::loadLevelData(short stage) {
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
    return players.at(0);
}

Block* MapLayer::getCamp() {
    return blocks.at(0);
}

cocos2d::Vector<Block*>& MapLayer::getAllBlocks() {
    return blocks;
}

const std::string& MapLayer::getMapData() {
    return data;
}
