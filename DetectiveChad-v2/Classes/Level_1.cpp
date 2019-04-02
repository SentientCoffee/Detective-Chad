#include "Level_1.h"
#include "GameOver.h"
#include "WinScreen.h"
#include "MainMenu.h"
#include "TutorialCutscene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Level1::createScene() { return Level1::create(); }

void Level1::onEnter() { Scene::onEnter(); }

bool Level1::init() {
	if (!Scene::init()) return false;

	camera = this->getDefaultCamera();
	gamePaused = false;
	gameOver = false;
	gameWin = false;
	time = 0;

	totalItems = 0u;
	requiredItems = 1u;
	itemsCollected = 0u;
	levelScale = 0.9f;
	UI_Scale = 0.5f;

	initDirector();
	initSpriteCache();

	initPlayer();
	initItems();
	initLevel();
	initFoW();
	initProps();
	initWalls();

	initUI();
	initTextboxes();
	initPauseMenu();

	initKeyboardListener();

	showHitboxes();

	this->scheduleUpdate();
	return true;
}

void Level1::onExit() { Scene::onExit(); }

void Level1::initDirector() {
	director = Director::getInstance();

	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();
}

void Level1::initSpriteCache() {
	spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("characters/characters.plist");
	spriteCache->addSpriteFramesWithFile("items/items.plist");
}

void Level1::initPlayer() {
	playerPosition = Vec2(1080, 760) * levelScale;
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

	player->addToScene(this, 3);
}

void Level1::initProps() {
	
}

void Level1::initLevel() {
	Vec2 offset = { -1984, -2112 };
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sfx/tutorial.mp3", true);

	// Floor plan sprite
	warehouseBase = Sprite::create("backgrounds/warehouse-base.png");
	warehouseBase->setScale(levelScale);
	warehouseBase->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	warehouseBase->setPosition(Vec2(offset.x, offset.y) * levelScale);

	bottomWall = Sprite::create("backgrounds/warehouse-bottom-wall.png");
	bottomWall->setScale(levelScale);
	bottomWall->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	bottomWall->setPosition(Vec2(offset.x, offset.y) * levelScale);

	securityOfficeWall = Sprite::create("backgrounds/warehouse-security-office-wall.png");
	securityOfficeWall->setScale(levelScale);
	securityOfficeWall->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	securityOfficeWall->setPosition(Vec2(offset.x, offset.y) * levelScale);

	supervisorOfficeWall = Sprite::create("backgrounds/warehouse-supervisor-office-wall.png");
	supervisorOfficeWall->setScale(levelScale);
	supervisorOfficeWall->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	supervisorOfficeWall->setPosition(Vec2(offset.x, offset.y) * levelScale);

	workerAreaUpperWall = Sprite::create("backgrounds/warehouse-wroker-area-top-wall.png");
	workerAreaUpperWall->setScale(levelScale);
	workerAreaUpperWall->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	workerAreaUpperWall->setPosition(Vec2(offset.x, offset.y) * levelScale);

	workerAreaMiddleWall = Sprite::create("backgrounds/warehouse-wroker-area-middle-wall.png");
	workerAreaMiddleWall->setScale(levelScale);
	workerAreaMiddleWall->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	workerAreaMiddleWall->setPosition(Vec2(offset.x, offset.y) * levelScale);

	workerAreaLowerWall = Sprite::create("backgrounds/warehouse-wroker-area-bottom-wall.png");
	workerAreaLowerWall->setScale(levelScale);
	workerAreaLowerWall->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	workerAreaLowerWall->setPosition(Vec2(offset.x, offset.y) * levelScale);

	redContainerTop = Sprite::create("backgrounds/warehouse-red-top-wall.png");
	redContainerTop->setScale(levelScale);
	redContainerTop->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	redContainerTop->setPosition(Vec2(offset.x, offset.y) * levelScale);

	redContainerBottom = Sprite::create("backgrounds/warehouse-red-bottom-wall.png");
	redContainerBottom->setScale(levelScale);
	redContainerBottom->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	redContainerBottom->setPosition(Vec2(offset.x, offset.y) * levelScale);

	greenContainerTop = Sprite::create("backgrounds/warehouse-green-top-wall.png");
	greenContainerTop->setScale(levelScale);
	greenContainerTop->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	greenContainerTop->setPosition(Vec2(offset.x, offset.y) * levelScale);

	greenContainerBottom = Sprite::create("backgrounds/warehouse-green-bottom-wall.png");
	greenContainerBottom->setScale(levelScale);
	greenContainerBottom->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	greenContainerBottom->setPosition(Vec2(offset.x, offset.y) * levelScale);

	purpleContainerTop = Sprite::create("backgrounds/warehouse-purple-top-wall.png");
	purpleContainerTop->setScale(levelScale);
	purpleContainerTop->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	purpleContainerTop->setPosition(Vec2(offset.x, offset.y) * levelScale);

	purpleContainerBottom = Sprite::create("backgrounds/warehouse-purple-bottom-wall.png");
	purpleContainerBottom->setScale(levelScale);
	purpleContainerBottom->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	purpleContainerBottom->setPosition(Vec2(offset.x, offset.y) * levelScale);

	pinkContainer = Sprite::create("backgrounds/warehouse-pink-wall.png");
	pinkContainer->setScale(levelScale);
	pinkContainer->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	pinkContainer->setPosition(Vec2(offset.x, offset.y) * levelScale);

	surroundingCrates = Sprite::create("backgrounds/warehouse-surrounding-crates.png");
	surroundingCrates->setScale(levelScale);
	surroundingCrates->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	surroundingCrates->setPosition(Vec2(offset.x, offset.y) * levelScale);

	extraCrates = Sprite::create("backgrounds/warehouse-extra-crates.png");
	extraCrates->setScale(levelScale);
	extraCrates->setAnchorPoint(Vec2(0, 0));   // THIS IS IMPORTANT TO MAKE SURE THE WALL HITBOXES SCALE WITH THE LEVEL BACKGROUND!!!
	extraCrates->setPosition(Vec2(offset.x, offset.y) * levelScale);

	this->addChild(warehouseBase, -1000);
	this->addChild(bottomWall, -999);

	this->addChild(securityOfficeWall, -998);
	this->addChild(supervisorOfficeWall, -997);

	this->addChild(workerAreaUpperWall, -996);
	this->addChild(workerAreaMiddleWall, -995);
	this->addChild(workerAreaLowerWall, -994);

	this->addChild(redContainerTop, -993);
	this->addChild(redContainerBottom, -992);
	this->addChild(greenContainerTop, -991);
	this->addChild(greenContainerBottom, -990);
	this->addChild(purpleContainerTop, -989);
	this->addChild(purpleContainerBottom, -988);
	this->addChild(pinkContainer, -987);

	this->addChild(surroundingCrates,-986);
	this->addChild(extraCrates,-989);
}

