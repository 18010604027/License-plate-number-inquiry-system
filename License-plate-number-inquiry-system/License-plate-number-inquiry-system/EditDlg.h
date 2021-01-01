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
	CFont* mFont;

	CString caption_txt;
	CString id;
	CString name;
	CString site;
	CString phone;
protected:
	CMyButton exit_button;
	CMyButton ok_button;
	CMyButton cancel_button;
	CStatic caption;
	CEdit id_edit;
	CEdit name_edit;
	CEdit site_edit;
	CEdit phone_edit;
protected:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedExit2();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnStnClickedStatic4();
	DECLARE_MESSAGE_MAP()
protected:
	void SetControl();//设置控件
	void InitializedData();//初始化数据	
	void SetStyle();//设置窗口风格	
public:
	void SetData(int i, ...);//设置数据
	void SetCaption(CString caption);//设置标题
	void GetData(CString& _id, CString& _name, CString& _site, CString& _phone);//获取修改数据
};
