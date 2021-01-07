#include "pch.h"
#include "MyMenu.h"

/*用于删除菜单边框*/
static HHOOK g_hook = NULL; // 全局钩子
static LRESULT WINAPI CallWndProc(int, WPARAM, LPARAM); // 安装的钩子的窗口过程
static LRESULT WINAPI MenuWndProc(HWND, UINT, WPARAM, LPARAM); // 用来处理菜单的窗口过程


WNDPROC oldWndProc = NULL; // 用来保存被替换的窗口过程
LRESULT WINAPI CallWndProc(int code, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* pStruct = (CWPSTRUCT*)lParam;
	while (code == HC_ACTION)
	{
		HWND hWnd = pStruct->hwnd;
		// 捕捉创建消息WM_CREATE，后面筛选为是否是菜单的创建
		if (pStruct->message != WM_CREATE)
			break;
		TCHAR sClassName[10];
		int Count = ::GetClassName(hWnd, sClassName, sizeof(sClassName) / sizeof(sClassName[0]));
		// 检查是否菜单窗口，#32768为菜单类名
		if (Count != 6 || _tcscmp(sClassName, _T("#32768")) != 0)
			break;

		WNDPROC lastWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
		if (lastWndProc != MenuWndProc)
		{
			// 替换菜单窗口过程  
			SetWindowLong(hWnd, GWL_WNDPROC, (long)MenuWndProc);
			// 保留原有的窗口过程   
			oldWndProc = lastWndProc;
		}
		break;
	}

	return CallNextHookEx((HHOOK)WH_CALLWNDPROC, code, wParam, lParam);
}

// 处理菜单的窗口过程
LRESULT WINAPI MenuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult;
	switch (message)
	{
	case WM_CREATE:
	{
		// 首先要去掉菜单窗口的一些扩展风格
		// 包括：WS_BORDER、WS_EX_DLGMODALFRAME、WS_EX_WINDOWEDGE
		lResult = CallWindowProc(oldWndProc, hWnd, message, wParam, lParam);
		DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
		DWORD dwNewStyle = (dwStyle & ~WS_BORDER);
		::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
		DWORD dwExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		DWORD dwNewExStyle = (dwExStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE));
		::SetWindowLong(hWnd, GWL_EXSTYLE, dwNewExStyle);
		return lResult;
	}
	case   WM_PRINT: // 此处阻止非客户区地绘制
		return CallWindowProc(oldWndProc, hWnd, WM_PRINTCLIENT, wParam, lParam);

	case   WM_WINDOWPOSCHANGING:
	{
		// 最后,由于我们在MeasureItem里指定了菜单大小，而系统会自动替菜单加边框，
		// 因此必须去掉此部分额外地尺寸，将菜单大小改小
		LPWINDOWPOS lpPos = (LPWINDOWPOS)lParam;
		lpPos->cx -= 2 * GetSystemMetrics(SM_CXBORDER) + 4;
		lpPos->cy -= 2 * GetSystemMetrics(SM_CYBORDER) + 4;
		lResult = CallWindowProc(oldWndProc, hWnd, message, wParam, lParam);
		return 0;
	}
	case   WM_GETICON:
		return 0;
	default:
		return  CallWindowProc(oldWndProc, hWnd, message, wParam, lParam);
	}
}

IMPLEMENT_DYNAMIC(CMyMenu, CMenu)
CMyMenu::CMyMenu()
	:CMenu()
{
	m_bRemoveBorder = false;
}
CMyMenu::~CMyMenu()
{
	UnhookWindowsHookEx(g_hook);
}
BOOL CMyMenu::AppendMenuW(UINT nFlags, UINT_PTR nIDNewItem, LPCTSTR lpszNewItem)
{

	return CMenu::AppendMenu(nFlags | MF_OWNERDRAW, nIDNewItem, lpszNewItem);
}

void CMyMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect(lpDrawItemStruct->rcItem);
	CRect rect2 = rect;
	/*CString str;
	if (lpDrawItemStruct->itemID)
	{
		str=
	}*/
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(165, 206, 245));//39, 128, 165
		//rect2.DeflateRect(1, 1);
		static CPen pen(PS_SOLID, 1, RGB(95, 158, 160));
		static CBrush br(RGB(212, 242, 231));
		pDC->SelectObject(&pen);
		pDC->SelectObject(&br);
		pDC->Rectangle(rect2);
	}
	else
	{
		pDC->FillSolidRect(rect, RGB(165, 206, 245));
	}
	pDC->SetBkMode(TRANSPARENT);
	rect.left += 22;
	CString str = ((MENUDATA*)(lpDrawItemStruct->itemData))->menuText;
	pDC->DrawText(str, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}

void CMyMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 30;
	lpMeasureItemStruct->itemWidth = 80;
}

void CMyMenu::RemoveMenuBorder(HINSTANCE hInst, BOOL bRemove /* = TRUE */)
{
	m_bRemoveBorder = bRemove; // 标识

	// 需要移除边框时，要安装钩子
	if (m_bRemoveBorder)
	{
		DWORD id = ::GetCurrentThreadId(); // 获取当前线程的ID
		g_hook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, hInst, id);
	}
	//UnhookWindowsHookEx(g_hook);
}

