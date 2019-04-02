#include "TutorialCutscene.h"
#include "Tutorial.h"

USING_NS_CC;

cocos2d::Scene* TutorialCS::createScene() { return TutorialCS::create(); }

void TutorialCS::onEnter() { Scene::onEnter(); }

bool TutorialCS::init() {
	if(!Scene::init()) return false;

	sceneIter = 0u;
	levelScale = 1.35f;

	initDirector();
	initSpriteCache();
	initKeyboardListener();

	initLevel();
	initSprites();
	initTextbox();

	this->scheduleUpdate();

	return true;
}

void TutorialCS::onExit() { Scene::onExit(); }

void TutorialCS::initDirector() {
	director = Director::getInstance();
	audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();
}

void TutorialCS::initSpriteCache() {
	spriteCache = SpriteFrameCache::getInstance();
	spriteCache->addSpriteFramesWithFile("characters/cutscene-characters.plist");
}

void TutorialCS::initKeyboardListener() {
	typedef EventKeyboard::KeyCode Key;

	keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [&](Key key, Event* kEvent) {
		if (key == Key::KEY_SPACE) {
			sceneIter++;
		}
	};

	keyboardListener->onKeyReleased = [&](Key key, Event* kEvent) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void TutorialCS::initSprites() {	
	chad = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("chad/cutscene/default.png"));
	chad->setPosition(300, 350);
	chad->setScale(0.8f);

	dee = Sprite::createWithSpriteFrame(spriteCache->getSpriteFrameByName("dee/cutscene/default.png"));
	dee->setPosition(windowSize.x - 150, 250);
	dee->setScale(0.8f);

	this->addChild(chad, 100);
	this->addChild(dee, 100);
}

void TutorialCS::initLevel() {
	Vec2 offset = { -527, -513 };

	// Floor plan sprite
	houseBase = Sprite::create("backgrounds/chad-house-base.png");
	houseBase->setScale(levelScale);
	houseBase->setAnchorPoint(Vec2(0, 0));
	houseBase->setPosition(Vec2(offset.x, offset.y) * levelScale);

	// Upper walls sprite
	upperWalls = Sprite::create("backgrounds/chad-house-walls-upper.png");
	upperWalls->setScale(levelScale);
	upperWalls->setAnchorPoint(Vec2(0, 0));
	upperWalls->setPosition(Vec2(offset.x, offset.y) * levelScale);

	// Middle walls sprite
	middleWalls = Sprite::create("backgrounds/chad-house-walls-middle.png");
	middleWalls->setScale(levelScale);
	middleWalls->setAnchorPoint(Vec2(0, 0));
	middleWalls->setPosition(Vec2(offset.x, offset.y) * levelScale);

	// Lower walls sprite
	lowerWalls = Sprite::create("backgrounds/chad-house-walls-lower.png");
	lowerWalls->setScale(levelScale);
	lowerWalls->setAnchorPoint(Vec2(0, 0));
	lowerWalls->setPosition(Vec2(offset.x, offset.y) * levelScale);

	background = g3nts::PrimitiveRect(Vec2::ZERO, windowSize, Color4F(0, 0, 0, 0.92f), true);

	this->addChild(houseBase, -1000);
	this->addChild(upperWalls, 10);
	this->addChild(middleWalls, 20);
	this->addChild(lowerWalls, 30);
	this->addChild(background.getNode(), 50);
}

void TutorialCS::initTextbox() {
	Vec2 margin = { 25, 10 }, padding = { 5, 5 };

	dialogueBack = g3nts::PrimitiveRect(Vec2::ZERO + margin, Vec2(windowSize.x, 325) - margin, Color4F(0.1f, 0.1f, 0.1f, 0.85f), true);
	dialogueBorder = g3nts::PrimitiveRect(Vec2::ZERO + margin, Vec2(windowSize.x, 325) - margin, Color4F(0.9f, 0.9f, 0.9f, 1.0f), false);
	
	speakerBack = g3nts::PrimitiveRect(  Vec2::ZERO, Vec2(250, 90), Color4F(0.1f, 0.1f, 0.1f, 1.0f), true);
	speakerBorder = g3nts::PrimitiveRect(Vec2::ZERO, Vec2(250, 90), Color4F(0.9f, 0.9f, 0.9f, 1.0f), false);
	speakerBack.setPosition(Vec2(margin.x / 2 + speakerBack.getWidth() / 2, 325 - speakerBack.getHeight() / 2 + margin.y));
	speakerBorder.setPosition(Vec2(margin.x / 2 + speakerBorder.getWidth() / 2, 325 - speakerBorder.getHeight() / 2 + margin.y));

	dialogue = Label::createWithTTF("Test", "fonts/GillSansUltraBold.ttf", 36);
	dialogue->setPosition(dialogueBack.getCentrePosition());

	speaker = Label::createWithTTF("Test", "fonts/GillSansUltraBold.ttf", 42);
	speaker->setPosition(speakerBack.getCentrePosition());

	prompt = Label::createWithTTF("[ Space ]", "fonts/GillSansUltraBold.ttf", 24);
	prompt->setPosition(
		dialogueBorder.getEndPosition().x - (prompt->getContentSize().width / 2) - padding.x,
		dialogueBorder.getStartPosition().y + (prompt->getContentSize().height / 2) + padding.y
	);

	this->addChild(dialogueBack.getNode(), 150);
	this->addChild(dialogueBorder.getNode(), 151);
	this->addChild(speakerBack.getNode(), 152);
	this->addChild(speakerBorder.getNode(), 153);
	
	this->addChild(speaker, 152);
	this->addChild(dialogue, 153);
	this->addChild(prompt, 154);
}

