
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "TaskTray.h"

//////////////////////////////////////////////////////////////////////
// TaskTray クラス
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

TaskTray::TaskTray()
{
	Initialize();
}

TaskTray::~TaskTray()
{
	//ﾀｽｸﾄﾚｲ廃棄
	Destory();
}

// 初期化
void TaskTray::Initialize(void)
{
	m_lpTrayName = NULL;	//ﾀｽｸﾄﾚｲ名初期化
	//ﾀｽｸﾄﾚｲ用構造体の初期化
	memset(&m_typNotifyIconData, 0, sizeof(NOTIFYICONDATA));
}

//ﾀｽｸﾄﾚｲ作成(登録)関数
BOOL TaskTray::Create( HWND hWnd, LPSTR lpTaskTrayName, HICON hIcon )
{
	int	iNameLen = 0;

	//登録済みﾁｪｯｸ
	if( m_typNotifyIconData.uCallbackMessage != 0 )
	{
		return FALSE;
	}

	//引数ﾁｪｯｸ
	if (hWnd == 0 || lpTaskTrayName == NULL)
	{
		return FALSE;
	}

	//ﾀｽｸﾄﾚｲ登録名格納
	m_lpTrayName = strdup( lpTaskTrayName );
	
	//ﾀｽｸﾄﾚｲ用ﾕｰｻﾞｰﾒｯｾｰｼﾞ取得
	m_typNotifyIconData.uCallbackMessage = RegisterWindowMessage( lpTaskTrayName );
	if (m_typNotifyIconData.uCallbackMessage == 0)
	{
		return	FALSE;
	}

    //構造体のｻｲｽﾞを設定
    m_typNotifyIconData.cbSize = sizeof( NOTIFYICONDATA );

	//ｳｨﾝﾄﾞｳﾊﾝﾄﾞﾙを格納
    m_typNotifyIconData.hWnd = hWnd;
	
	//ｱｲｺﾝ・ﾂｰﾙﾁｯﾌﾟを表示させる、ﾒｯｾｰｼﾞを返させる(ｺﾚよくわからんのでｻﾝﾌﾟﾙにあったﾏﾈ）
    m_typNotifyIconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;

	//ﾄﾚｲに表示するｱｲｺﾝを設定
    m_typNotifyIconData.hIcon = hIcon;

	//ﾂｰﾙﾁｯﾌﾟ登録
	memset( m_typNotifyIconData.szTip, 0, 64 );
	iNameLen = strlen( lpTaskTrayName );
	if (iNameLen >= 64)
	{
		iNameLen = 64;
	}
	memcpy( m_typNotifyIconData.szTip, lpTaskTrayName, iNameLen );

	//ﾀｽｸﾄﾚｲ登録
	return Shell_NotifyIcon( NIM_ADD, &m_typNotifyIconData );
}

//ﾀｽｸﾄﾚｲ廃棄処理
BOOL TaskTray::Destory()
{
	//廃棄処理
	//登録済みﾁｪｯｸ
	if (m_typNotifyIconData.uCallbackMessage == 0)
	{
		return FALSE;
	}

	//ﾀｽｸﾄﾚｲ名文字列ﾒﾓﾘ解放
	if (m_lpTrayName != NULL)
	{
		free(m_lpTrayName);
		m_lpTrayName = NULL;
	}

	//ﾀｽｸﾄﾚｲ廃棄
	Shell_NotifyIcon( NIM_DELETE, &m_typNotifyIconData );
	memset(&m_typNotifyIconData, 0, sizeof(m_typNotifyIconData));

	return TRUE;
}

UINT TaskTray::MessageID()
{
	return m_typNotifyIconData.uCallbackMessage;
}
