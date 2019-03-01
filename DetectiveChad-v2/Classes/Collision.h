#pragma once

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Primitives.h"

namespace g3nts {
	
	bool isColliding(PrimitiveRect& r1, PrimitiveRect& r2);
	bool isColliding(PrimitiveRect& r1, PrimitiveCircle& c2);

	bool isColliding(PrimitiveCircle& c1, PrimitiveCircle& c2);
	bool isColliding(PrimitiveCircle& c1, PrimitiveRect& r2);
}

#endif