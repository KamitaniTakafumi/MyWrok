#pragma once
//
// 定数・構造体定義
//
struct ATTACK
{
	int		use;						// この配列を使用するかの確認( 0:未使用 1:使用中 ) 
	int		x, y;						// 座標
	int		w, h;						// 大きさ
	int		hit_x, hit_y, hit_w, hit_h;	// 当たり判定
};

struct ATTACKITEM
{
	int		use;						// この配列を使用するかの確認( 0:未使用 1:使用中 ) 
	int		x, y;						// 座標
	int		w, h;						// 大きさ
	int		hit_x, hit_y, hit_w, hit_h;	// 当たり判定
	int		item_no;					// 
};

//
// グローバル変数宣言
//
extern struct ATTACK atk;
extern struct ATTACKITEM atkit;

void LoadAttackEff();				// 攻撃エフェクトのロード

void InitAttack();					// 攻撃の初期設定

void playerAttack();				// プレイヤーの攻撃

void PlayerItemAttack(int itemId);	// プレイヤーのアイテム攻撃

void AttackCooltime();				// 攻撃のクールタイム
