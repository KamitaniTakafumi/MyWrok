/*------------------------------------------------
*  @file episode2S4.cpp
*  @brief ストーリーパート2_4
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ヘッダーファイルのインクルード
------------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include <stdint.h>
#include <crtdbg.h>
#include	"script_parser.h"
#include "input_manager.h"
#include "camera.h"
#include	"game.h"
#include	"episode2S4.h"
#include	"episode2L.h"
#include	"mapdata_2.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"
#include	"end.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int Skipflag7;			// スキップフラグ
int bi_alpha_ep2s4_fi;	// フェードイン
int bi_alpha_ep2s4_fo;	// フェードアウト

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 初期化
int IntoEpisode2S4()
{
	Skipflag7 = 0;
	ScriptCreate();
	initblackin_ep2s4();
	return STATE_EP2STORY4;
}

// フェード初期化
void initblackin_ep2s4()
{
	bi_alpha_ep2s4_fi = 0;
	bi_alpha_ep2s4_fo = 255;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
int Episode2_Story4()
{
	// ゲームの更新
	ScriptUpdate();

	// キー入力の更新
	InputMgrUpdate();

	// ストーリーが終わったらフェードアウトしていく
	if (Endflag > 1)
	{
		bi_alpha_ep2s4_fi += 5;
	}

	if (Endflag == 60)
	{
		StopAllEpisodeMusic();
		return IntoEnd();
	}

	return STATE_EP2STORY4;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// フェードアウト
void blackfadeout_ep2s4()
{

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s4_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2s4_fo > 0)
	{
		bi_alpha_ep2s4_fo -= 15;
	}

}

// フェードイン
void blackfadein_ep2s4()
{
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s4_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// ストーリーパートの描画
void DrawEp2S4Process()
{

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// 画面を消す
	HCls();

	// ゲームの描画
	ScriptRender();

	// フェードイン・アウト描画
	blackfadein_ep2s4();
	blackfadeout_ep2s4();

	// 更新
	Flip();

}