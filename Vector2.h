#pragma once
#include <cmath>
#include "Component.h"

class Vector2 {
private:
	double x, y;

public:
	Vector2():x(0), y(0){}
	Vector2(const Vector2& v):x(v.x), y(v.y){}
	Vector2(double x, double y):x(x), y(y){}


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
	Vector2& operator+=(const Vector2& v){
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2 operator+(const Vector2& v) const{
		return Vector2(x, y) += v;
	}
	Vector2& operator-=(const Vector2& v){
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2 operator-(const Vector2& v) const{
		return Vector2(x, y) -= v;
	}

	//æœŽZ
	Vector2& operator*=(const double k){
		x *= k;
		y *= k;
		return *this;
	}
	Vector2 operator*(const double k) const{
		return	Vector2(x, y) *= k;
	}
	Vector2& operator/=(const double k){
		x /= k;
		y /= k;
		return *this;
	}
	Vector2 operator/(const double k) const{
		return Vector2(x, y) /= k;
	}
	Vector2& operator /=(const int k){
		x *= k;
		y *= k;
		return *this;
	}
	Vector2 operator/(const int k) const{
		return Vector2(x, y) /= k;
	}

	//“àÏ
	double operator*(const Vector2& v) const{
		return (x * v.x) + (y * v.y);
	}

	//ŠOÏ
	double operator/(const Vector2& v) const{
		return (x * v.y) - (y * v.x);
	}

	//‘å‚«‚³
	double abs() const{
		return sqrt(x * x + y * y);
	}

	//³‹K‰»
	Vector2 unit() const{
		double len = abs();
		return len == 0 ? *this : *this / len;
	}

	//Šp“x
	double angle() const{
		return atan2(y, x);
	}

	//‰ñ“]
	Vector2& rotate(int radian){
		const double _sin = sin(radian);
		const double _cos = cos(radian);
		double newX = x * _cos - y * _sin;
		y = x * _sin + y * _cos;
		x = newX;
		return *this;
	}

	static Vector2 rotate(const Vector2& v, int radian){
		const double _sin = sin(radian);
		const double _cos = cos(radian);
		return Vector2(v.x * _cos - v.y * _sin, v.x * _sin + v.y * _cos);
	}

	//À•W
	void setX(double x){ this->x = x; }
	void setY(double y){ this->y = y; }
	double getX(){ return x; }
	double getY(){ return y; }

	void set(double x, double y){ this->x = x; this->y = y; }
	Vector2& get(){ return *this; }
};
