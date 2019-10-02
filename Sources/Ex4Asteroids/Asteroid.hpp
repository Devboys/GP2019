#pragma once
#include "GameObject.hpp"
#include "Collidable.hpp"
#include "sre/SpriteAtlas.hpp"

class Asteroid : public GameObject, public Collidable {

public:
	static enum asteroidType { big, medium, small };

	Asteroid(glm::vec2 pos, glm::vec2 velocity, asteroidType type, std::shared_ptr<sre::SpriteAtlas> atlas);
	void update(float deltaTime);
	void onCollision(std::shared_ptr<GameObject> other);

private:
	float rotationSpeed;
	glm::vec2 velocity;

	std::shared_ptr<sre::SpriteAtlas> atlas;
	asteroidType type;
};