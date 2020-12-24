
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

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMyButton min_button;
	CMyButton exit_button;
	CImage imgBackground;
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedMin();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic caption;
	CMyList list;
	CMyButton max_button;
	afx_msg void OnBnClickedMax();
};
