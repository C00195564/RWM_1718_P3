#include "stdafx.h"
#include "LevelLoader.h"


int GameData::m_playerX;
int GameData::m_playerY;
int GameData::m_maxGameObjects;
int GameData::m_maxb2Bodies;
std::vector<b2Body*> GameData::m_b2BodyVec;
std::vector<GameData::GObject> GameData::m_gameObjectVector;
std::string GameData::fontFile;
	
////////////////////////////////////////////////////////////
LevelLoader::LevelLoader(std::string const & filename)
{

	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
}

////////////////////////////////////////////////////////////
LevelLoader::~LevelLoader() {
	delete m_value;
}

////////////////////////////////////////////////////////////
void LevelLoader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
	
}

////////////////////////////////////////////////////////////
void LevelLoader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			m_JSONData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		std::cout << "Could not open " + filename + " exiting!" << std::endl;
		throw std::exception(errorMessage.c_str());
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::loadMenuData()
{
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject menuData = root[L"general_game_data"]->AsObject();
	// Locate the menu font file.	
	JSONObject globalSettings = menuData[L"global_settings"]->AsObject();
	m_menuData.m_MenuFontFile = wStringToString(globalSettings[L"font_file"]->AsString());

	JSONObject mainMenu = menuData[L"main_menu_items"]->AsObject();
	JSONArray menuItems = mainMenu[L"menu_items"]->AsArray();
	for (unsigned int i = 0; i < menuItems.size(); i++)
	{
		JSONObject object = menuItems[i]->AsObject();
		m_menuData.m_mainMenuVec.push_back(MenuData::MObject(object[L"Width"]->AsNumber(), object[L"Height"]->AsNumber(), object[L"x"]->AsNumber(), object[L"y"]->AsNumber(),
			wStringToString(object[L"text"]->AsString())));
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::loadLevelData(int level)
{
	
	m_gameData.m_gameObjectVector.clear();
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	// Load the time to place towers field and related text settings.
	JSONObject globalSettings = gameData[L"global_settings"]->AsObject();
	m_gameData.fontFile = wStringToString(globalSettings[L"font_file"]->AsString());
	//use level to find the correct object in the json
	std::string word("level" + std::to_string(level));
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject m_level = gameData[wWord]->AsObject();
	//m_gameData.m_levelBackgroundFile = wStringToString(m_level[L"level_background_file"]->AsString());
	m_gameData.m_maxGameObjects = m_level[L"max_game_objects"]->AsNumber();
	m_gameData.m_playerX = m_level[L"player_x"]->AsNumber();
	m_gameData.m_playerY = m_level[L"player_y"]->AsNumber();
	JSONArray gameObjects = m_level[L"GameObjects"]->AsArray();
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		JSONObject object = gameObjects[i]->AsObject();
		m_gameData.m_gameObjectVector.push_back(GameData::GObject(object[L"x"]->AsNumber(), object[L"y"]->AsNumber(), 
			object[L"Width"]->AsNumber(), object[L"Height"]->AsNumber(),
			wStringToString(object[L"Type"]->AsString())));
	}
}

#if __has_include("Box2D\Box2D.h")
////////////////////////////////////////////////////////////
void LevelLoader::LoadBox2dData(b2World* world, int level)
{

	m_gameData.m_b2BodyVec.clear();
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	// Load the time to place towers field and related text settings.
	JSONObject globalSettings = gameData[L"global_settings"]->AsObject();
	//use level to find the correct object in the json
	std::string word("level" + std::to_string(level) + "Box2D");
	std::wstring wWord;
	wWord.assign(word.begin(), word.end());
	JSONObject m_level = gameData[wWord]->AsObject();
	//m_gameData.m_levelBackgroundFile = wStringToString(m_level[L"level_background_file"]->AsString());
	m_gameData.m_maxb2Bodies = m_level[L"max_b2shape"]->AsNumber();
	JSONArray gameObjects = m_level[L"b2List"]->AsArray();
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		b2BodyDef bodydef;
		JSONObject object = gameObjects[i]->AsObject();
		std::string temp = wStringToString(object[L"type"]->AsString());
		if (temp == "dynamic")
		{
			bodydef.type = b2_dynamicBody;
		}
		else if (temp == "static")
		{
			bodydef.type = b2_staticBody;
		}
		else
		{
			bodydef.type = b2_kinematicBody;
		}
		bodydef.position.Set(object[L"x"]->AsNumber(), object[L"y"]->AsNumber());
		bodydef.awake = object[L"awake"]->AsBool();

		b2Body *body = world->CreateBody(&bodydef);

		temp = wStringToString(object[L"shape"]->AsString());
		if(temp == "box")
		{
			b2PolygonShape shape;
			shape.SetAsBox(object[L"width"]->AsNumber() / 2, object[L"height"]->AsNumber() / 2,
				b2Vec2(object[L"width"]->AsNumber() / 2, object[L"height"]->AsNumber() / 2), 0);
			body->CreateFixture(&shape, object[L"density"]->AsNumber());
		}
		else if (temp == "circle")
		{
			b2CircleShape shape;
			shape.m_p.Set(object[L"width"]->AsNumber()/2, object[L"height"]->AsNumber()/2);
			shape.m_radius = object[L"radius"]->AsNumber();
			body->CreateFixture(&shape, object[L"density"]->AsNumber());
		}
		else if (temp == "polygon")
		{
			b2PolygonShape shape;
			JSONArray verticeArray = object[L"vertices"]->AsArray();
			int size = verticeArray.size();
			b2Vec2 *vertices = nullptr;
			vertices = new b2Vec2[size];
			for (unsigned int i = 0; i < verticeArray.size(); i++)
			{
				vertices[i] = b2Vec2(object[L"x"]->AsNumber(), object[L"y"]->AsNumber());
			}
			shape.Set(vertices, size);
			delete[] vertices;
			vertices = nullptr;
			body->CreateFixture(&shape, object[L"density"]->AsNumber());
		}

		body->GetFixtureList()->SetRestitution(object[L"restitution"]->AsNumber());
		body->GetFixtureList()->SetFriction(object[L"friction"]->AsNumber());
		body->SetTransform(body->GetPosition(), object[L"angle"]->AsNumber());
		m_gameData.m_b2BodyVec.push_back(body);
	}
}
#endif
////////////////////////////////////////////////////////////
MenuData const & LevelLoader::getMenuData() const
{
	return m_menuData;
}

GameData & LevelLoader::getGameData(int level)
{
	loadLevelData(level);
	return m_gameData;
}

////////////////////////////////////////////////////////////
JSONObject LevelLoader::getTopLevelJSONObject() {
	// Retrieve the main (root) object
	JSONObject root;

	if (m_value->IsObject() == false)
	{
		throw std::exception("Problem with root element in json file, exiting");
	}
	root = m_value->AsObject();

	return root;
}

////////////////////////////////////////////////////////////
std::string LevelLoader::wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}

