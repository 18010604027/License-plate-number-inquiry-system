#include "pch.h"
#include "MyList.h"
#define M false//是否为动态链表
IMPLEMENT_DYNAMIC(CMyList, CWnd)//声明控件
CMyList::CMyList()
{


	initialization = false;//是否已初始化
	draw_dc = true;//是否需要绘画缓冲
	option_num = -1;//被选中项
	menu_num = -1;//菜单打开项
	mouse_focus = false;//是否获得鼠标焦点
	l_click = false;//鼠标左键是否被按下

	space_len = 0;//当前存放数据长度

	now_page = 1;//当前页数
	total_page = 1;//总页数
	page_options = 5;//每页选项数

	layer_background = NULL;//背景图层
	layer_text = NULL;//文字图层
	layer_select_box = NULL;//选框图层
	layer_select_box_click = NULL;//选框图层（单击）
	layer_menu = NULL;//菜单图层

	box_height = 25;//选框高度

	if (M)
	{
		if (list_data.plate_read("Data\\plate_num.data"))
		{
			space_len = list_data.count();
		}
	}
	else
	{
		if (list_data2.plate_read("Data\\plate_num.data"))
		{
			space_len = list_data2.count();
		}
	}
	total_page = space_len / page_options + (space_len % page_options ? 1 : 0);
	if (total_page == 0)
	{
		total_page = 1;
	}
	list_num = NULL;
}
CMyList:: ~CMyList()
{
	if (M)
	{
		list_data.plate_write();
	}
	else
	{
		list_data2.plate_write();
	}

}

