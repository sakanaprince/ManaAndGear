#pragma once
#include <d2d1.h>
#include <windows.h>

struct Transform
{
	struct Position
	{
		float x{ 0.0f };
		float y{ 0.0f };

		//Position pos;@‚Á‚Ä‚â‚Á‚Ä‚à‚¢‚¢‚µ
		//Position pos{50, 20}‚Á‚Ä‚â‚Á‚Ä‚à‚¢‚¢‚æ
		Position() = default;
		Position(float _x, float _y) :x(_x), y(_y) {};

		operator D2D1_POINT_2F() const
		{
			return D2D1::Point2F(x, y);
		}

		operator POINT() const
		{
			POINT p;
			p.x = static_cast<LONG>(x);
			p.y = static_cast<LONG>(x);
			return p;
			//return (static_cast<LONG>(x), static_cast<LONG>(y));
		}
	};
};