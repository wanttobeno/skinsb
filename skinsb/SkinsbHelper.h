#ifndef __SkinsbHelper_H__
#define __SkinsbHelper_H__
/*
官方网站上Detours最新版本是2.1,而SkinSB原生用的是1.5的版本的,
这两个版本的API差异还是很大的,
所以头文件对此做了一个桥接,以下为头文件的代码:

在 CxxxApp中包含本头文件 #include "./include/SkinsbHelper.h"
	在InitInstance()里面使用:
	RegisterSkinSB();
	在ExitInstance中使用;
	UnRegisterSkinSB();
在 CxxxDlg中包含头文件 #include "./include/skinsb.h"
	CBitmap m_bmScroll;
	在OnInitDialog()中调用
	//装入滚动条位图，初始化
	m_bmScroll.LoadBitmap(IDB_SCROLL);
	SkinSB_Init(m_list, m_bmScroll);
*/

// 包含头文件
#include "../detours/detours.h"
#include "skinsb.h"


#if defined(_DEBUG)
	#pragma comment(lib, "../Debug/skinsb.lib")
    #pragma comment(lib, "../Debug/detours.lib")
#else
    #pragma comment(lib, "../Release/skinsb.lib")
	#pragma comment(lib, "../Release/detours.lib")
#endif


//////////////////////////////////////////////////////////////////////////
// 申明钩子
//////////////////////////////////////////////////////////////////////////
#if (DETOURS_VERSION >= 20100)
    int (WINAPI* SetScrollInfoT) (HWND, int, LPCSCROLLINFO, BOOL) = SetScrollInfo;
    BOOL (WINAPI* GetScrollInfoT) (HWND, int, LPSCROLLINFO) = GetScrollInfo;
    int (WINAPI* SetScrollPosT) (HWND, int, int, BOOL) = SetScrollPos;
    int (WINAPI* GetScrollPosT) (HWND, int) = GetScrollPos;
    BOOL (WINAPI* GetScrollRangeT) (HWND, int, LPINT, LPINT) = GetScrollRange;
    BOOL (WINAPI* SetScrollRangeT) (HWND, int, int, int, BOOL) = SetScrollRange;
    BOOL (WINAPI* ShowScrollBarT) (HWND, int, BOOL) = ShowScrollBar;
    BOOL (WINAPI* EnableScrollBarT) (HWND, UINT, UINT) = EnableScrollBar;
#else
    DETOUR_TRAMPOLINE(int   WINAPI SetScrollInfoT(HWND, int, LPCSCROLLINFO, BOOL), SetScrollInfo)
    DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollInfoT(HWND, int, LPSCROLLINFO), GetScrollInfo)
    DETOUR_TRAMPOLINE(int   WINAPI SetScrollPosT(HWND, int, int, BOOL), SetScrollPos)
    DETOUR_TRAMPOLINE(int   WINAPI GetScrollPosT(HWND, int), GetScrollPos)
    DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollRangeT(HWND, int, LPINT, LPINT), GetScrollRange)
    DETOUR_TRAMPOLINE(BOOL  WINAPI SetScrollRangeT(HWND, int, int, int, BOOL), SetScrollRange)
    DETOUR_TRAMPOLINE(BOOL  WINAPI ShowScrollBarT(HWND, int, BOOL), ShowScrollBar)
    DETOUR_TRAMPOLINE(BOOL  WINAPI EnableScrollBarT(HWND, UINT, UINT), EnableScrollBar)
#endif


int WINAPI SetScrollInfoD(HWND hwnd, int fnBar, LPCSCROLLINFO lpsi, BOOL bRedraw)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_SetScrollInfo(hwnd, fnBar, lpsi, bRedraw);
    else
        return SetScrollInfoT(hwnd, fnBar, lpsi, bRedraw);
}

BOOL WINAPI GetScrollInfoD(HWND hwnd, int fnBar, LPSCROLLINFO lpsi)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_GetScrollInfo(hwnd, fnBar, lpsi);
    else
        return GetScrollInfoT(hwnd, fnBar, lpsi);
}

int WINAPI SetScrollPosD(HWND hwnd, int nBar, int nPos, BOOL bRedraw)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_SetScrollPos(hwnd, nBar, nPos, bRedraw);
    else
        return SetScrollPosT(hwnd, nBar, nPos, bRedraw);
}

int WINAPI GetScrollPosD(HWND hwnd, int nBar)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_GetScrollPos(hwnd, nBar);
    else
        return GetScrollPosT(hwnd, nBar);
}

