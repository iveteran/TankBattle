#include "MenuScene.h"
#include "Common.h"
#include "GameScene.h"
#include "AudioEngine.h"

USING_NS_CC;

cocos2d::Scene* MenuScene::createScene() {
	return MenuScene::create();
}

bool MenuScene::init() {
	if (!Scene::init())
		return false;

	__initBackground();

	return true;
}

//TODO
void MenuScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	auto position = selector->getPosition();
	static int select = 0;

	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
	{	//������Ϸ����
		//���ſ�ʼ����
		int id = AudioEngine::play2d("sound/gamePause.wav");
		
		//�л�����
		Director::getInstance()->replaceScene(GameScene::createScene());
		
	}
	break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		if (select == 0) {
			select = 2;
			selector->setPosition(position.x, position.y - 2 * ARROWS_DIS);
		} else {
			select--;
			selector->setPosition(position.x, position.y + ARROWS_DIS);
		}

		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		if (select == 2) {
			select = 0;
			selector->setPosition(position.x, position.y + 2 * ARROWS_DIS);
		} else {
			select++;
			selector->setPosition(position.x, position.y - ARROWS_DIS);
		}

		break;
	default:
		break;
	}
}

void MenuScene::__initBackground() {
	//��������
	background = Sprite::create("images/select_player.png");
	if (!background) return;

	auto windowSize = Director::getInstance()->getVisibleSize();

	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, windowSize.height));
	this->addChild(background);

	//���������¼�
	auto* listener = EventListenerKeyboard::create();
	
	listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event*) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ENTER:
			background->stopAllActions();
			background->setAnchorPoint(Vec2(0.f, 0.f));
			background->setPosition(Vec2(0.f, 0.f));

			__initSelector();
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//��������
	auto bkAction = Sequence::create(
		MoveTo::create(4.f, Vec2(0, 0)), 
		CallFunc::create([=](){
			this->__initSelector();
		}), 
		nullptr
		);
	background->runAction(bkAction);

	
}

void MenuScene::__initSelector() {
	selector = Sprite::create("images/m0-2-1.png");
	selector->setPosition(ARROWS_X, WINDOW_HEIGHT - ARROWS_Y);

	//ѭ�����Ŷ���
	auto animate = __getAnimFrams();
	selector->runAction(RepeatForever::create(animate));

	this->addChild(selector);

	auto* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyPressed, this);
	_eventDispatcher->removeAllEventListeners();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

Animate* MenuScene::__getAnimFrams() {
	Vector<SpriteFrame*> animFrams;
	animFrams.reserve(2);

	animFrams.pushBack(
		SpriteFrame::create("images/m0-2-1.png", Rect(0, 0, TANK_SIZE, TANK_SIZE)));

	animFrams.pushBack(
		SpriteFrame::create("images/m0-2-2.png", Rect(0, 0, TANK_SIZE, TANK_SIZE)));

	auto animation = Animation::createWithSpriteFrames(animFrams, 0.01f);
	return Animate::create(animation);
}
