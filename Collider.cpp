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
	int t_type = root->getComponentAs<Collider>("Collider")->type;

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


shared_ptr<Collider> Collider::rc;
shared_ptr<Collider> Collider::tc;

bool Collider::hitCvC(Object* root, Object* target){
	initialize(root, target);

	//(Ax-Bx)^2 + (Ay-By)^2 <= (Rx+Ry)^2
	return pow(rc->getCenter().getX() - tc->getCenter().getX(), 2) + pow(rc->getCenter().getY() - tc->getCenter().getY(), 2) <= pow(rc->getRadius() + tc->getRadius(), 2);
}

bool Collider::hitCvL(Object* root, Object* target){//TODO:
	initialize(root, target);

	return true;
}

bool Collider::hitCvS(Object* root, Object* target){
	initialize(root, target);

	return
		isIncludingVertexInCircle(root, target) ||
		isIncludingCircleInRecangle(root, target) ||
		isLineOnCircle(root, target);
}

bool Collider::hitLvL(Object* root, Object* target){//TODO:
	initialize(root, target);

	return true;
}

bool Collider::hitLvS(Object* root, Object* target){//TODO:
	initialize(root, target);

	return true;
}

bool Collider::hitSvS(Object* root, Object* target){
	initialize(root, target);
	MyRectangule r_rect(root);
	MyRectangule t_rect(root);

	rc->left_top = rc->center - Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);
	rc->right_down = rc->center + Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);
	tc->left_top = tc->center - Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);
	tc->right_down = tc->center + Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);

	//(a.left < b.right) && (a.right > b.left) && (a.top < b.bottom) && (a.bottom > b.top))
	return (r_rect.points[0].getX() < t_rect.points[3].getX())
		&& (r_rect.points[0].getY() < t_rect.points[3].getY())
		&& (r_rect.points[3].getX() > t_rect.points[0].getX())
		&& (r_rect.points[3].getY() > t_rect.points[0].getY());
}


bool Collider::isIncludingVertexInCircle(Object* circle, Object* rect){
	initialize(circle, rect);
	MyRectangule myrect(rect);

	Vector2 diff;
	for(auto& point : myrect.points){
		diff = rc->getCenter() - point;
		if(diff * diff < rc->getRadius() * rc->getRadius()){
			return true;
		}
	}

	return false;
}

bool Collider::isIncludingCircleInRecangle(Object* circle, Object* rect){
	initialize(circle, rect);
	MyRectangule myrect(rect);

	//ü•ª‚Æ‰~‚Ì’†S‚ÌŠp“x‚ª0~PI/2‚ª‘Î‚Ìü•ª‚É‚¢‚¦‚é‚È‚ç‹éŒ`“à‚É‰~‚ª‘¶İ
	return
		0 <= myrect.points[1].angle(myrect.points[0], rc->getCenter()) && myrect.points[1].angle(myrect.points[0], rc->getCenter()) <= PI / 2 &&
		0 <= myrect.points[2].angle(myrect.points[3], rc->getCenter()) && myrect.points[2].angle(myrect.points[3], rc->getCenter()) <= PI / 2;
}

bool Collider::isLineOnCircle(Object* circle, Object* rect){
	initialize(circle, rect);
	MyRectangule myrect(rect);
	//ü•ªpq, ‰~‚Ì’†S‚ğm, m‚©‚çpq‚Ö‚Ì–@ü‚ğh‚Æ‚·‚é
	//v(ph) = k * v(pq);
	Vector2 pq, pm, ph, mh;
	double k, distance2;
	const int n[][4] = {{1, 4, 3, 0}, {0, 1, 4, 3}};
	for(int i = 0; i < 4; ++i){
		pq = myrect.points[n[0][i]] - myrect.points[n[1][i]];
		pm = rc->getCenter() - myrect.points[n[0][i]];

		k = (pq * pm) / (pq * pq);
		//k > 1 || k < 0 ‚Ì‚Æ‚«‚ÍA‰~‚©‚ç‚Ì‚ü‚ªü•ªã‚É‚È‚¢
		if(k > 1 || k < 0) continue;

		ph = pq * k;
		mh = ph - pm;

		distance2 = mh * mh;
		if(distance2 < rc->getRadius() * rc->getRadius()){
			return true;
		}
	}

	return false;
}
