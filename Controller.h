#pragma once
#include <string>
#include "Component.h"

class Controller : public Component{
public:
	virtual const std::string& getKeyString() const override {
		static std::string key = "Gamepad";
		return key;
	}

	void update() override;
};