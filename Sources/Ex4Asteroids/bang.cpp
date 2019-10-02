#include "bang.hpp"
#include "sre/SpriteAtlas.hpp"
#include "sre/Sprite.hpp"
#include "iostream"
Bang::Bang(glm::vec2 pos, sre::Sprite spr) : GameObject(spr) {
	position = pos;
	deathTimer = 0;
}

void Bang::update(float deltaTime) {
	deathTimer += deltaTime;
	if (deathTimer >= duration) {
		destroyed = true;
	}
}