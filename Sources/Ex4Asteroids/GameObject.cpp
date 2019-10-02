//
// Created by Morten Nobel-Jørgensen on 12/09/2017.
//

#include "GameObject.hpp"

GameObject::GameObject()
	: position(0, 0),
	rotation(0),
	scale(1, 1),
	visible(false),
	destroyed(false)
{
}

GameObject::GameObject(sre::Sprite sprite)
	:position(0, 0),
	rotation(0),
	scale(1, 1),
	sprite(sprite),
	visible(true),
	destroyed(false)
{
}

GameObject::~GameObject(){
}

void GameObject::update(float deltaTime) {
}

void GameObject::render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
	if (visible)
	{
		sprite.setPosition(position);
		sprite.setRotation(rotation);
		sprite.setScale(scale);
		spriteBatchBuilder.addSprite(sprite);
	}
}

void GameObject::onKey(SDL_Event &keyEvent) {

}

void GameObject::wrapObject(glm::vec2& position, glm::vec2 bounds)
{
	if (position.x < 0) {
		position.x += bounds.x;
	}
	else if (position.x > bounds.x) {
		position.x -= bounds.x;
	}
	if (position.y < 0) {
		position.y += bounds.y;
	}
	else if (position.y > bounds.y) {
		position.y -= bounds.y;
	}
}

bool GameObject::isDestroyed() {
	return destroyed;
}

