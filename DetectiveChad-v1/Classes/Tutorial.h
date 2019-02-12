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

	cocos2d::Director* director;           // Director to change and transition scenes and get info about the window

	cocos2d::Vec2 windowSize, origin;      // Window size and origin (point (0, 0))
	cocos2d::Size visibleSize;             // Visible size of the window

	cocos2d::Sprite* floorplan;           // Background sprite
	cocos2d::Sprite* aptWalls;                // Sprite for just the walls
	g3nts::Character* player;              // Player character (object controlled by user)

	// ALL THE WALLS IN THE TUTORIAL LEVEL
	g3nts::PrimitiveRect upperBoundary;
	g3nts::PrimitiveRect lowerBoundary;
	g3nts::PrimitiveRect rightBoundary;
	g3nts::PrimitiveRect leftBoundary;

	g3nts::PrimitiveRect upperHouseWall;
	g3nts::PrimitiveRect lowerHouseWall;
	g3nts::PrimitiveRect leftHouseWall;
	g3nts::PrimitiveRect rightHouseWall_1;
	g3nts::PrimitiveRect rightHouseWall_2;
	
	g3nts::PrimitiveRect bathroomDoorway_1;
	g3nts::PrimitiveRect bathroomDoorway_2;
	g3nts::PrimitiveRect bedroomDoorway_1;
	g3nts::PrimitiveRect bedroomDoorway_2;
	g3nts::PrimitiveRect livingRoomDoorway_1;
	g3nts::PrimitiveRect livingRoomDoorway_2;

	g3nts::PrimitiveRect verticalBathroomWall;
	g3nts::PrimitiveRect vecticalLivingRoomWall_1;
	g3nts::PrimitiveRect vecticalLivingRoomWall_2;
	
	std::vector<g3nts::PrimitiveRect> walls; // Vector to hold all the walls

	cocos2d::Menu* pauseMenu;       // Pause Menu object when the game is paused
	cocos2d::Vec2 playerPosition;   // Will be used in pause menu function to ensure player stays in the same position

	// Mouse and keyboard structs, along with their listeners
	Input::Mouse mouse;
	Input::Keyboard keyboard;
	cocos2d::EventListenerMouse* mouseListener;
	cocos2d::EventListenerKeyboard* keyboardListener;

	//cocos2d::Label* testLabel;   // To test for collisions

	bool gamePaused = false;       // Bool to check if the game is paused
	float playerSpeed = 400.0f;    // Player's normal speed
	float levelScale = 1.25f;      // Scaling of the level
};

#endif