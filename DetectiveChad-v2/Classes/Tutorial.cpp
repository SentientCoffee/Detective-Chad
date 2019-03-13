#include "Tutorial.h"
#include "GameOver.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* Tutorial::createScene() { return Tutorial::create(); }

void Tutorial::onEnter() { Scene::onEnter(); }

bool Tutorial::init() {
	if (!Scene::init()) return false;

	camera = this->getDefaultCamera();
	gamePaused = false;
	gameOver = false;
	
	totalItems = 0u;
	itemsCollected = 0u;
	levelScale = 1.35f;
	UI_Scale = 0.5f;

	initDirector();
	initSpriteCache();

	initPlayer();
	initItems();
	initLevel();
	initWalls();

	initUI();
	initTextboxes();
	initPauseMenu();

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
	//playerPosition = Vec2(1800, 760) * levelScale;
	camera->setPosition(playerPosition);

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

	player->addAnimation("flex", "chad/flex/%02d.png", 8);

	player->addToScene(this, 2);
}

void Tutorial::initLevel() {
	Vec2 offset = { -527, -513 };

	// Floor plan sprite
	houseBase = Sprite::create("backgrounds/chad-house-base.png");
	houseBase->setScale(levelScale);
	houseBase->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	houseBase->setPosition(Vec2(offset.x, offset.y) * levelScale);

	// Upper walls sprite
	upperWalls = Sprite::create("backgrounds/chad-house-walls-upper.png");
	upperWalls->setScale(levelScale);
	upperWalls->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	upperWalls->setPosition(Vec2(offset.x, offset.y) * levelScale);

	// Middle walls sprite
	middleWalls = Sprite::create("backgrounds/chad-house-walls-middle.png");
	middleWalls->setScale(levelScale);
	middleWalls->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	middleWalls->setPosition(Vec2(offset.x, offset.y) * levelScale);

	// Lower walls sprite
	lowerWalls = Sprite::create("backgrounds/chad-house-walls-lower.png");
	lowerWalls->setScale(levelScale);
	lowerWalls->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	lowerWalls->setPosition(Vec2(offset.x, offset.y) * levelScale);

	this->addChild(houseBase, -1000);
	this->addChild(upperWalls, 10);
	this->addChild(middleWalls, 20);
	this->addChild(lowerWalls, 30);
}

void Tutorial::initItems() {

	g3nts::Item* shirtTemplate;
	g3nts::Item* magGlassTemplate;

	shirtTemplate = new g3nts::Item(Vec2(0, 0), spriteCache->getSpriteFrameByName("items/shirt.png"), true, "shirt");
	magGlassTemplate = new g3nts::Item(Vec2(0, 0), spriteCache->getSpriteFrameByName("items/evidence.png"), true, "evidence");
	
	itemTemps.push_back(shirtTemplate);
	itemTemps.push_back(magGlassTemplate);

	g3nts::Item* shirt_1 = new g3nts::Item(*shirtTemplate);
	g3nts::Item* shirt_2 = new g3nts::Item(*shirtTemplate);
	g3nts::Item* shirt_3 = new g3nts::Item(*shirtTemplate);
	
	g3nts::Item* magGlass_1 = new g3nts::Item(*magGlassTemplate);
	g3nts::Item* magGlass_2 = new g3nts::Item(*magGlassTemplate);
	
	shirt_1->setPosition(Vec2(120, 720) * levelScale);
	shirt_2->setPosition(Vec2(1050, 680) * levelScale);
	shirt_3->setPosition(Vec2(620 , 290) * levelScale);

	magGlass_1->setPosition(Vec2(690, 420) * levelScale);
	magGlass_2->setPosition(Vec2(720, 180) * levelScale);

	items.push_back(shirt_1);
	items.push_back(shirt_2);
	items.push_back(shirt_3);

	items.push_back(magGlass_1);
	items.push_back(magGlass_2);

	totalItems = items.size();

	for (g3nts::Item* item : items) {
		item->addToScene(this);
	}

	bathroomMirror = new g3nts::Mirror(Vec2(170, 800) * levelScale, spriteCache->getSpriteFrameByName("items/mirror.png"));
	bathroomMirror->addToScene(this, 3);

	flexMobile = new g3nts::Item(Vec2(1550, 460) * levelScale, "items/flexmobile.png");
	//flexMobile->addAnimation();
	flexMobile->getSprite()->setScale(2.0f);
	flexMobile->addToScene(this, 3);
}

