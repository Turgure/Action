#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "DxLib.h"
#include "Component.h"

typedef int DxGraphicHandle;

/*
 * Unique(唯一)の画像を管理するクラス
 */
class GraphicManager;
class Graphic{
public:
	Graphic(DxGraphicHandle handle, int width, int height):handle(handle), width(width), height(height){}
	Graphic():handle(0), width(0), height(0){}
	virtual ~Graphic();
	DxGraphicHandle getHandle(){ return handle; }
	int getWidth(){ return width; }
	int getHeight(){ return height; }
protected:
	DxGraphicHandle handle;
	int width;
	int height;
};

/*
 * Graphic管理クラス
 * Graphic一覧を配列で管理
 */
class GraphicManager{
public:
	static GraphicManager& getInstance(){
		static GraphicManager instance;
		return instance;
	}
	std::shared_ptr<Graphic> getGraphic(const std::string& name){ return graphics[name]; }
private:
	GraphicManager();
	void push(const std::string& path, int width, int height){
		graphics[path] = std::make_shared<Graphic>(LoadGraph(path.c_str()), width, height);
	}
	std::unordered_map<std::string, std::shared_ptr<Graphic>> graphics;
};

/*
 * 画像管理クラス
 * 複数の同一画像も扱う
 * 更新、描写を行う
 */
class Sprite;
class SpriteManager {
public:
	static SpriteManager& getInstance(){
		static SpriteManager instance;
		return instance;
	}
	void addSprite(std::shared_ptr<Sprite>& sprite){
		sprites.push_back(sprite);
	}
	void update();
	void draw();
private:
	SpriteManager(){}
	~SpriteManager(){}
	std::vector<std::weak_ptr<Sprite>> sprites;
};

/*
 * グラフィッククラスのコンポーネント
 * ゲームオブジェクトが所有する
 */
class Sprite : public Component{
public:
	virtual const std::string& getKeyString() const override {
		static std::string key = "Sprite";
		return key;
	}
	void set(std::shared_ptr<Graphic> graph, int zIndex = -1){
		this->graph = graph;
		this->zIndex = zIndex;
	}

	static std::shared_ptr<Sprite> create(){
		auto sprite = std::make_shared<Sprite>();
		SpriteManager::getInstance().addSprite(sprite);
		return sprite;
	}
	/*
	void setZIndex(int zIndex){ this->zIndex = zIndex; }
	void setGraph(std::shared_ptr<Graphic> graph){ this->graph = graph; }
	*/
	std::shared_ptr<Graphic> getGraph(){ return graph; }
	int getZIndex() const{ return zIndex; }
private:
	std::shared_ptr<Graphic> graph;
	int zIndex;	//値が大きいほど手前に表示される
};
