#pragma once

#include <vector>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "AsteroidHandler.hpp"

class GameObject;

class AsteroidsGame {
public:
    AsteroidsGame();
private:
    void update(float deltaTime);
    void render();
    void keyEvent(SDL_Event &event);
	void initGame();

    sre::Camera camera;
    sre::SDLRenderer r;
    std::shared_ptr<sre::SpriteAtlas> atlas;
    bool debugCollisionCircles = false;
    int score = 0;

	void checkCollisions();

};


