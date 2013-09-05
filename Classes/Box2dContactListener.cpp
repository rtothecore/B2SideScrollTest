#include "Box2dContactListener.h"
#include "Missionaries.h"

Box2dContactListener::Box2dContactListener()
{
}

Box2dContactListener::~Box2dContactListener()
{
}

void Box2dContactListener::BeginContact(b2Contact* contact) {
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if ( bodyUserData )
		static_cast<MissionariesLayer*>( bodyUserData )->startContact();

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if ( bodyUserData )
		static_cast<MissionariesLayer*>( bodyUserData )->startContact();
}
  
void Box2dContactListener::EndContact(b2Contact* contact) {
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if ( bodyUserData )
		static_cast<MissionariesLayer*>( bodyUserData )->endContact();

	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if ( bodyUserData )
		static_cast<MissionariesLayer*>( bodyUserData )->endContact();
}
