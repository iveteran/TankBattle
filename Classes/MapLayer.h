#pragma once

#include "cocos2d.h"
#include "Vec2Hash.h"

#include "Block.h"
#include "constants/MapConstants.h"
#include "Direction.h"
#include "Utils.h"
#include "Camp.h"

#include <map>
#include <string>

using cocos2d::Node;
using cocos2d::LayerColor;
using cocos2d::Rect;
using cocos2d::Vector;
using cocos2d::Map;
using cocos2d::Vec2;
using cocos2d::Vec3;

using YAxisBlock = std::map<int, Block*>;
using XYAxisBlock = std::map<int, YAxisBlock>;
using FloorXYAxisBlockMap = std::map<int, XYAxisBlock>;
using CoordBlockMap = Map<Vec2, Block*>;

using BlockPositionFilter = std::function<bool(const Vec2&)>;

class MovableBlock;
class Camp;
class Player;
class GameRuntime;

class MapLayer : public LayerColor {
public:
    bool init() override;

    static void initSpriteFrameCache();             // 加载精灵帧缓存

    static MapLayer* getInstance();                 // 得到地图图层实例

    //void loadCamp();
    bool loadMapData();
    void loadLevelData(short stage);                // 加载指定关卡的数据
    void loadGame(GameRuntime* gameRuntime);

    void createCamps();
    const Vector<Camp*> getCamps() const;
    Camp* createCamp(const Vec2& pos);
    Camp* getPublicCamp() const;
    Camp* getCamp() const;
    Camp* getEnemyCamp() const;
    void createCampusParapetWall(const Camp* camp);

    Player* getPlayer1() const;                       // 得到玩家1
    const std::string& getMapData();                // 得到地图数据

    CoordBlockMap getAroundBlocks(const Block* block, int blockFloor=NoneFloor,
            Direction dir=Direction::NONE);
    CoordBlockMap getInsideSquareBlocks(const Vec2& origin, float sideLength,
            const BlockTypeSet& btSet, const BlockPositionFilter& positionFilter, int floor=NoneFloor);
    CoordBlockMap getInsideCircleBlocks(const Vec2& center, float radius,
            const BlockTypeSet& btSet, int floor=NoneFloor);

    bool addAndManageBlock(Block* block);
    bool removeAndUnmanageBlock(Block* block);
    void addNode(Node* node);
    void removeNode(Node* node);

    bool manageBlock(Block* block);
    bool unmanageBlock(Block* block);
    bool updateBlockPosition(MovableBlock* block);
    bool hasBlockAtPosition(const Vec2& pos, int floor=0) const;

    bool createBlock(int i, int j, BlockType t, Actor* actor=nullptr);
    bool createBlock(float x, float y, BlockType t, Actor* actor=nullptr);
    bool createBlock(const Vec2& pos, BlockType t, Actor* actor=nullptr);
    int createBlocks(const std::vector<Vec2>& posList, BlockType t, Actor* actor=nullptr);

    void resetMap();                                // 清理工作
    void clearBlocks();

private:
    CREATE_FUNC(MapLayer);                          // 单例对象

    using Node::addChild;           // make it private, to use addNode/addAndManageBlock instead of it
    using Node::removeChild;        // make it private, to use removeNode/removeAndUnmanageBlock instead of it

    bool _addBlock(float x, float y, BlockType t, Actor* actor=nullptr);
    bool _addBlock(int i, int j, BlockType t, Actor* actor=nullptr);

    bool _manageBlock(Block* block, FloorXYAxisBlockMap& floorPosBlocks);
    bool _updateBlockPosition(const Vec3& updatePos, BlockType type, Block* block);
    bool _updateBlockPosition(const Vec3& updatePos, Block* block, FloorXYAxisBlockMap& floorPosBlocks);
    Block* _removeBlockPosition(int floor, int x, int y,  FloorXYAxisBlockMap& floorPosBlocks);

    Vec3 _getBlockMngmtPosition(int64_t blockId);
    void _addBlockMngmtPosition(int64_t blockId, const Vec3& mngmtPos);
    void _removeBlockMngmtPosition(int64_t blockId);

    void _getAroundBlocks(CoordBlockMap& posBlocks, const Block* block,
            const XYAxisBlock& xyAxisBlock, Direction dir=Direction::NONE);
    void _getInsideSquareBlocks(CoordBlockMap& posBlocks,/* output */
        const Vec2& origin, float sideLength, const BlockTypeSet& btSet,
        const BlockPositionFilter& positionFilter,
        const XYAxisBlock& xyAxisBlock);

private:
    FloorXYAxisBlockMap _floorPosBlocks;
    FloorXYAxisBlockMap _floorPosPlayers;
    FloorXYAxisBlockMap _floorPosWeapons;
    std::unordered_map<int64_t, Vec3> _blockIdPositionMap;

    std::string _mapData;                               // 地图数据

    Camp* _publicCamp = nullptr;
    Camp* _camp = nullptr;
    Camp* _enemyCamp = nullptr;
    Vector<Camp*> _camps;
    Player* _player1 = nullptr;
};
