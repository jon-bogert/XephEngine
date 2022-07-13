#include "C_PhysicsBox.h"
namespace C
{
	PhysicsBox::PhysicsBox(PhysicsBody bodyType, Vector2 dimensions, GameObject* gameObject)
		:Component(gameObject), dimensions(dimensions)
	{
		bodyDef = new b2BodyDef;
		switch (bodyType)
		{
		case (PhysicsBody::Dynamic):
			bodyDef->type = b2_dynamicBody;
			break;
		case (PhysicsBody::Kinematic):
			bodyDef->type = b2_kinematicBody;
			break;
		default:
			bodyDef->type = b2_staticBody;
		}
	}

	PhysicsBox::~PhysicsBox()
	{
		delete fixtureDef;
		delete shape;
		delete bodyDef;
	}
		
	void PhysicsBox::Start()
	{
		bodyDef->position.Set(gameObject->transform.position.x, gameObject->transform.position.y);
		body = Engine::GetActiveScene()->GetWorld()->PhysicsWorld()->CreateBody(bodyDef);

		shape = new b2PolygonShape;
		shape->SetAsBox(dimensions.x * 0.5f, dimensions.y * 0.5f); // TODO - Get from drawable component

		fixtureDef = new b2FixtureDef;
		fixtureDef->shape = shape;
		fixtureDef->density = density;
		fixtureDef->friction = friction;

		body->CreateFixture(fixtureDef);
	}
	
	void PhysicsBox::Update()
	{
		gameObject->transform.position = { body->GetPosition().x, body->GetPosition().y };
		gameObject->transform.rotation.SetRad(body->GetAngle() * -1);
	}
}
