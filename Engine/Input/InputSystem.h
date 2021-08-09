#pragma once
#include "Framework/System.h"
#include <vector>
#include <SDL.h>
#include <algorithm>
#include<array>
#include "Math/Vector2.h"

namespace jc
{
	class InputSystem : public System
	{
	public:
		enum class eKeyState
		{
			Idle, Pressed, Held, Release

		};
		enum class eMouseButton
		{
			Left,
			middle,
			Right
		};
	public:
		eKeyState GetKeyState(int id);

		bool IsKeyDown(int id);

		bool IsPreviousKeyDown(int id);

		// Inherited via System
		void Startup() override;
		void Shutdown() override;

		void Update(float dt) override;
		const Vector2& GetMousePostion() const { return mousePosition ;}
		bool IsButtonDown(int id) { return mouseButtonState[id]; }
		bool IsPrevButtonDown(int id) { return prevMouseButtonState[id]; }
		eKeyState GetButtonState(int id);



	private:
		std::vector<Uint8> keyboardState;
		std::vector<Uint8> prevKeyboardState; 
		int numKeys;

		Vector2 mousePosition;
		std::array<Uint8,3> mouseButtonState;
		std::array<Uint8, 3> prevMouseButtonState;
	};

}