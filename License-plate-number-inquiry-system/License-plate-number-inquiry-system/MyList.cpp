#include "pch.h"
#include "MyList.h"

IMPLEMENT_DYNAMIC(CMyList, CWnd)//�����ؼ�
CMyList::CMyList()
{
	initialization = false;//�Ƿ��ѳ�ʼ��
	draw_dc = true;//�Ƿ���Ҫ�滭����
	option_num = -1;//��ѡ����
	menu_num = -1;//�˵�����
	mouse_focus = false;//�Ƿ�����꽹��
	l_click = false;//�������Ƿ񱻰���

	space_len = 0;//��ǰ������ݳ���

	now_page = 1;//��ǰҳ��
	total_page = 2;//��ҳ��
	page_options = 5;//ÿҳѡ����

	layer_background = NULL;//����ͼ��
	layer_text = NULL;//����ͼ��
	layer_select_box = NULL;//ѡ��ͼ��
	layer_select_box_click = NULL;//ѡ��ͼ�㣨������
	layer_menu = NULL;//�˵�ͼ��

	box_height = 30;//ѡ��߶�
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


void CMyList::AddItem(int i, ...)//�����б�ѡ�� 
{
	LPCWSTR str = 0;
	va_list arg_ptr;
	va_start(arg_ptr, i);
	int j = 0;
	for (int j = 0; j < i; j++)
	{
		str = va_arg(arg_ptr, LPCWSTR);
		list_space[space_len][j] = str;
	}
	space_len++;
	va_end(arg_ptr);
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
		tme.dwHoverTime = 13;//HOVER_DEFAULT// ������˲��������޷�����mouseHover
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

void CMyList::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();//��ȡ����
	l_click = true;
	Draw();
	Drawrefresh();
}

void CMyList::OnLButtonUp(UINT nFlags, CPoint point)
{
	l_click = false;
	Draw();
	Drawrefresh();
	if (option_num != -1 && option_num < page_options && option_num + page_options * (now_page - 1) < space_len)
	{
		menu_num = option_num;
		MenuChange();
	}
}

void CMyList::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();//��ȡ����
	menu_num = option_num;
	if (option_num != -1 && option_num < page_options && option_num + page_options * (now_page - 1) < space_len)
	{
		RECT rect2;
		GetWindowRect(&rect2);

		CMyMenu menu;
		menu.CreatePopupMenu();
		menu.RemoveMenuBorder(GetModuleHandle(NULL));
		menu.AppendMenu(MF_STRING, WM_MENU_ADD, L"���");
		menu.AppendMenu(MF_STRING, WM_MENU_EDIT, L"�޸�");
		menu.AppendMenu(MF_STRING, WM_MENU_DELETE, L"ɾ��");
		menu.TrackPopupMenu(TPM_LEFTALIGN, rect2.left + point.x - 10, rect2.top + point.y - 10, this); //ȷ������ʽ�˵���λ��
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu(); //��Դ����
	}
	else
	{
		RECT rect2;
		GetWindowRect(&rect2);

		CMyMenu menu;
		menu.CreatePopupMenu();
		menu.RemoveMenuBorder(GetModuleHandle(NULL));
		menu.AppendMenu(MF_STRING, WM_MENU_ADD, L"���");
		menu.TrackPopupMenu(TPM_LEFTALIGN, rect2.left + point.x - 10, rect2.top + point.y - 10, this); //ȷ������ʽ�˵���λ��
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu(); //��Դ����
	}
}

