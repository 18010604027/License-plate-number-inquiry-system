#pragma once

class MENUDATA
{
public:
	MENUDATA() { menuIconNormal = -1; menuIconSelected = -1; };
	wchar_t menuText[32] = {};
	UINT menuIconNormal;
	UINT menuIconSelected;
};

class CMyMenu :public CMenu
{
	DECLARE_DYNAMIC(CMyMenu)
public:
	CMyMenu();
	virtual ~CMyMenu();

	BOOL AppendMenuW(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem = NULL);
	void RemoveMenuBorder(HINSTANCE hInst, BOOL bRemove = TRUE);
protected:

	BOOL m_bRemoveBorder;//ฑ๊สถ
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};