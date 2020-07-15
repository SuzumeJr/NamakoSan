
#include <windows.h>
#include "Namako.h"

#define SPORT_ADDRESS	"http://homepage1.nifty.com/Suzume/"
#define MASKI_ADDRESS	"http://www.netlaputa.ne.jp/~MASKI/"

// ﬁ∞ºﬁÆ›¿ﬁ≤±€∏ﬁProc
LRESULT CALLBACK VerDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	//“Øæ∞ºﬁîªï 
	switch(uMsg){
	case WM_INITDIALOG:{
			//¿ﬁ≤±€∏ﬁèâä˙âªèàóù
			SetDlgItemText(hDlg,IDC_HPAD,SPORT_ADDRESS);
			SetDlgItemText(hDlg,IDC_HPAD2,MASKI_ADDRESS);
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
		case ID_VER_OK:
			EndDialog(hDlg,0);
		}
		break;

	default:
		return(FALSE);
	}
	return(TRUE);
}
