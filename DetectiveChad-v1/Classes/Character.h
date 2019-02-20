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
		cocos2d::Vec2 getDirection() const;
		PrimitiveRect getHitbox() const;

		void setPosition(cocos2d::Vec2& position);
		void setPosition(const float x, const float y);
		void setDirection(cocos2d::Vec2& direction);
		void setDirection(const float x, const float y);

		void addToScene(cocos2d::Scene* scene);
		void update(const float dt);

	private:
		float _characterSpeed = 400.0f;
		
		cocos2d::Sprite* _sprite;
		PrimitiveRect _hitbox;
		cocos2d::Vec2 _position;
		cocos2d::Vec2 _playerDirection;

		//Input::Mouse mouse;
		//cocos2d::EventListenerMouse* mouseListener;
		Input::Keyboard _keyboard;
		cocos2d::EventListenerKeyboard* _keyboardListener;

		void initKeyboardListener();
	};
}

#endif