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
		~Mirror();



	private:
		cocos2d::Sprite* _sprite;
		const cocos2d::Vec2 _position;
		PrimitiveRect _hitbox;

	};
}

#endif