// TaskTray.h: TaskTray クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKTRAY_H__CFD4426A_23EA_11D5_931A_00E0292F71F1__INCLUDED_)
#define AFX_TASKTRAY_H__CFD4426A_23EA_11D5_931A_00E0292F71F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ﾀｽｸﾄﾚｲﾏｳｽｲﾍﾞﾝﾄﾒｯｾｰｼﾞｺｰﾄﾞ
#define	TM_LBUTTONUP		0x202	//左ﾎﾞﾀﾝUP
#define	TM_LBUTTONDBLCLK	0x203	//左ﾎﾞﾀﾝﾀﾞﾌﾞﾙｸﾘｯｸ
#define	TM_RBUTTONUP		0x205	//右ﾎﾞﾀﾝUP

#include <windows.h>

class TaskTray
{
public:
	UINT MessageID(void);
	BOOL Destory(void);					//ﾀｽｸﾄﾚｲ廃棄
	BOOL Create( HWND, LPSTR, HICON );	//ﾀｽｸﾄﾚｲ作成
	TaskTray();
	virtual ~TaskTray();

private:
	LPSTR m_lpTrayName = NULL;					//ﾀｽｸﾄﾚｲ名
	NOTIFYICONDATA m_typNotifyIconData = {0};	//ﾀｽｸﾄﾚｲ用構造体

	void Initialize(void);						//初期化
};

#endif // !defined(AFX_TASKTRAY_H__CFD4426A_23EA_11D5_931A_00E0292F71F1__INCLUDED_)
