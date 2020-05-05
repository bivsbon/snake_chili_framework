#pragma once
#include "Location.h"
#include "Colors.h"

class SpeedUp
{
public:
	Location GetLocation() const;
	float GetDuration() const;
	void Spawn(const Location in_loc);
	bool IsExist() const;
	void Terminate();
public:
	static constexpr Color COLOR = Colors::Green;
private:
	bool exist = false;
	Location loc;
	float duration = 35.0f;
};
