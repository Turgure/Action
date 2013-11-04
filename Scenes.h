#pragma once
#include <vector>
#include "BaseScene.h"
#include "Player.h"
#include "Map.h"

class SceneA : public BaseScene{
private:
	void start() override;
	void update() override;
	void terminate() override;

	void createPlayer();
	void createObject(int x, int y);

	std::vector<std::shared_ptr<Object>> objects;
	Player player;
	Map map;
};

class SceneB : public BaseScene{
private:
	void start() override;
	void update() override;
	void terminate() override;
};
