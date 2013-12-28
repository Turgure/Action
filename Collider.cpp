#include "Collider.h"
#include "MyMath.h"
#include "Object.h"
#include "Transform.h"
#include "Graphic.h"
using namespace std;

void Collider::update(){
	auto graph = getObject()->getComponentAs<Sprite>("Sprite")->getGraph();
	center = getObject()->getComponentAs<Transform>("Transform")->get() + Vector2(graph->getWidth() / 2, graph->getHeight() / 2);
}

void Collider::set(Type type){
	this->type = type;
}

void Collider::set(Type type, double radius){
	this->type = type; this->radius = radius;
}

void Collider::set(Type type, double lrRate, double udRate){
	this->type = type;
	this->lrRate = lrRate;
	this->udRate = udRate;
}

bool Collider::hit(Object* root, Object* target){
	int r_type = root->getComponentAs<Collider>("Collider")->type;
	int t_type = target->getComponentAs<Collider>("Collider")->type;

	switch(r_type){
	case CIRCLE:
		switch(t_type){
		case CIRCLE: return hitCvC(root, target);
		case LINE: return hitCvL(root, target);
		case SQUARE: return hitCvS(root, target);
		default: printfDx("Unexpected hit type."); break;
		}
	case LINE:
		switch(t_type){
		case CIRCLE: return hitCvL(root, target);
		case LINE: return hitLvL(root, target);
		case SQUARE: return hitLvS(root, target);
		default: printfDx("Unexpected hit type."); break;
		}
		break;
	case SQUARE:
		switch(t_type){
		case CIRCLE: return hitCvS(root, target);
		case LINE: return hitLvS(root, target);
		case SQUARE: return hitSvS(root, target);
		default: printfDx("Unexpected hit type."); break;
		}
	default:
		printfDx("Unexpected hit type.");
		break;
	}

	return false;
}

vector<Vector2> Collider::getHitPos(Object* obj){
	vector<Vector2> hitPos;
	auto collider = obj->getComponentAs<Collider>("Collider");
	const int width = obj->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth();
	const int height = obj->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight();

	//TODO: リファクタリング
	hitPos.push_back(Vector2(collider->getCenter().getX() - width / 2 * collider->getLrRate(), collider->getCenter().getY() - height / 2 * collider->getUdRate()));
	hitPos.push_back(Vector2(collider->getCenter().getX() + width / 2 * collider->getLrRate(), collider->getCenter().getY() - height / 2 * collider->getUdRate()));
	hitPos.push_back(Vector2(collider->getCenter().getX() - width / 2 * collider->getLrRate(), collider->getCenter().getY() + height / 2 * collider->getUdRate()));
	hitPos.push_back(Vector2(collider->getCenter().getX() + width / 2 * collider->getLrRate(), collider->getCenter().getY() + height / 2 * collider->getUdRate()));

	return hitPos;
}

bool Collider::hitCvC(Object* root, Object* target){
	auto tc = target->getComponentAs<Collider>("Collider");

	//(Ax-Bx)^2 + (Ay-By)^2 <= (Rx+Ry)^2
	return pow(getCenter().getX() - tc->getCenter().getX(), 2) + pow(getCenter().getY() - tc->getCenter().getY(), 2) <= pow(getRadius() + tc->getRadius(), 2);
}

bool Collider::hitCvL(Object* root, Object* target){
	//TODO:
	return true;
}

bool Collider::hitCvS(Object* root, Object* target){
	//return
	//	isIncludingVertexInCircle(root, target) ||
	//	isIncludingCircleInRecangle(root, target) ||
	//	isLineOnCircle(root, target);

	bool flag = false;
	if(isIncludingVertexInCircle(root, target)){
		printfDx("hit : isIncludingVertexInCircle\n");
		flag = true;
	}
	if(isIncludingCircleInRecangle(root, target)){
		printfDx("hit : isIncludingCircleInRecangle\n");
		flag = true;
	}
	if(isLineOnCircle(root, target)){
		printfDx("hit : isLineOnCircle\n");
		flag = true;
	}

	return flag;
}

bool Collider::hitLvL(Object* root, Object* target){
	//TODO:
	return true;
}

bool Collider::hitLvS(Object* root, Object* target){
	//TODO:
	return true;
}

bool Collider::hitSvS(Object* root, Object* target){
	auto r_hitPos = getHitPos(root);
	auto t_hitPos = getHitPos(target);

	//(a.left < b.right) && (a.right > b.left) && (a.top < b.bottom) && (a.bottom > b.top))
	return (r_hitPos[0].getX() < t_hitPos[3].getX())
		&& (r_hitPos[0].getY() < t_hitPos[3].getY())
		&& (r_hitPos[3].getX() > t_hitPos[0].getX())
		&& (r_hitPos[3].getY() > t_hitPos[0].getY());
}


bool Collider::isIncludingVertexInCircle(Object* circle, Object* rect){
	auto hitPos = getHitPos(rect);

	Vector2 diff;
	for(auto& point : hitPos){
		diff = getCenter() - point;
		if(diff * diff < getRadius() * getRadius()){
			return true;
		}
	}

	return false;
}

bool Collider::isIncludingCircleInRecangle(Object* circle, Object* rect){
	auto hitPos = getHitPos(rect);

	//線分と円の中心の角度が0~PI/2, が対の線分にいえるなら矩形内に円が存在
	return
		0 <= hitPos[1].angle(hitPos[0], getCenter()) && hitPos[1].angle(hitPos[0], getCenter()) <= PI / 2 &&
		0 <= hitPos[2].angle(hitPos[3], getCenter()) && hitPos[2].angle(hitPos[3], getCenter()) <= PI / 2;
}

bool Collider::isLineOnCircle(Object* circle, Object* rect){
	auto hitPos = getHitPos(rect);

	//線分pq, 円の中心をm, mからpqへの法線をhとする
	//v(ph) = k * v(pq);
	Vector2 pq, pm, ph, mh;
	double k, distance2;

	const int n[][4] = {{0, 1, 3, 2}, {1, 3, 2, 0}};
	for(int i = 0; i < 4; ++i){
		pq = hitPos[n[1][i]] - hitPos[n[0][i]];
		pm = getCenter() - hitPos[n[0][i]];

		k = (pq * pm) / (pq * pq);
		//k > 1 || k < 0 のときは、円からの垂線が線分上にない
		if(k > 1 || k < 0) continue;

		ph = pq * k;
		mh = ph - pm;

		distance2 = mh * mh;
		if(distance2 < getRadius() * getRadius()){
			return true;
		}
	}

	return false;
}
