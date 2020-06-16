#pragma once

#include "Common.h"
#include "cocos2d.h"
#include <utility>

// �������
enum class BlockCategory {
    OBSTACLE,                     // ̹�˲���ͨ�����ӵ����Դݻ�
    NON_OBSTACLE,                 // ̹�˿���ͨ�����ӵ����ܴݻ�
    RIVER                         // ̹�˲���ͨ�����ӵ����ܴݻ�
};

// ��������
enum class BlockType {
    CAMP,
    FOREST,
    ICE,
    RIVER,
    STONE,
    WALL,
    UNDIFINE
};

class Block : public cocos2d::Sprite {
public:
    bool init() override;             // ���ø����init

    virtual BlockCategory getCategory() = 0;
    virtual BlockType getType() { return BlockType::UNDIFINE; }

    static void addSpriteFrameCache();
};

class __Obstacle : public Block {
public:
    BlockCategory getCategory() override { return BlockCategory::OBSTACLE; }
};

class __NonObstacle : public Block {
public:
    BlockCategory getCategory() override { return BlockCategory::NON_OBSTACLE; }
};

class __River : public Block {
public:
    BlockCategory getCategory() override { return BlockCategory::RIVER; }
};

class BlockCamp : public __Obstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::CAMP; }

    CREATE_FUNC(BlockCamp);
};

class BlockWall : public __Obstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::WALL; }

    std::pair<bool, bool> destory(Dir d, const cocos2d::Rect& box);

    CREATE_FUNC(BlockWall);

private:
    cocos2d::LayerColor* blacks[4]{};        // 4����ɫ���飬�����ڵ�
    bool __isDestory();                      // ��ⷽ���Ƿ񱻴ݻ�
};

class BlockStone : public __Obstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::STONE; }

    CREATE_FUNC(BlockStone);
};

class BlockForest : public __NonObstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::FOREST; }

    CREATE_FUNC(BlockForest);
};

class BlockIce : public __NonObstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::ICE; }

    CREATE_FUNC(BlockIce);
};

class BlockRiver : public __River {
public:
    bool init() override;
    BlockType getType() override { return BlockType::RIVER; }

    CREATE_FUNC(BlockRiver);
};
