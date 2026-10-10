#include "ManaAndGear.h"


POINT playerPos{};

World_WakeUp
{
	ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber1, L"./Data/Image/test.png");
}

World_Start{}

World_Update
{
	GetCursorPos(&playerPos);

ManaAndGear::_bitmapArt.DrawArt(ArtKeys::ArtNumber1, 
	{static_cast<float>(playerPos.x), static_cast<float>(playerPos.y) });
}