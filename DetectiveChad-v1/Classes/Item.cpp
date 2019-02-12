#include "Item.h"

USING_NS_CC;

int g3nts::Item::idCount = 0;

g3nts::Item::Item() {}
g3nts::Item::Item(Vec2& position, string spritePath) : _id(idCount++), _position(position), _sprite(Sprite::create(spritePath)) {
	_sprite->setPosition(position);
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width / 2.0f),
			_sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)),
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width / 2.0f),
			_sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);
}

g3nts::Item::~Item() { _sprite = nullptr; }

bool g3nts::Item::operator<(const Item& item)  { return _id < item._id; }
bool g3nts::Item::operator>(const Item& item)  { return _id > item._id; }
bool g3nts::Item::operator==(const Item& item) { return _id == item._id; }
bool g3nts::Item::operator!=(const Item& item) { return _id != item._id; }

Sprite* g3nts::Item::getSprite() const { return _sprite; }
Vec2 g3nts::Item::getPosition() const  { return _position; }
g3nts::PrimitiveRect g3nts::Item::getHitbox() const { return _hitbox; }

void g3nts::Item::addToScene(Scene* scene) {
	scene->addChild(_sprite);
	scene->addChild(_hitbox.getNode());
	_hitbox.getNode()->setVisible(false);
}

void g3nts::Item::setPosition(Vec2& position) {
	_position = position;
	_sprite->setPosition(position);
	_hitbox.setPosition(position);
}

void g3nts::Item::setPosition(const float x, const float y) { setPosition(Vec2(x, y)); }