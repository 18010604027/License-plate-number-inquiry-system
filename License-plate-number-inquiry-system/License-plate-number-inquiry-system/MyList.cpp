#include "pch.h"
#include "MyList.h"

IMPLEMENT_DYNAMIC(CMyList, CWnd)//�����ؼ�
CMyList::CMyList()
{
	initialization = false;
	draw_dc = true;
	img_background = Image::FromFile(L"bmp\\����ɫ.bmp");
	option_num = -1;
	mouse_focus = false;
	l_click = false;

	title = L"����   ���ƺ�";
	list_space[0] = L"�޵�   111111";
	list_space[1] = L"��֮   222222";
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


void CMyList::AddItem()//�����б�ѡ�� 
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
		tme.dwHoverTime = 13;//HOVER_DEFAULT// ������˲��������޷�����mouseHover
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
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"�޸�");
		menu.AppendMenu(MF_STRING, WM_DESTROY, L"ɾ��");
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
	layer_select_box = new Bitmap(rect.Width, box_height);
	layer_select_box_click = new Bitmap(rect.Width, box_height);

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
	layer_select_box = new Bitmap(rect.Width, box_height);
	layer_select_box_click = new Bitmap(rect.Width, box_height);

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
	g.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	g.SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);//����ģʽ
	Gdiplus::StringFormat font_attribute;
	font_attribute.SetAlignment(Gdiplus::StringAlignmentNear);
	font_attribute.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	Gdiplus::Font myFont(L"����", 9);                  //��������
	Gdiplus::SolidBrush blackBrush(Color(255, 255, 255, 255));

	//��ӡ����
	g.DrawString(title, title.GetLength(), &myFont, RectF(2, 0, rect.Width, box_height), &font_attribute, &blackBrush);
	for (int i = 0; i + page_options * (now_page - 1) < space_len && i < page_options; i++)
	{
		g.DrawString(list_space[i], list_space[i].GetLength(), &myFont, RectF(2, box_height * (i + 1) + 0, rect.Width, box_height), &font_attribute, &blackBrush);
	}

	//��ӡҳ��
	font_attribute.SetAlignment(Gdiplus::StringAlignmentCenter);
	CString prin_page;
	prin_page.Format(L"%d/%d", now_page, total_page);
	g.DrawString(prin_page, prin_page.GetLength(), &myFont, RectF(2, rect.Height - box_height, rect.Width, box_height), &font_attribute, &blackBrush);
}

void CMyList::DrawSelectBox()
{
	/*һ��ѡ���*/
	Gdiplus::Graphics g(layer_select_box);
	//���ø���ģʽ
	g.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//������
	Gdiplus::SolidBrush brush(Color(20, 127, 255, 170));
	g.FillRectangle(&brush, Rect(0, 0, rect.Width, box_height));

	/*����ʱѡ���*/
	Gdiplus::Graphics g2(layer_select_box_click);
	//���ø���ģʽ
	g2.SetCompositingMode(Gdiplus::CompositingModeSourceCopy);
	//������
	Gdiplus::SolidBrush brush2(Color(80, 127, 255, 170));
	g2.FillRectangle(&brush2, Rect(0, 0, rect.Width, box_height));
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
			g.DrawImage(layer_select_box_click, 0, (option_num + 1) * box_height);
		}
		else
		{
			g.DrawImage(layer_select_box, 0, (option_num + 1) * box_height);
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