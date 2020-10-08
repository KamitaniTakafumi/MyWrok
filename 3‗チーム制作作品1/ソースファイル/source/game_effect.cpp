/*------------------------------------------------
*  @file game_effect.cpp
*  @brief エフェクト処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*-----------------------------------------------
*  ヘッダーファイルのインクルード
-----------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"

#include	"game_effect.h"
#include	"camera.h"
#include	"enemy.h"
#include	"enemyattack.h"
#include	"alice.h"
#include	"HitJudgment.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// 画像データ

int cgWallBreak[8 * 1];		// エフェクト：壁破壊

int cgEffectDamage[5 * 1];	// エフェクト：敵ダメージ
int cgEffectBomb[8 * 1];	// エフェクト：死亡

int cgDamage[4];			// エフェクト：ダメージポイント
int cgDamageCritical[7];	// エフェクト：ダメージポイント(有利不利)

int cgItemAttack1[2];		// エフェクト：とげ爆弾(投げ)
int cgItemAttackB1[7 * 1];	// エフェクト：とげ爆弾(爆発)
int cgItemAttack2[2];		// エフェクト：火炎爆弾(投げ)
int cgItemAttackB2[7 * 1];	// エフェクト：火炎爆弾(爆発)
int cgItemAttack3[2];		// エフェクト：氷冷爆弾(投げ)
int cgItemAttackB3[7 * 1];	// エフェクト：氷冷爆弾(爆発)
int cgItemAttack4[2];		// エフェクト：雷電爆弾(投げ)
int cgItemAttackB4[7 * 1];	// エフェクト：雷電爆弾(爆発)

int cgItemAttack5[7 * 1];	// エフェクト：ポーション

int cgItemAttack6_down[9 * 1];	// エフェクト：ナイフ攻撃(下)
int cgItemAttack6_up[9 * 1];	// エフェクト：ナイフ攻撃(上)
int cgItemAttack6_right[1 * 9];	// エフェクト：ナイフ攻撃(右)
int cgItemAttack6_left[1 * 9];	// エフェクト：ナイフ攻撃(左)
int cgItemAttack7_down[9 * 1];	// エフェクト：火炎ナイフ攻撃(下)
int cgItemAttack7_up[9 * 1];	// エフェクト：火炎ナイフ攻撃(上)
int cgItemAttack7_right[1 * 9];	// エフェクト：火炎ナイフ攻撃(右)
int cgItemAttack7_left[1 * 9];	// エフェクト：火炎ナイフ攻撃(左)
int cgItemAttack8_down[9 * 1];	// エフェクト：氷冷ナイフ攻撃(下)
int cgItemAttack8_up[9 * 1];	// エフェクト：氷冷ナイフ攻撃(上)
int cgItemAttack8_right[1 * 9];	// エフェクト：氷冷ナイフ攻撃(右)
int cgItemAttack8_left[1 * 9];	// エフェクト：氷冷ナイフ攻撃(左)
int cgItemAttack9_down[9 * 1];	// エフェクト：雷電ナイフ攻撃(下)
int cgItemAttack9_up[9 * 1];	// エフェクト：雷電ナイフ攻撃(上)
int cgItemAttack9_right[1 * 9];	// エフェクト：雷電ナイフ攻撃(右)
int cgItemAttack9_left[1 * 9];	// エフェクト：雷電ナイフ攻撃(左)

int cgItemAttack10[2];		// エフェクト：火炎爆弾(投げ)
int cgItemAttackB10[7 * 1];	// エフェクト：火炎爆弾(爆発)
int cgItemAttack11[2];		// エフェクト：氷冷爆弾(投げ)
int cgItemAttackB11[7 * 1];	// エフェクト：氷冷爆弾(爆発)
int cgItemAttack12[2];		// エフェクト：雷電爆弾(投げ)
int cgItemAttackB12[7 * 1];	// エフェクト：雷電爆弾(爆発)

int cgItemAttack13[7 * 1];	// エフェクト：ハイポーション
int cgItemAttack14[7 * 1];	// エフェクト：フルポーション

int cgItemAttack15_down[9 * 1];		// エフェクト：強火炎ナイフ攻撃(下)
int cgItemAttack15_up[9 * 1];		// エフェクト：強火炎ナイフ攻撃(上)
int cgItemAttack15_right[1 * 9];	// エフェクト：強火炎ナイフ攻撃(右)
int cgItemAttack15_left[1 * 9];		// エフェクト：強火炎ナイフ攻撃(左)
int cgItemAttack16_down[9 * 1];		// エフェクト：強氷冷ナイフ攻撃(下)
int cgItemAttack16_up[9 * 1];		// エフェクト：強氷冷ナイフ攻撃(上)
int cgItemAttack16_right[1 * 9];	// エフェクト：強氷冷ナイフ攻撃(右)
int cgItemAttack16_left[1 * 9];		// エフェクト：強氷冷ナイフ攻撃(左)
int cgItemAttack17_down[9 * 1];		// エフェクト：強雷電ナイフ攻撃(下)
int cgItemAttack17_up[9 * 1];		// エフェクト：強雷電ナイフ攻撃(上)
int cgItemAttack17_right[1 * 9];	// エフェクト：強雷電ナイフ攻撃(右)
int cgItemAttack17_left[1 * 9];		// エフェクト：強雷電ナイフ攻撃(左)

int cgHatterAttack[7 * 1];			// エフェクト：マッドハッター攻撃(爆発)
int cgHatterAttack2_down[9 * 1];	// エフェクト：マッドハッター攻撃(ナイフ)
int cgHatterAttack2_up[9 * 1];		// エフェクト：マッドハッター攻撃(ナイフ)
int cgHatterAttack2_right[1 * 9];	// エフェクト：マッドハッター攻撃(ナイフ)
int cgHatterAttack2_left[1 * 9];	// エフェクト：マッドハッター攻撃(ナイフ)

int cgQueenAttack[4];				// エフェクト：ハートの女王攻撃(ハート落とし)
int cgQueenAttack2_down[9 * 1];		// エフェクト：ハートの女王攻撃(炎、下)
int cgQueenAttack2_up[9 * 1];		// エフェクト：ハートの女王攻撃(炎、上)
int cgQueenAttack2_right[9 * 1];	// エフェクト：ハートの女王攻撃(炎、右)
int cgQueenAttack2_left[9 * 1];		// エフェクト：ハートの女王攻撃(炎、左)

int cgQueen_Hatter_Attack3[7 * 1];	// エフェクト：ハートの女王、マッドハッター攻撃(爆発)

int cgHatterAttack4[4];	// エフェクト：マッドハッター攻撃(帽子落とし)

// エフェクト情報
struct EFFECT ef[EFFECT_MAX];

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// エフェクト画像の読み込み
void LoadCgEffect()
{
	// 壁壊しエフェクト
	LoadBlkTexture("res/wallbreak.png", 200, 200, 8, 1, 8 * 1, cgWallBreak);

	// 敵ダメージエフェクト
	LoadBlkTexture("res/enemydamage.png", 60, 60, 5, 1, 5 * 1, cgEffectDamage);
	LoadBlkTexture("res/smoke_sheet.png", 60, 60, 8, 1, 8 * 1, cgEffectBomb);

	// ダメージポイントエフェクト
	cgDamage[0] = LoadTexture("res/damage_0_0.png");
	cgDamage[1] = LoadTexture("res/damage_1_1.png");
	cgDamage[2] = LoadTexture("res/damage_2_2.png");
	cgDamage[3] = LoadTexture("res/damage_3_3.png");

	// クリティカルダメージポイントエフェクト
	cgDamageCritical[0] = LoadTexture("res/damageunfavorable_0_0.png");
	cgDamageCritical[1] = LoadTexture("res/damageunfavorable_1_1.png");
	cgDamageCritical[2] = LoadTexture("res/damageunfavorable_2_2.png");
	cgDamageCritical[3] = LoadTexture("res/damagecritical_3_3.png");
	cgDamageCritical[4] = LoadTexture("res/damagecritical_4_4.png");
	cgDamageCritical[5] = LoadTexture("res/damagecritical_5_5.png");
	cgDamageCritical[6] = LoadTexture("res/damagecritical_6_6.png");

	// 下位爆弾エフェクト
	cgItemAttack1[0] = LoadTexture("res/toge_bakudan_attack.png");
	cgItemAttack1[1] = LoadTexture("res/toge_bakudan_attack.png");
	LoadBlkTexture("res/toge_effects_sheet.png", 120, 120, 7, 1, 7 * 1, cgItemAttackB1);
	cgItemAttack2[0] = LoadTexture("res/kaen_bakudan_attack.png");
	cgItemAttack2[1] = LoadTexture("res/kaen_bakudan_attack.png");
	LoadBlkTexture("res/kaen_effects_sheet.png", 120, 120, 7, 1, 7 * 1, cgItemAttackB2);
	cgItemAttack3[0] = LoadTexture("res/koori_bakudan_attack.png");
	cgItemAttack3[1] = LoadTexture("res/koori_bakudan_attack.png");
	LoadBlkTexture("res/reitou_sheet.png", 120, 120, 7, 1, 7 * 1, cgItemAttackB3);
	cgItemAttack4[0] = LoadTexture("res/kaminari_nakudan_attack.png");
	cgItemAttack4[1] = LoadTexture("res/kaminari_nakudan_attack.png");
	LoadBlkTexture("res/dengeki_sheet.png", 120, 120, 7, 1, 7 * 1, cgItemAttackB4);

	// ポーションエフェクト
	LoadBlkTexture("res/potion_sheet.png", 40, 80, 7, 1, 7 * 1, cgItemAttack5);

	// 下位ナイフエフェクト
	LoadBlkTexture("res/knife_sheet.png", 40, 200, 9, 1, 9 * 1, cgItemAttack6_up);
	LoadBlkTexture("res/knife_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgItemAttack6_down);
	LoadBlkTexture("res/knife_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgItemAttack6_right);
	LoadBlkTexture("res/knife_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgItemAttack6_left);
	LoadBlkTexture("res/knife_red_sheet.png", 40, 200, 9, 1, 9 * 1, cgItemAttack7_up);
	LoadBlkTexture("res/knife_red_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgItemAttack7_down);
	LoadBlkTexture("res/knife_red_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgItemAttack7_right);
	LoadBlkTexture("res/knife_red_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgItemAttack7_left);
	LoadBlkTexture("res/knife_blue_sheet.png", 40, 200, 9, 1, 9 * 1, cgItemAttack8_up);
	LoadBlkTexture("res/knife_blue_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgItemAttack8_down);
	LoadBlkTexture("res/knife_blue_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgItemAttack8_right);
	LoadBlkTexture("res/knife_blue_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgItemAttack8_left);
	LoadBlkTexture("res/knife_yellow_sheet.png", 40, 200, 9, 1, 9 * 1, cgItemAttack9_up);
	LoadBlkTexture("res/knife_yellow_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgItemAttack9_down);
	LoadBlkTexture("res/knife_yellow_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgItemAttack9_right);
	LoadBlkTexture("res/knife_yellow_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgItemAttack9_left);

	// 上位爆弾エフェクト
	cgItemAttack10[0] = LoadTexture("res/kaenS_bakudan_attack.png");
	cgItemAttack10[1] = LoadTexture("res/kaenS_bakudan_attack.png");
	LoadBlkTexture("res/kaen_effects_sheet.png", 120, 120, 7, 1, 7 * 1, cgItemAttackB10);
	cgItemAttack11[0] = LoadTexture("res/kooriS_bakudan_attack.png");
	cgItemAttack11[1] = LoadTexture("res/kooriS_bakudan_attack.png");
	LoadBlkTexture("res/reitou_sheet.png", 120, 120, 7, 1, 7 * 1, cgItemAttackB11);
	cgItemAttack12[0] = LoadTexture("res/kaminariS_nakudan_attack.png");
	cgItemAttack12[1] = LoadTexture("res/kaminariS_nakudan_attack.png");
	LoadBlkTexture("res/dengeki_sheet.png", 120, 120, 7, 1, 7 * 1, cgItemAttackB12);

	// ハイポーションエフェクト
	LoadBlkTexture("res/potion_sheet.png", 40, 80, 7, 1, 7 * 1, cgItemAttack13);
	// フルポーションエフェクト
	LoadBlkTexture("res/full_potion_sheet.png", 40, 80, 7, 1, 7 * 1, cgItemAttack14);

	// 上位ナイフエフェクト
	LoadBlkTexture("res/knife_red_sheet.png", 40, 200, 9, 1, 9 * 1, cgItemAttack15_up);
	LoadBlkTexture("res/knife_red_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgItemAttack15_down);
	LoadBlkTexture("res/knife_red_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgItemAttack15_right);
	LoadBlkTexture("res/knife_red_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgItemAttack15_left);
	LoadBlkTexture("res/knife_blue_sheet.png", 40, 200, 9, 1, 9 * 1, cgItemAttack16_up);
	LoadBlkTexture("res/knife_blue_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgItemAttack16_down);
	LoadBlkTexture("res/knife_blue_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgItemAttack16_right);
	LoadBlkTexture("res/knife_blue_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgItemAttack16_left);
	LoadBlkTexture("res/knife_yellow_sheet.png", 40, 200, 9, 1, 9 * 1, cgItemAttack17_up);
	LoadBlkTexture("res/knife_yellow_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgItemAttack17_down);
	LoadBlkTexture("res/knife_yellow_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgItemAttack17_right);
	LoadBlkTexture("res/knife_yellow_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgItemAttack17_left);

	// マッドハッター(1戦目)攻撃エフェクト
	LoadBlkTexture("res/mad_explosion_effects_sheet.png", 120, 120, 7, 1, 7 * 1, cgHatterAttack);
	LoadBlkTexture("res/knife_mad_sheet.png", 40, 200, 9, 1, 9 * 1, cgHatterAttack2_up);
	LoadBlkTexture("res/knife_mad_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgHatterAttack2_down);
	LoadBlkTexture("res/knife_mad_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgHatterAttack2_right);
	LoadBlkTexture("res/knife_mad_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgHatterAttack2_left);

	// ハートの女王攻撃エフェクト
	cgQueenAttack[0] = LoadTexture("res/shadow_40.png");
	cgQueenAttack[1] = LoadTexture("res/queenattack.png");
	cgQueenAttack[2] = LoadTexture("res/queenattack.png");
	cgQueenAttack[3] = LoadTexture("res/queenattack.png");
	LoadBlkTexture("res/fire_sheet_down.png", 40, 200, 9, 1, 9 * 1, cgQueenAttack2_down);
	LoadBlkTexture("res/fire_sheet.png", 40, 200, 9, 1, 9 * 1, cgQueenAttack2_up);
	LoadBlkTexture("res/fire_sheet_right.png", 200, 40, 1, 9, 1 * 9, cgQueenAttack2_right);
	LoadBlkTexture("res/fire_sheet_left.png", 200, 40, 1, 9, 1 * 9, cgQueenAttack2_left);

	// ハートの女王、マッドハッター(2戦目)攻撃エフェクト
	LoadBlkTexture("res/mad_explosion_effects_sheet2.png", 160, 160, 7, 1, 7 * 1, cgQueen_Hatter_Attack3);

	// マッドハッター(2戦目)攻撃エフェクト
	cgHatterAttack4[0] = LoadTexture("res/shadow_120.png");
	cgHatterAttack4[1] = LoadTexture("res/hut.png");
	cgHatterAttack4[2] = LoadTexture("res/hut.png");
	cgHatterAttack4[3] = LoadTexture("res/hut.png");
}

// エフェクトの初期化
void InitEffect()
{
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		ef[i].type = EFFECTTYPE_NONE;
	}
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

/*
*  @brief エフェクト使用の有無
*  @param effectType エフェクトの種類
*  @param x 描画の座標
*  @param y 描画の座標
*  @param Id アイテム、エネミーの識別
*/
void PutEffect(int effectType, int x, int y, int Id)
{
	int i;
	// 使っていない配列を探す
	for (i = 0; i < EFFECT_MAX; i++)
	{
		if (ef[i].type == EFFECTTYPE_NONE)
		{
			// 使っていない。ここを使う
			ef[i].type = effectType;
			ef[i].x = x;
			ef[i].y = y;
			ef[i].cnt = 0;
			ef[i].frame = 0;
			ef[i].mx = 0;
			ef[i].my = 0;
			ef[i].id = Id;
			// エフェクト種類別の初期化処理
			switch (ef[i].type)
			{
			case EFFECTTYPE_BREAK:
				ef[i].w = 80;
				ef[i].h = 80;
				break;
			case EFFECTTYPE_ENEMY_DAMAGE:
				ef[i].w = 60;
				ef[i].h = 60;
				break;
			case EFFECTTYPE_BOMB:
				ef[i].w = 60;
				ef[i].h = 60;
				break;
			case EFFECTTYPE_DAMAGE:
				ef[i].w = 40;
				ef[i].h = 40;
				break;
			case EFFECTTYPE_CRITICAL:
				ef[i].w = 30;
				ef[i].h = 30;
				break;
			case EFFECTTYPE_ITEM_ATTACK:
				if ((Id == 0) || (Id == 1) || (Id == 2) || (Id == 3) || (Id == 10) || (Id == 11) || (Id == 12)) {
					ef[i].w = 120;
					ef[i].h = 120;
				}
				else if ((Id == 4) || (Id == 5) || (Id == 13)) {
					ef[i].w = 40;
					ef[i].h = 80;
				}
				else if ((Id == 6) || (Id == 7) || (Id == 8) || (Id == 9) || (Id == 14) || (Id == 15) || (Id == 16)) {
					if ((al.state == ALICE_STATE_ITEM_ATTACK_DOWN) || (ALICE_STATE_ITEM_ATTACK_UP)) {
						ef[i].w = 40;
						ef[i].h = 200;
					}
					else {
						ef[i].w = 200;
						ef[i].h = 40;
					}
				}
				break;
			case EFFECTTYPE_ENEMY_HATTER:
				if (enatk[Id].rand == 0) {
					if ((en[Id].direction == ENEMY_STATE_ATTACK_DOWN) || (ENEMY_STATE_ATTACK_UP)) {
						ef[i].w = 120;
						ef[i].h = 40;
					}
					else if ((en[Id].direction == ENEMY_STATE_ATTACK_RIGHT) || (ENEMY_STATE_ATTACK_LEFT)) {
						ef[i].w = 40;
						ef[i].h = 120;
					}
				}
				else if (enatk[Id].rand == 1) {
					if ((en[Id].direction == ENEMY_STATE_ATTACK_DOWN) || (ENEMY_STATE_ATTACK_UP)) {
						ef[i].w = 120;
						ef[i].h = 40;
					}
					else if ((en[Id].direction == ENEMY_STATE_ATTACK_RIGHT) || (ENEMY_STATE_ATTACK_LEFT)) {
						ef[i].w = 40;
						ef[i].h = 120;
					}
				}
				else if (enatk[Id].rand == 2) {
					ef[i].w = 40;
					ef[i].h = 40;
				}
				break;
			case EFFECTTYPE_ENEMY_QUEEN:
				ef[i].w = 40;
				ef[i].h = 40;
				break;
			}
			break;
		}
	}

}

