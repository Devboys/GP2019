//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include <ctime>
#include <glm/gtc/constants.hpp>
#include "AsteroidsGame.hpp"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Laser.hpp"
#include "GameObjectList.hpp"


using namespace sre;

AsteroidsGame::AsteroidsGame() {
    r.setWindowTitle("Asteroids");

    r.init()
     .withSdlWindowFlags(SDL_WINDOW_OPENGL);

    time_t t;                                               // random seed based on time
    srand((unsigned) time(&t));

    atlas = SpriteAtlas::create("asteroids.json","asteroids.png");

	initGame();

    camera.setWindowCoordinates();

    r.frameUpdate = [&](float deltaTime){
        update(deltaTime);
    };

    r.keyEvent = [&](SDL_Event& event){
        keyEvent(event);
    };

    r.frameRender = [&](){
        render();
    };

    r.startEventLoop();
}

void AsteroidsGame::initGame() {
	auto spaceshipSprite = atlas->get("playerShip3_blue.png");
	GameObjectList::getInstance().gameObjects.push_back(std::make_shared<SpaceShip>(spaceshipSprite, atlas));

	//AsteroidHandler is responsible for asteroid-objects on screen
	auto asteroidHandler = std::shared_ptr<AsteroidHandler>(new AsteroidHandler(5, atlas));
	GameObjectList::getInstance().gameObjects.push_back(asteroidHandler);
}

void AsteroidsGame::update(float deltaTime) {

	//update all objects
	for (int i = 0; i < GameObjectList::getInstance().gameObjects.size(); i++) {
		GameObjectList::getInstance().gameObjects[i]->update(deltaTime);
    }

	//call collision events for all objects
	checkCollisions();

	//remove destroyed objects
	for (int j = GameObjectList::getInstance().gameObjects.size() - 1; j >= 0; j--) {
		if (GameObjectList::getInstance().gameObjects[j]->isDestroyed()) {
			GameObjectList::getInstance().gameObjects.erase(GameObjectList::getInstance().gameObjects.begin() + j);
		}
	}

	//add new objects
	if (GameObjectList::getInstance().gameObjects.size() != 0) {
		GameObjectList::getInstance().gameObjects.insert (
			GameObjectList::getInstance().gameObjects.end(), 
			GameObjectList::getInstance().addedObjects.begin(), 
			GameObjectList::getInstance().addedObjects.end()
		);

		GameObjectList::getInstance().addedObjects.clear();
	}

}

void drawCircle(std::vector<glm::vec3>& lines, glm::vec2 position, float radius){
    float quaterPi = glm::quarter_pi<float>();
    for (float f = 0;f<glm::two_pi<float>();f += quaterPi){
        // line from
        lines.push_back(glm::vec3{position.x + cosf(f)*radius,
                                  position.y + sinf(f)*radius,
                                  0
        });
        // line to
        lines.push_back(glm::vec3{position.x + cosf(f+quaterPi)*radius,
                                  position.y + sinf(f+quaterPi)*radius,
                                  0
        });
    }
}

void AsteroidsGame::render() {
    auto renderPass = RenderPass::create()
            .withCamera(camera)
            .withClearColor(true, {.20, .60, .86, 1})
            .build();
    auto spriteBatchBuilder = SpriteBatch::create();

    for (int i = 0; i < GameObjectList::getInstance().gameObjects.size();i++) {
		GameObjectList::getInstance().gameObjects[i]->render(spriteBatchBuilder);
    }
    auto spriteBatch = spriteBatchBuilder.build();
    renderPass.draw(spriteBatch);

    if (debugCollisionCircles){
        std::vector<glm::vec3> lines;
        for (auto & go : GameObjectList::getInstance().gameObjects){
            auto col = std::dynamic_pointer_cast<Collidable>(go);
            if (col != nullptr){
                drawCircle(lines, go->position, col->getRadius());
            }
        }
        renderPass.drawLines(lines);
    }

    ImGui::SetNextWindowPos(ImVec2(Renderer::instance->getWindowSize().x/2-100, .0f), ImGuiSetCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, 70), ImGuiSetCond_Always);
    ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::LabelText("GOs", "%i", GameObjectList::getInstance().gameObjects.size());
    ImGui::LabelText("Score", "%i",score);
    ImGui::End();
}

void AsteroidsGame::keyEvent(SDL_Event &event) {
    for (int i = 0; i < GameObjectList::getInstance().gameObjects.size();i++) {
		GameObjectList::getInstance().gameObjects[i]->onKey(event);
    }
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
        debugCollisionCircles = !debugCollisionCircles;
    }
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
		std::cout << "restarting...\n";
		GameObjectList::getInstance().gameObjects.clear();

		initGame();
	}
}

void AsteroidsGame::checkCollisions() {
	for (int i = 0; i < GameObjectList::getInstance().gameObjects.size(); i++) {

		glm::vec2 objectPos = GameObjectList::getInstance().gameObjects[i]->position;
		auto object = std::dynamic_pointer_cast<Collidable>(GameObjectList::getInstance().gameObjects[i]);

		if (object != nullptr) {
			for (int j = 0; j < GameObjectList::getInstance().gameObjects.size(); j++) {
				if (j == i) continue;
				 glm::vec2 otherPos = GameObjectList::getInstance().gameObjects[j]->position;
				auto other = std::dynamic_pointer_cast<Collidable>(GameObjectList::getInstance().gameObjects[j]);
				if (other != nullptr) {
					float dist = glm::length(otherPos - objectPos);
					if (dist < object->getRadius() || dist < other->getRadius()) {
						object->onCollision(GameObjectList::getInstance().gameObjects[j]);
					}
				}

			}
		}
	}
}

int main(){
    new AsteroidsGame();
    return 0;
}