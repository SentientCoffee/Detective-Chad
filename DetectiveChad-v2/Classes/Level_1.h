#pragma once

#ifndef __LEVEL_1_SCENE_H__
#define __LEVEL_1_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Collision.h"
#include "InputDevices.h"
#include "Item.h"
#include "Mirror.h"
#include "Primitives.h"
#include "Textbox.h"
#include "WinScreen.h"

class Level1 : public cocos2d::Scene {
public:

	CREATE_FUNC(Level1);
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void initDirector();
	void initSpriteCache();

	void initPlayer();
	void initProps();
	void initLevel();
	void initItems();
	void initWalls();
	void initFoW();

	void initUI();
	void initTextboxes();
	void initPauseMenu();

	void initKeyboardListener();

	void update(const float dt) override;

	void screenshake();
	void togglePause();
	void showHitboxes();

private:
	// Cocos bulit-in classes
	cocos2d::Director* director;              // Director to change and transition scenes and get info about the window
	cocos2d::SpriteFrameCache* spriteCache;   // Sprite cache for all the different sprites
	cocos2d::Camera* camera;

	cocos2d::Vec2 windowSize, origin;         // Window size and origin (point (0, 0))
	cocos2d::Size visibleSize;                // Visible size of the window

	// Player								  
	g3nts::Character* player;                 // Player character (object controlled by user)
	cocos2d::Vec2 playerPosition;             // Player's starting position

	// Level sprites						  
	cocos2d::Sprite* warehouseBase;           // Background sprite
	cocos2d::Sprite* bottomWall;

	cocos2d::Sprite* securityOfficeWall;
	cocos2d::Sprite* supervisorOfficeWall;

	cocos2d::Sprite* workerAreaUpperWall;
	cocos2d::Sprite* workerAreaMiddleWall;
	cocos2d::Sprite* workerAreaLowerWall;

	cocos2d::Sprite* redContainerTop;
	cocos2d::Sprite* redContainerBottom;
	cocos2d::Sprite* greenContainerTop;
	cocos2d::Sprite* greenContainerBottom;
	cocos2d::Sprite* purpleContainerTop;
	cocos2d::Sprite* purpleContainerBottom;
	cocos2d::Sprite* pinkContainer;

	cocos2d::Sprite* surroundingCrates;
	cocos2d::Sprite* extraCrates;


	// Items in the scene					  
	std::vector<g3nts::Item*> items;          // Container to hold all the items in the level
	unsigned int totalItems;
	unsigned int requiredItems;
	unsigned int itemsCollected;

	g3nts::Item* flexMobile;
	g3nts::PrimitiveRect flexMobileDrop;

	// Mirrors
	std::vector<g3nts::Mirror*> mirrors;
	g3nts::Mirror *bathroomMirror, *containerMirror, *crateMirror;

	// UI									  
	float UI_Scale;                           // Scaling of UI
	float flexRefillTimer;
	cocos2d::Sprite* unflex_bg;               // Unflexed meter UI
	cocos2d::ProgressTimer* unflex_meter;

	cocos2d::Sprite* flex_bg;                 // Flexing meter UI
	cocos2d::ProgressTimer* flex_meter;

	std::vector<cocos2d::Sprite*> evidence;        // Evidence UI
	std::vector<cocos2d::Sprite*> broken_evidence; // Broken Evidence UI
	std::vector<cocos2d::Sprite*> collected_evidence;
	std::vector<bool> evidence_state;              // State of the evidence

	unsigned int broken;
	bool gameOver;
	bool gameWin;
	static float time;
	static unsigned int levelID;

	int mScore, eScore, tScore, aScore, sScore;
	std::string rScore;

	cocos2d::Sprite* inventory_bg;                    // inventory UI
	std::vector<g3nts::Item*> inventory;

	// Pause menu
	cocos2d::Menu* pauseMenu;                  // Pause Menu object when the game is paused
	bool gamePaused;                           // Bool to check if the game is paused

	// Textboxes
	bool showDropCommand;
	bool showPickupCommand;
	bool showFlexCommand;
	bool showExitCommand;

	g3nts::Textbox* dropCommandTextbox;
	g3nts::Textbox* pickupCommandTextbox;
	g3nts::Textbox* flexCommandTextbox;
	g3nts::Textbox* exitCommandTextbox;

	// Keyboard struct with listener
	Input::Keyboard keyboard;
	cocos2d::EventListenerKeyboard* keyboardListener;

	float levelScale;                               // Scaling of the level
	std::vector<g3nts::PrimitiveRect> playerWalls;  // Container to hold all the boundaries
	std::vector<g3nts::PrimitiveRect> itemWalls;    // Walls for items

	// Fogs of War
	std::vector<g3nts::PrimitiveRect> FoW;  // Container to hold solid fogs of war
	std::vector<g3nts::PrimitiveRect> sFoW; // Container to hold opaque fogs of war

	// Level boundaries to make sure the player does not leave the level
	g3nts::PrimitiveRect upperBoundary;
	g3nts::PrimitiveRect lowerBoundary;
	g3nts::PrimitiveRect leftBoundary;
	g3nts::PrimitiveRect rightBoundary;

};

#endif