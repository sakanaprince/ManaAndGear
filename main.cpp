#include "ManaAndGear.h"

GameObject player{200,350};
int waitTime = 0;

World_WakeUp
{
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber1, L"./Data/Image/test2.png");
	player.BindBitmapArt(&ManaAndGear::_bitmapArt);
}

World_Start{}

World_Update
{
	player.Draw(ArtKeys::ArtNumber1);

	waitTime++;
	if (waitTime < 60) { return; }

	player.transform.position.y -= 0.9f;
}