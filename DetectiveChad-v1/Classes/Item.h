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
		Item(cocos2d::Vec2& position, string spritePath);
		~Item();

		bool operator<(const Item& item);
		bool operator>(const Item& item);
		bool operator==(const Item& item);
		bool operator!=(const Item& item);

		cocos2d::Sprite* getSprite() const;
		cocos2d::Vec2 getPosition() const;
		PrimitiveRect getHitbox() const;

		void addToScene(cocos2d::Scene* scene);

		void setPosition(cocos2d::Vec2& position);
		void setPosition(const float x, const float y);

	private:

		cocos2d::Sprite* _sprite;
		PrimitiveRect _hitbox;
		cocos2d::Vec2 _position;

		int _id;
		static int idCount;
	};
}

#endif