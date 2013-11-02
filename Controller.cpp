#include "DxLib.h"
#include "Controller.h"
#include "Transform.h"
#include "Object.h"
#include "Input.h"

void Controller::update(){
	auto& position = getObject()->getComponentAs<Transform>("Transform");

	if(Input::getInstance().pushing(KEY_INPUT_RIGHT)){
		*position += Vector2(5, 0);
	}
	if(Input::getInstance().pushing(KEY_INPUT_LEFT)){
		*position += Vector2(-5, 0);
	}
	if(Input::getInstance().pushing(KEY_INPUT_UP)){
		*position += Vector2(0, -5);
	}
	if(Input::getInstance().pushing(KEY_INPUT_DOWN)){
		*position += Vector2(0, 5);
	}
}
