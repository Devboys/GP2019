#include "Asteroid.hpp"
#include "iostream";
#include "sre/Renderer.hpp"

Asteroid::Asteroid(glm::vec2 pos, sre::Sprite& sprite, float radius) : GameObject(sprite)
{
	position = pos;
	//rotationSpeed is randomized between 50-149f
	rotationSpeed = 50 + rand() % 100;
	velocity = glm::vec2(-80 + rand() %  161, -80 + rand() % 161);

	this->radius = radius;
	
}

void Asteroid::update(float deltaTime) 
{
	//apply velocity
	position += velocity * deltaTime;

	//apply rotation
	rotation += deltaTime * rotationSpeed;

	//wrap-around
	wrapObject(position, sre::Renderer::instance->getWindowSize());
}

void Asteroid::onCollision(std::shared_ptr<GameObject> other) {

}