void Tutorial::initWalls() {
	Vec2 bottomLeft = { -300, -300 }, topRight = { 1550, 1280 };

	// Level boundaries to make sure the player does not leave the level
	upperBoundary = g3nts::PrimitiveRect(Vec2(bottomLeft.x, topRight.y) * levelScale, Vec2(topRight.x, topRight.y) * levelScale);
	lowerBoundary = g3nts::PrimitiveRect(Vec2(bottomLeft.x, bottomLeft.y) * levelScale, Vec2(topRight.x, bottomLeft.y) * levelScale);
	leftBoundary = g3nts::PrimitiveRect(Vec2(bottomLeft.x, bottomLeft.y) * levelScale, Vec2(bottomLeft.x, topRight.y) * levelScale);
	rightBoundary = g3nts::PrimitiveRect(Vec2(topRight.x, bottomLeft.y) * levelScale, Vec2(topRight.x, topRight.y) * levelScale);

	// Outer house walls
	upperHouseWall = g3nts::PrimitiveRect(Vec2(0, 850) * levelScale, Vec2(1250, 766) * levelScale);
	lowerHouseWall = g3nts::PrimitiveRect(Vec2(0, 0) * levelScale, Vec2(1250, 0) * levelScale);
	leftHouseWall = g3nts::PrimitiveRect(Vec2(-30, 0) * levelScale, Vec2(0, 850) * levelScale);
	rightHouseWall_1 = g3nts::PrimitiveRect(Vec2(1250, 0) * levelScale, Vec2(1280, 382) * levelScale);
	rightHouseWall_2 = g3nts::PrimitiveRect(Vec2(1250, 524) * levelScale, Vec2(1280, 850) * levelScale);

	// Inner horizontal house walls
	bathroomDoorway_1 = g3nts::PrimitiveRect(Vec2(0, 594) * levelScale, Vec2(48, 524) * levelScale);
	bathroomDoorway_2 = g3nts::PrimitiveRect(Vec2(179, 594) * levelScale, Vec2(817, 524) * levelScale);
	bedroomDoorway = g3nts::PrimitiveRect(Vec2(947, 594) * levelScale, Vec2(1250, 524) * levelScale);
	livingRoomDoorway_1 = g3nts::PrimitiveRect(Vec2(0, 340) * levelScale, Vec2(48, 270) * levelScale);
	livingRoomDoorway_2 = g3nts::PrimitiveRect(Vec2(179, 340) * levelScale, Vec2(994, 270) * levelScale);

	// Inner vertical house walls
	verticalBathroomWall = g3nts::PrimitiveRect(Vec2(354, 594) * levelScale, Vec2(384, 850) * levelScale);
	vecticalLivingRoomWall_1 = g3nts::PrimitiveRect(Vec2(994, 270) * levelScale, Vec2(1024, 524) * levelScale);
	vecticalLivingRoomWall_2 = g3nts::PrimitiveRect(Vec2(994, 0) * levelScale, Vec2(1024, 128) * levelScale);

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
		this->addChild(wall.getNode(), 100);
		wall.getNode()->setVisible(false);
	}
}

void Tutorial::initPauseMenu() {

	Label* pausedLabel = Label::createWithTTF("PAUSED", "fonts/Marker Felt.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* resumeLabel = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* exitLabel = Label::createWithTTF("Back to Main Menu", "fonts/Marker Felt.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	pausedLabel->enableShadow();
	resumeLabel->enableShadow();
	exitLabel->enableShadow();

	MenuItemLabel* pausedItem = MenuItemLabel::create(pausedLabel);
	MenuItemLabel* resumeButton = MenuItemLabel::create(resumeLabel, [&](Ref* sender) {
		togglePause();
	});
	MenuItemLabel* exitButton = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
		togglePause();
		Scene* mainMenuScene = MainMenu::createScene();
		director->replaceScene(TransitionFade::create(2, mainMenuScene));
	});
	
	pausedItem->setPosition(0, windowSize.y * 0.35);
	resumeButton->setPosition(0, -(windowSize.y * 0.25));
	exitButton->setPosition(0, -(windowSize.y * 0.35));
	
	pauseMenu = Menu::create(pausedItem, resumeButton, exitButton, NULL);
	this->addChild(pauseMenu, 1000);
	pauseMenu->setVisible(false);
}

