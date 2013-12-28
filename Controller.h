#pragma once
#include <string>
#include "Vector2.h"
#include "Component.h"


class Controller : public Component{
private:
	enum Status{
		STOP,
		WALK,
		RUN,
		JUMP,
		FALL,
		STATUS_NUM
	} status;

public:
	virtual const std::string& getKeyString() const override {
		static std::string key = "Controller";
		return key;
	}

	Controller():status(STOP){}
	void update() override;
	void setMomentum(Vector2 v){ momentum = v; }
	Vector2 getMomentum(){ return momentum;  }
	void resetYMomentum(){ momentum.setY(0); }

private:
	struct LR{
		LR(){ reset(); }
		void reset(){
			spd = 0;
		}

		void accelerate(){
			if(spd++ >= max) spd = max;
		}

		int spd;
		const int max = 5;
	} lr;

	struct Jump{
		Jump(){ reset();  }
		void reset(){
			frame = 0;
			power = 20;
		}

		int frame;
		double power;
		const double max_fallspd = 15;
		const double max_power = 25;
	} jump;

	Vector2 momentum;
};