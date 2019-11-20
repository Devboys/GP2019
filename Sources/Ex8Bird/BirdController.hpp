#pragma once

#include "Component.hpp"

class BirdController : public Component {
public:
    explicit BirdController(GameObject *gameObject);

    bool onKey(SDL_Event &event) override;

    void onCollisionStart(PhysicsComponent *comp) override;

    void onCollisionEnd(PhysicsComponent *comp) override;

private:
	//cached components
	std::shared_ptr<PhysicsComponent> _physComp;

	//movement vectors
	float flapStrength = 0.2f; //speed added when player 'flaps' their wings.
	float moveSpeed = 1; //constant sideways movement
};
