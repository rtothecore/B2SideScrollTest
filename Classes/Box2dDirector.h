#ifndef __BOX2D_DIRECTOR_H__
#define __BOX2D_DIRECTOR_H__

#include "cocos2d.h"
#include "GLES-Render.h"
#include "Box2D/Box2D.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

#define PTM_RATIO 32

class Box2dDirectorLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(Box2dDirectorLayer);
	virtual void onExit();

	static b2World* world;
	GLESDebugDraw *m_debugDraw;

	void initPhysics();
	virtual void draw();
	void update(float dt);	
};

#endif