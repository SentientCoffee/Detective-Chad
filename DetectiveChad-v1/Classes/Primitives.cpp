#include "Primitives.h"

// DEFAULT CONSTRUCTORS
g3nts::PrimitiveRect::PrimitiveRect() {}
g3nts::PrimitiveCircle::PrimitiveCircle() {}
g3nts::PrimitiveLine::PrimitiveLine() {}
g3nts::PrimitiveCapsule::PrimitiveCapsule() {}



// CONSTRUCTORS WITH PARAMETERS
g3nts::PrimitiveRect::PrimitiveRect(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos, const cocos2d::Color4F& colour)
: _node(cocos2d::DrawNode::create()), _startPos(startPos), _endPos(endPos), _colour(colour) 
{ _node->drawRect(startPos, endPos, colour); }

g3nts::PrimitiveRect::PrimitiveRect(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos)
: PrimitiveRect(startPos, endPos, cocos2d::Color4F(1, 0, 0, 1)) {}

cocos2d::Vec2 g3nts::PrimitiveRect::getStartPosition() const  { return _startPos; }
cocos2d::Vec2 g3nts::PrimitiveRect::getEndPosition() const    { return _endPos; }
cocos2d::Vec2 g3nts::PrimitiveRect::getCentrePosition() const { return _startPos + (_endPos - _startPos) / 2.0f; }

float g3nts::PrimitiveRect::getWidth() const  { return _endPos.x - _startPos.x; }
float g3nts::PrimitiveRect::getHeight() const { return _endPos.y - _startPos.y; }

void g3nts::PrimitiveRect::setStartPosition(cocos2d::Vec2& startPos) {
	_startPos = startPos;
	redraw();
}

void g3nts::PrimitiveRect::setEndPosition(cocos2d::Vec2& endPos) {
	_endPos = endPos;
	redraw();
}

void g3nts::PrimitiveRect::setPosition(cocos2d::Vec2& centrePos) {
	_startPos.x = centrePos.x - (getWidth() / 2.0f);
	_startPos.y = centrePos.y - (getHeight() / 2.0f);
	_endPos.x = centrePos.x + (getWidth() / 2.0f);
	_endPos.y = centrePos.y + (getHeight() / 2.0f);
	redraw();
}

void g3nts::PrimitiveRect::setPosition(cocos2d::Vec2& startPos, cocos2d::Vec2& endPos) {
	_startPos = startPos;
	_endPos = endPos;
	redraw();
}

void g3nts::PrimitiveRect::setColour(cocos2d::Color4F& colour) {
	_colour = colour;
	redraw();
}

void g3nts::PrimitiveRect::redraw() {
	_node->clear();
	_node->drawRect(_startPos, _endPos, _colour);
}





g3nts::PrimitiveCircle::PrimitiveCircle(const cocos2d::Vec2& centrePos, const float radius, const float angle, const unsigned int segments, const bool drawRadius, const cocos2d::Color4F& colour)
: _node(cocos2d::DrawNode::create()), _position(centrePos), _radius(radius), _angle(angle), _segments(segments), _drawRadius(drawRadius), _colour(colour)
{ _node->drawCircle(centrePos, radius, angle, segments, drawRadius, colour); }

g3nts::PrimitiveCircle::PrimitiveCircle(const cocos2d::Vec2& centrePos, const float radius, const cocos2d::Color4F& colour)
: PrimitiveCircle(centrePos, radius, 1.0f, 20, false, colour) {}

g3nts::PrimitiveCircle::PrimitiveCircle(const cocos2d::Vec2& centrePos, const float radius)
: PrimitiveCircle(centrePos, radius, 1.0f, 20, false, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f)) {}

cocos2d::Vec2 g3nts::PrimitiveCircle::getPosition() const { return _position; }
float g3nts::PrimitiveCircle::getRadius() const			  { return _radius; }

void g3nts::PrimitiveCircle::setPosition(cocos2d::Vec2& position) {
	_position = position;
	redraw();
}

void g3nts::PrimitiveCircle::setRadius(const float radius) {
	_radius = radius;
	redraw();
}

void g3nts::PrimitiveCircle::setAngle(const float angle) {
	_angle = angle;
	redraw();
}

void g3nts::PrimitiveCircle::setSegments(const unsigned int segments) {
	_segments = segments;
	redraw();
}

void g3nts::PrimitiveCircle::setDrawRadius(const bool drawRadius) {
	_drawRadius = drawRadius;
	redraw();
}

void g3nts::PrimitiveCircle::setColour(cocos2d::Color4F& colour) {
	_colour = colour;
	redraw();
}

void g3nts::PrimitiveCircle::redraw() {
	_node->clear();
	_node->drawCircle(_position, _radius, _angle, _segments, _drawRadius, _colour);
}




g3nts::PrimitiveLine::PrimitiveLine(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos, const cocos2d::Color4F& colour)
: _node(cocos2d::DrawNode::create()), _startPos(startPos), _endPos(endPos), _colour(colour)
{ _node->drawLine(startPos, endPos, colour); }

g3nts::PrimitiveLine::PrimitiveLine(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos)
: PrimitiveLine(startPos, endPos, cocos2d::Color4F(1, 0, 0, 1)) {}

