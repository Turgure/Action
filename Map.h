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
	bool hit(Object* obj);
private:
	static int current;
	static int mapdata[2][15][20];

	struct Cell{
		int id;
		bool isMovable;
		std::shared_ptr<Object> obj;
	};

	std::vector<std::vector<Cell>> cells;
};
