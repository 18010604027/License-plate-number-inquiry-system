
// License-plate-number-inquiry-systemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "License-plate-number-inquiry-system.h"
#include "License-plate-number-inquiry-systemDlg.h"
#include "afxdialogex.h"
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//用于装载和卸载
Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
ULONG_PTR m_uGdiplusToken;

CLicenseplatenumberinquirysystemDlg::CLicenseplatenumberinquirysystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LICENSEPLATENUMBERINQUIRYSYSTEM_DIALOG, pParent)
{
	//加载GDI+
	Gdiplus::GdiplusStartup(&m_uGdiplusToken, &m_GdiplusStarupInput, nullptr);
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
	DDX_Control(pDX, IDC_EDIT1, search_edit);
	DDX_Control(pDX, SEARCH, search_button);
	DDX_Control(pDX, IDC_COMBO1, combo);
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
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_MOVE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(SEARCH, &CLicenseplatenumberinquirysystemDlg::OnBnClickedSearch)
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
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

	// TODO: 在此添加额外的初始化代码
	InitializedData();
	SetControl();
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
		GetWindowRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC m_dc(this);
		Graphics g(m_dc);
		g.Clear(Color(255, 255, 255, 255));
		g.DrawImage(_background, 0, 0);
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
	if (CRect(rect.left + 5, rect.top + 5, rect.right - 5, rect.bottom - 5).PtInRect(ptCur))
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
	if (pWnd == &min_button || pWnd == &exit_button || pWnd == &caption || pWnd == &list || pWnd == &search_button)
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
	if (max)
	{
		ShowWindow(SW_NORMAL);
		max = false;
		max_button.SetWindowTextW(L"🗖");
		CRect winrect;
		GetWindowRect(&winrect);
		AdjustSize(winrect);
		LoadBackgound(imgBackground, winrect);
		InvalidateRect(NULL);
	}
	else
	{
		GetWindowRect(m_rect);
		ShowWindow(SW_MAXIMIZE);
		max = true;
		max_button.SetWindowTextW(L"🗗");
		CRect winrect;
		GetWindowRect(&winrect);
		AdjustSize(winrect);
		LoadBackgound(imgBackground, winrect);
		InvalidateRect(NULL);
	}
}


void CLicenseplatenumberinquirysystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	if (refresh)
	{
		CRect winrect;
		GetWindowRect(&winrect);
		AdjustSize(winrect);
		LoadBackgound(imgBackground, winrect);
		RefreshAll();
		refresh = false;
	}
}


void CLicenseplatenumberinquirysystemDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);
	// TODO: 在此处添加消息处理程序代码
	refresh = true;
}

void CLicenseplatenumberinquirysystemDlg::AdjustSize(LPRECT pRect)
{
	CRect rect;
	//列表
	rect.left = 20;
	rect.right = (pRect->right - pRect->left) - 10;
	rect.top = 80;
	rect.bottom = (pRect->bottom - pRect->top) - 10;
	list.MoveWindow(rect, false);//false使它不直接刷新

	//下拉列表
	rect.right = rect.left + 110;
	rect.top = rect.top - 30;
	rect.bottom = rect.top + 25;
	combo.MoveWindow(rect, false);

	//搜索编辑框
	rect.left = rect.right + 10;
	rect.right = rect.left + 250;
	search_edit.MoveWindow(rect, false);

	//搜索按钮
	rect.left = rect.right + 20;
	rect.right = rect.left + 60;
	search_button.MoveWindow(rect, false);

	//关闭按钮
	rect.right = pRect->right - pRect->left;
	rect.top = 0;
	rect.left = rect.right - 43;
	rect.bottom = rect.top + 24;
	exit_button.MoveWindow(rect, false);

	//最大化按钮
	rect.right = rect.right - 44;
	rect.left = rect.right - 44;
	max_button.MoveWindow(rect, false);

	//最小化按钮
	rect.right = rect.right - 44;
	rect.left = rect.right - 44;
	min_button.MoveWindow(rect, false);
}

