/*------------------------------------------------
*  @file end.cpp
*  @brief エンドロール処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ヘッダーファイルのインクルード
------------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"global.h"
#include	"end.h"
#include	"changeroom.h"
#include	"title.h"
#include	"HitJudgment.h"
#include	"episode1L.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int cgBg;			// 背景
int cgStaffrole;	// スタッフロール
int countend;		// スクロールの時間

// エンドロール情報
struct END end;

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
int IntoEnd() {
	end.x = 0;
	end.y = 720;
	end.w = 1280;
	end.h = 5400;
	end.vx = 0;
	end.vy = 2;
	end.use = 1;
	countend = 0;
	fadeout = 90;

	cgBg = LoadTexture("res/endbg2.jpg");
	cgStaffrole = LoadTexture("res/staffrole.png");

	initblackin_ep3();

	PlayMemLoop(bgmEnd);			  // BGM再生スタート
	stateStage = STATE_END;
	return STATE_END;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
void EndRole() {
	// スタッフロールをスクロールする
	end.y -= end.vy;
	countend += end.vy;

	// 最後までスクロールが終わったらタイトルに戻る
	if (countend >= 6800) {
		end.use = 0;
		stateStage = STATE_TITLE;
		clearflag = 0;
		bgstage = STATE_EP1STAGE;
		bgstage2 = STATE_EP2STAGE1_1;
		StopPlayMem(bgmEnd);			  // BGM再生スタート
		PlayMemLoop(bgmTitle);			  // BGM再生スタート
		intoTitle();
	}
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/
void DrawEnd() {

	// 画面を消す
	HCls();

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// countが終わるまで描画
	if (end.use = 1) {
		DrawMem(0, 0, cgBg);
		SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
		DrawFBox(0, 0, DISP_W, DISP_H, GetColor(255, 255, 255));
		SetDrawMode(AMDRAW_NOBLEND, 0);
		DrawMemTh(end.x, end.y, cgStaffrole);
	}

	// ブラックフェードアウト
	blackfadein_ep3();
	blackfadeout_ep3();
	operationfadeout();

	Flip();
}
