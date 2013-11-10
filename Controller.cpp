#include "DxLib.h"
#include "Controller.h"
#include "Transform.h"
#include "Object.h"
#include "Input.h"

void Controller::update(){
	auto& position = getObject()->getComponentAs<Transform>("Transform");

	//move horizontal
	if(Input::getInstance().pushed(KEY_INPUT_LEFT, false) || Input::getInstance().pushed(KEY_INPUT_RIGHT, false)){
		lr.reset();
	}
	if(Input::getInstance().pushing(KEY_INPUT_RIGHT)){
		lr.accelerate();
		*position += Vector2(lr.spd, 0);
	}
	if(Input::getInstance().pushing(KEY_INPUT_LEFT)){
		lr.accelerate();
		*position += Vector2(-lr.spd, 0);
	}


	//jumping
	if(Input::getInstance().pushed(KEY_INPUT_SPACE, false) && status != FALL){
		status = JUMP;
	}
	if(Input::getInstance().pushing(KEY_INPUT_SPACE) && status == JUMP){
		jump.power += 0.5;
		jump.power >= jump.max_power ? jump.max_power : jump.power;
	}

	if(status == JUMP){
		if(++jump.frame < jump.power){
			double v = jump.power * 1.0 / jump.frame + 0.5 < 15 ? jump.power * 1.0 / jump.frame : 15;
			printfDx("v: %f\n", v);
			*position += Vector2(0, -v);
		}
		else {
			jump.reset();
			status = FALL;
		}
	}
	else if(status == FALL){
		double a = 1.0 / 2 * pow(jump.frame / 3, 2) < jump.max_fallspd ? 1.0 / 2 * pow(jump.frame / 3, 2) : jump.max_fallspd;
		++jump.frame;
		printfDx("a: %f\n", a);
		*position += Vector2(0, a);

		if(position->getY() > 480 - 32){
			position->setY(480 - 32);
			jump.reset();
			status = STOP;
		}
	}
}
