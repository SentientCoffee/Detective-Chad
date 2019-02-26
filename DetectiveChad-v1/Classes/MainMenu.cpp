#include "MainMenu.h"
#include "Tutorial.h"

USING_NS_CC;

cocos2d::Scene* MainMenu::createScene() { return MainMenu::create(); }

void MainMenu::onEnter() { Scene::onEnter(); }

bool MainMenu::init() {
	if (!Scene::init()) return false;

	director = Director::getInstance();
	windowSize = director->getWinSizeInPixels();
	visibleSize = director->getVisibleSize();
	origin = director->getVisibleOrigin();

	initMenu();

	return true;
}

void MainMenu::onExit() { Scene::onExit(); }

void MainMenu::initMenu() {
	background = Sprite::create("ui/mainmenuscreen.png");
	background->setPosition(windowSize.x / 2, windowSize.y / 2);

	Label* startLabel = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	startLabel->enableShadow();
	exitLabel->enableShadow();

	MenuItemLabel* startButton = MenuItemLabel::create(startLabel, [&](Ref* sender) {
		Scene* tutorialScene = Tutorial::createScene();
		director->replaceScene(TransitionFade::create(2, tutorialScene));
	});
	MenuItemLabel* exitButton = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
		director->end();
	});

	startButton->setPosition(20, -(windowSize.y * 0.18));
	exitButton->setPosition(20, -(windowSize.y * 0.35));


	menu = Menu::create(startButton, exitButton, NULL);

	this->addChild(background, -100);
	this->addChild(menu);
}