#pragma once
#include "GameObjcet.h"

class TestPlayer : public GameObject
{
public:
	TestPlayer(float _x, float _y) : GameObject(_x, _y) {};
	TestPlayer(Transform::Position _initPos) : GameObject(_initPos.x, _initPos.y) {};

	void Update() override{}

	float animSpeed{ 1.0f };

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void OnCloneDelated() override;

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	GameObject* Clone(Transform initTransform) override;
};

