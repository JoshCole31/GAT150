#include "Engine.h"
#include <SDL_Image.h>
#include <SDL.h>
#include <iostream>
#include<cassert>



int main(int, char**)
{
	jc::Engine engine;
	engine.Startup();

	engine.Get<jc::Renderer>()->Create("GAT150", 800, 600);

	jc::Scene scene;
	scene.engine = &engine;

	///std::cout << jc::GetFilePath() << std::endl;
	jc::SetFilePath("../Resources");
	engine.Get<jc::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
	engine.Get<jc::AudioSystem>()->AddAudio("music", "audio/SpaceCrusadeMusic.mp3");
	jc::AudioChannel channle = engine.Get<jc::AudioSystem>()->PlayAudio("music",1,1,true);
	std::shared_ptr<jc::Texture> texture = engine.Get<jc::ResourceSystem>()->Get<jc::Texture>("sf2.png",engine.Get<jc::Renderer>());

	for (size_t i = 0; i < 10; i++) {

		jc::Transform transform{ jc::Vector2{jc::RandomRange(0,800),jc::RandomRange(0,600) }, jc::RandomRange(0,360),1.0f};
		std::unique_ptr<jc::Actor> actor = std::make_unique<jc::Actor>(transform,texture);
		scene.Addactor(std::move (actor));
	}

	int size = 16;
	std::shared_ptr<jc::Font> font = engine.Get<jc::ResourceSystem>()->Get<jc::Font>("fonts/arial.ttf", &size);

	// create font texture
	std::shared_ptr<jc::Texture> textTexture = std::make_shared<jc::Texture>(engine.Get<jc::Renderer>());
	// set font texture with font surface
	textTexture->Create(font->CreateSurface("Hello world", jc::Color{ 1, 1, 1 }));
	// add font texture to resource system
	engine.Get<jc::ResourceSystem>()->Add("textTexture", textTexture);




	bool quit = false;
	SDL_Event event;
	float quitTime = engine.time.time + 3.0f;

	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	
		engine.Update();
		if (engine.Get<jc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == jc::InputSystem::eKeyState::Pressed)
		{
			quit =true;
		}

		if(engine.Get<jc::InputSystem>()->GetButtonState((int)jc::InputSystem::eMouseButton::Left)==jc::InputSystem::eKeyState::Pressed)
		{
			//channle.Stop();
			channle.SetPitch(jc::RandomRange(0.2f, 2.0f));

			jc::Vector2 position = engine.Get<jc::InputSystem>()->GetMousePostion();
			std::shared_ptr<jc::Texture> textureP = engine.Get<jc::ResourceSystem>()->Get<jc::Texture>("Particle1.png", engine.Get<jc::Renderer>());

			engine.Get<jc::ParticleSystem>()->Create(position,2,2,textureP,3);

			engine.Get<jc::AudioSystem>()->PlayAudio("explosion",jc::RandomRange(0.2f,2.0f));

			std::cout << position.x << " " << position.y << std::endl;
		}
		


		scene.Update(engine.time.deltaTime);

		//if (engine.time.time >= quitTime) quit = true;
		//engine.time.timeScale = 0.1f;


		//draw
		engine.Get<jc::Renderer>()->BeginFrame();

		jc::Transform t;
		t.position = { 30, 30 };
		engine.Get<jc::Renderer>()->Draw(textTexture, t);

		scene.Draw(engine.Get<jc::Renderer>());
		engine.Draw(engine.Get<jc::Renderer>());

		engine.Get<jc::Renderer>()->endFrame();


		//engine.Get<jc::Renderer>()->Draw(texture, position);//can put rotation and scale here 
		/*for (size_t i = 0; i < 50; i++)
		{
			SDL_Rect src{ 32,64,32,64 };
			SDL_Rect dest{ jc::RandomRangeInt(0,screen.x),jc::RandomRangeInt(0,screen.y),64,96 };

			SDL_RenderCopy(renderer, texture, &src, &dest);
		}*/
		
	}

	SDL_Quit();

	return 0;
}