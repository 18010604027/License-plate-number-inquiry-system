
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
	bool max = false;//窗口最大化
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedMin();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMax();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedSearch();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeCombo1();
	DECLARE_MESSAGE_MAP()
	void OnSearchEditDown();
protected:
	CMyButton min_button;
	CMyButton exit_button;
	CMyButton search_button;
	CStatic caption;
	CMyList list;
	CMyButton max_button;
	CEdit search_edit;
	CComboBox combo;
	CComboBox combo_province;
protected:
	CRect m_rect;//窗口大小
	Image* imgBackground;//背景
	CFont* mFont;//字体(标题用)
	bool value_province = false;//显示省份列表
protected:
	void AdjustSize(LPRECT pRect);//调整窗口控件位置
	void RefreshAll();//全体刷新
	void SetControl();//设置控件
	void InitializedData();//初始化数据	
};
