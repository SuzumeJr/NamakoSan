
#include <windows.h>
#include "Namako.h"

#define SPORT_ADDRESS	""
#define MASKI_ADDRESS	""

//�ް�ޮ��޲�۸�Proc
LRESULT CALLBACK VerDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	//ү���ޔ���
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			//�޲�۸ޏ���������
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
