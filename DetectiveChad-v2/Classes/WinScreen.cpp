#include "WinScreen.h"
#include "MainMenu.h"
#include "Tutorial.h"
#include "Level_1.h"

USING_NS_CC;

Scene* WinScreen::createScene(int newMirror, int newEvidence, int newTime, int newAdditional, int newScore, std::string newRating, unsigned int levelID) { 
	
	mirrorScore = newMirror;
	evidenceScore = newEvidence;
	timeScore = newTime;
	additionalScore = newAdditional;
	scoreScore = newScore;
	ratingScore = newRating;
	_levelID = levelID;

	return WinScreen::create(); 
}

void WinScreen::onEnter() { Scene::onEnter(); }

bool WinScreen::init() {
	if (!Scene::init()) return false;

	initDirector();
	initMenu();

	return true;
}

void WinScreen::onExit() { Scene::onExit(); }

void WinScreen::initDirector() {
	director = Director::getInstance();

	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();
}

void WinScreen::initMenu() {
	background = Sprite::create("ui/winscreen.png");
	background->setPosition(windowSize.x / 2, windowSize.y / 2);

	Label* restartLabel = Label::createWithTTF("Restart", "fonts/GillSansUltraBold.ttf", 16, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* exitLabel = Label::createWithTTF("Back to\nMain Menu", "fonts/GillSansUltraBold.ttf", 16, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* nextLabel = Label::createWithTTF("Next\nLevel", "fonts/GillSansUltraBold.ttf", 16, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);

	Label* MirrorLabel = Label::createWithTTF("Mirrors remaining: ", "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* EvidenceLabel = Label::createWithTTF("Evidence collected: ", "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* TimeLabel = Label::createWithTTF("Time: ", "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* AdditionalLabel = Label::createWithTTF("Extra evidence: ", "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* scoreLabel = Label::createWithTTF("Final Score: ", "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* RatingLabel = Label::createWithTTF("Rating: ", "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);

	Label* MirrorScoreLabel = Label::createWithTTF(std::to_string(mirrorScore), "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* EvidenceScoreLabel = Label::createWithTTF(std::to_string(evidenceScore), "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* TimeScoreLabel = Label::createWithTTF(std::to_string(timeScore), "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* AdditionalScoreLabel = Label::createWithTTF(std::to_string(additionalScore), "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* scoreScoreLabel = Label::createWithTTF(std::to_string(scoreScore), "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);
	Label* RatingScoreLabel = Label::createWithTTF(ratingScore, "fonts/GillSansUltraBold.ttf", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::CENTER);

	//gameOverLabel->enableShadow();
	restartLabel->enableShadow();
	exitLabel->enableShadow();
	nextLabel->enableShadow();

	MirrorLabel->enableShadow();
	EvidenceLabel->enableShadow();
	TimeLabel->enableShadow();
	AdditionalLabel->enableShadow();
	scoreLabel->enableShadow();
	RatingLabel->enableShadow();

	MirrorScoreLabel->enableShadow();
	EvidenceScoreLabel->enableShadow();
	TimeScoreLabel->enableShadow();
	AdditionalScoreLabel->enableShadow();
	scoreScoreLabel->enableShadow();
	RatingScoreLabel->enableShadow();

	MenuItemLabel* restartButton = MenuItemLabel::create(restartLabel, [&](Ref* sender) {
		Scene* tutorialScene = Tutorial::createScene();
		director->replaceScene(TransitionFade::create(2, tutorialScene));
	});
	MenuItemLabel* exitButton = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
		Scene* mainMenuScene = MainMenu::createScene();
		director->replaceScene(TransitionFade::create(2, mainMenuScene));
	});
	MenuItemLabel* nextButton = MenuItemLabel::create(nextLabel, [&](Ref* sender) {
		Scene* mainMenuScene = MainMenu::createScene();
		Scene* level1Scene = Level1::createScene();

		switch (_levelID) {
		case 0:
			director->replaceScene(TransitionFade::create(2, level1Scene));
			break;
		default:
			director->replaceScene(TransitionFade::create(2, mainMenuScene));
		}
	});


	//gameOverItem->setPosition(0, windowSize.y * 0.35);
	restartButton->setPosition(windowSize.x * 0.025, -(windowSize.y * 0.23));
	exitButton->setPosition(windowSize.x * 0.065, -(windowSize.y * 0.35));
	nextButton->setPosition(windowSize.x * 0.1, -(windowSize.y*0.24));

	MirrorLabel->setPosition(windowSize.x / 2 - 25, windowSize.y * 2 / 3 + 20);
	EvidenceLabel->setPosition(windowSize.x / 2 - 25, windowSize.y * 2 / 3 - 20);
	TimeLabel->setPosition(windowSize.x / 2 - 125, windowSize.y * 2 / 3 - 60);
	AdditionalLabel->setPosition(windowSize.x / 2 - 50, windowSize.y * 2 / 3 - 100);
	scoreLabel->setPosition(windowSize.x / 2 - 80, windowSize.y * 2 / 3 - 140);
	RatingLabel->setPosition(windowSize.x / 2 - 110, windowSize.y * 2 / 3 - 180);

	MirrorScoreLabel->setPosition(windowSize.x * 2 / 3 - 80, windowSize.y * 2 / 3 + 20);
	EvidenceScoreLabel->setPosition(windowSize.x * 2 / 3 - 80, windowSize.y * 2 / 3 - 20);
	TimeScoreLabel->setPosition(windowSize.x * 2 / 3 - 77, windowSize.y * 2 / 3 - 60);
	AdditionalScoreLabel->setPosition(windowSize.x * 2 / 3 - 80, windowSize.y * 2 / 3 - 100);
	scoreScoreLabel->setPosition(windowSize.x * 2 / 3 - 90, windowSize.y * 2 / 3 - 140);
	RatingScoreLabel->setPosition(windowSize.x * 2 / 3 - 100, windowSize.y * 2 / 3 - 180);

	menu = Menu::create(restartButton, exitButton, nextButton, NULL);
	menu->setPosition(menu->getPosition().x - 50, menu->getPosition().y);

	this->addChild(background, -100);
	this->addChild(menu);

	this->addChild(MirrorLabel);
	this->addChild(EvidenceLabel);
	this->addChild(TimeLabel);
	this->addChild(AdditionalLabel);
	this->addChild(scoreLabel);
	this->addChild(RatingLabel);

	this->addChild(MirrorScoreLabel);
	this->addChild(EvidenceScoreLabel);
	this->addChild(TimeScoreLabel);
	this->addChild(AdditionalScoreLabel);
	this->addChild(scoreScoreLabel);
	this->addChild(RatingScoreLabel);
}
