//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include "MovingPlatformComponent.hpp"
#include "PlatformComponent.hpp"
#include "GameObject.hpp"
#include "iostream"

MovingPlatformComponent::MovingPlatformComponent(GameObject *gameObject) : Component(gameObject)
{
    platformComponent = gameObject->getComponent<PlatformComponent>();
}

void MovingPlatformComponent::update(float deltaTime) {
    totalTime += deltaTime;

	//get vector between start and end;
	glm::vec2 moveVec = movementEnd - movementStart;

	//calculate ease between 0-1. This is the platforms 'progress' along its path.
	float progressTime = fmod(totalTime, platformMoveDuration);
	float pathProgress = QuadEaseInOut(progressTime, 0, 1, platformMoveDuration);
	
	//move platform along moveVec depending on progress.
	if (fmod(totalTime, platformMoveDuration * 2) > platformMoveDuration) {
		platformComponent->moveTo(movementStart + moveVec * (1 - pathProgress));
	}
	else {
		platformComponent->moveTo(movementStart + moveVec * pathProgress);
	}
}

//Quadratic in-out easing function.
//Source: http://gizma.com/easing/
float MovingPlatformComponent::QuadEaseInOut(float time, float start, float change, float duration) {
	time /= duration / 2;
	if (time < 1) return change / 2 * time * time + start;
	time--;
	return -change/2 * (time*(time-2) - 1) + start;
}
void MovingPlatformComponent::setMovementStart(glm::vec2 pos) {
    movementStart = pos;
}

void MovingPlatformComponent::setMovementEnd(glm::vec2 pos) {
    movementEnd = pos;
}
