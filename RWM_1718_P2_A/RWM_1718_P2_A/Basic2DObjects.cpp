#include "Basic2DObjects.h"

Ground::Ground(b2World* world, Renderer& r, Rect rect)
{
	type = "Ground";

	// Define Cannon's position, width and height
	GroundRect = rect;

	// Create Body definition
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(GroundRect.pos.x, GroundRect.pos.y);
	GroundBody = world->CreateBody(&bodyDef);

	// Creat Shape polygon
	b2PolygonShape Shape;
	Shape.SetAsBox(GroundRect.size.w / 2, (GroundRect.size.h / 2) - 5, b2Vec2(GroundRect.size.w / 2, GroundRect.size.h / 2), 0);
	GroundBody->CreateFixture(&Shape, 10.0f);

	GroundBody->GetFixtureList()->SetFriction(0.2f);
	GroundBody->GetFixtureList()->SetRestitution(0.2f);

	GroundSprite.Init("Assets/Images/Ground.png", r, Rect(0, 0, 274, 128), GroundRect);

}

void Ground::Render(Renderer& r)
{
	GroundSprite.Render(r);
}

B2Object::B2Object(Renderer&rend, b2Body* body)
{
	type = "ground";
	m_body = body;
	m_rect.pos.x = m_body->GetPosition().x;
	m_rect.pos.y = m_body->GetPosition().y;
	m_rect.size.h = 100;
	m_rect.size.w = 100;

	if (typeid(m_body->GetFixtureList()->GetShape()) == typeid(b2CircleShape()))
	{
		m_sprite.Init("Assets/Images/ball.png", rend, Rect(0, 0, 274, 277), m_rect);
	}
	else
	{
		m_sprite.Init("Assets/Images/Ground.png", rend, Rect(0, 0, 274, 128), m_rect);
	}
	m_sprite.setRotation(m_body->GetAngle());
}

void B2Object::Render(Renderer& r)
{
	m_rect.pos.x = m_body->GetPosition().x;
	m_rect.pos.y = m_body->GetPosition().y;
	m_sprite.setRotation(m_body->GetAngle());
	m_sprite.setPosition(m_rect);
	m_sprite.Render(r, (m_body->GetAngle() * (180.0 / 3.14159)));
}