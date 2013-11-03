#pragma once
#include <memory>
#include <vector>

class Object;
class Player;

class Map{
public:
	Map();
	void loadMap(int id);
	void update(Player& player);
	void updateMap();
	void updatePlayer(Player& player);
private:
	static int current;
	static int mapdata[2][15][20];

	std::vector<std::shared_ptr<Object>> cells;
};
