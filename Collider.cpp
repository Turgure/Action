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



bool Collider::hitCvC(Object* root, Object* target){
	auto tc = target->getComponentAs<Collider>("Collider");

	//(Ax-Bx)^2 + (Ay-By)^2 <= (Rx+Ry)^2
	return pow(getCenter().getX() - tc->getCenter().getX(), 2) + pow(getCenter().getY() - tc->getCenter().getY(), 2) <= pow(getRadius() + tc->getRadius(), 2);
}

bool Collider::hitCvL(Object* root, Object* target){//TODO:
	auto tc = target->getComponentAs<Collider>("Collider");

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

bool Collider::hitLvL(Object* root, Object* target){//TODO:
	auto tc = target->getComponentAs<Collider>("Collider");

	return true;
}

bool Collider::hitLvS(Object* root, Object* target){//TODO:
	auto tc = target->getComponentAs<Collider>("Collider");

	return true;
}

bool Collider::hitSvS(Object* root, Object* target){
	MyRectangule r_rect(root);
	MyRectangule t_rect(root);

	//(a.left < b.right) && (a.right > b.left) && (a.top < b.bottom) && (a.bottom > b.top))
	return (r_rect.points[0].getX() < t_rect.points[3].getX())
		&& (r_rect.points[0].getY() < t_rect.points[3].getY())
		&& (r_rect.points[3].getX() > t_rect.points[0].getX())
		&& (r_rect.points[3].getY() > t_rect.points[0].getY());
}


bool Collider::isIncludingVertexInCircle(Object* circle, Object* rect){
	MyRectangule myrect(rect);

	Vector2 diff;
	for(auto& point : myrect.points){
		diff = getCenter() - point;
		if(diff * diff < getRadius() * getRadius()){
			return true;
		}
	}

	return false;
}

bool Collider::isIncludingCircleInRecangle(Object* circle, Object* rect){
	MyRectangule myrect(rect);

	//ü•ª‚Æ‰~‚Ì’†S‚ÌŠp“x‚ª0~PI/2, ‚ª‘Î‚Ìü•ª‚É‚¢‚¦‚é‚È‚ç‹éŒ`“à‚É‰~‚ª‘¶Ý
	return
		0 <= myrect.points[1].angle(myrect.points[0], getCenter()) && myrect.points[1].angle(myrect.points[0], getCenter()) <= PI / 2 &&
		0 <= myrect.points[2].angle(myrect.points[3], getCenter()) && myrect.points[2].angle(myrect.points[3], getCenter()) <= PI / 2;
}

bool Collider::isLineOnCircle(Object* circle, Object* rect){
	MyRectangule myrect(rect);

	//ü•ªpq, ‰~‚Ì’†S‚ðm, m‚©‚çpq‚Ö‚Ì–@ü‚ðh‚Æ‚·‚é
	//v(ph) = k * v(pq);
	Vector2 pq, pm, ph, mh;
	double k, distance2;

	const int n[][4] = {{0, 1, 3, 2}, {1, 3, 2, 0}};
	for(int i = 0; i < 4; ++i){
		pq = myrect.points[n[1][i]] - myrect.points[n[0][i]];
		pm = getCenter() - myrect.points[n[0][i]];

		k = (pq * pm) / (pq * pq);
		//k > 1 || k < 0 ‚Ì‚Æ‚«‚ÍA‰~‚©‚ç‚Ì‚ü‚ªü•ªã‚É‚È‚¢
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
