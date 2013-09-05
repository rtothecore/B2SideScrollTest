#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "cocos2d.h"

USING_NS_CC;

class TileMapLayer : public Layer
{
public:
	CREATE_FUNC(TileMapLayer);
	virtual bool init();

	TMXTiledMap *map;

	void createWithTMX(const char* tmxFile);
	void prepareLayers();
	//void checkLayer(TMXLayer* layer);

	// query
	//Sprite* getUnderTileWithXY(int footXPos, int footYPos);

	// box2d
	void createFixtures(TMXLayer* layer);
	void createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height);

	void createFixturesWithObjGrp(TMXObjectGroup *objectGroup);
	void createRectangularFixtureWithObjProp(Dictionary* objectProp);
};

#endif