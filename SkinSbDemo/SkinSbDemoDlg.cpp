
// SkinSbDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SkinSbDemo.h"
#include "SkinSbDemoDlg.h"

#include "resource.h"
#include <algorithm>
#include "../skinsb/skinsb.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSkinSbDemoDlg 对话框




CSkinSbDemoDlg::CSkinSbDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkinSbDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CleanVector(ListData* pListData)
{
	delete pListData;
	pListData = NULL;
}

CSkinSbDemoDlg::~CSkinSbDemoDlg()
{

	for_each(m_listData.begin(),m_listData.end(),CleanVector);
	m_listData.clear();
}


void CSkinSbDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CSkinSbDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, &CSkinSbDemoDlg::OnLvnGetdispinfoList1)
END_MESSAGE_MAP()


// CSkinSbDemoDlg 消息处理程序

BOOL CSkinSbDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	char szTitle[MAX_PATH] = {0};
	GetWindowTextA(m_hWnd,szTitle,MAX_PATH);
	strcat(szTitle," ");
	strcat(szTitle,__TIMESTAMP__);
	SetWindowTextA(m_hWnd,szTitle);

	m_bmScroll.LoadBitmap(IDB_SCROLL);
	SkinSB_Init(m_list, m_bmScroll);

	for (int i=0 ; i <20 ;i++)
	{
		m_list.InsertColumn(i,_T("ID"),LVCFMT_CENTER,80);
	}
	
	for (int j=0; j< 100000; j++)
	{
		ListData* pData = new ListData;
		pData->nOffset = j;
		m_listData.push_back(pData);
	}
	m_list.SetItemCount(m_listData.size());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSkinSbDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSkinSbDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSkinSbDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSkinSbDemoDlg::OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_list.InsertItemDataCallBack(pNMHDR,m_listData);
	*pResult = 0;
}
