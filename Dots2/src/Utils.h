#pragma once

#include <chrono>
#include <random>

template<typename T>
struct Vec2
{
	T x, y;

	Vec2() : x(0), y(0) {}
	Vec2(T xx, T yy) : x(xx), y(yy) {}

	static Vec2<T> Random(T xMax, T yMax)
	{
		std::default_random_engine re(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::uniform_real_distribution<double> random(0, std::max(xMax, yMax));
		return { (T)random(re) % xMax, (T)random(re) % yMax };
	}
};

template<typename T>
std::ostream& operator <<(std::ostream& out, const Vec2<T>& vec2)
{
	out << vec2.x << ' ' << vec2.y;
	return out;
}

template<typename T>
Vec2<T> operator +(const Vec2<T>& vec1, const Vec2<T>& vec2)
{
	return { vec1.x + vec2.x, vec1.y + vec2.y };
}

template<typename T>
void operator +=(Vec2<T>& vec1, Vec2<T>& vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
}

template<typename T>
Vec2<T> operator -(const Vec2<T>& vec1, const Vec2<T>& vec2)
{
	return { vec1.x - vec2.x, vec1.y - vec2.y };
}

template<typename T>
Vec2<T> operator *(const Vec2<T>& vec1, const Vec2<T>& vec2)
{
	return { vec1.x * vec2.x, vec1.y * vec2.y };
}

template<typename T>
bool operator ==(const Vec2<T>& vec1, const Vec2<T>& vec2)
{
	if (vec1.x == vec2.x && vec1.y == vec2.y)
		return true;
	return false;
}