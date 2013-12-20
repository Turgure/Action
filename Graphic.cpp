#include <algorithm>
#include "DxLib.h"
#include "Transform.h"
#include "Graphic.h"
#include "Object.h"
using namespace std;

Graphic::~Graphic(){
	DeleteGraph(handle);
}

GraphicManager::GraphicManager(){
	push("data/image/eirin.jpg", 32, 32);	//TODO: csvで管理。ファイル名、ハッシュの登録
	push("data/image/youmu.jpg", 32, 32);

	push("data/image/bg1.png", 640, 480);
	push("data/image/bg2.png", 640, 480);

	push("data/image/chip1.jpg", 32, 32);
	push("data/image/chip2.jpg", 32, 32);
	push("data/image/chip3.jpg", 32, 32);
}

void SpriteManager::update(){
}

void SpriteManager::draw(){
	typedef std::weak_ptr<Sprite> Spr;
	//無効になったスプライトを削除する。定石
	sprites.erase(std::remove_if(begin(sprites), end(sprites), [](const Spr& spr){ return spr.expired(); }), sprites.end());
	//安定ソート
	std::stable_sort(begin(sprites), end(sprites), [](const Spr& s1, const Spr& s2){ return s1.lock()->getZIndex() < s2.lock()->getZIndex(); });
	for(auto& sprite : sprites){
		auto position = sprite.lock()->getObject()->getComponentAs<Transform>("Transform");
		if(position){
			DrawGraph((int)position->getX(), (int)position->getY(), sprite.lock()->getGraph()->getHandle(), true);
			DrawFormatString((int)position->getX(), (int)position->getY() + 10, GetColor(0, 0, 0), "%d", sprite.lock()->getZIndex());
		}
	}
	DxLib::ScreenFlip();
}
