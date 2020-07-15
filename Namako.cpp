//�޽�į�߂Ȃ܎q����
//Version 1.01
//
//Programaer		���� �����q
//Special Thanks	�V�� ���P
//
//Date			1998.10.08
//				2001.05.17

#include <windows.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "Namako.h"
#include "PopupMenu.h"
#include "TaskTray.h"
#include "IniFile.h"

#define INIT_FILE_NAME		"NamakoSan.ini"

//��׸���
#define APPLI_TITLE_NAME	"�Ȃ܎q����"

#define TIMER_ERIKA	1		//��ϰID

#define	WND_HEIGHT	48		//����޳�̊�{�c�T�C�Y
#define WND_WIDTH	48		//����޳�̊�{���T�C�Y

#define BACK_BITMAP_HEIGHT	48 
#define BACK_BITMAP_WIDTH	48

#define WORK_BITMAP_WIDTH	48
#define WORK_BITMAP_HEIGHT	48

#define ANIME_PA_PIKUN		0		//ɰ��
#define ANIME_PA_JITA2		1		//������
#define ANIME_PA_HJUMP		2		//HI�ެ���
#define ANIME_PA_NEGAERI	3		//�˂�����`
#define ANIME_PA_DANS		4		//��ݽ
#define ANIME_PA_RIBON		5		//����
#define ANIME_PA_LHJUMP		6		//���ެ���
#define ANIME_PA_RHJUMP		7		//�E�ެ���
#define ANIME_PA_IJI2		8		//��޲��
#define ANIME_PA_WAIT		9		//�����`�`�`
#define ANIME_PA_FUKKIN		10		//�ӂ�����
#define ANIME_PA_SLEEP  	11		//�޳�޳
#define ANIME_PA_LSOWA2		12		//(��)���킻��
#define ANIME_PA_RSOWA2		13		//(�E)���킻��

#define SLEEP_TIME	3600		//��P����

#define ANIME_PATURN		14
#define ANIME_TI_SLEEP		0
#define	ANIME_TI_COUNT		1

/*
struct CHARCTER_STRUCT {
	HDC		hDC;						//���޲���÷��						
	HWND	hBitmap;					//��׸��ޯ�ϯ��
	int		Mode;						//����Ӱ��
	int		AnimeCounter;				//��Ұ��ݶ����
	int		PaturnType;					//��Ұ��������
	int		Paturn[ANIME_PATRUN][12];	//��������
	int		MoveX[ANIME_PATRUN][12];	//�ړ�X���W
	int		MoveY[ANIME_PATRUN][12];	//�ړ�Y���W
	int		AnimeCount[ANIME_PATRUN];	//��Ұ�������ݶ���
	int		TimeCount[1];				//�Q��܂Ŷ���=0
}
*/

HINSTANCE	MainInst;
HWND		hDeskTopWnd;	//�޽�į�߂������
HWND		hMainWnd;		//Ҳݳ���޳�������
HWND		hMouCapWnd;		//ϳ�����������O�ɷ��������Ă������؂������
HWND		VerWnd;			//�ް�ޮ��޲�۸ނ������
HBITMAP		hErikaBitmap;	//�G�������ޯ�ϯ�������
HBITMAP		hBackBitmap;	//�w�i�pܰ��ޯ�ϯ��

HDC		hdcErika;			//�G���������޲���÷��
HDC		hdcMainWnd;			//Ҳݳ���ނ����޲���÷��
HDC		hdcBackBitmap;		//�w�i�摜�ޔ����޲���÷��
HDC		hdcWorkBitmap;		//�����pܰ����޲���÷��

RECT	WndRect;
RECT	DeskTopRect;		//�޽�į�߂̻���

//��۰��ٸ׽
PopupMenu	g_clsMainMenu;	//�E�د��ƭ�
TaskTray	g_clsTaskTray;	//����ڲ
IniFile		g_clsNamakoIni;	//�Ȃ܎q���񏉊��ݒ�

int AnimeCounter;			//��Ұ��ݕ\������̶݂���
int AnimePaturn;			//�\�������Ұ�������ݔԍ�

//�������ݐ�
int ErikaAnimeCount[ANIME_PATURN]	  = {9,11, 8,11,7,8,8,8,5,11,11,11,10,10};		

