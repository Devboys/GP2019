//
// Created by Morten Nobel-Jørgensen on 29/09/2017.
//

#include <SDL_events.h>
#include "sre/Camera.hpp"

class FirstPersonController {
public:
    explicit FirstPersonController(sre::Camera * camera);

    void update(float deltaTime);
    void onKey(SDL_Event& event);
    void onMouse(SDL_Event &event);

    void setInitialPosition(glm::vec2 position, float rotation);

    float rotation = 0;
    glm::vec3 position;
private:
    sre::Camera * camera;

	struct MoveState {
		bool UP;
		bool DOWN;
		bool LEFT;
		bool RIGHT;

		MoveState() {
			UP = DOWN = LEFT = RIGHT = false;
		}
	};

	MoveState mState;
	float moveSpeed = 2;
	float lookSensitivity = 0.1f;
};

