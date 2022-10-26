#include "Game.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Collectible.h"
#include "Orbs.h"
#include "Input.h"
#include "Collider.h"
#include <iostream>
#include <vector>

using namespace std;

//constructor
Game::Game()
{
	//set the SDL Window and Renderer to null in case it has memory
	sdlWindow = nullptr;
	sdlRenderer = nullptr;

	//Initialise the subsystem in the SDL2 Framework
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {

		bIsGameOver = true;
		//if failed to initialise the subsystem, tell us on console
		cout << "Initialise SDL - failed" << endl;
	}
	else {
		//enable game loop
		bIsGameOver = false;
		//if the subsystem succesfully initialises
		cout << "initialise SDL - success" << endl;
	}

}

//deconstructor
Game::~Game()
{

}

bool Game::Start()
{
	// create the SDL renderer and define it
	sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, -1);

	lastUpdatedTime = SDL_GetTicks();
	
	//make sure the renderer worked
	if (sdlRenderer != nullptr) {
		cout << "Create Renderer - success" << endl;

		//Start detecting input
		userInput = new Input();

		////create some random box colliders
		//Collider* box1 = new Collider(Vector2(150.0f, 150.0f), Vector2(25.0f, 25.0f));
		//Collider* box2 = new Collider(Vector2(200.0f, 150.0f), Vector2(50.0f, 50.0f));
		//
		////add the boxes abothe into the boxcollider array
		//boxColliders.push_back(box1);
		//boxColliders.push_back(box2);


		//initialise the player textertexture
		playerTexture = new Texture();
		//load the texture
		playerTexture->loadImageFromFile("Assets/hero_spritesheet_50x37_109.png", sdlRenderer);
		//construct the player as a character
		Player* playerCharacter = new Player(playerTexture, Vector2(0,0), 109);
		gameObjects.push_back(playerCharacter);
		//add the gameobjects collision to allow to propper detection
		boxColliders.push_back(playerCharacter->getCollision());

		//intialised the enemy texture
		enemyTexture = new Texture();
		//load the enemy texture
		enemyTexture->loadImageFromFile("Assets/goblin-spritesheet-65x35-28.png", sdlRenderer);
	
		//construct the enemy as a Enemy using the enemy texture
		Enemy* enemyCharacter = new Enemy(enemyTexture, Vector2(0,0), 28);
		gameObjects.push_back(enemyCharacter);
		boxColliders.push_back(enemyCharacter->getCollision());

		//construct the second enemy using the same texture
		Enemy* enemyCharacter2 = new Enemy(enemyTexture, Vector2(0,50), 28);
		gameObjects.push_back(enemyCharacter2);
		boxColliders.push_back(enemyCharacter2->getCollision());

		//initialise collectible(orb) texture
		orbsTexture = new Texture();
		//load the orb texture
		orbsTexture->loadImageFromFile("Assets/rotating_orbs_128x32-4.png", sdlRenderer);
		//construct the orb as a collectible
		Orbs* orb = new Orbs(orbsTexture,Vector2(0,100), 4);
		gameObjects.push_back(orb);
		boxColliders.push_back(orb->getCollision());

		return true;
	}
	
	cout << "Create Renderer - failed" << endl;

	return false;
}

void Game::ProcessInput()
{
	userInput->updateInput(bIsGameOver);

	//cycle through all gameobjects and run their input
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->processInput(userInput);
	}
}

void Game::Update()
{
	//Process any changes to the game
	//int seconds = SDL_GetTicks() / 1000;

	//how long has it been since the last frame updated in milliseconds
	unsigned int tick = SDL_GetTicks() - lastUpdatedTime;

	//change the tick to seconds
	float deltaTime = tick / 1000.0f;

	//Refresh the last update time
	lastUpdatedTime = SDL_GetTicks();

	if (userInput->isKeyDown(SDL_SCANCODE_W)) {
		SDL_Log("Pressing the W key");
	}
	//cycle through all gameobjects and run their update
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->update(deltaTime);
	}

	for (unsigned int i = 0; i < boxColliders.size(); ++i) {
		boxColliders[i]->update(deltaTime, boxColliders);
	}
}

void Game::Draw()
{
	//set the draw color
	SDL_SetRenderDrawColor(sdlRenderer, 15, 15, 15, 255);

	//clear the renderer
	SDL_RenderClear(sdlRenderer);


	//cycle through all gameobjects and run their draw
	for (unsigned int i = 0; i < gameObjects.size(); ++i) {
		gameObjects[i]->draw(sdlRenderer);
	}

	for (unsigned int i = 0; i < boxColliders.size(); ++i) {
		boxColliders[i]->draw(sdlRenderer);
	}

	SDL_RenderPresent(sdlRenderer);
}

void Game::Run(const char* title, int width, int height, bool fullscreen)
{
	//define the creation flag
	int creationFlag = 0;

	//if fullscreen is set to false then set to window mode
	if (!fullscreen) {
		creationFlag = SDL_WINDOW_SHOWN;

	}

	else {
		creationFlag = SDL_WINDOW_FULLSCREEN;
	}

	sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, creationFlag);

	//check if the SDL window work
	////create the renderer and start game loop
	if (sdlWindow != nullptr && Start()) {
		cout << "Create window - success" << endl;

		//run the loop
		while (!bIsGameOver) {
			//check for the player input
			ProcessInput();

			//process any changes that were made either by input or game code
			Update();

			//draw everything to screen
			Draw();

		}
	}

	//debug or was exited
	cout << "Create Window - failed or was exited" << endl;

	Shutdown();
	Destroy();


}

void Game::Shutdown()
{
}

void Game::Destroy()
{
	//dealocate the window
	SDL_DestroyWindow(sdlWindow);

	//dealocate the renderer
	SDL_DestroyRenderer(sdlRenderer);

	//shutdown the SDL framework
	SDL_Quit();

}