void Level1::initItems() {
	g3nts::Item* boltCutterTemplate = new g3nts::Item(Vec2::ZERO, spriteCache->getSpriteFrameByName("items/evidence/shirt.png"), true, "boltcutters");
	g3nts::Item* cdTemplate = new g3nts::Item(Vec2::ZERO, spriteCache->getSpriteFrameByName("items/evidence/evidence.png"), true, "cd");
	g3nts::Item* knifeTemplate = new g3nts::Item(Vec2::ZERO, spriteCache->getSpriteFrameByName("items/evidence/evidence.png"), true, "knife");
	g3nts::Item* manifestTemplate = new g3nts::Item(Vec2::ZERO, spriteCache->getSpriteFrameByName("items/evidence/evidence.png"), true, "manifest");

	g3nts::Item* boltcutters = new g3nts::Item(*boltCutterTemplate);
	g3nts::Item* securityCD = new g3nts::Item(*cdTemplate);
	g3nts::Item* bloodyKnife = new g3nts::Item(*knifeTemplate);
	g3nts::Item* shippingManifest = new g3nts::Item(*manifestTemplate);

	boltcutters->setPosition(Vec2(120, 720) * levelScale);
	securityCD->setPosition(Vec2(150, 710) * levelScale);
	bloodyKnife->setPosition(Vec2(620, 150) * levelScale);
	shippingManifest->setPosition(Vec2(690, 170) * levelScale);

	items.push_back(boltcutters);
	items.push_back(securityCD);
	items.push_back(bloodyKnife);
	items.push_back(shippingManifest);

	totalItems = items.size();

	for (g3nts::Item* item : items) {
		item->addToScene(this);
	}

	flexMobile = new g3nts::Item(Vec2(100, 1750) * levelScale, spriteCache->getSpriteFrameByName("items/flexmobile/dropoff/01.png"));
	flexMobile->getSprite()->setRotation(90);
	flexMobile->addAnimation("dropoff", "items/flexmobile/dropoff/%02d.png", 7);
	flexMobile->addAnimation("levelEnd", "items/flexmobile/level-end/%02d.png", 3);
	flexMobile->addToScene(this, 3);

	flexMobileDrop = g3nts::PrimitiveRect(Vec2(50, 1350) * levelScale, Vec2(150, 1450) * levelScale);
	this->addChild(flexMobileDrop.getNode(), 100);
	flexMobileDrop.getNode()->setVisible(false);

	g3nts::Mirror* mirrorTemplate1 = new g3nts::Mirror(Vec2(0, 0), spriteCache->getSpriteFrameByName("items/mirrors/default-mirror.png"));
	g3nts::Mirror* mirrorTemplate2 = new g3nts::Mirror(Vec2(0, 0), spriteCache->getSpriteFrameByName("items/mirrors/wooden-mirror.png"));

	bathroomMirror = new g3nts::Mirror(*mirrorTemplate1);
	bathroomMirror->setTag("default");
	bathroomMirror->setPosition(Vec2(-1870, 0) * levelScale);
	bathroomMirror->addToScene(this, 3);

	containerMirror = new g3nts::Mirror(*mirrorTemplate2);
	containerMirror->setTag("wooden");
	containerMirror->setPosition(Vec2(-510, 500) * levelScale);
	containerMirror->addToScene(this, 13);
	
	crateMirror = new g3nts::Mirror(*mirrorTemplate2);
	crateMirror->setTag("wooden");
	crateMirror->setPosition(Vec2(875, -550) * levelScale);
	crateMirror->addToScene(this, 13);

	mirrors.push_back(bathroomMirror); mirrors.push_back(containerMirror); mirrors.push_back(crateMirror);
}

