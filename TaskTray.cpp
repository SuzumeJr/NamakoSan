
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "TaskTray.h"

//////////////////////////////////////////////////////////////////////
// TaskTray ƒNƒ‰ƒX
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// \’z/Á–Å
//////////////////////////////////////////////////////////////////////

TaskTray::TaskTray()
{
	m_lpTrayName = NULL;	//À½¸ÄÚ²–¼‰Šú‰»
	//À½¸ÄÚ²—p\‘¢‘Ì‚Ì‰Šú‰»
	memset( &m_typNotifyIconData, 0, sizeof( NOTIFYICONDATA ) );
}

TaskTray::~TaskTray()
{
	//À½¸ÄÚ²”pŠü
	Destory();
}

//À½¸ÄÚ²ì¬(“o˜^)ŠÖ”
BOOL TaskTray::Create( HWND hWnd, LPSTR lpTaskTrayName, HICON hIcon )
{
	int	iNameLen = 0;

	//“o˜^Ï‚İÁª¯¸
	if( m_typNotifyIconData.uCallbackMessage != 0 )
		return FALSE;

	//ˆø”Áª¯¸
	if( hWnd == 0 || lpTaskTrayName == NULL )
		return FALSE;

	//À½¸ÄÚ²“o˜^–¼Ši”[
	m_lpTrayName = strdup( lpTaskTrayName );
	
	//À½¸ÄÚ²—pÕ°»Ş°Ò¯¾°¼Şæ“¾
	m_typNotifyIconData.uCallbackMessage = RegisterWindowMessage( lpTaskTrayName );
	if( m_typNotifyIconData.uCallbackMessage == 0 )
		return	FALSE;

    //\‘¢‘Ì‚Ì»²½Ş‚ğİ’è
    m_typNotifyIconData.cbSize = sizeof( NOTIFYICONDATA );

	//³¨İÄŞ³ÊİÄŞÙ‚ğŠi”[
    m_typNotifyIconData.hWnd = hWnd;
	
	//±²ºİEÂ°ÙÁ¯Ìß‚ğ•\¦‚³‚¹‚éAÒ¯¾°¼Ş‚ğ•Ô‚³‚¹‚é(ºÚ‚æ‚­‚í‚©‚ç‚ñ‚Ì‚Å»İÌßÙ‚É‚ ‚Á‚½ÏÈj
    m_typNotifyIconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;

	//ÄÚ²‚É•\¦‚·‚é±²ºİ‚ğİ’è
    m_typNotifyIconData.hIcon = hIcon;

	//Â°ÙÁ¯Ìß“o˜^
	memset( m_typNotifyIconData.szTip, 0, 64 );
	iNameLen = strlen( lpTaskTrayName );
	if( iNameLen >= 64 )
		iNameLen = 64;
	memcpy( m_typNotifyIconData.szTip, lpTaskTrayName, iNameLen );

	//À½¸ÄÚ²“o˜^
	return Shell_NotifyIcon( NIM_ADD, &m_typNotifyIconData );
}

//À½¸ÄÚ²”pŠüˆ—
BOOL TaskTray::Destory()
{
	//”pŠüˆ—
	//“o˜^Ï‚İÁª¯¸
	if( m_typNotifyIconData.uCallbackMessage == 0 )
		return FALSE;

	//À½¸ÄÚ²–¼•¶š—ñÒÓØ‰ğ•ú
	if( m_lpTrayName != NULL )
		free( m_lpTrayName );

	//À½¸ÄÚ²”pŠü
	Shell_NotifyIcon( NIM_DELETE, &m_typNotifyIconData );

	//‰Šú‰»
	TaskTray();

	return TRUE;
}

UINT TaskTray::MessageID()
{
	return m_typNotifyIconData.uCallbackMessage;
}
