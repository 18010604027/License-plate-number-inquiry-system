// EditDlg.cpp: 实现文件
//

#include "pch.h"
#include "License-plate-number-inquiry-system.h"
#include "EditDlg.h"
#include "afxdialogex.h"


// EditDlg 对话框

IMPLEMENT_DYNAMIC(EditDlg, CDialogEx)

EditDlg::EditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_background = NULL;
	mFont = NULL;
}

EditDlg::~EditDlg()
{
	delete mFont;
}

void EditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EXIT2, exit_button);
	DDX_Control(pDX, IDC_BUTTON1, ok_button);
	DDX_Control(pDX, IDC_BUTTON2, cancel_button);
	DDX_Control(pDX, CAPTION2, caption);
	DDX_Control(pDX, IDC_EDIT2, id_edit);
	DDX_Control(pDX, IDC_EDIT3, name_edit);
	DDX_Control(pDX, IDC_EDIT4, site_edit);
	DDX_Control(pDX, IDC_EDIT5, phone_edit);
}

BEGIN_MESSAGE_MAP(EditDlg, CDialogEx)
	ON_BN_CLICKED(EXIT2, &EditDlg::OnBnClickedExit2)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &EditDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &EditDlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_STATIC2, &EditDlg::OnStnClickedStatic2)
	ON_STN_CLICKED(IDC_STATIC4, &EditDlg::OnStnClickedStatic4)
END_MESSAGE_MAP()

// EditDlg 消息处理程序

void EditDlg::OnBnClickedExit2()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

LRESULT EditDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 取得鼠标所在的窗口区域
	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	CPoint ptCur;
	CRect rect;
	GetCursorPos(&ptCur);
	GetWindowRect(&rect);
	/*用于拖动窗口*/
	if (CRect(rect.left, rect.top, rect.right, rect.bottom).PtInRect(ptCur))
	{
		return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
	}
	return nHitTest;
}

void EditDlg::OnPaint()
{
	CPaintDC m_dc(this);
	Graphics g(m_dc);
	g.Clear(Color(255, 255, 255, 255));
	g.DrawImage(m_background, 0, 0);
}

BOOL EditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetStyle();
	InitializedData();
	SetControl();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL EditDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPaintDC m_dc(this);

	//擦除采用双缓冲，防闪烁
	CPaintDC* Mdc = &m_dc;
	CDC dc;
	CBitmap bmp;
	CRect winrect;
	GetClientRect(&winrect);
	dc.CreateCompatibleDC(Mdc);
	bmp.CreateCompatibleBitmap(Mdc, winrect.Width(), winrect.Height());
	dc.SelectObject(&bmp);

	Graphics g(dc);
	g.Clear(Color(255, 255, 255, 255));
	g.DrawImage(m_background, 0, 0);
	Mdc->BitBlt(0, 0, winrect.Width(), winrect.Height(), &dc, 0, 0, SRCCOPY);
	return true;
}


HBRUSH EditDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == &exit_button || pWnd == &caption || pWnd->GetDlgCtrlID() == IDC_STATIC1 || pWnd->GetDlgCtrlID() == IDC_STATIC2 || pWnd->GetDlgCtrlID() == IDC_STATIC3 || pWnd->GetDlgCtrlID() == IDC_STATIC4)
	{
		pDC->SetBkMode(TRANSPARENT); //设置控件背景透明
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void EditDlg::SetControl()
{
	mFont = new CFont;
	mFont->CreateFont(18,			// 字体高度
		0,							// 字体宽度
		0,							// 字体倾斜角
		0,							// 字体倾斜角
		FW_EXTRALIGHT,				// 字体的粗细
		FALSE,						// 字体是否为斜体
		FALSE,						// 字体是否有下划线
		0,							// 字体是否有删除线
		ANSI_CHARSET,				// 字体使用的字符集
		OUT_DEFAULT_PRECIS,			// 指定如何选择合适的字体
		CLIP_DEFAULT_PRECIS,		// 确定裁剪的精度
		DEFAULT_QUALITY,			// 怎么样跟选择的字体相符合
		DEFAULT_PITCH | FF_SWISS,	// 间距标志和属性标志
		_T("楷体"));				// 字体的名称
	caption.SetFont(mFont, true);

	exit_button.SetBkColorClick(RGB(255, 0, 0));
	exit_button.SetBkGound(&m_background);
	ok_button.SetBkGound(&m_background);
	cancel_button.SetBkGound(&m_background);

	//ok_button.SetDiaphaneity(180, 220, 110);
	//ok_button.SetBkColor(RGB(64, 224, 208));
	//ok_button.SetBkColorClick(RGB(105, 105, 105));
	ok_button.SetRound(3);

	//cancel_button.SetDiaphaneity(180, 220, 110);
	//cancel_button.SetBkColor(RGB(64, 224, 208));
	//cancel_button.SetBkColorClick(RGB(105, 105, 105));
	cancel_button.SetRound(3);

	caption.SetWindowTextW(caption_txt);
	id_edit.SetWindowTextW(id);
	name_edit.SetWindowTextW(name);
	site_edit.SetWindowTextW(site);
	phone_edit.SetWindowTextW(phone);
}

void EditDlg::InitializedData()
{
	CRect winrect;
	GetWindowRect(&winrect);
	Image* imgBackground;
	imgBackground = Image::FromFile(L"Data\\bmp\\背景色2.bmp");
	m_background = new Bitmap(winrect.Width(), winrect.Height());
	Graphics g(m_background);
	g.Clear(Color(255, 255, 255, 255));
	g.DrawImage(imgBackground, 0, 0);
}

void EditDlg::SetStyle()
{
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);
}

void EditDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	id_edit.GetWindowTextW(id);
	name_edit.GetWindowTextW(name);
	site_edit.GetWindowTextW(site);
	phone_edit.GetWindowTextW(phone);
	OnOK();
}


void EditDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void EditDlg::OnStnClickedStatic2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void EditDlg::OnStnClickedStatic4()
{
	// TODO: 在此添加控件通知处理程序代码
}


void EditDlg::SetData(int i, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, i);
	id = va_arg(arg_ptr, LPCWSTR);
	name = va_arg(arg_ptr, LPCWSTR);
	site = va_arg(arg_ptr, LPCWSTR);
	phone = va_arg(arg_ptr, LPCWSTR);
	va_end(arg_ptr);
}
void EditDlg::SetCaption(CString caption)
{
	caption_txt = caption;
}

void EditDlg::GetData(CString& _id, CString& _name, CString& _site, CString& _phone)
{
	_id = id;
	_name = name;
	_site = site;
	_phone = phone;
}

