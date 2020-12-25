#pragma once
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
void sleep_ms(unsigned int secs);//延时（毫秒）
void PutDebug(int i, ...);//输出一串数字
void PutDebug(LPCWSTR s, ...);//输出
CString   ExpandShortcut(CString& inFile);
Bitmap* SaveHIcon2PngFile(HICON hIcon);