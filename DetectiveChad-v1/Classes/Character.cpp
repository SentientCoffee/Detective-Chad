#include "Character.h"

USING_NS_CC;

g3nts::Character::Character() {}
g3nts::Character::Character(Vec2& position, string spritePath) : _position(position), _sprite(Sprite::create(spritePath)) {
	_sprite->setPosition(position);
	_sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	_playerDirection = Vec2(0, 0);

	_hitbox = g3nts::PrimitiveRect(
		Vec2(_sprite->getPosition().x - (_sprite->getContentSize().width / 2.0f),
			 _sprite->getPosition().y - (_sprite->getContentSize().height / 2.0f)), 
		Vec2(_sprite->getPosition().x + (_sprite->getContentSize().width / 2.0f),
			 _sprite->getPosition().y + (_sprite->getContentSize().height / 2.0f))
	);

	initKeyboardListener();
}

g3nts::Character::~Character() { _sprite = nullptr; }

Sprite* g3nts::Character::getSprite() const { return _sprite; }
Vec2 g3nts::Character::getPosition() const  { return _position; }
Vec2 g3nts::Character::getDirection() const { return _playerDirection; }
g3nts::PrimitiveRect g3nts::Character::getHitbox() const { return _hitbox; }

void g3nts::Character::setPosition(Vec2& position){
	_position = position;
	_sprite->setPosition(position);
	_hitbox.setPosition(position);
}
void g3nts::Character::setPosition(const float x, const float y) { setPosition(Vec2(x, y)); }

void g3nts::Character::setDirection(cocos2d::Vec2& direction) { _playerDirection = direction; }
void g3nts::Character::setDirection(const float x, const float y) { setDirection(Vec2(x, y)); }

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

void g3nts::Character::addToScene(Scene* scene) {
	scene->addChild(_sprite);
	scene->addChild(_hitbox.getNode());
	_hitbox.getNode()->setVisible(false);
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_keyboardListener->clone(), scene);
}

void g3nts::Character::update(const float dt) {
	typedef EventKeyboard::KeyCode KB;

	// PLAYER MOVEMENT
	_playerDirection = Vec2(0, 0);
	// Up and right (W + D)
	if (_keyboard.keyDown[(int)KB::KEY_W] && _keyboard.keyDown[(int)KB::KEY_D]) {
		_playerDirection = Vec2(1, 1);
		_sprite->setTexture("characters/chad/chad-up-right.png");
	}
	// Up and left (W + A)
	else if (_keyboard.keyDown[(int)KB::KEY_W] && _keyboard.keyDown[(int)KB::KEY_A]) {
		_playerDirection = Vec2(-1, 1);
		_sprite->setTexture("characters/chad/chad-up-left.png");
	}
	// Down and right (S + D)
	else if (_keyboard.keyDown[(int)KB::KEY_S] && _keyboard.keyDown[(int)KB::KEY_D]) {
		_playerDirection = Vec2(1, -1);
		_sprite->setTexture("characters/chad/chad-down-right.png");
	}
	// Down and left (S + A)
	else if (_keyboard.keyDown[(int)KB::KEY_S] && _keyboard.keyDown[(int)KB::KEY_A]) {
		_playerDirection = Vec2(-1, -1);
		_sprite->setTexture("characters/chad/chad-down-left.png");
	}
	// Up (W)
	else if (_keyboard.keyDown[(int)KB::KEY_W]) {
		_playerDirection = Vec2(0, 1);
		_sprite->setTexture("characters/chad/chad-up.png");
	}
	// Down (S)
	else if (_keyboard.keyDown[(int)KB::KEY_S]) {
		_playerDirection = Vec2(0, -1);
		_sprite->setTexture("characters/chad/chad-down.png");
	}
	// Left (A)
	else if (_keyboard.keyDown[(int)KB::KEY_D]) {
		_playerDirection = Vec2(1, 0);
		_sprite->setTexture("characters/chad/chad-right.png");
	}
	// Right (D)
	else if (_keyboard.keyDown[(int)KB::KEY_A]) {
		_playerDirection = Vec2(-1, 0);
		_sprite->setTexture("characters/chad/chad-left.png");
	}

	_position += _playerDirection.getNormalized() * _characterSpeed * dt;

}

