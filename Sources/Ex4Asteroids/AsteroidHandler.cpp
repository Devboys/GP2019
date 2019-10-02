#include "AsteroidHandler.hpp"
#include "iostream"
#include "sre/Renderer.hpp"
#include "GameObjectList.hpp"

AsteroidHandler::AsteroidHandler(int numAsteroids, std::shared_ptr<sre::SpriteAtlas> atlas) 
{
	visible = false;
	numInitAsteroids = numAsteroids;
	//spawn asteroids in random positions on the screen.
	for (int i = 0; i < numInitAsteroids; i++)
	{
		int randX = rand() % sre::Renderer::instance->getWindowSize().x;
		int randY = rand() % sre::Renderer::instance->getWindowSize().y;

		glm::vec2 asteroidPos = glm::vec2(randX, randY);

		//only asteroids in asteroidList are updated/rendered, so add them.
		auto velocity = glm::vec2(-80 + rand() %  161, -80 + rand() % 161);
		auto asteroid = std::shared_ptr<Asteroid>(new Asteroid(asteroidPos, velocity, Asteroid::asteroidType::big, atlas));
		GameObjectList::getInstance().addedObjects.push_back(asteroid);
	}
}