#pragma once

#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include "cocos2d.h"

typedef std::string string;

namespace g3nts {
	class Textbox {
	public:

		Textbox();
		Textbox(cocos2d::Vec2& position, string text, string font = "fonts/Marker Felt.ttf", unsigned int fontSize = 36, cocos2d::Color4F& bgColour = cocos2d::Color4F(1, 0, 0, 1));
		~Textbox();

		cocos2d::Vec2 getPosition() const;
		string getText() const;
		bool isVisible() const;

		void setPosition(cocos2d::Vec2& position);
		void setBackgroundColour(cocos2d::Color4F& colour);
		void setText(const string text);
		void setVisible(const bool isVisible);

		void addToScene(cocos2d::Scene* scene, const int zIndex = 0);

	private:

		cocos2d::DrawNode* _node;
		cocos2d::Color4F _bgColour;
		cocos2d::Vec2 _position;

		cocos2d::Label* _label;
		string _text;

		float _labelWidth;
		float _labelHeight;
		bool _isVisible;

	};
}

#endif