#pragma once
/*------------------------------------------------
*  @file enemy1.cpp , enemy2.cpp
*  @brief エネミー処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ヘッダーファイルのインクルード
------------------------------------------------*/
#include "vector.h"

/*------------------------------------------------
*  定数定義
------------------------------------------------*/

// 最大敵数
#define ENEMY_MAX 15

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

extern int cgCaterpiller[3 * 4];	// 芋虫
extern int cgHatter[4 * 4];			// マッドハッター
extern int hattbl[];				// 描画テーブル(マッドハッター)

/*------------------------------------------------
*  構造体定義
------------------------------------------------*/

// エネミーの構造体
struct ENEMY {
	int use;
	int state;      // 状態
	int direction;  // 向き
	int entype;		// 敵の種類
	double	x, y;	// 座標
	int	w, h;		// 大きさ
	int	spd;		// 移動速度
	int drc;        // 移動方向
	Vector2 d;		// 単位ベクトル
	int period;		// 敵自動移動(左右)
	int period2;	// 敵自動移動(上下)
	int period3;	// 敵自動移動(マップ壁に当たったら反対を向く)
	int period4;	// 敵追尾移動
	int	hit_x, hit_y, hit_w, hit_h;  //当たり判定
	int	hit_range_x, hit_range_y, hit_range_w, hit_range_h;  //当たり判定(行動範囲)
	int hp;			// 敵の体力
	int nohit_cnt;	// 無敵時間
	int damagecooltime;			// ダメージを受けてから動けるまでの時間
	int itemdamagecooltime;		// アイテムダメージを受けてから動けるまでの時間
	int anim_count;				// モーション時間
	int damage_point;			// ダメージ数
	int damage_critical_point;	// ダメージ数(有利、不利)
	int required;				// 必須処理敵
	int max_hp;			// 最大HP
	int state_enemy;	// ボスが死んでも消えないようにする
	int recipe_no;		// 敵が落とすレシピの種類
};

// エネミー情報
extern struct ENEMY en[ENEMY_MAX];

// 敵の種類
enum ENEMYTYPE{
	ENEMY_CATERPILLAR,		// 芋虫
	ENEMY_MATANGO,			// マタンゴ
	ENEMY_MERGE_MATANGO,	// マージマタンゴ
	ENEMY_WOLF,				// 狼
	ENEMY_MAD_HATTER,		// マッドハッター

	ENEMY_HEART,			// トランプ兵(ハート)
	ENEMY_DIA,				// トランプ兵(ダイヤ)
	ENEMY_CLOVER,			// トランプ兵(クローバー)
	ENEMY_SPADE,			// トランプ兵(スペード)
	ENEMY_QUEEN,			// ハートの女王
	ENEMY_MAD_HATTER2,		// マッドハッター
};

enum enemy_state {

	ENUM_EMPTY,		// 0のため使わないようにする

	ENEMY_STATE_DOWN,	// 敵移動(下)
	ENEMY_STATE_UP,		// 敵移動(上)
	ENEMY_STATE_RIGHT,	// 敵移動(右)
	ENEMY_STATE_LEFT,	// 敵移動(左)
	
	ENEMY_STATE_ATTACK_DOWN,	// 敵攻撃(下)
	ENEMY_STATE_ATTACK_UP,		// 敵攻撃(上)
	ENEMY_STATE_ATTACK_RIGHT,	// 敵攻撃(右)
	ENEMY_STATE_ATTACK_LEFT,	// 敵攻撃(左)
};

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// 線形補完による等速移動
// start -> end に値が動く場合、 cnt/max 時の位置を返す
int LerpN(int cnt, int max, int start, int end);
// 敵画像の読み込み
void LoadCgEnemy();
// 敵画像の読み込み(ステージ２)
void LoadCgEnemy2();
// エネミー初期化
void InitEnemy();
// エネミー初期化(ステージ２)
void InitEnemy2();
// エネミー移動
void EnemyMove();
// エネミー移動(ステージ２)
void EnemyMove2();
// 当たり判定を行うか？
// 返値：
//   1 = 行う
//   0 = 行わない
int IsHitProcessEnemy(int enemyId);
// エネミー描画
void DrawEnemy();
// エネミー描画(ステージ２)
void DrawEnemy2();
// 敵の体力描画(ボスのみ)
void DrawEnemyHitpoint();
// 敵の体力描画(ボスのみ、ステージ２)
void DrawEnemyHitpoint2();