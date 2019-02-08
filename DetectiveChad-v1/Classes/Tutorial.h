#pragma once

#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "InputDevices.h"
#include "Character.h"
#include "Primitives.h"

class Tutorial : public cocos2d::Scene {
public:
	
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void initSprites();
	void initHitboxes();

	void initPauseMenu();

	void initKeyboardListener();
	void initMouseListener();

	void update(float dt);
	void togglePause();

	CREATE_FUNC(Tutorial);

private:

	cocos2d::Director* director;

	cocos2d::Vec2 windowSize, origin;
	cocos2d::Size visibleSize;

	cocos2d::Sprite* background;
	g3nts::Character* player;

	cocos2d::Menu* pauseMenu;
	cocos2d::Vec2 playerPosition;

	Input::Mouse mouse;
	Input::Keyboard keyboard;
	cocos2d::EventListenerMouse* mouseListener;
	cocos2d::EventListenerKeyboard* keyboardListener;

	

	//cocos2d::Camera* camera;
	bool gamePaused = false;

	float playerSpeed = 400.0f;
};

#endif