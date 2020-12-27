#include "pch.h"
#include "MyList.h"

IMPLEMENT_DYNAMIC(CMyList, CWnd)//声明控件
CMyList::CMyList()
{
	initialization = false;
	draw_dc = true;
	img_background = Image::FromFile(L"bmp\\背景色.bmp");
	option_num = -1;
	mouse_focus = false;
	l_click = false;

	title = L"名字   车牌号";
	list_space[0] = L"无敌   111111";
	list_space[1] = L"神之   222222";
	space_len = 2;

	now_page = 1;
	total_page = 2;

	page_options = 5;
}

CMyList:: ~CMyList()
{

}

BEGIN_MESSAGE_MAP(CMyList, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()


void CMyList::AddItem()//增加列表选项 
{

}


BOOL CMyList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0)
	{
		ChangePage(false);
	}
	else
	{
		ChangePage(true);
	}
	return true;
}

void CMyList::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!mouse_focus)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 13;//HOVER_DEFAULT// 若不设此参数，则无法触发mouseHover
		mouse_focus = (bool)_TrackMouseEvent(&tme);
	}
	option_num = point.y / box_height - 1;
	Draw();
	Drawrefresh();
}

LRESULT CMyList::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	mouse_focus = false;
	option_num = -1;
	Draw();
	Drawrefresh();
	return 0;
}

LRESULT CMyList::OnMouseHover(WPARAM wParam, LPARAM lParam)
{

	return 0;
}

void CMyList::OnLButtonDown(UINT nFlags, CPoint point)
{
	l_click = true;
	Draw();
	Drawrefresh();

}

void CMyList::OnLButtonUp(UINT nFlags, CPoint point)
{
	l_click = false;
	Draw();
	Drawrefresh();
}

void CMyList::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (option_num != -1 && option_num < page_options && option_num + page_options * (now_page - 1) < space_len)
	{
		RECT rect2;
		GetWindowRect(&rect2);

		CMyMenu menu;
		menu.CreatePopupMenu();
		menu.RemoveMenuBorder(GetModuleHandle(NULL));
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"修改");
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"删除");
		menu.TrackPopupMenu(TPM_LEFTALIGN, rect2.left + point.x - 10, rect2.top + point.y - 10, this); //确定弹出式菜单的位置
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu(); //资源回收
	}
	
}

void CMyList::OnSize(UINT nType, int cx, int cy)
{
	//调整大小参数
	if (initialization)
	{
		refresh = true;
	}
}

BOOL CMyList::OnEraseBkgnd(CDC* pDC)
{
	if (draw_dc)
	{
		Draw();
	}
	if (refresh)
	{
		Reinitialize();
		Draw();
		refresh = false;
	}
	Drawrefresh();
	return true;
}

void CMyList::Initialize()//初始化
{
	/*初始化位置参数*/
	GetClientRect(&crect);
	rect.X = crect.top;
	rect.Y = crect.left;
	rect.Width = crect.Width();
	rect.Height = crect.Height();

	/*初始化图层、缓冲*/
	CDC* pdc = GetDC();

	//初始化缓冲
	dc.CreateCompatibleDC(pdc);
	dc_bmp.CreateCompatibleBitmap(GetDC(), crect.Width(), crect.Height());
	dc.SelectObject(&dc_bmp);

	//初始化背景图层	
	layer_background = new Bitmap(rect.Width, rect.Height);

	//初始化文字图层	
	layer_text = new Bitmap(rect.Width, rect.Height);

	//初始化选框图层	
	layer_select_box = new Bitmap(rect.Width, box_height);
	layer_select_box_click = new Bitmap(rect.Width, box_height);

	//初始化选框图层菜单	
	layer_menu = new Bitmap(50, 100);

	/*绘制图层*/
	DrawBackground();
	DrawSelectBox();
}

void CMyList::Reinitialize()//重置大小参数
{
	/*重置位置参数*/
	GetClientRect(&crect);
	rect.X = crect.top;
	rect.Y = crect.left;
	rect.Width = crect.Width();
	rect.Height = crect.Height();
	/*重置图层、缓冲*/
	dc_bmp.Detach();
	dc_bmp.CreateCompatibleBitmap(GetDC(), crect.Width(), crect.Height());
	dc.SelectObject(&dc_bmp);

	//重置背景图层
	delete layer_background;
	layer_background = new Bitmap(rect.Width, rect.Height);

	//重置文字图层	
	delete layer_text;
	layer_text = new Bitmap(rect.Width, rect.Height);

	//重置选框图层
	delete layer_select_box;
	delete layer_select_box_click;
	layer_select_box = new Bitmap(rect.Width, box_height);
	layer_select_box_click = new Bitmap(rect.Width, box_height);

	/*绘制图层*/
	DrawBackground();
	DrawSelectBox();
}

