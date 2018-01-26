#pragma once
#include "GameObject.h"

class Ground : public GameObject
{
private:
	b2Body* GroundBody;
	Rect GroundRect;
	Sprite GroundSprite;

public:
	Ground() {};
	Ground(b2World*, Renderer&, Rect);
	~Ground() {};

	void setB2Body(b2Body* body) { GroundBody = body; };

	void Render(Renderer& r);
	void Update(unsigned int deltaTime) {};

	// Set Variables
	void SetType(std::string t) { type = t; };

	// Get Variables
	b2Body* GetBody() { return GroundBody; };
	std::string GetType() { return type; };
};


class B2Object : public GameObject
{
public:
	B2Object() {};
	B2Object(Renderer &rend, b2Body* body);
	~B2Object() {};

	void setB2Body(b2Body* body) { m_body = body; };

	void Render(Renderer& r);
	void Update(unsigned int deltaTime) {};

	// Set Variables
	void SetType(std::string t) { type = t; };

	// Get Variables
	b2Body* GetBody() { return m_body; };
	std::string GetType() { return type; };
private:
	b2Body* m_body;
	Rect m_rect;
	Sprite m_sprite;
};