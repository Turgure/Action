#include "Player.h"
#include "Transform.h"
#include "Graphic.h"
#include "Controller.h"
#include "Collider.h"
using namespace std;

Player::Player(){
	auto transform = make_shared<Transform>();
	addComponent(transform);
	transform->set(96, 96);

	auto sprite = Sprite::create();
	addComponent(sprite);
	sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 3);

	auto controller = make_shared<Controller>();
	addComponent(controller);
	
	auto collider = make_shared<Collider>();
	addComponent(collider);
	collider->set(collider->SQUARE, 0.3, 1);
}

void Player::update(){
	Object::update();
}

bool Player::hit(shared_ptr<Object> target){

	if(getComponentAs<Transform>("Transform")->getY() > DEFAULT_SCREEN_SIZE_Y - 64){
		int x = 1;
	}

	if(getComponentAs<Collider>("Collider")->hit(getComponent("Collider")->getObject(), target.get())){
		printfDx("hit : to enemy\n");
		return true;
	}

	return false;
}