cocos2d::Vec2 g3nts::PrimitiveLine::getStartPosition() const { return _startPos; }
cocos2d::Vec2 g3nts::PrimitiveLine::getEndPosition() const   { return _endPos; }

void g3nts::PrimitiveLine::setStartPosition(cocos2d::Vec2& startPos) {
	_startPos = startPos;
	redraw();
}

void g3nts::PrimitiveLine::setEndPosition(cocos2d::Vec2& endPos) {
	_endPos = endPos;
	redraw();
}

void g3nts::PrimitiveLine::setColour(cocos2d::Color4F& colour) {
	_colour = colour;
	redraw();
}

void g3nts::PrimitiveLine::redraw() {
	_node->clear();
	_node->drawLine(_startPos, _endPos, _colour);
}



g3nts::PrimitiveCapsule::PrimitiveCapsule(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos, const float radius, const cocos2d::Color4F& colour)
: _node(cocos2d::DrawNode::create()), _startPos(startPos), _endPos(endPos), _radius(radius), _colour(colour) {
	cocos2d::Vec2 direction = startPos - endPos;
	cocos2d::Vec2 normal = { direction.y, -direction.x };

	_node->drawCircle(startPos + (direction.getNormalized() * radius), radius, 1.0f, 40, false, colour);
	_node->drawCircle(endPos - (direction.getNormalized() * radius), radius, 1.0f, 40, false, colour);
	_node->drawLine(startPos + (normal.getNormalized() * radius), endPos + (normal.getNormalized() * radius), colour);
	_node->drawLine(startPos - (normal.getNormalized() * radius), endPos - (normal.getNormalized() * radius), colour);
}

g3nts::PrimitiveCapsule::PrimitiveCapsule(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos, const float radius)
: PrimitiveCapsule(startPos, endPos, radius, cocos2d::Color4F(1, 0, 0, 1)) {}

cocos2d::Vec2 g3nts::PrimitiveCapsule::getStartPosition() const { return _startPos; }
cocos2d::Vec2 g3nts::PrimitiveCapsule::getEndPosition() const   { return _endPos; }
float g3nts::PrimitiveCapsule::getRadius() const { return _radius; }

void g3nts::PrimitiveCapsule::redraw() {
	cocos2d::Vec2 direction = _startPos - _endPos;
	cocos2d::Vec2 normal = { direction.y, -direction.x };

	_node->clear();
	_node->drawCircle(_startPos + (direction.getNormalized() * _radius), _radius, 1.0f, 40, false, _colour);
	_node->drawCircle(_endPos - (direction.getNormalized() * _radius), _radius, 1.0f, 40, false, _colour);
	_node->drawLine(_startPos + (normal.getNormalized() * _radius), _endPos + (normal.getNormalized() * _radius), _colour);
	_node->drawLine(_startPos - (normal.getNormalized() * _radius), _endPos - (normal.getNormalized() * _radius), _colour);
}




// NODE GETTERS (SO WE CAN ADD TO THE SCREEN)
cocos2d::DrawNode* g3nts::PrimitiveRect::getNode() const    { return _node; }
cocos2d::DrawNode* g3nts::PrimitiveCircle::getNode() const  { return _node; }
cocos2d::DrawNode* g3nts::PrimitiveLine::getNode() const    { return _node; }
cocos2d::DrawNode* g3nts::PrimitiveCapsule::getNode() const { return _node; }


bool g3nts::isColliding(g3nts::PrimitiveCircle& c1, g3nts::PrimitiveCircle& c2) {
	cocos2d::Vec2 distance = c1.getPosition() - c2.getPosition();
	float squaredDistance = (distance.x * distance.x) + (distance.y * distance.y);
	float squaredRadii = (c1.getRadius() * c1.getRadius()) + (c2.getRadius() * c2.getRadius());

	if (squaredDistance <= squaredRadii) return true;
	return false;
}

bool g3nts::isColliding(g3nts::PrimitiveRect& r1, g3nts::PrimitiveCircle& c2) {
	cocos2d::Vec2 test;

	if (c2.getPosition().x < r1.getStartPosition().x) test.x = r1.getStartPosition().x;
	else if (c2.getPosition().x > r1.getEndPosition().x) test.x = r1.getEndPosition().x;
	else test.x = c2.getPosition().x;

	if (c2.getPosition().y < r1.getStartPosition().y) test.y = r1.getStartPosition().y;
	else if (c2.getPosition().y > r1.getEndPosition().y) test.y = r1.getEndPosition().y;
	else test.y = c2.getPosition().y;

	float distanceSq = test.getDistanceSq(c2.getPosition());
	return distanceSq <= (c2.getRadius() * c2.getRadius());
}

bool g3nts::isColliding(g3nts::PrimitiveCircle& c1, g3nts::PrimitiveRect& r2) { return isColliding(r2, c1); }

bool g3nts::isColliding(g3nts::PrimitiveRect& r1, g3nts::PrimitiveRect& r2) {
	if (r1.getStartPosition().x > r2.getEndPosition().x || r1.getEndPosition().x < r2.getStartPosition().x) return false;
	if (r1.getStartPosition().y > r2.getEndPosition().y || r1.getEndPosition().y < r2.getStartPosition().y) return false;
	
	return true;
}
