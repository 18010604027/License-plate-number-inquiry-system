#pragma once
using namespace Gdiplus;

class CMyButton :public CButton
{
	DECLARE_DYNAMIC(CMyButton)
public:
	CMyButton();
	virtual ~CMyButton();
	void SetBkColor(COLORREF color);
	void SetBkColorClick(COLORREF color);
	void SetTextColor(COLORREF color);
	void SetDiaphaneity(int Over,int Down,int Disable);
	void SetRound(int Round);
	void SetBkGound(Bitmap** BkGound);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnable(BOOL bEnable);
protected:
	bool m_bOver;
	bool m_bDown;
	bool m_bDisable;
	bool m_bTracking;
	COLORREF m_bkColor;
	COLORREF m_bkColor_click;
	COLORREF m_textColor;	
	int bOver;
	int bDown;
	int bDisable;
	int round;

	Bitmap** bkGound;//±³¾°Í¼²ã
protected:
	void ButtonInit();
	void DrawButton();
	void DrawButton(HDC hDestDC);
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
};