void CMyList::DrawBackground()
{
	//白色填充
	Gdiplus::Graphics g(layer_background);
	SolidBrush Brush(Color(255, 255, 255, 255));
	g.FillRectangle(&Brush, rect);
	//复制背景
	CPoint point(0, 0);
	CLicenseplatenumberinquirysystemDlg* p = (CLicenseplatenumberinquirysystemDlg*)GetParent();
	MapWindowPoints(p, &point, 1);
	g.DrawImage(_background, -point.x, -point.y);
}

void CMyList::DrawTexts()//画文字
{
	//创建平台
	Gdiplus::Graphics g(layer_text);

	//清除原区域(擦除背景)
	g.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	Gdiplus::SolidBrush brush(Color(0, 0, 0, 0));
	g.FillRectangle(&brush, rect);

	//设置格式
	g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);//文字模式
	Gdiplus::StringFormat font_attribute;
	font_attribute.SetAlignment(Gdiplus::StringAlignmentNear);
	font_attribute.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	Gdiplus::Font myFont(L"宋体", 9);                  //设置字体
	Gdiplus::SolidBrush blackBrush(Color(255, 255, 255, 255));

	//打印内容
	g.DrawString(title, title.GetLength(), &myFont, RectF(2, 0, rect.Width, box_height), &font_attribute, &blackBrush);
	for (int i = 0; i + page_options * (now_page - 1) < space_len && i < page_options; i++)
	{
		g.DrawString(list_space[i], list_space[i].GetLength(), &myFont, RectF(2, box_height * (i + 1) + 0, rect.Width, box_height), &font_attribute, &blackBrush);
	}

	//打印页数
	font_attribute.SetAlignment(Gdiplus::StringAlignmentCenter);
	CString prin_page;
	prin_page.Format(L"%d/%d", now_page, total_page);
	g.DrawString(prin_page, prin_page.GetLength(), &myFont, RectF(2, rect.Height - box_height, rect.Width, box_height), &font_attribute, &blackBrush);
}

void CMyList::DrawSelectBox()
{
	/*一般选框层*/
	Gdiplus::Graphics g(layer_select_box);
	//采用覆盖模式
	g.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//画矩形
	Gdiplus::SolidBrush brush(Color(20, 127, 255, 170));
	g.FillRectangle(&brush, Rect(0, 0, rect.Width, box_height));

	/*单击时选框层*/
	Gdiplus::Graphics g2(layer_select_box_click);
	//采用覆盖模式
	g2.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//画矩形
	Gdiplus::SolidBrush brush2(Color(80, 127, 255, 170));
	g2.FillRectangle(&brush2, Rect(0, 0, rect.Width, box_height));
}

void CMyList::Draw()
{
	draw_dc = false;
	//第一次初始化
	if (!initialization)
	{
		Initialize();
		initialization = true;
	}
	//显示
	Gdiplus::Graphics g(dc);
	//清除原图
	g.Clear(Color(0, 255, 255, 255));

	//画背景
	g.DrawImage(layer_background, 0, 0);
	//画选框
	if (option_num != -1 && option_num < page_options && option_num + page_options * (now_page - 1) < space_len)
	{
		if (l_click)
		{
			g.DrawImage(layer_select_box_click, 0, (option_num + 1) * box_height);
		}
		else
		{
			g.DrawImage(layer_select_box, 0, (option_num + 1) * box_height);
		}
	}
	//画文字
	DrawTexts();
	g.DrawImage(layer_text, 0, 0);
}

void CMyList::Drawrefresh()
{
	CDC* pdc = GetDC();
	pdc->BitBlt(crect.left, crect.top, crect.Width(), crect.Height(), &dc, 0, 0, SRCCOPY);
}

void CMyList::ChangePage(bool next)
{
	if (next)
	{
		if (now_page < total_page)
		{
			now_page++;
			Draw();
			Drawrefresh();
		}
	}
	else
	{
		if (now_page > 1)
		{
			now_page--;
			Draw();
			Drawrefresh();
		}
	}
}