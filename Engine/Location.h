#pragma once

struct Location
{
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
		if (x == val.x && y == val.y)
			return true;
		else
			return false;
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
	int x;
	int y;
};