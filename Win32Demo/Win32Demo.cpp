// 一个测试通过的模板，控件消息正常，关闭正常

#include <windows.h>
#include "resource.h"
#include <WindowsX.h>
#include <CommCtrl.h>
#pragma comment(lib,"comctl32.lib")

#include "../skinsb/SkinsbHelper.h"

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


HWND CreateListView(HWND hwndParent);
#define  C_COLUMNS  100


HWND CreateListView222(HWND hwndParent, HMENU hMenu, HINSTANCE hInst)
{
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(hwndParent, &rcClient);

	// Create the list-view window in report view with label editing enabled.
	HWND hWndListView = CreateWindow(WC_LISTVIEW,
		L"",
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
		0, 0,
		rcClient.right - rcClient.left,
		rcClient.bottom - rcClient.top,
		hwndParent,
		hMenu,
		hInst,
		NULL);

	return (hWndListView);
}

LRESULT CALLBACK Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		char szTitle[MAX_PATH] = { 0 };
		GetWindowTextA(hDlg, szTitle, MAX_PATH);
		strcat(szTitle, " ");
		strcat(szTitle, __TIMESTAMP__);
		SetWindowTextA(hDlg, szTitle);



		RegisterSkinSB();
		HWND m_hList = GetDlgItem(hDlg, IDC_LIST1);
		HBITMAP hBitmap = (HBITMAP)::LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_SCROLL), IMAGE_BITMAP, 256, 48, 0);
		if (hBitmap != INVALID_HANDLE_VALUE)
		{
			SkinSB_Init(m_hList, hBitmap);
		}
		LVCOLUMN _lvcol;
		memset(&_lvcol, 0, sizeof(LVCOLUMN));
		_lvcol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		_lvcol.pszText = L"表头";
		_lvcol.cx = 80;
		for (int i = 0; i < 20; i++)
		{
			::SendMessage(m_hList, LVM_INSERTCOLUMN, i/*第一列*/, (LPARAM)&_lvcol);
		}

		for (int index = 0; index < 10000; index++)
		{
			LVITEM _lvitem;
			memset(&_lvitem, 0, sizeof(LVITEM));
			_lvitem.iItem = index;
			ListView_InsertItem(m_hList, &_lvitem); // 插入行
			//添加子项;
			_lvitem.mask = LVIF_TEXT;
			_lvitem.pszText = L"数据";
			for (int j = 0; j < 5; j++)
			{
				_lvitem.iSubItem = j;
				ListView_SetItem(m_hList, &_lvitem);
			}
		}
	}
	return TRUE;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}
	break;
	case WM_CLOSE:
	{
		EndDialog(hDlg, wParam);
		UnRegisterSkinSB();
		return TRUE;
	}
	break;

	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)Proc);

	return 0;
}