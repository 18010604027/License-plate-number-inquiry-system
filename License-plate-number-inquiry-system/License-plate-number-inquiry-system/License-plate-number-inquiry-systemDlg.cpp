
// License-plate-number-inquiry-systemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "License-plate-number-inquiry-system.h"
#include "License-plate-number-inquiry-systemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLicenseplatenumberinquirysystemDlg::CLicenseplatenumberinquirysystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LICENSEPLATENUMBERINQUIRYSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLicenseplatenumberinquirysystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, MIN, min_button);
	DDX_Control(pDX, EXIT, exit_button);
	DDX_Control(pDX, CAPTION, caption);
	DDX_Control(pDX, LIST, list);
	DDX_Control(pDX, MAX, max_button);
}

BEGIN_MESSAGE_MAP(CLicenseplatenumberinquirysystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(EXIT, &CLicenseplatenumberinquirysystemDlg::OnBnClickedExit)
	ON_BN_CLICKED(MIN, &CLicenseplatenumberinquirysystemDlg::OnBnClickedMin)
	ON_WM_NCHITTEST()
	ON_WM_SETCURSOR()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(MAX, &CLicenseplatenumberinquirysystemDlg::OnBnClickedMax)
END_MESSAGE_MAP()


// CLicenseplatenumberinquirysystemDlg 消息处理程序

BOOL CLicenseplatenumberinquirysystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	imgBackground.Load(L"bmp\\背景色.bmp");

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLicenseplatenumberinquirysystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLicenseplatenumberinquirysystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		//画图DC
		CPaintDC dc(this);
		imgBackground.BitBlt(dc, POINT{ 0,0 }, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLicenseplatenumberinquirysystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLicenseplatenumberinquirysystemDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void CLicenseplatenumberinquirysystemDlg::OnBnClickedMin()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_MINIMIZE);
}


LRESULT CLicenseplatenumberinquirysystemDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//当鼠标在客户区（控件区域不在内(这样也有好处就是在拖动图标时，不会导致窗口移动，当然也可另外设置）移动时通知窗口鼠标在标题栏

	// 取得鼠标所在的窗口区域
	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	CPoint ptCur;
	CRect rect;
	GetCursorPos(&ptCur);
	GetWindowRect(&rect);
	/*用于拖动窗口*/
	if (CRect(rect.left, rect.top + 5, rect.right - 128, rect.bottom - 5).PtInRect(ptCur))
	{
		return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
	}
	/*用于拉伸窗口大小*//*注意先判断四个角，再判定四边，否则四角会被屏蔽*/
	if (CRect(rect.left, rect.top, rect.left + 5, rect.top + 5).PtInRect(ptCur))/*左上*/
	{
		return HTTOPLEFT;
	}
	else if (CRect(rect.right - 5, rect.top, rect.right, rect.top + 5).PtInRect(ptCur))/*右上*/
	{
		return HTTOPRIGHT;
	}
	else if (CRect(rect.left, rect.bottom - 5, rect.left + 5, rect.bottom).PtInRect(ptCur))/*左下*/
	{
		return HTBOTTOMLEFT;
	}
	else if (CRect(rect.right - 5, rect.bottom - 5, rect.right, rect.bottom).PtInRect(ptCur))/*右下*/
	{
		return HTBOTTOMRIGHT;
	}
	else if (CRect(rect.left, rect.top, rect.left + 5, rect.bottom).PtInRect(ptCur))
	{
		return HTLEFT;
	}
	else if (CRect(rect.right - 5, rect.top, rect.right, rect.bottom).PtInRect(ptCur))
	{
		return HTRIGHT;
	}
	else if (CRect(rect.left, rect.top, rect.right - 128, rect.top + 5).PtInRect(ptCur)) // 128 Min,Max,Close
	{
		return HTTOP;
	}
	else if (CRect(rect.left, rect.bottom - 5, rect.right, rect.bottom).PtInRect(ptCur))
	{
		return HTBOTTOM;
	}
	return nHitTest;
}


BOOL CLicenseplatenumberinquirysystemDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint ptCur;
	CRect rect;
	/*获取屏幕大小*/
	int m_nCxFullScreen = GetSystemMetrics(SM_CXFULLSCREEN);
	int m_nCyFullScreen = GetSystemMetrics(SM_CYFULLSCREEN);
	/*获取鼠标权限和窗口权限*/
	GetCursorPos(&ptCur);
	GetWindowRect(&rect);

	/*窗口大小限制*/
	if (rect.Width() >= m_nCxFullScreen - 3 && rect.Height() >= m_nCyFullScreen - 3)
		return CDialog::OnSetCursor(pWnd, nHitTest, message);
	/*窗口大小改变&鼠标位置&光标改变*/
	if (CRect(rect.left, rect.top, rect.left + 5, rect.top + 5).PtInRect(ptCur) || CRect(rect.right - 5, rect.bottom - 5, rect.right, rect.bottom).PtInRect(ptCur))
	{
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));/*注意IDC_SIZENWSE中，最后的NW和SE是由北到东和由南到西，指明鼠标变化类型*/
		return 0;
	}
	else if (CRect(rect.left, rect.bottom - 5, rect.left + 5, rect.bottom).PtInRect(ptCur) || CRect(rect.right - 5, rect.top, rect.right, rect.top + 5).PtInRect(ptCur))
	{
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
		return 0;
	}
	else if (CRect(rect.left, rect.top, rect.right - 128, rect.top + 5).PtInRect(ptCur) || CRect(rect.left, rect.bottom - 5, rect.right, rect.bottom).PtInRect(ptCur))
	{
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
		return 0;
	}
	else if (CRect(rect.left, rect.top, rect.left + 5, rect.bottom).PtInRect(ptCur) || CRect(rect.right - 5, rect.top, rect.right, rect.bottom).PtInRect(ptCur))
	{
		SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
		return 0;
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CLicenseplatenumberinquirysystemDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*鼠标按下后拖动改变窗口大小*/
	switch (nHitTest)
	{
	case HTTOP:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
		return;
	case HTBOTTOM:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		return;
	case HTLEFT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
		return;
	case HTRIGHT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		return;
	case HTTOPLEFT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
		return;
	case HTTOPRIGHT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
		return;
	case HTBOTTOMLEFT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
		return;
	case HTBOTTOMRIGHT:
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
		return;
	default:
		CDialogEx::OnNcLButtonDown(nHitTest, point);
	}
}


HBRUSH CLicenseplatenumberinquirysystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == &min_button|| pWnd == &exit_button || pWnd == &caption)
	{
		pDC->SetBkMode(TRANSPARENT); //设置控件背景透明
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CLicenseplatenumberinquirysystemDlg::OnBnClickedMax()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_MAXIMIZE);
}
