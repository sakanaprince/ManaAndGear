#pragma once
#include <windows.h>
#include <array>

class GameInput
{
private:

public:

	/// <summary>
	/// キーが押されているかを確認する
	/// </summary>
	/// <param name="keyCode"> 'Z'みたいに送る。シングルクオーテーションで囲って...（数字の7とシフト）</param>
	/// <returns>そのkeyCodeが押されているならtrueになり、押されていなければfalseになる</returns>
	bool GetKey(char keyCode);


};

