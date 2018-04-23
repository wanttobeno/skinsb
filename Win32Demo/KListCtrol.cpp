/*
** KListCtrl.cpp
** JieYang 2010-01-10 11:05
** KListCtrl Class, Written By Win32 API
** When You Use This Class, You Must pragma commctl32.lib First
*/

#include "KListCtrol.h"

#include <CommCtrl.h>

KListCtrol::KListCtrol()
{
	m_hList = NULL;
}

BOOL KListCtrol::BindList(HWND hWndList)
{
	if (m_hList)
	{
		return FALSE;
	}
	m_hList = hWndList;
	return TRUE;
}

BOOL KListCtrol::CreateList(HINSTANCE _hInst, HWND _hParent, POINT _pt, SIZE _sz)
{
	InitCommonControls();

	m_pt = _pt;
	m_sz = _sz;
	p_head = NULL;
	m_hList = ::CreateWindow(L"syslistview32", L"", WS_VISIBLE | WS_CHILD | WS_BORDER |
		LVS_REPORT | LVS_SHOWSELALWAYS, m_pt.x, m_pt.y,
		m_sz.cx, m_sz.cy, _hParent, NULL, _hInst, NULL);
	if (!m_hList)
	{
		::MessageBox(NULL, TEXT("CreateWindow Error: KListCtrl.cpp 22"), TEXT("Error"), MB_OK);
		return FALSE;
	} 
	return TRUE;
}

KListCtrol::~KListCtrol()
{}

void KListCtrol::CreateColumn(UINT _mask, int _cx, TCHAR *_text, int _col)
{
	LVCOLUMN _lvcol;
	memset(&_lvcol, 0, sizeof(LVCOLUMN));
	_lvcol.mask = _mask;
	_lvcol.pszText = _text;
	_lvcol.cx = _cx;
	::SendMessage(m_hList, LVM_INSERTCOLUMN, _col, (LPARAM)&_lvcol);
}

void KListCtrol::SetListItem(int _iItem, int _iSubItem, TCHAR *_text)
{
	LVITEM _lvitem;
	memset(&_lvitem, 0, sizeof(LVITEM));
	_lvitem.mask = LVIF_TEXT;
	_lvitem.cchTextMax = MAX_PATH;
	_lvitem.iItem = _iItem;
	_lvitem.iSubItem = _iSubItem;
	_lvitem.pszText = _text;
	::SendMessage(m_hList, LVM_INSERTITEM, _lvitem.iItem, (LPARAM)&_lvitem);
}

void KListCtrol::SetListItemText(int _iItem, int _iSubItem, TCHAR *_text)
{
	LVITEM _lvitem;
	memset(&_lvitem, 0, sizeof(LVITEM));
	_lvitem.mask = LVIF_TEXT;
	_lvitem.cchTextMax = MAX_PATH;
	_lvitem.iItem = _iItem;
	_lvitem.iSubItem = _iSubItem;
	_lvitem.pszText = _text;
	::SendMessage(m_hList, LVM_SETITEMTEXT, _lvitem.iItem, (LPARAM)&_lvitem);

	LSTELE _ele;
	_ele._item = _lvitem.iItem;
	lstrcpy(_ele._path, _text);
	_ele.next = NULL;
	AddListPath(_ele);
}

void KListCtrol::AddListPath(LSTELE _ele)
{
	PLSTELE p = NULL;
	PLSTELE q = NULL;

	if (NULL == p_head)
	{
		p_head = new LSTELE;
		(*p_head) = _ele;
	}
	else {
		q = p_head;
		while(q->next)
		{
			q = q->next;
		}
		p = new LSTELE;
		(*p) = _ele;
		q->next = p;
	}
}

PLSTELE KListCtrol::GetListPath()
{
	if (p_head)
	{
		return p_head;
	}
	return NULL;
}

BOOL KListCtrol::RemoveListItem()
{
	LVITEM _lvitem;
	PLSTELE _p = p_head;
	PLSTELE _q = p_head;
	BOOL _state = FALSE;

	_lvitem.iItem = ::SendMessage(m_hList, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if (-1 != _lvitem.iItem)
	{
		::SendMessage(m_hList, LVM_DELETEITEM, _lvitem.iItem, 0);

		while (_p)
		{
			if (_p->_item == _lvitem.iItem)
			{
				_state = TRUE;
				break;
			}
			_q = _p;
			_p = _p->next;
		}

		if (_p == p_head)
		{
			p_head = _p->next;
			delete _p;
			_p = NULL;
		}
		else if (_p != p_head)
		{
			_q->next = _p->next;
			delete _p;
			_p = NULL;
		}

		_p = p_head;
		int i = 0;
		while (_p)
		{
			_p->_item = i ++;
			_p = _p->next;
		}
	}
	return _state;
}