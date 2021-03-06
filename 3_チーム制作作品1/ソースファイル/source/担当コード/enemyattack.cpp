/*------------------------------------------------
*  @file enemyattack.cpp
*  @brief ステージ１のエネミー攻撃処理
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
#include    "enemy.h"
#include	"enemyattack.h"
#include	"camera.h"
#include	"HitJudgment.h"
#include	"game_effect.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// 画像データ

int cgAttackJudgment_1;		// 当たり範囲１
int cgAttackJudgment_2;		// 当たり範囲２
int cgAttackJudgment_3;		// 当たり範囲３
int cgAttackJudgment_4;		// 当たり範囲４
int cgAttackJudgment_5;		// 当たり範囲５
int cgAttackJudgment_6;		// 当たり範囲６
int cgAttackJudgment_7;		// 当たり範囲７
int cgAttackJudgment_8;		// 当たり範囲８
int cgAttackJudgment_9;		// 当たり範囲９
int cgAttackJudgment_10;	// 当たり範囲１０
int cgAttackJudgment_11;	// 当たり範囲１１
int cgAttackJudgment_12;	// 当たり範囲１２
int cgAttackJudgment_13;	// 当たり範囲１３
int cgAttackJudgment_14;	// 当たり範囲１４
int cgAttackJudgment_15;	// 当たり範囲１５

int enemyattackCooltime;		// 攻撃のクールタイム

// 敵攻撃の情報
struct ENEMYATTACK enatk[ENEMY_MAX];

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 画像読み込み
void LoadCgEnemyAttack() {
	cgAttackJudgment_1 = LoadTexture("res/attackjudgment_1.png");
	cgAttackJudgment_2 = LoadTexture("res/attackjudgment_2.png");
	cgAttackJudgment_3 = LoadTexture("res/attackjudgment_3.png");
	cgAttackJudgment_4 = LoadTexture("res/attackjudgment_4.png");
	cgAttackJudgment_5 = LoadTexture("res/attackjudgment_5.png");
	cgAttackJudgment_6 = LoadTexture("res/attackjudgment_6.png");
	cgAttackJudgment_7 = LoadTexture("res/attackjudgment_7.png");
	cgAttackJudgment_8 = LoadTexture("res/attackjudgment_8.png");
}

// 初期化
void InitEnemyAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		enatk[i].use = 0;
		enatk[i].x = 0;
		enatk[i].y = 0;
		enatk[i].x2 = 0;
		enatk[i].y2 = 0;
		enatk[i].x3 = 0;
		enatk[i].y3 = 0;
		enatk[i].x4 = 0;
		enatk[i].y4 = 0;
		enatk[i].hit_x = 0;
		enatk[i].hit_y = 0;
		enatk[i].hit_w = 0;
		enatk[i].hit_h = 0;
		enatk[i].hit_x2 = 0;
		enatk[i].hit_y2 = 0;
		enatk[i].hit_w2 = 0;
		enatk[i].hit_h2 = 0;
		enatk[i].range_x = 0;
		enatk[i].range_y = 0;
		enatk[i].range_w = 0;
		enatk[i].range_h = 0;
		enatk[i].range_x2 = 0;
		enatk[i].range_y2 = 0;
		enatk[i].range_w2 = 0;
		enatk[i].range_h2 = 0;
		enatk[i].attack_time = 0;
		enatk[i].attack_state = 0;
		enatk[i].select_attack = 0;
		enatk[i].rand = 0;
	}
	enemyattackCooltime = 0;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

/*
*  @brief 攻撃判定の更新
*  @param enemyId 敵の識別番号
*/
void AttackCooldinate(int enemyId) {
	// プレイヤーが敵の攻撃範囲内に入っている
	if (en[enemyId].state == STATE_ONE) {
		if (enatk[enemyId].use == 0) {
			if ((en[enemyId].direction == ENEMY_STATE_DOWN) ||
				(en[enemyId].direction == ENEMY_STATE_LEFT) ||
				(en[enemyId].direction == ENEMY_STATE_RIGHT) ||
				(en[enemyId].direction == ENEMY_STATE_UP)) {
				// 敵の状態を攻撃状態にする
				if (en[enemyId].direction == ENEMY_STATE_DOWN) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_DOWN;
				}
				if (en[enemyId].direction == ENEMY_STATE_LEFT) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_LEFT;
				}
				if (en[enemyId].direction == ENEMY_STATE_RIGHT) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_RIGHT;
				}
				if (en[enemyId].direction == ENEMY_STATE_UP) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_UP;
				}
			}
			// 敵ごとに攻撃判定を変える
			switch (en[enemyId].entype)
			{
				// 芋虫
			case ENEMY_CATERPILLAR:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				break;
				// マタンゴ
			case ENEMY_MATANGO:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 80;
					enatk[enemyId].rand = 0;
				}
				else {
					enatk[enemyId].w = 80;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 4) * 3;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 50;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 80;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 50;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 80;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w / 2;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 50;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 80;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 50;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 80;
				}
				break;
				// マージマタンゴ
			case ENEMY_MERGE_MATANGO:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 160;
					enatk[enemyId].rand = 0;
				}
				else {
					enatk[enemyId].w = 160;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 8) * 3;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 130;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 160;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 130;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 160;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w / 4;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 130;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 160;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 130;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 160;
				}
				break;
				// 狼
			case ENEMY_WOLF:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x + 10;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 2) * 3;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + (enatk[enemyId].w / 2) * 3;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x + 10;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				break;
				// マッドハッター
			case ENEMY_MAD_HATTER:
				if (enatk[enemyId].select_attack == 0) {
					if (enatk[enemyId].attack_state == 0) {
						enatk[enemyId].rand = rand() % 3;
					}
					// 前方攻撃
					if (enatk[enemyId].rand == 0) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 120;
							enatk[enemyId].h = 200;
							enatk[enemyId].select_attack = 20;
						}
						else {
							enatk[enemyId].w = 200;
							enatk[enemyId].h = 120;
							enatk[enemyId].select_attack = 20;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w / 3;
							enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 5) * 2;
							enatk[enemyId].x2 = en[enemyId].x;
							enatk[enemyId].y2 = en[enemyId].y + (enatk[enemyId].h / 5) * 2;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 3;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 5) * 2;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 40;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 120;
							enatk[enemyId].range_h = 200;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y = en[enemyId].y;
							enatk[enemyId].x2 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y2 = en[enemyId].y + enatk[enemyId].h / 3;
							enatk[enemyId].x3 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 40;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 120;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
							enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w / 5;
							enatk[enemyId].y = en[enemyId].y;
							enatk[enemyId].x2 = en[enemyId].x + enatk[enemyId].w / 5;
							enatk[enemyId].y2 = en[enemyId].y + enatk[enemyId].h / 3;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 5;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 40;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 120;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w / 3;
							enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].x2 = en[enemyId].x;
							enatk[enemyId].y2 = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 3;
							enatk[enemyId].y3 = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 40;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 120;
							enatk[enemyId].range_h = 200;
						}
					}
					// 爆弾攻撃
					else if (enatk[enemyId].rand == 1) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 120;
							enatk[enemyId].h = 120;
							enatk[enemyId].select_attack = 20;
						}
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y = en[enemyId].y - (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].x2 = en[enemyId].x + (enatk[enemyId].w / 3);
							enatk[enemyId].y2 = en[enemyId].y - (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].x3 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].x4 = en[enemyId].x + (enatk[enemyId].w / 3);
							enatk[enemyId].y4 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].hit_x = 20;
							enatk[enemyId].hit_y = 20;
							enatk[enemyId].hit_w = 100;
							enatk[enemyId].hit_h = 100;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 120;
							enatk[enemyId].range_h = 120;
						}
					}
					// ナイフ攻撃
					else if (enatk[enemyId].rand == 2) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 160;
							enatk[enemyId].h = 160;
							enatk[enemyId].select_attack = 20;
						}
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 4;
							enatk[enemyId].x2 = en[enemyId].x;
							enatk[enemyId].y2 = en[enemyId].y - (enatk[enemyId].h / 4) * 3;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 4;
							enatk[enemyId].y3 = en[enemyId].y + enatk[enemyId].h / 4;
							enatk[enemyId].x4 = en[enemyId].x;
							enatk[enemyId].y4 = en[enemyId].y + enatk[enemyId].h / 2;
							enatk[enemyId].hit_x = 0;
							enatk[enemyId].hit_y = 0;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 40;
							enatk[enemyId].hit_x2 = 0;
							enatk[enemyId].hit_y2 = 0;
							enatk[enemyId].hit_w2 = 40;
							enatk[enemyId].hit_h2 = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 160;
							enatk[enemyId].range_h = 40;
							enatk[enemyId].range_x2 = 0;
							enatk[enemyId].range_y2 = 0;
							enatk[enemyId].range_w2 = 40;
							enatk[enemyId].range_h2 = 160;
						}
					}
				}
				break;
			default:
				break;
			}
			// 攻撃までの時間があれば
			if (enatk[enemyId].attack_time > 0) {
				enatk[enemyId].attack_time--;		// 攻撃までの時間を減らす
				// 攻撃までの時間が0なら
				if (enatk[enemyId].attack_time == 0) {
					if (en[enemyId].entype == ENEMY_MAD_HATTER) {
						// 攻撃によってエフェクトを変える
						if (enatk[enemyId].rand == 0) {
							// エフェクト処理
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
						}
						else if (enatk[enemyId].rand == 1) {
							// エフェクト処理
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x4, enatk[enemyId].y4, enemyId);
						}
						else if (enatk[enemyId].rand == 2) {
							// エフェクト処理
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x4, enatk[enemyId].y4, enemyId);
						}
					}
					HitCheckEnemyAttack();			// プレイヤーと敵攻撃の当たり判定
					EnemyAttack(enemyId);			// 攻撃を行った
				}
			}
			// アリスが攻撃範囲に入っているか
			// 攻撃によって攻撃のクールタイムなどを変える
			if (enatk[enemyId].rand == 0) {
				if (IsHitEnemyAttack(enemyId)) {
					if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
						if (en[enemyId].entype == ENEMY_MAD_HATTER) {
							enatk[enemyId].attack_time = 20;		// 攻撃までの時間
							enatk[enemyId].select_attack = 0;		// 攻撃パターンの初期化
						}
						else if ((en[enemyId].entype == ENEMY_CATERPILLAR) || (en[enemyId].entype == ENEMY_WOLF)) {
							enatk[enemyId].attack_time = 10;		// 攻撃までの時間
						}
						else {
							enatk[enemyId].attack_time = 20;		// 攻撃までの時間
						}
						enatk[enemyId].attack_state = 1;		// 攻撃状態にする
					}
				}
			}
			else if (enatk[enemyId].rand == 1) {
				if (IsHitEnemyAttack2(enemyId)) {
					if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
						if (en[enemyId].entype == ENEMY_MAD_HATTER) {
							enatk[enemyId].attack_time = 20;		// 攻撃までの時間
							enatk[enemyId].select_attack = 0;		// 攻撃パターンの初期化
						}
						else {
							enatk[enemyId].attack_time = 20;		// 攻撃までの時間
						}
						enatk[enemyId].attack_state = 1;		// 攻撃状態にする
					}
				}
			}
			else if (enatk[enemyId].rand == 2) {
				if (IsHitEnemyAttack3(enemyId)) {
					if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
						if (en[enemyId].entype == ENEMY_MAD_HATTER) {
							enatk[enemyId].attack_time = 15;		// 攻撃までの時間
							enatk[enemyId].select_attack = 0;		// 攻撃パターンの初期化
						}
						else {
							enatk[enemyId].attack_time = 20;		// 攻撃までの時間
						}
						enatk[enemyId].attack_state = 1;		// 攻撃状態にする
					}
				}
			}

			// 敵が攻撃状態に入っていない
			if (enatk[enemyId].attack_state == 0) {
				if (enatk[enemyId].select_attack > 0) {
					enatk[enemyId].select_attack--;
				}
				// 敵の状態を元に戻す
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					en[enemyId].direction = ENEMY_STATE_DOWN;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					en[enemyId].direction = ENEMY_STATE_LEFT;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					en[enemyId].direction = ENEMY_STATE_RIGHT;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					en[enemyId].direction = ENEMY_STATE_UP;
				}
				// 敵攻撃判定の初期化
				enatk[enemyId].x = 0;
				enatk[enemyId].y = 0;
				enatk[enemyId].x2 = 0;
				enatk[enemyId].y2 = 0;
				enatk[enemyId].x3 = 0;
				enatk[enemyId].y3 = 0;
				enatk[enemyId].x4 = 0;
				enatk[enemyId].y4 = 0;
				enatk[enemyId].hit_x = 0;
				enatk[enemyId].hit_y = 0;
				enatk[enemyId].hit_w = 0;
				enatk[enemyId].hit_h = 0;
				enatk[enemyId].range_x = 0;
				enatk[enemyId].range_y = 0;
				enatk[enemyId].range_w = 0;
				enatk[enemyId].range_h = 0;
				enatk[enemyId].attack_time = 0;
			}
		}
	}
	else {
		// 敵攻撃判定の初期化
		enatk[enemyId].x = 0;
		enatk[enemyId].y = 0;
		enatk[enemyId].hit_x = 0;
		enatk[enemyId].hit_y = 0;
		enatk[enemyId].hit_w = 0;
		enatk[enemyId].hit_h = 0;
		enatk[enemyId].hit_x2 = 0;
		enatk[enemyId].hit_y2 = 0;
		enatk[enemyId].hit_w2 = 0;
		enatk[enemyId].hit_h2 = 0;
		enatk[enemyId].range_x = 0;
		enatk[enemyId].range_y = 0;
		enatk[enemyId].range_w = 0;
		enatk[enemyId].range_h = 0;
		enatk[enemyId].range_x2 = 0;
		enatk[enemyId].range_y2 = 0;
		enatk[enemyId].range_w2 = 0;
		enatk[enemyId].range_h2 = 0;

		enatk[enemyId].attack_state = 0;
		enatk[enemyId].attack_time = 0;
		enemyattackCooltime = 0;
		enatk[enemyId].use = 0;
	}
}

