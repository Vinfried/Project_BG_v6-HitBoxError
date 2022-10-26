#include "GameObject.h"
#include "Vector2.h"
#include "SDL.h"

GameObject::GameObject()
{
	position = Vector2().zero();
	objectTexture = nullptr;
	objectCenter = position;
	collision = nullptr;
	numberOfFrames = 1;
}

GameObject::~GameObject()
{
}

void GameObject::draw(SDL_Renderer* renderer)
{
}

void GameObject::update(float deltaTime)
{
	//this will find the object center based on the textuure if there is one
	findObjectCenter();
	//this will update the collision position to match the object center
	updateCollisionPositions();

}

void GameObject::processInput(Input *userInput)
{
}

void GameObject::setCollision(Vector2 position, Vector2 halfDimentions, bool shouldDebug)
{
	//if there is a collision curently
	if (collision != nullptr) {
		//clear it
		delete(collision);
	}
	//define the gameobjects collision
	collision = new Collider(this, position, halfDimentions,shouldDebug);
}

void GameObject::setCollisionDimentions(Collider* collision,Vector2 halfDimentions)
{
	if (collision != nullptr) {
		//set the width of the collider
		collision->colliderRect.w = halfDimentions.x * 2;
		//set the height of the collider
		collision->colliderRect.h = halfDimentions.y * 2;
	}
}

void GameObject::updateCollisionPositions()
{
	//check if there is even a collision
	if (collision != nullptr) {
		float w = collision->colliderRect.w / 2;
		float h = collision->colliderRect.h / 2;

		//change the position of the collider equal to the object center
		//center the collider based on it's half dimention
		collision->colliderRect.x = objectCenter.x - w;
		collision->colliderRect.y = objectCenter.y - h;
	}
}

void GameObject::findObjectCenter()
{
	//make sure we set back to the position each frame
	objectCenter = position;

	if (objectTexture != nullptr) {
		float w = objectTexture->getImageWidth() / SDL_max(1, numberOfFrames);
		float h = objectTexture->getImageHeight();

		w /= 2;
		h /= 2;

		objectCenter.x += w;
		objectCenter.y += h;
	}
}

Collider* GameObject::getCollision()
{
	return collision;
}
