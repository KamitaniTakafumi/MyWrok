/*------------------------------------------------
*  @file gameover.cpp
*  @brief ゲームオーバー処理
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
#include	"gameover.h"
#include	"global.h"
#include	"HitJudgment.h"
#include	"script_parser.h"
#include	"title.h"
#include	"enemy.h"
#include	"episode1L.h"
#include	"episode2L.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// 画像データ

int cgGameOver;			// ゲームオーバー
int cgBack;				// バック

int GameOverAlpha;		// α値(ゲームオーバー)
int GameOverAlpha2;		// α値(バック)

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
void LoadCgGameOver() {
	cgGameOver = LoadTexture("res/GameOver.png");
	cgBack = LoadTexture("res/back.png");
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

// ゲームオーバーになったらタイトルに戻す
void GameOverProcess() {
	// α値をプラス
	if (GameOverAlpha < 200) {

		GameOverAlpha += 5;

	}

	// ゲームオーバー
	if (GameOverAlpha >= 200) {
		GameOverAlpha2 += 15;
		if (GameOverAlpha2 > 255) {
			// コンティニューボタンを押した
			if (gTrg & KEYIN_X) {
				// そのステージから始める
				GameOverAlpha = 0;
				StopPlayMem(seDead);
				if (continueflag == 1) {
					stateStage = bgstage;
					if (stateStage == STATE_EP1STAGE_4) {
						stateStage = STATE_EP1STAGE_3;
					}
					IntoEpisode1L_Re();
				}
				else if (continueflag == 2) {
					stateStage = bgstage2;
					if (stateStage == STATE_EP2STAGE1_2) {
						stateStage = STATE_EP2STAGE1_1;
					}
					if (stateStage == STATE_EP2STAGE_3) {
						stateStage = STATE_EP2STAGE2_2;
					}
					IntoEpisode2L_Re();
				}
			}
			// 終了ボタンを押した
			if (gTrg & KEYIN_Z) {
				// タイトルに戻る
				int i;
				for (i = 0; i < ENEMY_MAX; i++) {
					en[i].required = 0;
				}
				GameOverAlpha = 0;
				StopPlayMem(seDead);
				PlayMemLoop(bgmTitle);			  // BGM再生スタート
				ScriptDestroy();
				stateStage = STATE_TITLE;
				intoTitle();
			}
		}
	}
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// 画面全体に黒の半透明Boxを被せる
void DrawGameOverBackground() {
	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_ALPHABLEND, GameOverAlpha);
	DrawFBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
}

// ロゴ
void DrawGameOverLogo() {
	SetDrawMode(AMDRAW_ALPHABLEND, GameOverAlpha2);
	DrawMemTh((DISP_W - 640) / 2, 120, cgGameOver);
	if (GameOverAlpha2 >= 255) {

		DrawMemTh((DISP_W - 640) - 150, 500, cgBack);
	}
}

// ゲームオーバー描画
void DrawGameOver() {
	if (stateStage == GAME_OVER)
	{
		DrawGameOverBackground();
		DrawGameOverLogo();

	}
	else if (stateStage == GAME_OVER2)
	{
		DrawGameOverBackground();
		DrawGameOverLogo();

	}
}