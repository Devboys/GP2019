
//I realize now that i could've just passed pointers around inside GameObject instead of making a singleton...

#pragma once
#include <vector>
#include"GameObject.hpp"

class GameObjectList {

public:
	static GameObjectList& getInstance() {
		static GameObjectList instance;
		return instance;
	}
	
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<GameObject>> addedObjects;

	GameObjectList(GameObjectList const&) = delete;
	void operator=(GameObjectList const&) = delete;

private:
	GameObjectList(){} //constructor
};