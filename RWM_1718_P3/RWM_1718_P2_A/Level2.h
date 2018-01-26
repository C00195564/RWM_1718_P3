#ifndef LEVEL2_H
#define LEVEL2_H

#include "SceneManager.h"
#include "Scene.h"
#include "GameData.h"
#include "World.h"
#include "Basic2DObjects.h"
#include "stdafx.h"
#include "Platform.h"

class Level2 : public Scene, public EventListener
{
public:
	Level2(LevelLoader* l);
	~Level2();

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

