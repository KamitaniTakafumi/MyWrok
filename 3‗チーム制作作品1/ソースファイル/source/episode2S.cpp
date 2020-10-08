/*------------------------------------------------
*  @file episode2S.cpp
*  @brief ストーリーパート2_1
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
#include	"episode2S.h"
#include	"episode2L.h"
#include	"mapdata_1.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int Skipflag4;			// スキップフラグ
int bi_alpha_ep2s_fi;	// フェードイン
int bi_alpha_ep2s_fo;	// フェードアウト

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 初期化
int IntoEpisode2S()
{
	Skipflag4 = 0;
	ScriptCreate();
	initblackin_ep2s();
	return STATE_EP2STORY;
}

// フェード初期化
void initblackin_ep2s()
{
	bi_alpha_ep2s_fi = 0;
	bi_alpha_ep2s_fo = 255;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
int Episode2_Story()
{

	// ゲームの更新
	ScriptUpdate();

	// キー入力の更新
	InputMgrUpdate();

	// 特定のボタンが押されたらフラグを立てる
	if (gTrg & KEYIN_Q)
	{
		Skipflag4 = 1;
	}

	// スキップフラグがたったらストーリー終了
	if (Skipflag4 == 1)
	{
		Endflag += 1;
	}

	// ストーリーが終わったらフェードアウトしていく
	if (Endflag > 1)
	{
		bi_alpha_ep2s_fi += 15;
	}

	if (Endflag == 30)
	{
		StopAllEpisodeMusic();
		bi_alpha_ep2s_fi = 0;
		bi_alpha_ep2s_fo = 0;
		switch (bgstage2)
		{
		case STATE_EP2STAGE1_1:
			required_count = 0;
			wallflag = 2;
			//required_count = 8;		// 壁を消す(開発用)
			stateStage = STATE_EP2STAGE1_1;		// 1章のステージに飛ぶ(開発用)
			break;
		case STATE_EP2STAGE1_2:
			required_count = 0;
			wallflag = 2;
			stateStage = STATE_EP2STAGE1_1;		// 1章のステージに飛ぶ(開発用)
			break;
		case STATE_EP2STAGE1_3:
			required_count = 6;
			wallflag = 4;
			stateStage = STATE_EP2STAGE1_3;		// 1章のステージに飛ぶ(開発用)
			break;
		case STATE_EP2STAGE2_1:
			required_count = 3;
			wallflag = 3;
			stateStage = STATE_EP2STAGE2_1;	// 2ステージに移動(開発用)
			break;
		case STATE_EP2STAGE2_2:
			required_count = 8;
			wallflag = 5;
			stateStage = STATE_EP2STAGE2_2;	// 2ステージに移動(開発用)
			break;
		case STATE_EP2STAGE_3:
			required_count = 8;
			wallflag = 5;
			stateStage = STATE_EP2STAGE2_2;	// 3ステージに移動(開発用)
			break;
		}
		return IntoEpisode2L();
	}

	return STATE_EP2STORY;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// フェードアウト
void blackfadeout_ep2s()
{

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2s_fo > 0)
	{
		bi_alpha_ep2s_fo -= 15;
	}

}

// フェードイン
void blackfadein_ep2s()
{
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// ストーリーパートの描画
void DrawEp2SProcess()
{

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// 画面を消す
	HCls();

	// ゲームの描画
	ScriptRender();

	// フェードイン・アウト描画
	blackfadein_ep2s();
	blackfadeout_ep2s();

	// 更新
	Flip();

}