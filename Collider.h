#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "Vector2.h"

class Collider : public Component {
public:
	virtual const std::string& getKeyString() const override {
		static std::string key = "Collider";
		return key;
	}

	enum Type{
		CIRCLE,
		LINE,
		SQUARE,
		TYPE_NUM
	} type;

	void update() override;
	void set(Type type, double radius = 0){ this->type = type; this->radius = radius; }
	double getRadius(){ return radius; }
	Vector2 getCenter(){ return center; }
	bool hit(Object* root, Object* target);

private:
	double radius;
	Vector2 center;
	Vector2 left_top;
	Vector2 right_down;

	bool hitCvC(Object* root, Object* target);
	bool hitCvL(Object* root, Object* target);
	bool hitCvS(Object* root, Object* target);
	bool hitLvL(Object* root, Object* target);
	bool hitLvS(Object* root, Object* target);
	bool hitSvS(Object* root, Object* target);
};