void Level1::initWalls() {
	Vec2 bottomLeft = { -1984, -1700 }, topRight = { 1984, 2000 };

	// Level boundaries to make sure the player does not leave the level
	upperBoundary = g3nts::PrimitiveRect(Vec2(bottomLeft.x, topRight.y) * levelScale, Vec2(topRight.x, topRight.y) * levelScale);
	lowerBoundary = g3nts::PrimitiveRect(Vec2(bottomLeft.x, bottomLeft.y) * levelScale, Vec2(topRight.x, bottomLeft.y) * levelScale);
	leftBoundary = g3nts::PrimitiveRect(Vec2(bottomLeft.x, bottomLeft.y) * levelScale, Vec2(bottomLeft.x, topRight.y) * levelScale);
	rightBoundary = g3nts::PrimitiveRect(Vec2(topRight.x, bottomLeft.y) * levelScale, Vec2(topRight.x, topRight.y) * levelScale);

	
	// Add all the walls to the walls vector
	playerWalls.push_back(upperBoundary); playerWalls.push_back(lowerBoundary);
	playerWalls.push_back(leftBoundary);  playerWalls.push_back(rightBoundary);

	// Add all the walls to the scene
	for (g3nts::PrimitiveRect wall : playerWalls) {
		this->addChild(wall.getNode(), 100);
		wall.getNode()->setVisible(false);
	}

	for (g3nts::PrimitiveRect wall : itemWalls) {
		this->addChild(wall.getNode(), 100);
		wall.getNode()->setVisible(false);
	}
}

void Level1::initFoW() {

}

