#include "Tutorial.h"

USING_NS_CC;

cocos2d::Scene* Tutorial::createScene() { return Tutorial::create(); }

void Tutorial::onEnter() { Scene::onEnter(); }

bool Tutorial::init() {
	if (!Scene::init()) return false;

	director = Director::getInstance();
	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();

	initSprites();
	initHitboxes();
	initPauseMenu();
	initMouseListener();
	initKeyboardListener();

	//camera = Camera::createOrthographic(windowSize.x, windowSize.y, 1, 1000);
	//camera->lookAt(Vec3(player->getPosition().x, player->getPosition().y, 0), Vec3::UNIT_Z);
	//
	//this->addChild(camera, 1000);
	//this->getDefaultCamera()->setVisible(false);

	this->scheduleUpdate();

	return true;
}

void Tutorial::onExit() { Scene::onExit(); }

void Tutorial::initSprites() {
	background = Sprite::create("temp/background-map.png");
	//background->setScale(2.0f);
	background->setPosition(windowSize.x / 2, windowSize.y / 2);

	player = new g3nts::Character(cocos2d::Vec2(windowSize.x / 2, windowSize.y / 2), "characters/chad/chad-right.png");

	this->addChild(background, -100);
	this->addChild(player->getSprite());
}

void Tutorial::initHitboxes() {

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

	//this->getDefaultCamera()->setPosition(player->getPosition());

	if (keyboard.keyDown[(int)KB::KEY_W] && keyboard.keyDown[(int)KB::KEY_D]) {
		cocos2d::Vec2 newPosition(1, 1);
		player->getSprite()->setTexture("characters/chad/chad-up-right.png");
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed * dt));
	}
	else if (keyboard.keyDown[(int)KB::KEY_W] && keyboard.keyDown[(int)KB::KEY_A]) {
		cocos2d::Vec2 newPosition(-1, 1);
		player->getSprite()->setTexture("characters/chad/chad-up-left.png");
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed * dt));
	}
	else if (keyboard.keyDown[(int)KB::KEY_S] && keyboard.keyDown[(int)KB::KEY_D]) {
		cocos2d::Vec2 newPosition(1, -1);
		player->getSprite()->setTexture("characters/chad/chad-down-right.png");
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed * dt));
	}
	else if (keyboard.keyDown[(int)KB::KEY_S] && keyboard.keyDown[(int)KB::KEY_A]) {
		cocos2d::Vec2 newPosition(-1, -1);
		player->getSprite()->setTexture("characters/chad/chad-down-left.png");
		player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed * dt));
	}
	else if (keyboard.keyDown[(int)KB::KEY_W]) {
		player->getSprite()->setTexture("characters/chad/chad-up.png");
		player->setPosition(player->getPosition().x, player->getPosition().y + playerSpeed * dt);
	}
	else if (keyboard.keyDown[(int)KB::KEY_S]) {
		player->getSprite()->setTexture("characters/chad/chad-down.png");
		player->setPosition(player->getPosition().x, player->getPosition().y - playerSpeed * dt);
	}
	else if (keyboard.keyDown[(int)KB::KEY_D]) {
		player->getSprite()->setTexture("characters/chad/chad-right.png");
		player->setPosition(player->getPosition().x + playerSpeed * dt, player->getPosition().y);
	}
	else if (keyboard.keyDown[(int)KB::KEY_A]) {
		player->getSprite()->setTexture("characters/chad/chad-left.png");
		player->setPosition(player->getPosition().x - playerSpeed * dt, player->getPosition().y);
	}

}
