#pragma once
#include "GameObject.hpp"

class Bang : public GameObject {
public:
	Bang(glm::vec2 position, sre::Sprite spr);
	void update(float deltaTime);

private:
	float deathTimer;
	float duration = 1;
};