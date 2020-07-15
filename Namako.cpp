//ﾃﾞｽｸﾄｯﾌﾟなま子さん
//Version 1.01
//
//Programaer		草薙 雀っ子
//Special Thanks	天河 龍輝
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

//ｷｬﾗｸﾀ名
#define APPLI_TITLE_NAME	"なま子さん"

#define TIMER_ERIKA	1		//ﾀｲﾏｰID

#define	WND_HEIGHT	48		//ｳｲﾝﾄﾞｳの基本縦サイズ
#define WND_WIDTH	48		//ｳｲﾝﾄﾞｳの基本横サイズ

#define BACK_BITMAP_HEIGHT	48 
#define BACK_BITMAP_WIDTH	48

#define WORK_BITMAP_WIDTH	48
#define WORK_BITMAP_HEIGHT	48

#define ANIME_PA_PIKUN		0		//ﾉｰﾏﾙ
#define ANIME_PA_JITA2		1		//ｼﾞﾀｼﾞﾀ
#define ANIME_PA_HJUMP		2		//HIｼﾞｬﾝﾌﾟ
#define ANIME_PA_NEGAERI	3		//ねがえり～
#define ANIME_PA_DANS		4		//ﾀﾞﾝｽ
#define ANIME_PA_RIBON		5		//ﾘﾎﾞﾝ
#define ANIME_PA_LHJUMP		6		//左ｼﾞｬﾝﾌﾟ
#define ANIME_PA_RHJUMP		7		//右ｼﾞｬﾝﾌﾟ
#define ANIME_PA_IJI2		8		//ｲｼﾞｲｼﾞ
#define ANIME_PA_WAIT		9		//じぃ～～～
#define ANIME_PA_FUKKIN		10		//ふっきん
#define ANIME_PA_SLEEP  	11		//ｸﾞｳｸﾞｳ
#define ANIME_PA_LSOWA2		12		//(左)そわそわ
#define ANIME_PA_RSOWA2		13		//(右)そわそわ

#define SLEEP_TIME	3600		//約１時間

#define ANIME_PATURN		14
#define ANIME_TI_SLEEP		0
#define	ANIME_TI_COUNT		1

/*
struct CHARCTER_STRUCT {
	HDC		hDC;						//ﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ						
	HWND	hBitmap;					//ｷｬﾗｸﾀﾋﾞｯﾄﾏｯﾌﾟ
	int		Mode;						//感情ﾓｰﾄﾞ
	int		AnimeCounter;				//ｱﾆﾒｰｼｮﾝｶｳﾝﾀｰ
	int		PaturnType;					//ｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝ
	int		Paturn[ANIME_PATRUN][12];	//ｱﾆﾒﾊﾟﾀｰﾝ
	int		MoveX[ANIME_PATRUN][12];	//移動X座標
	int		MoveY[ANIME_PATRUN][12];	//移動Y座標
	int		AnimeCount[ANIME_PATRUN];	//ｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝｶｳﾝﾄ
	int		TimeCount[1];				//寝るまでｶｳﾝﾀ=0
}
*/

HINSTANCE	MainInst;
HWND		hDeskTopWnd;	//ﾃﾞｽｸﾄｯﾌﾟのﾊﾝﾄﾞﾙ
HWND		hMainWnd;		//ﾒｲﾝｳｲﾝﾄﾞｳのﾊﾝﾄﾞﾙ
HWND		hMouCapWnd;		//ﾏｳｽをｷｬﾌﾟﾁｬする前にｷｬﾌﾟﾁｬしていたｱﾌﾟﾘのﾊﾝﾄﾞﾙ
HWND		VerWnd;			//ﾊﾞｰｼﾞｮﾝﾀﾞｲｱﾛｸﾞのﾊﾝﾄﾞﾙ
HBITMAP		hErikaBitmap;	//絵理香のﾋﾞｯﾄﾏｯﾌﾟﾊﾟﾀｰﾝ
HBITMAP		hBackBitmap;	//背景用ﾜｰｸﾋﾞｯﾄﾏｯﾌﾟ

HDC		hdcErika;			//絵理香のﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ
HDC		hdcMainWnd;			//ﾒｲﾝｳｲﾝﾄﾞのﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ
HDC		hdcBackBitmap;		//背景画像退避ﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ
HDC		hdcWorkBitmap;		//合成用ﾜｰｸﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ

RECT	WndRect;
RECT	DeskTopRect;		//ﾃﾞｽｸﾄｯﾌﾟのｻｲｽﾞ