BEGIN_MESSAGE_MAP(CMyList, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	ON_WM_DROPFILES()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()


void CMyList::AddItem(int i, ...)//增加列表选项 
{
	/*LPCWSTR str = 0;
	va_list arg_ptr;
	va_start(arg_ptr, i);
	int j = 0;
	for (int j = 0; j < i; j++)
	{
		str = va_arg(arg_ptr, LPCWSTR);
		list_space[space_len][j] = str;
	}
	space_len++;
	va_end(arg_ptr);*/
}
void CMyList::AddProverty(CString Title)
{
	titles[title_len++] = Title;
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
	option_num = point.y / (int)box_height - 1;
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
void CMyList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (option_num != -1 && option_num < page_options && option_num + page_options * (now_page - 1) < space_len)
	{
		menu_num = option_num;
		MenuChange(page_options * (now_page - 1) + menu_num);
	}
}
void CMyList::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();//获取焦点
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
	SetFocus();//获取焦点
	menu_num = option_num;
	if (option_num != -1 && option_num < page_options && option_num + page_options * (now_page - 1) < space_len)
	{
		RECT rect2;
		GetWindowRect(&rect2);

		CMyMenu menu;
		menu.CreatePopupMenu();
		menu.RemoveMenuBorder(GetModuleHandle(NULL));
		menu.AppendMenu(MF_STRING, WM_MENU_ADD, L"添加");
		menu.AppendMenu(MF_STRING, WM_MENU_EDIT, L"修改");
		menu.AppendMenu(MF_STRING, WM_MENU_DELETE, L"删除");
		menu.TrackPopupMenu(TPM_LEFTALIGN, rect2.left + point.x - 10, rect2.top + point.y - 10, this); //确定弹出式菜单的位置
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu(); //资源回收
	}
	else
	{
		RECT rect2;
		GetWindowRect(&rect2);

		CMyMenu menu;
		menu.CreatePopupMenu();
		menu.RemoveMenuBorder(GetModuleHandle(NULL));
		menu.AppendMenu(MF_STRING, WM_MENU_ADD, L"添加");
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
void CMyList::OnDropFiles(HDROP hDropInfo)
{
	WCHAR szFilePath[1024];
	UINT count;
	count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0); //获取拖拽文件数
	
	for (int i = count - 1; i >= 0; i--)
	{
		
		DragQueryFile(hDropInfo, i, szFilePath, sizeof(szFilePath)); //获取文件路径
		DWORD dwNum;
		CHAR psText[1024];
		dwNum = sizeof(szFilePath);
		WideCharToMultiByte(CP_OEMCP, NULL, szFilePath, -1, psText, dwNum, NULL, FALSE);
		if (M)
		{
			if (list_data.plate_read(psText))
			{
				change_file = true;
			}
		}
		else
		{
			if (list_data2.plate_read(psText))
			{
				change_file = true;
			}
		}
	}
	//list_data._radix_sort();
	if (M)
	{
		list_data._quick_sort();
		space_len = list_data.count();
	}
	else
	{
		list_data2._radix_sort();
		space_len = list_data2.count();
	}
	total_page = space_len / page_options + (space_len % page_options ? 1 : 0);
	if (total_page == 0)
	{
		total_page = 1;
	}
	DrawTexts();
	Draw();
	Drawrefresh();
}
BOOL CMyList::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	UINT uMsg = LOWORD(wParam);
	//接收菜单信息
	if (uMsg == WM_MENU_ADD)
	{
		EditDlg dlg;
		dlg.SetCaption(L"添加");
		if (dlg.DoModal() == IDOK)
		{
			change_file = true;
			CString license;
			CString name;
			CString place;
			CString phone;
			dlg.GetData(license,
				name,
				place,
				phone);
			if (M)
			{
				list_data.insert(license, name, place, phone);
			}
			else
			{
				list_data2.insert(license, name, place, phone);
			}
			DrawTexts();
			Draw();
			Drawrefresh();
		}
	}
	if (uMsg == WM_MENU_EDIT)
	{
		MenuChange(page_options * (now_page - 1) + menu_num);
	}
	if (uMsg == WM_MENU_DELETE)
	{
		if (M)
		{
			list_data._delete(page_options * (now_page - 1) + menu_num + 1);
		}
		else
		{
			list_data2._delete(page_options * (now_page - 1) + menu_num + 1);
		}
	}

	return CWnd::OnCommand(wParam, lParam);
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
	layer_select_box = new Bitmap(rect.Width, int(box_height));
	layer_select_box_click = new Bitmap(rect.Width, int(box_height));

	//初始化选框图层菜单	
	layer_menu = new Bitmap(50, 100);

	//设置页面选项数
	page_options = rect.Height / box_height - 2;
	total_page = space_len / page_options + (space_len % page_options ? 1 : 0);
	if (total_page == 0)
	{
		total_page = 1;
	}
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
	layer_select_box = new Bitmap(rect.Width, (int)box_height);
	layer_select_box_click = new Bitmap(rect.Width, (int)box_height);

	//设置页面选项数
	page_options = rect.Height / box_height - 2;
	total_page = space_len / page_options + (space_len % page_options ? 1 : 0);
	if (total_page == 0)
	{
		total_page = 1;
	}
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
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	Gdiplus::StringFormat font_attribute;
	font_attribute.SetAlignment(Gdiplus::StringAlignmentNear);
	font_attribute.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	Gdiplus::Font myFont(L"黑体", 11);                  //设置字体
	Gdiplus::SolidBrush blackBrush(Color(255, 255, 255, 255));

	//打印属性
	Gdiplus::REAL len = (Gdiplus::REAL)rect.Width / title_len;
	for (int i = 0; i < title_len; i++)
	{
		g.DrawString(titles[i], titles[i].GetLength(), &myFont, Gdiplus::RectF(i * len, 0, len, box_height), &font_attribute, &blackBrush);
	}

	//打印页数
	font_attribute.SetAlignment(Gdiplus::StringAlignmentCenter);
	CString prin_page;
	prin_page.Format(L"%d/%d", now_page, total_page);
	g.DrawString(prin_page, prin_page.GetLength(), &myFont, Gdiplus::RectF(2, (Gdiplus::REAL)(rect.Height - box_height), (Gdiplus::REAL)rect.Width, box_height), &font_attribute, &blackBrush);

	//打印内容
	Gdiplus::Font myFont2(L"宋体", 10);
	font_attribute.SetAlignment(Gdiplus::StringAlignmentNear);
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);//文字模式
	if (list_num)
	{
		struct ListNum* p;
		p = list_num->next;
		for (int i = 0; i < page_options * (now_page - 1); i++)
		{
			p = p->next;
		}
		for (int i = 0; p && i < page_options; i++, p = p->next)
		{
			plate_data* data;
			if (M)
			{
				data = list_data.return_num(p->num + 1)->data;
			}
			else
			{
				data = list_data2.return_num(p->num + 1)->data;
			}
			g.DrawString(data->license, data->license.GetLength(), &myFont2, RectF(2 + 0 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
			g.DrawString(data->name, data->name.GetLength(), &myFont2, RectF(2 + 1 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
			g.DrawString(data->place, data->place.GetLength(), &myFont2, RectF(2 + 2 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
			g.DrawString(data->phone, data->phone.GetLength(), &myFont2, RectF(2 + 3 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
		}

	}
	else
	{
		for (int i = 0; i + page_options * (now_page - 1) < space_len && i < page_options; i++)
		{
			plate_data* data;
			if (M)
			{
				data = list_data.return_num(i + page_options * (now_page - 1) + 1)->data;

			}
			else
			{
				data = list_data2.return_num(i + page_options * (now_page - 1) + 1)->data;
			}
			g.DrawString(data->license, data->license.GetLength(), &myFont2, RectF(2 + 0 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
			g.DrawString(data->name, data->name.GetLength(), &myFont2, RectF(2 + 1 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
			g.DrawString(data->place, data->place.GetLength(), &myFont2, RectF(2 + 2 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
			g.DrawString(data->phone, data->phone.GetLength(), &myFont2, RectF(2 + 3 * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
		}

	}


}
void CMyList::DrawSelectBox()
{
	/*一般选框层*/
	Gdiplus::Graphics g(layer_select_box);
	//采用覆盖模式
	g.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//画矩形
	Gdiplus::SolidBrush brush(Color(20, 127, 255, 170));
	g.FillRectangle(&brush, RectF(0, 0, (Gdiplus::REAL)rect.Width, box_height));

	/*单击时选框层*/
	Gdiplus::Graphics g2(layer_select_box_click);
	//采用覆盖模式
	g2.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//画矩形
	Gdiplus::SolidBrush brush2(Color(80, 127, 255, 170));
	g2.FillRectangle(&brush2, RectF(0, 0, (Gdiplus::REAL)rect.Width, box_height));
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
			g.DrawImage(layer_select_box_click, (Gdiplus::REAL)0, (option_num + 1) * box_height);
		}
		else
		{
			g.DrawImage(layer_select_box, (Gdiplus::REAL)0, (option_num + 1) * box_height);
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
void CMyList::MenuChange(int num)
{
	if (num == -1)
	{
		MessageBox(L"该车牌号不在记录内",L"提示");
		return;
	}
	EditDlg dlg;
	dlg.SetCaption(L"编辑");
	plate_data* data;
	plate_node* node;
	int num2;
	if (list_num)
	{
		struct ListNum* p;
		p = list_num->next;
		for (int i = 0; i < num; i++)
		{
			p = p->next;
		}
		if (M)
		{
			node = list_data.return_num(p->num + 1);
		}
		else
		{
			data = list_data2.return_num(p->num + 1)->data;
		}
		num2 = p->num + 1;
	}
	else
	{
		if (M)
		{
			node = list_data.return_num(num + 1);
		}
		else
		{
			data = list_data2.return_num(num + 1)->data;
		}
		num2 = num + 1;
	}
	if (M)
	{
		data = node->data;
	}
	
	dlg.SetData(4,
		data->license,
		data->name,
		data->place,
		data->phone);
	if (dlg.DoModal() == IDOK)
	{
		change_file = true;
		if (M)
		{
			list_data._delete(node);
		}
		else
		{
			list_data2._delete(num2);
		}
		CString license;
		CString name;
		CString place;
		CString phone;
		dlg.GetData(license,
			name,
			place,
			phone);
		if (M)
		{
			list_data.insert(license, name, place, phone);

		}
		else
		{
			list_data2.insert(license, name, place, phone);
		}
		DrawTexts();
		Draw();
		Drawrefresh();
	}
}
void CMyList::Search(CString str, int index)
{
	if (index == 0)
	{
		if (list_num)
		{
			delete list_num;
		}
		if (M)
		{
			list_num = list_data.Search(str, space_len);
		}
		else
		{
			list_num = list_data2.Search(str, space_len);
		}
		total_page = space_len / page_options + (space_len % page_options ? 1 : 0);
		if (total_page == 0)
		{
			total_page = 1;
		}
		DrawTexts();
		Draw();
		Drawrefresh();
	}
	else
	{
		if (list_num)
		{
			delete list_num;
			list_num = NULL;
		}
		if (M)
		{
			if (index == 1)
			{
				MenuChange(list_data.half_search(str));
			}
			else if (index == 2)
			{
				MenuChange(list_data._index_search(str));
			}
		}
		else
		{
			if (index == 1)
			{
				MenuChange(list_data2.half_search(str));
			}
			else if (index == 2)
			{
				MenuChange(list_data2._index_search(str));
			}
		}
	}
	
}