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
	void set(Type type, double radius = 0){ this->type = type; this->radius = radius; }
	double getRadius(){ return radius; }
	Vector2 getCenter(){ return center; }
	bool hit(Object* root, Object* target);

private:
	double radius;
	Vector2 center;

	bool hitCvC(Object* root, Object* target);
	bool hitCvL(Object* root, Object* target);
	bool hitCvS(Object* root, Object* target);
	bool hitLvL(Object* root, Object* target);
	bool hitLvS(Object* root, Object* target);
	bool hitSvS(Object* root, Object* target);

	struct MyRectangule{
		MyRectangule(Object* rect){
			auto pos = rect->getComponentAs<Transform>("Transform");
			auto graph = rect->getComponentAs<Sprite>("Sprite")->getGraph();

			points.push_back( pos->get() + Vector2(-graph->getWidth() / 2, -graph->getHeight() / 2) );
			points.push_back( pos->get() + Vector2(graph->getWidth() / 2, -graph->getHeight() / 2) );
			points.push_back( pos->get() + Vector2(-graph->getWidth() / 2, graph->getHeight() / 2) );
			points.push_back( pos->get() + Vector2(graph->getWidth() / 2, graph->getHeight() / 2) );
		}

		//p0 p1
		//p2 p3
		std::vector<Vector2> points;
	};

	//‰~‚Æ‹éŒ`‚Ì‚ ‚½‚è”»’è
	bool isIncludingVertexInCircle(Object* circle, Object* rect);
	bool isIncludingCircleInRecangle(Object* circle, Object* rect);
	bool isLineOnCircle(Object* circle, Object* rect);
};
