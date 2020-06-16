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
    bool init() override;                               // ��ʼ��������ӵ�

    virtual void playAnimate();                         // �����ƶ�����
    virtual void stopAnimate();                         // ֹͣ���Ŷ���
    virtual void shoot();                               // �����ӵ�
    virtual void setDir(Dir d) = 0;                     // ̹�˸ı䷽��

    void startMove();                                   // �����Զ��ƶ�
    void stopMove();                                    // ֹͣ�Զ��ƶ�
    void birthAnimation(std::string);                   // ̹�˳�������
    void beInvincible(int);                             // ʹ̹���޵�

    static void addSpriteFrameCache();

    cocos2d::Vector<Bullet*>& getAllBullets();          // ���̹��ӵ�е������ӵ�
    Bullet* getBullet1();                               // �õ���һ���ӵ�

protected:
    virtual void __initBullets();                       // �����ӵ�
    virtual const cocos2d::Vector<cocos2d::Animate*>*
        __getAnimations() = 0;                          // ��ȡ֡����

    void __autoMove(float t);                           // �Զ��ƶ�
    void __adjustPosition();                            // ����λ��Ϊ8�ı���
    void __shoot(Bullet* bullet);                       // �����ӵ���������

    Dir dir = Dir::DOWN;                                // ̹�˵�ǰ����
    TankLevel level = 0;                                // ̹�˵�ǰ�ȼ�
    bool canMove = false;                               // �ж��ܷ��ƶ����ճ���ʱһ��ʱ�����޷��ƶ���
    cocos2d::Vector<Bullet*> bullets;                   // �洢̹�����е��ӵ�

private:
    static float __adjustNumber(int number);            // ���������ֵ���Ϊ8�ı���
    bool __isMapIntersection();                         // ���̹�����ͼ��Ե����ײ
    bool __isBlockIntersection();                       // ���̹���뷽�����ײ
    bool __isTankIntersection();                        // ���̹��֮�����ײ

    int musicId = -1;                                   // �ƶ�ʱ���ŵ�����id
    bool isMove = false;                                // �ж��Ƿ������ƶ�
    bool isInvincible = false;                          // �ж��Ƿ��޵�
};
