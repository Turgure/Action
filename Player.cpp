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
	collider->setRadius(getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2 * 0.8);
	addComponent(collider);
}

void Player::update(){
	Object::update();
}

bool Player::hit(std::shared_ptr<Object> target){
	auto i_col = getComponentAs<Collider>("Collider");
	auto t_col = target->getComponentAs<Collider>("Collider");

	if(pow(i_col->getCenter().getX() - t_col->getCenter().getX(), 2) + pow(i_col->getCenter().getY() - t_col->getCenter().getY(), 2)
		<= pow(i_col->getRadius() + t_col->getRadius(), 2)){
		printfDx("hit");
		return true;
	}
	return false;
}
