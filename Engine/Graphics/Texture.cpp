#include "Texture.h"
#include "Graphics/Renderer.h"
#include <SDL_image.h>
#include <iostream>

namespace jc {

	bool Texture::Load(const std::string& name,void* data)
	{
		renderer = static_cast<Renderer*>(data)->renderer;

		//load surface
		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr) 
		{
			std::cout << "IMG_Load Error: " << SDL_GetError() << std::endl;
			return false;
		}

		//Creat texture
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (texture == nullptr) 
		{
			std::cout << "SDL_CreateTextureFromSurfaceError: " << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}
}
