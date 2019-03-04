#include "UI.h"

UI::UI()
{
	
	//flex_state = player.getFlexState();
	//evidence_num = tutorial.getEvidence();

	//placeholder values
	flex_state = false;
	evidence_num = 2;
	//setting up sprites
	flexing_meter = Sprite::create("ui/flexing.png");
	flex_meter = Sprite::create("ui/unflex.png");
	
	for (unsigned int i = 0;i < evidence_num;i++)
	{
		evidence.push_back(Sprite::create("ui/evidence.png"));
		broken_evidence.push_back(Sprite::create("ui/broken.png"));
	}
}

void UI::update(float dt)
{
	cocos2d::Vec2 player_position = Tutorial::getPlayer()->getPosition();
	cocos2d::Vec2 winSize = getWindowSize();
	flex_meter->setPosition(player_position.x - windowSize.x)
}

