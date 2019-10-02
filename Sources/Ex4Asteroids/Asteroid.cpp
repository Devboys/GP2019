#include "Asteroid.hpp"
#include "iostream";
#include "sre/Renderer.hpp"
#include "Laser.hpp"
#include "GameObjectList.hpp"

Asteroid::Asteroid(glm::vec2 pos, glm::vec2 vel, asteroidType type, std::shared_ptr<sre::SpriteAtlas> atlas) : GameObject()
{
	visible = true;
	sre::Sprite asteroidSprite;
	switch (type) {
	case big:
		asteroidSprite = atlas->get("meteorBrown_big4.png");
		radius = 50.0f;
		break;
	case medium:
		asteroidSprite = atlas->get("meteorBrown_med3.png");
		radius = 25.0f;
		break;
	case small:
		asteroidSprite = atlas->get("meteorBrown_small1.png");
		radius = 10.0f;
		break;
	}
	this->sprite = asteroidSprite;

	this->atlas = atlas;
	this->type = type;
	velocity = vel;
	position = pos;
	//rotationSpeed is randomized between 50-149f
	rotationSpeed = 50 + rand() % 100;

	this->radius = radius;
	
}

void Asteroid::update(float deltaTime) 
{

	//apply velocity
	position += velocity * deltaTime;

	//apply rotation
	rotation += deltaTime * rotationSpeed;

	//wrap-around screen bounds
	wrapObject(position, sre::Renderer::instance->getWindowSize());
}

void Asteroid::onCollision(std::shared_ptr<GameObject> other) {
	if (std::dynamic_pointer_cast<Laser>(other) != nullptr) {

		this->destroyed = true;
		if (type == small) return;

		asteroidType newType;
		switch (type) {
		case big:
			newType = asteroidType::medium;
			break;
		case medium:
			newType = asteroidType::small;
			break;
		}
		glm::vec2 newVel = glm::vec2(velocity.y, -velocity.x);

		GameObjectList::getInstance().addedObjects.push_back(std::shared_ptr<Asteroid>(new Asteroid(position, newVel, newType, atlas)));
		newVel = -newVel;
		GameObjectList::getInstance().addedObjects.push_back(std::shared_ptr<Asteroid>(new Asteroid(position, newVel, newType, atlas)));

	}
}