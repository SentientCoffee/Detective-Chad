#include "Item.h"

USING_NS_CC;

int g3nts::Item::idCount = 0;

g3nts::Item::Item() {}
g3nts::Item::Item(Vec2& position, string spritePath, const bool isBreakable) : _id(idCount++), _isBreakable(isBreakable), _position(position), _sprite(Sprite::create(spritePath)) {
	_sprite->setPosition(position);
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)),
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);
}

g3nts::Item::~Item() { _sprite = nullptr; }

bool g3nts::Item::operator<(const Item& item)  { return _id < item._id; }
bool g3nts::Item::operator>(const Item& item)  { return _id > item._id; }
bool g3nts::Item::operator==(const Item& item) { return _id == item._id; }
bool g3nts::Item::operator!=(const Item& item) { return _id != item._id; }

Sprite* g3nts::Item::getSprite() const { return _sprite; }
g3nts::PrimitiveRect g3nts::Item::getHitbox() const { return _hitbox; }

Vec2 g3nts::Item::getAcceleration() const { return _acceleration; }
Vec2 g3nts::Item::getVelocity() const { return _velocity; }
Vec2 g3nts::Item::getPosition() const { return _position; }

bool g3nts::Item::isBreakable() const { return _isBreakable; }
void g3nts::Item::setBreakable(const bool isBreakable) { _isBreakable = isBreakable; }

void g3nts::Item::addForce(cocos2d::Vec2& force) { _acceleration = force; }
void g3nts::Item::setVelocity(cocos2d::Vec2& velocity) { _velocity = velocity; }
void g3nts::Item::setPosition(Vec2& position) { _position = position; }

void g3nts::Item::addToScene(Scene* scene, const int zIndex) {
	scene->addChild(_sprite, zIndex);
	scene->addChild(_hitbox.getNode(), zIndex);
	_hitbox.getNode()->setVisible(false);
}

void g3nts::Item::update(const float dt) {
	// Add friction to already moving objects
	if (_velocity.getLengthSq() > 25.0f) {
		_acceleration = -(_velocity.getNormalized() * 1000.0f);
	}
	else {
		_acceleration = Vec2(0, 0);
		_velocity = Vec2(0, 0);
	}
	
	// Clamp acceleration
	if (_acceleration.getLengthSq() > _maxAccel * _maxAccel) {
		_acceleration = _acceleration.getNormalized() * _maxAccel;
	}

	// Add acceleration to velocity
	_velocity += _acceleration * dt;
	// Clamp velocity
	if (_velocity.getLengthSq() > _maxVelocity * _maxVelocity) {
		_velocity = _velocity.getNormalized() * _maxVelocity;
	}

	// Set position
	_position += _velocity * dt;

	// Set the position of the player to the new calculated position
	_sprite->setPosition(_position);
	_hitbox.setPosition(_position);
	
	// Reset acceleration
	_acceleration = Vec2(0, 0);
}