#include "InputSystem.h"

namespace jc {

	InputSystem::eKeyState InputSystem::GetKeyState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsKeyDown(id);
		bool prevKeyDown = IsPreviousKeyDown (id);

		if(keyDown) 
		{
			state = (prevKeyDown) ? eKeyState::Held :eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
		}
			return state;
	}

	bool InputSystem::IsKeyDown(int id)
	{
		return keyboardState[id];
	}

	bool InputSystem::IsPreviousKeyDown(int id)
	{
		return prevKeyboardState[id];
	}

	void InputSystem::Startup()
	{
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(&numKeys);
		keyboardState.resize(numKeys);
		std::copy(keyboardStateSDL,keyboardStateSDL+numKeys,keyboardState.begin());
		prevKeyboardState = keyboardState;
	}

	void InputSystem::Shutdown()
	{
	}

	void InputSystem::Update(float dt)
	{
		prevKeyboardState = keyboardState;
		const Uint8* keyboardStateSDL = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardStateSDL, keyboardStateSDL + numKeys, keyboardState.begin());

		prevMouseButtonState = mouseButtonState;
		int x, y;
		Uint32 buttons = SDL_GetMouseState(&x, &y);
		mousePosition = jc::Vector2{ x,y };
		mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;//buttons [0001]
		mouseButtonState[1] = buttons & SDL_BUTTON_MMASK;//buttons [0010]
		mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;//buttons [0100]

	}

	InputSystem::eKeyState InputSystem::GetButtonState(int id)
	{
		eKeyState state = eKeyState::Idle;

		bool keyDown = IsButtonDown(id);
		bool prevKeyDown = IsPrevButtonDown(id);

		if (keyDown)
		{
			state = (prevKeyDown) ? eKeyState::Held : eKeyState::Pressed;
		}
		else
		{
			state = (prevKeyDown) ? eKeyState::Release : eKeyState::Idle;
		}
		return state;
	}

}
