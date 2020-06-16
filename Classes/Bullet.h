#pragma once

#include "cocos2d.h"
#include "Common.h"

using BulletLevel = short;

class Bullet : public cocos2d::Sprite {
public:
    bool init() override;

    void startMove();

    void setDir(Dir d);
    void setLevel(BulletLevel lev);

    static void addSpriteFrameCache();

    CREATE_FUNC(Bullet);

private:
    void __autoMove(float t);
    void __stopMove();
    bool __isMapIntersection();               // ���͵�ͼ��Ե����ײ
    bool __isBlockIntersection();             // ���ͷ������ײ
    bool __isTankIntersection();              // ����̹�˵���ײ
    void __showEffect();                      // չʾ��ײ��Ч

    Dir dir{};                                // �ӵ�����
    BulletLevel level{};                      // �ӵ��ȼ�
};
