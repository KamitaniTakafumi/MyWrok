/*
 * @file Framework.cpp
 * @brief フレームワーク処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include	"library.h"
#include	"Framework.h"
#include	"time.h"
#include	"SceneMain.h"

struct Framework frm;	// フレームワーク情報

/*
*  @brief フレームワーク初期化
*  @param InitFPSMode FPSモード
*/
void InitFramework(int InitFPSMode)
{
	frm.FPSMode = InitFPSMode;

	frm.dwGameFrame = 0;

	frm.dwFrameTime = clock();
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
int UpdateFramework()
{
	static unsigned long dwSec = 0;
	unsigned long CurrentTime = clock() * 10;

	//	フレーム制限
	if (CurrentTime < frm.dwFrameTime + 167) return false;

	//	経過時間
	unsigned long dTime = CurrentTime - frm.dwFrameTime;
	if (dTime > 2000) frm.dwFrameTime = CurrentTime;

	//	スキップタイプ 
	switch (frm.FPSMode) {
	case FPS_60:	frm.bRender = TRUE;	break;
	case FPS_30:	if (frm.dwGameFrame & 0x01) frm.bRender = TRUE; else frm.bRender = FALSE;
		break;
	case FPS_FLEX:	if (dTime > 167 * 2) frm.bRender = FALSE; else frm.bRender = TRUE;
		break;
	}

	//	フレーム時間更新
	if (GetKeyState(VK_LCONTROL) < 0) frm.dwFrameTime += 300;
	frm.dwFrameTime += 167;

	//	秒間フレーム数保存
	if (dwSec < CurrentTime) {
		frm.dwFPS = frm.dwCurFrame;
		frm.dwRenderFPS = frm.dwRCurFrame;
		frm.dwCurFrame = frm.dwRCurFrame = 0;
		dwSec += 10000;
	}
	frm.dwCurFrame++;	//	フレーム数更新
	frm.dwGameFrame++;	//	ゲームフレーム数更新

	return true;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/
void RenderFramework()
{
	if (!frm.bRender) return;
	//	シーン開始
	BeginScene();
	//	シーン描画
	SceneRender();

	//	フレーム表示
#ifdef _DEBUG
	DrawString(10, 10, GetColor(255, 255, 255, 0), "FPS %03d / %03d\n", frm.dwFPS, frm.dwRenderFPS);
#endif

	// シーン終了
	EndScene();

	frm.dwRCurFrame++;	//	描画フレーム数更新
}
