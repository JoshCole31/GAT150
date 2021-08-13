#include "Game.h"
//#include "Engine.h"
//#include <SDL_Image.h>
//#include <SDL.h>
//#include <iostream>
//#include<cassert>



int main(int, char**)
{
	Game game;
	game.Initialize();

	bool quit = false;
	SDL_Event event;

	while (!quit&& !game.IsQuit())
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	
		game.Update();
		game.Draw();

		//scene.Update(engine.time.deltaTime);
	}

	SDL_Quit();

	return 0;
}