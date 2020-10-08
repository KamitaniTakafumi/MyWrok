/*------------------------------------------------
*  @file game.cpp
*  @brief ゲーム本体処理
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
#include    "alice.h"
#include    "enemy.h"
#include    "preparation.h"
#include    "HitJudgment.h"
#include	"script_parser.h"
#include    "Material.h"
#include    "Object.h"
#include    "recipe.h"
#include	"title.h"
#include	"episode1S.h"
#include	"episode1S2.h"
#include	"episode1S3.h"
#include	"episode2S.h"
#include	"episode2S2.h"
#include	"episode2S3.h"
#include	"episode2S4.h"
#include	"episode1L.h"
#include	"episode2L.h"
#include	"global.h"
#include	"gameover.h"
#include	"end.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// ゲーム情報
int stateStage;		// 現在のステージ
int gFrameCount;	// 毎フレーム+1するカウント
int gKey;			// キー入力の情報
int gTrg;			// トリガ入力の情報
int gFrameWait;		// 行動した時のクールタイム
int gGameoverCount;	// ゲームオーバー時のカウントダウン
int check;			// キー入力の判定
int pick;			// キー入力の判定
int bgstage;		// ゲームオーバー時に描画するステージ
int bgstage2;		// ゲームオーバー時に描画するステージ
int required_count; // 進むのに必要な倒す敵のカウント
int clearwait;		// ボス後、ストーリーパートへの移行時間
int clearflag;		// 進むためのフラグ変数
int check_number;	// アイテムを持っているかのチェック変数
int check_number2;	// アイテムを持っているかのチェック変数２
int wallwait;		// 壁壊し待ち時間
int wallflag;		// 壁壊しフラグ
int continueflag;	// コンティニューフラグ

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
// アプリの初期化
// 起動時に1回だけ実行される
void AppInit() {

	stateStage = STATE_TITLE;
	check = STATE_NONE;
	pick = STATE_NONE;
	bgstage = STATE_EP1STAGE;
	bgstage2 = STATE_EP2STAGE1_1;

	// 画像の読み込み
	LoadCgTitle();
	LoadCgGameOver();
	LoadSe();
	LoadBgm();

	//フレームカウントの初期化
	gFrameCount = 0;
	gFrameWait = 0;
	gGameoverCount = 0;
	clearwait = 0;
	clearflag = 0;
	check_number = 0;
	check_number2 = 0;
	wallwait = 0;
	wallflag = 0;
	continueflag = 0;

	//初期化
	cursorInit();
}

// アプリの解放
// 終了時に1回だけ実行される
void AppRelease() {

}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

//
// フレーム処理。1フレームに1回ずつ実行される
//

// フレーム処理：入力
void FrameInput() {
	// キーの入力、トリガ入力を得る
	int keyold = gKey;
	gKey = CheckKey(0);
	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	gTrg = (gKey ^ keyold) & gKey;
}

// フレーム処理：計算
void FrameProcess() {

	// 毎フレーム処理
	gFrameCount++;		// フレームカウントを増やす

	// 状態ごとに処理を分ける
	switch (stateStage) {
	case STATE_TITLE:
		titleSelect();
		break;
	case STATE_EP1STORY:
		Episode1_Story();
		break;
	case STATE_EP1STORY2:
		Episode1_Story2();
		break;
	case STATE_EP1STORY3:
		Episode1_Story3();
		break;
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
	case STATE_EP1STAGE_4:
		Episode1_Stage();
		break;
	case STATE_EP2STORY:
		Episode2_Story();
		break;
	case STATE_EP2STORY2:
		Episode2_Story2();
		break;
	case STATE_EP2STORY3:
		Episode2_Story3();
		break;
	case STATE_EP2STORY4:
		Episode2_Story4();
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
	case STATE_EP2STAGE_3:
		Episode2_Stage();
		break;
	case STATE_END:
		EndRole();
		break;
	case GAME_OVER:
	case GAME_OVER2:
		GameOverProcess();
		break;
	default:
		break;
	}
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// フレーム処理：描画
void FrameDraw() {
	// 状態ごとに描画を分ける
	switch (stateStage) {
	case STATE_TITLE:
		DrawTitleProcess();
		break;
	case STATE_EP1STORY:
		DrawEp1SProcess();
		break;
	case STATE_EP1STORY2:
		DrawEp1S2Process();
		break;
	case STATE_EP1STORY3:
		DrawEp1S3Process();
		break;
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
	case STATE_EP1STAGE_4:
		DrawEp1LProcess();
		break;
	case STATE_EP2STORY:
		DrawEp2SProcess();
		break;
	case STATE_EP2STORY2:
		DrawEp2S2Process();
		break;
	case STATE_EP2STORY3:
		DrawEp2S3Process();
		break;
	case STATE_EP2STORY4:
		DrawEp2S4Process();
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
	case STATE_EP2STAGE_3:
		DrawEp2LProcess();
		break;
	case STATE_END:
		DrawEnd();
		break;
	case GAME_OVER:
		if ((bgstage == STATE_EP1STAGE) || (bgstage == STATE_EP1STAGE_2) || (bgstage == STATE_EP1STAGE_3) || (bgstage == STATE_EP1STAGE_4)) {
			DrawEp1LProcess();
		}
		if (stateStage == GAME_OVER) {
			DrawGameOver();
		}
		Flip();
		break;
	case GAME_OVER2:
		if ((bgstage2 == STATE_EP2STAGE1_1) || (bgstage2 == STATE_EP2STAGE1_2) || (bgstage2 == STATE_EP2STAGE1_3) || (bgstage2 == STATE_EP2STAGE2_1) || (bgstage2 == STATE_EP2STAGE2_2) || (bgstage2 == STATE_EP2STAGE_3)) {
			DrawEp2LProcess();
		}
		if (stateStage == GAME_OVER2) {
			DrawGameOver();
		}
		Flip();
		break;
	default:
		break;
	}
}

