#pragma once

#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Collision.h"
#include "InputDevices.h"
#include "Item.h"
#include "Mirror.h"
#include "Primitives.h"
#include "Textbox.h"

class GameOver : public cocos2d::Scene {
public:

	CREATE_FUNC(GameOver);
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void initDirector();
	void initMenu();

private:

	cocos2d::Director* director;             // Director to change and transition scenes and get info about the window
	cocos2d::Vec2 windowSize, origin;        // Window size and origin (point (0, 0))
	cocos2d::Size visibleSize;               // Visible size of the window

	cocos2d::Menu* menu;
	cocos2d::Sprite* background;
};

#endif