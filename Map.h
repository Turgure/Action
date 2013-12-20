#pragma once
#include <memory>
#include <vector>

class Object;
class Player;

class Map{
public:
	Map();
	void update(Player& player);
	void updateMap();
	void updatePlayer(Player& player);
	bool hit(Object* obj);
private:
	static int current;
	static int mapdata[2][15][20];

	void loadBackground(int id);
	void loadMap(int id);
	void clearCells();

	struct Cell{
		int id;
		bool isMovable = true;
		std::shared_ptr<Object> obj;
	};

	std::vector<std::vector<Cell>> cells;
	std::shared_ptr<Object> background;
};
