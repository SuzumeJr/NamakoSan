// IniFile.cpp: IniFile �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "IniFile.h"

#define INIT_SECTION_SCR	"SCREEN"
#define INIT_SCR_X			"PointX"
#define INIT_SCR_Y			"PointY"
#define OPT_SECTION_WND		"OPTION"
#define OPT_WND_MODE		"WindowMode"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

IniFile::IniFile()
{

}

IniFile::~IniFile()
{

}

BOOL IniFile::Load( void )
{
	//INI̧�ٍ��ړǍ�
	//�Ȃ܎q����\��X���W�Ǎ�
	m_NamakoRect.left = GetPrivateProfileInt(INIT_SECTION_SCR,INIT_SCR_X,0,m_szFilePath);
	//�Ȃ܎q����\��Y���W�Ǎ�
	m_NamakoRect.top = GetPrivateProfileInt(INIT_SECTION_SCR,INIT_SCR_Y,0,m_szFilePath);
	
	//�Ȃ܎q����E�C���h���[�h
	m_uiWndMode = GetPrivateProfileInt(OPT_SECTION_WND,OPT_WND_MODE,0,m_szFilePath);

	return TRUE;
}

LPSTR IniFile::GetPath()
{
	return	m_szFilePath;
}

BOOL IniFile::Create( HINSTANCE hInst, LPSTR lpFileName )
{
	//��������
	if( hInst == NULL || lpFileName == NULL )
		return FALSE;
	
	//Ӽޭ�ق���Ƃ肠�����߽���擾����B
	if( GetModuleFileName( hInst, m_szFilePath, MAX_PATH ) == 0 )
		return	FALSE;

	//̧���߽����̧�ٖ�������
    LPSTR lpModuleName = strrchr( m_szFilePath, '\\' );
    if( NULL != lpFileName )
        lpModuleName[1] = '\0';
	else
		m_szFilePath[0] = '\0';

	strcat( m_szFilePath, lpFileName );

	return TRUE;
}

BOOL IniFile::Save()
{
	char	szWork[ MAX_PATH ];
	
	//�Ȃ܎q���񎟉�\�����WX����
	wsprintf(szWork,"%d",m_NamakoRect.left);
	WritePrivateProfileString(INIT_SECTION_SCR,INIT_SCR_X,szWork,m_szFilePath);

	//�Ȃ܎q���񎟉�\��Y���W����
	wsprintf(szWork,"%d",m_NamakoRect.top);
	WritePrivateProfileString(INIT_SECTION_SCR,INIT_SCR_Y,szWork,m_szFilePath);

	//�Ȃ܎q����E�C���h���[�h
	wsprintf(szWork,"%d",m_uiWndMode);
	WritePrivateProfileString(OPT_SECTION_WND,OPT_WND_MODE,szWork,m_szFilePath);

	return TRUE;
}
