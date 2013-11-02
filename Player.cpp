#include "Player.h"
#include "Transform.h"
#include "Graphic.h"
#include "Controller.h"
using namespace std;

Player::Player(){
	auto transform = make_shared<Transform>();
	auto sprite = Sprite::create();
	auto input = make_shared<Controller>();
	transform->set(0, 100);
	sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 3);
	addComponent(transform);
	addComponent(sprite);
	addComponent(input);
}

void Player::update(){
	Object::update();
}
