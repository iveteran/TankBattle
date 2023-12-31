#pragma once

#include "Block.h"
#include "Direction.h"

class ImmovableBlock : public Block {
public:
    bool init() override { return Block::init(); }
    BlockType getType() const override { return BlockType::IMMOVABLE_BLOCK; }

    virtual bool movable() const override { return false; }

    virtual std::string getSpriteFrameName() const { return ""; } // FIXME
};

class MapBorder : public ImmovableBlock {
public:
    static const int DefaultFloor = 0;

    CREATE_FUNC(MapBorder);

    static MapBorder* TOP();
    static MapBorder* RIGHT();
    static MapBorder* BOTTOM();
    static MapBorder* LEFT();

    Direction direction;

public:
    bool init() override;
    BlockType getType() const override { return BlockType::MAP_BORDER; }
};

class BlockWall : public ImmovableBlock {
public:
    static constexpr float BRICK_SIZE = Block::SIZE / 2;

    static const int DefaultFloor = 0;
    static const constexpr char* UIIcon = "images/block-icon-brick-wall.png";

    CREATE_FUNC(BlockWall);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::WALL; }

    std::pair<int, bool> destory(Direction dir, const cocos2d::Rect& box);

    virtual void onBeCollided(Block* activeBlock) override;

private:
    bool _isDestory();                      // 检测方块是否被摧毁

private:
    cocos2d::LayerColor* _blacks[4]{};      // 4个黑色方块，用于遮挡
};

class BlockStone : public ImmovableBlock {
public:
    static const int DefaultFloor = 0;
    static const constexpr char* UIIcon = "images/block-icon-stone-wall.png";

    CREATE_FUNC(BlockStone);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::STONE; }

    virtual void onBeCollided(Block* activeBlock) override;
};

class BlockForest : public ImmovableBlock {
public:
    static const int DefaultFloor = 9;
    static const constexpr char* UIIcon = "images/block-icon-forest.png";

    CREATE_FUNC(BlockForest);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::FOREST; }
};

class BlockBridge : public ImmovableBlock {
public:
    static const int DefaultFloor = 0;
    static const constexpr char* UIIcon = "images/block-icon-bridge.png";

    CREATE_FUNC(BlockBridge);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::BRIDGE; }
};

class BlockCloud : public ImmovableBlock {
public:
    static const int DefaultFloor = 99;
    static const constexpr char* UIIcon = "images/block-icon-cloud.png";

    CREATE_FUNC(BlockCloud);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::CLOUD; }
};

class BlockIce : public ImmovableBlock {
public:
    static const int DefaultFloor = 0;
    static const constexpr char* UIIcon = "images/block-icon-ice.png";

    CREATE_FUNC(BlockIce);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::ICE; }
};

class BlockTrench : public ImmovableBlock {
public:
    static const int DefaultFloor = -1;
    static const constexpr char* UIIcon = "images/block-icon-trench.png";

    CREATE_FUNC(BlockTrench);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::TRENCH; }
};

class BlockRiver : public ImmovableBlock {
public:
    static const int DefaultFloor = -1;
    static const constexpr char* UIIcon = "images/block-icon-river.png";

    CREATE_FUNC(BlockRiver);
    static void initSpriteFrameCache();

public:
    bool init() override;
    BlockType getType() const override { return BlockType::RIVER; }
};

//class BlockBarrier : public ImmovableBlock {
//public:
//    static const int DefaultFloor = -1;
//    static const constexpr char* UIIcon = "images/block-icon-barrier.png";
//
//    CREATE_FUNC(BlockBarrier);
//    static void initSpriteFrameCache();
//
//public:
//    bool init() override;
//    BlockType getType() const override { return BlockType::BARRIER; }
//};
