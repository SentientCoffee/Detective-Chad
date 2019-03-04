#pragma once

#ifndef __MIRROR_H__
#define __MIRROR_H__

#include "cocos2d.h"
#include "Primitives.h"

typedef std::string string;

namespace g3nts {
	class Mirror {
	public:

		Mirror();
		Mirror(cocos2d::Vec2& position, cocos2d::Sprite* sprite);
		Mirror(cocos2d::Vec2& position, cocos2d::SpriteFrame* spriteFrame);
		Mirror(cocos2d::Vec2& position, string spritePath);
		~Mirror();

		cocos2d::Sprite* getSprite() const;
		PrimitiveRect getHitbox() const;
		cocos2d::Vec2 getPosition() const;
		bool isBroken() const;

		void setBroken(const bool isBroken);
		
		void addToScene(cocos2d::Scene* scene, const int zIndex = 0);

	private:

		cocos2d::Sprite* _sprite;
		PrimitiveRect _hitbox;
		const cocos2d::Vec2 _position;

		bool _isBroken = false;
	};
}

#endif