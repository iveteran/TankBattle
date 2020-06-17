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
    void birth(std::string);                            // ̹�˳�������
    void beInvincible(int);                             // ʹ̹���޵�
    virtual void disBlood();                            // ̹�˵�Ѫ

    static void addSpriteFrameCache();

    cocos2d::Vector<Bullet*>& getAllBullets();          // ���̹��ӵ�е������ӵ�
    Bullet* getBullet1();                               // �õ���һ���ӵ�
    bool canMove = false;                               // �ж��ܷ��ƶ����ճ���ʱһ��ʱ�����޷��ƶ���

protected:
    virtual void __initBullets() = 0;                   // �����ӵ�
    virtual const cocos2d::Vector<cocos2d::Animate*>*
        __getAnimations() = 0;                          // ��ȡ֡����

    void __autoMove(float t);                           // �Զ��ƶ�
    void __adjustPosition();                            // ����λ��Ϊ8�ı���
    void __shoot(Bullet* bullet);                       // �����ӵ���������

    Dir dir = Dir::DOWN;                                // ̹�˵�ǰ����
    TankLevel level = 0;                                // ̹�˵�ǰ�ȼ�
    cocos2d::Vector<Bullet*> bullets;                   // �洢̹�����е��ӵ�
    unsigned char blood = 1;                            // ̹������ֵ
    bool isInvincible = false;                          // �ж��Ƿ��޵�
    int moveDistance = 0;                               // �ƶ��ܾ���

private:
    static float __adjustNumber(int number);            // ���������ֵ���Ϊ8�ı���
    bool __isMapIntersection();                         // ���̹�����ͼ��Ե����ײ
    bool __isBlockIntersection();                       // ���̹���뷽�����ײ
    virtual bool __isTankIntersection() = 0;            // ���̹��֮�����ײ

    int musicId = -1;                                   // �ƶ�ʱ���ŵ�����id
    bool isMove = false;                                // �ж��Ƿ������ƶ�
};
