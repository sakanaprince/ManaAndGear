#pragma once
#include <d2d1.h>

//‚Ü‚Ÿ‚Ë hResult != S_OK‚Å‚à—Ç‚¢‚ñ‚¾‚¯‚Ç‚ËAƒ}ƒNƒ‚ª‚ ‚é‚ñ‚Å
inline bool IsNG(HRESULT hResult) { return FAILED(hResult); }


