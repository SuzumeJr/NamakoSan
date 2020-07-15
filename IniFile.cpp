// IniFile.cpp: IniFile クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "IniFile.h"

#define INIT_SECTION_SCR	"SCREEN"
#define INIT_SCR_X			"PointX"
#define INIT_SCR_Y			"PointY"
#define OPT_SECTION_WND		"OPTION"
#define OPT_WND_MODE		"WindowMode"

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

IniFile::IniFile()
{

}

IniFile::~IniFile()
{

}

BOOL IniFile::Load( void )
{
	//INIﾌｧｲﾙ項目読込
	//なま子さん表示X座標読込
	m_NamakoRect.left = GetPrivateProfileInt(INIT_SECTION_SCR,INIT_SCR_X,0,m_szFilePath);
	//なま子さん表示Y座標読込
	m_NamakoRect.top = GetPrivateProfileInt(INIT_SECTION_SCR,INIT_SCR_Y,0,m_szFilePath);
	
	//なま子さんウインドモード
	m_uiWndMode = GetPrivateProfileInt(OPT_SECTION_WND,OPT_WND_MODE,0,m_szFilePath);

	return TRUE;
}

LPSTR IniFile::GetPath()
{
	return	m_szFilePath;
}

BOOL IniFile::Create( HINSTANCE hInst, LPSTR lpFileName )
{
	//引数ﾁｪｯｸ
	if( hInst == NULL || lpFileName == NULL )
		return FALSE;
	
	//ﾓｼﾞｭｰﾙからとりあえずﾊﾟｽを取得する。
	if( GetModuleFileName( hInst, m_szFilePath, MAX_PATH ) == 0 )
		return	FALSE;

	//ﾌｧｲﾙﾊﾟｽからﾌｧｲﾙ名を除去
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
	
	//なま子さん次回表示座標X書込
	wsprintf(szWork,"%d",m_NamakoRect.left);
	WritePrivateProfileString(INIT_SECTION_SCR,INIT_SCR_X,szWork,m_szFilePath);

	//なま子さん次回表示Y座標書込
	wsprintf(szWork,"%d",m_NamakoRect.top);
	WritePrivateProfileString(INIT_SECTION_SCR,INIT_SCR_Y,szWork,m_szFilePath);

	//なま子さんウインドモード
	wsprintf(szWork,"%d",m_uiWndMode);
	WritePrivateProfileString(OPT_SECTION_WND,OPT_WND_MODE,szWork,m_szFilePath);

	return TRUE;
}
