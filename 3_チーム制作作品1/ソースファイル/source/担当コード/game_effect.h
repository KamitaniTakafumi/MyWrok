#pragma once
/*------------------------------------------------
*  @file game_effect.cpp
*  @brief エフェクト処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  定数定義
------------------------------------------------*/

// エフェクト同時出現数
#define	EFFECT_MAX	(60)

/*------------------------------------------------
*  構造体定義
------------------------------------------------*/

// エフェクト構造体
struct EFFECT
{
	int	type;		// この配列のエフェクトタイプ（0:使用しない、1～:種類）
	int	x, y;		// 座標。位置はエフェクトの中心位置とする
	int	w, h;		// エフェクトの大きさ
	int	cnt;		// カウント。毎フレーム+1される
	int	frame;		// フレーム。絵の番号
	int	mx, my;		// 移動方向
	int id;			// 敵の配列情報
};

// エフェクト情報
extern struct EFFECT ef[EFFECT_MAX];

// EFFECTTYPE各種
enum EFFECTTYPE{
	EFFECTTYPE_NONE,			// 使用しない
	EFFECTTYPE_BREAK,			// 壁が壊れる
	EFFECTTYPE_ENEMY_DAMAGE,	// 敵ダメージ
	EFFECTTYPE_BOMB,			// 死亡
	EFFECTTYPE_DAMAGE,			// ダメージ
	EFFECTTYPE_CRITICAL,		// アイテムダメージ
	EFFECTTYPE_ITEM_ATTACK,		// アイテム攻撃
	EFFECTTYPE_ENEMY_HATTER,	// マッドハッター攻撃
	EFFECTTYPE_ENEMY_HATTER2,	// マッドハッター攻撃(二戦目)
	EFFECTTYPE_ENEMY_QUEEN		// ハートの女王攻撃
};

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// 画像読み込み
void LoadCgEffect();
// エフェクト情報の初期化
void InitEffect();
/*
*  @brief エフェクト使用の有無
*  @param effectType エフェクトの種類
*  @param x 描画の座標
*  @param y 描画の座標
*  @param Id アイテム、エネミーの識別
*/
void PutEffect(int effectType, int x, int y, int Id);
// エフェクトの処理
void ProcessEffect();
// 当たり判定を行うか？
// 返値：
//   1 = 行う
//   0 = 行わない
int IsHitItemAttack();
// エフェクトの描画
void DrawEffect();
