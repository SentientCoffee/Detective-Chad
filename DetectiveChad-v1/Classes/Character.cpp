#include "Character.h"

USING_NS_CC;

g3nts::Character::Character() {}
g3nts::Character::Character(Vec2& position, string spritePath) : _position(position), _sprite(Sprite::create(spritePath)) {
	_sprite->setPosition(position);
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width / 2.0f),
			 _sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)), 
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width / 2.0f),
			 _sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);
}

g3nts::Character::~Character() { _sprite = nullptr; }

Sprite* g3nts::Character::getSprite() const { return _sprite; }
Vec2 g3nts::Character::getPosition() const  { return _position; }
g3nts::PrimitiveRect g3nts::Character::getHitbox() const { return _hitbox; }

void g3nts::Character::setPosition(Vec2& position){
	_position = position;
	_sprite->setPosition(position);
	_hitbox.setPosition(position);
}
void g3nts::Character::setPosition(const float x, const float y) { setPosition(Vec2(x, y)); }

void g3nts::Character::addToScene(Scene* scene) {
	scene->addChild(_sprite);
	scene->addChild(_hitbox.getNode());
	_hitbox.getNode()->setVisible(false);
}
