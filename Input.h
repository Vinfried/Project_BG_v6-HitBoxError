#pragma once
#include "SDL.h"

class Input
{
public:
	Input();
	~Input();

	void updateInput(bool& bIsGameOver);

	//detect if a particular key is up or down
	bool isKeyDown(SDL_Scancode key);
	bool isKeyUp(SDL_Scancode key);

private:
	//store the state of each key
	const Uint8* keyboardState;
	
};

