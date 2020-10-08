/*------------------------------------------------
*  @file episode1S.cpp
*  @brief ストーリーパート1_1
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
#include	"episode1S.h"
#include	"episode1L.h"
#include	"mapdata_1.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"
#include	"recipe.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int Skipflag;			// スキップフラグ
int bi_alpha_ep1s_fi;	// フェードイン
int bi_alpha_ep1s_fo;	// フェードアウト

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 初期化
int IntoEpisode1S() {
	Skipflag = 0;
	ScriptCreate();
	initblackin_ep1s();
	return STATE_EP1STORY;
}

// フェード初期化
void initblackin_ep1s() {
	bi_alpha_ep1s_fi = 0;
	bi_alpha_ep1s_fo = 255;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
int Episode1_Story() {

	// ゲームの更新
	ScriptUpdate();

	// キー入力の更新
	InputMgrUpdate();

	// 特定のボタンが押されたらフラグを立てる
	if (gTrg & KEYIN_Q){
		Skipflag = 1;
	}

	// スキップフラグがたったらストーリー終了
	if (Skipflag == 1)
	{
		Endflag += 1;
	}

	// ストーリーが終わったらフェードアウトしていく
	if (Endflag > 1) {
		bi_alpha_ep1s_fi += 15;
	}

	if (Endflag == 30) {
		ScriptDestroy();
		StopAllEpisodeMusic();
		bi_alpha_ep1s_fi = 0;
		bi_alpha_ep1s_fo = 0;
		switch (bgstage) {
		case STATE_EP1STAGE:
			required_count = 0;
			wallflag = 0;
			stateStage = STATE_EP1STAGE;	// 1章のステージに飛ぶ
			break;
		case STATE_EP1STAGE_2:
			required_count = 0;
			wallflag = 0;
			stateStage = STATE_EP1STAGE_2;	// 2ステージに移動
			break;
		case STATE_EP1STAGE_3:
			required_count = 2;
			wallflag = 1;
			stateStage = STATE_EP1STAGE_3;	// 3ステージに移動
			break;
		case STATE_EP1STAGE_4:
			required_count = 4;
			wallflag = 2;
			stateStage = STATE_EP1STAGE_3;
			break;
		}
		return IntoEpisode1L();
	}

	return STATE_EP1STORY;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// テキスト描画
void DrawStoryTexte1() {
	DrawString((DISP_W / 2), 100, "第1章", GetColor(0, 0, 0));
}

// フェードアウト
void blackfadeout_ep1s() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep1s_fo > 0) {
		bi_alpha_ep1s_fo -= 15;
	}

}

// フェードイン
void blackfadein_ep1s() {
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// ストーリーパートの描画
void DrawEp1SProcess() {

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// 画面を消す
	HCls();

	// ゲームの描画
	ScriptRender();

	// フェードイン・アウト描画
	blackfadein_ep1s();
	blackfadeout_ep1s();

	// 更新
	Flip();

}