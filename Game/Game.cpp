#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/EnemyComponent.h"
#include "GameComponent/PickupComponent.h"

//int global = 10;

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<jc::Engine>();
	engine->Startup();
	engine->Get<jc::Renderer>()->Create("GAT150", 800, 600);

	//register classes
	REDISTER_CLASS(PlayerComponent);
	REDISTER_CLASS(EnemyComponent);
	REDISTER_CLASS(PickupComponent);



	//create scene
	scene = std::make_unique<jc::Scene>();
	scene->engine = engine.get();

	jc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	jc::SetFilePath("../Resources");

	//events
	engine->Get<jc::EventSystem>()->Subcribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
	engine->Get<jc::EventSystem>()->Subcribe("player_hurt", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));
	engine->Get<jc::EventSystem>()->Subcribe("player_heal", std::bind(&Game::OnPlayerHeal, this, std::placeholders::_1));
	//player death


	/*
	for (int i = 0; i < 10; i++) 
	{
		auto actor = jc::ObjectFactory::Instance().Create<jc::Actor>("Coin");
		actor->transform.position = jc::Vector2{ jc::RandomRange(0,800),jc::RandomRange(100,300) };
		scene->Addactor(std::move(actor));
	}
	for (int i = 0; i < 10; i++)
	{
		auto actor = jc::ObjectFactory::Instance().Create<jc::Actor>("Bat");
		actor->transform.position = jc::Vector2{ jc::RandomRange(0,800),jc::RandomRange(100,300) };
		scene->Addactor(std::move(actor));
	}*/
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
	
}

void Game::Update()
{
	engine->Update();

	if (engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == jc::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}
	
	switch (state)
	{
	case Game::eState::Rest:
		Rest();
		break;
	case Game::eState::Title:
		Title();
		break;
	case Game::eState::StartGame:
		StartGame();
		break;
	case Game::eState::StartLevel:
		StartLevel();
		break;
	case Game::eState::Level:
		Level();
		break;
	case Game::eState::PlayerDead:
		PlayerDead();
		break;
	case Game::eState::GameOver:
		GameOver();
		break;
	default:
		break;
	}

	//update score 
	auto scoreActor = scene->FindActor("Score");
	if (scoreActor)
	{
		scoreActor->GetComponent<jc::TextComponent>()->SetText(std::to_string(score));
	}
	auto livesActor = scene->FindActor("numLives");
	if (livesActor)
	{
		livesActor->GetComponent<jc::TextComponent>()->SetText(std::to_string(lives));
	}
	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<jc::Renderer>()->BeginFrame();
	
	engine->Draw(engine->Get<jc::Renderer>());
	scene->Draw(engine->Get<jc::Renderer>());

	engine->Get<jc::Renderer>()->endFrame();
}

void Game::Rest()
{
	scene->RemoveAllActors();

	rapidjson::Document document;
	bool success = jc::json::Load("title.txt", document);
	assert(success);

	scene->Read(document);

	lives = 5;
	numOfEnemys = 0;
	score = 0;
	heathpacks = 0;
	state = eState::Title;
}

void Game::Title()
{
	
	if (engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == jc::InputSystem::eKeyState::Pressed)
	{
		auto title = scene->FindActor("Title");
		title->active = false;

		state = eState::StartGame;
	}

}

void Game::StartGame()
{
	rapidjson::Document document;
	bool success = jc::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);

	jc::Tilemap tilemap;
	tilemap.scene = scene.get();
	success = jc::json::Load("map.txt", document);
	assert(success);
	tilemap.Read(document);
	tilemap.Create();

	state = eState::StartLevel;
	stateTimer = 0;
}

void Game::StartLevel()
{
	stateTimer += engine->time.deltaTime;
	if (stateTimer >= 1)
	{
		auto player = jc::ObjectFactory::Instance().Create<jc::Actor>("Player");
		player->transform.position = jc::Vector2{ 400,350 };
		scene->Addactor(std::move(player));

		spawnTimer = 2;
		state = eState::Level;
	}
}

void Game::Level()
{
	spawnTimer -= engine->time.deltaTime;
	if (spawnTimer<=0)
	{
		spawnTimer = jc::RandomRange(1, 3);
		auto Coin = jc::ObjectFactory::Instance().Create<jc::Actor>("Coin");
		Coin->transform.position = jc::Vector2{ jc::RandomRange(100,700),150.0f };
		scene->Addactor(std::move(Coin));
	}
	if (heathpacks <= 1&& lives<=5)
	{
		
		auto Health = jc::ObjectFactory::Instance().Create<jc::Actor>("Health");
		Health->transform.position = jc::Vector2{ jc::RandomRange(100,700),150.0f};
		scene->Addactor(std::move(Health));
		heathpacks++;
	}
	if (score == 10 && numOfEnemys ==0) 
	{
		auto enemy = jc::ObjectFactory::Instance().Create<jc::Actor>("Bat");
		enemy->transform.position = jc::Vector2{ jc::RandomRange(100,700),150.0f };
		scene->Addactor(std::move(enemy));
		numOfEnemys++;
	}
	if (score == 50 && numOfEnemys == 1)
	{
		auto enemy = jc::ObjectFactory::Instance().Create<jc::Actor>("Bat");
		enemy->transform.position = jc::Vector2{ jc::RandomRange(100,700),150.0f };
		scene->Addactor(std::move(enemy));
		numOfEnemys++;
	}
	if (score == 100 && numOfEnemys == 2)
	{
		auto enemy = jc::ObjectFactory::Instance().Create<jc::Actor>("Bat");
		enemy->transform.position = jc::Vector2{ jc::RandomRange(100,700),150.0f };
		scene->Addactor(std::move(enemy));
		numOfEnemys++;
	}
	if (score > 250 && numOfEnemys == 3)
	{
		auto enemy = jc::ObjectFactory::Instance().Create<jc::Actor>("Bat");
		enemy->transform.position = jc::Vector2{ jc::RandomRange(100,700),150.0f };
		scene->Addactor(std::move(enemy));
		numOfEnemys++;
	}
}

void Game::PlayerDead()
{
	scene->RemoveAllActors();

	state = eState::GameOver;

	rapidjson::Document document;
	bool success = jc::json::Load("GameOver.txt", document);
	assert(success);
	scene->Read(document);
}

void Game::GameOver()
{
	auto gameOverscore = scene->FindActor("gameOverscore");
	gameOverscore->GetComponent<jc::TextComponent>()->SetText(std::to_string(score));

	if (engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == jc::InputSystem::eKeyState::Pressed)
	{
	  state = eState::Rest;
	}
}

void Game::OnAddScore(const jc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerHit(const jc::Event& event)
{
	lives -= std::get<int>(event.data);
	if (lives < 0)
	{
		state = eState::PlayerDead;
	}
}

void Game::OnPlayerHeal(const jc::Event& event)
{
	lives++;
	heathpacks--;
}

