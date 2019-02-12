#pragma once

#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Collision.h"
#include "InputDevices.h"
#include "Primitives.h"

class Tutorial : public cocos2d::Scene {
public:
	
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void initSprites();
	void initWalls();

	void initPauseMenu();

	void initKeyboardListener();
	void initMouseListener();

	void showHitboxes();

	void update(float dt);
	void togglePause();

	CREATE_FUNC(Tutorial);

private:

	cocos2d::Director* director;

	cocos2d::Vec2 windowSize, origin;
	cocos2d::Size visibleSize;

	cocos2d::Sprite* background;
	g3nts::Character* player;

	g3nts::PrimitiveRect upperHouseWall;
	g3nts::PrimitiveRect lowerHouseWall;
	g3nts::PrimitiveRect leftHouseWall;
	g3nts::PrimitiveRect rightHouseWall_1;
	g3nts::PrimitiveRect rightHouseWall_2;
	

	std::vector<g3nts::PrimitiveRect> walls;

	cocos2d::Menu* pauseMenu;
	cocos2d::Vec2 playerPosition;

	Input::Mouse mouse;
	Input::Keyboard keyboard;
	cocos2d::EventListenerMouse* mouseListener;
	cocos2d::EventListenerKeyboard* keyboardListener;

	cocos2d::Label* testLabel;

	bool gamePaused = false;
	float playerSpeed = 400.0f;
	float levelScale = 1.25f;
};

#endif