
// SkinSbDemoDlg.h : 头文件
//

#pragma once
#include "virtuallist.h"
#include <vector>
#include "afxwin.h"

// CSkinSbDemoDlg 对话框
class CSkinSbDemoDlg : public CDialog
{
// 构造
public:
	CSkinSbDemoDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CSkinSbDemoDlg();
// 对话框数据
	enum { IDD = IDD_SKINSBDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	std::vector<ListData*> m_listData;
// 实现
protected:
	HICON m_hIcon;
	CBitmap m_bmScroll;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CVirtualList m_list;
	afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);
};
