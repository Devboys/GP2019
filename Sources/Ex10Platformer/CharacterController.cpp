//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "CharacterController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "PlatformerGame.hpp"
#include "SpriteComponent.hpp"
#include "math.h" //for fmod

CharacterController::CharacterController(GameObject *gameObject) : Component(gameObject) {
    characterPhysics = gameObject->addComponent<PhysicsComponent>();

    auto physicsScale = PlatformerGame::instance->physicsScale;
    radius = 10/physicsScale;
    characterPhysics->initCircle(b2_dynamicBody, radius, glm::vec2{1.5,1.5}*Level::tileSize/physicsScale,1);
    characterPhysics->getFixture()->SetRestitution(0);
    characterPhysics->fixRotation();
    spriteComponent = gameObject->getComponent<SpriteComponent>();

	totalTime = 0.0f;
}

bool CharacterController::onKey(SDL_Event &event) {
        switch (event.key.keysym.sym){
            case SDLK_SPACE:
            {
                if (isGrounded && event.type == SDL_KEYDOWN){ // prevents double jump
                    jump();
                }
            }
            break;
                case SDLK_LEFT:
            {
                left = event.type == SDL_KEYDOWN;
            }
            break;
                case SDLK_RIGHT:
            {
                right = event.type == SDL_KEYDOWN;
            }
            break;
        }

    return false;
}

void CharacterController::update(float deltaTime) {
    // raycast ignores any shape in the starting point
    auto from = characterPhysics->getBody()->GetWorldCenter();
    b2Vec2 to {from.x,from.y -radius*1.3f};
    isGrounded = false;
    PlatformerGame::instance->world->RayCast(this, from, to);

    characterPhysics->fixRotation();
    glm::vec2 movement{0,0};
    if (left){
        movement.x --;
    }
    if (right){
        movement.x ++;
    }
    float accelerationSpeed = 0.010f;
    characterPhysics->addImpulse(movement*accelerationSpeed);
    auto linearVelocity = characterPhysics->getLinearVelocity();
    float currentVelocity = linearVelocity.x;
    if (abs(currentVelocity) > maxVelocity){
        linearVelocity.x = glm::sign(linearVelocity.x)*maxVelocity;
        characterPhysics->setLinearVelocity(linearVelocity);
    }
    updateSprite(deltaTime);
}

void CharacterController::jump() {
    characterPhysics->addImpulse({0,0.15f});
}

void CharacterController::onCollisionStart(PhysicsComponent *comp) {

}

void CharacterController::onCollisionEnd(PhysicsComponent *comp) {

}

float32 CharacterController::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) {
    isGrounded = true;
    return 0; // terminate raycast
}

void CharacterController::setSprites(sre::Sprite standing, sre::Sprite walk1, sre::Sprite walk2, sre::Sprite flyUp,
                                     sre::Sprite fly, sre::Sprite flyDown) {
    this->standing = standing;
    this->walk1 = walk1;
    this->walk2 = walk2;
    this->flyUp = flyUp;
    this->fly = fly;
    this->flyDown = flyDown;
}

void CharacterController::updateSprite(float deltaTime) {
    auto velocity = characterPhysics->getLinearVelocity();

	float normalizedVelocity = abs(velocity.x) / maxVelocity;
	totalTime += deltaTime * normalizedVelocity; //animation time ticks slower when player is slow.

	if (velocity.x == 0) { //standing character uses standing sprite
		spriteComponent->setSprite(standing);
	}
	else if (isGrounded) { //grounded moving character uses walk sprites
		if (fmod(totalTime, animationTime*2) > animationTime) {
			spriteComponent->setSprite(walk1);
		}
		else {
			spriteComponent->setSprite(walk2);
		}
	}

	//jumping character uses jump sprites
	if (velocity.y > 0) { //going up
		spriteComponent->setSprite(flyUp);
	}
	else if (velocity.y == 0 && !isGrounded) { //flying
		spriteComponent->setSprite(fly);
	}
	else if (velocity.y < 0) { //going down
		spriteComponent->setSprite(flyDown);
	}



	//flip player
	glm::bvec2 flip = glm::bvec2(left, false);

	walk1.setFlip(flip);
	walk2.setFlip(flip);
	flyUp.setFlip(flip);
	fly.setFlip(flip);
	flyDown.setFlip(flip);
	//spriteComponent->getSprite().setFlip(glm::bvec2(true, false)); //this didnt work...

}


