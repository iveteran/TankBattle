#pragma once

#include "TankBase.h"

enum class AttacTarget {
    PLAYER, CAMP
};

class EnemyTank : public TankBase {
public:
    CREATE_FUNC(EnemyTank);

    bool init() override;

    void setDir(Dir d) override;

    static void loadFrameAnimation();                          // ����̹���ƶ�֡����

protected:
    void __initBullets() override;
    const cocos2d::Vector<cocos2d::Animate*>*
        __getAnimations() override;

private:
    static cocos2d::Vector<cocos2d::Animate*> animations[4];   // �洢̹���ƶ�֡����������͵ȼ���
    AttacTarget target = AttacTarget::PLAYER;                  // ̹�˵Ĺ���Ŀ��
};
