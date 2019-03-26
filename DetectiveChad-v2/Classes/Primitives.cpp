#include "Primitives.h"

USING_NS_CC;

// DEFAULT CONSTRUCTORS
g3nts::PrimitiveRect::PrimitiveRect() {}
g3nts::PrimitiveCircle::PrimitiveCircle() {}
g3nts::PrimitiveLine::PrimitiveLine() {}
g3nts::PrimitiveCapsule::PrimitiveCapsule() {}


// CONSTRUCTORS WITH PARAMETERS
g3nts::PrimitiveRect::PrimitiveRect(const Vec2& startPos, const Vec2& endPos, const Color4F& colour, const bool filled)
: _node(DrawNode::create()), _startPos(startPos), _endPos(endPos), _colour(colour), _filled(filled)
{
	if (filled) {
		_node->drawSolidRect(startPos, endPos, colour);
	}
	else {
		_node->drawRect(startPos, endPos, colour);
	}
}

Vec2 g3nts::PrimitiveRect::getStartPosition() const  { return _startPos; }
Vec2 g3nts::PrimitiveRect::getEndPosition() const    { return _endPos; }
Vec2 g3nts::PrimitiveRect::getCentrePosition() const { return _startPos + (_endPos - _startPos) / 2.0f; }

float g3nts::PrimitiveRect::getWidth() const  {
	float width = _endPos.x - _startPos.x;
	return width > 0.0f ? width : -width;
}
float g3nts::PrimitiveRect::getHeight() const {
	float height = _endPos.y - _startPos.y;
	return height > 0.0f ? height : -height;
}

void g3nts::PrimitiveRect::setStartPosition(Vec2& startPos) {
	_startPos = startPos;
	redraw();
}

void g3nts::PrimitiveRect::setEndPosition(Vec2& endPos) {
	_endPos = endPos;
	redraw();
}

void g3nts::PrimitiveRect::setPosition(Vec2& centrePos) {
	float width = getWidth();
	float height = getHeight();

	_startPos.x = centrePos.x - (width / 2.0f);
	_startPos.y = centrePos.y - (height / 2.0f);
	_endPos.x = centrePos.x + (width / 2.0f);
	_endPos.y = centrePos.y + (height / 2.0f);

	redraw();
}

void g3nts::PrimitiveRect::setPosition(Vec2& startPos, Vec2& endPos) {
	_startPos = startPos;
	_endPos = endPos;
	redraw();
}

void g3nts::PrimitiveRect::setColour(Color4F& colour) {
	_colour = colour;
	redraw();
}

void g3nts::PrimitiveRect::redraw() {
	_node->clear();

	if (_filled) {
		_node->drawSolidRect(_startPos, _endPos, _colour);
	}
	else {
		_node->drawRect(_startPos, _endPos, _colour);
	}
}





g3nts::PrimitiveCircle::PrimitiveCircle(const Vec2& centrePos, const float radius, const float angle, const unsigned int segments, const bool drawRadius, const Color4F& colour)
: _node(DrawNode::create()), _position(centrePos), _radius(radius), _angle(angle), _segments(segments), _drawRadius(drawRadius), _colour(colour)
{ _node->drawCircle(centrePos, radius, angle, segments, drawRadius, colour); }

Vec2 g3nts::PrimitiveCircle::getPosition() const { return _position; }
float g3nts::PrimitiveCircle::getRadius() const			  { return _radius; }

void g3nts::PrimitiveCircle::setPosition(Vec2& position) {
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

void g3nts::PrimitiveCircle::setColour(Color4F& colour) {
	_colour = colour;
	redraw();
}

void g3nts::PrimitiveCircle::redraw() {
	_node->clear();
	_node->drawCircle(_position, _radius, _angle, _segments, _drawRadius, _colour);
}




g3nts::PrimitiveLine::PrimitiveLine(const Vec2& startPos, const Vec2& endPos, const Color4F& colour)
: _node(DrawNode::create()), _startPos(startPos), _endPos(endPos), _colour(colour)
{ _node->drawLine(startPos, endPos, colour); }

Vec2 g3nts::PrimitiveLine::getStartPosition() const { return _startPos; }
Vec2 g3nts::PrimitiveLine::getEndPosition() const   { return _endPos; }

void g3nts::PrimitiveLine::setStartPosition(Vec2& startPos) {
	_startPos = startPos;
	redraw();
}

void g3nts::PrimitiveLine::setEndPosition(Vec2& endPos) {
	_endPos = endPos;
	redraw();
}

void g3nts::PrimitiveLine::setColour(Color4F& colour) {
	_colour = colour;
	redraw();
}

void g3nts::PrimitiveLine::redraw() {
	_node->clear();
	_node->drawLine(_startPos, _endPos, _colour);
}



g3nts::PrimitiveCapsule::PrimitiveCapsule(const Vec2& startPos, const Vec2& endPos, const float radius, const Color4F& colour)
: _node(DrawNode::create()), _startPos(startPos), _endPos(endPos), _radius(radius), _colour(colour) {
	Vec2 direction = startPos - endPos;
	Vec2 normal = { direction.y, -direction.x };

	_node->drawCircle(startPos + (direction.getNormalized() * radius), radius, 1.0f, 40, false, colour);
	_node->drawCircle(endPos - (direction.getNormalized() * radius), radius, 1.0f, 40, false, colour);
	_node->drawLine(startPos + (normal.getNormalized() * radius), endPos + (normal.getNormalized() * radius), colour);
	_node->drawLine(startPos - (normal.getNormalized() * radius), endPos - (normal.getNormalized() * radius), colour);
}

Vec2 g3nts::PrimitiveCapsule::getStartPosition() const { return _startPos; }
Vec2 g3nts::PrimitiveCapsule::getEndPosition() const   { return _endPos; }
float g3nts::PrimitiveCapsule::getRadius() const { return _radius; }

void g3nts::PrimitiveCapsule::redraw() {
	Vec2 direction = _startPos - _endPos;
	Vec2 normal = { direction.y, -direction.x };

	_node->clear();
	_node->drawCircle(_startPos + (direction.getNormalized() * _radius), _radius, 1.0f, 40, false, _colour);
	_node->drawCircle(_endPos - (direction.getNormalized() * _radius), _radius, 1.0f, 40, false, _colour);
	_node->drawLine(_startPos + (normal.getNormalized() * _radius), _endPos + (normal.getNormalized() * _radius), _colour);
	_node->drawLine(_startPos - (normal.getNormalized() * _radius), _endPos - (normal.getNormalized() * _radius), _colour);
}




// NODE GETTERS (SO WE CAN ADD TO THE SCREEN)
DrawNode* g3nts::PrimitiveRect::getNode() const    { return _node; }
DrawNode* g3nts::PrimitiveCircle::getNode() const  { return _node; }
DrawNode* g3nts::PrimitiveLine::getNode() const    { return _node; }
DrawNode* g3nts::PrimitiveCapsule::getNode() const { return _node; }
