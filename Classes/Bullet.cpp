#include "Bullet.h"
#include "Common.h"
#include "MapLayer.h"

#include "AudioEngine.h"

USING_NS_CC;

bool Bullet::init() {
	if (!Sprite::init()) {
		return false;
	}

	this->setVisible(false);

	return true;
}

void Bullet::startMove() {
	this->schedule(CC_SCHEDULE_SELECTOR(Bullet::__autoMove), 0.008f);
}

void Bullet::__stopMove() {
	this->unschedule(CC_SCHEDULE_SELECTOR(Bullet::__autoMove));
}

void Bullet::setDir(Dir d) {
	dir = d;
}

void Bullet::setLevel(BulletLevel lev) {
	level = lev;
}

void Bullet::__showEffect() {
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	auto mapLayer = MapLayer::getInstance();

	auto animation = Animation::createWithSpriteFrames({
		spriteFrameCache->getSpriteFrameByName("bumb_0"),
		spriteFrameCache->getSpriteFrameByName("bumb_1"),
		spriteFrameCache->getSpriteFrameByName("bumb_2")
		},
		0.05f);

	auto effect = Sprite::create();
	mapLayer->addChild(effect);
	effect->setPosition(this->getPosition());

	effect->runAction(Sequence::create(
		Animate::create(animation),
		CallFunc::create([=]() {
			mapLayer->removeChild(effect);
			}),
		nullptr)
	);
}

void Bullet::__autoMove(float t) {
	// 1. �ƶ�ʱ���͵�ͼ��Ե����ײ
	// 2. �ƶ�ʱ���ͷ������ײ
	// 3. �ƶ�ʱ����̹�˵���ײ
	// 4. �ƶ�ʱ�����ӵ�����ײ

	auto position = this->getPosition();
	auto step = 1;
	if (level >= 1) {
		step = 2;
	}

	// ��������ƶ�
	switch (dir) {
	case Dir::LEFT:
		this->setPositionX(position.x - step);
		break;
	case Dir::UP:
		this->setPositionY(position.y + step);
		break;
	case Dir::RIGHT:
		this->setPositionX(position.x + step);
		break;
	case Dir::DOWN:
		this->setPositionY(position.y - step);
		break;
	default:
		break;
	}

	// ���������ײ:
	// <1> �����ӵ�
	// <2.1> ����ǵ��ˣ�����˵�Ѫ
	// <2.2> ����Ƿ��飬�򷽿鱻�ݻ�(������ҵȼ�)
	// <2.3> �����ǽ�ڣ���ʲô������
	// <3> չʾ�ӵ���ײ��Ч
	// <4> ֹͣ�Զ��ƶ�
	if (__isBlockIntersection() || __isMapIntersection() || __isTankIntersection()) {
		this->setVisible(false);
		this->__showEffect();
		this->__stopMove();
	}

}

bool Bullet::__isMapIntersection() {
	auto position = this->getPosition();
	if (position.x - BULLET_SIZE / 2 < 0
		|| position.y + BULLET_SIZE / 2 > CENTER_HEIGHT
		|| position.x + BULLET_SIZE / 2 > CENTER_WIDTH
		|| position.y - BULLET_SIZE / 2 < 0) {

		AudioEngine::play2d("music/bin.mp3");
		return true;
	}
	return false;
}

bool Bullet::__isBlockIntersection() {
	// �õ����з���λ��
	auto& blocks = MapLayer::getInstance()->getAllBlocks();
	auto box = getBoundingBox();
	auto count = 0;

	for (auto it = blocks.begin(); it != blocks.end(); ) {
		auto block = (*it);
		// �����ϰ���
		if (block->getCategory() == BlockCategory::OBSTACLE
			&& box.intersectsRect(block->getBoundingBox())) {
			if (block->getType() == BlockType::WALL) {
				// ����ǽ
				auto result =
					dynamic_cast<BlockWall*>(block)->destory(this->dir, box);

				if (result.first) {
					// ������ײ
					count++;
					if (result.second) {
						// ������ײ�ұ��ݻ�
						block->removeFromParent();
						it = blocks.erase(it);
					} else {
						++it;
					}
				} else {
					++it;
				}

				
			} else if (block->getType() == BlockType::STONE) {
				// ����ʯͷ
				if (level >= 2) {
					count++;
					block->removeFromParent();
					it = blocks.erase(it);
				} else {
					AudioEngine::play2d("music/bin.mp3");

					count++;
					++it;
				}
			} else {
				// ������Ӫ
				++it;
			}

		} else {
			// û�������ϰ���
			++it;
		}
	}

	return count;
}

bool Bullet::__isTankIntersection() {
	// TODO
	return false;
}
