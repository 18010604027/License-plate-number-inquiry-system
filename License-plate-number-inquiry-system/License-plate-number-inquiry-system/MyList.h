#pragma once
using namespace Gdiplus;

#define WM_MENU_ADD 11990
#define WM_MENU_EDIT 11991
#define WM_MENU_DELETE 11992
class CMyList :public CWnd
{
	DECLARE_DYNAMIC(CMyList)
public:
	CMyList();
	virtual ~CMyList();
	void AddItem(int i, ...);//�����б�ѡ��
	void AddProverty(CString Title);//�����б�����
public://��Ϣ��
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()//��Ϣ�ؼ�
protected://�б�����
	CString titles[10]; int title_len = 0;//�б�����⣨�б����ԣ�
	CString list_space[10][10]; int space_len = 0;//�б����
protected://�б�״̬
	int option_num;//��ҳ��ѡ��
	int menu_num;//�˵���ѡ����
	int now_page;//��ǰҳ��
	bool mouse_focus;//��꽹��
	bool l_click;//����������
	bool menu_focus;//�˵�����
	bool initialization;//�Ƿ��ѳ�ʼ��
	bool draw_dc;//�Ƿ�滭����
	bool refresh = false;//�Ƿ����λ��ˢ��
protected://�б�����
	int total_page;//��ҳ��
	int page_options;//һҳѡ����
	const int box_height = 30;//ѡ��߶�	
	CRect crect;//�ؼ�����
	Rect rect;//�ؼ�����
	Image* img_background;//����
protected://ͼ��
	CDC dc; CBitmap dc_bmp; //����
	Bitmap* layer_background;//����ͼ��
	Bitmap* layer_text;//����ͼ��
	Bitmap* layer_select_box;//ѡ��ͼ��
	Bitmap* layer_select_box_click;//ѡ��ͼ�㣨������
	Bitmap* layer_menu;//�˵�ͼ��
protected://�滭����
	void Initialize();//��ʼ������
	void Reinitialize();//���ò���
	void DrawBackground();//������
	void DrawTexts();//������
	void DrawSelectBox();//��ѡ��
	void Draw();//���
	void Drawrefresh();//ˢ��
protected://�б���
	void ChangePage(bool next);//�ı�ҳ��
	void MenuChange();//�༭ѡ��
};