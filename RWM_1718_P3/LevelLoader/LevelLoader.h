#include "stdafx.h"
#ifndef LEVElLOADER_H
#define LEVElLOADER_H

#include "MenuData.h"
#include "GameData.h"
#include "JSON.h"
#include "stdafx.h"

#if __has_include("Box2D\Box2D.h")
	#include "Box2D\Box2D.h" 
#endif

#if __has_include("SDL.h")
	#include "SDL.h"
#endif


#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////
/// \brief A class to load all the configuration data
///        required by the game. 
///
////////////////////////////////////////////////////////////

class LevelLoader {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// This constructor initialises the JSON parser and loads
	/// the menu and game level data.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	LevelLoader(std::string const & filename);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// Frees resources acquired by the JSON parser.
	///
	////////////////////////////////////////////////////////////
	~LevelLoader();

	////////////////////////////////////////////////////////////
	/// \brief Loads the JSON data from the specified file.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	void load(std::string const & filename);

	////////////////////////////////////////////////////////////
	/// \brief Get the menu configuration data
	///
	/// \return A MenuData instance containing config values
	///
	///
	////////////////////////////////////////////////////////////
	MenuData const & getMenuData() const;

#if __has_include("Box2D\Box2D.h")

	////////////////////////////////////////////////////////////
	/// \brief Finds the "level" + level + "Box2D" object in the .json to load from
	///
	/// \param world A b2world object needed to create the b2body's
	///
	/// \param level specify what level's b2bodies need to be loaded from the .json
	////////////////////////////////////////////////////////////
	void LoadBox2dData(b2World* world, int level);

#endif


	////////////////////////////////////////////////////////////
	/// \brief Get the game configuration data
	///
	/// \return A GameData instance containing config values
	///
	///	
	////////////////////////////////////////////////////////////
	GameData & getGameData(int level);

	////////////////////////////////////////////////////////////
	/// \brief Finds the "Level" + level object in the .json to load from
	///
	/// \param level specify what level's objects need to be loaded from the .json
	////////////////////////////////////////////////////////////
	void loadLevelData(int level);

private:
	JSONValue *m_value;
	std::string m_JSONData;
	MenuData m_menuData;
	GameData m_gameData;

	void loadJSONData(std::string const & filename);

	void loadMenuData();

	


	// Utility methods.
	JSONObject getTopLevelJSONObject();
	std::string wStringToString(std::wstring const & wstr);

};

#endif