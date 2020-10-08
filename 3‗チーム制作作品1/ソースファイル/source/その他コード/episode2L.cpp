/*------------------------------------------------
*  @file episode2L.cpp
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
#include	"mapdata_2.h"
#include	"episode2S3.h"
#include	"episode2S4.h"
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
#include	"end.h"
#include	"script_parser.h"

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
// 画像読み込み、初期化
int IntoEpisode2L() {
	if (bgstage2 == STATE_EP2STAGE1_1) {
		if (bgstage == STATE_EP1STAGE_4) {
			required_count = 0;
			recipe1 = 0;
			recipe2 = 0;
			recipe3 = 0;
		}
	}

	LoadCgMapChip_2();		// マップチップ
	LoadCgAlice2();         // アリス
	LoadAttackEff();		// 攻撃エフェクト
	LoadCgHealth();			// 体力
	LoadCgEnemy2();			// 敵
	LoadCgEnemyAttack2();	// 敵攻撃エフェクト
	LoadCgPreparation();    // 調合釜
	LoadCgMaterial();       // 素材
	LoadCgObject();         // オブジェクト
	LoadCgItem();
	LoadCgUi();				// UI
	LoadCgEffect();			// エフェクト
	LoadCgFukidashi2();

	initblackin_ep2();		// ブラックイン
	cameraInit();			// カメラ
	InitAlice2();           // プレイヤー
	InitAttack();			// 攻撃エフェクト
	InitEnemy2();           // 敵
	InitEnemyAttack2();		// 敵攻撃エフェクト
	InitItemColumn();       // アイテムフレーム
	InitPreparation();      // 調合
	InitObject2();          // オブジェクト
	InitItem();             // アイテム
	InitMaterial();			// 素材
	InitUseItem();			// 使用アイテム
	InitSystem();			// システムウィンドウ
	InitEquipment();		// 個数カウント
	InitEffect();			// エフェクト
	InitFukidashi2(); 
	InitDescription();
	SetFontSize(14);		// フォントサイズの変更

	PlayMemLoop(bgmMap2);	// BGM再生スタート

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

// 画像読み込み、初期化
int IntoEpisode2L_Re() {
	if (bgstage2 == STATE_EP2STAGE1_1) {
		if (bgstage == STATE_EP1STAGE_4) {
			required_count = 0;
			recipe1 = 0;
			recipe2 = 0;
			recipe3 = 0;
		}
	}

	LoadCgMapChip_2();		// マップチップ
	LoadCgAlice2();         // アリス
	LoadAttackEff();		// 攻撃エフェクト
	LoadCgHealth();			// 体力
	LoadCgEnemy2();			// 敵
	LoadCgEnemyAttack2();	// 敵攻撃エフェクト
	LoadCgPreparation();    // 調合釜
	LoadCgMaterial();       // 素材
	LoadCgObject();         // オブジェクト
	LoadCgItem();
	LoadCgUi();				// UI
	LoadCgEffect();			// エフェクト
	LoadCgFukidashi2();

	initblackin_ep2();		// ブラックイン
	cameraInit();			// カメラ
	InitAlice2();           // プレイヤー
	InitAttack();			// 攻撃エフェクト
	InitEnemy2();           // 敵
	InitEnemyAttack2();		// 敵攻撃エフェクト
	InitItemColumn();       // アイテムフレーム
	InitPreparation();      // 調合
	InitObject2();          // オブジェクト
	InitItem();             // アイテム
	InitUseItem();			// 使用アイテム
	InitSystem();			// システムウィンドウ
	InitEquipment();		// 個数カウント
	InitEffect();			// エフェクト
	InitFukidashi2();
	InitDescription();
	SetFontSize(14);		// フォントサイズの変更

	PlayMemLoop(bgmMap2);	// BGM再生スタート

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

int IntoEpisode2L_3_1() {
	al.x = 40 * 18;
	al.y = 40 * 20;
	al.state = ALICE_STATE_IDLE_UP;
	InitEnemy2();
	InitPreparation();
	InitObject2();
	InitPoz();
	initblackin_ep2();
	releaseAlice2();
	SetFontSize(14);		// フォントサイズの変更
	PlayMemLoop(bgmBoss2);			  // BGM再生スタート
	al.move = 0;

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

int IntoEpisode2L_3_2() {
	al.x = 40 * 18;
	al.y = 40 * 20;
	al.state = ALICE_STATE_IDLE_UP;
	PlayMemLoop(bgmBoss3);			  // BGM再生スタート
	initblackin_ep2();
	InitEnemy2();
	SetFontSize(14);		// フォントサイズの変更

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

// 待ち時間
void FrameWait2() {
	int i;
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
			if (recipe1 == 4) {
				recipe1 = 0;
			}
			else if (recipe2 == 4) {
				recipe2 = 0;
			}
			else if (recipe1 == 5) {
				recipe1 = 0;
			}
			else if (recipe2 == 5) {
				recipe2 = 0;
			}
			else if (recipe1 == 6) {
				recipe1 = 0;
			}
			else if (recipe2 == 6) {
				recipe2 = 0;
			}
			else if (recipe3 == 6) {
				recipe3 = 0;
			}
		}
	}
}

// メインゲームの中身(ステージ2)
int Episode2_Stage() {

	// ゲームオーバー処理中か？
	if (gGameoverCount > 0)
	{
		StopPlayMem(seWalk2);
		gGameoverCount--;
		if (gGameoverCount == 0)
		{
			continueflag = 2;
			selectTrg = STATE_NONE;
			// ゲームオーバーにする
			stateStage = GAME_OVER2;
			return GAME_OVER2;
		}
	}

	FrameWait2();			// 待ち時間
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
	if ((gFrameWait == 0) & (attackCooltime == 0) && (clearwait == 0) && (wallwait == 0)) {
		cameraProcess();		// カメラ移動
		ControllAlice2();		// アリス移動
		FrameControll();		// アイテムフレーム移動
	}

	// 敵移動
	EnemyMove2();

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
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
		HitCheckPlayerPreparation();
	}

	// プレイヤーとオブジェクトの当たり判定
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
		HitCheckPlayerObject();
	}

	// 壁が壊れる
	wallbreak2();

	// エフェクト処理
	ProcessEffect();

	//初めての調合
	FirstCreate();

	if (wallwait <= 0) {
		// 所持素材、アイテム確認画面表示
		if (gTrg & KEYIN_C) {
			if (selectTrg == STATE_NONE) {
				StopPlayMem(seWalk2);
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
			// ハートの女王
			if (clearflag == 1) {
				StopPlayMem(seWalk2);
				clearflag = 2;
				StopPlayMem(bgmBoss2);
				stateStage = STATE_EP2STORY3;
				ScriptCreate();
				Skipflag4 = 0;
				initblackin_ep2s3();
				return STATE_EP2STORY3;
			}
			// マッドハッター
			else if (clearflag == 2) {
				clearflag = 3;
				StopPlayMem(seWalk2);
				StopPlayMem(bgmBoss3);
				stateStage = STATE_EP2STORY4;
				ScriptCreate();
				Skipflag7 = 0;
				initblackin_ep2s4();
				return STATE_EP2STORY4;
			}
		}
	}

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/
void DrawEp2LProcess() {

	int i;

	// 画面を消す
	HCls();
	worldToView();

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// マップ
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		DrawMapChip_2_1_1();
		if (wallflag <= 2) {
			DrawMapChiplm_2_1_1();
			DrawFukidashi2();
		}
		DrawObject2();		// オブジェクト
		bgstage2 = STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		DrawMapChip_2_1_2();
		DrawObject2();		// オブジェクト
		bgstage2 = STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		DrawMapChip_2_1_3();
		if (wallflag <= 4) {
			DrawMapChiplm_2_1_3();
			DrawFukidashi2();
		}
		DrawObject2();		// オブジェクト
		bgstage2 = STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		DrawMapChip_2_2_1();
		if (wallflag <= 3) {
			DrawMapChiplm_2_2_1();
			DrawFukidashi2();
		}
		DrawObject2();		// オブジェクト
		bgstage2 = STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		DrawMapChip_2_2_2();
		DrawObject2();		// オブジェクト
		bgstage2 = STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		DrawMapChip_2_3();
		bgstage2 = STATE_EP2STAGE_3;
		break;
	case GAME_OVER2:
		if (bgstage2 == STATE_EP2STAGE1_1) {
			DrawMapChip_2_1_1();
			if (wallflag <= 2) {
				DrawMapChiplm_2_1_1();
			}
			DrawObject2();		// オブジェクト
		}
		else if (bgstage2 == STATE_EP2STAGE1_2) {
			DrawMapChip_2_1_2();
			DrawObject2();		// オブジェクト
		}
		else if (bgstage2 == STATE_EP2STAGE1_3) {
			DrawMapChip_2_1_3();
			if (wallflag <= 4) {
				DrawMapChiplm_2_1_3();
			}
			DrawObject2();		// オブジェクト
		}
		else if (bgstage2 == STATE_EP2STAGE2_1) {
			DrawMapChip_2_2_1();
			if (wallflag <= 3) {
				DrawMapChiplm_2_2_1();
			}
			DrawObject2();		// オブジェクト
		}
		else if (bgstage2 == STATE_EP2STAGE2_2) {
			DrawMapChip_2_2_2();
			DrawObject2();		// オブジェクト
		}
		else {
			DrawMapChip_2_3();
		}
		break;
	default:
		break;
	}

	// ドロップアイテム
	DropMaterial();

	// キャラクター
	DrawAlice2();

	// 敵攻撃エフェクト
	DrawEnemyAttack2();

	//敵
	DrawEnemy2();

	// マップの影になる部分
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		DrawMapChiphd_2_1_1();
		break;
	case STATE_EP2STAGE1_2:
		DrawMapChiphd_2_1_2();
		break;
	case STATE_EP2STAGE1_3:
		DrawMapChiphd_2_1_3();
		break;
	case STATE_EP2STAGE2_1:
		DrawMapChiphd_2_2_1();
		break;
	case STATE_EP2STAGE2_2:
		break;
	case STATE_EP2STAGE_3:
		DrawMapChiphd_2_3();
		break;
	}

	// オブジェクトに触れている
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		if ((obj[1].use == 1) || (obj[2].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE1_2:
		if ((obj[13].use == 1) || (obj[14].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE1_3:
		if ((obj[8].use == 1) || (obj[9].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE2_1:
		if ((obj[8].use == 1) || (obj[9].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE2_2:
		if ((obj[8].use == 1) || (obj[9].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE_3:
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
				for (i = 6; i < 12; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//アイテムを手に入れた
					}
				}
			}
			else if (frm[2].move == 2) {
				for (i = 12; i < 17; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//アイテムを手に入れた
					}
				}
			}
		}
	}

	// ボスのヒットポイント
	DrawEnemyHitpoint2();

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

	blackfadein_ep2();	// ブラックフェードイン
	blackfadeout_ep2();	// ブラックフェードアウト

	Systemfadein_out();		// 素材獲得時のフェードイン、アウト
	FirstCreatefadein();	// 調合時のフェードイン

	// ステージパートの間Flipする
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2) || (stateStage == STATE_EP2STAGE_3)) {
		Flip();
	}

}