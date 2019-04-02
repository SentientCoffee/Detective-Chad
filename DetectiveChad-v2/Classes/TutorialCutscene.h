#pragma once

#ifndef __TUTORIAL_CUTSCENE_H__
#define __TUTORIAL_CUTSCENE_H__

#include "cocos2d.h"
#include "Primitives.h"
#include "SimpleAudioEngine.h"
#include "Textbox.h"

class TutorialCS : public cocos2d::Scene {
public:

	CREATE_FUNC(TutorialCS);
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void initDirector();
	void initSpriteCache();
	void initKeyboardListener();
	
	void initSprites();
	void initLevel();
	void initTextbox();

	void update(const float dt) override;

private:

	cocos2d::Director* director;
	cocos2d::SpriteFrameCache* spriteCache;
	CocosDenshion::SimpleAudioEngine* audioEngine;

	cocos2d::Vec2 windowSize, origin;
	cocos2d::Size visibleSize;

	cocos2d::EventListenerKeyboard* keyboardListener;

	unsigned int sceneIter;
	float levelScale;

	cocos2d::Sprite *houseBase, *upperWalls, *middleWalls, *lowerWalls;
	g3nts::PrimitiveRect background;

	cocos2d::Sprite *chad, *dee;
	cocos2d::Label *dialogue, *speaker, *prompt;
	g3nts::PrimitiveRect dialogueBack, dialogueBorder;
	g3nts::PrimitiveRect speakerBack, speakerBorder;

};

#endif