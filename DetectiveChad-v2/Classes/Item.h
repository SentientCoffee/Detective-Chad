#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Primitives.h"

typedef std::string string;

namespace g3nts {
	class Item {
	public:

		Item();
		Item(cocos2d::Vec2& position, string spritePath, const bool isBreakable = false);
		~Item();

		bool operator<(const Item& item);
		bool operator>(const Item& item);
		bool operator==(const Item& item);
		bool operator!=(const Item& item);

		cocos2d::Sprite* getSprite() const;
		PrimitiveRect getHitbox() const;
		const int getZIndex() const;

		cocos2d::Vec2 getAcceleration() const;
		cocos2d::Vec2 getVelocity() const;
		cocos2d::Vec2 getPosition() const;

		bool isBreakable() const;
		void setBreakable(const bool isBreakable);

		void addForce(cocos2d::Vec2& force);
		void setVelocity(cocos2d::Vec2& velocity);
		void setPosition(cocos2d::Vec2& position);
		void setZIndex(const int zIndex);

		void addToScene(cocos2d::Scene* scene, const int zIndex = 0);
		void update(const float dt);

	private:

		cocos2d::Sprite* _sprite;
		PrimitiveRect _hitbox;

		cocos2d::Vec2 _acceleration;
		cocos2d::Vec2 _velocity;
		cocos2d::Vec2 _position;

		float _maxVelocity = 500.0f, _maxAccel = 1000.0f;
		bool _isBreakable;

		int _id;
		static int idCount;
	};
}

#endif