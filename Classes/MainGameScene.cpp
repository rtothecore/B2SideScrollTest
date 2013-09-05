#include "MainGameScene.h"
#include "Tags.h"
#include "Missionaries.h"
#include "TileMap.h"
#include "Box2dDirector.h"
#include "Box2dContactListener.h"

//------------------------------------------------------------------
//
// MainGameScene
//
//------------------------------------------------------------------
bool MainGameScene::init()
{
	MainGameLayer* layer = MainGameLayer::create();
	addChild(layer);

	return true;
}

//------------------------------------------------------------------
//
// MainGameLayer
//
//------------------------------------------------------------------

bool MainGameLayer::init()
{
	isLeftTouched = false;
	isSwipeStart = false;
	iSwipeStartY = 0;
	iSwipeEndY = 0;

	// Touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	//// background
	//initBackground();

	// Box2d
	Box2dDirectorLayer* box2dDirecL = Box2dDirectorLayer::create();
	addChild(box2dDirecL, 0, kTagLyrBox2dDirec);

	// TMX
	TileMapLayer* tilemapL = TileMapLayer::create();
	addChild(tilemapL, 1, kTagTileMap);
	tilemapL->createWithTMX("testMap.tmx");

	// player
	addMissionaries();

	// Box2d ContactListener
	Box2dContactListener* box2dContactListener = new Box2dContactListener();
	box2dDirecL->world->SetContactListener(box2dContactListener);

	return true;
}

void MainGameLayer::initBackground()
{
	//Size screen = Director::getInstance()->getWinSize();
	//Sprite* background = Sprite::create("bg-hd.png");
	//background->setPosition( Point(screen.width/2, screen.height/2) );
	//addChild(background, 0);

	//// Particles
	//CCParticleSystemQuad *sunPollen = CCParticleSystemQuad::create("Particles/sun_pollen.plist");
	//addChild(sunPollen);
}

void MainGameLayer::addMissionaries()
{
	MissionariesLayer* missionariesL = MissionariesLayer::create();
	addChild(missionariesL, 1, kTagLyrMissionaries);
	missionariesL->setPosition(ccp(30, 200));
}

bool MainGameLayer::ccTouchBegan(Touch* touch, Event* event)
{
	Size winSize = Director::getInstance()->getWinSize();

	if(winSize.width/2 < touch->getLocation().x)	// screen right click
	{
		isLeftTouched = false;
	} 
	else
	{
		isLeftTouched = true;
	}

	schedule(schedule_selector(MainGameLayer::checkTouchHold), 0.1f);	

    return true;
}

void MainGameLayer::checkTouchHold(float dt)
{
	MissionariesLayer* missionariesL = (MissionariesLayer*)getChildByTag(kTagLyrMissionaries);

	if(isLeftTouched)
	{
		log("move to left!");	
		missionariesL->walk(true);
	}
	else
	{
		log("move to right!");
		missionariesL->walk(false);
	}
}

void MainGameLayer::ccTouchMoved(Touch* touch, Event* event)
{
	if(!isSwipeStart)
	{
		iSwipeStartY = touch->getLocation().y;
		isSwipeStart = true;

		schedule(schedule_selector(MainGameLayer::checkSwipe), 0.1f);
	}

	if(isSwipeStart)
		iSwipeEndY = touch->getLocation().y;
}

void MainGameLayer::checkSwipe(float dt)
{
	MissionariesLayer* missionariesL = (MissionariesLayer*)getChildByTag(kTagLyrMissionaries);

	if( iSwipeStartY < iSwipeEndY 
		&& 20 < (iSwipeEndY - iSwipeStartY) )
	{
		log("Jump!");
		if(isLeftTouched)
		{
			missionariesL->jump(true);
		}
		else
		{
			missionariesL->jump(false);
		}

		// stop move
		unschedule(schedule_selector(MainGameLayer::checkTouchHold));

		// stop check swipe
		unschedule(schedule_selector(MainGameLayer::checkSwipe));
	}
}

void MainGameLayer::ccTouchEnded(Touch* touch, Event* event)
{
	// stop move
	unschedule(schedule_selector(MainGameLayer::checkTouchHold));
	log("stop move!");

	// stop check swipe
	isSwipeStart = false;
	unschedule(schedule_selector(MainGameLayer::checkSwipe));

	// box2d
	//addBox( Point(touch->getLocation().x, touch->getLocation().y) );
}

void MainGameLayer::addBox(Point p)
{
	// Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

    b2Body *body = (Box2dDirectorLayer::world)->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    //dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
	dynamicBox.SetAsBox(.5f, .8f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;   
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);    

	// body to sprite
	Texture2D *texture = TextureCache::getInstance()->addImage("gabriel.png");
	PhysicsSprite *sprite = PhysicsSprite::createWithTexture(texture);
    addChild(sprite);
    sprite->setB2Body(body);
    sprite->setPTMRatio(PTM_RATIO);
    sprite->setPosition( Point( p.x, p.y) );
}