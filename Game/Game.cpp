#include "Game.h"


//int global = 10;

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

	rapidjson::Document document;
	bool success = jc::json::Load("scene.txt", document);
	assert(success);
	scene->Read(document);
	////actors
	//std::unique_ptr <jc::Actor> actor = std::make_unique<jc::Actor>(jc::Transform{ jc::Vector2{400,300},0,1 });
	//{
	//	//jc::SpriteComponent* component = actor->AddComponent<jc::SpriteComponent>();
	//	//jc::SpriteAnimationComponent* component = actor->AddComponent<jc::SpriteAnimationComponent>();

	//	auto component = jc::ObjectFactory::Instance().Create<jc::SpriteAnimationComponent>("SpriteAnimationComponent");
	//	component->texture = engine->Get<jc::ResourceSystem>()->Get<jc::Texture>("spritesheet.png", engine->Get<jc::Renderer>());
	//	component->fps = 15;
	//	component->numFramesX = 12;
	//	component->numFramesY = 8;
	//	actor->AddComponent(std::move(component));
	//}
	//{
	//	jc::physicsComponent* component =actor->AddComponent<jc::physicsComponent>();
	//	//component->ApplyForce(jc::Vector2::right*200);
	//}
	//scene->Addactor(std::move(actor));

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
