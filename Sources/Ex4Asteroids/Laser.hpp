#pragma once
#include "GameObject.hpp"
#include "sre/Sprite.hpp"

class Laser : public GameObject{

public:
	Laser(glm::vec2 direction, glm::vec2 poss, sre::Sprite sprite);

	void update(float deltaTime);

private:
	glm::vec2 direction;
	float speed = 500;
	float deathTimer;
	float duration = 1; //laser persists for 1 sec, then destroys itself.
};