//ｸﾞﾛｰﾊﾞﾙｸﾗｽ
PopupMenu	g_clsMainMenu;	//右ｸﾘｯｸﾒﾆｭｰ
TaskTray	g_clsTaskTray;	//ﾀｽｸﾄﾚｲ
IniFile		g_clsNamakoIni;	//なま子さん初期設定

int AnimeCounter;			//ｱﾆﾒｰｼｮﾝ表示ﾊﾟﾀｰﾝのｶｳﾝﾀ
int AnimePaturn;			//表示するｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝ番号

//ｱﾆﾒﾊﾟﾀｰﾝ数
int ErikaAnimeCount[ANIME_PATURN]	  = {9,11, 8,11,7,8,8,8,5,11,11,11,10,10};		

//ｱﾆﾒﾊﾟﾀｰﾝ画像座標
int ErikaAnime[ANIME_PATURN][12] = {
							  0,  0,  0,  0,  0,  0,  0, 49, 97, 49,  0,  0,	//ノ～マル
							  0, 49, 97, 49,  0, 49, 97, 49,  0, 49, 97, 49,	//ジタジタ
                              0, 97, 49, 49, 49, 97, 97,  0,  0,  0,  0,  0,	//ぴょん
							145,145,145,145,145,145,145,145,145,193,241,193,	//寝返り
							432,432,480,480,432,432,528,528,  0,  0,  0,  0,	//ダンス
							288,288,288,288,288,288,384,336,384,  0,  0,  0,	//☆				
                              0, 97, 49, 49, 49, 97, 97,  0,  0,  0,  0,  0,	//ぴょん（左）
                              0, 97, 49, 49, 49, 97, 97,  0,  0,  0,  0,  0,	//ぴょん（右）
							  0,576,576,  0,576,576,  0,  0,  0,  0,  0,  0,	//いじいじ
							  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,	//じぃ～っとしてる
							432,432,672,672,480,480,624,624,480,480,672,672,	//ふっきん
							145,145,145,145,145,145,145,145,145,145,145,145,	//ぐうぐう
							  0, 49,  0, 49,  0,  0, 49,  0, 49,  0,  0,  0,	//(左)そわそわ	
							  0, 49,  0, 49,  0,  0, 49,  0, 49,  0,  0,  0		//(右)そわそわ
							};

//ｱﾆﾒｰｼｮﾝX座標
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
//ｱﾆﾒｰｼｮﾝY座標
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

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);			//ﾒｲﾝｳｲﾝﾄﾞｳ関数
BOOL ScrPointChk(RECT *,RECT *);							//ｽｸﾘｰﾝ表示座標ﾁｪｯｸ関数
int RandAnimeP(int);										//ﾗﾝﾀﾞﾑｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝ関数

