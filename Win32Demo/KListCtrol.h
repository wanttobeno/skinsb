/*
** KListCtrl.h
** JieYang 2010-01-10 11:05
** KListCtrl Class, Written By Win32 API
** When You Use This Class, You Must pragma commctl32.lib First
*/

#ifndef __KLISTCTRL_H__
#define __KLISTCTRL_H__

#include <Windows.h>
#include <tchar.h>

typedef struct _lstele LSTELE;
typedef struct _lstele* PLSTELE;

struct _lstele {
	int _item;
	TCHAR _path[MAX_PATH];
	PLSTELE next;
};

class KListCtrol
{
public:
	KListCtrol();
	BOOL BindList(HWND hWnd);
	BOOL CreateList(HINSTANCE, HWND, POINT, SIZE);
	~KListCtrol();

	void CreateColumn(UINT _mask, int _cx, TCHAR* _text, int _col);
	void SetListItem(int _iItem, int _iSubItem, TCHAR* _text);
	void SetListItemText(int _iItem, int _iSubItem, TCHAR* _text);
	void AddListPath(LSTELE _ele);
	PLSTELE GetListPath();
	BOOL RemoveListItem();
private:
	HWND    m_hList;
	POINT   m_pt;
	SIZE    m_sz;
	PLSTELE p_head;
};

#endif