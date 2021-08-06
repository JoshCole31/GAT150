#pragma once
#include "Framework/System.h"
#include <vector>
#include <SDL.h>
#include <algorithm>

namespace jc
{
	class InputSystem : public System
	{
	public:
		enum class eKeyState 
		{
			Idle, Pressed, Held, Release
	
		};
	public:
		eKeyState GetKeyState(int id);

		bool IsKeyDown(int id);

		bool IsPreviousKeyDown(int id);

		// Inherited via System
		 void Startup() override;

		 void Shutdown() override;

		 void Update(float dt) override;

	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState; 
		int numKeys;
	};

}