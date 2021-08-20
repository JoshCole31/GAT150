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


	rapidjson::Document document;
	bool success = jc::json::Load("json.txt", document);
	assert(success);

	std::string str;
	jc::json::Get(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	jc::json::Get(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	jc::json::Get(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	jc::json::Get(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	jc::json::Get(document, "float", f);
	std::cout << f << std::endl;

	jc::Vector2 v2;
	jc::json::Get(document, "vector2", v2);
	std::cout << v2 << std::endl;

	jc::Color color;
	jc::json::Get(document, "color", color);
	std::cout << color << std::endl;


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