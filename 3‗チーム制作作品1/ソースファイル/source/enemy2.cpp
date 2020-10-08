/*------------------------------------------------
*  @file enemy2.cpp
*  @brief ステージ2のエネミー処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ヘッダーファイルのインクルード
------------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"
#include	"vector.h"

#include	"game.h"
#include	"global.h"

#include    "alice.h"
#include    "enemy.h"
#include	"camera.h"
#include	"mapdata_2.h"
#include	"HitJudgment.h"
#include	"enemyattack.h"
#include	"recipe.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// 画像データ

int cgHeart[4 * 3];					// ハート兵
int cgDia[4 * 3];					// ダイア兵
int cgClover[4 * 3];				// クローバー兵
int cgSpade[4 * 3];					// スペード兵
int cgQueen[4 * 4];					// ハートの女王
int cgQueenDead;					// ハートの女王(死亡)
int cgHatterDead;					// マッドハッター(死亡)
int hearttbl[] = { 0, 1, 2 };		// 描画テーブル(ハート兵)
int diatbl[] = { 0, 1, 2 };			// 描画テーブル(ダイア兵)
int clovertbl[] = { 0, 1, 2 };		// 描画テーブル(クローバー兵)
int spadetbl[] = { 0, 1, 2 };		// 描画テーブル(スペード兵)
int queentbl[] = { 0, 1, 2, 3 };	// 描画テーブル(ハートの女王)
int cgHeartAttack;					// ハート兵攻撃
int cgDiaAttack;					// ダイア兵攻撃
int cgCloverAttack;					// クローバー兵攻撃
int cgSpadeAttack;					// スペード兵攻撃
int cgHeartF;						// 吹き出し(ハート兵)
int cgDiaF;							// 吹き出し(ダイア兵)
int cgCloverF;						// 吹き出し(クローバー兵)
int cgSpadeF;						// 吹き出し(スペード兵)

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 敵画像の読み込み(ステージ２)
void LoadCgEnemy2()
{
	LoadBlkTexture("res/trumpsoldiershart_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgHeart);
	LoadBlkTexture("res/trumpsoldiersdiamond_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgDia);
	LoadBlkTexture("res/trumpsoldierclovershart_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgClover);
	LoadBlkTexture("res/trumpsoldiersspade_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgSpade);
	LoadBlkTexture("res/queen.png", 40, 80, 4, 4, 4 * 4, cgQueen);
	LoadBlkTexture("res/madhatter_sheet.png", 40, 80, 4, 4, 4 * 4, cgHatter);

	cgHeartAttack = LoadTexture("res/hart_kougeki.png");
	cgDiaAttack = LoadTexture("res/diamond_kougeki.png");
	cgCloverAttack = LoadTexture("res/clover_kougeki.png");
	cgSpadeAttack = LoadTexture("res/spade_kougwki.png");

	cgHeartF = LoadTexture("res/heartF.png");
	cgDiaF = LoadTexture("res/diaF.png");
	cgCloverF = LoadTexture("res/cloverF.png");
	cgSpadeF = LoadTexture("res/spadeF.png");

	cgQueenDead = LoadTexture("res/queenend.png");
	cgHatterDead = LoadTexture("res/madhatterend.png");
}

/*
*  @brief 敵の基本情報
*  @param enemyId 敵の識別番号
*  @param enemytype 敵の種類
*/
void EnemyDef2(int enemyId, int enemytype) {
	switch (enemytype) {
	case ENEMY_HEART:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 8;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		en[enemyId].required = 0;
		break;
	case ENEMY_DIA:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 5;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_CLOVER:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 5;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_SPADE:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 5;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_QUEEN:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 40;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -1160;
		en[enemyId].hit_range_y = -1160;
		en[enemyId].hit_range_w = 2360;
		en[enemyId].hit_range_h = 2360;
		en[enemyId].hp = 50;
		en[enemyId].max_hp = 50;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_MAD_HATTER2:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 4;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 40;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -1160;
		en[enemyId].hit_range_y = -1160;
		en[enemyId].hit_range_w = 2360;
		en[enemyId].hit_range_h = 2360;
		en[enemyId].hp = 80;
		en[enemyId].max_hp = 80;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	}
}

