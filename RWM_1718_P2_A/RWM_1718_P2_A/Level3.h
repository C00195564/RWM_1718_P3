#ifndef LEVEL3_H
#define LEVEL3_H

#include "SceneManager.h"
#include "Scene.h"
#include "GameData.h"
#include "World.h"
#include "Basic2DObjects.h"
#include "stdafx.h"
#include "Platform.h"

class Level3 : public Scene, public EventListener
{
public:
	Level3(LevelLoader* l);
	~Level3();

	void Update(unsigned int);
	void Draw(Renderer& renderer);
	void Event();
	bool GetQuit();
	void Init(Renderer& r);
	void onEvent(EventListener::Event evt);
	bool GetCompleted() { return completed; };
private:
	bool completed;
	LevelLoader *loader;
	InputManager input;
	World BoxWorld;
	vector<GameObject*> Objects;
	B2Object obj;
};

#endif // !LEVEL1_H

