// IniFile.h: IniFile �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__A78BC851_2E11_11D5_932E_00E0292F71F1__INCLUDED_)
#define AFX_INIFILE_H__A78BC851_2E11_11D5_932E_00E0292F71F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class IniFile {
public:
	BOOL Save( void );
	BOOL Create( HINSTANCE hInst, LPSTR lpFileName );
	LPSTR GetPath( void );
	BOOL Load( void );
	IniFile();
	virtual ~IniFile();

	//INI̧�ٍ��ڒl
	RECT	m_NamakoRect = {0};		//�Ȃ܎q����̈ʒu���i�[����\����
	UINT	m_uiWndMode = 0;		//�����Ӱ��

private:
	//INI̧���߽
	char m_szFilePath[MAX_PATH + 1] = {0};

};

#endif // !defined(AFX_INIFILE_H__A78BC851_2E11_11D5_932E_00E0292F71F1__INCLUDED_)
