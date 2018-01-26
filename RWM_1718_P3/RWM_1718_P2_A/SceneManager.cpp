#include "SceneManager.h"

SceneManager::Scenes SceneManager::m_currentScene;
Scene* SceneManager::m_scene;
vector<Scene*> SceneManager::m_sceneList;

SceneManager::SceneManager()
{
	//m_sceneList.push_back(new TestScene());
}

SceneManager::SceneManager(LevelLoader *l)
{

	m_sceneList.push_back(new StartScene());
	m_sceneList.push_back(new Level1(l));
	m_sceneList.push_back(new Level2(l));
	m_sceneList.push_back(new Level3(l));
	m_sceneList.push_back(new EndScene());
	m_scene = m_sceneList.at(SceneManager::start);
	m_currentScene = Scenes::start;
}

SceneManager::~SceneManager() {}

void SceneManager::EventScene()
{
	m_scene->Event();
}

void SceneManager::ChangeStates(SceneManager::Scenes newScene)
{
	switch (newScene)
	{
	case SceneManager::start:
		cout << "going to: Start scene" << endl;
		m_scene = m_sceneList.at(SceneManager::start);
		m_currentScene = Scenes::start;
		break;
	case SceneManager::levelselection:
		cout << "goint to: Level selection" << endl;
		m_scene = m_sceneList.at(SceneManager::levelselection);
		m_currentScene = Scenes::levelselection;
		break;
	case SceneManager::level1:
		cout << "going to: level1 scene" << endl;
		m_scene = m_sceneList.at(SceneManager::level1);
		m_currentScene = Scenes::level1;
		break;
	case SceneManager::level2:
		cout << "going to: level2 scene" << endl;
		m_scene = m_sceneList.at(SceneManager::level2);
		m_currentScene = Scenes::level2;
		break;
	case SceneManager::level3:
		cout << "going to: level3 scene" << endl;
		m_scene = m_sceneList.at(SceneManager::level3);
		m_currentScene = Scenes::level3;
		break;
	case SceneManager::level4:
		cout << "going to: level4 scene" << endl;
		m_scene = m_sceneList.at(SceneManager::level4);
		m_currentScene = Scenes::level4;
		break;
	case SceneManager::level5:
		cout << "going to: level5 scene" << endl;
		m_scene = m_sceneList.at(SceneManager::level5);
		m_currentScene = Scenes::level5;
		break;
	case SceneManager::level6:
		cout << "going to: level6 scene" << endl;
		m_scene = m_sceneList.at(SceneManager::level6);
		m_currentScene = Scenes::level6;
		break;
	case SceneManager::end:
		cout << "going to: end scene" << endl;
		m_scene = m_sceneList.at(SceneManager::end);
		m_currentScene = Scenes::end;
		break;
	default:
		cout << "Scene manager had an error. Going to start" << endl;
		m_scene = m_sceneList.at(SceneManager::start);
		break;
	}
}

void SceneManager::LoadNextLevel(Renderer& r, SceneManager::Scenes next)
{
	m_sceneList.at(next)->Init(r);

}

void SceneManager::UpdateScene(unsigned int DeltaTime)
{
	m_scene->Update(DeltaTime);
}

void SceneManager::DrawScene(Renderer& renderer)
{
	if (m_scene != nullptr)
	{
		m_scene->Draw(renderer);
	}
}
