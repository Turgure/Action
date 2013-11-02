#pragma once
#include <cmath>
#include "Component.h"

class Vector2 {
private:
	double x, y;

public:	
	Vector2():x(0),y(0){};
	Vector2(const Vector2& v):x(v.x), y(v.y){};
	Vector2(double x, double y):x(x), y(y){};


	//‘ã“ü
	Vector2& operator=(const Vector2& v){
		x = v.x;
		y = v.y;
		return *this;
	}
	//”äŠr
	bool operator==(const Vector2& v) const{
		return (x == v.x && y == v.y);
	}
	bool operator!=(const Vector2& v) const{
		return (x != v.x || y != v.y);
	}

	//³•‰
	const Vector2& operator+() const{
		return *this;
	}
	Vector2 operator-() const{
		return Vector2(-x, -y);
	}

	//‰ÁŒ¸ŽZ
	Vector2 operator+(const Vector2& v) const{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2& operator+=(const Vector2& v){
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2 operator-(const Vector2& v) const{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2& operator-=(const Vector2& v){
		x -= v.x;
		y -= v.y;
		return *this;
	}
	
	//À•W
	void setX(double x){ this->x = x; }
	void setY(double y){ this->y = y; }
	double getX(){ return x; }
	double getY(){ return y; }

	void set(double x, double y){ this->x = x; this->y = y; }
	Vector2& get(){ return *this; }
};