// エフェクトの処理
void ProcessEffect()
{
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		// このエフェクトは使用中か？
		if (ef[i].type != EFFECTTYPE_NONE)
		{
			// エフェクト種類別の処理
			switch (ef[i].type)
			{
			case EFFECTTYPE_BREAK:
				// このエフェクトは使用中である
				ef[i].cnt++;		// カウントを+1

				 // 座標の移動
				ef[i].x += ef[i].mx;
				ef[i].y += ef[i].my;

				if (ef[i].cnt > 7)
				{	// アニメーションを進める
					ef[i].frame++;
					ef[i].cnt = 0;
				}
				if (ef[i].frame == 8)
				{	// アニメーションが終了したので、このエフェクトは削除する
					ef[i].type = EFFECTTYPE_NONE;
				}
				break;
			case EFFECTTYPE_ENEMY_DAMAGE:
				// このエフェクトは使用中である
				ef[i].cnt++;		// カウントを+1

				 // 座標の移動
				ef[i].x += ef[i].mx;
				ef[i].y += ef[i].my;

				if (ef[i].cnt > 2)
				{	// アニメーションを進める
					ef[i].frame++;
					ef[i].cnt = 0;
				}
				if (ef[i].frame == 5)
				{	// アニメーションが終了したので、このエフェクトは削除する
					ef[i].type = EFFECTTYPE_NONE;
				}
				break;
			case EFFECTTYPE_BOMB:
				// このエフェクトは使用中である
				ef[i].cnt++;		// カウントを+1

				 // 座標の移動
				ef[i].x += ef[i].mx;
				ef[i].y += ef[i].my;

				if (ef[i].cnt > 2)
				{	// アニメーションを進める
					ef[i].frame++;
					ef[i].cnt = 0;
				}
				if (ef[i].frame == 8)
				{	// アニメーションが終了したので、このエフェクトは削除する
					ef[i].type = EFFECTTYPE_NONE;
				}
				break;
			case EFFECTTYPE_DAMAGE:
				// このエフェクトは使用中である
				ef[i].frame++;		// カウントを+1

				if (ef[i].frame == 60)
				{	// アニメーションが終了したので、このエフェクトは削除する
					ef[i].type = EFFECTTYPE_NONE;
					en[ef[i].id].damage_point = 0;
				}
				break;
			case EFFECTTYPE_CRITICAL:
				// このエフェクトは使用中である
				ef[i].frame++;		// カウントを+1

				if (ef[i].frame == 60)
				{	// アニメーションが終了したので、このエフェクトは削除する
					ef[i].type = EFFECTTYPE_NONE;
					en[ef[i].id].damage_critical_point = 0;
				}
				break;
			case EFFECTTYPE_ITEM_ATTACK:
				// このエフェクトは使用中である
				if ((ef[i].id == 0) || (ef[i].id == 1) || (ef[i].id == 2) || (ef[i].id == 3) || (ef[i].id == 10) || (ef[i].id == 11) || (ef[i].id == 12)) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 9)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
					if ((ef[i].cnt == 1) & (ef[i].frame == 0)) {
						PlayMemBack(seAliceAttack);		// SE再生
					}
					if ((ef[i].id == 0) || (ef[i].id == 1) || (ef[i].id == 2) || (ef[i].id == 3)) {
						if ((ef[i].cnt == 1) & (ef[i].frame == 2)) {
							PlayMemBack(seBomb);		// SE再生
						}
					}
					else {
						if ((ef[i].cnt == 1) & (ef[i].frame == 2)) {
							PlayMemBack(seBomb2);		// SE再生
						}
					}
				}
				else if ((ef[i].id == 4) || (ef[i].id == 5) || (ef[i].id == 13)) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 7)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				else if ((ef[i].id == 6) || (ef[i].id == 7) || (ef[i].id == 8) || (ef[i].id == 9) || (ef[i].id == 14) || (ef[i].id == 15) || (ef[i].id == 16)) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 9)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
						en[ef[i].id].damage_point = 0;
						en[ef[i].id].damage_critical_point = 0;
					}
				}
				break;
			case EFFECTTYPE_ENEMY_HATTER:
				// このエフェクトは使用中である
				if (enatk[ef[i].id].rand == 0) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 9)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				else if (enatk[ef[i].id].rand == 1) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 7)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				else if (enatk[ef[i].id].rand == 2) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 9)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				break;
			case EFFECTTYPE_ENEMY_QUEEN:
				// このエフェクトは使用中である
				if (enatk[ef[i].id].rand == 0) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 3)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				else if (enatk[ef[i].id].rand == 1) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 8)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				else if (enatk[ef[i].id].rand == 2) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 7)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				break;
			case EFFECTTYPE_ENEMY_HATTER2:
				// このエフェクトは使用中である
				if (enatk[ef[i].id].rand == 0) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 9)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				else if (enatk[ef[i].id].rand == 1) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 7)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				else if (enatk[ef[i].id].rand == 2) {
					ef[i].cnt++;		// カウントを+1

					if (ef[i].cnt > 2)
					{	// アニメーションを進める
						ef[i].frame++;
						ef[i].cnt = 0;
					}
					if (ef[i].frame == 4)
					{	// アニメーションが終了したので、このエフェクトは削除する
						ef[i].type = EFFECTTYPE_NONE;
					}
				}
				break;
			}
		}
	}
}

