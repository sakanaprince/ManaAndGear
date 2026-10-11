#pragma once
#include <d2d1.h>
#include <windows.h>

struct Transform
{
	Transform() = default;


	struct Position
	{
		float x{ 0.0f };
		float y{ 0.0f };

		//Position pos;Å@Ç¡ÇƒÇ‚Ç¡ÇƒÇ‡Ç¢Ç¢Çµ
		//Position pos{50, 20}Ç¡ÇƒÇ‚Ç¡ÇƒÇ‡Ç¢Ç¢ÇÊ
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

	Position position{};
	Transform(float _x, float _y) :position(_x, _y) {};
};