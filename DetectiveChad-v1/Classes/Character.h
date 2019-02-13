#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Primitives.h"
#include "InputDevices.h"

typedef std::string string;

namespace g3nts {
	class Character {
	public:
		Character();
		Character(cocos2d::Vec2& position, string spritePath);
		~Character();

		cocos2d::Sprite* getSprite() const;
		cocos2d::Vec2 getPosition() const;
		PrimitiveRect getHitbox() const;

		void setPosition(cocos2d::Vec2& position);
		void setPosition(const float x, const float y);

		void initKeyboardListener();

		void addToScene(cocos2d::Scene* scene);
		void update(const float dt);

	private:
		cocos2d::Sprite* _sprite;
		PrimitiveRect _hitbox;
		cocos2d::Vec2 _position;

		//Input::Mouse mouse;
		//cocos2d::EventListenerMouse* mouseListener;
		/*Input::Keyboard _keyboard;
		cocos2d::EventListenerKeyboard* _keyboardListener;*/

		float characterSpeed = 400.0f;
	};
}

#endif