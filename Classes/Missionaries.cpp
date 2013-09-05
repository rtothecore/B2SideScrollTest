#include "Missionaries.h"
#include "Tags.h"
#include "MainGameScene.h"
#include "Box2dDirector.h"
//#include "Box2D\Box2D.h"
#define PTM_RATIO 32

bool MissionariesLayer::init()
{
	walkStep = 1;
	jumpStep = 1;
	m_numContact = 0;

	initWithSprite();

	return true;
}

void MissionariesLayer::initWithSprite()
{
	//// box2d
	createFixtureWithPhysicsSprite(this->getPosition());
}

void MissionariesLayer::walk(bool toTheLeft)
{
	if(m_numContact)
	{
		int walkStepWithD = walkStep;
		toTheLeft ? walkStepWithD = -walkStep : 0;

		// apply impulse if x velocity is getting low
		b2Vec2 currentVelocity = _body->GetLinearVelocity();
		b2Vec2 impulse(0.0f, 0.0f);

		if( fabsf(currentVelocity.x) < 5.0f )
		{
			impulse.y = 0.0f;
			impulse.x = 50.0f * walkStepWithD;

			_body->ApplyLinearImpulse(impulse, _body->GetWorldCenter());
		}
	} 
	else 
	{
		log("You can't move in the air");
	}
}

void MissionariesLayer::jump(bool toTheLeft)
{
	if(m_numContact)
	{
		int jumpStepWithD = jumpStep;
		toTheLeft ? jumpStepWithD = -jumpStep : 0;

		// apply impulse
		b2Vec2 impulse(0.0f, 0.0f);

		impulse.y = 120.0f;
		//impulse.x = 20.0f * jumpStepWithD;

		log("implulse(%f,%f)", impulse.x, impulse.y);

		_body->ApplyLinearImpulse(impulse, _body->GetWorldCenter());
	} 
	else 
	{
		log("You can't jump in the air");
	}
}

Size MissionariesLayer::getSpriteSize()
{
	return getChildByTag(kTagSprtGabriel)->getContentSize();
}

void MissionariesLayer::createFixtureWithPhysicsSprite(Point p)
{
	// Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
	bodyDef.angle = 0.0f;
	bodyDef.fixedRotation = true;

    b2Body *body = (Box2dDirectorLayer::world)->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    //dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
	dynamicBox.SetAsBox(.5f, .8f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 10.0f;
    //fixtureDef.friction = 0.3f;
	fixtureDef.friction = 10.0f;
    body->CreateFixture(&fixtureDef);

	// set Userdata
	body->SetUserData(this);

	// body to sprite
	Texture2D *texture = TextureCache::getInstance()->addImage("gabriel.png");
	PhysicsSprite *sprite = PhysicsSprite::createWithTexture(texture);
	addChild(sprite, 1, kTagSprtGabriel);
    sprite->setB2Body(body);
    sprite->setPTMRatio(PTM_RATIO);
	_body = body;
}

void MissionariesLayer::setPosition(Point position)
{
	_body->SetTransform(b2Vec2(position.x/PTM_RATIO,position.y/PTM_RATIO), _body->GetAngle());
}

void MissionariesLayer::activateCollisions()
{
	b2Fixture *fixture = _body->GetFixtureList();
	b2Filter filter = fixture->GetFilterData();
	filter.categoryBits = 0x0001;
	filter.maskBits = 0x0001;
	fixture->SetFilterData(filter);
}

void MissionariesLayer::deactivateCollisions()
{
	b2Fixture *fixture = _body->GetFixtureList();
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 0;
    filter.maskBits = 0;
    fixture->SetFilterData(filter);
}