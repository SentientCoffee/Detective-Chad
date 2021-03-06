#pragma once

#ifndef __WINSCREEN_SCENE_H__
#define __WINSCREEN_SCENE_H__

#include "cocos2d.h"

class WinScreen : public cocos2d::Scene {
public:

	CREATE_FUNC(WinScreen);
	static cocos2d::Scene* createScene(
		int newMirror, int newEvidence, 
		int newTime, int newAdditional, 
		int newScore, std::string newRating,
		unsigned int levelID);

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
	static int mirrorScore, evidenceScore, timeScore, additionalScore, scoreScore, _levelID;
	static std::string ratingScore;

};
#endif