#pragma once
#include <string>
#include "Component.h"

class Controller : public Component{
private:
	enum Status{
		EMPTY,
		STOP,
		WALK,
		RUN,
		JUMP,
		FALL,
		STATUS_NUM
	} status;

public:
	virtual const std::string& getKeyString() const override {
		static std::string key = "Gamepad";
		return key;
	}

	Controller() :status(EMPTY){}
	void update() override;

private:
	int frame = 0;
	int jump_power = 10;
};