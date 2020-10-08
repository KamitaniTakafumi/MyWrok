#pragma once
/*------------------------------------------------
*  @file enemyattack.cpp , enemyattack.cpp
*  @brief エネミー攻撃処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/
extern int cgAttackJudgment_1;		// 当たり範囲１
extern int cgAttackJudgment_2;		// 当たり範囲２
extern int cgAttackJudgment_3;		// 当たり範囲３
extern int cgAttackJudgment_7;		// 当たり範囲７
extern int cgAttackJudgment_8;		// 当たり範囲８
extern int cgAttackJudgment_9;		// 当たり範囲９
extern int cgAttackJudgment_10;		// 当たり範囲１０
extern int cgAttackJudgment_11;		// 当たり範囲１１
extern int cgAttackJudgment_12;		// 当たり範囲１２
extern int cgAttackJudgment_13;		// 当たり範囲１３
extern int cgAttackJudgment_14;		// 当たり範囲１４
extern int cgAttackJudgment_15;		// 当たり範囲１５
extern int enemyattackCooltime;		// 攻撃のクールタイム

/*------------------------------------------------
*  構造体定義
------------------------------------------------*/

// 敵攻撃の構造体
struct ENEMYATTACK {
	int		use;									// この配列を使用するかの確認( 0:未使用 1:使用中 ) 
	double		x, y;								// x, y座標
	double		x2, y2;								// x, y座標
	double		x3, y3;								// x, y座標
	double		x4, y4;								// x, y座標
	double		x5, y5;								// x, y座標
	double		x6, y6;								// x, y座標
	double		x7, y7;								// x, y座標
	double		x8, y8;								// x, y座標
	double		x9, y9;								// x, y座標
	double		x10, y10;							// x, y座標
	double		x11, y11;							// x, y座標
	double		x12, y12;							// x, y座標
	double		x13, y13;							// x, y座標
	double		x14, y14;							// x, y座標
	double		x15, y15;							// x, y座標
	double		x16, y16;							// x, y座標
	double		w, h;								// 大きさ
	double		w2, h2;								// 大きさ
	double		hit_x, hit_y, hit_w, hit_h;			// 当たり判定
	double	hit_x2, hit_y2, hit_w2, hit_h2;			// 当たり判定
	double	range_x, range_y, range_w, range_h;		// 攻撃範囲
	double	range_x2, range_y2, range_w2, range_h2;	// 攻撃範囲
	int		rand;									// 攻撃パターン
	int		attack_time;							// 攻撃までの時間
	int		attack_state;							// 攻撃状態の有無
	int		select_attack;							// 攻撃パターンの状態維持
};

extern struct ENEMYATTACK enatk[ENEMY_MAX];

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// 画像読み込み
void LoadCgEnemyAttack();
// 画像読み込み(ステージ２)
void LoadCgEnemyAttack2();
// 初期化
void InitEnemyAttack();
// 初期化(ステージ２)
void InitEnemyAttack2();
/*
*  @brief 攻撃判定の更新
*  @param enemyId 敵の識別番号
*/
void AttackCooldinate(int enemyId);
/*
*  @brief 攻撃判定の更新(ステージ２)
*  @param enemyId 敵の識別番号
*/
void AttackCooldinate2(int enemyId);
/*
*  @brief 敵が攻撃を行った
*  @param enemyId 敵の識別番号
*/
void EnemyAttack(int enemyId);
// 敵の攻撃クールタイム
void EnemyAttackCooltime();
// 敵攻撃の描画
void DrawEnemyAttack();
// 敵攻撃の描画(ステージ２)
void DrawEnemyAttack2();