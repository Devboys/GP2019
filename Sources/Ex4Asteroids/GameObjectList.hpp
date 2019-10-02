#include <vector>

#include"GameObject.hpp"

class GameObjectList {

public:
	static GameObjectList& getInstance();
	static std::vector<std::shared_ptr<GameObject>> gameObjects;

private:
	GameObjectList(); //constructor
	~GameObjectList(); //destructor
	GameObjectList(const GameObjectList& s); //copy-constructor
};