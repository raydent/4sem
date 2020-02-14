#pragma once
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;


class vector2 {
private:
	float x = 0, y = 0;
public:
	vector2 (float x_ = 0, float y_ = 0): x(x_), y(y_){}
	float x_() const { return x; }
	float y_() const { return y; }
	void assign(float x_, float y_) {
		x = x_;
		y = y_;
	}
	vector2 norm() const {
		float normer = sqrt(x_() * x_() + y_() * y_());
		return vector2(x_()/normer, y_() / normer);
	}
	vector2 normal () const {
		return vector2(y_(), -x_());
	}
	float len() const {
		return sqrt(x_() * x_() + y_() * y_());
	}
	float squareLen() const {
		return (x_() * x_() + y_() * y_());
	}
	void rotate() {
		float temp = x;
		x = y;
		y = -temp;
	}
	vector2 getRotated() {
		return norm();
	}
};

vector2 operator * (vector2 v, float k) {
	vector2 v1(v.x_() * k, v.y_() * k);
}
vector2 operator * (float k, vector2 v) {
	vector2 v1(v.x_() * k, v.y_() * k);
}
ostream& operator << (ostream& os, vector2 v) {
	os << v.x_() << " " << v.y_();
	return os;
}
istream& operator >> (istream& is, vector2& v) {
	int x, y;
	is >> x >> y;
	v.assign(x, y);
	return is;
}

vector2 operator + (const vector2& lhs, const vector2 & rhs) {
	return vector2(lhs.x_() + rhs.x_(), lhs.y_() + rhs.y_());
}

vector2& operator += (vector2& lhs, const vector2& rhs) {
	lhs.assign(lhs.x_() + rhs.x_(), lhs.y_() + rhs.y_());
	return lhs;
}

vector2 operator - (const vector2& lhs, const vector2& rhs) {
	return vector2(lhs.x_() - rhs.x_(), lhs.y_() - rhs.y_());
}

vector2& operator -= (vector2& lhs, const vector2& rhs) {
	lhs.assign(lhs.x_() - rhs.x_(), lhs.y_() - rhs.y_());
	return lhs;
}

float operator * (vector2& lhs, const vector2& rhs) {
	return lhs.x_() * rhs.x_() + lhs.y_() * rhs.y_();
}

float operator ^ (vector2& lhs, const vector2& rhs) {
	return lhs.x_() * rhs.y_() - lhs.y_() * rhs.x_();
}
vector2 operator / (vector2 v, float k) {
	vector2 v1(v.x_() / k, v.y_() / k);
}
vector2& operator -- (vector2& v) {
	v.assign(v.x_() - 1, v.y_() - 1);
	return v;
}
