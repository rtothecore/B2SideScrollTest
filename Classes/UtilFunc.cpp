#include "UtilFunc.h"

float UtilFunc::getTimeTick() {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	return (ltm->tm_hour * 3600) + (ltm->tm_min * 60) + (ltm->tm_sec);
}



//A rectangle. The origin value is offset in the x-axis by the distance specified by the dx parameter 
//and in the y-axis by the distance specified by the dy parameter, and its size adjusted by (2*dx,2*dy), 
//relative to the source rectangle. If dx and dy are positive values, then the rectangle¡¯s size is decreased. 
//If dx and dy are negative values, the rectangle¡¯s size is increased.
//CGRect collisionBox = CGRectInset(self.boundingBox, 3, 0);
Rect UtilFunc::rectInset(const Rect& rect, float dx, float dy)
{
	return Rect(rect.origin.x - dx, rect.origin.y - dy, rect.size.width - dx, rect.size.height - dy);
}

//A rectangle that is the same size as the source, but with its origin offset by dx units along the x-axis and 
//dy units along the y-axis with respect to the source.
//CGRect returnBoundingBox = CGRectOffset(collisionBox, diff.x, diff.y);
Rect UtilFunc::rectOffset(const Rect& rect, float dx, float dy)
{
	return Rect(rect.origin.x + dx, rect.origin.y + dy, rect.size.width, rect.size.height);
}

Rect UtilFunc::rectIntersection(const Rect& rect1, const Rect& rect2)
{
	float newRectOriginX = 0;
	float newRectOriginY = 0;
	float newRectWidth = 0;
	float newRectHeight = 0;

	if(rect1.getMinX() < rect2.getMinX())
	{
		newRectOriginX = rect2.getMinX();
		newRectWidth = rect1.getMaxX() - rect2.getMinX();
	} 
	else 
	{
		newRectOriginX = rect1.getMinX();
		newRectWidth = rect2.getMaxX() - rect1.getMinX();
	}

	if(rect1.getMinY() < rect2.getMinY())
	{
		newRectOriginY = rect2.getMinY();
		newRectHeight = rect1.getMaxY() - rect2.getMinY();
	}
	else
	{
		newRectOriginY = rect1.getMinY();
		newRectHeight = rect2.getMaxY() - rect1.getMinY();
	}

	return Rect(newRectOriginX, newRectOriginY, newRectWidth, newRectHeight);
}