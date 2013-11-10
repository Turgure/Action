#include "DxLib.h"
#include "Scenes.h"
#include "Graphic.h"
#include "Transform.h"
#include "Controller.h"
#include "Collider.h"
using namespace std;

void SceneA::start(){
	//createPlayer();
	createObject(100, DEFAULT_SCREEN_SIZE_Y-32);
}
void SceneA::update(){
	for(auto& obj : objects){
		obj->update();
	}

	player.update();
	map.update(player);

	player.hit(objects[0]);
}

void SceneA::terminate(){
}

void SceneA::createPlayer(){
	auto transform = make_shared<Transform>();
	auto sprite = Sprite::create();
	auto input = make_shared<Controller>();
	transform->set(0, 100);
	sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 3);
	player.addComponent(transform);
	player.addComponent(sprite);
	player.addComponent(input);
}

void SceneA::createObject(int x, int y){
	auto obj = make_shared<Object>();

	auto transform = make_shared<Transform>();
	transform->set(x, y);
	obj->addComponent(transform);
	
	auto sprite = Sprite::create();
	sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 2);
	obj->addComponent(sprite);

	auto collider = make_shared<Collider>();
	collider->set(obj->getComponentAs<Collider>("Collider")->CIRCLE, 16);
	obj->addComponent(collider);

	objects.push_back(obj);
}


//TODO: ƒV[ƒ“‘JˆÚ
void SceneB::start(){}
void SceneB::update(){}
void SceneB::terminate(){}
