#pragma once

struct Location
{
public:
	Location() = default;
	Location(const int x, const int y)
		:
		x(x),
		y(y)
	{}
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}
	void Mul(const Location& val)
	{
		x *= val.x;
		y *= val.y;
	}
	Location operator+(const Location& rhs)
	{
		return Location{ x + rhs.x, y + rhs.y };
	}
	bool operator==(const Location& val) const
	{
		return (x == val.x && y == val.y);
	}
	void Reverse()
	{
		int tmp = x;
		x = y;
		y = tmp;
	}
	void Negate()
	{
		x = -x;
		y = -y;
	}
public:
	int x;
	int y;
};