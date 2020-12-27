#pragma once


// EditDlg 对话框

class EditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EditDlg)

public:
	EditDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~EditDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	Bitmap* m_background;
	DECLARE_MESSAGE_MAP()
public:	
	CMyButton exit_button;
	CMyButton ok_button;
	CMyButton cancel_button;
	CStatic caption;
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();	
	afx_msg void OnBnClickedExit2();
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
public:
	void SetControl();//设置控件
	void InitializedData();//初始化数据	
	void SetStyle();//设置窗口风格
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