void CMyList::OnSize(UINT nType, int cx, int cy)
{
	//������С����
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

void CMyList::Initialize()//��ʼ��
{
	/*��ʼ��λ�ò���*/
	GetClientRect(&crect);
	rect.X = crect.top;
	rect.Y = crect.left;
	rect.Width = crect.Width();
	rect.Height = crect.Height();

	/*��ʼ��ͼ�㡢����*/
	CDC* pdc = GetDC();

	//��ʼ������
	dc.CreateCompatibleDC(pdc);
	dc_bmp.CreateCompatibleBitmap(GetDC(), crect.Width(), crect.Height());
	dc.SelectObject(&dc_bmp);

	//��ʼ������ͼ��	
	layer_background = new Bitmap(rect.Width, rect.Height);

	//��ʼ������ͼ��	
	layer_text = new Bitmap(rect.Width, rect.Height);

	//��ʼ��ѡ��ͼ��	
	layer_select_box = new Bitmap(rect.Width, int(box_height));
	layer_select_box_click = new Bitmap(rect.Width, int(box_height));

	//��ʼ��ѡ��ͼ��˵�	
	layer_menu = new Bitmap(50, 100);

	/*����ͼ��*/
	DrawBackground();
	DrawSelectBox();
}

void CMyList::Reinitialize()//���ô�С����
{
	/*����λ�ò���*/
	GetClientRect(&crect);
	rect.X = crect.top;
	rect.Y = crect.left;
	rect.Width = crect.Width();
	rect.Height = crect.Height();
	/*����ͼ�㡢����*/
	dc_bmp.Detach();
	dc_bmp.CreateCompatibleBitmap(GetDC(), crect.Width(), crect.Height());
	dc.SelectObject(&dc_bmp);

	//���ñ���ͼ��
	delete layer_background;
	layer_background = new Bitmap(rect.Width, rect.Height);

	//��������ͼ��	
	delete layer_text;
	layer_text = new Bitmap(rect.Width, rect.Height);

	//����ѡ��ͼ��
	delete layer_select_box;
	delete layer_select_box_click;
	layer_select_box = new Bitmap(rect.Width, (int)box_height);
	layer_select_box_click = new Bitmap(rect.Width, (int)box_height);

	/*����ͼ��*/
	DrawBackground();
	DrawSelectBox();
}

void CMyList::DrawBackground()
{
	//��ɫ���
	Gdiplus::Graphics g(layer_background);
	SolidBrush Brush(Color(255, 255, 255, 255));
	g.FillRectangle(&Brush, rect);
	//���Ʊ���
	CPoint point(0, 0);
	CLicenseplatenumberinquirysystemDlg* p = (CLicenseplatenumberinquirysystemDlg*)GetParent();
	MapWindowPoints(p, &point, 1);
	g.DrawImage(_background, -point.x, -point.y);
}

void CMyList::DrawTexts()//������
{
	//����ƽ̨
	Gdiplus::Graphics g(layer_text);

	//���ԭ����(��������)
	g.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	Gdiplus::SolidBrush brush(Color(0, 0, 0, 0));
	g.FillRectangle(&brush, rect);

	//���ø�ʽ
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	Gdiplus::StringFormat font_attribute;
	font_attribute.SetAlignment(Gdiplus::StringAlignmentNear);
	font_attribute.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	Gdiplus::Font myFont(L"����", 11);                  //��������
	Gdiplus::SolidBrush blackBrush(Color(255, 255, 255, 255));

	//��ӡ����
	Gdiplus::REAL len = (Gdiplus::REAL)rect.Width / title_len;
	for (int i = 0; i < title_len; i++)
	{
		g.DrawString(titles[i], titles[i].GetLength(), &myFont, Gdiplus::RectF(i * len, 0, len, box_height), &font_attribute, &blackBrush);
	}

	//��ӡҳ��
	font_attribute.SetAlignment(Gdiplus::StringAlignmentCenter);
	CString prin_page;
	prin_page.Format(L"%d/%d", now_page, total_page);
	g.DrawString(prin_page, prin_page.GetLength(), &myFont, Gdiplus::RectF(2, (Gdiplus::REAL)(rect.Height - box_height), (Gdiplus::REAL)rect.Width, box_height), &font_attribute, &blackBrush);

	//��ӡ����
	Gdiplus::Font myFont2(L"����", 10);
	font_attribute.SetAlignment(Gdiplus::StringAlignmentNear);
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);//����ģʽ
	for (int i = 0; i + page_options * (now_page - 1) < space_len && i < page_options; i++)
	{
		CString str;
		for (int j = 0; j < title_len; j++)
		{
			g.DrawString(list_space[i][j], list_space[i][j].GetLength(), &myFont2, RectF(2 + j * len, box_height * (i + 1) + 0, len, box_height), &font_attribute, &blackBrush);
		}
	}


}

void CMyList::DrawSelectBox()
{
	/*һ��ѡ���*/
	Gdiplus::Graphics g(layer_select_box);
	//���ø���ģʽ
	g.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//������
	Gdiplus::SolidBrush brush(Color(20, 127, 255, 170));
	g.FillRectangle(&brush, RectF(0, 0, (Gdiplus::REAL)rect.Width, box_height));

	/*����ʱѡ���*/
	Gdiplus::Graphics g2(layer_select_box_click);
	//���ø���ģʽ
	g2.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//������
	Gdiplus::SolidBrush brush2(Color(80, 127, 255, 170));
	g2.FillRectangle(&brush2, RectF(0, 0, (Gdiplus::REAL)rect.Width, box_height));
}

void CMyList::Draw()
{
	draw_dc = false;
	//��һ�γ�ʼ��
	if (!initialization)
	{
		Initialize();
		initialization = true;
	}
	//��ʾ
	Gdiplus::Graphics g(dc);
	//���ԭͼ
	g.Clear(Color(0, 255, 255, 255));

	//������
	g.DrawImage(layer_background, 0, 0);
	//��ѡ��
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
	//������
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
void CMyList::MenuChange()
{
	EditDlg dlg;
	dlg.SetCaption(L"�༭");
	dlg.SetData(4,
		list_space[menu_num][0],
		list_space[menu_num][1],
		list_space[menu_num][2],
		list_space[menu_num][3]);
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetData(list_space[menu_num][0],
			list_space[menu_num][1],
			list_space[menu_num][2],
			list_space[menu_num][3]);
		DrawTexts();
		Draw();
		Drawrefresh();
	}
}
BOOL CMyList::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	UINT uMsg = LOWORD(wParam);
	//���ղ˵���Ϣ
	if (uMsg == WM_MENU_ADD)
	{
		EditDlg dlg;
		dlg.SetCaption(L"���");
		if (dlg.DoModal() == IDOK)
		{
			//list_data.insert()
			/*dlg.GetData(list_space[menu_num][0],
				list_space[menu_num][1],
				list_space[menu_num][2],
				list_space[menu_num][3]);*/
			DrawTexts();
			Draw();
			Drawrefresh();
		}
	}
	if (uMsg == WM_MENU_EDIT)
	{
		MenuChange();
	}
	if (uMsg == WM_MENU_DELETE)
	{

	}

	return CWnd::OnCommand(wParam, lParam);
}