//�������݉摜���W
int ErikaAnime[ANIME_PATURN][12] = {
							  0,  0,  0,  0,  0,  0,  0, 49, 97, 49,  0,  0,	//�m�`�}��
							  0, 49, 97, 49,  0, 49, 97, 49,  0, 49, 97, 49,	//�W�^�W�^
                              0, 97, 49, 49, 49, 97, 97,  0,  0,  0,  0,  0,	//�҂��
							145,145,145,145,145,145,145,145,145,193,241,193,	//�Q�Ԃ�
							432,432,480,480,432,432,528,528,  0,  0,  0,  0,	//�_���X
							288,288,288,288,288,288,384,336,384,  0,  0,  0,	//��				
                              0, 97, 49, 49, 49, 97, 97,  0,  0,  0,  0,  0,	//�҂��i���j
                              0, 97, 49, 49, 49, 97, 97,  0,  0,  0,  0,  0,	//�҂��i�E�j
							  0,576,576,  0,576,576,  0,  0,  0,  0,  0,  0,	//��������
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	//�����`���Ƃ��Ă�
							432,432,672,672,480,480,624,624,480,480,672,672,	//�ӂ�����
							145,145,145,145,145,145,145,145,145,145,145,145,	//��������
							  0, 49,  0, 49,  0,  0, 49,  0, 49,  0,  0,  0,	//(��)���킻��	
							  0, 49,  0, 49,  0,  0, 49,  0, 49,  0,  0,  0		//(�E)���킻��
							};

//��Ұ���X���W
int ErikaAnimeX[ANIME_PATURN][12] = {	
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,-12,-12,-12,-12,  0,  0,  0,  0,  0,
                              0,  0,  0, 12, 12, 12, 12,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0, -6, -6, -6, -6,  0,  6,  6,  6,  6,  0,  0,
							  0,  6,  6,  6,  6,  0, -6, -6, -6, -6,  0,  0
						};
//��Ұ���Y���W
int ErikaAnimeY[ANIME_PATURN][12] = {
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,-24,-12, 12, 24,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0,  0,-24,-12, 12, 24,  0,  0,  0,  0,  0,
                              0,  0,  0,-24,-12, 12, 24,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
						};
long ErikaSleepTimer;

int	WndMovFlg;
int	WMPAINT_Flag;
POINT	MouPoint;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);			//Ҳݳ���޳�֐�
BOOL ScrPointChk(RECT *,RECT *);							//��ذݕ\�����W�����֐�
int RandAnimeP(int);										//����ѱ�Ұ�������݊֐�

