/*------------------------------------------------
*  @file episode1S2.cpp
*  @brief ストーリーパート1_2
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
#include	"changeroom.h"
#include	"episode1S2.h"
#include	"episode1L.h"
#include	"mapdata_1.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h" 
#include	"mapdata_1.h"
#include	"HitJudgment.h"
#include	"camera.h"
#include	"Item.h"
#include	"UI.h"
#include	"enemy.h"
#include	"preparation.h"
#include	"Object.h"
#include	"Material.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int Skipflag2;			// スキップフラグ
int bi_alpha_ep1s2_fi;	// フェードイン
int bi_alpha_ep1s2_fo;	// フェードアウト

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 初期化
int IntoEpisode1S2() {
	Skipflag2 = 0;
	ScriptCreate();
	initblackin_ep1s2();
	return STATE_EP1STORY2;
}

// フェード初期化
void initblackin_ep1s2() {
	Skipflag2 = 0;
	bi_alpha_ep1s2_fi = 0;
	bi_alpha_ep1s2_fo = 255;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
int Episode1_Story2() {

	// ゲームの更新
	ScriptUpdate();

	// キー入力の更新
	InputMgrUpdate();

	// 特定のボタンが押されたらフラグを立てる
	if (gTrg & KEYIN_Q)
	{
		Skipflag2 = 1;
	}

	// スキップフラグがたったらストーリー終了
	if (Skipflag2 == 1)
	{
		Endflag += 1;
	}

	// ストーリーが終わったらフェードアウトしていく
	if (Endflag > 1)
	{
		bi_alpha_ep1s2_fi += 15;
	}

	if (Endflag == 30)
	{
		//ScriptDestroy();
		StopAllEpisodeMusic();
		bi_alpha_ep1s2_fi = 0;
		bi_alpha_ep1s2_fo = 0;
		return IntoEpisode1L_4();
	}
	return STATE_EP1STORY2;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// フェードアウト
void blackfadeout_ep1s2() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s2_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep1s2_fo > 0) {
		bi_alpha_ep1s2_fo -= 15;
	}

}

// フェードイン
void blackfadein_ep1s2() {

		SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s2_fi);
		DrawFBox(0, 0,
			1280, 720,
			GetColor(0, 0, 0));

}

// ストーリーパートの描画
void DrawEp1S2Process() {

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// 画面を消す
	HCls();

	// ゲームの描画
	ScriptRender();

	// フェードイン・アウト描画
	blackfadein_ep1s2();
	blackfadeout_ep1s2();

	// 更新
	Flip();

}