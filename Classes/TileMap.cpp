#include "TileMap.h"
#include "Tags.h"
#include "MainGameScene.h"
#include "Box2dDirector.h"
#include "Box2D\Box2D.h"

bool TileMapLayer::init()
{
	return true;
}

void TileMapLayer::createWithTMX(const char* tmxFile)
{
	// create a TMX map --- WARNING : if tsx path in the tmx file is subclass of Resources, libs can't find *.tsx, *.png
	map = TMXTiledMap::create(tmxFile);
	prepareLayers();
	addChild(map);

	// All the tiles by default will be aliased. If you want to create anti-alias tiles, you should do:
	// iterate over all the "layers" (atlas sprite managers)
	// and set them as 'antialias' 
	Array * pChildrenArray = map->getChildren();
	SpriteBatchNode* child = NULL;
	Object* pObject = NULL;

	CCARRAY_FOREACH(pChildrenArray, pObject)
	{
		child = (SpriteBatchNode*)pObject;

		if(!child)
			break;

		child->getTexture()->setAntiAliasTexParameters();
	}
}

void TileMapLayer::prepareLayers()
{
	// layer
	//Object* object = NULL;

	//CCARRAY_FOREACH(map->getChildren(), object)
	//{
	//	// is this map child a tile layer?
	//	TMXLayer* layer = dynamic_cast<TMXLayer*>(object);
	//	if( layer != nullptr )
	//	{
	//		this->createFixtures(layer);
	//		//this->checkLayer(layer);
	//	}
	//}

	// object group
	TMXObjectGroup *objectGroup = map->getObjectGroup("Object Layer 1");
	this->createFixturesWithObjGrp(objectGroup);
}

void TileMapLayer::createFixturesWithObjGrp(TMXObjectGroup *objectGroup)
{
	Array* arrObjGrp = objectGroup->getObjects();

	//Array * pChildrenArray = map->getChildren();
	Dictionary* dict = NULL;
	Object* pObject = NULL;

	CCARRAY_FOREACH(arrObjGrp, pObject)
	{
		dict = (Dictionary*)pObject;

		if(!dict)
			break;

		/*log("Dict.x : %d", ((String*)(dict->objectForKey(String::create("x")->getCString())))->intValue() );
		log("Dict.y : %d", ((String*)(dict->objectForKey(String::create("y")->getCString())))->intValue() );
		log("Dict.width : %d", ((String*)(dict->objectForKey(String::create("width")->getCString())))->intValue() );
		log("Dict.height : %d", ((String*)(dict->objectForKey(String::create("height")->getCString())))->intValue() );*/
		
		createRectangularFixtureWithObjProp(dict);
	}
}

void TileMapLayer::createFixtures(TMXLayer* layer)
{
	// create all the rectangular fixtures for each tile in the level
	Size layerSize = layer->getLayerSize();
	for( int y=0; y < layerSize.height; y++ )
	{
		for( int x=0; x < layerSize.width; x++ )
		{
			// create a fixture if this tile has a sprite
			Sprite* tileSprite = layer->tileAt(ccp(x, y));
			if( tileSprite )
			{
				this->createRectangularFixture(layer, x, y, 1.1f, 1.1f);
				//log("createRectangularFixture(%d,%d)", x, y);
			}
		}
	}
}

void TileMapLayer::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height)
{
	// get position & size
	Point p = layer->positionAt(ccp(x,y));
	Size tileSize = this->map->getTileSize();

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set( (p.x + (tileSize.width / 2)) / PTM_RATIO,
		                  (p.y + (tileSize.height / 2)) / PTM_RATIO );
	//b2Body* body = world->CreateBody(&bodyDef);
	b2Body* body = (Box2dDirectorLayer::world)->CreateBody(&bodyDef);

	// define the shape
	b2PolygonShape shape;
	shape.SetAsBox( (tileSize.width / PTM_RATIO) * 0.5f * width,
					(tileSize.width / PTM_RATIO) * 0.5f * height );

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;   
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	//uint32 flags = 0;	//added
	//fixtureDef.filter.categoryBits = flags;
	//fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
}

void TileMapLayer::createRectangularFixtureWithObjProp(Dictionary* objectProp)
{
	// get position & size
	int objPropX = ((String*)(objectProp->objectForKey(String::create("x")->getCString())))->intValue();
	int objPropY = ((String*)(objectProp->objectForKey(String::create("y")->getCString())))->intValue();
	int objPropWidth = ((String*)(objectProp->objectForKey(String::create("width")->getCString())))->intValue();
	int objPropHeight = ((String*)(objectProp->objectForKey(String::create("height")->getCString())))->intValue();

	Point p = ccp(objPropX, objPropY);

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set( (p.x + (objPropWidth / 2)) / PTM_RATIO,
		                  (p.y + (objPropHeight / 2)) / PTM_RATIO );
	//b2Body* body = world->CreateBody(&bodyDef);
	b2Body* body = (Box2dDirectorLayer::world)->CreateBody(&bodyDef);

	// define the shape
	b2PolygonShape shape;
	/*shape.SetAsBox( (objPropWidth / PTM_RATIO) * 0.5f * 1.1f,
					(objPropHeight / PTM_RATIO) * 0.5f * 1.1f );*/
	shape.SetAsBox( (objPropWidth / PTM_RATIO) * 0.5f * 1.1f,
					(objPropHeight / PTM_RATIO) * 0.5f * 1.1f);

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;   
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	//uint32 flags = 0;	//added
	//fixtureDef.filter.categoryBits = flags;
	//fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
}