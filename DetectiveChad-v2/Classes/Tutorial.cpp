#include "Tutorial.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* Tutorial::createScene() { return Tutorial::create(); }

void Tutorial::onEnter() { Scene::onEnter(); }

bool Tutorial::init() {
	if (!Scene::init()) return false;

	initDirector();
	initSpriteCache();

	initPlayer();
	initItems();
	initLevel();
	initWalls();
	initPauseMenu();
	
	initMouseListener();
	initKeyboardListener();

	showHitboxes();

	this->scheduleUpdate();
	return true;
}

void Tutorial::onExit() { Scene::onExit(); }

void Tutorial::initDirector() {
	director = Director::getInstance();

	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();
}

void Tutorial::initSpriteCache() {
	spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("characters/characters.plist");
	spriteCache->addSpriteFramesWithFile("items/items.plist");
}

void Tutorial::initPlayer() {
	playerPosition = Vec2(1080, 760) * levelScale;
	this->getDefaultCamera()->setPosition(playerPosition);

	// Playable character with animations
	player = new g3nts::Character(playerPosition, spriteCache->getSpriteFrameByName("chad/idle/left/01.png"));
	player->addAnimation("upWalk", "chad/walk/up/%02d.png", 4);
	player->addAnimation("downWalk", "chad/walk/down/%02d.png", 4);
	player->addAnimation("leftWalk", "chad/walk/left/%02d.png", 4);
	player->addAnimation("rightWalk", "chad/walk/right/%02d.png", 4);

	player->addAnimation("upLeftWalk", "chad/walk/up-left/%02d.png", 4);
	player->addAnimation("upRightWalk", "chad/walk/up-right/%02d.png", 4);
	player->addAnimation("downLeftWalk", "chad/walk/down-left/%02d.png", 4);
	player->addAnimation("downRightWalk", "chad/walk/down-right/%02d.png", 4);

	player->addAnimation("upIdle", "chad/idle/up/%02d.png", 1);
	player->addAnimation("downIdle", "chad/idle/down/%02d.png", 1);
	player->addAnimation("leftIdle", "chad/idle/left/%02d.png", 1);
	player->addAnimation("rightIdle", "chad/idle/right/%02d.png", 1);

	player->addAnimation("upLeftIdle", "chad/idle/up-left/%02d.png", 1);
	player->addAnimation("upRightIdle", "chad/idle/up-right/%02d.png", 1);
	player->addAnimation("downLeftIdle", "chad/idle/down-left/%02d.png", 1);
	player->addAnimation("downRightIdle", "chad/idle/down-right/%02d.png", 1);

	player->addAnimation("flex", "chad/flex/%02d.png", 1);

	player->addToScene(this, 2);
}

void Tutorial::initLevel() {
	// Floor plan sprite
	floorplan = Sprite::create("backgrounds/apartment-floorplan.png");
	floorplan->setScale(levelScale);
	floorplan->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	floorplan->setPosition(Vec2(-800, -1050) * levelScale);
	
	// Upper walls sprite
	upperWalls = Sprite::create("backgrounds/apartment-walls-upper.png");
	upperWalls->setScale(levelScale);
	upperWalls->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	upperWalls->setPosition(Vec2(-800, -1050) * levelScale);
	
	// Middle walls sprite
	middleWalls = Sprite::create("backgrounds/apartment-walls-middle.png");
	middleWalls->setScale(levelScale);
	middleWalls->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	middleWalls->setPosition(Vec2(-800, -1050) * levelScale);

	// Lower walls sprite
	lowerWalls = Sprite::create("backgrounds/apartment-walls-lower.png");
	lowerWalls->setScale(levelScale);
	lowerWalls->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	lowerWalls->setPosition(Vec2(-800, -1050) * levelScale);

	this->addChild(floorplan  , -1000);
	this->addChild(upperWalls ,    0 );
	this->addChild(middleWalls,   10 );
	this->addChild(lowerWalls ,   20 );
}

void Tutorial::initItems() {
	shirt_1 = new g3nts::Item(Vec2(900 , 720) * levelScale, spriteCache->getSpriteFrameByName("items/shirt.png"));
	shirt_2 = new g3nts::Item(Vec2(1050, 680) * levelScale, spriteCache->getSpriteFrameByName("items/shirt.png"), true, "shirt");
	magGlass_1 = new g3nts::Item(Vec2(900, 720) * levelScale, spriteCache->getSpriteFrameByName("items/evidence.png"), true, "evidence");
	
	bathroomMirror = new g3nts::Mirror(Vec2(170, 890) * levelScale, spriteCache->getSpriteFrameByName("items/mirror.png"));
	
	items.push_back(shirt_1);
	items.push_back(shirt_2);
	items.push_back(magGlass_1);

	for (g3nts::Item* item : items) {
		item->addToScene(this);
	}

	bathroomMirror->addToScene(this, 3);
}