//メイン(ｱﾌﾟﾘ登録処理)
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE, LPTSTR lpCmdLine, int showCmd)
{
	static char psAppName[] = APPLI_TITLE_NAME;
	MSG msg;
	HWND hWnd;

	memset(&WndRect,0x00,sizeof(RECT));

	//クラスの設定
	WNDCLASS	wndClass;
	memset(&wndClass,0x00,sizeof(WNDCLASS));
	wndClass.lpszClassName	= psAppName;
	wndClass.lpfnWndProc	= WndProc;
	wndClass.style			= CS_DBLCLKS;		//ﾀﾞﾌﾞﾙｸﾘｯｸﾒｯｾｰｼﾞ有効化
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.lpszMenuName	= 0;
	wndClass.hbrBackground	= NULL;
	wndClass.hInstance		= hInst;
	wndClass.hIcon			= LoadIcon( hInst, MAKEINTRESOURCE(IDI_MAIN) );
	wndClass.hCursor		= LoadCursor( hInst, MAKEINTRESOURCE(IDC_HAND1) );

	MainInst = hInst;

	RegisterClass(&wndClass);

	//初期設定ﾌｧｲﾙ読込
	g_clsNamakoIni.Create( hInst, INIT_FILE_NAME );
	g_clsNamakoIni.Load();
	//ﾒｲﾝｳｲﾝﾄﾞ作成
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

//ｷｬﾗｸﾀ表示関数
//HWND	hWnd	:表示するｳｲﾝﾄﾞｳのﾊﾝﾄﾞﾙ
//LONG	MoveX	:移動するX座標の相対距離
//LONG	MoveY	:移動するY座標の相対距離
void CharacterMove(HWND hWnd,LONG MoveX,LONG MoveY){
	
	HDC hdcWnd;

	BitBlt(hdcWorkBitmap,0,0,BACK_BITMAP_WIDTH,BACK_BITMAP_HEIGHT,hdcBackBitmap,0,0,SRCCOPY);

	WndRect.top += MoveY;		
	WndRect.left += MoveX;
	
	//ﾃﾞｨﾌｫﾙﾄﾊﾞｯｸｸﾞﾗｳﾝﾄﾞｶｯﾊﾟﾗｲ
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

//ｷｬﾗｸﾀｱﾆﾒｰｼｮﾝ用ﾀｲﾏ
VOID CALLBACK TimerProc (HWND hWnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
	//ﾊﾟﾀｰﾝｶｳﾝﾄ
	if(WMPAINT_Flag){
		//背景ｶｯﾊﾟﾗｲﾀｲﾐﾝｸﾞ待ち
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
		//ｷｬﾗﾊﾟﾀｰﾝｶｳﾝﾄ
		if(AnimeCounter >= ErikaAnimeCount[AnimePaturn]){
			AnimeCounter = 0;
			AnimePaturn = RandAnimeP(AnimePaturn);
		}else{
			++AnimeCounter;
		}
		//ｷｬﾗｸﾀ表示
			CharacterMove(hWnd,ErikaAnimeX[AnimePaturn][AnimeCounter],ErikaAnimeY[AnimePaturn][AnimeCounter]);
		}
}

//ﾜｰｸ用ﾋﾞｯﾄﾏｯﾌﾟﾜｰｸ領域作成関数(天河龍輝さん作)
HBITMAP	CreateBitmapImage( HDC hDC, LONG lWidth, LONG lHeight ){
	//	フルカラーのビットマップを CreateDIBSection() 関数で作成
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
	
	//	作成失敗
	if( hBitmap == NULL )
		return( NULL );
	
	//	オブジェクトに関連付け
	HBITMAP	hBmpOld = (HBITMAP)SelectObject( hDC, hBitmap );
	
	//	元々選択されていたビットマップハンドルを返す
	return( hBmpOld );
}

//ﾒｲﾝﾒｯｾｰｼﾞ処理部分
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

	//ｷｬﾝｾﾙﾎﾞﾀﾝ処理
	switch (message){
	case WM_CREATE:{
			//ｼｮｰﾄｶｯﾄﾒﾆｭｰ作成
			g_clsMainMenu.Create(hWnd);
			g_clsMainMenu.Append(MFT_STRING,ID_VER,"ﾊﾞｰｼﾞｮﾝ情報");
			g_clsMainMenu.Append(MFT_SEPARATOR,0,NULL);
			g_clsMainMenu.Append(MFT_STRING,ID_END,"ﾊﾞｲﾊﾞｲ(終了)");
			//ﾀｽｸﾄﾚｲ作成
			g_clsTaskTray.Create( hWnd, APPLI_TITLE_NAME, 
								LoadIcon( MainInst, MAKEINTRESOURCE(IDI_TASKICON)) );

			MouPoint.x = 0;
			MouPoint.y = 0;
			WndMovFlg = FALSE;
			AnimeCounter = 0;
			AnimePaturn  = ANIME_PA_PIKUN;

			WMPAINT_Flag = 99;
			hMainWnd = hWnd;

			//乱数発生関数の初期化
			srand((unsigned int)LOWORD(GetTickCount()));
			
			//ﾃﾞｽｸﾄｯﾌﾟのﾊﾝﾄﾞﾙと領域を取得
			hDeskTopWnd = GetDesktopWindow();
			GetWindowRect(hDeskTopWnd,&DeskTopRect);
			ScrPointChk(&DeskTopRect,&WndRect);			//表示位置ﾁｪｯｸ

			//ｷｬﾗﾊﾟﾀｰﾝﾋﾞｯﾄﾏｯﾌﾟﾘｿｰｽ読み込み
			hErikaBitmap = LoadBitmap(MainInst,MAKEINTRESOURCE(IDB_ERIKA));
			
			GetWindowRect(hWnd,&WndRect);

			//ｷｬﾗﾊﾟﾀｰﾝﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ設定
			hdcErika = CreateCompatibleDC(hdcMainWnd);
			SelectObject(hdcErika,hErikaBitmap);
			
			//背景ﾊﾞｯﾌｧ格納ﾜｰｸﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ作成
			hdcBackBitmap = CreateCompatibleDC(hdcMainWnd);
			CreateBitmapImage( hdcBackBitmap,BACK_BITMAP_HEIGHT,BACK_BITMAP_WIDTH);
			
			//合成用ﾜｰｸﾋﾞｯﾄﾏｯﾌﾟ領域作成
			hdcWorkBitmap = CreateCompatibleDC(hdcMainWnd);
			CreateBitmapImage(hdcWorkBitmap,WORK_BITMAP_WIDTH,WORK_BITMAP_HEIGHT);

			//ﾃﾞｨﾌｫﾙﾄﾊﾞｯｸｸﾞﾗｳﾝﾄﾞ格納
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

	//ﾒﾆｭｰ処理ﾒｯｾｰｼﾞ
	case WM_COMMAND:	//ﾒﾆｭｰ処理
		switch(LOWORD(wParam)){
		case ID_VER:	//ﾊﾞｰｼﾞｮﾝ情報表示
			DialogBox(MainInst,MAKEINTRESOURCE(IDD_VER),hWnd,(DLGPROC)VerDlgProc);
			AnimePaturn = ANIME_PA_RIBON;
			break;

		case ID_END:	//終了
			DestroyWindow(hWnd);	//親ｳｲﾝﾄﾞｳの破棄ﾒｯｾｰｼﾞ発行
			break;
		}
		return 0;

	//ﾏｳｽ左ﾎﾞﾀﾝDown時処理
	case WM_LBUTTONDOWN:
		GetWindowRect(hWnd,&WndRect);
	
		//ﾏｳｽのﾒｯｾｰｼﾞをｷｬﾌﾟﾁｬｰ
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

	//MouseﾎﾞﾀﾝUp時処理
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

	//ﾏｳｽｶｰｿﾙ移動時処理
	case WM_MOUSEMOVE:
		//ﾏｳｽﾎﾞﾀﾝﾀDownﾁｪｯｸ
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
	
	//右ﾎﾞﾀﾝDown時処理
	case WM_RBUTTONDOWN:
		g_clsMainMenu.Show();
		return 0;
	
	//左ﾀﾞﾌﾞﾙｸﾘｯｸ時処理
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

	//ｳｲﾝﾄﾞｳ破棄ﾒｯｾｰｼﾞ
	case WM_DESTROY:			
		KillTimer(hWnd,TIMER_ERIKA);
		ReleaseDC(hWnd,hdcErika);
		ReleaseDC(hWnd,hdcBackBitmap);
		g_clsTaskTray.Destory();			//ﾀｽｸﾄﾚｲ廃棄
		//初期設定ﾌｧｲﾙ保存
		GetWindowRect( hWnd, &g_clsNamakoIni.m_NamakoRect );
		g_clsNamakoIni.Save();
		PostQuitMessage(0);
		return 0;

	//画面ｻｲｽﾞ変更
	case WM_DISPLAYCHANGE:
		GetWindowRect(hDeskTopWnd,&DeskTopRect);	//ﾃﾞｽｸﾄｯﾌﾟｻｲｽﾞ取得
		ScrPointChk(&DeskTopRect,&WndRect);			//表示位置ﾁｪｯｸ
		return 0;

	default:
		//ﾀｽｸﾄﾚｲからのﾒｯｾｰｼﾞかをﾁｪｯｸ
		if( g_clsTaskTray.MessageID() == message ){
			ScrPointChk(&DeskTopRect,&WndRect);			//表示位置ﾁｪｯｸ
			switch(lParam){
			case TM_LBUTTONUP: //ﾏｳｽ左ﾎﾞﾀﾝUp
				SetWindowPos(hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
				return 0;

			case TM_LBUTTONDBLCLK:	//ﾏｳｽ左ﾎﾞﾀﾝﾀﾞﾌﾞﾙｸﾘｯｸ
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

			case TM_RBUTTONUP:	//ﾏｳｽ右ﾎﾞﾀﾝUp
				SetForegroundWindow( hWnd );
				g_clsMainMenu.Show();
				return 0;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);	//処理されないﾒｯｾｰｼﾞの処理
}

//ﾗﾝﾀﾞﾑｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝ関数
int RandAnimeP(int BaseAnimeP){
	
	int RetAP;
	int RandP = rand() & 0xff;

	//おねんねﾁｪｯｸ
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

	//表示Y座標がｵｰﾊﾞｰしていないかﾁｪｯｸ
	if(MasRect->right <= SlvRect->left)
		SlvRect->left = MasRect->right - (int)WND_HEIGHT;

	//表示Y座標がｵｰﾊﾞｰしていないかﾁｪｯｸ
	if(MasRect->bottom <= SlvRect->top)
		SlvRect->top = MasRect->bottom - (int)WND_WIDTH;

	return(TRUE);
}