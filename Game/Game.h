#pragma once
#include"Engine.h"

class Game
{
public:
	enum class eState
	{
		Rest,
		Title,
		StartGame,
		StartLevel,
		Level,
		PlayerDead,
		GameOver
	};

public:

	void Initialize();
	void Shutdown();

	void Update();
	void Draw();

	bool IsQuit() { return quit; }
private:
	void Rest();
	void Title();
	void StartGame();
	void StartLevel();
	void Level();
	void PlayerDead();
	void GameOver();

	void OnAddScore(const jc::Event& event);

public:
	std::unique_ptr <jc::Engine> engine;
	std::unique_ptr <jc::Scene> scene;

private:
	bool quit = false;

	eState state = eState::Rest;
	float spawnTimer;
	float stateTimer = 0;
	int score = 0;
};

extern int global;