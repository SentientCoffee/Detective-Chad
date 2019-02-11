#include "Collision.h"

bool g3nts::isColliding(g3nts::PrimitiveRect& r1, g3nts::PrimitiveRect& r2) {
	if (r1.getStartPosition().x >= r2.getEndPosition().x || r1.getEndPosition().x <= r2.getStartPosition().x) return false;
	if (r1.getStartPosition().y >= r2.getEndPosition().y || r1.getEndPosition().y <= r2.getStartPosition().y) return false;

	return true;
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

bool g3nts::isColliding(g3nts::PrimitiveCircle& c1, g3nts::PrimitiveCircle& c2) {
	cocos2d::Vec2 distance = c1.getPosition() - c2.getPosition();
	float squaredDistance = (distance.x * distance.x) + (distance.y * distance.y);
	float squaredRadii = (c1.getRadius() * c1.getRadius()) + (c2.getRadius() * c2.getRadius());

	if (squaredDistance <= squaredRadii) return true;
	return false;
}

bool g3nts::isColliding(g3nts::PrimitiveCircle& c1, g3nts::PrimitiveRect& r2) { return isColliding(r2, c1); }
