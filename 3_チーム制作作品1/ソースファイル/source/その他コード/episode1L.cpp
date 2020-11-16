/*------------------------------------------------
*  @file episode1L.cpp
*  @brief メインゲーム処理
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
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"
#include	"title.h"
#include	"mapdata_1.h"
#include	"Object.h"
#include	"camera.h"
#include	"Object.h"
#include	"enemy.h"
#include	"preparation.h"
#include	"Item.h"
#include	"Material.h"
#include	"recipe.h"
#include	"HitJudgment.h"
#include	"UI.h"
#include	"enemyattack.h"
#include	"changeroom.h"
#include	"game_effect.h"
#include	"episode1S3.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// 画像データ

int cgOperation;		// 操作説明

int OperationFlag;		// フラグ
int fadein, fadeout;	// フェードイン、フェードアウト

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
// 画像読み込み、初期化
int IntoEpisode1L() {
	// ステージの最初だけ操作説明の初期化
	if (stateStage == STATE_EP1STAGE) {
		gFrameWait = 60;
		OperationFlag = 1;
		fadein = 255;
		fadeout = 0;
		cgOperation = LoadTexture("res/operation.png");
	}

	LoadAttackEff();		// 攻撃エフェクト
	LoadCgMapChip_1();		// マップチップ
	LoadCgItem();           // アイテム
	LoadCgAlice();          // アリス
	LoadCgHealth();			// 体力
	LoadCgEnemy();			// 敵
	LoadCgEnemyAttack();	// 敵攻撃エフェクト
	LoadCgPreparation();    // 調合釜
	LoadCgMaterial();       // 素材
	LoadCgObject();         // オブジェクト
	LoadCgRecipe();         // レシピ
	LoadCgUi();				// UI
	LoadCgEffect();			// エフェクト
	LoadCgFukidashi();		// 吹き出し(マージマタンゴ)

	initblackin_ep1();		// ブラックイン
	cameraInit();			// カメラ
	InitAlice();            // プレイヤー
	InitAttack();			// 攻撃エフェクト
	InitEnemy();            // 敵
	InitEnemyAttack();		// 敵攻撃エフェクト
	InitItemColumn();       // アイテムフレーム
	InitPreparation();      // 調合
	InitObject();           // オブジェクト
	InitRecipe();           // レシピ
	InitItem();             // アイテム
	InitMaterial();			// 素材
	InitUseItem();			// 使用アイテム
	InitSystem();			// システムウィンドウ
	InitEquipment();		// 個数カウント
	InitEffect();			// エフェクト
	SetFontSize(14);		// フォントサイズの変更
	InitDescription();		// アイテム説明欄

	StopPlayMem(bgmOp01);	// BGM再生ストップ
	PlayMemLoop(bgmMap1);	// BGM再生スタート

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

// 画像読み込み、初期化
int IntoEpisode1L_Re() {
	if (stateStage == STATE_EP1STAGE) {
		gFrameWait = 60;
		OperationFlag = 1;
		fadein = 255;
		fadeout = 0;
		cgOperation = LoadTexture("res/operation.png");
	}

	LoadAttackEff();		// 攻撃エフェクト
	LoadCgMapChip_1();		// マップチップ
	LoadCgItem();           // アイテム
	LoadCgAlice();          // アリス
	LoadCgHealth();			// 体力
	LoadCgEnemy();			// 敵
	LoadCgEnemyAttack();	// 敵攻撃エフェクト
	LoadCgPreparation();    // 調合釜
	LoadCgMaterial();       // 素材
	LoadCgObject();         // オブジェクト
	LoadCgRecipe();         // レシピ
	LoadCgUi();				// UI
	LoadCgEffect();			// エフェクト
	LoadCgFukidashi();		// 吹き出し(マージマタンゴ)

	initblackin_ep1();		// ブラックイン
	cameraInit();			// カメラ
	InitAlice();            // プレイヤー
	InitAttack();			// 攻撃エフェクト
	InitEnemy();            // 敵
	InitEnemyAttack();		// 敵攻撃エフェクト
	InitItemColumn();       // アイテムフレーム
	InitPreparation();      // 調合
	InitObject();           // オブジェクト
	InitRecipe();           // レシピ
	InitItem();             // アイテム
	InitUseItem();			// 使用アイテム
	InitSystem();			// システムウィンドウ
	InitEquipment();		// 個数カウント
	InitEffect();			// エフェクト
	SetFontSize(14);		// フォントサイズの変更
	InitDescription();		// アイテム説明欄

	PlayMemLoop(bgmMap1);	// BGM再生スタート

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

// 画像読み込み、初期化
int IntoEpisode1L_4() {
	stateStage = STATE_EP1STAGE_4;
	InitAlice();
	InitEnemy();
	InitPreparation();
	InitObject();
	InitPoz();
	initblackin_ep1();
	releaseAlice();
	SetFontSize(14);		// フォントサイズの変更
	PlayMemLoop(bgmBoss1);			  // BGM再生スタート
	//InitUseItem();			// プレゼン用

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

// 待ち時間
void FrameWait() {
	int i, j;
	if (gFrameWait > 0) {
		gFrameWait--;
		for (i = 0; i < OBJECT_MAX; i++) {
			// 待ち時間が無くなったら動けるようにする
			if (gFrameWait == 0) {
				if (material[sy.number].use == 1) {
					material[sy.number].use = 0;
				}
				if (al.state == ALICE_STATE_GATHERING_UP) {
					al.state = ALICE_STATE_UP;
				}
				if (al.state == ALICE_STATE_GATHERING_DOWN) {
					al.state = ALICE_STATE_DOWN;
				}
				if (al.state == ALICE_STATE_GATHERING_RIGHT) {
					al.state = ALICE_STATE_RIGHT;
				}
				if (al.state == ALICE_STATE_GATHERING_LEFT) {
					al.state = ALICE_STATE_LEFT;
				}
			}
		}
		// 待ち時間が無くなったら使えるようにする
		if (gFrameWait == 0) {
			// 調合窯
			pre[0].use = 0;
			pre[1].use = 0;
			pre[2].use = 0;
			pre[3].use = 0;

			gFrameWait = 0;		// 待ち時間を0にする
			GetRecipe = 0;		// レシピをゲットし終わった
			firstcreate = 0;	// 最初の調合が終わった
			material_max = 0;	// アイテム最大表示を消す
			// 敵が落としたレシピを消す
			if (recipe1 == 1) {
				recipe1 = 0;
			}
			else if (recipe2 == 1) {
				recipe2 = 0;
			}
			else if (recipe1 == 2) {
				recipe1 = 0;
			}
			else if (recipe2 == 2) {
				recipe2 = 0;
			}
			else if (recipe1 == 3) {
				recipe1 = 0;
			}
			else if (recipe2 == 3) {
				recipe2 = 0;
			}
			else if (recipe3 == 3) {
				recipe3 = 0;
			}
		}
	}
}

// メインゲームの中身
int Episode1_Stage() {

	// 操作説明の処理(ステージ最初だけ)
	if (stateStage == STATE_EP1STAGE) {
		if (OperationFlag == 1) {
			cameraProcess();		// カメラ移動
				if (gFrameWait > 0) {
					gFrameWait--;
				}
			if (gFrameWait <= 0) {
				if (gTrg & KEYIN_Z) {
					OperationFlag = 0;
				}
			}
			return STATE_EP1STAGE;
		}
	}

	// ゲームオーバー処理中か？
	if (gGameoverCount > 0)
	{
		StopPlayMem(seWalk1);
		gGameoverCount--;
		if (gGameoverCount == 0)
		{
			continueflag = 1;
			selectTrg = STATE_NONE;
			// ゲームオーバーにする
			stateStage = GAME_OVER;
			return GAME_OVER;
		}
	}

	FrameWait();			// 待ち時間
	AttackCooltime();		// 攻撃クールタイム(プレイヤー)
	ReGetMaterialWait();	// 再びアイテムをゲットできるまでの時間
	EnemyAttackCooltime();	// 攻撃クールタイム(敵)
	SystemWait();			// システムウィンドウの表示時間

	// 調合画面を開く
	if (selectTrg == STATE_ONE) {
		SelectItem();
	}

	DropItem();		// アイテムのドロップ

	// 待ち時間がない間動かす
	if ((gFrameWait == 0) && (attackCooltime == 0) && (clearwait == 0) && (wallwait == 0)) {
		cameraProcess();		// カメラ移動
		ControllAlice();		// アリス移動
		FrameControll();		// アイテムフレーム移動
	}

	// 敵移動
	EnemyMove();

	// プレイヤーと敵の当たり判定
	HitCheckPlayerEnemy();

	// プレイヤーと敵(行動範囲)の当たり判定
	HitCheckPlayerEnemyRange();

	// プレイヤーの攻撃の当たり判定
	HitCheckPlayerAttack();

	// プレイヤーのアイテム攻撃の当たり判定
	HitCheckPlayerItemAttack();

	// プレイヤーと調合釜の当たり判定
	switch (stateStage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
		HitCheckPlayerPreparation();
	}
	
	// プレイヤーとオブジェクトの当たり判定
	switch(stateStage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
		HitCheckPlayerObject();
	}

	// 壁が壊れる
	wallbreak();

	// エフェクト処理
	ProcessEffect();

	//初めての調合
	FirstCreate();

	if (wallwait <= 0) {
		// 所持素材、アイテム確認画面表示
		if (gTrg & KEYIN_C) {
			if (selectTrg == STATE_NONE) {
				StopPlayMem(seWalk1);
				PlayMemBack(seSelect);		// SE再生
				check = STATE_ONE;
			}
		}

		// 所持素材、アイテム確認画面閉じる
		if (gTrg & KEYIN_Z) {
			if (check == STATE_ONE) {
				if (pick == STATE_NONE) {
					PlayMemBack(seCancel);	// SE再生
					check = STATE_NONE;
					InitSelect();
				}
			}
		}
	}

	// アイテムの変更
	if (check == STATE_ONE) {
		EquipmentItem();
	}

	// ボスを倒した
	if (clearwait > 0) {
		clearwait--;
		if (clearwait == 0) {
			clearflag = 1;
			StopPlayMem(seWalk1);
			StopPlayMem(bgmBoss1);
			stateStage = STATE_EP1STORY3;
			return IntoEpisode1S3();
		}
	}

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/
void DrawEp1LProcess() {
	int i;

	// 画面を消す
	HCls();
	worldToView();

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// マップ
	switch (stateStage) {
	case STATE_EP1STAGE:
		DrawMapChip_1();
		DrawObject();		// オブジェクト
		bgstage = STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		DrawMapChip_2();
		if (wallflag <= 0) {
			DrawMapChiplm_2();
			DrawFukidashi();
		}
		DrawObject ();		// オブジェクト
		bgstage = STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		DrawMapChip_3();
		if (wallflag <= 1) {
			DrawMapChiplm_3();
			DrawFukidashi();
		}
		DrawObject ();		// オブジェクト
		bgstage = STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		DrawMapChip_4();
		bgstage = STATE_EP1STAGE_4;
		break;
	case GAME_OVER:
		if (bgstage == STATE_EP1STAGE) {
			DrawMapChip_1();
			DrawObject();		// オブジェクト
		}
		else if (bgstage == STATE_EP1STAGE_2) {
			DrawMapChip_2();
			if (required_count < 2) {
				DrawMapChiplm_2();
			}
			DrawObject ();		// オブジェクト
		}
		else if (bgstage == STATE_EP1STAGE_3) {
			DrawMapChip_3();
			if (required_count < 4) {
				DrawMapChiplm_3();
			}
			DrawMapChiphd_3();
			DrawObject ();		// オブジェクト
		}
		else {
			DrawMapChip_4();
		}
		break;
	default:
		break;
	}
	
	// ドロップアイテム
	DropMaterial();

	// キャラクター
	DrawAlice();
	
	// 敵攻撃エフェクト
	DrawEnemyAttack();

	//敵
	DrawEnemy();
	
	switch (stateStage) {
	case STATE_EP1STAGE:
		DrawMapChiphd_1();
		break;
	case STATE_EP1STAGE_2:
		DrawMapChiphd_2();
		break;
	case STATE_EP1STAGE_3:
		DrawMapChiphd_3();
		break;
	case STATE_EP1STAGE_4:
		DrawMapChiphd_4();
		break;

	}

	// オブジェクトに触れている
	switch (stateStage) {
	case STATE_EP1STAGE:
		if ((obj[7].use == 1) || (obj[8].use == 1)) {
			TouchObject();
		}
		break;
	case STATE_EP1STAGE_2:
		if ((obj[15].use == 1) || (obj[16].use == 1)) {
			TouchObject();
		}
		break;
	case STATE_EP1STAGE_3:
		if ((obj[21].use == 1) || (obj[22].use == 1)) {
			TouchObject();
		}
		break;
	}

	if (wallwait < 1) {
		if (firstcreate == 0) {
			// アリスのヒットポイント
			DrawAliceHealth();

			// アイテム装備欄
			DrawItemColumn();//アイテムフレーム

			// 調合アイテム
			if (frm[2].move == 0) {
				for (i = 0; i < 6; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//アイテムを手に入れた
					}
				}
			}
			else if (frm[2].move == 1) {
				for (i = 6; i < 10; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//アイテムを手に入れた
					}
				}
			}
		}
	}

	// ボスのヒットポイント
	DrawEnemyHitpoint();

	// エフェクト
	DrawEffect();

	// システムウィンドウ
	DrawSystem();
	
	//調合釜
	DrawPreparation();

	// アイテム所持数
	if (check == STATE_ONE) {
		DrawEquipmentItem();
	}

	// 素材
	DrawMaterial();

	// レシピのゲット
	DrawGetRecipe();
	
	// 初めての調合
	DrawFirstCreate();

	// 操作説明
	if (stateStage == STATE_EP1STAGE) {
		if (gFrameWait <= 0) {
			if (fadeout < 0) {
				SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
				DrawMemTh(0, 0, cgOperation);
				DrawMemTh(1100, 680, ButtonB);
				SetDrawMode(AMDRAW_NOBLEND, 0);
			}
			else {
				SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
				DrawMemTh(0, 0, cgOperation);
				DrawTBox(1100, 680, 1200, 710, GetColor(0, 0, 0));
				DrawMemTh(1100, 680, ButtonA);
				DrawPrintf(1140, 690, GetColor(0, 0, 0), "閉じる");
				SetDrawMode(AMDRAW_NOBLEND, 0);
			}
		}
		operationfadeout();
	}

	blackfadein_ep1();	// ブラックフェードイン
	blackfadeout_ep1();	// ブラックフェードアウト

	Systemfadein_out();		// 素材獲得時のフェードイン、アウト
	FirstCreatefadein();	// 調合時のフェードイン

	// ステージパートの間Flipする
	if ((stateStage == STATE_EP1STAGE) || (stateStage == STATE_EP1STAGE_2) || (stateStage == STATE_EP1STAGE_3) || (stateStage == STATE_EP1STAGE_4)) {
		Flip();
	}

}