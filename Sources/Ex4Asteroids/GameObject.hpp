#pragma once

#include <SDL_events.h>
#include <string>
#include "sre/Sprite.hpp"
#include "sre/SpriteBatch.hpp"

class GameObject {
public:
	GameObject();
    explicit GameObject(sre::Sprite sprite);
    virtual ~GameObject();
    virtual void render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
    virtual void update(float deltaTime);
    virtual void onKey(SDL_Event& keyEvent);

	void wrapObject(glm::vec2& position, glm::vec2 bounds);
	bool isDestroyed();

protected:
    glm::vec2 position;
    glm::vec2 scale;
    sre::Sprite sprite;
    float rotation;
	bool visible;
	bool destroyed;

    friend class AsteroidsGame;
};