void Tutorial::initTextboxes() {
	pickupCommandTextbox = new g3nts::Textbox(Vec2::ZERO, "Pick up: L", "fonts/Marker Felt.ttf", 24, Color4F(0.0f, 0.0f, 0.0f, 1.0f), Color4F(1.0f, 1.0f, 1.0f, 0.8f));
	flexCommandTextbox = new g3nts::Textbox(Vec2::ZERO, "Flex: Space", "fonts/Marker Felt.ttf", 24, Color4F(1.0f, 1.0f, 1.0f, 1.0f), Color4F(0.0f, 0.0f, 0.0f, 1.0f));

	pickupCommandTextbox->addToScene(this, 100);
	flexCommandTextbox->addToScene(this, 100);

	pickupCommandTextbox->setVisible(false);
	flexCommandTextbox->setVisible(false);
}

void Tutorial::initUI() {
	// UI flexing meter
	flex_meter = ProgressTimer::create(Sprite::create("ui/flexing.png"));
	flex_meter->setScale(UI_Scale);
	flex_meter->setType(ProgressTimer::Type::BAR);
	flex_meter->setMidpoint(Vec2(0, 0.5f));
	flex_meter->setBarChangeRate(Vec2(1, 0));
	flex_meter->setPercentage(100);

	flex_bg = Sprite::create("ui/flexing-transparent.png");
	flex_bg->setScale(UI_Scale);

	// UI unflexed meter
	unflex_meter = ProgressTimer::create(Sprite::create("ui/unflex.png"));
	unflex_meter->setScale(UI_Scale);
	unflex_meter->setType(ProgressTimer::Type::BAR);
	unflex_meter->setMidpoint(Vec2(0, 0.5f));
	unflex_meter->setBarChangeRate(Vec2(1, 0));
	unflex_meter->setPercentage(100);

	unflex_bg = Sprite::create("ui/unflex-transparent.png");
	unflex_bg->setScale(UI_Scale);

	// UI inventory
	inventory_bg = Sprite::create("ui/inventory.png");
	inventory_bg->setPosition(camera->getPosition() + Vec2(visibleSize.width / 2 - inventory_bg->getContentSize().width / 2 * UI_Scale, inventory_bg->getContentSize().height * UI_Scale / 2));
	inventory_bg->setScale(UI_Scale);

	for (g3nts::Item* temp : itemTemps) {
		inventory_state[temp->getTag()] = false;
	}

	for (unsigned int i = 0; i < totalItems; ++i)
	{
		evidence.push_back(Sprite::create("ui/evidence-default.png"));
		evidence[i]->setScale(UI_Scale);

		broken_evidence.push_back(Sprite::create("ui/evidence-broken.png"));
		broken_evidence[i]->setScale(UI_Scale);
		broken_evidence[i]->setVisible(false);

		collected_evidence.push_back(Sprite::create("ui/evidence-collected.png"));
		collected_evidence[i]->setScale(UI_Scale);
		collected_evidence[i]->setVisible(false);

		evidence_state.push_back(true);
	}

	// Adding UI to scene
	this->addChild(flex_bg, 1000);
	this->addChild(flex_meter, 1001);
	this->addChild(unflex_bg, 1000);
	this->addChild(unflex_meter, 1001);

	for (unsigned int i = 0; i < totalItems; ++i)
	{
		this->addChild(evidence[i], 1000);
		this->addChild(broken_evidence[i], 1000);
		this->addChild(collected_evidence[i], 1000);
	}

	this->addChild(inventory_bg, 1000);

	flex_bg->setVisible(false);
}

