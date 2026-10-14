#pragma once
#include "GameObjcet.h"

class TestPlayer : public GameObject
{
	
public:

	TestPlayer(float _x, float _y) : GameObject(_x, _y) {};

	void OnCloned() override
	{
		transform.position = { 20,20 };

		MessageBox(NULL, L" A L I V E", L"", 0);
	};
};

