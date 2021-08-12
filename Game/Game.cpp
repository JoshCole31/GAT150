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

	jc::SetFilePath("../Resources");

	//game
	engine->Get<jc::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<jc::AudioSystem>()->AddAudio("EnemyShoot", "EnemyShoot.wav");
	engine->Get<jc::AudioSystem>()->AddAudio("PlayerShoot", "PlayerShoot.wav");
	engine->Get<jc::AudioSystem>()->AddAudio("Music", "SpaceCrusadeMusic.mp3");

	engine->Get<jc::EventSystem>()->Subcribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<jc::EventSystem>()->Subcribe("PlayerHit", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));
	engine->Get<jc::EventSystem>()->Subcribe("SpawnPowerUP", std::bind(&Game::OnRockdistroyed, this, std::placeholders::_1));
	engine->Get<jc::EventSystem>()->Subcribe("Heal", std::bind(&Game::OnHeal, this, std::placeholders::_1));
	engine->Get<jc::EventSystem>()->Subcribe("spawnEnemys", std::bind(&Game::OnSpawnEnemys, this, std::placeholders::_1));
	engine->Get<jc::EventSystem>()->Subcribe("spawnAsteroids", std::bind(&Game::OnSpawnAsteroids, this, std::placeholders::_1));

	engine->Get<jc::AudioSystem>()->AddAudio("music", "audio/SpaceCrusadeMusic.mp3");
	jc::AudioChannel musicChannel = engine->Get<jc::AudioSystem>()->PlayAudio("music", 1, 1, true);
	std::shared_ptr<jc::Texture> texture = engine->Get<jc::ResourceSystem>()->Get<jc::Texture>("sf2.png", engine->Get<jc::Renderer>());

	for (size_t i = 0; i < 10; i++) {

		jc::Transform transform{ jc::Vector2{jc::RandomRange(0,800),jc::RandomRange(0,600) }, jc::RandomRange(0,360),1.0f };
		std::unique_ptr<jc::Actor> actor = std::make_unique<jc::Actor>(transform, texture);
		scene->Addactor(std::move(actor));
	}

	int size = 16;
	std::shared_ptr<jc::Font> font = engine->Get<jc::ResourceSystem>()->Get<jc::Font>("fonts/arial.ttf", &size);

	// create font texture
	textTexture = std::make_shared<jc::Texture>(engine->Get<jc::Renderer>());
	// set font texture with font surface
	textTexture->Create(font->CreateSurface("Hello world", jc::Color{ 1, 1, 1 }));
	// add font texture to resource system
	engine->Get<jc::ResourceSystem>()->Add("textTexture", textTexture);


	//stateFunction = &Game::UpdateTitle;
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
	
}