void Tutorial::initKeyboardListener() {
	keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		keyboard.keyDown[(int)key] = true;
	};

	keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		keyboard.keyDown[(int)key] = false;

		if (key == EventKeyboard::KeyCode::KEY_ESCAPE) {
			if (!gameOver) togglePause();
		}
		else if (key == EventKeyboard::KeyCode::KEY_SPACE) {
			if (!gameOver) {
				if (bathroomMirror->getPosition().getDistanceSq(player->getPosition()) <= 200 * 200) {
					if (!player->isFlexing()) {
						player->setFlexing(true);
					}

					for (g3nts::Item* item : items) {
						if (item->getPosition().getDistanceSq(player->getPosition()) <= 250 * 250) {
							if (item->isBreakable()) {
								item->getSprite()->setSpriteFrame(spriteCache->getSpriteFrameByName("items/broken-" + item->getTag() + ".png"));
								item->setBreakable(false);

								for (unsigned int i = 0; i < evidence_state.size(); ++i) {
									if (evidence_state[i]) {
										evidence_state[i] = false;
										break;
									}
								}
							}

							Vec2 direction = item->getPosition() - player->getPosition();
							item->setVelocity(direction.getNormalized() * 1000.0f);
						}
					}

					if (!bathroomMirror->isBroken()) {
						bathroomMirror->setBroken(true);
						bathroomMirror->getSprite()->setSpriteFrame(spriteCache->getSpriteFrameByName("items/broken-mirror.png"));
					}
				}
			}
		}
		else if (key == EventKeyboard::KeyCode::KEY_L) {
			if (!gameOver) {
				if (inventory.size() < 1) {
					for (g3nts::Item* item : items) {
						if (g3nts::isColliding(player->getHitbox(), item->getHitbox())) {
							inventory.push_back(item);
							item->setZIndex(1001);
							inventory_state[item->getTag()] = true;
							items.erase(std::find(items.begin(), items.end(), item));
							break;
						}
					}
				}
				else if (inventory.size() > 0) {
					inventory[0]->setPosition(player->getPosition());
					inventory[0]->setVelocity(player->getDirection().getNormalized() * 2000.0f);
					inventory_state[inventory[0]->getTag()] = false;
					items.push_back(inventory[0]);
					inventory.erase(inventory.begin());
				}
			}
		}
	};

	for (unsigned int i = 0; i < 256; ++i) {
		keyboard.keyDown[i] = false;
	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Tutorial::update(const float dt) {

	// CAMERA MOVEMENT (Camera follows the player)
	if (player->isFlexing())
	{
		screenshake();
	}
	else
	{
		this->getDefaultCamera()->setRotation(0);
		//camera->setPosition(player->getPosition());
		if (player->getPosition().x >= 145 * levelScale && player->getPosition().x <= 1200 * levelScale) {
			camera->setPositionX(player->getPosition().x);
		}
		if (player->getPosition().y >= 35 * levelScale && player->getPosition().y <= 950 * levelScale) {
			camera->setPositionY(player->getPosition().y);
		}
	}

	// UI MOVEMENT (UI follows camera)
	flexRefillTimer -= dt;
	if (player->isFlexing()) flexRefillTimer = 0.4f;

	if (flexRefillTimer > 0)
	{
		flex_meter->setVisible(true);
		flex_bg->setVisible(true);

		if (flex_meter->getNumberOfRunningActionsByTag('UI') == 0) {
			flex_meter->stopAllActionsByTag('UI');
			ProgressFromTo* flexProgress = ProgressFromTo::create(0.4f, unflex_meter->getPercentage(), 100);
			DelayTime* UIdelay = DelayTime::create(1.5f);

			Sequence* UIseq = Sequence::create(flexProgress, UIdelay, NULL);
			UIseq->setTag('UI');
			flex_meter->runAction(UIseq);
		}

		unflex_meter->stopAllActionsByTag('UI');
		unflex_meter->setPercentage(100);
		unflex_meter->setVisible(false);
		unflex_bg->setVisible(false);
	}
	else
	{
		unflex_meter->setVisible(true);
		unflex_bg->setVisible(true);

		if (unflex_meter->getNumberOfRunningActionsByTag('UI') == 0) {
			ProgressTo* unflexProgress = ProgressTo::create(45.0f, 0);
			unflexProgress->setTag('UI');
			unflex_meter->runAction(unflexProgress);
		}

		flex_meter->setVisible(false);
		flex_bg->setVisible(false);
	}

	flex_meter->setPosition(camera->getPosition() + Vec2(-visibleSize.width / 2 + unflex_bg->getContentSize().width / 2 * UI_Scale - 40, visibleSize.height / 2 - flex_bg->getContentSize().height * UI_Scale / 2 - 5));
	flex_bg->setPosition(camera->getPosition() + Vec2(-visibleSize.width / 2 + unflex_bg->getContentSize().width / 2 * UI_Scale - 40, visibleSize.height / 2 - flex_bg->getContentSize().height * UI_Scale / 2 - 5));
	unflex_meter->setPosition(camera->getPosition() + Vec2(-visibleSize.width / 2 + unflex_bg->getContentSize().width / 2 * UI_Scale + 5, visibleSize.height / 2 - flex_bg->getContentSize().height * UI_Scale / 2));
	unflex_bg->setPosition(camera->getPosition() + Vec2(-visibleSize.width / 2 + unflex_bg->getContentSize().width / 2 * UI_Scale + 5, visibleSize.height / 2 - flex_bg->getContentSize().height * UI_Scale / 2));

	for (unsigned int i = 0; i < itemsCollected; ++i) {
		collected_evidence[i]->setPosition(camera->getPosition() + Vec2(20 + visibleSize.width / 2 - (totalItems - i) * (collected_evidence[i]->getContentSize().width * UI_Scale), visibleSize.height / 2 - (evidence[i]->getContentSize().height * UI_Scale / 2) - 20));
		collected_evidence[i]->setVisible(true);
	}

	for (unsigned int i = 0; i < evidence.size(); ++i)
	{
		evidence[i]->setPosition(camera->getPosition() + Vec2(20 + visibleSize.width / 2 - (i + 1) * (evidence[i]->getContentSize().width * UI_Scale), visibleSize.height / 2 - (evidence[i]->getContentSize().height * UI_Scale / 2) - 20));
		broken_evidence[i]->setPosition(camera->getPosition() + Vec2(20 + visibleSize.width / 2 - (i + 1) * (evidence[i]->getContentSize().width * UI_Scale), visibleSize.height / 2 - (evidence[i]->getContentSize().height * UI_Scale / 2) - 20));
		if (evidence_state[i])
		{
			evidence[i]->setVisible(true);
			broken_evidence[i]->setVisible(false);
		}
		else
		{
			evidence[i]->setVisible(false);
			broken_evidence[i]->setVisible(true);
		}
	}

	if (totalItems - itemsCollected < totalItems && totalItems - itemsCollected > 0) {
		for (int i = totalItems - 1; i >= totalItems - itemsCollected; --i) {
			evidence[i]->setVisible(false);
			broken_evidence[i]->setVisible(false);
		}
	}

	broken = 0;
	for (bool state : evidence_state) {
		if (!state) broken++;
	}

	if (broken >= 3 || unflex_meter->getPercentage() == 0) {
		gameOver = true;
	}
	
	inventory_bg->setPosition(camera->getPosition() + Vec2(visibleSize.width / 2 - inventory_bg->getContentSize().width / 2 * UI_Scale, inventory_bg->getContentSize().height * UI_Scale / 2));
	for (g3nts::Item* inv : inventory) {
		inv->setPosition(inventory_bg->getPosition());
		inv->setVisible(inventory_state[inv->getTag()]);
	}

	if (gameOver) {
		this->unscheduleUpdate();
		Scene* gameOverScene = GameOver::createScene();
		director->replaceScene(TransitionFade::create(2, gameOverScene));
	}
	else {
		// Update the player
		player->update(dt);

		// Update player sprite to be on top or behind walls
		player->setZIndex(25);
		lowerWalls->setOpacity(255 * 0.25);
		middleWalls->setOpacity(255);
		upperWalls->setOpacity(255);


		if (player->getPosition().y > livingRoomDoorway_1.getEndPosition().y + 35) {
			player->setZIndex(15);
			lowerWalls->setOpacity(255);
			middleWalls->setOpacity(255 * 0.25);
		}
		if (player->getPosition().y > bedroomDoorway.getEndPosition().y + 35) {
			player->setZIndex(5);
			middleWalls->setOpacity(255);
			upperWalls->setOpacity(255 * 0.25);
		}

		showPickupCommand = false;
		for (g3nts::Item* item : items) {
			// Update all items in the scene
			item->update(dt);

			item->setZIndex(24);
			if (item->getPosition().y > livingRoomDoorway_1.getEndPosition().y + item->getHitbox().getHeight() / 2.0f - 10) item->setZIndex(14);
			if (item->getPosition().y > bedroomDoorway.getEndPosition().y + item->getHitbox().getHeight() / 2.0f - 10)  item->setZIndex(4);

			// Check item collision with player
			if (g3nts::isColliding(player->getHitbox(), item->getHitbox())) {
				if (player->getZIndex() == item->getZIndex() + 1) {
					showPickupCommand = true;

					//Vec2 direction = player->getDirection() + item->getPosition() - player->getPosition();
					//if (item->getVelocity().getLengthSq() <= 50 * 50)
					//	item->setVelocity(direction.getNormalized() * 500.0f);
					//else {
					//	if (player->getDirection().getLengthSq() == 0) {
					//		item->setVelocity((item->getVelocity() + direction).getNormalized() * item->getVelocity().getLength() * 0.4f);
					//	}
					//	else {
					//		item->setVelocity(direction.getNormalized() * 200.0f);
					//	}
					//}
				}
			}

			if (g3nts::isColliding(item->getHitbox(), flexMobile->getHitbox())) {
				itemsCollected++;
				item->setVisible(false);
				items.erase(std::find(items.begin(), items.end(), item));
			}
		}

		for (g3nts::PrimitiveRect wall : walls) {

			// Check player collision with walls
			if (g3nts::isColliding(player->getHitbox(), wall) && player->getDirection().getLengthSq() != 0) {
				player->update(-dt);
			//	if (wall.getWidth() <= 50) {
			//		player->setDirection(Vec2(-player->getDirection().x, player->getDirection().y));
			//	}
			//	else if (wall.getHeight() <= 50) {
			//		player->setDirection(Vec2(player->getDirection().x, -player->getDirection().y));
			//	}
			}

			// Check item collision with walls
			for (g3nts::Item* item : items) {
				if (g3nts::isColliding(item->getHitbox(), wall)) {
					if (wall.getWidth() <= 50) {
						item->setVelocity(Vec2(-item->getVelocity().x, item->getVelocity().y));
					}
					else if (wall.getHeight() <= 50) {
						item->setVelocity(Vec2(item->getVelocity().x, -item->getVelocity().y));
					}
				}
			}
		}
		
		showFlexCommand = false;
		if (bathroomMirror->getPosition().getDistanceSq(player->getPosition()) <= 200 * 200) {
			showFlexCommand = true;
		}

		if (showPickupCommand) {
			pickupCommandTextbox->setPosition(Vec2(player->getPosition().x - 60, player->getPosition().y + 120));
			pickupCommandTextbox->setVisible(true);
		}
		else {
			pickupCommandTextbox->setVisible(false);
		}

		if (showFlexCommand) {
			flexCommandTextbox->setPosition(Vec2(player->getPosition().x + 60, player->getPosition().y + 120));
			flexCommandTextbox->setVisible(true);
		}
		else {
			flexCommandTextbox->setVisible(false);
		}
	}
}

void Tutorial::togglePause() {
	gamePaused = !gamePaused;
	pauseMenu->setPosition(camera->getPosition());

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
	flexMobile->getHitbox().getNode()->setVisible(true);
	for (g3nts::PrimitiveRect wall : walls) wall.getNode()->setVisible(true);
	for (g3nts::Item* item : items) item->getHitbox().getNode()->setVisible(true);
}

void Tutorial::screenshake() {
	Vec2 cameraPos = camera->getPosition();
	for (float radius = 1.0f; radius > 0.0f; radius -= 0.1f)
	{
		camera->setRotation(0);
		camera->setPosition(cameraPos);

		//change values for varying jitter
		float angle = radius * 25 * rand_minus1_1();
		float offsetX = radius * 30 * rand_minus1_1();
		float offsetY = radius * 30 * rand_minus1_1();

		camera->setRotation(angle + camera->getRotation());
		camera->setPosition(camera->getPosition() + Vec2(offsetX, offsetY));
	}
}