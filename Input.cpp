#include "Input.h"
#include "SDL.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::updateInput(bool& bIsGameOver)
{
	SDL_Event aEvent;
	if (SDL_PollEvent(&aEvent)) {

		//detect the type of input used
		switch (aEvent.type) {
		
		case SDL_KEYDOWN:
			keyboardState = SDL_GetKeyboardState(NULL);
			break;

		case SDL_KEYUP:
			keyboardState = SDL_GetKeyboardState(NULL);
			break;

		default:
			break;

			

		}

		//when you hit the cross button on the app, close the game
		if (aEvent.type == SDL_QUIT) {
			bIsGameOver == true;
		}
	}
}

bool Input::isKeyDown(SDL_Scancode key)
{
	if (keyboardState != nullptr && keyboardState[key] == true) {
		return true;
	}

	return false;
}

bool Input::isKeyUp(SDL_Scancode key)
{
	if (keyboardState != nullptr && keyboardState[key] == true) {
		return false;
	}

	return true;
}