void CLicenseplatenumberinquirysystemDlg::RefreshAll()
{
	InvalidateRect(NULL);
}

void CLicenseplatenumberinquirysystemDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	if (max)
	{
		max = false;
		max_button.SetWindowTextW(L"🗖");
		CRect winrect;
		GetWindowRect(&winrect);
		AdjustSize(winrect);
		LoadBackgound(imgBackground, winrect);
		InvalidateRect(NULL);
	}
}


BOOL CLicenseplatenumberinquirysystemDlg::OnEraseBkgnd(CDC* pDC)
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
	g.DrawImage(_background, 0, 0);
	Mdc->BitBlt(0, 0, winrect.Width(), winrect.Height(), &dc, 0, 0, SRCCOPY);
	return true;
}

void CLicenseplatenumberinquirysystemDlg::SetControl()
{
	search_button.SetDiaphaneity(180, 220, 110);
	search_button.SetBkColor(RGB(128, 128, 128));
	search_button.SetBkColorClick(RGB(105, 105, 105));
	search_button.SetRound(3);
	min_button.SetBkColorClick(RGB(0, 122, 205));
	max_button.SetBkColorClick(RGB(0, 122, 205));
	exit_button.SetBkColorClick(RGB(255, 0, 0));

	combo.AddString(L"一般查询");
	combo.AddString(L"正则表达式查询");
	combo.SetCurSel(0);

	list.AddProverty(L"车牌号");
	list.AddProverty(L"姓名");
	list.AddProverty(L"地址");
	list.AddProverty(L"联系方式");

	list.AddItem(4, L"123321", L"刘", L"天堂", L"1243213121");
}

void CLicenseplatenumberinquirysystemDlg::InitializedData()
{
	//初始化窗口控件位置
	CRect pRect;
	ifstream infile;
	infile.open("Data\\windows", ios::in | ios::binary);
	bool max_ = false;
	if (infile)
	{
		int len = sizeof(pRect.top);
		infile.read((char*)&max_, sizeof(bool));//临时存放max，防止修改窗口大小时刷新
		infile.read((char*)&pRect.top, len);
		infile.read((char*)&pRect.bottom, len);
		infile.read((char*)&pRect.left, len);
		infile.read((char*)&pRect.right, len);
		MoveWindow(pRect, true);
	}
	else
	{
		GetClientRect(pRect);
	}
	imgBackground = Image::FromFile(L"Data\\bmp\\背景色.bmp");
	if (max_)
	{
		m_rect = pRect;
		ShowWindow(SW_MAXIMIZE);
		max_button.SetWindowTextW(L"🗗");
		max = max_;
	}
	CRect winrect;
	GetWindowRect(&winrect);
	LoadBackgound(imgBackground, winrect);
	AdjustSize(winrect);
	if (max_)
	{
		RefreshAll();
	}
}

void CLicenseplatenumberinquirysystemDlg::OnBnClickedSearch()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CLicenseplatenumberinquirysystemDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x = 500;   //x宽度  
	lpMMI->ptMinTrackSize.y = 200;   //y高度 
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CLicenseplatenumberinquirysystemDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	CRect pRect;
	ofstream outfile;
	outfile.open("Data\\windows", std::ios::binary);
	if (max)
	{
		pRect = m_rect;
	}
	else
	{
		GetWindowRect(pRect);
	}

	if (outfile)
	{
		const int len = sizeof(int);
		outfile.write((char*)&max, sizeof(bool));
		outfile.write((char*)&pRect.top, len);
		outfile.write((char*)&pRect.bottom, len);
		outfile.write((char*)&pRect.left, len);
		outfile.write((char*)&pRect.right, len);
	}
	outfile.close();
}




BOOL CLicenseplatenumberinquirysystemDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus() == &search_edit)
		{
			OnSearchEditDown();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CLicenseplatenumberinquirysystemDlg::OnSearchEditDown()
{

}