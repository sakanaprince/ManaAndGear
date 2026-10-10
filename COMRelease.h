#pragma once

#include <windows.h>
#include <vector>


/// <summary>
/// このクラスは監視対象に入っているCOMを解放する
/// COMは全員継承しているIUnknownを活躍して
/// </summary>
class COMRelease
{
private:
	//COM（コンポーネントオブジェクトモデル）は全員IUnknown抽象クラスを継承しとる,これで上手く全開放出来る説
	std::vector<IUnknown*> releaseTargets;

public:
	~COMRelease()
	{
		MessageBox(NULL, L"Destracta", L"", 0);
		AllRelease();
	}

	// COMオブジェクト解放用テンプレート
	//Tであらゆる型に対応できるように

	//～～～知恵～～～ 
	//ポインタのポインタっていうのがあるらしい、 int **aみたいな？
	//ポインタのポインタは普段他人を指してるポインタ「を」指すためのポインタ
	void AllRelease()
	{
		//ポインタを指してるオブジェクト参照　をリリースってこと？
		for (IUnknown*& obj : releaseTargets)
		{
			if (obj)
			{
				obj->Release();
				obj = nullptr;
			}
		}

		releaseTargets.clear();
		MessageBox(NULL, L"解放した", L"", 1);
	}

	//IUnknown継承してるクラス(COMのやつら)を監視対象にいれる
	void AddReleaseTarget(IUnknown* obj)
	{
		if(!obj)
		{ 
			MessageBox(NULL, L"大丈夫？null入れようとしてるから監視対象にしないよ(後から中身を入れても解放対象にならない)", L"", 1);
			return;
		}

		releaseTargets.push_back(obj);
	}
};

