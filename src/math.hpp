#pragma once

#include <iostream>
#include <vector>
#include <cmath>

struct Vector2
{
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(double x, double y) : x(x), y(y) {}
	void normalize()
	{
		double reciprocal = normalizeLength / static_cast<double>(sqrt(this->x * this->x + this->y * this->y));
		this->x *= reciprocal;
		this->y *= reciprocal;
	}

	double dot(Vector2 other) { return this->x * other.x + this->y * other.y; }

	Vector2 cross(Vector2 other) { return Vector2(this->x * other.x, this->y * other.y); }

	void add(Vector2& other) { this->x += other.x; this->y += other.y; }

	double length() { return sqrt(this->x * this->x + this->y * this->y); }
	constexpr inline double& getX() { return this->x; }
	constexpr inline double& getY() { return this->y; }
	constexpr inline const double getX() const { return this->x; }
	constexpr inline const double getY() const { return this->y; }

	friend std::ostream& operator<<(std::ostream& os, Vector2& v)
	{
		os << v.x << ", " << v.y << "\n";
		return os;
	}

	void operator++() { ++x; ++y; }
	void operator++(int a) { ++x; ++y; }
	void operator--() { --x; --y; }
	void operator--(int a) { --x; --y; }
	void operator*=(double a) { x *= a; y *= a; }
	void operator/=(double a) { x /= a; y /= a; }
	void operator+=(double a) { x += a; y += a; }
	void operator-=(double a) { x -= a; y -= a; }

	union
	{
		double x;
		double w;
	};
	union
	{
		double y;
		double h;
	};
	double normalizeLength = 1;
};

struct Rect
{
    Rect(int x, int y, int w, int h) : xy({x, y}), wh({w, h})
    {
        this->x = xy.x;
        this->y = xy.y;
        this->w = wh.w;
        this->h = wh.h;
    }
    Vector2 xy;
    Vector2 wh;
    int x, y;
    int w, h;
};

namespace Math
{
	int Random(int lb, int hb)
	{
		return (rand() % (hb - lb) + 1) + lb;
	}
}