#pragma once
#include "GameObjcet.h"

class TestBullet : public GameObject
{


public:
	TestBullet(float _x, float _y) : GameObject(_x, _y) {};
	TestBullet(Transform::Position _initPos) : GameObject(_initPos.x, _initPos.y) {};

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void Update() override;
	void OnCloneDelated() override;

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void BulletInit(Transform::Position pos) { transform.position = pos; }

	// GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	GameObject* Clone(Transform initTransform) override;
};

