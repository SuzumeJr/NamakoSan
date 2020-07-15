// PopupMenu.h: PopupMenu クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POPUPMENU_H__0CFCD091_78BD_11D4_9F20_00E0292F71F1__INCLUDED_)
#define AFX_POPUPMENU_H__0CFCD091_78BD_11D4_9F20_00E0292F71F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class PopupMenu  
{
public:
	BOOL Create(HWND hWnd);
	BOOL Show(void);
	BOOL Append(UINT uFlags,UINT uIDNewItem, LPSTR lpsNewItem);
	PopupMenu();
	virtual ~PopupMenu();

private:
	HWND m_hWnd;
	HMENU m_hMenu;
};

#endif // !defined(AFX_POPUPMENU_H__0CFCD091_78BD_11D4_9F20_00E0292F71F1__INCLUDED_)
