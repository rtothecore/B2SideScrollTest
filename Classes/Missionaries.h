#ifndef __MISSIONARIES_H__
#define __MISSIONARIES_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

class MissionariesLayer : public Layer
{
public:
	CREATE_FUNC(MissionariesLayer);
	virtual bool init();

	void initWithSprite();
	Size getSpriteSize();

	// move
	unsigned int walkStep;
	unsigned int jumpStep;

	void walk(bool toTheLeft);
	void jump(bool toTheLeft);

	// box2d
	b2Body *_body;
	void activateCollisions();
	void deactivateCollisions();

	void createFixtureWithPhysicsSprite(Point p);
	virtual void setPosition(Point position);

	// box2d contact listener callback
	int m_numContact;
	void startContact() { m_numContact++; }
	void endContact() { m_numContact--; }

};

#endif