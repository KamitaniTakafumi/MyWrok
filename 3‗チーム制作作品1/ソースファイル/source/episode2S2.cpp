/*------------------------------------------------
*  @file episode2S2.cpp
*  @brief ストーリーパート2_2
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
#include	"episode2S2.h"
#include	"episode2L.h"
#include	"mapdata_2.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int Skipflag5;			// スキップフラグ
int bi_alpha_ep2s2_fi;	// フェードイン
int bi_alpha_ep2s2_fo;	// フェードアウト

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 初期化
int IntoEpisode2S2()
{
	Skipflag5 = 0;
	ScriptCreate();
	initblackin_ep2s2();
	return STATE_EP2STORY2;
}

// フェード初期化
void initblackin_ep2s2() {
	Skipflag5 = 0;
	bi_alpha_ep2s2_fi = 0;
	bi_alpha_ep2s2_fo = 255;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
int Episode2_Story2() {
	// ゲームの更新
	ScriptUpdate();

	// キー入力の更新
	InputMgrUpdate();

	// 特定のボタンが押されたらフラグを立てる
	if (gTrg & KEYIN_Q) {
		Skipflag5 = 1;
	}

	// スキップフラグがたったらストーリー終了
	if (Skipflag5 == 1) {
		Endflag += 1;
	}

	// ストーリーが終わったらフェードアウトしていく
	if (Endflag > 1) {
		bi_alpha_ep2s2_fi += 15;
	}

	if (Endflag == 30) {
		StopAllEpisodeMusic();
		bi_alpha_ep2s2_fi = 0;
		bi_alpha_ep2s2_fo = 0;
		stateStage = STATE_EP2STAGE_3;
		return IntoEpisode2L_3_1();
	}

		return STATE_EP2STORY2;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// フェードアウト
void blackfadeout_ep2s2()
{

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s2_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2s2_fo > 0)
	{
		bi_alpha_ep2s2_fo -= 15;
	}

}

// フェードイン
void blackfadein_ep2s2()
{
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s2_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// ストーリーパートの描画
void DrawEp2S2Process()
{

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// 画面を消す
	HCls();

	// ゲームの描画
	ScriptRender();

	// フェードイン・アウト描画
	blackfadein_ep2s2();
	blackfadeout_ep2s2();

	// 更新
	Flip();

}