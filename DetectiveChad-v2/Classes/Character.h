#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Primitives.h"
#include "InputDevices.h"

typedef std::string string;
typedef cocos2d::Vector<cocos2d::SpriteFrame*> SpriteFrames;
//typedef std::vector<cocos2d::Animation*> Animations;

namespace g3nts {
	class Character {
	public:
		Character();
		Character(cocos2d::Vec2& position, cocos2d::Sprite* sprite);
		Character(cocos2d::Vec2& position, cocos2d::SpriteFrame* spriteFrame);
		Character(cocos2d::Vec2& position, string spritePath);
		~Character();

		const int getZIndex() const;
		const bool isFlexing() const;
		cocos2d::Sprite* getSprite() const;
		cocos2d::Vec2 getPosition() const;
		cocos2d::Vec2 getDirection() const;
		PrimitiveRect getHitbox() const;
		cocos2d::EventListenerKeyboard* getKeyboardListener() const;

		void setPosition(cocos2d::Vec2& position);
		void setPosition(const float x, const float y);
		void setDirection(cocos2d::Vec2& direction);
		void setDirection(const float x, const float y);
		void setFlexing(const bool flexing);
		void setZIndex(const int zIndex);

		void addAnimation(string tag, string file, const unsigned int numFrames);
		void runAnimation(string tag);
		void addToScene(cocos2d::Scene* scene, const int zIndex = 0);
		void update(const float dt);

	private:
		float _characterSpeed = 400.0f;
		bool _flexState = false;
		
		cocos2d::Sprite* _sprite;		
		std::unordered_map<string, cocos2d::Animation*> _animations;

		string _lastDirection = "left";
		string _currentAnimation, _nextAnimation;
		
		PrimitiveRect _hitbox;
		cocos2d::Vec2 _position, _playerDirection;
		
		Input::Keyboard _keyboard;
		cocos2d::EventListenerKeyboard* _keyboardListener;
		

		void initKeyboardListener();
	};
}

#endif