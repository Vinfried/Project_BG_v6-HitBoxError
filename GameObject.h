#pragma once

#include"SDL.h"
#include "Texture.h"
#include "Vector2.h"
#include "Input.h"
#include "Collider.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void draw(SDL_Renderer* renderer);
	virtual void update(float deltaTime);
	virtual void processInput(Input *userInput);

	//this is going to create a collision for the game object
	void setCollision(Vector2 position, Vector2 halfDimentions, bool shouldDebug = true);

	//this will change the width and height of the collider
	void setCollisionDimentions(Collider* collision, Vector2 halfDimentions);

	//this will move the position of the collision based on the objects center
	void updateCollisionPositions();
	void findObjectCenter();

	//Get the collision publicly
	Collider* getCollision();

protected:
	//position for the game object to display
	Vector2 position;
	//the objects texture
	Texture* objectTexture;
	//Collider
	Collider* collision;
	//get the center of the object
	Vector2 objectCenter;
	//number of frames in the object texture
	unsigned int numberOfFrames;
};

