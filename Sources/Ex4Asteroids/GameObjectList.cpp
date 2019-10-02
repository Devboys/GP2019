#include "GameObjectList.hpp"


GameObjectList::GameObjectList() {} //constructor
GameObjectList::~GameObjectList() {}//destructor
GameObjectList::GameObjectList(const GameObjectList& s) {} //copy-constructor

GameObjectList& GameObjectList::getInstance() {
	static GameObjectList instance;
	return instance;
}