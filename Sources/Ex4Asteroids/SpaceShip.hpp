#pragma once

#include "GameObject.hpp"
#include "Collidable.hpp"
#include "Laser.hpp"
#include "sre/SpriteAtlas.hpp"

class SpaceShip : public GameObject, public Collidable  {
public:
    SpaceShip(const sre::Sprite &sprite, std::shared_ptr<sre::SpriteAtlas> atlas);

    void update(float deltaTime) override;

    void onCollision(std::shared_ptr<GameObject> other) override;

    void onKey(SDL_Event &keyEvent) override;

	void render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);

    glm::vec2 velocity;
private:
    bool rotateCW = false;
    bool rotateCCW = false;
    bool thrust = false;
	bool fired = false;
    float drag = 0.80f;
    float maxSpeed = 460.0f;
    float thrustPower = 600.0f;
    float rotationSpeed = 100.0f;
    glm::vec2 winSize;

	std::vector<std::shared_ptr<Laser>> laserList;
	std::shared_ptr<sre::SpriteAtlas> spriteAtlas;
};


