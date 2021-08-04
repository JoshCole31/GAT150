#include "Engine.h"
#include <SDL_Image.h>
#include <SDL.h>
#include <iostream>

int main(int, char**)
{
	jc::Engine engine;
	engine.Startup();

	engine.Get<jc::Renderer>()->Create("GAT150", 800, 600);

	std::cout << jc::GetFilePath() << std::endl;
	jc::SetFilePath("../Resources");
	std::cout << jc::GetFilePath() << std::endl;

	std::shared_ptr<jc::Texture> texture = engine.Get<jc::ResourceSystem>()->Get<jc::Texture>("sf2.png",engine.Get<jc::Renderer>());

	
	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		engine.Get<jc::Renderer>()->BeginFrame();

		jc::Vector2 position{ 300,400 };
		engine.Get<jc::Renderer>()->Draw(texture,position);


		engine.Get<jc::Renderer>()->endFrame();


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