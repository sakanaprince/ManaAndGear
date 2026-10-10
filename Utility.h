#pragma once
#include <d2d1.h>

namespace Util
{
    //まぁね hResult != S_OKでも良いんだけどね、マクロがあるんで
    inline bool IsNG(HRESULT hResult) { return FAILED(hResult); }

    /// <summary>
    /// ゲームが強制終了する！
    /// </summary>
    /// <param name="text">終了時に表示されるお好きなメッセージを入れてね</param>
    inline void FatalError(LPCWSTR text = L"")
    {
        MessageBox(NULL, text, L"", 0);
        exit(-1);
    }
}