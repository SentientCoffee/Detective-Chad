#include "GameOver.h"
#include "MainMenu.h"
#include "Tutorial.h"

USING_NS_CC;

Scene* GameOver::createScene() { return GameOver::create(); }

void GameOver::onEnter() { Scene::onEnter(); }

bool GameOver::init() {
	if (!Scene::init()) return false;

	initDirector();
	initMenu();

	return true;
}

void GameOver::onExit() { Scene::onExit(); }

void GameOver::initDirector() {
	director = Director::getInstance();

	windowSize = director->getWinSizeInPixels();
	origin = director->getVisibleOrigin();
	visibleSize = director->getVisibleSize();
}

void GameOver::initMenu() {
	background = Sprite::create("ui/gameoverscreen.png");
	background->setPosition(windowSize.x / 2, windowSize.y / 2);

	//Label* gameOverLabel = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 72, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* restartLabel = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 24, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
	Label* exitLabel = Label::createWithTTF("Back to\nMain Menu", "fonts/Marker Felt.ttf", 24, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);

	//gameOverLabel->enableShadow();
	restartLabel->enableShadow();
	exitLabel->enableShadow();

	//MenuItemLabel* gameOverItem = MenuItemLabel::create(gameOverLabel);
	MenuItemLabel* restartButton = MenuItemLabel::create(restartLabel, [&](Ref* sender) {
		Scene* tutorialScene = Tutorial::createScene();
		director->replaceScene(TransitionFade::create(2, tutorialScene));
	});
	MenuItemLabel* exitButton = MenuItemLabel::create(exitLabel, [&](Ref* sender) {
		Scene* mainMenuScene = MainMenu::createScene();
		director->replaceScene(TransitionFade::create(2, mainMenuScene));
	});


	//gameOverItem->setPosition(0, windowSize.y * 0.35);
	restartButton->setPosition(-(windowSize.x * 0.05), -(windowSize.y * 0.22));
	exitButton->setPosition(windowSize.x * 0.04, -(windowSize.y * 0.23));

	menu = Menu::create(restartButton, exitButton, NULL);
	menu->setPosition(menu->getPosition().x - 50, menu->getPosition().y);

	this->addChild(background, -100);
	this->addChild(menu);
}