void Game::Update()
{
	float dt = engine->time.deltaTime;
	stateTimer += (dt);
	switch (state)
	{
	case Game::eState::Title:
		if (engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == jc::InputSystem::eKeyState::Pressed)
		{
			state = eState::StartGame;
			scene->engine->Get<jc::AudioSystem>()->PlayAudio("Music");
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
			state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateLevelStart(dt);
		state = eState::Game;
		break;
	case Game::eState::Game:
		/*if (scene->GetActors<Enemy>().size() == 0)
		{
			state = eState::Gameover;
		}*/
		break;
		break;
	case Game::eState::Gameover:
		/*if (Core::Input::IsPressed(VK_SPACE))
		{
			state = eState::StartGame;
		}
		break*/;
	default:
		break;
	}

	engine->Update();
	scene->Update(dt);

	if (engine->Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == jc::InputSystem::eKeyState::Pressed)
	{
		quit = true;
	}

	if (engine->Get<jc::InputSystem>()->GetButtonState((int)jc::InputSystem::eMouseButton::Left) == jc::InputSystem::eKeyState::Pressed)
	{
		//musicChannel.Stop();
		musicChannel.SetPitch(jc::RandomRange(0.2f, 2.0f));

		jc::Vector2 position = engine->Get<jc::InputSystem>()->GetMousePostion();
		particleTexture = engine->Get<jc::ResourceSystem>()->Get<jc::Texture>("Particle1.png", engine->Get<jc::Renderer>());

		engine->Get<jc::ParticleSystem>()->Create(position, 2, 2, particleTexture, 3);

		engine->Get<jc::AudioSystem>()->PlayAudio("explosion", jc::RandomRange(0.2f, 2.0f));

		std::cout << position.x << " " << position.y << std::endl;
	}
}

void Game::Draw()
{
	switch (state)
	{
	case Game::eState::Title:
		/*graphics.SetColor(jc::Color::Red);
		graphics.DrawString(380, 300+static_cast<int>(std::sin(stateTimer*6.0f)*20), "Vectrex");
		graphics.SetColor(jc::Color::Green);
		graphics.DrawString(340, 360, "Press Space to Start");*/
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::Gameover:
		/*scene->RemoveAllActors();
		graphics.SetColor(jc::Color::Red);
		graphics.DrawString(340, 250, "Game Over");
		graphics.SetColor(jc::Color::White);
		graphics.DrawString(340,280,"Your score ");
		graphics.DrawString(360,300,std::to_string(score).c_str());
		graphics.DrawString(300, 320, "Press spcae to play again");*/
		break;
	default:
		break;
	}

	/*graphics.SetColor(jc::Color::White);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(670, 20,"lives left");*/
	if (lives >= 0) 
	{
		//graphics.DrawString(750, 20, std::to_string(lives).c_str());
	}
	else
	{
		//graphics.DrawString(750, 20, "0");

	}

	engine->Get<jc::Renderer>()->BeginFrame();

	jc::Transform t;
	t.position = { 30, 30 };
	engine->Get<jc::Renderer>()->Draw(textTexture, t);

	scene->Draw(engine->Get<jc::Renderer>());
	engine->Draw(engine->Get<jc::Renderer>());

	engine->Get<jc::Renderer>()->endFrame();
}

void Game::UpdateLevelStart(float dt)
{
	/*scene->Addactor(std::make_unique<Player>(jc::Transform{ jc::Vector2{ 400.0f, 300.0f }, 0.0f, 3.0f }, engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("shape.txt"), 300.0f));
	scene->Addactor(std::make_unique<Asteroid>(jc::Transform{ jc::Vector2{jc::RandomRange(0,800), jc::RandomRange(0, 600) }, jc::RandomRange(0, jc::TwoPi), 5.0f }, engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("rock.txt"), 100.0f));
	
	for (size_t i = 0; i < 4; i++)
	{
		scene->Addactor(std::make_unique<Enemy>(jc::Transform{ jc::Vector2{jc::RandomRange(0,800), jc::RandomRange(0, 600) }, jc::RandomRange(0, jc::TwoPi), 5.0f }, engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("EnemyShape.txt"), 100.0f));
	}*/
}

void Game::UpdateTitle(float dt)
{
	//if (Core::Input::IsPressed(VK_SPACE))
	//{
	//	stateFunction = &Game::UpdateTitle;
	//	//state = eState::StartGame;
	//}
}

void Game::OnAddPoints(const jc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerHit(const jc::Event& event)
{
	lives -= std::get<int>(event.data);
	if (lives < 0) 
	{ 
		state = eState::Gameover;
		jc::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yes i'm dead!");
		scene->engine->Get<jc::EventSystem>()->Notify(event);
	};
}

void Game::OnHeal(const jc::Event& event)
{
	if (lives < 5)
	{
		lives++;
	}
}

void Game::OnRockdistroyed(const jc::Event& event)
{
	/*if (scene->GetActors<HealthPack>().size()  >6)
	{
		return;
	}
	scene->Addactor(std::make_unique<HealthPack>(std::get<jc::Vector2>(event.data),engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("healthpack.txt"), 100.0f));*/
}

void Game::OnSpawnEnemys(const jc::Event& event)
{
	/*if (scene->GetActors<Enemy>().size() > 25)
	{
		return;
	}
	float e = std::get<float>(event.data);
	if (e > 0) 
	{
		for (size_t i = 0; i < e; i++)
		{
			scene->Addactor(std::make_unique<Enemy>(jc::Transform{ jc::Vector2{0.0f, jc::RandomRange(0, 600) }, jc::RandomRange(0, jc::TwoPi), 5.0f }, engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("EnemyShape.txt"), 100.0f));
		}
	}*/
}

void Game::OnSpawnAsteroids(const jc::Event& event)
{
	/*if (scene->GetActors<Asteroid>().size() >4)
	{
		return;
	}
	float e = std::get<float>(event.data);
	if (e > 0)
	{
		for (size_t i = 0; i < e; i++)
		{
			scene->Addactor(std::make_unique<Asteroid>(jc::Transform{ jc::Vector2{jc::RandomRange(0,800), 0.0f}, jc::RandomRange(0, jc::TwoPi), 5.0f }, engine->Get<jc::ResourceSystem>()->Get<jc::Shape>("rock.txt"), 100.0f));
		}
	}*/
}
