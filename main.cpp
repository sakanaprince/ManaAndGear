#include "ManaAndGear.h"

POINT mousePos{};
GameObject player;

Transform::Position pos{ 1, 1 };

World_WakeUp
{
ManaAndGear::_bitmapArt.LoadArt(ArtKeys::ArtNumber1, L"./Data/Image/test.png");
player.BindBitmapArt(&ManaAndGear::_bitmapArt);
}

World_Start{}

World_Update
{
GetCursorPos(&mousePos);

ManaAndGear::_bitmapArt.DrawArt(ArtKeys::ArtNumber1, 
	{static_cast<float>(player.position.x), static_cast<float>(player.position.y) });

Transform::Position mouseCastPos{ 
	static_cast<float>(mousePos.x), 
	static_cast<float>(mousePos.y) };

player.Draw(ArtKeys::ArtNumber1, 
	mouseCastPos);
}