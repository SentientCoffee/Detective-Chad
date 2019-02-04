#include "Tutorial.h"

USING_NS_CC;

cocos2d::Scene * Tutorial::createScene() { return Tutorial::create(); }

void Tutorial::onEnter() { Scene::onEnter(); }

bool Tutorial::init() {
	if (!Scene::init()) return false;

	director = Director::getInstance();
	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();

	initSprites();
	initPauseMenu();
	initMouseListener();
	initKeyboardListener();

	this->scheduleUpdate();

	return true;
}

void Tutorial::onExit() { Scene::onExit(); }

void Tutorial::initSprites() {
	background = Sprite::create("temp/background.jpg");
	background->setScale(2.0f);
	background->setPosition(windowSize.x / 2, windowSize.y / 2);

	player = Sprite::create("characters/chad/chad-right.png");
	//player->setScale(0.2);
	player->setPosition(windowSize.x / 2, windowSize.y / 2);

	this->addChild(background, -100);
	this->addChild(player);
}

void Tutorial::initPauseMenu() {
	Label* title = Label::createWithTTF("PAUSED", "fonts/Marker Felt.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	
	title->enableShadow();
}

void Tutorial::initKeyboardListener() {
	keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		keyboard.keyDown[(int)key] = true;
	};

	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		keyboard.keyDown[(int)key] = false;

		/*if (key == EventKeyboard::KeyCode::KEY_ESCAPE) {
			togglePause();
		}*/
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Tutorial::initMouseListener() {
	mouseListener = EventListenerMouse::create();

	mouseListener->onMouseDown = [&](Event* mEvent) {};
	mouseListener->onMouseUp = [&](Event* mEvent) {};
	mouseListener->onMouseMove = [&](Event* mEvent) {};
	mouseListener->onMouseScroll = [&](Event* mEvent) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

}

void Tutorial::update(float dt) {

	typedef EventKeyboard::KeyCode KB;

	if (keyboard.keyDown[(int)KB::KEY_W] && keyboard.keyDown[(int)KB::KEY_D]) {
		Vec2 newPosition(1, 1);
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed));
	}
	else if (keyboard.keyDown[(int)KB::KEY_W] && keyboard.keyDown[(int)KB::KEY_A]) {
		Vec2 newPosition(-1, 1);
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed));
	}
	else if (keyboard.keyDown[(int)KB::KEY_S] && keyboard.keyDown[(int)KB::KEY_D]) {
		Vec2 newPosition(1, -1);
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed));
	}
	else if (keyboard.keyDown[(int)KB::KEY_S] && keyboard.keyDown[(int)KB::KEY_A]) {
		Vec2 newPosition(-1, -1);
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed));
	}
	else if (keyboard.keyDown[(int)KB::KEY_W]) {
		player->setTexture("characters/chad/chad-up.png");
		player->setPositionY(player->getPositionY() + playerSpeed);
	}
	else if (keyboard.keyDown[(int)KB::KEY_S]) {
		player->setTexture("characters/chad/chad-down.png");
		player->setPositionY(player->getPositionY() - playerSpeed);
	}

	else if (keyboard.keyDown[(int)KB::KEY_D]) {
		player->setTexture("characters/chad/chad-right.png");
		player->setPositionX(player->getPositionX() + playerSpeed);
	}
	else if (keyboard.keyDown[(int)KB::KEY_A]) {
		player->setTexture("characters/chad/chad-left.png");
		player->setPositionX(player->getPositionX() - playerSpeed);
	}

}
