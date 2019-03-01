#pragma once

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene {
public:

	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void initMenu();

	CREATE_FUNC(MainMenu);


private:

	cocos2d::Director* director;
	
	cocos2d::Vec2 windowSize, origin;
	cocos2d::Size visibleSize;

	cocos2d::Sprite* background;
	//cocos2d::Label* title;
	cocos2d::Menu* menu;

	cocos2d::EventListenerMouse* mouseListener;

};

#endif