// アイテム攻撃の判定の有無
int IsHitItemAttack() {
	int i;
	for (i = 0; i < EFFECT_MAX; i++)
	{
		// このエフェクトは使用中か？
		if (ef[i].type != EFFECTTYPE_NONE)
		{
			// エフェクト種類別の処理
			switch (ef[i].type)
			{
			case EFFECTTYPE_ITEM_ATTACK:
				if (ef[i].frame > 2) {
					return 1;
				}
				break;
			}
		}
	}
	return 0;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// エフェクト描画
void DrawEffect()
{
	int i;
	int cg2 = 0;	// 向きの判定
	for (i = 0; i < EFFECT_MAX; i++)
	{
		// この敵は使用中か？
		if (ef[i].type != EFFECTTYPE_NONE)
		{
			// このエフェクトは使用中である
			int cg = -1;	// 画像
			// エフェクト別に処理
			switch (ef[i].type)
			{
			case EFFECTTYPE_BREAK:
				cg = cgWallBreak[ef[i].frame];
				break;
			case EFFECTTYPE_ENEMY_DAMAGE:
				cg = cgEffectDamage[ef[i].frame];
				break;
			case EFFECTTYPE_BOMB:
				cg = cgEffectBomb[ef[i].frame];
				break;
			case EFFECTTYPE_DAMAGE:
				cg = cgDamage[en[ef[i].id].damage_point];
				break;
			case EFFECTTYPE_CRITICAL:
				cg = cgDamageCritical[en[ef[i].id].damage_critical_point];
				break;
			case EFFECTTYPE_ITEM_ATTACK:
				if (ef[i].id == 0) {
					if (ef[i].frame < 2) {
						cg = cgItemAttack1[ef[i].frame];
					}
					else {
						cg = cgItemAttackB1[ef[i].frame - 2];
					}
				}
				else if (ef[i].id == 1) {
					if (ef[i].frame < 2) {
						cg = cgItemAttack2[ef[i].frame];
					}
					else {
						cg = cgItemAttackB2[ef[i].frame - 2];
					}
				}
				else if (ef[i].id == 2) {
					if (ef[i].frame < 2) {
						cg = cgItemAttack3[ef[i].frame];
					}
					else {
						cg = cgItemAttackB3[ef[i].frame - 2];
					}
				}
				else if (ef[i].id == 3) {
					if (ef[i].frame < 2) {
						cg = cgItemAttack4[ef[i].frame];
					}
					else {
						cg = cgItemAttackB4[ef[i].frame - 2];
					}
				}
				else if (ef[i].id == 4) {
					cg = cgItemAttack5[ef[i].frame];
				}
				else if (ef[i].id == 5) {
					cg = cgItemAttack13[ef[i].frame];
				}
				else if (ef[i].id == 6) {
					if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
						cg = cgItemAttack6_down[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
						cg = cgItemAttack6_up[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
						cg = cgItemAttack6_left[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
						cg = cgItemAttack6_right[ef[i].frame];
					}
				}
				else if (ef[i].id == 7) {
					if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
						cg = cgItemAttack7_down[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
						cg = cgItemAttack7_up[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
						cg = cgItemAttack7_left[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
						cg = cgItemAttack7_right[ef[i].frame];
					}
				}
				else if (ef[i].id == 8) {
					if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
						cg = cgItemAttack8_down[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
						cg = cgItemAttack8_up[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
						cg = cgItemAttack8_left[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
						cg = cgItemAttack8_right[ef[i].frame];
					}
				}
				else if (ef[i].id == 9) {
					if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
						cg = cgItemAttack9_down[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
						cg = cgItemAttack9_up[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
						cg = cgItemAttack9_left[ef[i].frame];
					}
					else if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
						cg = cgItemAttack9_right[ef[i].frame];
					}
				}
				else if (ef[i].id == 10) {
					if (ef[i].frame < 2) {
						cg = cgItemAttack10[ef[i].frame];
					}
					else {
						cg = cgItemAttackB10[ef[i].frame - 2];
					}
				}
				else if (ef[i].id == 11) {
					if (ef[i].frame < 2) {
						cg = cgItemAttack11[ef[i].frame];
					}
					else {
						cg = cgItemAttackB11[ef[i].frame - 2];
					}
				}
				else if (ef[i].id == 12) {
					if (ef[i].frame < 2) {
						cg = cgItemAttack12[ef[i].frame];
					}
					else {
						cg = cgItemAttackB12[ef[i].frame - 2];
					}
				}
				else if (ef[i].id == 13) {
				cg = cgItemAttack14[ef[i].frame];
				}
				else if (ef[i].id == 14) {
				if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
					cg = cgItemAttack15_down[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
					cg = cgItemAttack15_up[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
					cg = cgItemAttack15_left[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
					cg = cgItemAttack15_right[ef[i].frame];
				}
				}
				else if (ef[i].id == 15) {
				if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
					cg = cgItemAttack16_down[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
					cg = cgItemAttack16_up[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
					cg = cgItemAttack16_left[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
					cg = cgItemAttack16_right[ef[i].frame];
				}
				}
				else if (ef[i].id == 16) {
				if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
					cg = cgItemAttack17_down[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
					cg = cgItemAttack17_up[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
					cg = cgItemAttack17_left[ef[i].frame];
				}
				else if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
					cg = cgItemAttack17_right[ef[i].frame];
				}
				}
				break;
			case EFFECTTYPE_ENEMY_HATTER:
				if (enatk[ef[i].id].rand == 0) {
					if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_UP) {
						cg = cgHatterAttack2_up[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_DOWN) {
						cg = cgHatterAttack2_down[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_LEFT) {
						cg = cgHatterAttack2_left[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_RIGHT) {
						cg = cgHatterAttack2_right[ef[i].frame];
					}
				}
				else if (enatk[ef[i].id].rand == 1) {
					cg = cgHatterAttack[ef[i].frame];
				}
				else if (enatk[ef[i].id].rand == 2) {
					if (cg2 == 0) {
						if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_UP) {
							cg = cgHatterAttack2_left[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_DOWN) {
							cg = cgHatterAttack2_left[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_LEFT) {
							cg = cgHatterAttack2_left[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_RIGHT) {
							cg = cgHatterAttack2_left[ef[i].frame];
						}
					}
					else if (cg2 == 1) {
						if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_UP) {
							cg = cgHatterAttack2_up[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_DOWN) {
							cg = cgHatterAttack2_up[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_LEFT) {
							cg = cgHatterAttack2_up[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_RIGHT) {
							cg = cgHatterAttack2_up[ef[i].frame];
						}
					}
					else if (cg2 == 2) {
						if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_UP) {
							cg = cgHatterAttack2_right[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_DOWN) {
							cg = cgHatterAttack2_right[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_LEFT) {
							cg = cgHatterAttack2_right[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_RIGHT) {
							cg = cgHatterAttack2_right[ef[i].frame];
						}
					}
					else if (cg2 == 3) {
						if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_UP) {
							cg = cgHatterAttack2_down[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_DOWN) {
							cg = cgHatterAttack2_down[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_LEFT) {
							cg = cgHatterAttack2_down[ef[i].frame];
						}
						else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_RIGHT) {
							cg = cgHatterAttack2_down[ef[i].frame];
						}
					}
				}
				break;
			case EFFECTTYPE_ENEMY_QUEEN:
				if (enatk[ef[i].id].rand == 0) {
					cg = cgQueenAttack[ef[i].frame];
				}
				else if (enatk[ef[i].id].rand == 1) {
					if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_UP) {
						cg = cgQueenAttack2_up[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_DOWN) {
						cg = cgQueenAttack2_down[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_LEFT) {
						cg = cgQueenAttack2_left[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_RIGHT) {
						cg = cgQueenAttack2_right[ef[i].frame];
					}
				}
				else if (enatk[ef[i].id].rand == 2) {
					cg = cgQueen_Hatter_Attack3[ef[i].frame];
				}
				break;
			case EFFECTTYPE_ENEMY_HATTER2:
				if (enatk[ef[i].id].rand == 0) {
					if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_UP) {
						cg = cgHatterAttack2_up[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_DOWN) {
						cg = cgHatterAttack2_down[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_LEFT) {
						cg = cgHatterAttack2_left[ef[i].frame];
					}
					else if (en[ef[i].id].direction == ENEMY_STATE_ATTACK_RIGHT) {
						cg = cgHatterAttack2_right[ef[i].frame];
					}
				}
				else if (enatk[ef[i].id].rand == 1) {
					cg = cgQueen_Hatter_Attack3[ef[i].frame];
				}
				else if (enatk[ef[i].id].rand == 2) {
					cg = cgHatterAttack4[ef[i].frame];
				}
				break;
			}
			// 画像が指定されていたら、その絵を表示する
			switch (ef[i].type) {
			case EFFECTTYPE_BREAK:
				if (cg != -1) {
					DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
				}
				break;
			case EFFECTTYPE_ENEMY_DAMAGE:
				if (cg != -1)
				{
					DrawMemTh(ef[i].x - ef[i].w / 2 - cv.view_x, ef[i].y - ef[i].h / 2 - cv.view_y, cg);
				}
				break;
			case EFFECTTYPE_BOMB:
				if (cg != -1)
				{
					DrawMemTh(ef[i].x - ef[i].w / 2 - cv.view_x, ef[i].y - ef[i].h / 2 - cv.view_y, cg);
				}
				break;
			case EFFECTTYPE_DAMAGE:
				if (cg != -1)
				{
					DrawMemTh(ef[i].x - cv.view_x, ef[i].y - ef[i].h / 2 - cv.view_y, cg);
				}
				break;
			case EFFECTTYPE_CRITICAL:
				if (cg != -1)
				{
					DrawMemTh(ef[i].x - cv.view_x, ef[i].y - ef[i].h / 2 - cv.view_y, cg);
				}
				break;
			case EFFECTTYPE_ITEM_ATTACK:
				if (cg != -1) {
					if ((ef[i].id == 0) || (ef[i].id == 1) || (ef[i].id == 2) || (ef[i].id == 3) || (ef[i].id == 10) || (ef[i].id == 11) || (ef[i].id == 12)) {
						if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN) || (al.state == ALICE_STATE_ATTACK_DOWN) || (al.state == ALICE_STATE_ITEM_ATTACK_DOWN)) {
							if (ef[i].frame < 1) {
								DrawMemTh(ef[i].x + 40 - cv.view_x, ef[i].y - 40 - cv.view_y, cg);
							}
							else if (ef[i].frame < 2) {
								DrawMemTh(ef[i].x + 40 - cv.view_x, ef[i].y - cv.view_y, cg);
							}
						}
						else if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP) || (al.state == ALICE_STATE_ATTACK_UP) || (al.state == ALICE_STATE_ITEM_ATTACK_UP)) {
							if (ef[i].frame < 1) {
								DrawMemTh(ef[i].x + 40 - cv.view_x, ef[i].y + 120 - cv.view_y, cg);
							}
							else if (ef[i].frame < 2) {
								DrawMemTh(ef[i].x + 40 - cv.view_x, ef[i].y + 80 - cv.view_y, cg);
							}
						}
						else if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT) || (al.state == ALICE_STATE_ATTACK_RIGHT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT)) {
							if (ef[i].frame < 1) {
								DrawMemTh(ef[i].x - 40 - cv.view_x, ef[i].y + 40 - cv.view_y, cg);
							}
							else if (ef[i].frame < 2) {
								DrawMemTh(ef[i].x - cv.view_x, ef[i].y + 40 - cv.view_y, cg);
							}
						}
						else if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT) || (al.state == ALICE_STATE_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_LEFT)) {
							if (ef[i].frame < 1) {
								DrawMemTh(ef[i].x + 120 - cv.view_x, ef[i].y + 40 - cv.view_y, cg);
							}
							else if (ef[i].frame < 2) {
								DrawMemTh(ef[i].x + 80 - cv.view_x, ef[i].y + 40 - cv.view_y, cg);
							}
						}
						if (ef[i].frame > 1) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
						}
					}
					else if ((ef[i].id == 4) || (ef[i].id == 5) || (ef[i].id == 13)) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
					else if ((ef[i].id == 6) || (ef[i].id == 7) || (ef[i].id == 8) || (ef[i].id == 9) || (ef[i].id == 14) || (ef[i].id == 15) || (ef[i].id == 16)) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
				}
				break;
			case EFFECTTYPE_ENEMY_HATTER:
				if (cg != -1) {
					if (enatk[ef[i].id].rand == 0) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
					else if (enatk[ef[i].id].rand == 1) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
					else if (enatk[ef[i].id].rand == 2) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
						cg2++;
					}
				}
				break;
			case EFFECTTYPE_ENEMY_QUEEN:
				if (cg != -1) {
					if (enatk[ef[i].id].rand == 0) {
						if (ef[i].frame < 1) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
						}
						else if (ef[i].frame < 2) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - 40 - cv.view_y, cg);
						}
						else if (ef[i].frame < 3) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - 20 - cv.view_y, cg);
						}
						else if (ef[i].frame < 4) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
						}
					}
					else if (enatk[ef[i].id].rand == 1) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
					else if (enatk[ef[i].id].rand == 2) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
				}
				break;
			case EFFECTTYPE_ENEMY_HATTER2:
				if (cg != -1) {
					if (enatk[ef[i].id].rand == 0) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
					else if (enatk[ef[i].id].rand == 1) {
						DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
					}
					else if (enatk[ef[i].id].rand == 2) {
						if (ef[i].frame < 1) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
						}
						else if (ef[i].frame < 2) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - 40 - cv.view_y, cg);
						}
						else if (ef[i].frame < 3) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - 20 - cv.view_y, cg);
						}
						else if (ef[i].frame < 4) {
							DrawMemTh(ef[i].x - cv.view_x, ef[i].y - cv.view_y, cg);
						}
					}
				}
				break;
			}
		}
	}
}
