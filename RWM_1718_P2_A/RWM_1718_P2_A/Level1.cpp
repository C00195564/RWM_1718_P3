#include "Level1.h"

void HandleCollision(GameObject*, string);

Level1::Level1(LevelLoader* l): loader(l)
{
	input.AddListener(EventListener::Event::QUIT, this);
	input.AddListener(EventListener::Event::RIGHT, this);
	input.AddListener(EventListener::Event::LEFT, this);
	input.AddListener(EventListener::Event::POWERUP, this);
	input.AddListener(EventListener::Event::POWERDOWN, this);
	input.AddListener(EventListener::Event::SPACE, this);
	input.AddListener(EventListener::Event::RESET, this);
}

Level1::~Level1()
{

}

void Level1::Init(Renderer& r)
{
	if (Objects.size() > 0)
	{
		Objects.clear();
	}

	
	BoxWorld.Init();
	quit = false;
	complete = false;

	//because box2d bodies need a b2world object to be created properly we call the load AFTER creating our world.
 	loader->LoadBox2dData(BoxWorld.getWorld(), 1);

	//instantiate basic objects from the gameobjectvector which we loaded form the .json
	for (int i = 0; i < GameData::m_maxGameObjects; i++)
	{
		if (GameData::m_gameObjectVector.at(i).type == "Ground")
		{
			Objects.push_back(new Ground(BoxWorld.getWorld(), r,
				Rect(GameData::m_gameObjectVector.at(i).X, GameData::m_gameObjectVector.at(i).Y,
					GameData::m_gameObjectVector.at(i).Width, GameData::m_gameObjectVector.at(i).Height)));
		}
		else if (GameData::m_gameObjectVector.at(i).type == "Platform")
		{
			Objects.push_back(new Platform(BoxWorld.getWorld(), r,
				Rect(GameData::m_gameObjectVector.at(i).X, GameData::m_gameObjectVector.at(i).Y,
					GameData::m_gameObjectVector.at(i).Width, GameData::m_gameObjectVector.at(i).Height)));
		}
	}
	gorm = Platform(BoxWorld.getWorld(), r, Rect(0, 200, 500, 20));
	gorm.GetBody()->SetTransform(gorm.GetBody()->GetPosition(), 20);
	gorm.SetAngle(20);
	//add our objects specifically from the box2d body vec which we loaded from the .json
	for (int i = 0; i < GameData::m_b2BodyVec.size(); i++)
	{
		Objects.push_back(new B2Object(r, GameData::m_b2BodyVec.at(i)));
	}

}

void Level1::Draw(Renderer& r)
{
	
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Render(r);
	}
	gorm.Render(r);
}


void Level1::Update(unsigned int dt)
{

	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Update(dt);
	}

	BoxWorld.Update(Objects);
	complete = BoxWorld.getLevelComplete();
}

void Level1::Event()
{
	//input.ProcessInput();
}

void Level1::onEvent(EventListener::Event evt)
{
	switch (evt)
	{
	case EventListener::Event::QUIT:
		quit = true;
		break;
	case EventListener::Event::RIGHT:
		
		break;
	case EventListener::Event::LEFT:
		
		break;
	case EventListener::Event::POWERUP:
		
		break;
	case EventListener::Event::POWERDOWN:
		
		break;
	case EventListener::Event::SPACE:
		
		break;
	case EventListener::Event::RESET:
		
		break;
	}
}

bool Level1::GetQuit()
{
	return quit;
}
