#pragma once
#include <string>
#include "Component.h"
#include "Vector2.h"

class Collider : public Component {
public:
	virtual const std::string& getKeyString() const override {
		static std::string key = "Collider";
		return key;
	}

	void update() override;
	void setRadius(double radius){ this->radius = radius; }
	double getRadius(){ return radius; }
	Vector2 getCenter(){ return center; }

private:
	double radius;
	Vector2 center;
};
