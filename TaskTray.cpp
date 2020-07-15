
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "TaskTray.h"

//////////////////////////////////////////////////////////////////////
// TaskTray �N���X
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

TaskTray::TaskTray()
{
	m_lpTrayName = NULL;	//����ڲ��������
	//����ڲ�p�\���̂̏�����
	memset( &m_typNotifyIconData, 0, sizeof( NOTIFYICONDATA ) );
}

TaskTray::~TaskTray()
{
	//����ڲ�p��
	Destory();
}

//����ڲ�쐬(�o�^)�֐�
BOOL TaskTray::Create( HWND hWnd, LPSTR lpTaskTrayName, HICON hIcon )
{
	int	iNameLen = 0;

	//�o�^�ς�����
	if( m_typNotifyIconData.uCallbackMessage != 0 )
		return FALSE;

	//��������
	if( hWnd == 0 || lpTaskTrayName == NULL )
		return FALSE;

	//����ڲ�o�^���i�[
	m_lpTrayName = strdup( lpTaskTrayName );
	
	//����ڲ�pհ�ްү���ގ擾
	m_typNotifyIconData.uCallbackMessage = RegisterWindowMessage( lpTaskTrayName );
	if( m_typNotifyIconData.uCallbackMessage == 0 )
		return	FALSE;

    //�\���̻̂��ނ�ݒ�
    m_typNotifyIconData.cbSize = sizeof( NOTIFYICONDATA );

	//����޳����ق��i�[
    m_typNotifyIconData.hWnd = hWnd;
	
	//���݁E°����߂�\��������Aү���ނ�Ԃ�����(�ڂ悭�킩���̂Ż���قɂ������ȁj
    m_typNotifyIconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;

	//�ڲ�ɕ\�����鱲�݂�ݒ�
    m_typNotifyIconData.hIcon = hIcon;

	//°����ߓo�^
	memset( m_typNotifyIconData.szTip, 0, 64 );
	iNameLen = strlen( lpTaskTrayName );
	if( iNameLen >= 64 )
		iNameLen = 64;
	memcpy( m_typNotifyIconData.szTip, lpTaskTrayName, iNameLen );

	//����ڲ�o�^
	return Shell_NotifyIcon( NIM_ADD, &m_typNotifyIconData );
}

//����ڲ�p������
BOOL TaskTray::Destory()
{
	//�p������
	//�o�^�ς�����
	if( m_typNotifyIconData.uCallbackMessage == 0 )
		return FALSE;

	//����ڲ����������؉��
	if( m_lpTrayName != NULL )
		free( m_lpTrayName );

	//����ڲ�p��
	Shell_NotifyIcon( NIM_DELETE, &m_typNotifyIconData );

	//������
	TaskTray();

	return TRUE;
}

UINT TaskTray::MessageID()
{
	return m_typNotifyIconData.uCallbackMessage;
}
