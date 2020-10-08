/*------------------------------------------------
*  @file changeroom.cpp
*  @brief ステージ移動処理
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
#include    "global.h"   
#include    "alice.h"
#include	"aliceattack.h"
#include	"episode1S2.h"
#include	"episode2S2.h"
#include	"episode1L.h"
#include	"episode2L.h"
#include	"mapdata_1.h"
#include	"mapdata_2.h"
#include	"HitJudgment.h"
#include	"camera.h"
#include	"Item.h"
#include	"UI.h"
#include	"enemy.h"
#include	"preparation.h"
#include	"Object.h"
#include	"Material.h"
#include	"end.h"
#include	"script_parser.h"
#include	"enemyattack.h"
#include	"game_effect.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int bi_alpha_ep1_fi;	// フェードイン
int bi_alpha_ep1_fo;	// フェードアウト
int bi_alpha_ep2_fi;	// フェードイン
int bi_alpha_ep2_fo;	// フェードアウト
int bi_alpha_ep3_fi;	// フェードイン
int bi_alpha_ep3_fo;	// フェードアウト

int stock = 0;			// 移動前のステージ情報を取っておく

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 初期化
void initblackin_ep1 () {
	bi_alpha_ep1_fi = 255;
	bi_alpha_ep1_fo = 0;
}

// 初期化
void initblackin_ep2() {
	bi_alpha_ep2_fi = 255;
	bi_alpha_ep2_fo = 0;
}

// 初期化
void initblackin_ep3() {
	bi_alpha_ep3_fi = 255;
	bi_alpha_ep3_fo = 0;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

// ステージ間の移動
void changeroom () {
	// ステージを行き来できるようにする
	switch (stateStage) {
	case STATE_EP1STAGE:
		if (al.y + al.h < 0) {
			freezeAlice();		// プレイヤーを動けないようにする
			if (bi_alpha_ep1_fo >= 255) {
				StopPlayMem(seWalk1);	// SEストップ
				stateStage = STATE_EP1STAGE_2;
				al.x = 2320;
				al.y = 2040;
				// 次のステージ情報を読み込み
				InitEnemy ();
				InitPreparation ();
				InitObject ();
				InitPoz ();
				initblackin_ep1();
				InitFukidashi();
				InitEnemyAttack();
				releaseAlice();
			}
		}
		break;
	case STATE_EP1STAGE_2:
		if (al.y + al.h < 0) {
			freezeAlice();		// プレイヤーを動けないようにする
			if (bi_alpha_ep1_fo >= 255) {
				StopPlayMem(seWalk1);	// SEストップ
				stateStage = STATE_EP1STAGE_3;
				al.x = 1400;
				al.y = 2320;
				// 次のステージ情報を読み込み
				InitEnemy ();
				InitPreparation ();
				InitObject ();
				InitPoz ();
				initblackin_ep1 ();
				InitFukidashi();
				InitEnemyAttack();
				releaseAlice();
			}
		}
		else if (al.y + al.h - cv.view_y > DISP_H) {
			freezeAlice();		// プレイヤーを動けないようにする
			if (bi_alpha_ep1_fo >= 255) {
				StopPlayMem(seWalk1);	// SEストップ
				stateStage = STATE_EP1STAGE;
				al.x = 2320;
				al.y = 40;
				// 次のステージ情報を読み込み
				InitEnemy();
				InitPreparation();
				InitObject();
				InitPoz();
				initblackin_ep1();
				InitEnemyAttack();
				releaseAlice();
			}
		}
		break;
	case STATE_EP1STAGE_3:
		if (al.y + al.h < 0) {
			freezeAlice();		// プレイヤーを動けないようにする
			if (bi_alpha_ep1_fo >= 255) {
				StopPlayMem(seWalk1);	// SEストップ
				stateStage = STATE_EP1STORY2;
				ScriptCreate();
				initblackin_ep1s2();
				InitEnemyAttack();
				StopPlayMem(bgmMap1);	// BGMストップ
			}
		} 
		else if (al.y + al.h - cv.view_y > DISP_H) {
			freezeAlice();		// プレイヤーを動けないようにする
			if (bi_alpha_ep1_fo >= 255) {
				StopPlayMem(seWalk1);	// SEストップ
				stateStage = STATE_EP1STAGE_2;
				al.x = 1800;
				al.y = 40;
				// 次のステージ情報を読み込み
				InitEnemy();
				InitPreparation();
				InitObject();
				InitPoz();
				initblackin_ep1();
				InitEnemyAttack();
				releaseAlice();
			}
		}
	case STATE_EP1STAGE_4:
		break;
	case STATE_EP2STAGE1_1:
		if (al.move == 5) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE2_1;
				al.x = 40 * 7;
				al.y = 40 * 12;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				InitFukidashi2();
				releaseAlice2();
				PlayMemBack(seMove);	// SE再生
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 1) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_2;
				al.x = 40 * 1;
				al.y = 40 * 20;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 2) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_2;
				al.x = 40 * 11;
				al.y = 40 * 39;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 3) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_2;
				al.x = 40 * 32;
				al.y = 40 * 39;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 4) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_2;
				al.x = 40 * 43;
				al.y = 40 * 51;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		break;
	case STATE_EP2STAGE1_2:
		if (al.move == 1) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_1;
				al.x = 40 * 23;
				al.y = 40 * 29;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				InitFukidashi2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 2) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_1;
				al.x = 40 * 36;
				al.y = 40 * 51;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				InitFukidashi2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 3) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_1;
				al.x = 40 * 57;
				al.y = 40 * 51;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				InitFukidashi2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 4) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_1;
				al.x = 40 * 64;
				al.y = 40 * 60;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				InitFukidashi2();
				releaseAlice2();
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		break;
	case STATE_EP2STAGE1_3:
		if (al.move == 1) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE2_2;
				al.x = 40 * 24;
				al.y = 40 * 12;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				PlayMemBack(seMove);	// SE再生
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 2) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE2_1;
				al.x = 40 * 22;
				al.y = 40 * 46;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				PlayMemBack(seMove);	// SE再生
				al.move = 0;
				InitEnemyAttack2();
			}
		}
	case STATE_EP2STAGE2_1:
		if (al.move == 1) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_3;
				al.x = 40 * 5;
				al.y = 40 * 2;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				InitFukidashi2();
				releaseAlice2();
				PlayMemBack(seMove);	// SE再生
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		else if (al.move == 2) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_1;
				al.x = 40 * 7;
				al.y = 40 * 3;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				PlayMemBack(seMove);	// SE再生
				al.move = 0;
				InitEnemyAttack2();
			}
		}
		break;
	case STATE_EP2STAGE2_2:
		if (al.move == 1) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				if (clearflag == 1) {
					StopPlayMem(seWalk2);	// SEストップ
					stateStage = STATE_EP2STORY2;
					ScriptCreate();
					initblackin_ep2s2();
					PlayMemBack(seMove);	// SE再生
					StopPlayMem(bgmMap2);	// BGMストップ
					al.move = 0;
					InitEnemyAttack2();
				}
				else if (clearflag == 2) {
					StopPlayMem(seWalk2);	// SEストップ
					stateStage = STATE_EP2STAGE_3;
					PlayMemBack(seMove);	// SE再生
					StopPlayMem(bgmMap2);	// BGMストップ
					IntoEpisode2L_3_2();
					releaseAlice2();
					al.move = 0;
					InitEnemyAttack2();
				}
			}
		}
		else if (al.move == 2) {
			freezeAlice2();		// プレイヤーを動けないようにする
			if (bi_alpha_ep2_fo >= 255) {
				StopPlayMem(seWalk2);	// SEストップ
				stateStage = STATE_EP2STAGE1_3;
				al.x = 40 * 59;
				al.y = 40 * 1;
				// 次のステージ情報を読み込み
				InitEnemy2();
				InitPreparation();
				InitObject2();
				InitPoz();
				initblackin_ep2();
				releaseAlice2();
				PlayMemBack(seMove);	// SE再生
				al.move = 0;
				InitEnemyAttack2();
			}
		}
	case STATE_EP2STAGE_3:
		break;
	}
}

// 条件を満たしたら壁が壊れる
void wallbreak() {
	if (wallwait > 0) {
		wallwait--;
		StopPlayMem(seWalk1);	// SEストップ
		switch (stateStage) {
		case STATE_EP1STAGE_2:
			if (bi_alpha_ep1_fo >= 255) {
				cv.view_x = 40 * 30;
				cv.view_y = 40 * 0;
				initblackin_ep1();
			}
			if (wallwait == 430) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 40, 40 * 0, -1);
			}
			if (wallwait == 370) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 44, 40 * 0, -1);
			}
			if (wallwait == 310) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 42, 40 * 0, -1);
			}
			if (wallwait == 250) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 46, 40 * 0, -1);
			}
			if (wallwait == 240) {
				wallflag = 1;
			}
			break;
		case STATE_EP1STAGE_3:
			if (bi_alpha_ep1_fo >= 255) {
				cv.view_x = 40 * 0;
				cv.view_y = 40 * 0;
				initblackin_ep1();
			}
			if (wallwait == 430) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 0, 40 * 0, -1);
			}
			if (wallwait == 370) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 2, 40 * 0, -1);
			}
			if (wallwait == 310) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 1, 40 * 0, -1);
			}
			if (wallwait == 250) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 3, 40 * 0, -1);
			}
			if (wallwait == 240) {
				wallflag = 2;
			}
			break;
		}
		if (wallwait <= 0) {
			cv.view_x = al.x - (DISP_W / 2);		// 画面の横中央にキャラを置く
			cv.view_y = al.y - (DISP_H / 2);		// 画面の縦中央にキャラを置く
			initblackin_ep2();
		}
	}
}

// 条件を満たしたら壁が壊れる
void wallbreak2() {
	if (wallwait > 0) {
		wallwait--;
		StopPlayMem(seWalk2);	// SEストップ
		switch (stateStage) {
		case STATE_EP2STAGE1_1:
			if (bi_alpha_ep2_fo >= 255) {
				cv.view_x = 40 * 0;
				cv.view_y = 40 * 15;
				initblackin_ep2();
			}
			if (wallwait == 430) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 4, 40 * 19, -1);
			}
			if (wallwait == 370) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 7, 40 * 19, -1);
			}
			if (wallwait == 310) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 5, 40 * 19, -1);
			}
			if (wallwait == 250) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 8, 40 * 19, -1);
			}
			if (wallwait == 240) {
				wallflag = 3;
			}
			break;
		case STATE_EP2STAGE1_2:
			if (bi_alpha_ep2_fo >= 255) {
				stock = STATE_EP2STAGE1_2;
				stateStage = STATE_EP2STAGE1_1;
				cv.view_x = 40 * 0;
				cv.view_y = 40 * 15;
				initblackin_ep2();
			}
			if (wallwait == 430) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 4, 40 * 19, -1);
			}
			if (wallwait == 370) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 7, 40 * 19, -1);
			}
			if (wallwait == 310) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 5, 40 * 19, -1);
			}
			if (wallwait == 250) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 8, 40 * 19, -1);
			}
			if (wallwait == 240) {
				wallflag = 3;
			}
			break;
		case STATE_EP2STAGE1_3:
			if (bi_alpha_ep2_fo >= 255) {
				cv.view_x = 40 * 33;
				cv.view_y = 40 * 0;
				initblackin_ep2();
			}
			if (wallwait == 430) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 53, 40 * 1, -1);
			}
			if (wallwait == 370) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 53, 40 * 5, -1);
			}
			if (wallwait == 310) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 53, 40 * 3, -1);
			}
			if (wallwait == 250) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 53, 40 * 7, -1);
			}
			if (wallwait == 240) {
				wallflag = 5;
			}
			break;
		case STATE_EP2STAGE2_1:
			if (bi_alpha_ep2_fo >= 255) {
				cv.view_x = 40 * 7;
				cv.view_y = 40 * 25;
				initblackin_ep2();
			}
			if (wallwait == 430) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 19, 40 * 33, -1);
			}
			if (wallwait == 370) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 21, 40 * 33, -1);
			}
			if (wallwait == 310) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 20, 40 * 33, -1);
			}
			if (wallwait == 250) {
				PlayMemBack(seWallBreak);	// SE再生
				PutEffect(EFFECTTYPE_BREAK, 40 * 22, 40 * 33, -1);
			}
			if (wallwait == 240) {
				wallflag = 4;
			}
			break;
		}
		if (wallwait <= 0) {
			if (stock == STATE_EP2STAGE1_2) {
				stateStage = STATE_EP2STAGE1_2;
				stock = 0;
			}
			cv.view_x = al.x - (DISP_W / 2);		// 画面の横中央にキャラを置く
			cv.view_y = al.y - (DISP_H / 2);		// 画面の縦中央にキャラを置く
			initblackin_ep2();
		}
	}
}

// 操作説明のフェード
void operationfadeout() {
	switch (stateStage) {
	case STATE_EP1STAGE:
		SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
		if (OperationFlag == 0) {
			if (fadeout <= 255) {
				fadeout -= 15;
			}
		}
		else {
			if (gFrameWait <= 0) {
				fadeout += 15;
				if (fadeout >= 255) {
					fadeout = 255;
				}
			}
		}
		break;
	case STATE_END:
		SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
		if (countend >= 6100) {
			if (fadeout <= 255) {
				fadeout -= 3;
			}
		}
	}

}

// フェードイン
void blackfadein_ep1 () {

	SetDrawMode (AMDRAW_ALPHABLEND, bi_alpha_ep1_fi);
	DrawFBox (0, 0,
			  1280, 720,
			  GetColor (0, 0, 0));
	if (bi_alpha_ep1_fi > 0) {
		bi_alpha_ep1_fi -= 15;
	}

}

// フェードイン
void blackfadein_ep2() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2_fi > 0) {
		bi_alpha_ep2_fi -= 15;
	}

}

// フェードイン
void blackfadein_ep3() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep3_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep3_fi > 0) {
		bi_alpha_ep3_fi -= 15;
	}

}

// フェードアウト
void blackfadeout_ep1 () {

	SetDrawMode (AMDRAW_ALPHABLEND, bi_alpha_ep1_fo);
	DrawFBox (0, 0,
			  1280, 720,
			  GetColor (0, 0, 0));
	if (bi_alpha_ep1_fo <= 255) {
		if((al.y + al.h < 0) || (al.y + al.h - cv.view_y > DISP_H) && (wallwait == 0)) {
		bi_alpha_ep1_fo += 15;
		}
		else if ((stateStage == STATE_EP1STAGE_4) & (en[0].state_enemy == 1)) {
			bi_alpha_ep1_fo += 5;
		}
		else if (((required_count == 2) && (wallwait >= 549)) || ((required_count == 4) && (wallwait >= 549))) {
			bi_alpha_ep1_fo += 5;
		}
		else if ((wallflag == 1) && (wallwait <= 51) && (wallwait > 0) || (wallflag == 2) && (wallwait <= 51) && (wallwait > 0)) {
			bi_alpha_ep1_fo += 5;
		}
	}

}

// フェードアウト
void blackfadeout_ep2() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2_fo <= 255) {
		if ((al.move == 1) || (al.move == 2) || (al.move == 3) || (al.move == 4) || (al.move == 5)) {
			bi_alpha_ep2_fo += 15;
		}
		else if ((clearwait > 0) & ((stateStage == STATE_EP2STAGE_3) & (en[0].use == 0) || (stateStage == STATE_EP2STAGE_3) & (en[1].use == 0))) {
			bi_alpha_ep2_fo += 5;
		}
		else if (((required_count == 3) && (wallwait >= 549)) || ((required_count == 6) && (wallwait >= 549)) || ((required_count == 8) && (wallwait >= 549))) {
			bi_alpha_ep2_fo += 5;
		}
		else if ((wallflag == 3) && (wallwait <= 51) && (wallwait > 0) || (wallflag == 4) && (wallwait <= 51) && (wallwait > 0) || (wallflag == 5) && (wallwait <= 51) && (wallwait > 0)) {
			bi_alpha_ep2_fo += 5;
		}
	}
}

// フェードアウト
void blackfadeout_ep3() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep3_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep3_fo <= 255) {
		if (countend >= 6300) {
			bi_alpha_ep3_fo += 2;
		}
	}
}

// 素材獲得時のフェードイン、アウト
void Systemfadein_out() {
	SetDrawMode(AMDRAW_ALPHABLEND, systemAlpha);
	if (sy.use == 1) {
		if (systemAlpha <= 255) {
			systemAlpha += 15;
			if (systemAlpha >= 255) {
				systemAlpha = 255;
			}
		}
	}
	else {
		if (systemAlpha >= 0) {
			systemAlpha -= 15;
			if (systemAlpha <= 0) {
				systemAlpha = 0;
			}
		}
	}
}

// 調合時のフェードイン
void FirstCreatefadein() {
	SetDrawMode(AMDRAW_ADDBLEND, createalpha);
	if ((fc[0].use == 0) & (fc[1].use == 0) & (fc[2].use == 0)) {
		if (createalpha <= 255) {
			createalpha += 15;
			if (createalpha >= 255) {
				createalpha = 255;
			}
		}
	}
}