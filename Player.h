#pragma once
#include "Object.h"

class Player : public Object{
public:
	Player();
	void update();

private:
	double radius;
};
