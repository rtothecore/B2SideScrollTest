#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameScene);
};

class MainGameLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MainGameLayer);

	void addMissionaries();

	// check touch holding 
	bool isLeftTouched;
	void checkTouchHold(float dt);

	// check swipe
	bool isSwipeStart;
	int iSwipeStartY;
	int iSwipeEndY;
	void checkSwipe(float dt);

	virtual bool ccTouchBegan(Touch* touch, Event* event);
    virtual void ccTouchMoved(Touch* touch, Event* event);
    virtual void ccTouchEnded(Touch* touch, Event* event);

	// sprite background
	void initBackground();

	// box2d
	void addBox(Point p);
};

#endif 
