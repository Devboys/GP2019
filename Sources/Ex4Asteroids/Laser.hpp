#pragma once
#include "GameObject.hpp"
#include "sre/Sprite.hpp"
#include "Collidable.hpp"

class Laser : public GameObject, public Collidable{

public:
	Laser(glm::vec2 direction, glm::vec2 poss, sre::Sprite sprite, float radius);

	void update(float deltaTime);

	void onCollision(std::shared_ptr<GameObject> other);

private:
	glm::vec2 direction;
	float speed = 500;
	float deathTimer;
	float duration = 1; //laser persists for 1 sec, then destroys itself.
};