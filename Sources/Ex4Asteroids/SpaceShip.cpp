//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "SpaceShip.hpp"
#include "sre/Renderer.hpp"

SpaceShip::SpaceShip(const sre::Sprite &sprite, std::shared_ptr<sre::SpriteAtlas> atlas) : GameObject(sprite) {
    scale = glm::vec2(0.5f,0.5f);
    winSize = sre::Renderer::instance->getWindowSize();
    radius = 23;
    position = winSize * 0.5f;
    velocity = glm::vec2(0.0f,0.0f);
	spriteAtlas = atlas;
}

void SpaceShip::update(float deltaTime) {
    if (thrust){
        float acceleration = deltaTime*thrustPower;
        glm::vec2 direction = glm::rotateZ(glm::vec3(0,acceleration,0), glm::radians(rotation));
        velocity += direction;
        float speed = glm::length(velocity);
        if (speed > maxSpeed){
            velocity = velocity * (maxSpeed / speed);
        }
    } else {
        velocity = velocity * (1.0f - drag*deltaTime);
    }

    position += velocity * deltaTime;
    if (rotateCCW){
        rotation += deltaTime * rotationSpeed;
    }
    if (rotateCW){
        rotation -= deltaTime * rotationSpeed;
    }

	wrapObject(position, winSize);

	//spawn lasers in the same direction as ship.
	if (fired) {
		fired = false;
		
		sre::Sprite laserSprite = spriteAtlas->get("laserBlue01.png");
		glm::vec2 shipDirection = glm::rotateZ(glm::vec3(0, 1, 0), glm::radians(rotation));
		children.push_back(std::shared_ptr<Laser>(new Laser(shipDirection, position, laserSprite)));
	}

	GameObject::update(deltaTime);

}

void SpaceShip::render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
	GameObject::render(spriteBatchBuilder);

	for (int i = 0; i < children.size(); i++) {
		children[i]->render(spriteBatchBuilder);
	}
}

void SpaceShip::onCollision(std::shared_ptr<GameObject> other) {

}

void SpaceShip::onKey(SDL_Event &keyEvent) {
    if (keyEvent.key.keysym.sym == SDLK_UP){
        thrust = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_LEFT){
        rotateCCW = keyEvent.type == SDL_KEYDOWN;
    }
    if (keyEvent.key.keysym.sym == SDLK_RIGHT){
        rotateCW = keyEvent.type == SDL_KEYDOWN;
    }
	if (keyEvent.key.keysym.sym == SDLK_SPACE) {
		fired = keyEvent.type == SDL_KEYDOWN;
	}
}
