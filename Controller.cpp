#include "DxLib.h"
#include "Controller.h"
#include "Transform.h"
#include "Object.h"
#include "Input.h"

void Controller::update(){
	auto& position = getObject()->getComponentAs<Transform>("Transform");

	/*
	* move horizontal
	*/
	//accelerator
	if(Input::getInstance().pushing(KEY_INPUT_RIGHT)){
		momentum += Vector2(2, 0);
	}
	if(Input::getInstance().pushing(KEY_INPUT_LEFT)){
		momentum += Vector2(-2, 0);
	}
	//brake
	if(momentum.getX() != 0){//TODO: –€ŽC‚ðl—¶i‹ó’†‚ÍŒ¸‘¬‚µ‚È‚¢j
		if(momentum.getX() > 0) momentum -= Vector2( 1, 0);
		if(momentum.getX() < 0) momentum -= Vector2(-1, 0);
	}
	//adjust to max_speed
	momentum.setX(momentum.getX() >=  8 ?  8 : momentum.getX());
	momentum.setX(momentum.getX() <= -8 ? -8 : momentum.getX());


	/* 
	 * move vertical
	 */
	//jumping
	if(Input::getInstance().pushed(KEY_INPUT_SPACE, false) && status != FALL){
		status = JUMP;
	}
	if(Input::getInstance().pushing(KEY_INPUT_SPACE) && status == JUMP){
		momentum -= Vector2(0, 2);

		//jump.power += 0.5;
		//jump.power >= jump.max_power ? jump.max_power : jump.power;
	}

	/*
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
	*/

	//gravity
	momentum += Vector2(0, 0.98);

	//adjust to max_speed
	if(momentum.getY() > 24/*chip size * 3/4*/){
		momentum.setY(24);
	}

	*position += momentum;
}
