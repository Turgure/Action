#include "Player.h"
#include "Transform.h"
#include "Graphic.h"
#include "Controller.h"
#include "Collider.h"
using namespace std;

Player::Player(){
	auto transform = make_shared<Transform>();
	transform->set(0, 100);
	addComponent(transform);

	auto sprite = Sprite::create();
	sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 3);
	addComponent(sprite);

	auto input = make_shared<Controller>();
	addComponent(input);
	
	auto collider = make_shared<Collider>();
	collider->set(getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2 * 0.8, collider->CIRCLE);
	addComponent(collider);
}

void Player::update(){
	Object::update();
}

bool Player::hit(shared_ptr<Object> target){
	if(getComponentAs<Collider>("Collider")->hit(getComponent("Collider")->getObject(), target.get())){
		printfDx("hit");
		return true;
	}

	return false;
}
