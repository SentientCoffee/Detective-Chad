#pragma once

#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__

#include "cocos2d.h"

namespace g3nts {
	class PrimitiveRect {
	public:
		// CONSTRUCTORS/DECONSTRUCTORS
		PrimitiveRect();
		PrimitiveRect(const cocos2d::Vec2& startPos,
					  const cocos2d::Vec2& endPos);
		PrimitiveRect(const cocos2d::Vec2& startPos,
					  const cocos2d::Vec2& endPos,
					  const cocos2d::Color4F& colour);

		// MEMBER FUNCTIONS
		cocos2d::DrawNode* getNode() const;

		cocos2d::Vec2 getStartPosition() const;
		cocos2d::Vec2 getEndPosition() const;
		cocos2d::Vec2 getCentrePosition() const;

		float getWidth() const;
		float getHeight() const;

		void setStartPosition(cocos2d::Vec2& startPos);
		void setEndPosition(cocos2d::Vec2& endPos);

		void setPosition(cocos2d::Vec2& centrePos);
		void setPosition(cocos2d::Vec2& startPos, cocos2d::Vec2& endPos);
		void setColour(cocos2d::Color4F& colour);


	private:

		cocos2d::DrawNode* _node;
		
		cocos2d::Vec2 _startPos, _endPos;
		cocos2d::Color4F _colour;
		
		void redraw();

	};

	class PrimitiveCircle {
	public:
		// CONSTRUCTORS/DECONSTRUCTORS
		PrimitiveCircle();
		PrimitiveCircle(const cocos2d::Vec2& centrePos,
						const float radius);
		PrimitiveCircle(const cocos2d::Vec2& centrePos,
						const float radius,
						const cocos2d::Color4F& colour);
		PrimitiveCircle(const cocos2d::Vec2& centrePos,
					    const float radius,
					    const float angle,
					    const unsigned int segments,
					    const bool drawRadius,
					    const cocos2d::Color4F& colour);

		// MEMBER FUNCTIONS
		cocos2d::DrawNode* getNode() const;

		cocos2d::Vec2 getPosition() const;
		float getRadius() const;

		void setPosition(cocos2d::Vec2& position);
		void setRadius(const float radius);
		void setAngle(const float angle);
		void setSegments(const unsigned int segments);
		void setDrawRadius(const bool drawRadius);
		void setColour(cocos2d::Color4F& colour);


	private:

		cocos2d::DrawNode* _node;

		cocos2d::Vec2 _position;
		float _radius;
		float _angle;
		unsigned int _segments;
		bool _drawRadius;
		cocos2d::Color4F _colour;

		void redraw();

	};

	class PrimitiveLine {
	public:
		// CONSTRUCTORS/DECONSTRUCTORS
		PrimitiveLine();
		PrimitiveLine(const cocos2d::Vec2& startPos,
					  const cocos2d::Vec2& endPos);
		PrimitiveLine(const cocos2d::Vec2& startPos,
					  const cocos2d::Vec2& endPos,
					  const cocos2d::Color4F& colour);

		// MEMBER FUNCTIONS
		cocos2d::DrawNode* getNode() const;

		cocos2d::Vec2 getStartPosition() const;
		cocos2d::Vec2 getEndPosition() const;

		void setStartPosition(cocos2d::Vec2& startPos);
		void setEndPosition(cocos2d::Vec2& endPos);
		void setColour(cocos2d::Color4F& colour);

	private:

		cocos2d::DrawNode* _node;
		
		cocos2d::Vec2 _startPos, _endPos;
		cocos2d::Color4F _colour;

		void redraw();
	};

	class PrimitiveCapsule {
	public:
		// CONSTRUCTORS/DECONSTRUCTORS
		PrimitiveCapsule();
		PrimitiveCapsule(const cocos2d::Vec2& startPos,
						 const cocos2d::Vec2& endPos,
						 const float radius);
		PrimitiveCapsule(const cocos2d::Vec2& startPos,
						 const cocos2d::Vec2& endPos,
						 const float radius, 
						 const cocos2d::Color4F& colour);

		// MEMBER FUNCTIONS
		cocos2d::DrawNode* getNode() const;

		cocos2d::Vec2 getStartPosition() const;
		cocos2d::Vec2 getEndPosition() const;
		float getRadius() const;

	private:

		cocos2d::DrawNode* _node;

		cocos2d::Vec2 _startPos, _endPos;
		float _radius;
		cocos2d::Color4F _colour;

		void redraw();

	};

	bool isColliding(g3nts::PrimitiveCircle& c1, g3nts::PrimitiveCircle& c2);
	bool isColliding(g3nts::PrimitiveRect& r1, g3nts::PrimitiveRect& r2);
	bool isColliding(g3nts::PrimitiveRect& r1, g3nts::PrimitiveCircle& c2);
	bool isColliding(g3nts::PrimitiveCircle& c1, g3nts::PrimitiveRect& r2);
}

#endif