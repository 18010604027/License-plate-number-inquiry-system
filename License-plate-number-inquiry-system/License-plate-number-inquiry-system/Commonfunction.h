#pragma once
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
void sleep_ms(unsigned int secs);//��ʱ�����룩
void PutDebug(int i, ...);//���һ������
void PutDebug(LPCWSTR s, ...);//���
CString   ExpandShortcut(CString& inFile);
Bitmap* SaveHIcon2PngFile(HICON hIcon);