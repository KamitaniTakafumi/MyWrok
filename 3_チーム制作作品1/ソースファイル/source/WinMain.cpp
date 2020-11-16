/*
** WinMain
*/

//
// include 部
//

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "amgame.h"
#include "game.h"
#include "AmHelper.h"




//
// WinMain(). プログラム起動関数
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	//
	// AMライブラリの初期化
	//

	SetGlobalMode( AMMODE_WINDOWED );	// これをコメントアウトするとフルスクリーンで動く
	SetAMDebugMode(AMDEBUG_ALL_OFF);
	SetGraphMode( DISP_W, DISP_H, 32 );
	if ( !InitGraph( hInstance ) ) 
	{	// ライブラリ初期化失敗
		return -1;
	}
	if (InitSound(0) < 0)
	{	// サウンド初期化失敗
		EndGraph();
		return -1;
	}

	srand( (unsigned int)time( NULL ) );


	//
	// プログラムの初期化
	//

	AppInit();




	// １フレームループ /////////////////////////////
	while( ProcessEvent() )
	{
		//
		// 入力
		//

		FrameInput();


		//
		// 計算・処理
		//

		FrameProcess();


		//
		// 描画
		//

		FrameDraw();

	}

	//
	// プログラムの解放
	//

	AppRelease();


	//
	// AMライブラリの解放
	//

	EndGraph();

	return 0;
}
