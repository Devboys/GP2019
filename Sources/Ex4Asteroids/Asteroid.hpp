#pragma once
#include "GameObject.hpp"

class Asteroid : public GameObject{

public:
	Asteroid(glm::vec2 pos, sre::Sprite& sprite);
	void update(float deltaTime);

private:
	float rotationSpeed;
	glm::vec2 velocity;
};