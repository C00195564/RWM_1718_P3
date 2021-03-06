#ifndef LEVEL1_H
#define LEVEL1_H

#include "SceneManager.h"
#include "Scene.h"
#include "GameData.h"
#include "World.h"
#include "Basic2DObjects.h"
#include "stdafx.h"
#include "Platform.h"
#include "LevelLoader.h"

class Level1 : public Scene, public EventListener
{
public:
	Level1(LevelLoader* l);
	~Level1();

	void Update(unsigned int);
	void Draw(Renderer& renderer);
	void Event();
	bool GetQuit();
	void Init(Renderer& r);
	void onEvent(EventListener::Event evt);
	bool GetCompleted() { return completed; };
private:
	bool completed;
	Platform gorm;
	LevelLoader *loader;
	InputManager input;
	World BoxWorld;
	vector<GameObject*> Objects;
	B2Object obj;
};

#endif // !LEVEL1_H

