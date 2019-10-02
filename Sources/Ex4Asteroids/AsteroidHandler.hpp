#pragma once
#include "GameObject.hpp"
#include "Asteroid.hpp"
#include "sre/SpriteAtlas.hpp"

class AsteroidHandler : public GameObject {
public:
	AsteroidHandler(int numAsteroids, std::shared_ptr<sre::SpriteAtlas> atlas);

	void update(float deltaTime);
	void render(sre::SpriteBatch::SpriteBatchBuilder& batchBuilder);
	int numAsteroids();

private:
	int numInitAsteroids;
	std::vector<std::shared_ptr<Asteroid>> asteroidList;
};