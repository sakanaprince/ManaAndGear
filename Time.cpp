#include "Time.h"
#include "Utility.h"


void Time::Init()
{
	isInitDone = true;
	_currentTime = std::chrono::system_clock::now();
	_prevTime = _currentTime;
}

void Time::StartFrame()
{
	if (!isInitDone) { Util::FatalError(L"‰Šú‰»–Y‚ê(ƒ‰ƒCƒuƒ‰ƒŠ‚Ì–â‘è‚Å‚·B‚²‚ß‚ñ‚È‚³‚¢)"); }

	_currentTime = std::chrono::system_clock::now();
}

double Time::GetDeltaTime()
{
	return std::chrono::duration<double>(_currentTime - _prevTime).count();
}

void Time::EndFrame()
{
	_prevTime = _currentTime;
}
