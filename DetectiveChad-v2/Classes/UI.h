#pragma once

//include list of every level made
#include "Tutorial.cpp"
#include "MainMenu.h"

class UI
{
public:
	UI::UI();
	void UI::update(float dt);

private:
	cocos2d::Sprite* flex_meter; //500x220 px
	cocos2d::Sprite* flexing_meter; //500x551 px
	std::vector<cocos2d::Sprite*> evidence; //500x668 px
	std::vector<cocos2d::Sprite*> broken_evidence; //500x375 px
	int evidence_num; //taken from player
	bool flex_state; //taken from player


};