// TaskTray.h: TaskTray �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKTRAY_H__CFD4426A_23EA_11D5_931A_00E0292F71F1__INCLUDED_)
#define AFX_TASKTRAY_H__CFD4426A_23EA_11D5_931A_00E0292F71F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//����ڲϳ������ү���޺���
#define	TM_LBUTTONUP		0x202	//������UP
#define	TM_LBUTTONDBLCLK	0x203	//����������ٸد�
#define	TM_RBUTTONUP		0x205	//�E����UP

#include <windows.h>

class TaskTray
{
public:
	UINT MessageID(void);
	BOOL Destory(void);					//����ڲ�p��
	BOOL Create( HWND, LPSTR, HICON );	//����ڲ�쐬
	TaskTray();
	virtual ~TaskTray();

private:
	LPSTR m_lpTrayName = NULL;					//����ڲ��
	NOTIFYICONDATA m_typNotifyIconData = {0};	//����ڲ�p�\����

	void Initialize(void);						//������
};

#endif // !defined(AFX_TASKTRAY_H__CFD4426A_23EA_11D5_931A_00E0292F71F1__INCLUDED_)
