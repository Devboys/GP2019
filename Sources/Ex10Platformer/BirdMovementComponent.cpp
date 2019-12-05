//
// Created by Morten Nobel-Jørgensen on 11/6/17.
//

#include <iostream>
#include "BirdMovementComponent.hpp"
#include "GameObject.hpp"

BirdMovementComponent::BirdMovementComponent(GameObject *gameObject) : Component(gameObject) {}

void BirdMovementComponent::update(float deltaTime) {
    time += deltaTime;
    gameObject->setPosition(computePositionAtTime(time));
}

glm::vec2 BirdMovementComponent::computePositionAtTime(float time) {
    int segment = (int)fmod(time, getNumberOfSegments());
    float t = fmod(time,1.0f);
	
	//Use quadratic bezier curve to move bird in smooth pattern
	int pointIndex = 2 * segment; //intermediate points are re-used so only 2n
	return QuadBezCurve(positions[pointIndex], positions[pointIndex+1],  positions[pointIndex+2], t);

}

glm::vec2 BirdMovementComponent::QuadBezCurve(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, float time) {
	float b0 = pow((1 - time), 2);
	float b1 = 2 * (1 - time) * time;
	float b2 = pow(time, 2);

	return b0 * p0 + b1 * p1 + b2 * p2;
}

const std::vector<glm::vec2> &BirdMovementComponent::getPositions() {
    return positions;
}

void BirdMovementComponent::setPositions(std::vector<glm::vec2> positions) {
    this->positions = std::move(positions);
}

int BirdMovementComponent::getNumberOfSegments() {
    //num points(p) in (n)-sized bezier curves sequence is p=2n+1, therefore n = (p-1)/2 
    return (positions.size()-1) / 2;
}

