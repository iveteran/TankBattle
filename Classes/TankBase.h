#pragma once

#include "cocos2d.h"
#include "Bullet.h"
#include "Common.h"

// ̹�˵ȼ�
// ��ҷ�Ϊ4��
// 2�������Ͽɷ�����ö�ӵ�
// ���˷�Ϊ4��
using TankLevel = short;

class TankBase : public cocos2d::Sprite {
public:
    bool init() override;

    virtual void playAnimate();                         // �����ƶ�����
    virtual void stopAnimate();                         // ֹͣ���Ŷ���
    virtual void shoot();                               // �����ӵ�
    virtual void setDir(Dir d) = 0;                     // ̹�˸ı䷽��

    void startMove();                                   // �����Զ��ƶ�
    void stopMove();                                    // ֹͣ�Զ��ƶ�

    cocos2d::Vector<Bullet*>& getAllBullets();          // ���̹��ӵ�е������ӵ�

protected:
    virtual void __initSpriteFrameCache() = 0;          // ��ʼ��̹�˾���֡����
    virtual void __initBullets();                       // �����ӵ�

    void __autoMove(float t);                           // �Զ��ƶ�
    void __adjustPosition();                            // ����λ��Ϊ8�ı���
    void __shoot(Bullet* bullet);                       // �����ӵ���������

    Dir dir;                                            // ̹�˵�ǰ����
    TankLevel level;                                    // ̹�˵�ǰ�ȼ�
    cocos2d::Vector<cocos2d::Animate*> animations[4];   // �洢̹�˶���������͵ȼ���
    cocos2d::Vector<Bullet*> bullets;                   // �洢̹�����е��ӵ�

private:
    static float __adjustNumber(int number);            // ���������ֵ���Ϊ8�ı���
    bool __isMapIntersection();                         // ���̹�����ͼ��Ե����ײ
    bool __isBlockIntersection();                       // ���̹���뷽�����ײ
    bool __isTankIntersection();                        // ���̹��֮�����ײ
};
