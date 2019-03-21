#include "Character.h"

USING_NS_CC;

g3nts::Character::Character() {}
g3nts::Character::Character(cocos2d::Vec2 position, Sprite* sprite) : _position(position), _sprite(sprite) {
	_sprite->setPosition(position);
	_sprite->getTexture()->setAliasTexParameters();
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	_playerDirection = { 0, 0 };

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)),
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width  / 2.0f),
			 _sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);

	initKeyboardListener();
}
g3nts::Character::Character(cocos2d::Vec2 position, SpriteFrame* spriteFrame) : Character(position, Sprite::createWithSpriteFrame(spriteFrame)) {}
g3nts::Character::Character(cocos2d::Vec2 position, string spritePath) : Character(position, Sprite::create(spritePath)) {}

g3nts::Character::~Character() {
	_sprite = nullptr;
	for (auto& it : _animations) {
		it.second->release();
	}
}

const int g3nts::Character::getZIndex() const { return _sprite->getLocalZOrder(); }
const bool g3nts::Character::isFlexing() const { return _flexState; }
Sprite* g3nts::Character::getSprite() const { return _sprite; }
Vec2 g3nts::Character::getPosition() const  { return _position; }
Vec2 g3nts::Character::getDirection() const { return _playerDirection; }
g3nts::PrimitiveRect g3nts::Character::getHitbox() const { return _hitbox; }
EventListenerKeyboard* g3nts::Character::getKeyboardListener() const { return _keyboardListener; }

void g3nts::Character::setPosition(Vec2 position){
	_position = position;
	_sprite->setPosition(position);
	_hitbox.setPosition(position);
}
void g3nts::Character::setPosition(const float x, const float y) { setPosition(Vec2(x, y)); }
void g3nts::Character::setDirection(cocos2d::Vec2 direction) { _playerDirection = direction; }
void g3nts::Character::setDirection(const float x, const float y) { setDirection(Vec2(x, y)); }
void g3nts::Character::setFlexing(const bool flexState) { _flexState = flexState; }
void g3nts::Character::setZIndex(const int zIndex) {
	_sprite->setLocalZOrder(zIndex);
	_hitbox.getNode()->setLocalZOrder(zIndex);
}

void g3nts::Character::initKeyboardListener() {
	_keyboardListener = EventListenerKeyboard::create();
	
	_keyboardListener->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		_keyboard.keyDown[(int)key] = true;
	};
	
	_keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode key, Event* kEvent) {
		_keyboard.keyDown[(int)key] = false;
	};

	for (unsigned int i = 0; i < 256; i++) {
		_keyboard.keyDown[i] = false;
	}
}

void g3nts::Character::addAnimation(string tag, string file, const unsigned int numFrames) {
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

void g3nts::Character::runAnimation(string tag) {
	Animate* animate = createAnimate(tag);
	_sprite->runAction(animate);
}

cocos2d::Animate* g3nts::Character::createAnimate(string tag) {
	Animate* animate = Animate::create(_animations[tag]->clone());
	animate->setTag('anim');
	return animate;
}

void g3nts::Character::addToScene(Scene* scene, const int zIndex) {
	scene->addChild(_sprite, zIndex);
	scene->addChild(_hitbox.getNode(), zIndex);
	_hitbox.getNode()->setVisible(false);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener->clone(), scene);
}

void g3nts::Character::update(const float dt) {
	typedef EventKeyboard::KeyCode KB;

	// PLAYER MOVEMENT
	_playerDirection = { 0, 0 };
	// Up and right (W + D)
	if (_keyboard.keyDown[(int)KB::KEY_W] && _keyboard.keyDown[(int)KB::KEY_D]) {
		_playerDirection = { 1, 1 };
		_lastDirection = "upRight";
	}
	// Up and left (W + A)
	else if (_keyboard.keyDown[(int)KB::KEY_W] && _keyboard.keyDown[(int)KB::KEY_A]) {
		_playerDirection = { -1, 1 };
		_lastDirection = "upLeft";
	}
	// Down and right (S + D)
	else if (_keyboard.keyDown[(int)KB::KEY_S] && _keyboard.keyDown[(int)KB::KEY_D]) {
		_playerDirection = { 1, -1 };
		_lastDirection = "downRight";
	}
	// Down and left (S + A)
	else if (_keyboard.keyDown[(int)KB::KEY_S] && _keyboard.keyDown[(int)KB::KEY_A]) {
		_playerDirection = { -1, -1 };
		_lastDirection = "downLeft";
	}
	// Up (W)
	else if (_keyboard.keyDown[(int)KB::KEY_W]) {
		_playerDirection = { 0, 1 };
		_lastDirection = "up";
	}
	// Down (S)
	else if (_keyboard.keyDown[(int)KB::KEY_S]) {
		_playerDirection = { 0, -1 };
		_lastDirection = "down";
	}
	// Right (D)
	else if (_keyboard.keyDown[(int)KB::KEY_D]) {
		_playerDirection = { 1, 0 };
		_lastDirection = "right";
	}
	// Left (A)
	else if (_keyboard.keyDown[(int)KB::KEY_A]) {
		_playerDirection = { -1, 0 };
		_lastDirection = "left";
	}

	// Check if Chad is flexing
	if (_flexState) {
		if (_sprite->getNumberOfRunningActionsByTag('anim') == 0) _flexState = false;
		else _nextAnimation = "flex";
	}
	else {
		_position += _playerDirection.getNormalized() * _characterSpeed * dt;
		_sprite->setPosition(_position);
		_hitbox.setPosition(_position);

		_nextAnimation = _lastDirection;
		if (_playerDirection.getLengthSq() != 0) _nextAnimation += "Walk";
		else _nextAnimation += "Idle";
	}
	
	// Check for animations that are running and run the proper one
	if (_currentAnimation != _nextAnimation || _sprite->getNumberOfRunningActionsByTag('anim') == 0) {
		
		_currentAnimation = _nextAnimation;
		_sprite->stopAllActionsByTag('anim');
		runAnimation(_currentAnimation);
	}

}



