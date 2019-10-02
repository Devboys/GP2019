#include "AsteroidHandler.hpp"
#include "iostream"
#include "sre/Renderer.hpp"

AsteroidHandler::AsteroidHandler(int numAsteroids, std::shared_ptr<sre::SpriteAtlas> atlas)
{
	numInitAsteroids = numAsteroids;
	sre::Sprite asteroidSprite = atlas->get("meteorBrown_big4.png");

	//spawn asteroids in random positions on the screen.
	for (int i = 0; i < numInitAsteroids; i++)
	{
		int randX = rand() % sre::Renderer::instance->getWindowSize().x;
		int randY = rand() % sre::Renderer::instance->getWindowSize().y;

		glm::vec2 asteroidPos = glm::vec2(randX, randY);

		//only asteroids in asteroidList are updated/rendered, so add them.
		auto asteroid = std::shared_ptr<Asteroid>(new Asteroid(asteroidPos, asteroidSprite));
		asteroidList.push_back(asteroid);
	}
}

void AsteroidHandler::update(float deltaTime) {
	for (std::shared_ptr<Asteroid> n : asteroidList) {
		n->update(deltaTime);
	}
}

void AsteroidHandler::render(sre::SpriteBatch::SpriteBatchBuilder& batchBuilder) {
	for (std::shared_ptr<Asteroid> n : asteroidList) {
		n->render(batchBuilder);
	}
}

int AsteroidHandler::numAsteroids() {
	return asteroidList.size();
}