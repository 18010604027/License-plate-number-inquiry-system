
// License-plate-number-inquiry-systemDlg.h: 头文件
//

#pragma once


// CLicenseplatenumberinquirysystemDlg 对话框
class CLicenseplatenumberinquirysystemDlg : public CDialogEx
{
// 构造
public:
	CLicenseplatenumberinquirysystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LICENSEPLATENUMBERINQUIRYSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	bool refresh = false;//是否进行位置刷新
	bool max=false;//窗口最大化
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMyButton min_button;
	CMyButton exit_button;
	Image* imgBackground;
	CStatic caption;
	CMyList list;
	CMyButton max_button;
	CEdit search_edit;
public:
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedMin();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	
	afx_msg void OnBnClickedMax();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
public:
	void AdjustSize(LPRECT pRect);//调整窗口控件位置
	void RefreshAll();//全体刷新
	afx_msg void OnMove(int x, int y);
};
