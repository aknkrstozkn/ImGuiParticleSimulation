#pragma once
#ifndef  VEC_H_
#define VEC_H_

#include <cmath>

namespace myengine
{
	
struct Vec
{	
	double x;
	double y;

	double length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	void normalize()
	{
		const auto l = length();
		x /= l;
		y /= l;
	}

	Vec operator+(const Vec & other) const { return Vec{ x + other.x, y + other.y }; }
	Vec& operator+=(const Vec & other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec operator-(const Vec & other) const { return Vec{ x - other.x, y - other.y }; }
	Vec& operator-=(const Vec & other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
};

}



#endif


