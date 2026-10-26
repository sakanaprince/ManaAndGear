#include "TestBullet.h"

GameObject* TestBullet::Clone(Transform initTransform)
{
    GameObject* maked = new TestBullet(*this);

    maked->transform.position = initTransform.position;

    return maked;
}

void TestBullet::Update()
{
    transform.position.x += 15.0f;

    if (transform.position.x > 900.0f) { SetActive(false); }
}

void TestBullet::OnCloneDelated()
{
}
