#include "Engine.h"
#include <SDL_Image.h>
#include <SDL.h>
#include <iostream>

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, 800, 600, SDL_WINDOW_SHOWN |SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

	std::cout << jc::GetFilePath() << std::endl;
	jc::SetFilePath("../Resources");
	std::cout << jc::GetFilePath() << std::endl;

	//load surface
	SDL_Surface* surface = IMG_Load("sf2.png");
	//Creat texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_RenderPresent(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}


	SDL_Quit();

	return 0;
}