#include "Item.h"

USING_NS_CC;

int g3nts::Item::idCount = 0;

g3nts::Item::Item() {}
g3nts::Item::Item(Vec2 position, Sprite* sprite, const bool isBreakable, const string tag)
: _id(idCount++), _isBreakable(isBreakable), _position(position), _sprite(sprite), _tag(tag) {
	_sprite->setPosition(position);
	_sprite->getTexture()->setAliasTexParameters();
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)),
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);
}

g3nts::Item::Item(cocos2d::Vec2 position, string spritePath, const bool isBreakable, const string tag)
	: Item(position, Sprite::create(spritePath), isBreakable, tag) {}
g3nts::Item::Item(cocos2d::Vec2 position, cocos2d::SpriteFrame* spriteFrame, const bool isBreakable, const string tag)
	: Item(position, Sprite::createWithSpriteFrame(spriteFrame), isBreakable, tag) {}
g3nts::Item::Item(const Item& item)
	: Item(item._position, Sprite::createWithSpriteFrame(item._sprite->getSpriteFrame()), item._isBreakable, item._tag) {}
g3nts::Item::~Item() { _sprite = nullptr; }

bool g3nts::Item::operator<(const Item& item)  { return _id < item._id; }
bool g3nts::Item::operator>(const Item& item)  { return _id > item._id; }
bool g3nts::Item::operator==(const Item& item) { return _id == item._id; }
bool g3nts::Item::operator!=(const Item& item) { return _id != item._id; }

string g3nts::Item::getTag() const { return _tag; }
void g3nts::Item::setTag(const string tag) { _tag = tag; }

Sprite* g3nts::Item::getSprite() const { return _sprite; }
g3nts::PrimitiveRect g3nts::Item::getHitbox() const { return _hitbox; }
const int g3nts::Item::getZIndex() const { return _sprite->getLocalZOrder(); }

Vec2 g3nts::Item::getAcceleration() const { return _acceleration; }
Vec2 g3nts::Item::getVelocity() const { return _velocity; }
Vec2 g3nts::Item::getPosition() const { return _position; }

bool g3nts::Item::isBreakable() const { return _isBreakable; }
bool g3nts::Item::isVisible() const { return _isVisible; }
void g3nts::Item::setBreakable(const bool isBreakable) { _isBreakable = isBreakable; }
void g3nts::Item::setVisible(const bool isVisible) {
	_isVisible = isVisible;
	_sprite->setVisible(isVisible);
}

void g3nts::Item::addForce(cocos2d::Vec2 force) { _acceleration = force; }
void g3nts::Item::setVelocity(cocos2d::Vec2 velocity) { _velocity = velocity; }
void g3nts::Item::setPosition(Vec2 position) {
	_position = position;
	_sprite->setPosition(position);
	_hitbox.setPosition(position);
}

void g3nts::Item::setZIndex(const int zIndex) {
	_sprite->setLocalZOrder(zIndex);
	_hitbox.getNode()->setLocalZOrder(zIndex);
}

void g3nts::Item::addAnimation(string tag, string file, const unsigned int numFrames) {
	SpriteFrameCache* spriteCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frames;
	char name[100];

	for (unsigned int i = 1; i <= numFrames; ++i) {
		sprintf(name, file.c_str(), i);
		frames.pushBack(spriteCache->getSpriteFrameByName(name));
	}

	Animation* anim = Animation::createWithSpriteFrames(frames, 1.0f / numFrames * 0.5);
	anim->setLoops(1);

	_animations[tag] = anim;
	_animations[tag]->retain();
}

void g3nts::Item::runAnimation(string tag) {
	Animate* animate = createAnimate(tag);
	_sprite->runAction(animate);
}

cocos2d::Animate * g3nts::Item::createAnimate(string tag) {
	Animate* animate = Animate::create(_animations[tag]->clone());
	animate->setTag('anim');
	return animate;
}

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
		_acceleration = { 0, 0 };
		_velocity = { 0, 0 };
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
	_acceleration = { 0, 0 };

}