
#include <windows.h>
#include "Namako.h"

#define SPORT_ADDRESS	""
#define MASKI_ADDRESS	""

//ﾊﾞｰｼﾞｮﾝﾀﾞｲｱﾛｸﾞProc
LRESULT CALLBACK VerDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	//ﾒｯｾｰｼﾞ判別
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			//ﾀﾞｲｱﾛｸﾞ初期化処理
			SetDlgItemText(hDlg,IDC_HPAD,SPORT_ADDRESS);
			SetDlgItemText(hDlg,IDC_HPAD2,MASKI_ADDRESS);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_VER_OK:
			EndDialog(hDlg,0);
		}
		break;

	default:
		return(FALSE);
	}

	return(TRUE);
}
