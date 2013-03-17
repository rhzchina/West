#ifndef TOOL_H 
#define TOOL_H
#include <math.h>

#define POINT_INSTANCE(_p1,_p2) \
	sqrt((_p1.x + _p2.x) * \
	(_p1.x + _p2.x) + \
	(_p1.y + _p2.y) + \
	(_p1.y + _p2.y))
#endif