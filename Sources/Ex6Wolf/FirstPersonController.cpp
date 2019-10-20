//
// Created by Morten Nobel-Jørgensen on 29/09/2017.
//

#include "FirstPersonController.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "iostream"

using namespace sre;
using namespace glm;


FirstPersonController::FirstPersonController(sre::Camera * camera)
:camera(camera)
{
    camera->setPerspectiveProjection(45,0.1f,1000);
    position = vec3(0,0,0);
}


void FirstPersonController::update(float deltaTime){
	//Default look-direction to straight down the z-axis, rotate depending on rotation-variable
	glm::vec3 lookVector = vec3(0, 0, -1);
	lookVector = glm::rotateY<float>(lookVector, glm::radians(std::fmod(rotation, 361)));
	
	vec3 moveVector = vec3(0, 0, 0);
	//up and down defines movement along the look-vector.
	if (mState.UP) moveVector += lookVector * moveSpeed * deltaTime;
	if (mState.DOWN) moveVector -= lookVector * moveSpeed * deltaTime;
	//left and right defines movement along the perpendicular of the look-vector(in 2D)
	vec3 perpVector = vec3(lookVector.z, 0, -lookVector.x);
	if (mState.RIGHT) moveVector -= perpVector * moveSpeed * deltaTime;
	if (mState.LEFT) moveVector += perpVector * moveSpeed * deltaTime;
	position += moveVector;

	//lookVector is a vector relative to current camera position. lookAt expects a point in world-space
	lookVector += position;

    camera->lookAt(position, lookVector, vec3{0,1,0});
}

void FirstPersonController::onKey(SDL_Event &event) {

	if (event.key.keysym.sym == SDLK_w) {
		mState.UP = event.type == SDL_KEYDOWN;
	}
	if (event.key.keysym.sym == SDLK_s) {
		mState.DOWN = event.type == SDL_KEYDOWN;
	}
	if (event.key.keysym.sym == SDLK_a) {
		mState.LEFT = event.type == SDL_KEYDOWN;
	}
	if (event.key.keysym.sym == SDLK_d) {
		mState.RIGHT = event.type == SDL_KEYDOWN;
	}
}

void FirstPersonController::onMouse(SDL_Event &event) {
	if (event.motion.type == SDL_MOUSEMOTION) {
		rotation -= event.motion.xrel * lookSensitivity;
	}
}

void FirstPersonController::setInitialPosition(glm::vec2 position, float rotation) {
    this->position = glm::vec3(position.x,0,position.y);
    this->rotation = rotation;
}
