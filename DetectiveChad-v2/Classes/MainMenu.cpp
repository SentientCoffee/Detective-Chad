#include "MainMenu.h"
#include "TutorialCutscene.h"

USING_NS_CC;

Scene* MainMenu::createScene() { return MainMenu::create(); }

void MainMenu::onEnter() { Scene::onEnter(); }

bool MainMenu::init() {
	if (!Scene::init()) return false;

	initDirector();
	initMenu();

	return true;
}

void MainMenu::onExit() { Scene::onExit(); }

void MainMenu::initDirector() {
	director = Director::getInstance();

	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();
}

void MainMenu::initMenu() {
	background = Sprite::create("ui/mainmenuscreen.png");
	background->setPosition(windowSize.x / 2, windowSize.y / 2);

	Label* startLabel = Label::createWithTTF("Start", "fonts/GillSansUltraBold.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* exitLabel = Label::createWithTTF("Exit", "fonts/GillSansUltraBold.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	startLabel->enableShadow();
	exitLabel->enableShadow();

	MenuItemLabel* startButton = MenuItemLabel::create(startLabel, [&](Ref* sender) {
		Scene* tutorialCutscene = TutorialCS::createScene();
		director->replaceScene(TransitionFade::create(2, tutorialCutscene));
	});
	MenuItemLabel* exitButton = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
		director->end();
	});

	startButton->setPosition(20, -(windowSize.y * 0.15));
	exitButton->setPosition(20, -(windowSize.y * 0.32));


	menu = Menu::create(startButton, exitButton, NULL);

	this->addChild(background, -100);
	this->addChild(menu);
}