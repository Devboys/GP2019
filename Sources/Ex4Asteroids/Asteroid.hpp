#pragma once
#include "GameObject.hpp"
#include "Collidable.hpp"

class Asteroid : public GameObject, public Collidable {

public:
	Asteroid(glm::vec2 pos, sre::Sprite& sprite, float radius);
	void update(float deltaTime);
	
	void onCollision(std::shared_ptr<GameObject> other);

private:
	float rotationSpeed;
	glm::vec2 velocity;
};