#include "DxLib.h"
#include "Scenes.h"
#include "Graphic.h"
#include "Transform.h"
#include "Controller.h"
using namespace std;

void SceneA::start(){
	//createPlayer();
	createObjects();
}
void SceneA::update(){
	for(auto& obj : objects){
		obj->update();
	}

	player.update();
	map.update(player);
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

void SceneA::createObjects(){
	for(int i = 0; i < 10; ++i){
		auto obj = make_shared<Object>();
		auto transform = make_shared<Transform>();
		auto sprite = Sprite::create();
		
		transform->set(i*20, i*5);
		if(i < 5){
			sprite->set(GraphicManager::getInstance().getGraphic("data/image/youmu.jpg"), 2);
		} else {
			sprite->set(GraphicManager::getInstance().getGraphic("data/image/eirin.jpg"), 1);
		}

		obj->addComponent(transform);
		obj->addComponent(sprite);

		objects.push_back(obj);
	}
}


//TODO: ƒV[ƒ“‘JˆÚ
void SceneB::start(){}
void SceneB::update(){}
void SceneB::terminate(){}
