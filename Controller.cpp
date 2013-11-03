#include "DxLib.h"
#include "Controller.h"
#include "Transform.h"
#include "Object.h"
#include "Input.h"

void Controller::update(){
	auto& position = getObject()->getComponentAs<Transform>("Transform");

	if (Input::getInstance().pushing(KEY_INPUT_RIGHT)){
		*position += Vector2(5, 0);
	}
	if (Input::getInstance().pushing(KEY_INPUT_LEFT)){
		*position += Vector2(-5, 0);
	}
	/*
	if (Input::getInstance().pushing(KEY_INPUT_UP)){
	*position += Vector2(0, -5);
	}
	if (Input::getInstance().pushing(KEY_INPUT_DOWN)){
	*position += Vector2(0, 5);
	}
	*/
	printfDx("%d", jump_power);

	if (Input::getInstance().pushed(KEY_INPUT_SPACE, false) && status != FALL){
		status = JUMP;
	}
	if (Input::getInstance().pushing(KEY_INPUT_SPACE)){
		jump_power += 2;
		jump_power >= 20 ? 20 : jump_power;
	}

	if (status == JUMP){
		*position -= Vector2(0, jump_power / (++frame)*2);
		if (frame >= jump_power){
			status = FALL;
			frame = 0;
		}
	}
	else if (status == FALL){
		*position += Vector2(0, (frame++));
		if (position->getY() > 480 - 32){
			position->setY(480 - 32);
			status = STOP;
			frame = 0;
			jump_power = 10;
		}
	}
}
