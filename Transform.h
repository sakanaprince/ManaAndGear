#pragma once
#include <d2d1.h>
#include <windows.h>

struct Transform
{
	struct Position
	{
		float x{ 0.0f };
		float y{ 0.0f };

		//Position pos;Å@Ç¡ÇƒÇ‚Ç¡ÇƒÇ‡Ç¢Ç¢Çµ
		//Position pos{50, 20}Ç¡ÇƒÇ‚Ç¡ÇƒÇ‡Ç¢Ç¢ÇÊ
		constexpr Position() = default;
		constexpr Position(float _x, float _y) :x(_x), y(_y) {};

		operator D2D1_POINT_2F() const
		{
			return D2D1::Point2F(x, y);
		}

		operator POINT() const
		{
			POINT p;
			p.x = static_cast<LONG>(x);
			p.y = static_cast<LONG>(y);
			return p;
		}

		Position& operator+=(const Position& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr Position operator+(const Position& _pos) const
		{
			return Position(x + _pos.x, y + _pos.y);
		}
	};

	Transform() = default;
	Transform(float _x, float _y) :position(_x, _y) {};
	Position position{};
};