// エネミー初期化(ステージ２)
void InitEnemy2()
{
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		en[i].use = 0;
		en[i].state = STATE_NONE;
		en[i].direction = ENEMY_STATE_DOWN;
		en[i].nohit_cnt = 0;
		en[i].damagecooltime = 0;
		en[i].itemdamagecooltime = 0;
		en[i].period = 0;
		en[i].period2 = 0;
		en[i].period3 = 0;
		en[i].period4 = 0;
		en[i].state_enemy = 0;
		en[i].recipe_no = 0;
	}

	if (stateStage == STATE_EP2STAGE2_1) {
		i = 1;
		en[i].required = 1;
		i = 3;
		en[i].required = 1;
		i = 6;
		en[i].required = 1;
	}
	else if (stateStage == STATE_EP2STAGE1_3) {
		i = 1;
		en[i].required = 1;
		i = 3;
		en[i].required = 1;
		i = 4;
		en[i].required = 1;
		i = 6;
		en[i].required = 1;
		i = 11;
		en[i].required = 1;
		i = 14;
		en[i].required = 1;
	}

	// ステージごとに出現させる敵を変える
	switch (stateStage) {
		// 一章1ステージ
	case STATE_EP2STAGE1_1:
		i = 0;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 54;
		en[i].y = 40 * 55;
		EnemyDef2(i, en[i].entype);

		i = 1;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 14;
		en[i].y = 40 * 55;
		EnemyDef2(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 9;
		en[i].y = 40 * 55;
		EnemyDef2(i, en[i].entype);

		i = 3;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 14;
			en[i].y = 40 * 45;
			EnemyDef2(i, en[i].entype);
		}

		i = 4;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 9;
		en[i].y = 40 * 45;
		EnemyDef2(i, en[i].entype);

		i = 5;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 15;
		en[i].y = 40 * 25;
		EnemyDef2(i, en[i].entype);

		i = 6;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 10;
			en[i].y = 40 * 25;
			en[i].recipe_no = 5;
			EnemyDef2(i, en[i].entype);
		}

		break;
	case STATE_EP2STAGE1_2:

		i = 0;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 49;
		en[i].y = 40 * 49;
		EnemyDef2(i, en[i].entype);

		i = 1;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 49;
			en[i].y = 40 * 32;
			en[i].recipe_no = 4;
			EnemyDef2(i, en[i].entype);
		}

		i = 2;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 33;
		en[i].y = 40 * 33;
		EnemyDef2(i, en[i].entype);

		i = 3;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 33;
		en[i].y = 40 * 21;
		EnemyDef2(i, en[i].entype);

		i = 4;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 11;
		en[i].y = 40 * 33;
		EnemyDef2(i, en[i].entype);

		i = 5;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 11;
		en[i].y = 40 * 20;
		EnemyDef2(i, en[i].entype);

		break;
	case STATE_EP2STAGE1_3:

		i = 0;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 27;
			en[i].y = 40 * 19;
			EnemyDef2(i, en[i].entype);
		}

		i = 1;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 26;
		en[i].y = 40 * 22;
		EnemyDef2(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 29;
		en[i].y = 40 * 20;
		EnemyDef2(i, en[i].entype);

		i = 3;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 36;
		en[i].y = 40 * 14;
		EnemyDef2(i, en[i].entype);

		i = 4;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 48;
		en[i].y = 40 * 5;
		EnemyDef2(i, en[i].entype);

		i = 5;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 52;
			en[i].y = 40 * 5;
			EnemyDef2(i, en[i].entype);
		}

		i = 6;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 44;
		en[i].y = 40 * 8;
		EnemyDef2(i, en[i].entype);

		break;
	case STATE_EP2STAGE2_1:

		i = 0;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 7;
		en[i].y = 40 * 24;
		EnemyDef2(i, en[i].entype);

		i = 1;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 5;
		en[i].y = 40 * 28;
		EnemyDef2(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 10;
		en[i].y = 40 * 30;
		EnemyDef2(i, en[i].entype);

		i = 3;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 20;
		en[i].y = 40 * 24;
		EnemyDef2(i, en[i].entype);

		i = 4;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 22;
			en[i].y = 40 * 29;
			en[i].recipe_no = 6;
			EnemyDef2(i, en[i].entype);
		}

		i = 5;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 26;
		en[i].y = 40 * 22;
		EnemyDef2(i, en[i].entype);

		i = 6;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 35;
		en[i].y = 40 * 23;
		EnemyDef2(i, en[i].entype);

		i = 7;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 37;
		en[i].y = 40 * 26;
		EnemyDef2(i, en[i].entype);

		i = 8;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 40;
		en[i].y = 40 * 30;
		EnemyDef2(i, en[i].entype);

		i = 9;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 6;
		en[i].y = 40 * 39;
		EnemyDef2(i, en[i].entype);

		i = 10;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 9;
		en[i].y = 40 * 42;
		EnemyDef2(i, en[i].entype);

		i = 11;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 7;
			en[i].y = 40 * 45;
			EnemyDef2(i, en[i].entype);
		}

		i = 12;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 38;
		en[i].y = 40 * 39;
		EnemyDef2(i, en[i].entype);

		i = 13;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 36;
		en[i].y = 40 * 43;
		EnemyDef2(i, en[i].entype);

		i = 14;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 37;
			en[i].y = 40 * 45;
			EnemyDef2(i, en[i].entype);
		}

		break;
	case STATE_EP2STAGE2_2:
		break;
	case STATE_EP2STAGE_3:

		if (clearflag == 1) {
			i = 0;
			en[i].entype = ENEMY_QUEEN;
			en[i].x = 40 * 18;
			en[i].y = 40 * 8;
			EnemyDef2(i, en[i].entype);
		}

		if (en[0].use == 0) {
			i = 1;
			en[i].entype = ENEMY_MAD_HATTER2;
			en[i].x = 40 * 18;
			en[i].y = 40 * 8;
			EnemyDef2(i, en[i].entype);
		}

		break;
	default:
		break;
	}
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int CheckHitMapChipEnemy_2_1_1(int x, int y)
{
	if (stateStage == STATE_EP2STAGE1_1) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE2_1_1_W && 0 <= y && y < MAPSIZE2_1_1_H) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap_2_1_1[y *MAPSIZE2_1_1_W + x];
			int chip_no2 = nMaplm_2_1_1[y *MAPSIZE2_1_1_W + x];

			if (required_count < 3) {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					101,102,103,104,105,120,-1		// 最後
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// 当たった
						return chip_no;
					}
					else if (chip_no2 == idtable[i]) {
						// 当たった
						return chip_no2;
					}
					i++;
				}
			}
			else {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					101,103,104,105,120,-1		// 最後
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// 当たった
						return chip_no;
					}
					i++;
				}
			}
		}

		// 当たっていない
		return 0;
	}
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int CheckHitMapChipEnemy_2_1_2(int x, int y)
{
	if (stateStage == STATE_EP2STAGE1_2) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE2_1_2_W && 0 <= y && y < MAPSIZE2_1_2_H) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap_2_1_2[y *MAPSIZE2_1_2_W + x];

			// 当たるIDかどうかをチェック
			int idtable[] =
			{
				101,102,103,104,105,119,120,-1		// 最後
			};
			int i = 0;
			while (idtable[i] != -1) {
				if (chip_no == idtable[i]) {
					// 当たった
					return chip_no;
				}
				i++;
			}
		}

		// 当たっていない
		return 0;
	}
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int CheckHitMapChipEnemy_2_1_3(int x, int y)
{
	if (stateStage == STATE_EP2STAGE1_3) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE2_1_3_W && 0 <= y && y < MAPSIZE2_1_3_H) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap_2_1_3[y *MAPSIZE2_1_3_W + x];
			int chip_no2 = nMaplm_2_1_3[y *MAPSIZE2_1_3_W + x];

			if (required_count < 8) {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					101,102,118,133,-1		// 最後
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// 当たった
						return chip_no;
					}
					else if (chip_no2 == idtable[i]) {
						// 当たった
						return chip_no2;
					}
					i++;
				}
			}
			else {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					101,118,133,-1		// 最後
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// 当たった
						return chip_no;
					}
					i++;
				}
			}
		}

		// 当たっていない
		return 0;
	}
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int CheckHitMapChipEnemy_2_2_1(int x, int y)
{
	if (stateStage == STATE_EP2STAGE2_1) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE2_2_1_W && 0 <= y && y < MAPSIZE2_2_1_H) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap_2_2_1[y *MAPSIZE2_2_1_W + x];
			int chip_no2 = nMaplm_2_2_1[y *MAPSIZE2_2_1_W + x];

			if (required_count < 6) {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					101,102,118,119,-1		// 最後
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// 当たった
						return chip_no;
					}
					else if (chip_no2 == idtable[i]) {
						// 当たった
						return chip_no2;
					}
					i++;
				}
			}
			else {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					101,118,119,-1		// 最後
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// 当たった
						return chip_no;
					}
					i++;
				}
			}
		}

		// 当たっていない
		return 0;
	}
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int CheckHitMapChipEnemy_2_3(int x, int y)
{
	if (stateStage == STATE_EP2STAGE_3) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE2_3_W && 0 <= y && y < MAPSIZE2_3_H) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap_2_3[y *MAPSIZE2_3_W + x];
			// 当たるIDかどうかをチェック
			int idtable[] =
			{
				101,-1		// 最後
			};
			int i = 0;
			while (idtable[i] != -1) {
				if (chip_no == idtable[i]) {
					// 当たった
					return chip_no;
				}
				i++;
			}
		}

		// 当たっていない
		return 0;
	}
}

// キャラとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//   i = キャラ番号
//   mx = Xの移動方向(マイナス:0:プラス)
//   my = Yの移動方向(マイナス:0:プラス)
// 戻値：
//   0 : 当たってない
//   1 : 当たった
int IsHitMapChipEnemy_2_1_1(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE1_1) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// この敵は使用中か？
			if (en[i].use == 0)
			{	// 未使用
				continue;
			}
			// キャラ矩形を作成する
			int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)は、マップチップの座標（チップ単位）
					// この位置のチップは当たるか？
					int chip_no = CheckHitMapChipEnemy_2_1_1(x, y);
					if (chip_no != 0) {	// このチップと当たった。
						// X,Yの移動方向を見て、その反対方向に補正する
						if (mx < 0) {	// 左に動いていたので、右に補正
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// 右に動いていたので、左に補正
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// 下に動いていたので、上に補正
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// 上に動いていたので、下に補正
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// 当たったので戻る
						return 1;
					}
				}
			}
		}
		// 当たらなかった
		return 0;
	}
}

// キャラとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//   i = キャラ番号
//   mx = Xの移動方向(マイナス:0:プラス)
//   my = Yの移動方向(マイナス:0:プラス)
// 戻値：
//   0 : 当たってない
//   1 : 当たった
int IsHitMapChipEnemy_2_1_2(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE1_2) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// この敵は使用中か？
			if (en[i].use == 0)
			{	// 未使用
				continue;
			}
			// キャラ矩形を作成する
			int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)は、マップチップの座標（チップ単位）
					// この位置のチップは当たるか？
					int chip_no = CheckHitMapChipEnemy_2_1_2(x, y);
					if (chip_no != 0) {	// このチップと当たった。
						// X,Yの移動方向を見て、その反対方向に補正する
						if (mx < 0) {	// 左に動いていたので、右に補正
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// 右に動いていたので、左に補正
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// 下に動いていたので、上に補正
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// 上に動いていたので、下に補正
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// 当たったので戻る
						return 1;
					}
				}
			}
		}
		// 当たらなかった
		return 0;
	}
}

// キャラとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//   i = キャラ番号
//   mx = Xの移動方向(マイナス:0:プラス)
//   my = Yの移動方向(マイナス:0:プラス)
// 戻値：
//   0 : 当たってない
//   1 : 当たった
int IsHitMapChipEnemy_2_1_3(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE1_3) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// この敵は使用中か？
			if (en[i].use == 0)
			{	// 未使用
				continue;
			}
			// キャラ矩形を作成する
			int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)は、マップチップの座標（チップ単位）
					// この位置のチップは当たるか？
					int chip_no = CheckHitMapChipEnemy_2_1_3(x, y);
					if (chip_no != 0) {	// このチップと当たった。
						// X,Yの移動方向を見て、その反対方向に補正する
						if (mx < 0) {	// 左に動いていたので、右に補正
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// 右に動いていたので、左に補正
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// 下に動いていたので、上に補正
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// 上に動いていたので、下に補正
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// 当たったので戻る
						return 1;
					}
				}
			}
		}
		// 当たらなかった
		return 0;
	}
}

// キャラとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//   i = キャラ番号
//   mx = Xの移動方向(マイナス:0:プラス)
//   my = Yの移動方向(マイナス:0:プラス)
// 戻値：
//   0 : 当たってない
//   1 : 当たった
int IsHitMapChipEnemy_2_2_1(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE2_1) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// この敵は使用中か？
			if (en[i].use == 0)
			{	// 未使用
				continue;
			}
			// キャラ矩形を作成する
			int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)は、マップチップの座標（チップ単位）
					// この位置のチップは当たるか？
					int chip_no = CheckHitMapChipEnemy_2_2_1(x, y);
					if (chip_no != 0) {	// このチップと当たった。
						// X,Yの移動方向を見て、その反対方向に補正する
						if (mx < 0) {	// 左に動いていたので、右に補正
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// 右に動いていたので、左に補正
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// 下に動いていたので、上に補正
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// 上に動いていたので、下に補正
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// 当たったので戻る
						return 1;
					}
				}
			}
		}
		// 当たらなかった
		return 0;
	}
}

// キャラとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//   i = キャラ番号
//   mx = Xの移動方向(マイナス:0:プラス)
//   my = Yの移動方向(マイナス:0:プラス)
// 戻値：
//   0 : 当たってない
//   1 : 当たった
int IsHitMapChipEnemy_2_3(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE_3) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// この敵は使用中か？
			if (en[i].use == 0)
			{	// 未使用
				continue;
			}
			// キャラ矩形を作成する
			int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)は、マップチップの座標（チップ単位）
					// この位置のチップは当たるか？
					int chip_no = CheckHitMapChipEnemy_2_3(x, y);
					if (chip_no != 0) {	// このチップと当たった。
						// X,Yの移動方向を見て、その反対方向に補正する
						if (mx < 0) {	// 左に動いていたので、右に補正
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// 右に動いていたので、左に補正
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// 下に動いていたので、上に補正
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// 上に動いていたので、下に補正
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// 当たったので戻る
						return 1;
					}
				}
			}
		}
		// 当たらなかった
		return 0;
	}
}

// エネミー移動(ステージ２)
void EnemyMove2()
{
	int i;
	int j = 0;

	// 移動をフラグで規制
	if ((selectTrg == STATE_NONE) && (check == STATE_NONE) && (GetRecipe < 1) && (wallwait == 0)) {
		for (i = 0; i < ENEMY_MAX; i++) {
			// この敵は使用中か？
			if (en[i].use == 0)
			{	// 未使用
				continue;
			}
			// ダメージを食らっているか
			if ((en[i].damagecooltime <= 0) & (en[i].itemdamagecooltime <= 0) & (enatk[i].use == 0) & (en[i].state_enemy == 0)) {
				// プレイヤーが行動範囲に入っていない
				if (en[i].state == STATE_NONE) {
					if (en[i].period > 0) {
						en[i].period--;
					}
					if (en[i].period > 0) {
						// 左に移動
						if (en[i].direction == ENEMY_STATE_RIGHT) {
							en[i].x -= en[i].spd;
						}
						// 右に移動
						if (en[i].direction == ENEMY_STATE_LEFT) {
							en[i].x += en[i].spd;
						}
					}
					if (en[i].period2 > 0) {
						en[i].period2--;
					}
					if (en[i].period2 > 0) {
						// 上に移動
						if (en[i].direction == ENEMY_STATE_DOWN) {
							en[i].y -= en[i].spd;
						}
						// 下に移動
						if (en[i].direction == ENEMY_STATE_UP) {
							en[i].y += en[i].spd;
						}
					}
					if (en[i].period3 > 0) {
						en[i].period3--;
					}
					else {
						en[i].period3 = 360;
					}
					// 下に移動
					if (en[i].period3 > 240) {
						en[i].direction = ENEMY_STATE_DOWN;
						en[i].y += en[i].spd;
						IsHitMapChipEnemy_2_1_1(j, 0, 1);
						IsHitMapChipEnemy_2_1_2(j, 0, 1);
						IsHitMapChipEnemy_2_1_3(j, 0, 1);
						IsHitMapChipEnemy_2_2_1(j, 0, 1);
						IsHitMapChipEnemy_2_3(j, 0, 1);
					}
					// 上に移動
					else if (en[i].period3 < 180 & en[i].period3 > 60) {
						en[i].direction = ENEMY_STATE_UP;
						en[i].y -= en[i].spd;
						IsHitMapChipEnemy_2_1_1(j, 0, -1);
						IsHitMapChipEnemy_2_1_2(j, 0, -1);
						IsHitMapChipEnemy_2_1_3(j, 0, -1);
						IsHitMapChipEnemy_2_2_1(j, 0, -1);
						IsHitMapChipEnemy_2_3(j, 0, -1);
					}
					else if ((en[i].period3 < 240 & en[i].period3 > 180) || (en[i].period3 < 60 & en[i].period3 > 0)) {
						if (en[i].direction == ENEMY_STATE_DOWN) {
							IsHitMapChipEnemy_2_1_1(j, 0, 1);
							IsHitMapChipEnemy_2_1_2(j, 0, 1);
							IsHitMapChipEnemy_2_1_3(j, 0, 1);
							IsHitMapChipEnemy_2_2_1(j, 0, 1);
							IsHitMapChipEnemy_2_3(j, 0, 1);
						}
						else {
							IsHitMapChipEnemy_2_1_1(j, 0, -1);
							IsHitMapChipEnemy_2_1_2(j, 0, -1);
							IsHitMapChipEnemy_2_1_3(j, 0, -1);
							IsHitMapChipEnemy_2_2_1(j, 0, -1);
							IsHitMapChipEnemy_2_3(j, 0, -1);
						}
					}
				}
				// プレイヤーが行動範囲に入った
				if (en[i].state == STATE_ONE) {
					if ((en[i].direction == ENEMY_STATE_DOWN) ||
						(en[i].direction == ENEMY_STATE_UP) ||
						(en[i].direction == ENEMY_STATE_RIGHT) ||
						(en[i].direction == ENEMY_STATE_LEFT)) {
						if (en[i].period4 > 0) {
							en[i].period4--;
						}
						else {
							en[i].period4 = 20;

							Vector2 d;
							d.x = al.x - en[i].x;
							d.y = (al.y + 40) - en[i].y;
							Normalize(&d, &d);//長さ1単位ベクトル
							MulVector(&d, &d, en[i].spd);//スピードの長さのベクトル
							// xとyの差分を比べる
							if (d.x * d.x > d.y * d.y) {
								d.y = 0;
							}
							else {
								d.x = 0;
							}
							en[i].d = d;
						}
						if (en[i].d.x > 0) {
							// 右に移動
							en[i].direction = ENEMY_STATE_RIGHT;
							en[i].x += en[i].d.x;
							IsHitMapChipEnemy_2_1_1(j, 1, 0);
							IsHitMapChipEnemy_2_1_2(j, 1, 0);
							IsHitMapChipEnemy_2_1_3(j, 1, 0);
							IsHitMapChipEnemy_2_2_1(j, 1, 0);
							IsHitMapChipEnemy_2_3(j, 1, 0);
						}
						else if (en[i].d.x < 0) {
							// 左に移動
							en[i].direction = ENEMY_STATE_LEFT;
							en[i].x += en[i].d.x;
							IsHitMapChipEnemy_2_1_1(j, -1, 0);
							IsHitMapChipEnemy_2_1_2(j, -1, 0);
							IsHitMapChipEnemy_2_1_3(j, -1, 0);
							IsHitMapChipEnemy_2_2_1(j, -1, 0);
							IsHitMapChipEnemy_2_3(j, -1, 0);
						}
						else if (en[i].d.y > 0) {
							// 下に移動
							en[i].direction = ENEMY_STATE_DOWN;
							en[i].y += en[i].d.y;
							IsHitMapChipEnemy_2_1_1(j, 0, 1);
							IsHitMapChipEnemy_2_1_2(j, 0, 1);
							IsHitMapChipEnemy_2_1_3(j, 0, 1);
							IsHitMapChipEnemy_2_2_1(j, 0, 1);
							IsHitMapChipEnemy_2_3(j, 0, 1);
						}
						else if (en[i].d.y < 0) {
							// 上に移動
							en[i].direction = ENEMY_STATE_UP;
							en[i].y += en[i].d.y;
							IsHitMapChipEnemy_2_1_1(j, 0, -1);
							IsHitMapChipEnemy_2_1_2(j, 0, -1);
							IsHitMapChipEnemy_2_1_3(j, 0, -1);
							IsHitMapChipEnemy_2_2_1(j, 0, -1);
							IsHitMapChipEnemy_2_3(j, 0, -1);
						}
					}
					AttackCooldinate2(i);	// 攻撃判定の更新
				}
			}
			// 無敵カウンタの処理
			if (en[i].nohit_cnt > 0) {
				en[i].nohit_cnt--;
			}
		}
	}
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// エネミー描画(ステージ２)
void DrawEnemy2() {
	int i;

	for (i = 0; i < ENEMY_MAX; i++) {
		// この敵は使用中か？
		if (en[i].use == 0)
		{	// 未使用
			continue;
		}
		en[i].anim_count++;
		// 無敵中は一定間隔で描画しない
		if (en[i].nohit_cnt == 0 || (en[i].nohit_cnt % 10) < 7)
		{
			// 敵のタイプによって描画を変える
			switch (en[i].entype)
			{
			case ENEMY_HEART:
				// 下向き
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 120) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 160) - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[0 * 3 + hearttbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				// 上向き
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 160) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 120) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[1 * 3 + hearttbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				// 右向き
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh((enatk[i].x + 120) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh((enatk[i].x + 160) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[3 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				// 左向き
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh((enatk[i].x + 160) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 120) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[2 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				break;
			case ENEMY_DIA:
				// 下向き
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgDia[0 * 3 + diatbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				// 上向き
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[1 * 3 + hearttbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				// 右向き
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[3 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				// 左向き
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[2 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				break;
			case ENEMY_CLOVER:
				// 下向き
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[0 * 3 + clovertbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				// 上向き
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[1 * 3 + clovertbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				// 右向き
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[3 * 3 + clovertbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				// 左向き
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[2 * 3 + clovertbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				break;
			case ENEMY_SPADE:
				// 下向き
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[0 * 3 + spadetbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				// 上向き
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[1 * 3 + spadetbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				// 右向き
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[3 * 3 + spadetbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				// 左向き
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[2 * 3 + spadetbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				break;
			case ENEMY_QUEEN:
				if (en[i].state_enemy == 0) {
					// 下向き
					if (en[i].direction == ENEMY_STATE_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[0 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}
					// 上向き
					if (en[i].direction == ENEMY_STATE_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[3 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}
					// 右向き
					if (en[i].direction == ENEMY_STATE_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[2 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}
					// 左向き
					if (en[i].direction == ENEMY_STATE_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[1 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}

					// 攻撃時の描画
					// 下向き
					if (en[i].direction == ENEMY_STATE_ATTACK_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[0 * 4 + queentbl[3]]);
					}
					// 上向き
					if (en[i].direction == ENEMY_STATE_ATTACK_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[3 * 4 + queentbl[3]]);
					}
					// 右向き
					if (en[i].direction == ENEMY_STATE_ATTACK_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[2 * 4 + queentbl[3]]);
					}
					// 左向き
					if (en[i].direction == ENEMY_STATE_ATTACK_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[1 * 4 + queentbl[3]]);
					}
				}
				else {
					DrawMemTh(en[i].x - 20 - cv.view_x, en[i].y + 50 - cv.view_y, cgQueenDead);
				}
				break;
			case ENEMY_MAD_HATTER2:
				if (en[i].state_enemy == 0) {
					// 下向き
					if (en[i].direction == ENEMY_STATE_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[0 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}
					// 上向き
					if (en[i].direction == ENEMY_STATE_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[3 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}
					// 右向き
					if (en[i].direction == ENEMY_STATE_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[2 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}
					// 左向き
					if (en[i].direction == ENEMY_STATE_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[1 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}

					// 攻撃時の描画
					// 下向き
					if (en[i].direction == ENEMY_STATE_ATTACK_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[0 * 4 + hattbl[3]]);
					}
					// 上向き
					if (en[i].direction == ENEMY_STATE_ATTACK_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[3 * 4 + hattbl[3]]);
					}
					// 右向き
					if (en[i].direction == ENEMY_STATE_ATTACK_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[2 * 4 + hattbl[3]]);
					}
					// 左向き
					if (en[i].direction == ENEMY_STATE_ATTACK_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[1 * 4 + hattbl[3]]);
					}
				}
				else {
					DrawMemTh(en[i].x - 20 - cv.view_x, en[i].y + 50 - cv.view_y, cgHatterDead);
				}
				break;
			default:
				break;
			}
		}
	}
}

// 敵の体力描画(ボスのみ、ステージ２)
void DrawEnemyHitpoint2() {
	switch (stateStage) {
	case STATE_EP2STAGE_3:
		// ハートの女王
		int i = 0;
		// 敵が生きていれば
		if (en[i].use == 1) {
			if (en[i].state_enemy != 1) {
				RECT rc = { en[i].x - 40, en[i].y - 40, en[i].x + (320 - 240), en[i].y - 20 };		// left, top, right, bottom
				int w_max = rc.right - rc.left;		// バーの横幅サイズ

				// まず下地として赤で塗りつぶす
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.right - cv.view_x, rc.bottom - cv.view_y, GetColor(255, 0, 0));

				// HP量の横幅サイズはいくつか計算
				int w = LerpN(en[i].hp, en[i].max_hp, 0, w_max);

				// HP量を緑で塗りつぶす
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.left + w - cv.view_x, rc.bottom - cv.view_y, GetColor(0, 192, 0));

				// 数値を表示（影文字）
				//DrawPrintf(rc.left + 4 + 1 - cv.view_x, rc.top + 4 + 1 - cv.view_y, GetColor(0, 0, 0), "%d / %d", en[i].hp, en[i].max_hp);
				//DrawPrintf(rc.left + 4 - cv.view_x, rc.top + 4 - cv.view_y, GetColor(255, 255, 255), "%d / %d", en[i].hp, en[i].max_hp);
			}
		}
		
		// マッドハッター
		i = 1;
		if (en[i].use == 1) {
			if (en[i].state_enemy != 1) {
				RECT rc = { en[i].x - 40, en[i].y - 40, en[i].x + (320 - 240), en[i].y - 20 };		// left, top, right, bottom
				int w_max = rc.right - rc.left;		// バーの横幅サイズ

				// まず下地として赤で塗りつぶす
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.right - cv.view_x, rc.bottom - cv.view_y, GetColor(255, 0, 0));

				// HP量の横幅サイズはいくつか計算
				int w = LerpN(en[i].hp, en[i].max_hp, 0, w_max);

				// HP量を緑で塗りつぶす
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.left + w - cv.view_x, rc.bottom - cv.view_y, GetColor(0, 192, 0));

			}
		}
		break;
	}
}