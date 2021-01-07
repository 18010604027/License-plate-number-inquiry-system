#include "pch.h"
#include "MyMenu.h"

/*����ɾ���˵��߿�*/
static HHOOK g_hook = NULL; // ȫ�ֹ���
static LRESULT WINAPI CallWndProc(int, WPARAM, LPARAM); // ��װ�Ĺ��ӵĴ��ڹ���
static LRESULT WINAPI MenuWndProc(HWND, UINT, WPARAM, LPARAM); // ��������˵��Ĵ��ڹ���


WNDPROC oldWndProc = NULL; // �������汻�滻�Ĵ��ڹ���
LRESULT WINAPI CallWndProc(int code, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* pStruct = (CWPSTRUCT*)lParam;
	while (code == HC_ACTION)
	{
		HWND hWnd = pStruct->hwnd;
		// ��׽������ϢWM_CREATE������ɸѡΪ�Ƿ��ǲ˵��Ĵ���
		if (pStruct->message != WM_CREATE)
			break;
		TCHAR sClassName[10];
		int Count = ::GetClassName(hWnd, sClassName, sizeof(sClassName) / sizeof(sClassName[0]));
		// ����Ƿ�˵����ڣ�#32768Ϊ�˵�����
		if (Count != 6 || _tcscmp(sClassName, _T("#32768")) != 0)
			break;

		WNDPROC lastWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
		if (lastWndProc != MenuWndProc)
		{
			// �滻�˵����ڹ���  
			SetWindowLong(hWnd, GWL_WNDPROC, (long)MenuWndProc);
			// ����ԭ�еĴ��ڹ���   
			oldWndProc = lastWndProc;
		}
		break;
	}

	return CallNextHookEx((HHOOK)WH_CALLWNDPROC, code, wParam, lParam);
}

// ����˵��Ĵ��ڹ���
LRESULT WINAPI MenuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult;
	switch (message)
	{
	case WM_CREATE:
	{
		// ����Ҫȥ���˵����ڵ�һЩ��չ���
		// ������WS_BORDER��WS_EX_DLGMODALFRAME��WS_EX_WINDOWEDGE
		lResult = CallWindowProc(oldWndProc, hWnd, message, wParam, lParam);
		DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
		DWORD dwNewStyle = (dwStyle & ~WS_BORDER);
		::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
		DWORD dwExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		DWORD dwNewExStyle = (dwExStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE));
		::SetWindowLong(hWnd, GWL_EXSTYLE, dwNewExStyle);
		return lResult;
	}
	case   WM_PRINT: // �˴���ֹ�ǿͻ����ػ���
		return CallWindowProc(oldWndProc, hWnd, WM_PRINTCLIENT, wParam, lParam);

	case   WM_WINDOWPOSCHANGING:
	{
		// ���,����������MeasureItem��ָ���˲˵���С����ϵͳ���Զ���˵��ӱ߿�
		// ��˱���ȥ���˲��ֶ���سߴ磬���˵���С��С
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
	m_bRemoveBorder = bRemove; // ��ʶ

	// ��Ҫ�Ƴ��߿�ʱ��Ҫ��װ����
	if (m_bRemoveBorder)
	{
		DWORD id = ::GetCurrentThreadId(); // ��ȡ��ǰ�̵߳�ID
		g_hook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, hInst, id);
	}
	//UnhookWindowsHookEx(g_hook);
}

