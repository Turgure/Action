#include "Map.h"
#include "Transform.h"
#include "Graphic.h"
#include "Collider.h"
#include "Player.h"
#include "Object.h"
using namespace std;

int Map::current = 0;

int Map::mapdata[2][15][20] = {
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}, {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	}
};

Map::Map(){
	clearCells();

	background = make_shared<Object>();
	auto transform = make_shared<Transform>();
	background->addComponent(transform);
	auto sprite = Sprite::create();
	background->addComponent(sprite);

	loadBackground(current);
	loadMap(current);
}

void Map::clearCells(){
	cells.clear();
	cells.resize(15);
	for(auto& row : cells){
		row.resize(20);
	}
}

void Map::loadBackground(int id){
	const auto& sprite = background->getComponentAs<Sprite>("Sprite");
	switch(id){
	case 0:
		sprite->set(GraphicManager::getInstance().getGraphic("data/image/bg1.png"));
		break;
	case 1:
		sprite->set(GraphicManager::getInstance().getGraphic("data/image/bg2.png"));
		break;
	}
}

void Map::loadMap(int id){
	clearCells();

	for(int h = 0; h < 15; ++h){
		for(int w = 0; w < 20; ++w){
			if(mapdata[id][h][w] == 0) continue;	//空白マスはまわさない

			auto obj = make_shared<Object>();

			auto transform = make_shared<Transform>();
			obj->addComponent(transform);
			transform->set(32 * w, 32 * h);

			auto sprite = Sprite::create();
			obj->addComponent(sprite);
			switch(mapdata[id][h][w]){
			case 0:
				//sprite->set(nullptr);
				break;
			case 1:
				sprite->set(GraphicManager::getInstance().getGraphic("data/image/chip3.jpg"));
				cells[h][w].isMovable = false;
				break;
			case 2:
			default:
				cells[h][w].obj = nullptr;
				break;
			}

			auto collider = make_shared<Collider>();
			obj->addComponent(collider);
			collider->set(Collider::SQUARE, 1, 1);

			cells[h][w].id = mapdata[id][h][w];
			cells[h][w].obj = obj;
		}
	}
}

void Map::update(Player& player){
	updatePlayer(player);
	updateMap();
}

void Map::updateMap(){
	for(int h = 0; h < 15; ++h){
		for(int w = 0; w < 20; ++w){
			if(cells[h][w].obj){
				cells[h][w].obj->getComponent("Collider")->update();
			}
		}
	}

	static int prev = current;
	if(prev != current){
		loadBackground(current);
		loadMap(current);
		prev = current;
	}
}

void Map::updatePlayer(Player& player){
	auto position = player.getComponentAs<Transform>("Transform");

	if(position->getX() < 0){
		switch(current){
		case 0:
			position->setX(0);
			break;
		case 1:
			position->setX(640 - 32);
			current = 0;
			break;
		}
	}
	if(position->getX() > 640 - 32){
		switch(current){
		case 0:
			position->setX(0);
			current = 1;
			break;
		case 1:
			position->setX(640 - 32);
			break;
		}
	}
	if(position->getY() < 0){
		position->setY(480 - 32);
	}
	if(position->getY() > 480 - 32){
		position->setY(0);
	}
}

#include "Controller.h"
bool Map::hit(Object* obj){//TODO: Scenes.cppで実装
	const auto collider = obj->getComponentAs<Collider>("Collider");
	static int prev = -1;	//初期化に-1を代入
	static vector<Cell> dismovable_points;

	if(prev != current){
		prev = current;
		dismovable_points.clear();

		for(auto& row : cells){
			for(auto& col : row){
				if(!col.isMovable){
					dismovable_points.push_back(col);
				}
			}
		}
	}

	//for(auto& point : dismovable_points){
	//	printfDx("x:%0f, y:%0f\n", point.obj->getComponentAs<Transform>("Transform")->getX(), point.obj->getComponentAs<Transform>("Transform")->getY());
	//}

	for(auto& point : dismovable_points){//TODO: ベクトル処理 or improvement
		if(collider->hit(obj, point.obj.get())){
			printfDx("マップのマスと衝突\n");
			auto playerPos = obj->getComponentAs<Transform>("Transform");
			auto diff = point.obj->getComponentAs<Transform>("Transform")->get() - *playerPos;
			obj->getComponentAs<Controller>("Controller")->resetYMomentum();

			//horizontal
			if(abs(diff.getY()) < 16){
				if(-16 < diff.getX() && diff.getX() < 32){//hit left
					playerPos->setX(playerPos->getX() - (32 - diff.getX()));
				}
				else if(-32 < diff.getX() && diff.getX() < -16){//hit right
					playerPos->setX(playerPos->getX() + (32 + diff.getX()));
				}
			}

			//vertical
			if(abs(diff.getX()) < 16){
				if(-16 < diff.getY() && diff.getY() < 32){//hit top
					playerPos->setY(playerPos->getY() - (32 - diff.getY()));
				}
				else if(-32 < diff.getY() && diff.getY() < -16){//hit bottom
					playerPos->setY(playerPos->getY() + (32 + diff.getY()));
				}
			}

			return true;
		}
	}

	return false;
}
