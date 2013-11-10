#include "Collider.h"
#include "Object.h"
#include "Transform.h"
#include "Graphic.h"

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

bool Collider::hitCvC(Object* root, Object* target){
	auto r_col = root->getComponentAs<Collider>("Collider");
	auto t_col = target->getComponentAs<Collider>("Collider");

	//(Ax-Bx)^2 + (Ay-By)^2 <= (Rx+Ry)^2
	return pow(r_col->getCenter().getX() - t_col->getCenter().getX(), 2) + pow(r_col->getCenter().getY() - t_col->getCenter().getY(), 2) <= pow(r_col->getRadius() + t_col->getRadius(), 2);
}

bool Collider::hitCvL(Object* root, Object* target){
	auto r_col = root->getComponentAs<Collider>("Collider");
	auto t_col = target->getComponentAs<Collider>("Collider");

	return true;
}

bool Collider::hitCvS(Object* root, Object* target){
	auto r_col = root->getComponentAs<Collider>("Collider");
	auto t_col = target->getComponentAs<Collider>("Collider");

	return true;
}

bool Collider::hitLvL(Object* root, Object* target){
	auto r_col = root->getComponentAs<Collider>("Collider");
	auto t_col = target->getComponentAs<Collider>("Collider");

	return true;
}

bool Collider::hitLvS(Object* root, Object* target){
	auto r_col = root->getComponentAs<Collider>("Collider");
	auto t_col = target->getComponentAs<Collider>("Collider");

	return true;
}

bool Collider::hitSvS(Object* root, Object* target){
	auto r_col = root->getComponentAs<Collider>("Collider");
	auto t_col = target->getComponentAs<Collider>("Collider");

	r_col->left_top = r_col->center - Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);
	r_col->right_down = r_col->center + Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);
	t_col->left_top = t_col->center - Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);
	t_col->right_down = t_col->center + Vector2(root->getComponentAs<Sprite>("Sprite")->getGraph()->getWidth() / 2, root->getComponentAs<Sprite>("Sprite")->getGraph()->getHeight() / 2);

	//(a.left < b.right) && (a.right > b.left) && (a.top < b.bottom) && (a.bottom > b.top))
	//(ALTx < BRDx && ALTy < BRDy) && (ARDx > BLTx && ARDy > BLTy)
	return (r_col->left_top.getX() < t_col->right_down.getX())
		&& (r_col->left_top.getY() < t_col->right_down.getY())
		&& (r_col->right_down.getX() > t_col->left_top.getX())
		&& (r_col->right_down.getY() > t_col->left_top.getY());
}