//���C��(���ؓo�^����)
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE, LPTSTR lpCmdLine, int showCmd)
{
	static char psAppName[] = APPLI_TITLE_NAME;
	MSG msg;
	HWND hWnd;

	memset(&WndRect,0x00,sizeof(RECT));

	//�N���X�̐ݒ�
	WNDCLASS	wndClass;
	memset(&wndClass,0x00,sizeof(WNDCLASS));
	wndClass.lpszClassName	= psAppName;
	wndClass.lpfnWndProc	= WndProc;
	wndClass.style			= CS_DBLCLKS;		//����ٸد�ү���ޗL����
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.lpszMenuName	= 0;
	wndClass.hbrBackground	= NULL;
	wndClass.hInstance		= hInst;
	wndClass.hIcon			= LoadIcon( hInst, MAKEINTRESOURCE(IDI_MAIN) );
	wndClass.hCursor		= LoadCursor( hInst, MAKEINTRESOURCE(IDC_HAND1) );

	MainInst = hInst;

	RegisterClass(&wndClass);

	//�����ݒ�̧�ٓǍ�
	g_clsNamakoIni.Create( hInst, INIT_FILE_NAME );
	g_clsNamakoIni.Load();
	//Ҳݳ���ލ쐬
	WndRect = g_clsNamakoIni.m_NamakoRect;
	DWORD WndStyle = WS_EX_TOOLWINDOW;
	if( g_clsNamakoIni.m_uiWndMode == 1 ){
		WndStyle |= WS_EX_TOPMOST; 
	}
	hWnd = CreateWindowEx(
				WndStyle,psAppName,APPLI_TITLE_NAME,
				WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS,
				WndRect.left,WndRect.top,
				WND_HEIGHT,WND_WIDTH,0,0,
				hInst,0);

	ShowWindow(hWnd,showCmd);
	UpdateWindow(hWnd);

	while(GetMessage(&msg,0,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//��׸��\���֐�
//HWND	hWnd	:�\�����鳲��޳�������
//LONG	MoveX	:�ړ�����X���W�̑��΋���
//LONG	MoveY	:�ړ�����Y���W�̑��΋���
void CharacterMove(HWND hWnd,LONG MoveX,LONG MoveY){
	
	HDC hdcWnd;

	BitBlt(hdcWorkBitmap,0,0,BACK_BITMAP_WIDTH,BACK_BITMAP_HEIGHT,hdcBackBitmap,0,0,SRCCOPY);

	WndRect.top += MoveY;		
	WndRect.left += MoveX;
	
	//�ި̫���ޯ���׳��޶���ײ
	HDC hdcDeskTopWnd = GetDC(hDeskTopWnd);
	BitBlt(hdcBackBitmap,0,0,BACK_BITMAP_WIDTH,BACK_BITMAP_HEIGHT,hdcDeskTopWnd,WndRect.left,WndRect.top,SRCCOPY);
	ReleaseDC(hWnd,hdcDeskTopWnd);

	if(-48 < MoveX && MoveX < 48 || -48 < MoveY && MoveY < 48){
		BitBlt(hdcBackBitmap,-MoveX,-MoveY,WORK_BITMAP_WIDTH,WORK_BITMAP_HEIGHT,hdcWorkBitmap,0,0,SRCCOPY);
	}

	BitBlt(hdcWorkBitmap,0,0,WND_WIDTH,WND_HEIGHT,hdcBackBitmap,0,0,SRCCOPY);
	BitBlt(hdcWorkBitmap,0,0,WND_WIDTH,WND_HEIGHT,hdcErika,ErikaAnime[AnimePaturn][AnimeCounter],48,SRCAND);
	BitBlt(hdcWorkBitmap,0,0,WND_WIDTH,WND_HEIGHT,hdcErika,ErikaAnime[AnimePaturn][AnimeCounter],0,SRCPAINT);
	
	SetWindowPos(hWnd,NULL,(int)WndRect.left,(int)WndRect.top,WND_WIDTH,WND_HEIGHT,SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
	hdcWnd=GetWindowDC(hWnd);
	BitBlt(hdcWnd,0,0,WND_WIDTH,WND_HEIGHT,hdcWorkBitmap,0,0,SRCCOPY);
	ReleaseDC(hWnd,hdcWnd);
	
}

//��׸���Ұ��ݗp���
VOID CALLBACK TimerProc (HWND hWnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
	//����ݶ���
	if(WMPAINT_Flag){
		//�w�i����ײ���ݸޑ҂�
		switch(WMPAINT_Flag){
		case 1:
			WMPAINT_Flag = 2;
			break;
		case 2:{
			HDC hdcDeskTopWnd = GetDC(hDeskTopWnd);
			BitBlt(hdcBackBitmap,0,0,BACK_BITMAP_WIDTH,BACK_BITMAP_HEIGHT,hdcDeskTopWnd,(int)(WndRect.left),(int)(WndRect.top),SRCCOPY);
			ReleaseDC(hWnd,hdcDeskTopWnd);
			WMPAINT_Flag = 99;
			SetWindowPos(hWnd,NULL,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_SHOWWINDOW);
			}
			break;
		case 99:
			WMPAINT_Flag = 0;
			break;
		}
	}else{
		//�������ݶ���
		if(AnimeCounter >= ErikaAnimeCount[AnimePaturn]){
			AnimeCounter = 0;
			AnimePaturn = RandAnimeP(AnimePaturn);
		}else{
			++AnimeCounter;
		}
		//��׸��\��
			CharacterMove(hWnd,ErikaAnimeX[AnimePaturn][AnimeCounter],ErikaAnimeY[AnimePaturn][AnimeCounter]);
		}
}

//ܰ��p�ޯ�ϯ��ܰ��̈�쐬�֐�(�V�͗��P�����)
HBITMAP	CreateBitmapImage( HDC hDC, LONG lWidth, LONG lHeight ){
	//	�t���J���[�̃r�b�g�}�b�v�� CreateDIBSection() �֐��ō쐬
	BITMAPINFOHEADER	tblBmpHedr;
	tblBmpHedr.biSize          = sizeof( BITMAPINFOHEADER );
	tblBmpHedr.biWidth         = lWidth;
	tblBmpHedr.biHeight        = lHeight;
	tblBmpHedr.biPlanes        = 1;
	tblBmpHedr.biBitCount      = 24;
	tblBmpHedr.biCompression   = BI_RGB;
	tblBmpHedr.biSizeImage     = 0;
	tblBmpHedr.biXPelsPerMeter = 0;
	tblBmpHedr.biYPelsPerMeter = 0;
	tblBmpHedr.biClrUsed       = 0;
	tblBmpHedr.biClrImportant  = 0;
	
	HBITMAP	hBitmap = CreateDIBSection(
	
		hDC, (LPBITMAPINFO)&tblBmpHedr,
		DIB_RGB_COLORS, NULL, NULL, 0
	);
	
	//	�쐬���s
	if( hBitmap == NULL )
		return( NULL );
	
	//	�I�u�W�F�N�g�Ɋ֘A�t��
	HBITMAP	hBmpOld = (HBITMAP)SelectObject( hDC, hBitmap );
	
	//	���X�I������Ă����r�b�g�}�b�v�n���h����Ԃ�
	return( hBmpOld );
}

//Ҳ�ү���ޏ�������
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

	//��ݾ����ݏ���
	switch (message){
	case WM_CREATE:{
			//���Ķ���ƭ��쐬
			g_clsMainMenu.Create(hWnd);
			g_clsMainMenu.Append(MFT_STRING,ID_VER,"�ް�ޮݏ��");
			g_clsMainMenu.Append(MFT_SEPARATOR,0,NULL);
			g_clsMainMenu.Append(MFT_STRING,ID_END,"�޲�޲(�I��)");
			//����ڲ�쐬
			g_clsTaskTray.Create( hWnd, APPLI_TITLE_NAME, 
								LoadIcon( MainInst, MAKEINTRESOURCE(IDI_TASKICON)) );

			MouPoint.x = 0;
			MouPoint.y = 0;
			WndMovFlg = FALSE;
			AnimeCounter = 0;
			AnimePaturn  = ANIME_PA_PIKUN;

			WMPAINT_Flag = 99;
			hMainWnd = hWnd;

			//���������֐��̏�����
			srand((unsigned int)LOWORD(GetTickCount()));
			
			//�޽�į�߂�����قƗ̈���擾
			hDeskTopWnd = GetDesktopWindow();
			GetWindowRect(hDeskTopWnd,&DeskTopRect);
			ScrPointChk(&DeskTopRect,&WndRect);			//�\���ʒu����

			//���������ޯ�ϯ��ؿ���ǂݍ���
			hErikaBitmap = LoadBitmap(MainInst,MAKEINTRESOURCE(IDB_ERIKA));
			
			GetWindowRect(hWnd,&WndRect);

			//�����������޲���÷�Đݒ�
			hdcErika = CreateCompatibleDC(hdcMainWnd);
			SelectObject(hdcErika,hErikaBitmap);
			
			//�w�i�ޯ̧�i�[ܰ����޲���÷�č쐬
			hdcBackBitmap = CreateCompatibleDC(hdcMainWnd);
			CreateBitmapImage( hdcBackBitmap,BACK_BITMAP_HEIGHT,BACK_BITMAP_WIDTH);
			
			//�����pܰ��ޯ�ϯ�ߗ̈�쐬
			hdcWorkBitmap = CreateCompatibleDC(hdcMainWnd);
			CreateBitmapImage(hdcWorkBitmap,WORK_BITMAP_WIDTH,WORK_BITMAP_HEIGHT);

			//�ި̫���ޯ���׳��ފi�[
			HDC hdcDeskTopWnd = GetDC(hDeskTopWnd);
			BitBlt(hdcBackBitmap,0,0,BACK_BITMAP_WIDTH,BACK_BITMAP_HEIGHT,hdcDeskTopWnd,(int)(WndRect.left),(int)(WndRect.top),SRCCOPY);
			ReleaseDC(hWnd,hdcDeskTopWnd);
			SetTimer(hWnd,TIMER_ERIKA,100,(TIMERPROC)TimerProc);
		}
		break;
	
	case WM_ACTIVATE:
		if(LOWORD(wParam) == WA_INACTIVE){
			WndMovFlg = FALSE;
			if(hWnd == GetCapture()){
				if(hMouCapWnd == NULL){
					ReleaseCapture();
				}else{
					SetCapture(hMouCapWnd);
				}
			}
		}
		return 0;
	
	case WM_PAINT:
		switch(WMPAINT_Flag){
		case 0:
			SetWindowPos(hWnd,NULL,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_HIDEWINDOW);
			WMPAINT_Flag = 1;
			break;
		case 2:
			WMPAINT_Flag = 1;
			break;
		case 99:
			WMPAINT_Flag = 0;
			break;
		}
		break;

	//�ƭ�����ү����
	case WM_COMMAND:	//�ƭ�����
		switch(LOWORD(wParam)){
		case ID_VER:	//�ް�ޮݏ��\��
			DialogBox(MainInst,MAKEINTRESOURCE(IDD_VER),hWnd,(DLGPROC)VerDlgProc);
			AnimePaturn = ANIME_PA_RIBON;
			break;

		case ID_END:	//�I��
			DestroyWindow(hWnd);	//�e����޳�̔j��ү���ޔ��s
			break;
		}
		return 0;

	//ϳ�������Down������
	case WM_LBUTTONDOWN:
		GetWindowRect(hWnd,&WndRect);
	
		//ϳ���ү���ނ������
		WndMovFlg = TRUE;
		AnimePaturn  = ANIME_PA_JITA2;
		AnimeCounter = 0;
		MouPoint.y = (LONG)HIWORD(lParam);
		MouPoint.x = (LONG)LOWORD(lParam);
		ErikaSleepTimer = 0;
		hMouCapWnd = GetCapture();
		SetCursor(LoadCursor(MainInst,MAKEINTRESOURCE(IDC_HAND2)));
		hMouCapWnd = SetCapture(hWnd);

		return 0;

	//Mouse����Up������
	case WM_LBUTTONUP:
		WndMovFlg = FALSE;
		if(AnimePaturn <2){
			AnimePaturn  = ANIME_PA_PIKUN;
			AnimeCounter = 0;
		}
		if(hWnd == GetCapture()){
			if(hMouCapWnd == NULL){
				ReleaseCapture();
			}else{
				SetCapture(hMouCapWnd);
			}
			SetCursor(LoadCursor(MainInst,MAKEINTRESOURCE(IDC_HAND1)));
		}
		return 0;

	//ϳ����وړ�������
	case WM_MOUSEMOVE:
		//ϳ������Down����
		if(LOWORD(wParam) == MK_LBUTTON){
			if(WndMovFlg && hWnd == GetCapture()){	
				CharacterMove(
					hWnd,
					(LONG)LOWORD(lParam) - MouPoint.x,
					(LONG)HIWORD(lParam) - MouPoint.y
				);				
			}
		}
		return 0;
	
	//�E����Down������
	case WM_RBUTTONDOWN:
		g_clsMainMenu.Show();
		return 0;
	
	//������ٸد�������
	case WM_LBUTTONDBLCLK:
		WndMovFlg = FALSE;
		GetWindowRect(hWnd,&WndRect);
		if (LOWORD(lParam)<=14){
			if((WndRect.left+48) >= (DeskTopRect.right-24)){
				AnimePaturn  = ANIME_PA_IJI2;
			}else{
				AnimePaturn  = ANIME_PA_RHJUMP;
			}
		}else if(LOWORD(lParam)<=34){
			AnimePaturn  = ANIME_PA_HJUMP;
		}else{
			if((WndRect.left-48) <= -24){
				AnimePaturn  = ANIME_PA_IJI2;
			}else{
				AnimePaturn  = ANIME_PA_LHJUMP;
			}
		}
		AnimeCounter = 0;
		return 0;

	//����޳�j��ү����
	case WM_DESTROY:			
		KillTimer(hWnd,TIMER_ERIKA);
		ReleaseDC(hWnd,hdcErika);
		ReleaseDC(hWnd,hdcBackBitmap);
		g_clsTaskTray.Destory();			//����ڲ�p��
		//�����ݒ�̧�ٕۑ�
		GetWindowRect( hWnd, &g_clsNamakoIni.m_NamakoRect );
		g_clsNamakoIni.Save();
		PostQuitMessage(0);
		return 0;

	//��ʻ��ޕύX
	case WM_DISPLAYCHANGE:
		GetWindowRect(hDeskTopWnd,&DeskTopRect);	//�޽�į�߻��ގ擾
		ScrPointChk(&DeskTopRect,&WndRect);			//�\���ʒu����
		return 0;

	default:
		//����ڲ�����ү���ނ�������
		if( g_clsTaskTray.MessageID() == message ){
			ScrPointChk(&DeskTopRect,&WndRect);			//�\���ʒu����
			switch(lParam){
			case TM_LBUTTONUP: //ϳ�������Up
				SetWindowPos(hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
				return 0;

			case TM_LBUTTONDBLCLK:	//ϳ�����������ٸد�
				switch( AnimePaturn ){
				case 0:
					AnimePaturn = ANIME_PA_DANS;
					AnimeCounter = 0;
					return 0;

				case 4:
					AnimePaturn = ANIME_PA_PIKUN;
					AnimeCounter = 0;
					break;
				}
				return 0;

			case TM_RBUTTONUP:	//ϳ��E����Up
				SetForegroundWindow( hWnd );
				g_clsMainMenu.Show();
				return 0;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);	//��������Ȃ�ү���ނ̏���
}

//����ѱ�Ұ�������݊֐�
int RandAnimeP(int BaseAnimeP){
	
	int RetAP;
	int RandP = rand() & 0xff;

	//���˂������
	if(BaseAnimeP == ANIME_PA_NEGAERI || BaseAnimeP == ANIME_PA_SLEEP){
		if(RandP < 17){
			RetAP = ANIME_PA_NEGAERI;
		}else{
			RetAP = ANIME_PA_SLEEP;
		}
		
	}else if(ErikaSleepTimer >= SLEEP_TIME){
		RetAP = ANIME_PA_SLEEP;				
		
	}else{		
		switch(BaseAnimeP){
		case ANIME_PA_HJUMP:
		case ANIME_PA_LHJUMP:
		case ANIME_PA_RHJUMP:
			if(RandP < 86){
				RetAP = ANIME_PA_PIKUN;
			}else if(RandP < 170){
				RetAP = ANIME_PA_WAIT;					
			}else{
				RetAP = ANIME_PA_HJUMP;					
			}
			ErikaSleepTimer++;
			break;
		
		case ANIME_PA_IJI2:
			if(RandP < 128){
				RetAP = ANIME_PA_PIKUN;
			}else{
				RetAP = ANIME_PA_WAIT;					
			}
			ErikaSleepTimer++;
			break;

		case ANIME_PA_LSOWA2:
		case ANIME_PA_RSOWA2:
		case ANIME_PA_DANS:
		case ANIME_PA_FUKKIN:
			if(RandP < 50){
				RetAP = ANIME_PA_PIKUN;
			}else if(RandP < 100){
				RetAP = ANIME_PA_WAIT;					
			}else if(RandP < 130){
				RetAP = ANIME_PA_HJUMP;					
			}else{
				RetAP = BaseAnimeP;
			}
			ErikaSleepTimer++;
			break;
		
		case ANIME_PA_PIKUN:
		case ANIME_PA_WAIT:				
			if(RandP < 80){
				RetAP = ANIME_PA_PIKUN;
			}else if(RandP < 160){
				RetAP = ANIME_PA_WAIT;					
			}else if(RandP < 180){
				RetAP = ANIME_PA_HJUMP;					
			}else if(RandP < 200){
				RetAP = ANIME_PA_FUKKIN;
			}else if(RandP < 220){
				RetAP = ANIME_PA_LSOWA2;
			}else if(RandP < 240){
				RetAP = ANIME_PA_RSOWA2;
			}else{
				RetAP = ANIME_PA_DANS;					
			}
			ErikaSleepTimer++;
			break;
		
		case ANIME_PA_RIBON:
			ErikaSleepTimer++;
		case ANIME_PA_JITA2:
			RetAP = BaseAnimeP;
			break;
		}
	}
	
	return(RetAP);
}

BOOL ScrPointChk(RECT *MasRect,RECT *SlvRect){

	//�\��Y���W�����ް���Ă��Ȃ�������
	if(MasRect->right <= SlvRect->left)
		SlvRect->left = MasRect->right - (int)WND_HEIGHT;

	//�\��Y���W�����ް���Ă��Ȃ�������
	if(MasRect->bottom <= SlvRect->top)
		SlvRect->top = MasRect->bottom - (int)WND_WIDTH;

	return(TRUE);
}