#include "DxLib.h"
#include "Scenes.h"
#include "Graphic.h"
#include "Transform.h"
#include "Controller.h"
#include "Collider.h"
using namespace std;

void SceneA::start(){
	//createPlayer();
	createObject(100, DEFAULT_SCREEN_SIZE_Y-64);
}
void SceneA::update(){
	for(auto& obj : objects){
		obj->update();
	}

	player.update();
	map.update(player);

	player.hit(objects[0]);

	auto center = objects[0]->getComponentAs<Collider>("Collider")->getCenter();

	//map.hit(player.getComponentAs<Collider>("Collider")->getObject());

	printfDx("px: %f, py: %f\n", player.getComponentAs<Transform>("Transform")->getX(), player.getComponentAs<Transform>("Transform")->getY());
}

void SceneA::terminate(){
}

void SceneA::createPlayer(){
	auto transform = make_shared<Transform>();
	player.addComponent(transform);
	transform->set(0, 100);

	auto sprite = Sprite::create();
	player.addComponent(sprite);
	sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 3);

	auto controller = make_shared<Controller>();
	player.addComponent(controller);
}

void SceneA::createObject(int x, int y){
	auto obj = make_shared<Object>();

	auto transform = make_shared<Transform>();
	obj->addComponent(transform);
	transform->set(x, y);
	
	auto sprite = Sprite::create();
	obj->addComponent(sprite);
	sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 2);

	auto collider = make_shared<Collider>();
	obj->addComponent(collider);
	collider->set(obj->getComponentAs<Collider>("Collider")->SQUARE, 1, 1);

	objects.push_back(obj);
}


//TODO: �V�[���J��
void SceneB::start(){}
void SceneB::update(){}
void SceneB::terminate(){}
