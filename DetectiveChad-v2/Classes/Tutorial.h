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
#include "WinScreen.h"

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
											  
	// Level sprites						  
	cocos2d::Sprite* houseBase;               // Background sprite
	cocos2d::Sprite* upperWalls;              // Sprites for just the upper walls
	cocos2d::Sprite* middleWalls;             // Sprites for just the middle walls
	cocos2d::Sprite* lowerWalls;              // Sprites for just the lower walls
											  
											  
	// Player								  
	g3nts::Character* player;                 // Player character (object controlled by user)
	cocos2d::Vec2 playerPosition;             // Player's starting position
	                                          // Will be used in pause menu function to ensure player stays in the same position
											  
	// Items in the scene					  
	std::vector<g3nts::Item*> items;          // Container to hold all the items in the level
	unsigned int totalItems;
	unsigned int requiredItems;
	unsigned int itemsCollected;			  
											  
	g3nts::Mirror* bathroomMirror;            // Bathroom mirror for Chad to flex in front of
	g3nts::Item* flexMobile;
	g3nts::PrimitiveRect flexMobileDrop;
											  
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
	float time;

	int mScore, eScore, tScore, aScore, sScore;
	std::string rScore;

	cocos2d::Sprite* inventory_bg;                    // inventory UI
	std::vector<g3nts::Item*> inventory;
	unsigned int pickedUp;
	
	// Pause menu
	cocos2d::Menu* pauseMenu;                  // Pause Menu object when the game is paused
	bool gamePaused;                           // Bool to check if the game is paused

	// Textboxes
	bool showDropCommand;
	bool showPickupCommand;
	bool showFlexCommand;
	g3nts::Textbox* dropCommandTextbox;
	g3nts::Textbox* pickupCommandTextbox;
	g3nts::Textbox* flexCommandTextbox;

	// Keyboard struct with listener
	Input::Keyboard keyboard;
	cocos2d::EventListenerKeyboard* keyboardListener;

	float levelScale;                         // Scaling of the level
	std::vector<g3nts::PrimitiveRect> playerWalls;  // Container to hold all the boundaries
	std::vector<g3nts::PrimitiveRect> itemWalls;

	// ALL THE BOUNDARIES IN THE LEVEL
	// ---------------------------------------------------
	// Level boundaries to make sure the player does not leave the level
	g3nts::PrimitiveRect upperBoundary;
	g3nts::PrimitiveRect lowerBoundary;
	g3nts::PrimitiveRect leftBoundary;
	g3nts::PrimitiveRect rightBoundary;

	g3nts::PrimitiveRect topHedge;
	g3nts::PrimitiveRect bottomHedge;

	// Outer house walls
	g3nts::PrimitiveRect upperHouseWall;
	g3nts::PrimitiveRect lowerHouseWall;
	g3nts::PrimitiveRect leftHouseWall;
	g3nts::PrimitiveRect rightHouseWall_1;
	g3nts::PrimitiveRect rightHouseWall_2;

	g3nts::PrimitiveRect iUpperHouseWall;

	// Inner horizontal house walls (for Chad)
	g3nts::PrimitiveRect bathroomDoorway_1;
	g3nts::PrimitiveRect bathroomDoorway_2;
	g3nts::PrimitiveRect bedroomDoorway;
	g3nts::PrimitiveRect livingRoomDoorway_1;
	g3nts::PrimitiveRect livingRoomDoorway_2;

	// Inner horizontal house walls (for items)
	g3nts::PrimitiveRect iBathroomDoorway_1;
	g3nts::PrimitiveRect iBathroomDoorway_2;
	g3nts::PrimitiveRect iBedroomDoorway;
	g3nts::PrimitiveRect iLivingRoomDoorway_1;
	g3nts::PrimitiveRect iLivingRoomDoorway_2;

	// Inner vertical house walls
	g3nts::PrimitiveRect verticalBathroomWall;
	g3nts::PrimitiveRect vecticalLivingRoomWall_1;
	g3nts::PrimitiveRect vecticalLivingRoomWall_2;

	// Fogs of War
	std::vector<g3nts::PrimitiveRect> FoW; //container to hold solid fogs of war
	std::vector<g3nts::PrimitiveRect> sFoW; //container to hold opaque fogs of war

	// -----------------------------------------------
	// Tutorial level rooms

	// State One (100% Opacity)
	g3nts::PrimitiveRect roomOne;
	g3nts::PrimitiveRect roomTwo;
	g3nts::PrimitiveRect roomThree;
	g3nts::PrimitiveRect roomFour;
	g3nts::PrimitiveRect roomFive;
	g3nts::PrimitiveRect roomSix;

	// State Two (40% Opacity)
	g3nts::PrimitiveRect sroomOne;
	g3nts::PrimitiveRect sroomTwo;
	g3nts::PrimitiveRect sroomThree;
	g3nts::PrimitiveRect sroomFour;
	g3nts::PrimitiveRect sroomFive;
	g3nts::PrimitiveRect sroomSix;

	// -----------------------------------------------
};

#endif