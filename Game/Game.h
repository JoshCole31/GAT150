#pragma once
#include"Engine.h"

class Game
{

public:

	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }
private:

	
public:
	std::unique_ptr <jc::Engine> engine;
	std::unique_ptr <jc::Scene> scene;

private:
	bool quit = false;
};

extern int global;