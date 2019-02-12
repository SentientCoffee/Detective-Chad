#include "Tutorial.h"
#include "MainMenu.h"

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
	initWalls();
	initPauseMenu();
	
	initMouseListener();
	initKeyboardListener();

	showHitboxes();

	this->scheduleUpdate();

	return true;
}

void Tutorial::onExit() { Scene::onExit(); }

void Tutorial::initSprites() {
	background = Sprite::create("temp/background-map2.png");
	background->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	background->setPosition(0, 0);
	background->setScale(levelScale);

	playerPosition = Vec2(1080, 760) * levelScale;
	player = new g3nts::Character(playerPosition, "characters/chad/chad-left.png");
	this->getDefaultCamera()->setPosition(player->getPosition());

	testLabel = Label::createWithTTF("COLLISION!", "fonts/Marker Felt.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	testLabel->enableOutline(Color4B(Color4F(1, 0, 0, 1)), 5);
	this->addChild(testLabel, -10);
	testLabel->setVisible(false);

	this->addChild(background, -100);
	player->addToScene(this);
}

void Tutorial::initWalls() {
	upperHouseWall   = g3nts::PrimitiveRect(	Vec2(32  , 865) * levelScale, Vec2(1228, 870) * levelScale	);
	lowerHouseWall   = g3nts::PrimitiveRect(	Vec2(32  , 30 ) * levelScale, Vec2(1228, 35)  * levelScale	);
	leftHouseWall    = g3nts::PrimitiveRect(	Vec2(32  , 30 ) * levelScale, Vec2(37  , 870) * levelScale	);
	rightHouseWall_1 = g3nts::PrimitiveRect(	Vec2(1223, 30 ) * levelScale, Vec2(1228, 427) * levelScale	);
	rightHouseWall_2 = g3nts::PrimitiveRect(	Vec2(1223, 605) * levelScale, Vec2(1228, 870) * levelScale	);

	walls.push_back(upperHouseWall);
	walls.push_back(lowerHouseWall);
	walls.push_back(leftHouseWall);
	walls.push_back(rightHouseWall_1);
	walls.push_back(rightHouseWall_2);

	for (g3nts::PrimitiveRect wall : walls) {
		this->addChild(wall.getNode(), -10);
		wall.getNode()->setVisible(false);
	}
}

void Tutorial::initPauseMenu() {
	Label* titleLabel = Label::createWithTTF("PAUSED", "fonts/Marker Felt.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	titleLabel->enableShadow();

	Label* resumeLabel = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* exitLabel = Label::createWithTTF("Back to Main Menu", "fonts/Marker Felt.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	resumeLabel->enableShadow();
	exitLabel->enableShadow();

	MenuItemLabel* titleItem = MenuItemLabel::create(titleLabel);
	MenuItemLabel* resumeButton = MenuItemLabel::create(resumeLabel, [&](Ref* sender) {
		togglePause();
	});
	MenuItemLabel* exitButton = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
		Scene* mainMenuScene = MainMenu::createScene();
		director->replaceScene(TransitionFade::create(2, mainMenuScene));
	});

	titleItem->setPosition(0, windowSize.y * 0.35);
	resumeButton->setPosition(0, -(windowSize.y * 0.25));
	exitButton->setPosition(0, -(windowSize.y * 0.35));

	pauseMenu = Menu::create(titleItem, resumeButton, exitButton, NULL);
	this->addChild(pauseMenu, 100);
	pauseMenu->setVisible(false);
}

void Tutorial::initKeyboardListener() {
	keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		keyboard.keyDown[(int)key] = true;
	};

	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		keyboard.keyDown[(int)key] = false;

		if (key == EventKeyboard::KeyCode::KEY_ESCAPE) {
			togglePause();
		}
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

void Tutorial::showHitboxes() {
	player->getHitbox().getNode()->setVisible(true);
	for(g3nts::PrimitiveRect wall : walls) wall.getNode()->setVisible(true);
}

void Tutorial::update(float dt) {
	typedef EventKeyboard::KeyCode KB;
	
	// CAMERA MOVEMENT (Camera follows the player)
	this->getDefaultCamera()->setPosition(player->getPosition());

	// PLAYER MOVEMENT
	cocos2d::Vec2 newPosition(0, 0);
	// Up and right (W + D)
	if (keyboard.keyDown[(int)KB::KEY_W] && keyboard.keyDown[(int)KB::KEY_D]) {
		newPosition = Vec2(1, 1);
		player->getSprite()->setTexture("characters/chad/chad-up-right.png");
	}
	// Up and left (W + A)
	else if (keyboard.keyDown[(int)KB::KEY_W] && keyboard.keyDown[(int)KB::KEY_A]) {
		newPosition = Vec2(-1, 1);
		player->getSprite()->setTexture("characters/chad/chad-up-left.png");
	}
	// Down and right (S + D)
	else if (keyboard.keyDown[(int)KB::KEY_S] && keyboard.keyDown[(int)KB::KEY_D]) {
		newPosition = Vec2(1, -1);
		player->getSprite()->setTexture("characters/chad/chad-down-right.png");
	}
	// Down and left (S + A)
	else if (keyboard.keyDown[(int)KB::KEY_S] && keyboard.keyDown[(int)KB::KEY_A]) {
		newPosition = Vec2(-1, -1);
		player->getSprite()->setTexture("characters/chad/chad-down-left.png");
	}
	// Up (W)
	else if (keyboard.keyDown[(int)KB::KEY_W]) {
		newPosition = Vec2(0, 1);
		player->getSprite()->setTexture("characters/chad/chad-up.png");
	}
	// Down (S)
	else if (keyboard.keyDown[(int)KB::KEY_S]) {
		newPosition = Vec2(0, -1);
		player->getSprite()->setTexture("characters/chad/chad-down.png");
	}
	// Left (A)
	else if (keyboard.keyDown[(int)KB::KEY_D]) {
		newPosition = Vec2(1, 0);
		player->getSprite()->setTexture("characters/chad/chad-right.png");
	}
	// Right (D)
	else if (keyboard.keyDown[(int)KB::KEY_A]) {
		newPosition = Vec2(-1, 0);
		player->getSprite()->setTexture("characters/chad/chad-left.png");
	}

	player->setPosition(player->getPosition() + (newPosition.getNormalized() * playerSpeed * dt));
	
	testLabel->setVisible(false);
	for (g3nts::PrimitiveRect wall : walls) {
		if (g3nts::isColliding(player->getHitbox(), wall)) {
			testLabel->setPosition(player->getPosition() - Vec2(200, 200));
			testLabel->setVisible(true);
			player->setPosition(player->getPosition() - (newPosition.getNormalized() * playerSpeed * dt));
		}
	}
	

}

void Tutorial::togglePause() {
	gamePaused = !gamePaused;
	pauseMenu->setPosition(this->getDefaultCamera()->getPosition());

	if (gamePaused) {
		playerPosition = player->getPosition();
		player->getSprite()->setVisible(false);

		this->unscheduleUpdate();
		pauseMenu->setVisible(true);
	}
	else {
		pauseMenu->setVisible(false);
		this->scheduleUpdate();

		player->setPosition(playerPosition);
		player->getSprite()->setVisible(true);
	}
}