void TutorialCS::update(const float dt) {
	typedef std::string string;
	
	static float timer = 0;
	bool timerSet = false;

	string _dialogue, _speaker;

	timer -= dt;

	switch (sceneIter) {
	case 0:
		_dialogue = "* RING *";
		_speaker = "";
		chad->setOpacity(0);
		dee->setOpacity(0);
		
		speakerBack.getNode()->setVisible(false);
		speakerBorder.getNode()->setVisible(false);

		audioEngine->playEffect("sfx/telephone.mp3");

		break;
	case 1:
		_dialogue = "";
		_speaker = "";

		chad->setSpriteFrame("chad/cutscene/annoyed.png");

		if (chad->getOpacity() + 10 < 255) chad->setOpacity(chad->getOpacity() + 10);
		else chad->setOpacity(255);
		
		dialogueBack.getNode()->setVisible(false);
		dialogueBorder.getNode()->setVisible(false);

		if (!timerSet) {
			timer = 1.0f;
			timerSet = true;
		}
		
		if (timer <= 0) {
			timerSet = false;
			sceneIter++;
		}

		break;
	case 2:
		_speaker = "Chad";
		_dialogue = "...Huh?";

		dialogueBack.getNode()->setVisible(true);
		dialogueBorder.getNode()->setVisible(true);
		speakerBack.getNode()->setVisible(true);
		speakerBorder.getNode()->setVisible(true);

		break;
	case 3:
		_dialogue = "* CLICK *";

		speakerBack.getNode()->setVisible(false);
		speakerBorder.getNode()->setVisible(false);

		if (!timerSet) {
			timer = 1.5f;
			timerSet = true;
		}

		if (timer <= 0) {
			timerSet = false;
			sceneIter++;
		}

		break;
	case 4:
		_speaker = "Chad";
		_dialogue = "...Hello?";

		speakerBack.getNode()->setVisible(true);
		speakerBorder.getNode()->setVisible(true);

		break;
	case 5:
		_dialogue = "Chad. It's Dee.";
		_speaker = "Dee";

		if (dee->getOpacity() + 10 < 255) dee->setOpacity(dee->getOpacity() + 10);
		else dee->setOpacity(255);

		if (chad->getOpacity() - 10 > 50) chad->setOpacity(chad->getOpacity() - 10);
		else chad->setOpacity(50);

		break;
	case 6:
		_dialogue = "I hate to call you at this time, but we have a case.";
		_speaker = "Dee";

		break;
	case 7:
		_dialogue = "A case? It's midnight! Can't this wait until\nmorning?";
		_speaker = "Chad";

		if (chad->getOpacity() + 10 < 255) chad->setOpacity(chad->getOpacity() + 10);
		else chad->setOpacity(255);

		if (dee->getOpacity() - 10 > 50) dee->setOpacity(dee->getOpacity() - 10);
		else dee->setOpacity(50);

		break;
	case 8:
		dee->setSpriteFrame("dee/cutscene/angry.png");

		_dialogue = "\nNo, it can't. There's been a murder at the shipping\nwarehouse. I need you to grab your things and\nbring them to your car.";
		_speaker = "Dee";

		if (dee->getOpacity() + 10 < 255) dee->setOpacity(dee->getOpacity() + 10);
		else dee->setOpacity(255);

		if (chad->getOpacity() - 10 > 50) chad->setOpacity(chad->getOpacity() - 10);
		else chad->setOpacity(50);

		break;
	case 9:
		_dialogue = "Criminals in this city aren't going to wait\nfor you to get your beauty sleep.";
		_speaker = "Dee";

		break;
	case 10:
		_dialogue = "Ugh...fine. I'll get up.";
		_speaker = "Chad";

		if (chad->getOpacity() + 10 < 255) chad->setOpacity(chad->getOpacity() + 10);
		else chad->setOpacity(255);

		if (dee->getOpacity() - 10 > 50) dee->setOpacity(dee->getOpacity() - 10);
		else dee->setOpacity(50);

		break;
	case 11:
		_dialogue = "Do we know any details about the crime?";
		_speaker = "Chad";

		break;
	case 12:
		_dialogue = "I'll tell you what I know once you get here.\nRight now, you need to get your stuff,\nbring it to your car, and get over here.";
		_speaker = "Dee";
		
		if (dee->getOpacity() + 10 < 255) dee->setOpacity(dee->getOpacity() + 10);
		else dee->setOpacity(255);

		if (chad->getOpacity() - 10 > 50) chad->setOpacity(chad->getOpacity() - 10);
		else chad->setOpacity(50);

		break;
	case 13:
		_dialogue = "Alright. I'm on my way.";
		_speaker = "Chad";

		if (chad->getOpacity() + 10 < 255) chad->setOpacity(chad->getOpacity() + 10);
		else chad->setOpacity(255);

		if (dee->getOpacity() - 10 > 50) dee->setOpacity(dee->getOpacity() - 10);
		else dee->setOpacity(50);

		break;
	case 14:
		if (chad->getOpacity() - 10 > 0) chad->setOpacity(chad->getOpacity() - 10);
		else chad->setOpacity(0);
		
		if (dee->getOpacity() - 10 > 0) dee->setOpacity(dee->getOpacity() - 10);
		else dee->setOpacity(0);

		dialogueBack.getNode()->setVisible(false);
		dialogueBorder.getNode()->setVisible(false);
		speakerBack.getNode()->setVisible(false);
		speakerBorder.getNode()->setVisible(false);

		if (!timerSet) {
			timer = 1.5f;
			timerSet = true;
		}

		if (timer <= 0) {
			timerSet = false;
			sceneIter++;
		}

		break;
	default:
		Scene* tutorialScene = Tutorial::createScene();
		director->replaceScene(tutorialScene);
		break;
	}

	dialogue->setString(_dialogue);
	speaker->setString(_speaker);
}