void Level1::initPauseMenu() {

	Label* pausedLabel = Label::createWithTTF("PAUSED", "fonts/GillSansUltraBold.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* resumeLabel = Label::createWithTTF("Resume", "fonts/GillSansUltraBold.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* exitLabel = Label::createWithTTF("Back to Main Menu", "fonts/GillSansUltraBold.ttf", 36, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
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

void Level1::initTextboxes() {
	pickupCommandTextbox = new g3nts::Textbox(Vec2::ZERO, "Pick up: L", "fonts/GillSansUltraBold.ttf", 16, Color4F(0.0f, 0.0f, 0.0f, 1.0f), Color4F(1.0f, 1.0f, 1.0f, 0.8f));
	dropCommandTextbox = new g3nts::Textbox(Vec2::ZERO, "Drop: L", "fonts/GillSansUltraBold.ttf", 16, Color4F(0.0f, 0.0f, 0.0f, 1.0f), Color4F(1.0f, 1.0f, 1.0f, 0.8f));
	flexCommandTextbox = new g3nts::Textbox(Vec2::ZERO, "Flex: Space", "fonts/GillSansUltraBold.ttf", 16, Color4F(1.0f, 1.0f, 1.0f, 1.0f), Color4F(0.0f, 0.0f, 0.0f, 1.0f));
	exitCommandTextbox = new g3nts::Textbox(Vec2::ZERO, "Exit: Space", "fonts/GillSansUltraBold.ttf", 16, Color4F(1.0f, 1.0f, 1.0f, 1.0f), Color4F(0.0f, 0.0f, 0.0f, 1.0f));

	pickupCommandTextbox->addToScene(this, 100);
	dropCommandTextbox->addToScene(this, 100);
	flexCommandTextbox->addToScene(this, 100);
	exitCommandTextbox->addToScene(this, 100);

	pickupCommandTextbox->setVisible(false);
	dropCommandTextbox->setVisible(false);
	flexCommandTextbox->setVisible(false);
	exitCommandTextbox->setVisible(false);
}

void Level1::initUI() {
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
	unflex_meter->setPercentage(50);

	unflex_bg = Sprite::create("ui/unflex-transparent.png");
	unflex_bg->setScale(UI_Scale);

	// UI inventory
	inventory_bg = Sprite::create("ui/inventory.png");
	inventory_bg->setPosition(camera->getPosition() + Vec2(visibleSize.width / 2 - inventory_bg->getContentSize().width / 2 * UI_Scale, inventory_bg->getContentSize().height * UI_Scale / 2));
	inventory_bg->setScale(UI_Scale);

	for (unsigned int i = 0; i < totalItems; ++i)
	{
		if (i >= totalItems - requiredItems) {
			evidence.push_back(Sprite::create("ui/evidence-default.png"));
		}
		else {
			evidence.push_back(Sprite::create("ui/evidence-extra.png"));
		}

		evidence[i]->setScale(UI_Scale);
		broken_evidence.push_back(Sprite::create("ui/evidence-broken.png"));
		broken_evidence[i]->setScale(UI_Scale);
		broken_evidence[i]->setVisible(false);

		evidence_state.push_back(true);
	}

	for (unsigned int i = 0; i < totalItems; ++i) {
		if (i < requiredItems) {
			collected_evidence.push_back(Sprite::create("ui/evidence-default-collected.png"));
		}
		else {
			collected_evidence.push_back(Sprite::create("ui/evidence-extra-collected.png"));
		}
		collected_evidence[i]->setScale(UI_Scale);
		collected_evidence[i]->setVisible(false);
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

	ProgressTo* unflexProgress = ProgressTo::create(60.0f, 0);
	unflexProgress->setTag('UI');
	unflex_meter->runAction(unflexProgress);
}


void Level1::initKeyboardListener() {
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
				if (gameWin && g3nts::isColliding(player->getHitbox(), flexMobileDrop) && inventory.size() < 1)
				{
					this->unscheduleUpdate();

					player->getSprite()->setVisible(false);
					flexMobile->runAnimation("levelEnd");

					MoveTo* move = MoveTo::create(2.0f, Vec3(flexMobile->getPosition().x, 1200, 0));
					flexMobile->getSprite()->runAction(move);

					if ((300 - floorf(time)) > 0) tScore += (300 - floorf(time));
					else tScore = 0;

					for (g3nts::Mirror* mirror : mirrors) {
						if (!mirror->isBroken()) mScore += 3000;
					}

					if (itemsCollected >= requiredItems) eScore += 1500;
					if (itemsCollected > requiredItems) aScore += ((totalItems - requiredItems) * 2500);

					sScore = tScore + mScore + eScore + aScore;

					if (sScore >= 10000) rScore = "A";
					else if (sScore >= 8000) rScore = "B";
					else if (sScore >= 6000) rScore = "C";
					else rScore = "D";

					Scene* gameWinScene = WinScreen::createScene(mScore, eScore, tScore, aScore, sScore, rScore, levelID);
					director->replaceScene(gameWinScene);
				}

				for (g3nts::Mirror* mirror : mirrors) {
					if (mirror->getPosition().getDistanceSq(player->getPosition()) <= 200 * 200) {
						if (!player->isFlexing()) {
							player->setFlexing(true);
						}

						if (!mirror->isBroken()) {
							mirror->setBroken(true);
							mirror->getSprite()->setSpriteFrame(spriteCache->getSpriteFrameByName("items/mirrors/broken-" + mirror->getTag() + "-mirror.png"));
							SimpleAudioEngine::getInstance()->playEffect("sfx/Glass_Shatter.mp3");
						}

						for (g3nts::Item* item : items) {
							if (item->getPosition().getDistanceSq(player->getPosition()) <= 250 * 250) {
								if (item->isBreakable()) {
									item->getSprite()->setSpriteFrame(spriteCache->getSpriteFrameByName("items/evidence/broken-" + item->getTag() + ".png"));
									item->setBreakable(false);
									SimpleAudioEngine::getInstance()->playEffect("sfx/evidence_break.mp3");

									for (unsigned int i = 0; i < evidence_state.size(); ++i) {
										if (evidence_state[i]) {
											evidence_state[i] = false;
											break;
										}
									}
								}

								Vec2 direction = item->getPosition() - player->getPosition();
								item->setVelocity(direction.getNormalized() * 2500.0f);
							}
						}

						for (g3nts::Item* inv : inventory) {
							if (inv->isBreakable()) {
								inv->getSprite()->setSpriteFrame(spriteCache->getSpriteFrameByName("items/evidence/broken-" + inv->getTag() + ".png"));
								inv->setBreakable(false);

								for (unsigned int i = 0; i < evidence_state.size(); ++i) {
									if (evidence_state[i]) {
										evidence_state[i] = false;
										break;
									}
								}

							}

							inv->setPosition(player->getPosition());
							inv->setVelocity(player->getDirection().getNormalized() * 2000.0f);
							items.push_back(inv);
							inventory.erase(std::find(inventory.begin(), inventory.end(), inv));
						}
					}
				}
			}
		}
		else if (key == EventKeyboard::KeyCode::KEY_L) {
			if (!gameOver) {
				if (inventory.size() < 1) {
					for (g3nts::Item* item : items) {
						if (item->isBreakable()) {
							if (g3nts::isColliding(player->getHitbox(), item->getHitbox())) {
								inventory.push_back(item);
								item->setZIndex(1001);
								items.erase(std::find(items.begin(), items.end(), item));
								break;
							}
						}
					}
				}
				else if (inventory.size() > 0) {
					if (g3nts::isColliding(player->getHitbox(), flexMobileDrop)) {
						itemsCollected++;
						inventory[0]->setVisible(false);
						flexMobile->runAnimation("dropoff");
						SimpleAudioEngine::getInstance()->playEffect("sfx/Object_in_Car.mp3");
					}
					else {
						inventory[0]->setPosition(player->getPosition());
						inventory[0]->setVelocity(player->getDirection().getNormalized() * 2000.0f);
						items.push_back(inventory[0]);
					}
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

void Level1::update(const float dt) {
	time += dt;
	// CAMERA MOVEMENT (Camera follows the player)
	if (player->isFlexing())
	{
		screenshake();
	}
	else
	{
		this->getDefaultCamera()->setRotation(0);
		if (player->getPosition().x >= -1185 * levelScale && player->getPosition().x <= 1185 * levelScale) {
			camera->setPositionX(player->getPosition().x);
		}
		if (player->getPosition().y >= -1614 * levelScale && player->getPosition().y <= 1630 * levelScale) {
			camera->setPositionY(player->getPosition().y);
		}
	}

	// Fog of War Revealing
	for (unsigned int i = 0; i < FoW.size(); ++i)
	{
		if (player->getPosition().x >= FoW[i].getStartPosition().x &&
			player->getPosition().y >= FoW[i].getStartPosition().y + 25 &&
			player->getPosition().x <= FoW[i].getEndPosition().x &&
			player->getPosition().y <= FoW[i].getEndPosition().y)
		{
			if (sFoW[i].getNode()->getOpacity() > 0)
				FoW[i].getNode()->setOpacity(FoW[i].getNode()->getOpacity() - 5);
			else
			{
				FoW[i].getNode()->setVisible(false);
				sFoW[i].getNode()->setVisible(true);
			}
		}
	}

	for (unsigned int i = 0; i < sFoW.size(); ++i)
	{
		if (player->getPosition().x >= sFoW[i].getStartPosition().x &&
			player->getPosition().y >= sFoW[i].getStartPosition().y + 25 &&
			player->getPosition().x <= sFoW[i].getEndPosition().x &&
			player->getPosition().y <= sFoW[i].getEndPosition().y)
		{
			if (sFoW[i].getNode()->getOpacity() > 0)
				sFoW[i].getNode()->setOpacity(sFoW[i].getNode()->getOpacity() - 5);
			else
				sFoW[i].getNode()->setOpacity(0);
		}
		else
		{
			if (sFoW[i].getNode()->getOpacity() < 255)
				sFoW[i].getNode()->setOpacity(sFoW[i].getNode()->getOpacity() + 5);
			else
				sFoW[i].getNode()->setOpacity(255);
		}
	}

	// UI MOVEMENT (UI follows camera)
	flexRefillTimer -= dt;
	if (player->isFlexing()) flexRefillTimer = 0.5f;

	if (flexRefillTimer > 0)
	{
		flex_meter->setVisible(true);
		flex_bg->setVisible(true);

		if (flex_meter->getNumberOfRunningActionsByTag('UI') == 0) {
			flex_meter->stopAllActionsByTag('UI');
			ProgressFromTo* flexProgress = ProgressFromTo::create(0.5f, unflex_meter->getPercentage(), 100);
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
			ProgressTo* unflexProgress = ProgressTo::create(120.0f * unflex_meter->getPercentage() / 100, 0);
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

	if (broken > totalItems - requiredItems || unflex_meter->getPercentage() == 0) {
		gameOver = true;
	}

	if (itemsCollected >= requiredItems) {
		gameWin = true;
	}

	inventory_bg->setPosition(camera->getPosition() + Vec2(visibleSize.width / 2 - inventory_bg->getContentSize().width / 2 * UI_Scale, inventory_bg->getContentSize().height * UI_Scale / 2));

	for (g3nts::Item* inv : inventory) {
		inv->setPosition(inventory_bg->getPosition());
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
		/*lowerWalls->setOpacity(255 * 0.25);
		middleWalls->setOpacity(255);
		upperWalls->setOpacity(255);*/


		/*if (player->getPosition().y > livingRoomDoorway_1.getEndPosition().y + 35) {
			player->setZIndex(15);
			lowerWalls->setOpacity(255);
			middleWalls->setOpacity(255 * 0.25);
		}
		if (player->getPosition().y > bedroomDoorway.getEndPosition().y + 35) {
			player->setZIndex(5);
			middleWalls->setOpacity(255);
			upperWalls->setOpacity(255 * 0.25);
		}*/

		for (g3nts::PrimitiveRect wall : playerWalls) {
			// Check player collision with walls
			if (g3nts::isColliding(player->getHitbox(), wall) && player->getDirection().getLengthSq() != 0) {
				player->update(-dt);
				//if (wall.getWidth() < wall.getHeight()) {
				//	player->setPosition(player->getPosition() + Vec2(player->getDirection().x, 0) * player->getSpeed() * dt);
				//}
				//else if (wall.getWidth() > wall.getHeight()) {
				//	player->setPosition(player->getPosition() + Vec2(0, player->getDirection().y) * player->getSpeed() * dt);
				//}
			}
		}

		if (g3nts::isColliding(player->getHitbox(), flexMobile->getHitbox())) {
			player->update(-dt);
		}

		showPickupCommand = false;
		for (g3nts::Item* item : items) {
			// Update all items in the scene
			item->update(dt);

			/*item->setZIndex(24);
			if (item->getPosition().y > livingRoomDoorway_1.getEndPosition().y + item->getHitbox().getHeight() / 2.0f - 10) item->setZIndex(14);
			if (item->getPosition().y > bedroomDoorway.getEndPosition().y + item->getHitbox().getHeight() / 2.0f - 10)  item->setZIndex(4);
*/
			// Check item collision with player
			if (g3nts::isColliding(player->getHitbox(), item->getHitbox())) {
				if (item->isBreakable()) {
					if (player->getZIndex() == item->getZIndex() + 1) {
						showPickupCommand = true;
					}
				}
			}
		}

		// Check item collision with walls
		for (g3nts::Item* item : items) {
			for (g3nts::PrimitiveRect wall : playerWalls) {
				if (g3nts::isColliding(item->getHitbox(), wall)) {
					if (wall.getWidth() < wall.getHeight()) {
						item->setVelocity(Vec2(-item->getVelocity().x * 0.4f, item->getVelocity().y));
					}
					else if (wall.getWidth() > wall.getHeight()) {
						item->setVelocity(Vec2(item->getVelocity().x, -item->getVelocity().y * 0.4f));
					}
				}
			}

			for (g3nts::PrimitiveRect wall : itemWalls) {
				if (g3nts::isColliding(item->getHitbox(), wall)) {
					if (wall.getWidth() < wall.getHeight()) {
						item->setVelocity(Vec2(-item->getVelocity().x * 0.4f, item->getVelocity().y));
					}
					else if (wall.getWidth() > wall.getHeight()) {
						item->setVelocity(Vec2(item->getVelocity().x, -item->getVelocity().y * 0.4f));
					}
				}
			}
		}

		showDropCommand = false; showExitCommand = false;
		if (g3nts::isColliding(player->getHitbox(), flexMobileDrop)) {
			if (inventory.size() > 0) showDropCommand = true;
			else {
				if (gameWin) showExitCommand = true;
			}
		}

		showFlexCommand = false;
		for (g3nts::Mirror* mirror : mirrors) {
			if (mirror->getPosition().getDistanceSq(player->getPosition()) <= 200 * 200) {
				if (!mirror->isBroken()) showFlexCommand = true;
			}
		}

		if (showPickupCommand) {
			pickupCommandTextbox->setPosition(Vec2(player->getPosition().x - 60, player->getPosition().y + 120));
			pickupCommandTextbox->setVisible(true);
		}
		else {
			pickupCommandTextbox->setVisible(false);
		}

		if (showDropCommand) {
			dropCommandTextbox->setPosition(Vec2(player->getPosition().x - 60, player->getPosition().y + 120));
			dropCommandTextbox->setVisible(true);
		}
		else {
			dropCommandTextbox->setVisible(false);
		}

		if (showFlexCommand) {
			flexCommandTextbox->setPosition(Vec2(player->getPosition().x + 60, player->getPosition().y + 120));
			flexCommandTextbox->setVisible(true);
		}
		else {
			flexCommandTextbox->setVisible(false);
		}

		if (showExitCommand) {
			exitCommandTextbox->setPosition(Vec2(player->getPosition().x + 60, player->getPosition().y + 120));
			exitCommandTextbox->setVisible(true);
		}
		else {
			exitCommandTextbox->setVisible(false);
		}
	}
}

void Level1::togglePause() {
	gamePaused = !gamePaused;
	pauseMenu->setPosition(camera->getPosition());

	if (gamePaused) {
		player->getKeyboardListener()->setEnabled(false);
		this->unscheduleUpdate();
		pauseMenu->setVisible(true);
		unflex_meter->stopAllActionsByTag('UI');
	}
	else {
		pauseMenu->setVisible(false);
		this->scheduleUpdate();
		player->getKeyboardListener()->setEnabled(true);
	}
}

void Level1::showHitboxes() {
	player->getHitbox().getNode()->setVisible(true);
	flexMobile->getHitbox().getNode()->setVisible(true);
	flexMobileDrop.getNode()->setVisible(true);
	for (g3nts::PrimitiveRect wall : playerWalls) wall.getNode()->setVisible(true);
	for (g3nts::PrimitiveRect wall : itemWalls) wall.getNode()->setVisible(true);
	for (g3nts::Item* item : items) item->getHitbox().getNode()->setVisible(true);
	for (g3nts::Mirror* mirror : mirrors) mirror->getHitbox().getNode()->setVisible(true);
}

void Level1::screenshake() {
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