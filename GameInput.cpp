#include "GameInput.h"
#include <algorithm>

bool GameInput::GetKey(char keyCode)
{
	//！？！？char型でintの代わりになるんか
	return GetAsyncKeyState(keyCode) & 0x8000;
}