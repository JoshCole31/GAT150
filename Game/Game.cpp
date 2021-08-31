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
	}
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

	scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
	engine->Get<jc::Renderer>()->BeginFrame();
	
	engine->Draw(engine->Get<jc::Renderer>());
	scene->Draw(engine->Get<jc::Renderer>());

	engine->Get<jc::Renderer>()->endFrame();
}
