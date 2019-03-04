#include "Mirror.h"

USING_NS_CC;

g3nts::Mirror::Mirror() {}
g3nts::Mirror::Mirror(Vec2& position, Sprite* sprite) : _position(position), _sprite(sprite) {
	_sprite->setPosition(_position);
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)),
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);
}
g3nts::Mirror::Mirror(Vec2& position, SpriteFrame* spriteFrame) : Mirror(position, Sprite::createWithSpriteFrame(spriteFrame)) {}
g3nts::Mirror::Mirror(Vec2& position, string spritePath) : Mirror(position, Sprite::create(spritePath)) {}
g3nts::Mirror::~Mirror() {}


Sprite* g3nts::Mirror::getSprite() const { return _sprite; }
g3nts::PrimitiveRect g3nts::Mirror::getHitbox() const { return _hitbox; }
Vec2 g3nts::Mirror::getPosition() const { return _position; }
bool g3nts::Mirror::isBroken() const { return _isBroken; }

void g3nts::Mirror::addToScene(Scene* scene, const int zIndex) {
	scene->addChild(_sprite, zIndex);
	scene->addChild(_hitbox.getNode(), zIndex);
	_hitbox.getNode()->setVisible(false);
}

void g3nts::Mirror::setBroken(const bool isBroken) { _isBroken = isBroken; }
