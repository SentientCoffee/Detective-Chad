#pragma once

#include "cocos/math/Vec2.h"

namespace Input {
	struct Mouse {
		cocos2d::Vec2 position;
	};

	struct Keyboard {
		bool keyDown[256];
	};
}