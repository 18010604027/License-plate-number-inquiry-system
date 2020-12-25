#include "pch.h"
#include "Commonfunction.h"
void sleep_ms(unsigned int secs)
{
	struct timeval tval;
	tval.tv_sec = secs / 1000;
	tval.tv_usec = (secs * 1000) % 1000000;
	select(0, NULL, NULL, NULL, &tval);
}

void PutDebug(int i, ...)
{
	int j = 0;
	va_list arg_ptr;
	va_start(arg_ptr, i);
	while (i--)
	{
		j = va_arg(arg_ptr, int);
		if (j == -1)break;
		CString str;
		str.Format(L"%d ", j);
		OutputDebugString(str);
	}
	OutputDebugString(L"\n");
	va_end(arg_ptr);
}
void PutDebug(LPCWSTR s, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, s);
	CString str;
	str.FormatV(s, arg_ptr);
	OutputDebugString(str);
}


//inFile是快捷方式文件名
//返回快捷方式所指向的文件名
CString   ExpandShortcut(CString& inFile)//获取快捷方式路径
{
	CString   outFile = _T(" ");

	ASSERT(inFile != _T(""));

	IShellLink* psl;
	HRESULT   hres;
	LPTSTR   lpsz = inFile.GetBuffer(MAX_PATH);

	hres = ::CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		if (SUCCEEDED(hres))
		{
#ifndef _UNICODE
			wchar_t   wsz[MAX_PATH];
			::MultiByteToWideChar(CP_ACP, 0, lpsz, -1, wsz, MAX_PATH);
			hres = ppf->Load(wsz, STGM_READ);
#else
			hres = ppf->Load(lpsz, STGM_READ);
#endif
			if (SUCCEEDED(hres))
			{
				WIN32_FIND_DATA   wfd;
				HRESULT   hres = psl->GetPath(outFile.GetBuffer(MAX_PATH),
					MAX_PATH,
					&wfd,
					SLGP_UNCPRIORITY);

				outFile.ReleaseBuffer();
			}
			ppf->Release();
		}
		psl->Release();
	}

	inFile.ReleaseBuffer();

	return   outFile;
}

//用于转格式，保留透明块
Bitmap* SaveHIcon2PngFile(HICON hIcon)
{
	if (hIcon == NULL)
	{
		ASSERT(FALSE);
		return NULL;
	}

	ICONINFO icInfo = { 0 };
	if (!::GetIconInfo(hIcon, &icInfo))
	{
		ASSERT(FALSE);
		return NULL;
	}
	BITMAP bitmap;
	GetObject(icInfo.hbmColor, sizeof(BITMAP), &bitmap);

	Bitmap* pBitmap = NULL;
	Bitmap* pWrapBitmap = NULL;
	if (bitmap.bmBitsPixel != 32)
	{
		pBitmap = Bitmap::FromHICON(hIcon);
	}
	else
	{
		pWrapBitmap = Bitmap::FromHBITMAP(icInfo.hbmColor, NULL);
		BitmapData bitmapData;
		Rect rcImage(0, 0, pWrapBitmap->GetWidth(), pWrapBitmap->GetHeight());
		pWrapBitmap->LockBits(&rcImage, ImageLockModeRead, pWrapBitmap->GetPixelFormat(), &bitmapData);

		pBitmap = new Bitmap(bitmapData.Width, bitmapData.Height, bitmapData.Stride,
			PixelFormat32bppARGB, (BYTE*)bitmapData.Scan0);
	}

	Gdiplus::Color Bmpcolor;
	BOOL BmpcolorTag = TRUE;;
	for (UINT bmpx = 0; bmpx < pBitmap->GetWidth(); bmpx++)
	{
		for (UINT bmpy = 0; bmpy < pBitmap->GetHeight(); bmpy++)
		{
			pBitmap->GetPixel(bmpx, bmpy, &Bmpcolor);
			if ((Bmpcolor.GetValue() >> 24) != 0)
			{
				BmpcolorTag = FALSE;
				break;
			}
		}
		if (BmpcolorTag == FALSE)
			break;
	}
	if (BmpcolorTag == TRUE)
	{
		delete pWrapBitmap;
		DeleteObject(icInfo.hbmColor);
		DeleteObject(icInfo.hbmMask);
		pBitmap = Gdiplus::Bitmap::FromHICON(hIcon);
	}
	return pBitmap;
}