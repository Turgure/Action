#pragma once
#include "Component.h"

class EnemyStatus : public Component{
public:
	int getHp(){ return hp; }
	int getStr(){ return str; }
	int getDef(){ return def; }

private:
	int hp;
	int str;
	int def;
};
