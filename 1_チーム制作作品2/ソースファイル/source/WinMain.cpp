/*
 * @file WinMain.cpp
 * @brief エントリーポイント処理
 * @author 上谷恭史
 * @date 2020/02/26
 */

#include "library.h"
#include "game.h"
#include "Framework.h"
#include "dslib.h"
#include "player.h"
#include "SceneMain.h"
#include "object.h"

/*
*  @brief WinMain
*  @param hInstance インスタンス
*  @param hPrevInstance 未使用(常にNULL)
*  @param lpCmdLine コマンドライン引数
*  @param nCmdShow ウィンドウの表示方法
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	MSG		msg;	// メッセージ

	// パッドの接続確認
	ConnectionPad();

	// ウインドウ作成
	InitWnd(hInstance, DISP_W, DISP_H, "グリスト");

	// ダイレクト3Dの初期化関数を呼ぶ
	if (!InitApp()) 
	{ 
		return false; 
	}

	// ゲームの初期化
	AppInit();

	//	メインループ
	for (;;) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0)) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			if (UpdateFramework())
			{
				// 入力
				FrameInput();

				// 処理
				FrameProcess();

				// 描画
				FrameDraw();
			}
		}
	}

	//	全解放	
	ReleaseD3D();
	ReleaseFont();
	ReleasePlayer();
	ReleaseObject();
	DSoundRelease();

	return 0;
}
