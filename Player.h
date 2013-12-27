#pragma once
#include "Object.h"
#include "Vector2.h"

class Player : public Object{
public:
	Player();
	void update();
	bool hit(std::shared_ptr<Object> target);

private:
	double radius;
	Vector2 center;
};
