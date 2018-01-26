#include "pch.h"
#include "LevelLoader.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(JSONTEST, Control)
{
	EXPECT_EQ(GameData::m_maxGameObjects, 0);
	EXPECT_TRUE(GameData::m_gameObjectVector.size() == 0);
}

TEST(JSONTEST, JSONRUNS)
{
	LevelLoader loader("GeneralGameData.json");
	loader.loadLevelData(1);
	//proof the loader has read in form the .json file
	EXPECT_EQ(GameData::m_maxGameObjects, 1);
	EXPECT_TRUE(GameData::m_gameObjectVector.size() == 1);
}