BOOL WINAPI SetScrollRangeD(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_SetScrollRange(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
    else
        return SetScrollRangeT(hwnd, nBar, nMinPos, nMaxPos, bRedraw);
}

BOOL WINAPI GetScrollRangeD(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_GetScrollRange(hwnd, nBar, lpMinPos, lpMaxPos);
    else
        return GetScrollRangeT(hwnd, nBar, lpMinPos, lpMaxPos);
}

BOOL WINAPI ShowScrollBarD(HWND hwnd, int nBar, BOOL bShow)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_ShowScrollBar(hwnd, nBar, bShow);
    else
        return ShowScrollBarT(hwnd, nBar, bShow);
}

BOOL WINAPI EnableScrollBarD(HWND hwnd, UINT wSBflags, UINT wArrows)
{
    if( SkinSB_IsValid(hwnd) )
        return SkinSB_EnableScrollBar(hwnd, wSBflags, wArrows);
    else
        return EnableScrollBarT(hwnd, wSBflags, wArrows);
}


//////////////////////////////////////////////////////////////////////////
/// 注册钩子
//////////////////////////////////////////////////////////////////////////
LONG RegisterSkinSB(VOID)
{
#if (DETOURS_VERSION >= 20100)
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    // 加载钩子
    ::DetourAttach(&(PVOID&)SetScrollInfoT, SetScrollInfoD);
    ::DetourAttach(&(PVOID&)GetScrollInfoT, GetScrollInfoD);
    ::DetourAttach(&(PVOID&)SetScrollPosT, SetScrollPosD);
    ::DetourAttach(&(PVOID&)GetScrollPosT, GetScrollPosD);
    ::DetourAttach(&(PVOID&)SetScrollRangeT, SetScrollRangeD);
    ::DetourAttach(&(PVOID&)GetScrollRangeT, GetScrollRangeD);
    ::DetourAttach(&(PVOID&)ShowScrollBarT, ShowScrollBarD);
    ::DetourAttach(&(PVOID&)EnableScrollBarT, EnableScrollBarD);
    return DetourTransactionCommit();
#else
    ::DetourFunctionWithTrampoline((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
    ::DetourFunctionWithTrampoline((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
    ::DetourFunctionWithTrampoline((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
    ::DetourFunctionWithTrampoline((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
    ::DetourFunctionWithTrampoline((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
    ::DetourFunctionWithTrampoline((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
    ::DetourFunctionWithTrampoline((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
    ::DetourFunctionWithTrampoline((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
    return 1;
#endif
}


//////////////////////////////////////////////////////////////////////////
/// 注销钩子
//////////////////////////////////////////////////////////////////////////
LONG UnRegisterSkinSB(VOID)
{
#if (DETOURS_VERSION >= 20100)    
    // 卸载钩子
    ::DetourDetach(&(PVOID&)SetScrollInfoT, SetScrollInfoD);
    ::DetourDetach(&(PVOID&)GetScrollInfoT, GetScrollInfoD);
    ::DetourDetach(&(PVOID&)SetScrollPosT, SetScrollPosD);
    ::DetourDetach(&(PVOID&)GetScrollPosT, GetScrollPosD);
    ::DetourDetach(&(PVOID&)SetScrollRangeT, SetScrollRangeD);
    ::DetourDetach(&(PVOID&)GetScrollRangeT, GetScrollRangeD);
    ::DetourDetach(&(PVOID&)ShowScrollBarT, ShowScrollBarD);
    ::DetourDetach(&(PVOID&)EnableScrollBarT, EnableScrollBarD);
#else
    ::DetourRemove((PBYTE)SetScrollInfoT, (PBYTE)SetScrollInfoD);
    ::DetourRemove((PBYTE)SetScrollPosT, (PBYTE)SetScrollPosD);
    ::DetourRemove((PBYTE)GetScrollInfoT, (PBYTE)GetScrollInfoD);
    ::DetourRemove((PBYTE)GetScrollPosT, (PBYTE)GetScrollPosD);
    ::DetourRemove((PBYTE)SetScrollRangeT, (PBYTE)SetScrollRangeD);
    ::DetourRemove((PBYTE)GetScrollRangeT, (PBYTE)GetScrollRangeD);
    ::DetourRemove((PBYTE)ShowScrollBarT, (PBYTE)ShowScrollBarD);
    ::DetourRemove((PBYTE)EnableScrollBarT, (PBYTE)EnableScrollBarD);
#endif
    return 1;
}


#endif
