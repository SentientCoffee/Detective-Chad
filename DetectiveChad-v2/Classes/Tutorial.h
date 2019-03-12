#pragma once

#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Collision.h"
#include "InputDevices.h"
#include "Item.h"
#include "Mirror.h"
#include "Primitives.h"
#include "Textbox.h"

class Tutorial : public cocos2d::Scene {
public:

	CREATE_FUNC(Tutorial);
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	void initDirector();
	void initSpriteCache();

	void initPlayer();
	void initLevel();
	void initItems();
	void initWalls();
	
	void initUI();
	void initTextboxes();
	void initPauseMenu();

	void initKeyboardListener();
	void initMouseListener();

	void update(const float dt) override;

	void screenshake();
	void togglePause();
	void showHitboxes();

private:
	// Cocos bulit-in classes
	cocos2d::Director* director;             // Director to change and transition scenes and get info about the window
	cocos2d::SpriteFrameCache* spriteCache;  // Sprite cache for all the different sprites
	cocos2d::Camera* camera;

	cocos2d::Vec2 windowSize, origin;        // Window size and origin (point (0, 0))
	cocos2d::Size visibleSize;               // Visible size of the window
	
	// Level sprites
	cocos2d::Sprite* floorplan;              // Background sprite
	cocos2d::Sprite* upperWalls;             // Sprites for just the upper walls
	cocos2d::Sprite* middleWalls;            // Sprites for just the middle walls
	cocos2d::Sprite* lowerWalls;             // Sprites for just the lower walls
	
	// Player
	g3nts::Character* player;                // Player character (object controlled by user)
	cocos2d::Vec2 playerPosition;            // Player's starting position
	                                         // Will be used in pause menu function to ensure player stays in the same position

	// Items in the scene
	std::vector<g3nts::Item*> items;         // Container to hold all the items in the level
	std::vector<g3nts::Item*> itemTemps;
	unsigned int totalItems;

	g3nts::Mirror* bathroomMirror;           // Bathroom mirror for Chad to flex in front of
	g3nts::Item* flexMobile;

	// UI
	float UI_Scale;                          // Scaling of UI
	float flexRefillTimer;
	cocos2d::Sprite* unflex_bg;              // Unflexed meter UI
	cocos2d::ProgressTimer* unflex_meter;

	cocos2d::Sprite* flex_bg;                // Flexing meter UI
	cocos2d::ProgressTimer* flex_meter;
	
	std::vector<cocos2d::Sprite*> evidence;        // Evidence UI
	std::vector<cocos2d::Sprite*> broken_evidence; // Broken Evidence UI
	std::vector<bool> evidence_state;              // State of the evidence
	unsigned int broken;

	cocos2d::Sprite* inventory_bg;                    // inventory UI
	std::vector<g3nts::Item*> inventory;
	std::unordered_map<string, bool> inventory_state;
	unsigned int pickedUp;
	
	// Pause menu
	cocos2d::Menu* pauseMenu;                 // Pause Menu object when the game is paused
	bool gamePaused;                          // Bool to check if the game is paused
	bool gameOver;

	// Textboxes
	bool showPickupCommand;
	g3nts::Textbox* textbox;

	// Mouse and keyboard structs, along with their listeners
	Input::Mouse mouse;
	cocos2d::EventListenerMouse* mouseListener;
	Input::Keyboard keyboard;
	cocos2d::EventListenerKeyboard* keyboardListener;

	
	// ALL THE BOUNDARIES IN THE TUTORIAL LEVEL
	// -----------------------------------------------
	float levelScale;                          // Scaling of the level
	std::vector<g3nts::PrimitiveRect> walls;   // Container to hold all the boundaries
	
	// Level boundaries to make sure the player does not leave the level
	g3nts::PrimitiveRect upperBoundary;
	g3nts::PrimitiveRect lowerBoundary;
	g3nts::PrimitiveRect rightBoundary;
	g3nts::PrimitiveRect leftBoundary;

	// Outer house walls
	g3nts::PrimitiveRect upperHouseWall;
	g3nts::PrimitiveRect lowerHouseWall;
	g3nts::PrimitiveRect leftHouseWall;
	g3nts::PrimitiveRect rightHouseWall_1;
	g3nts::PrimitiveRect rightHouseWall_2;
	
	// Inner horizontal house walls
	g3nts::PrimitiveRect bathroomDoorway_1;
	g3nts::PrimitiveRect bathroomDoorway_2;
	g3nts::PrimitiveRect bedroomDoorway;
	g3nts::PrimitiveRect livingRoomDoorway_1;
	g3nts::PrimitiveRect livingRoomDoorway_2;

	// Inner vertical house walls
	g3nts::PrimitiveRect verticalBathroomWall;
	g3nts::PrimitiveRect vecticalLivingRoomWall_1;
	g3nts::PrimitiveRect vecticalLivingRoomWall_2;
	// -----------------------------------------------		   

	
};

#endif