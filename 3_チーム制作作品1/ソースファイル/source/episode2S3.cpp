/*------------------------------------------------
*  @file episode2S3.cpp
*  @brief ストーリーパート2_3
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
#include	"episode2S3.h"
#include	"episode2L.h"
#include	"mapdata_2.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int Skipflag6;			// スキップフラグ
int bi_alpha_ep2s3_fi;	// フェードイン
int bi_alpha_ep2s3_fo;	// フェードアウト

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 初期化
int IntoEpisode2S3() {
	Skipflag6 = 0;
	ScriptCreate();
	initblackin_ep2s3();
	return STATE_EP2STORY3;
}

// フェード初期化
void initblackin_ep2s3() {
	bi_alpha_ep2s3_fi = 0;
	bi_alpha_ep2s3_fo = 255;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
int Episode2_Story3() {
	// ゲームの更新
	ScriptUpdate();

	// キー入力の更新
	InputMgrUpdate();

	// 特定のボタンが押されたらフラグを立てる
	if (gTrg & KEYIN_Q) {
		Skipflag6 = 1;
	}

	// スキップフラグがたったらストーリー終了
	if (Skipflag6 == 1) {
		Endflag += 1;
	}

	// ストーリーが終わったらフェードアウトしていく
	if (Endflag > 1) {
		bi_alpha_ep2s3_fi += 15;
	}

	if (Endflag == 30) {
		StopAllEpisodeMusic();
		bi_alpha_ep2s3_fi = 0;
		bi_alpha_ep2s3_fo = 0;
		stateStage = STATE_EP2STAGE_3;
		return IntoEpisode2L_3_2();
	}

	return STATE_EP2STORY3;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// フェードアウト
void blackfadeout_ep2s3() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s3_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2s3_fo > 0) {
		bi_alpha_ep2s3_fo -= 15;
	}

}

// フェードイン
void blackfadein_ep2s3() {
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s3_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// ストーリーパートの描画
void DrawEp2S3Process() {

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// 画面を消す
	HCls();

	// ゲームの描画
	ScriptRender();

	// フェードイン・アウト描画
	blackfadein_ep2s3();
	blackfadeout_ep2s3();

	// 更新
	Flip();

}