void Tutorial::initWalls() {
	//Level boundaries
	upperBoundary = g3nts::PrimitiveRect(Vec2(-180, 1300) * levelScale, Vec2(2000, 1300) * levelScale);
	lowerBoundary = g3nts::PrimitiveRect(Vec2(-180, -300) * levelScale, Vec2(2000, -300) * levelScale);
	leftBoundary  = g3nts::PrimitiveRect(Vec2(-180, -300) * levelScale, Vec2(-180, 1300) * levelScale);
	rightBoundary = g3nts::PrimitiveRect(Vec2(2000, -300) * levelScale, Vec2(2000, 1300) * levelScale);

	// Outer walls
	upperHouseWall   = g3nts::PrimitiveRect(Vec2( 0  , 950) * levelScale, Vec2(1600, 900) * levelScale);
	lowerHouseWall   = g3nts::PrimitiveRect(Vec2( 0  ,  0 ) * levelScale, Vec2(1600,  0 ) * levelScale);
	leftHouseWall    = g3nts::PrimitiveRect(Vec2( 0  ,  2 ) * levelScale, Vec2( 0  , 900) * levelScale);
	rightHouseWall_1 = g3nts::PrimitiveRect(Vec2(1600,  0 ) * levelScale, Vec2(1600, 400) * levelScale);
	rightHouseWall_2 = g3nts::PrimitiveRect(Vec2(1600, 600) * levelScale, Vec2(1600, 900) * levelScale);

	// Inner horizontal walls
	bathroomDoorway_1   = g3nts::PrimitiveRect(Vec2( 0  , 650) * levelScale, Vec2(100 , 600) * levelScale);
	bathroomDoorway_2   = g3nts::PrimitiveRect(Vec2(300 , 650) * levelScale, Vec2(1000, 600) * levelScale);
	bedroomDoorway	    = g3nts::PrimitiveRect(Vec2(1200, 650) * levelScale, Vec2(1600, 600) * levelScale);
	livingRoomDoorway_1 = g3nts::PrimitiveRect(Vec2( 0  , 400) * levelScale, Vec2(150 , 350) * levelScale);
	livingRoomDoorway_2 = g3nts::PrimitiveRect(Vec2(350 , 400) * levelScale, Vec2(1400, 350) * levelScale);
	
	// Inner vertical walls
	verticalBathroomWall	 = g3nts::PrimitiveRect(Vec2(400 , 650) * levelScale, Vec2(400 , 900) * levelScale);
	vecticalLivingRoomWall_1 = g3nts::PrimitiveRect(Vec2(1200, 250) * levelScale, Vec2(1200, 600) * levelScale);
	vecticalLivingRoomWall_2 = g3nts::PrimitiveRect(Vec2(1200,  0 ) * levelScale, Vec2(1200, 50 ) * levelScale);

	// Add all the walls to the walls vector
	walls.push_back(upperBoundary); walls.push_back(lowerBoundary);
	walls.push_back(leftBoundary);  walls.push_back(rightBoundary);

	walls.push_back(upperHouseWall); walls.push_back(lowerHouseWall);
	walls.push_back(leftHouseWall); walls.push_back(rightHouseWall_1); walls.push_back(rightHouseWall_2);

	walls.push_back(bathroomDoorway_1); walls.push_back(bathroomDoorway_2); walls.push_back(bedroomDoorway);
	walls.push_back(livingRoomDoorway_1); walls.push_back(livingRoomDoorway_2);
	
	walls.push_back(verticalBathroomWall); walls.push_back(vecticalLivingRoomWall_1); walls.push_back(vecticalLivingRoomWall_2);

	// Add all the walls to the scene
	for (g3nts::PrimitiveRect wall : walls) {
		this->addChild(wall.getNode(), 20);
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
		togglePause();
		Scene* mainMenuScene = MainMenu::createScene();
		director->replaceScene(TransitionFade::create(2, mainMenuScene));
	});

	titleItem->setPosition(0, windowSize.y * 0.35);
	resumeButton->setPosition(0, -(windowSize.y * 0.25));
	exitButton->setPosition(0, -(windowSize.y * 0.35));

	pauseMenu = Menu::create(titleItem, resumeButton, exitButton, NULL);
	this->addChild(pauseMenu, 1000);
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
		else if (key == EventKeyboard::KeyCode::KEY_SPACE) {
			DelayTime* delay = DelayTime::create(2.0f);
			player->runAnimation("flex");
			player->getSprite()->runAction(delay);

			for (g3nts::Item* item : items) {
				if (item->getPosition().getDistanceSq(player->getPosition()) <= 250 * 250) {
					if (item->isBreakable()) {
						item->getSprite()->setSpriteFrame(spriteCache->getSpriteFrameByName("items/broken-" + item->getTag() + ".png"));
						item->setBreakable(false);
					}

					Vec2 direction = item->getPosition() - player->getPosition();
					item->setVelocity(direction.getNormalized() * 1000.0f);
				}
			}

			if (bathroomMirror->getPosition().getDistanceSq(player->getPosition()) <= 200 * 200) {
				if (!bathroomMirror->isBroken()) {
					bathroomMirror->setBroken(true);
					bathroomMirror->getSprite()->setSpriteFrame(spriteCache->getSpriteFrameByName("items/broken-mirror.png"));
				}
			}
		}
	};

	for (unsigned int i = 0; i < 256; ++i) {
		keyboard.keyDown[i] = false;
	}

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

	// CAMERA MOVEMENT (Camera follows the player)
	if (player->getPosition().x >= 415 * levelScale && player->getPosition().x <= 1400 * levelScale) {
		this->getDefaultCamera()->setPositionX(player->getPosition().x);
	}
	if (player->getPosition().y >= 35 * levelScale && player->getPosition().y <= 965 * levelScale) {
		this->getDefaultCamera()->setPositionY(player->getPosition().y);
	}
	
	// Update the player
	player->update(dt);

	// Update player sprite to be on top or behind walls
	player->setZIndex(25);
	if (player->getPosition().y > livingRoomDoorway_1.getEndPosition().y + 10) player->setZIndex(15);
	if (player->getPosition().y > bedroomDoorway.getEndPosition().y + 10)      player->setZIndex(5);
	

	for (g3nts::Item* item : items) {
		// Update all items in the scene
		item->update(dt);

		item->setZIndex(24);
		if (item->getPosition().y > livingRoomDoorway_1.getEndPosition().y + item->getHitbox().getHeight() / 2.0f - 10) item->setZIndex(14);
		if (item->getPosition().y > bedroomDoorway.getEndPosition().y + item->getHitbox().getHeight() / 2.0f - 10)      item->setZIndex(4);

		// Check item collision with player
		if (g3nts::isColliding(player->getHitbox(), item->getHitbox()) && player->getZIndex() == item->getZIndex() + 1) {

			Vec2 direction = player->getDirection() + item->getPosition() - player->getPosition();

			if (item->getVelocity().getLengthSq() <= 50 * 50)
				item->setVelocity(direction.getNormalized() * 500.0f);
			else {

				if (player->getDirection().getLengthSq() == 0) {
					item->setVelocity((item->getVelocity() + direction).getNormalized() * item->getVelocity().getLength() * 0.2f);
				}
				else {
					item->setVelocity(direction.getNormalized() * 500.0f);
				}

			}

		}

	}

	for (g3nts::PrimitiveRect wall : walls) {

		// Check player collision with walls
		if (g3nts::isColliding(player->getHitbox(), wall) && player->getDirection().getLengthSq() != 0) {
			player->update(-dt);
		}

		// Check item collision with walls
		for (g3nts::Item* item : items) {

			if (g3nts::isColliding(item->getHitbox(), wall)) {

				if (wall.getWidth() <= 50)
					item->setVelocity(Vec2(-item->getVelocity().x, item->getVelocity().y));
				else if (wall.getHeight() <= 50)
					item->setVelocity(Vec2(item->getVelocity().x, -item->getVelocity().y));

			}

		}

	}

}

void Tutorial::togglePause() {
	gamePaused = !gamePaused;
	pauseMenu->setPosition(this->getDefaultCamera()->getPosition());

	if (gamePaused) {
		player->getKeyboardListener()->setEnabled(false);
		this->unscheduleUpdate();
		pauseMenu->setVisible(true);
	}
	else {
		pauseMenu->setVisible(false);
		this->scheduleUpdate();
		player->getKeyboardListener()->setEnabled(true);
	}
}

void Tutorial::showHitboxes() {
	player->getHitbox().getNode()->setVisible(true);
	bathroomMirror->getHitbox().getNode()->setVisible(true);
	for(g3nts::PrimitiveRect wall : walls) wall.getNode()->setVisible(true);
	for(g3nts::Item* item : items) item->getHitbox().getNode()->setVisible(true);
}
