//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
	//This controller only interacts with physics-component so cache this pointer for future reference.
	_physComp = this->getGameObject()->getComponent<PhysicsComponent>();

	//define starting parameters for physics simulation
	_physComp->setLinearVelocity(glm::vec2(moveSpeed, 0));
}

bool BirdController::onKey(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && BirdGame::instance->getGameState() == GameState::Running){
		if (event.key.keysym.sym == SDLK_SPACE) {
			
			_physComp->getLinearVelocity().x;
			_physComp->addImpulse(glm::vec2(0, flapStrength));
		}
    }
    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
	
	std::string name = comp->getGameObject()->name;

	if (name == "Coin") {
		comp->getGameObject()->destroyed = true;
	}
	else if (name == "Wall top" || name == "Wall bottom") {
		BirdGame::instance->setGameState(GameState::GameOver);
	}
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}


