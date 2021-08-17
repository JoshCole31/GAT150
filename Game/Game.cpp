#include "Game.h"

void Game::Initialize()
{
	//create engine
	engine = std::make_unique<jc::Engine>();
	engine->Startup();
	engine->Get<jc::Renderer>()->Create("GAT150", 800, 600);

	//create scene
	scene = std::make_unique<jc::Scene>();
	scene->engine = engine.get();

	jc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
	jc::SetFilePath("../Resources");

	//actors
	std::unique_ptr <jc::Actor> actor = std::make_unique<jc::Actor>(jc::Transform{ jc::Vector2{400,300} });
	{
		std::unique_ptr<jc::SpriteComponent> component = std::make_unique<jc::SpriteComponent>();
		component->texture = engine->Get<jc::ResourceSystem>()->Get<jc::Texture>("sf2.png", engine->Get<jc::Renderer>());
		actor->AddComponent(std::move(component));
	}
	{
		std::unique_ptr <jc::physicsComponent> component = std::make_unique<jc::physicsComponent>();
		component->ApplyForce(jc::Vector2::right*200);
		actor->AddComponent(std::move(component));
	}
	scene->Addactor(std::move(actor));

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
