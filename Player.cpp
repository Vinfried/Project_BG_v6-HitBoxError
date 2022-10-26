#include "Player.h"
#include "SDL.h"

Player::Player(Texture* characterTexture, Vector2 pos, int numberOfFrames)
	:Character::Character(characterTexture, pos, numberOfFrames)
{

}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	Character::update(deltaTime);
}

void Player::processInput(Input *userInput)
{
	float movementX = 0.0f;
	float movementY = 0.0f;

	if (userInput->isKeyDown(SDL_SCANCODE_W)) {
		movementY = -1.0f;
	}

	if (userInput->isKeyDown(SDL_SCANCODE_S)) {
		movementY = 1.0f;
	}

	if (userInput->isKeyDown(SDL_SCANCODE_A)) {
		movementX = -1.0f;
	}
	
	if (userInput->isKeyDown(SDL_SCANCODE_D)) {
		movementX = 1.0f;
	}

	if (userInput->isKeyDown(SDL_SCANCODE_SPACE)) {
		//store the colliders overlapping our collider
		vector<Collider*> otherColliders = getCollision()->getOverlappingColliders();
		//run through all the colliders we're overlapping
		for (unsigned int i = 0; i < otherColliders.size(); ++i) {
			SDL_Log("Collider detected, Enemy: Ouch!");
		}
	}

	setMovementAxis(Vector2(movementX, movementY));
}


