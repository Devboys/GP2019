#include "Laser.hpp"
#include "iostream"
#include "Asteroid.hpp"
#include "SpaceShip.hpp"

Laser::Laser(glm::vec2 dir, glm::vec2 pos, sre::Sprite sprite, float radius) : GameObject(sprite) {
	deathTimer = 0;

	this->direction = glm::normalize(dir);
	position = pos;
	
	glm::vec2 up = glm::vec2(0, 1);
	//calculate rotation angle, assuming both vectors are normalized.
	float angle = glm::degrees(glm::acos(glm::dot(up, direction)));
	
	//above calculation is jank, so results is only in range 0-180. We need full range (0-360) so 
	//correct for this.
	rotation = ((direction.x > 0) ? 360 - angle : angle);

	this->radius = radius;
}

void Laser::update(float deltaTime) {
	
	position += direction * speed * deltaTime;

	deathTimer += deltaTime;
	if (deathTimer >= duration) {
		destroyed = true;
	}
}

void Laser::onCollision(std::shared_ptr<GameObject> other) {
	if (std::dynamic_pointer_cast<SpaceShip>(other) == nullptr) {
		this->destroyed = true;
	}
}