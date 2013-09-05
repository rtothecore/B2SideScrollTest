#ifndef __UTILFUNC_H__
#define __UTILFUNC_H__

#include "cocos2d.h"

USING_NS_CC;

class UtilFunc
{
public:
	static float getTimeTick();

	static Rect rectInset(const Rect& rect, float dx, float dy);
	static Rect rectOffset(const Rect& rect, float dx, float dy);
	static Rect rectIntersection(const Rect& rect1, const Rect& rect2);
};

#endif