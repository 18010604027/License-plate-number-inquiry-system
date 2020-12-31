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
	void AddItem(int i, ...);//增加列表选项
	void AddProverty(CString Title);//增加列表属性
public://消息区
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
	DECLARE_MESSAGE_MAP()//消息必加
protected://列表内容
	CString titles[10]; int title_len = 0;//列表各标题（列表属性）
	CString list_space[10][10]; int space_len = 0;//列表各项
protected://列表状态
	int option_num;//该页被选项
	int menu_num;//菜单被选择项
	int now_page;//当前页数
	bool mouse_focus;//鼠标焦点
	bool l_click;//鼠标左键按下
	bool menu_focus;//菜单焦点
	bool initialization;//是否已初始化
	bool draw_dc;//是否绘画缓存
	bool refresh = false;//是否进行位置刷新
protected://列表属性
	int total_page;//总页数
	int page_options;//一页选项数
	const int box_height = 30;//选框高度	
	CRect crect;//控件矩形
	Rect rect;//控件矩形
	Image* img_background;//背景
protected://图层
	CDC dc; CBitmap dc_bmp; //缓存
	Bitmap* layer_background;//背景图层
	Bitmap* layer_text;//文字图层
	Bitmap* layer_select_box;//选框图层
	Bitmap* layer_select_box_click;//选框图层（单击）
	Bitmap* layer_menu;//菜单图层
protected://绘画功能
	void Initialize();//初始化参数
	void Reinitialize();//重置参数
	void DrawBackground();//画背景
	void DrawTexts();//画文字
	void DrawSelectBox();//画选框
	void Draw();//结合
	void Drawrefresh();//刷新
protected://列表功能
	void ChangePage(bool next);//改变页数
	void MenuChange();//编辑选项
};