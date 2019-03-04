#include "Mirror.h"

USING_NS_CC;

g3nts::Mirror::Mirror() {}
g3nts::Mirror::Mirror(Vec2& position, Sprite* sprite) : _position(position), _sprite(sprite) {
	_sprite->setPosition(_position);
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width / 2.0f),
			_sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)),
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width / 2.0f),
			_sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);
}
g3nts::Mirror::Mirror(cocos2d::Vec2& position, cocos2d::SpriteFrame* spriteFrame) : Mirror(position, Sprite::createWithSpriteFrame(spriteFrame)) {}
g3nts::Mirror::~Mirror() {}
