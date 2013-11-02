#pragma once
#include <string>
#include "Component.h"
#include "Vector2.h"

class Transform : public Component , public Vector2{
	virtual const std::string& getKeyString() const {
		static std::string key = "Transform";
		return key;
	}
};