/*
*  @brief 敵が攻撃を行った
*  @param enemyId 敵の識別番号
*/
void EnemyAttack(int enemyId) {
	if (enatk[enemyId].use == 0) {
		enatk[enemyId].use = 1;			// 攻撃を使用状態にする
		enemyattackCooltime = 30;		// 攻撃のクールタイムを設定
	}
}

// 敵の攻撃クールタイム
void EnemyAttackCooltime() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		if (enatk[i].use == 1) {
			enemyattackCooltime--;				// クールタイムを減らす
			if (enemyattackCooltime < 0) {		// クールタイムが終わったら
				// 攻撃状態を戻す
				if (en[i].direction == ENEMY_STATE_ATTACK_DOWN) {
					en[i].direction = ENEMY_STATE_DOWN;
				}
				if (en[i].direction == ENEMY_STATE_ATTACK_LEFT) {
					en[i].direction = ENEMY_STATE_LEFT;
				}
				if (en[i].direction == ENEMY_STATE_ATTACK_RIGHT) {
					en[i].direction = ENEMY_STATE_RIGHT;
				}
				if (en[i].direction == ENEMY_STATE_ATTACK_UP) {
					en[i].direction = ENEMY_STATE_UP;
				}
				// 敵攻撃判定の初期化
				enatk[i].x = 0;
				enatk[i].y = 0;
				enatk[i].hit_x = 0;
				enatk[i].hit_y = 0;
				enatk[i].hit_w = 0;
				enatk[i].hit_h = 0;
				enatk[i].hit_x2 = 0;
				enatk[i].hit_y2 = 0;
				enatk[i].hit_w2 = 0;
				enatk[i].hit_h2 = 0;
				enatk[i].range_x = 0;
				enatk[i].range_y = 0;
				enatk[i].range_w = 0;
				enatk[i].range_h = 0;
				enatk[i].range_x2 = 0;
				enatk[i].range_y2 = 0;
				enatk[i].range_w2 = 0;
				enatk[i].range_h2 = 0;

				enatk[i].attack_state = 0;
				enatk[i].attack_time = 0;
				enemyattackCooltime = 0;
				enatk[i].use = 0;
			}
		}
	}
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// 敵攻撃の描画
void DrawEnemyAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		if (en[i].use == 1) {
			// 無敵中は一定間隔で描画しない
			if (en[i].nohit_cnt == 0 || (en[i].nohit_cnt % 10) < 7)
			{
				if (enatk[i].attack_time != 0) {
					// 敵によって描画を変える
					switch (en[i].entype) {
						// 芋虫
					case ENEMY_CATERPILLAR:
						if (IsHitEnemyAttack != 0) {
							DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
							break;
						}
						// マタンゴ
					case ENEMY_MATANGO:
						if (IsHitEnemyAttack != 0) {
							if (enatk[i].attack_time > 0) {
								if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_UP)) {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_2);
								}
								else {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_3);
								}
								break;
							}
							break;
						}
						// マージマタンゴ
					case ENEMY_MERGE_MATANGO:
						if (IsHitEnemyAttack != 0) {
							if (IsHitPlayerEnemyRange(i) != 0) {
								if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_UP)) {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_4);
								}
								else {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_5);
								}
								break;
							}
							break;
						}
						// 狼
					case ENEMY_WOLF:
						if (IsHitEnemyAttack != 0) {
							DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
							break;
						}
						// マッドハッター
					case ENEMY_MAD_HATTER:
						// 前方攻撃
						if (enatk[i].rand == 0) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_7);
							}
							else {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_8);
							}
						}
						// 爆弾攻撃
						else if (enatk[i].rand == 1) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack2 != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_6);
								DrawMemTh(enatk[i].x2 + enatk[i].range_x2 - cv.view_x, enatk[i].y2 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_6);
								DrawMemTh(enatk[i].x3 + enatk[i].range_x - cv.view_x, enatk[i].y3 + enatk[i].range_y - cv.view_y, cgAttackJudgment_6);
								DrawMemTh(enatk[i].x4 + enatk[i].range_x2 - cv.view_x, enatk[i].y4 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_6);
							}
						}
						// ナイフ攻撃
						else if (enatk[i].rand == 2) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack3 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack3 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack3 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack3 != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_5);
								DrawMemTh(enatk[i].x2 + enatk[i].range_x2 - cv.view_x, enatk[i].y2 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_4);
								DrawMemTh(enatk[i].x3 + enatk[i].range_x - cv.view_x, enatk[i].y3 + enatk[i].range_y - cv.view_y, cgAttackJudgment_5);
								DrawMemTh(enatk[i].x4 + enatk[i].range_x2 - cv.view_x, enatk[i].y4 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_4);
							}
						}
						break;
					}
				}
			}
		}
	}
}