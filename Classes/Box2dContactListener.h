#ifndef __BOX2D_CONTACT_LISTENER_H__
#define __BOX2D_CONTACT_LISTENER_H__

#include "cocos2d.h"
#include "GLES-Render.h"
#include "Box2D/Box2D.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

#define PTM_RATIO 32

class Box2dContactListener : public b2ContactListener
{
public:
	Box2dContactListener();
	~Box2dContactListener();

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
};

#endif