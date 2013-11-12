#pragma once
#include <string>
#include <memory>
#include "Object.h"
#include "Graphic.h"
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

	static std::shared_ptr<Collider> rc;
	static std::shared_ptr<Collider> tc;
	void initialize(Object* root, Object* target){
		rc = root->getComponentAs<Collider>("Collider");
		tc = target->getComponentAs<Collider>("Collider");
	}

	struct MyRectangule{
		MyRectangule(Object* rect){
			points.push_back( tc->center + Vector2(-rect->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, -rect->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2) );
			points.push_back( tc->center + Vector2(rect->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, -rect->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2) );
			points.push_back( tc->center + Vector2(-rect->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, rect->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2) );
			points.push_back( tc->center + Vector2(rect->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, rect->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2) );
		}

		//p1 p2
		//p3 p4
		std::vector<Vector2> points;
	};

	//‰~‚Æ‹éŒ`‚Ì‚ ‚½‚è”»’è
	bool isIncludingVertexInCircle(Object* circle, Object* rect);
	bool isIncludingCircleInRecangle(Object* circle, Object* rect);
	bool isLineOnCircle(Object* circle, Object* rect);
};
