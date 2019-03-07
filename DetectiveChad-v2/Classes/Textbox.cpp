#include "Textbox.h"

USING_NS_CC;

g3nts::Textbox::Textbox() {}
g3nts::Textbox::Textbox(Vec2& position, string text, string font, unsigned int fontSize, Color4F& bgColour)
: _position(position), _text(text), _bgColour(bgColour), _node(DrawNode::create()) {
	_label = Label::create(text, font, fontSize);
	_label->setPosition(position);

	_labelWidth = _label->getContentSize().width;
	_labelHeight = _label->getContentSize().height;

	_node->drawSolidRect(
		Vec2(-_labelWidth / 2.0f - 10, -_labelHeight / 2.0f - 10),
		Vec2( _labelWidth / 2.0f + 10,  _labelHeight / 2.0f + 10),
		bgColour
	);

	_node->setPosition(position);
	
}
g3nts::Textbox::~Textbox() {}

Vec2 g3nts::Textbox::getPosition() const { return _position; }
string g3nts::Textbox::getText() const { return _text; }
bool g3nts::Textbox::isVisible() const { return _isVisible; }

void g3nts::Textbox::setPosition(Vec2& position) {
	_position = position;
	_label->setPosition(position);
	_node->setPosition(position);
}
void g3nts::Textbox::setBackgroundColour(cocos2d::Color4F& colour) {
	_bgColour = colour;

	_node->clear();
	_node->drawSolidRect(
		Vec2(-_labelWidth / 2.0f - 10, -_labelHeight / 2.0f - 10),
		Vec2(_labelWidth / 2.0f + 10, _labelHeight / 2.0f + 10),
		colour
	);
}

void g3nts::Textbox::setText(const string text) {
	_text = text;
	_label->setString(_text);
	_labelWidth = _label->getContentSize().width;
	_labelHeight = _label->getContentSize().height;

	_node->clear();
	_node->drawSolidRect(
		Vec2(-_labelWidth / 2.0f - 10, -_labelHeight / 2.0f - 10),
		Vec2(_labelWidth / 2.0f + 10, _labelHeight / 2.0f + 10),
		_bgColour
	);
}
void g3nts::Textbox::setVisible(const bool isVisible) {
	_isVisible = isVisible;
	_node->setVisible(isVisible);
	_label->setVisible(isVisible);
}

void g3nts::Textbox::addToScene(cocos2d::Scene* scene, const int zIndex) {
	scene->addChild(_node, zIndex);
	scene->addChild(_label, zIndex);
}
