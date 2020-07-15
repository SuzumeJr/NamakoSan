// PopupMenu.cpp: PopupMenu クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "PopupMenu.h"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

PopupMenu::PopupMenu()
{
	m_hMenu = NULL;
	m_hWnd = NULL;
}

PopupMenu::~PopupMenu()
{

}

BOOL PopupMenu::Append(UINT uFlags, UINT uIDNewItem, LPSTR lpsNewItem)
{
	return AppendMenu(m_hMenu,uFlags,uIDNewItem,lpsNewItem);
}

BOOL PopupMenu::Show()
{
 	POINT	Point;
 	
 	GetCursorPos(&Point);
 
 	return	TrackPopupMenu(m_hMenu,TPM_LEFTBUTTON,Point.x,Point.y,0,m_hWnd,NULL);
}

BOOL PopupMenu::Create(HWND hWnd)
{
	m_hWnd = hWnd;
	m_hMenu = CreatePopupMenu();
	if(m_hMenu == NULL)
		return FALSE;
	else
		return TRUE;
}
