#include "Level3.h"

void HandleCollision(GameObject*, string);

Level3::Level3(LevelLoader* l) : loader(l)
{
	input.AddListener(EventListener::Event::QUIT, this);
	input.AddListener(EventListener::Event::RIGHT, this);
	input.AddListener(EventListener::Event::LEFT, this);
	input.AddListener(EventListener::Event::POWERUP, this);
	input.AddListener(EventListener::Event::POWERDOWN, this);
	input.AddListener(EventListener::Event::SPACE, this);
	input.AddListener(EventListener::Event::RESET, this);
}

Level3::~Level3()
{

}

void Level3::Init(Renderer& r)
{
	if (Objects.size() > 0)
	{
		Objects.clear();
	}


	BoxWorld.Init();
	quit = false;
	complete = false;
	loader->LoadBox2dData(BoxWorld.getWorld(), 3);
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
	//add our objects specifically from the box2d body vec which we loaded from the .json
	for (int i = 0; i < GameData::m_b2BodyVec.size(); i++)
	{
		Objects.push_back(new B2Object(r, GameData::m_b2BodyVec.at(i)));
	}
}

void Level3::Draw(Renderer& r)
{

	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Render(r);
	}
}


void Level3::Update(unsigned int dt)
{

	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Update(dt);
	}

	BoxWorld.Update(Objects);
	complete = BoxWorld.getLevelComplete();
}

void Level3::Event()
{
	//input.ProcessInput();
}

void Level3::onEvent(EventListener::Event evt)
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

bool Level3::GetQuit()
{
	return quit;
}
