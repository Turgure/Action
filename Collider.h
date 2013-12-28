#pragma once
#include <string>
#include <memory>
#include "Object.h"
#include "Graphic.h"
#include "Transform.h"
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
	void set(Type type);
	void set(Type type, double radius);
	void set(Type type, double lrRate, double udRate);	///O <= rate <= 1;
	double getRadius(){ return radius; }
	Vector2 getCenter(){ return center; }
	double getLrRate(){ return lrRate; }
	double getUdRate(){ return udRate; }
	bool hit(Object* root, Object* target);

private:
	double radius;
	Vector2 center;
	double lrRate, udRate;

	std::vector<Vector2> getHitPos(Object* obj);

	bool hitCvC(Object* root, Object* target);
	bool hitCvL(Object* root, Object* target);
	bool hitCvS(Object* root, Object* target);
	bool hitLvL(Object* root, Object* target);
	bool hitLvS(Object* root, Object* target);
	bool hitSvS(Object* root, Object* target);

	//‰~‚Æ‹éŒ`‚Ì‚ ‚½‚è”»’è
	bool isIncludingVertexInCircle(Object* circle, Object* rect);
	bool isIncludingCircleInRecangle(Object* circle, Object* rect);
	bool isLineOnCircle(Object* circle, Object* rect);
};
