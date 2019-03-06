#include "Textbox.h"

USING_NS_CC;

g3nts::Textbox::Textbox() {}
g3nts::Textbox::Textbox(Vec2& position, string text, string font, int fontSize, Color4F bgColour, bool isVisible)
: _position(position), _text(text), _isVisible(isVisible), _node(DrawNode::create()) {

	_label = Label::create(text, font, fontSize);
	_label->setPosition(position);
	float labelWidth = _label->getContentSize().width;
	float labelHeight = _label->getContentSize().height;

	_node->drawSolidRect(
		Vec2(position.x - labelWidth / 2.0f, position.y - labelHeight / 2.0f),
		Vec2(position.x + labelWidth / 2.0f, position.y + labelHeight / 2.0f),
		bgColour
	);

	
}
g3nts::Textbox::~Textbox() {}

Vec2 g3nts::Textbox::getPosition() const { return _position; }
string g3nts::Textbox::getText() const { return _text; }
bool g3nts::Textbox::isVisible() const { return _isVisible; }

void g3nts::Textbox::setPosition(Vec2& position) { _position = position; }
void g3nts::Textbox::setText(const string text) { _text = text; }
void g3nts::Textbox::setVisible(const bool isVisible) { _isVisible = isVisible; }

void g3nts::Textbox::addToScene(cocos2d::Scene* scene, const int zIndex) {
	scene->addChild(_node, zIndex);
	scene->addChild(_label, zIndex);

	_node->setVisible(_isVisible);
	_label->setVisible(_isVisible);
}
