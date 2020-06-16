#include "MenuScene.h"
#include "Common.h"
#include "GameScene.h"
#include "AudioEngine.h"
#include "CCEventListener.h"

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

// TODO
void MenuScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    auto position = selector->getPosition();
    static int select = 0;

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_ENTER:
    {
        // �л�����
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

// TODO
bool MenuScene::onTouch(cocos2d::Touch* touch, cocos2d::Event*) {
    // �л�����
    Director::getInstance()->replaceScene(GameScene::createScene());

    return true;
}

void MenuScene::__initBackground() {
    offsetNode = Node::create();
    this->addChild(offsetNode);
    offsetNode->setPosition(Director::getInstance()->getVisibleSize() / 2);

    // ��������ͼƬ
    background = Sprite::create("images/select_player.png");
    if (!background) return;

    offsetNode->addChild(background);
    background->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));

    // ���¿ո�����
    auto* keyboardListener = EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event*) {
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_SPACE:
            background->stopAllActions();
            background->setPosition(Vec2(0.f, 0.f));

            if (!isSelectorInit)
                __initSelector();
            break;
        default:
            break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // ������Ļ���
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event*) {
        background->stopAllActions();
        background->setPosition(Vec2(0.f, 0.f));

        if (!isSelectorInit)
            __initSelector();

        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    //��������
    auto bkAction = Sequence::create(
        MoveTo::create(4.f, Vec2(0, 0)),
        CallFunc::create([=]() {
        if (!isSelectorInit)
            __initSelector();
    }),
        nullptr
        );

    background->runAction(bkAction);
}

void MenuScene::__initSelector() {
    selector = Sprite::create("images/m0-2-1.png");
    selector->setPosition(ARROWS_X, WINDOW_HEIGHT - ARROWS_Y);

    // ѭ�����Ŷ���
    auto animate = __getAnimFrames();
    selector->runAction(RepeatForever::create(animate));

    background->addChild(selector);

    // ʹ�ü����ƶ����
    auto* keyBoardlistener = EventListenerKeyboard::create();
    keyBoardlistener->onKeyPressed = CC_CALLBACK_2(MenuScene::onKeyPressed, this);

    // ������Ļ�ƶ����
    auto* touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouch, this);

    // �����¼�
    _eventDispatcher->removeAllEventListeners();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardlistener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    isSelectorInit = true;
}

Animate* MenuScene::__getAnimFrames() {
    Vector<SpriteFrame*> animFrams;
    animFrams.reserve(2);

    animFrams.pushBack(
        SpriteFrame::create("images/m0-2-1.png", Rect(0, 0, TANK_SIZE, TANK_SIZE)));

    animFrams.pushBack(
        SpriteFrame::create("images/m0-2-2.png", Rect(0, 0, TANK_SIZE, TANK_SIZE)));

    auto animation = Animation::createWithSpriteFrames(animFrams, 0.01f);
    return Animate::create(animation);
}
