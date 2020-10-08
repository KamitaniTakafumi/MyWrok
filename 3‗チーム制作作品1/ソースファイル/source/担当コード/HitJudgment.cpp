/*------------------------------------------------
*  @file HitJudgment.cpp
*  @brief 当たり判定処理
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
#include	"global.h"
#include    "alice.h"
#include    "enemy.h"
#include    "preparation.h"
#include    "HitJudgment.h"
#include    "Object.h"
#include    "Material.h"
#include	"aliceattack.h"
#include	"mapdata_1.h"
#include	"enemyattack.h"
#include	"Item.h"
#include	"game_effect.h"
#include	"recipe.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

int selectTrg = STATE_NONE;		// キー入力の判定
int flag = STATE_NONE;			// ヒットしたかの判定フラグ

// SEデータ

int seCursor;		// カーソル
int seSelect;		// セレクト
int seCancel;		// キャンセル
int seGetPlant;		// アイテムゲット(木の実系)
int seGetRock;		// アイテムゲット(岩系)
int seGetWater;		// アイテムゲット(水系)
int seGetPickup;	// 拾う
int seCreateItem;	// アイテム調合
int seAliceAttack;	// プレイヤー攻撃
int seAliceDamage;	// プレイヤーダメージ
int seEnemyDamage;	// エネミーダメージ
int seDead;			// 死亡
int seRecovery;		// 回復
int seOpen;			// オープン
int seMove;			// ステージ移動
int seWalk1;		// 歩き(ステージ１)
int seWalk2;		// 歩き(ステージ２)
int seBomb;			// ボム
int seBomb2;		// ボム２
int seRecipe;		// レシピ
int seFlash;		// ひらめき
int seWallBreak;	// 壁破壊
int seBoom;			// 人気
int seBladesound;	// 刃
int seFootstep;		// 足音(歩き)
int seFootstep_run;	// 足音(走り)
int seGetaway;		// 逃げる
int seOpendoor;		// 開ける
int seShock;		// 衝撃
int seSlashsound;	// 斬る
int seRun;			// 走る
int seFootstep_heel;// 足音(ヒール)

// BGMデータ
int bgmTitle;		// タイトル
int bgmOp01;		// オープニング１
int bgmOp02;		// オープニング２
int bgmOp03;		// オープニング３
int I_home;			// ストーリー挿入曲１
int DCF;			// ストーリー挿入曲２
int Lucifer;		// ストーリー挿入曲３
int cheshirebgm;	// ストーリー挿入曲４
int Assault;		// ストーリー挿入曲５
int Be_quiet;		// ストーリー挿入曲６
int cheshirebgm2;	// ストーリー挿入曲７
int loneliness;		// ストーリー挿入曲８
int midnightmoon;	// ストーリー挿入曲９
int queenbgm;		// ストーリー挿入曲１０
int queenbgm2;		// ストーリー挿入曲１１
int madhatterbgm;	// ストーリー挿入曲１２
int reddress;		// ストーリー挿入曲１３
int reunion;		// ストーリー挿入曲１４
int dustwall;		// ストーリー挿入曲１５
int farewell;		// ストーリー挿入曲１６
int BGMSilent;		// ストーリー挿入曲１７
int Inherited_Hope;	// ストーリー挿入曲１８
int bgmMap1;		// ステージ１
int bgmMap2;		// ステージ２
int bgmBoss1;		// ボス１
int bgmBoss2;		// ボス２
int bgmBoss3;		// ボス３
int bgmEnd;			// エンディング

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
// SEの読み込み
void LoadSe() {
	seCursor = LoadWavMem("res_se/cursor.wav");
	seSelect = LoadWavMem("res_se/Select.wav");
	seCancel = LoadWavMem("res_se/Cancel.wav");
	seGetPlant = LoadWavMem("res_se/GetPlant.wav");
	seGetRock = LoadWavMem("res_se/GetRock.wav");
	seGetPickup = LoadWavMem("res_se/GetPickup.wav");
	seCreateItem = LoadWavMem("res_se/CreateItem.wav");
	seAliceAttack = LoadWavMem("res_se/Alice_Attack.wav");
	seAliceDamage = LoadWavMem("res_se/AliceDamage.wav");
	seEnemyDamage = LoadWavMem("res_se/EnemyDamage.wav");
	seDead = LoadWavMem("res_se/GameOver.wav");
	seRecovery = LoadWavMem("res_se/recovery_1.wav");
	seOpen = LoadWavMem("res_se/open.wav");
	seMove = LoadWavMem("res_se/move.wav");
	seWalk1 = LoadWavMem("res_se/walk1.wav");
	seWalk2 = LoadWavMem("res_se/walk2.wav");
	seBomb = LoadWavMem("res_se/bomb.wav");
	seBomb2 = LoadWavMem("res_se/bomb2.wav");
	seRecipe = LoadWavMem("res_se/recipe.wav");
	seFlash = LoadWavMem("res_se/flash.wav");
	seWallBreak = LoadWavMem("res_se/wallbreak.wav");
	seBoom = LoadWavMem("res_se/boom.wav");
	seBladesound = LoadWavMem("res_se/bladesound.wav");
	seFootstep = LoadWavMem("res_se/footstep.wav");
	seFootstep_run = LoadWavMem("res_se/footstep_run.wav");
	seGetaway = LoadWavMem("res_se/getaway.wav");
	seOpendoor = LoadWavMem("res_se/opendoor.wav");
	seShock = LoadWavMem("res_se/shock.wav");
	seSlashsound = LoadWavMem("res_se/slashsound.wav");
	seRun = LoadWavMem("res_se/run.wav");
	seFootstep_heel = LoadWavMem("res_se/footstep_heel.wav");
}

// BGMの読み込み
void LoadBgm()
{
	bgmTitle = LoadWavMem("res_bgm/title.wav");
	bgmOp01 = LoadWavMem("res_bgm/StoryOp1-1.wav");
	bgmOp02 = LoadWavMem("res_bgm/StoryOp1-2.wav");
	bgmOp03 = LoadWavMem("res_bgm/StoryOp1-3.wav");
	I_home = LoadWavMem("res_bgm/I_home.wav");
	DCF = LoadWavMem("res_bgm/Dear_Childhood_Friend.wav");
	Lucifer = LoadWavMem("res_bgm/Lucifer.wav");
	cheshirebgm = LoadWavMem("res_bgm/cheshirebgm.wav");
	Assault = LoadWavMem("res_bgm/Assault.wav");
	Be_quiet = LoadWavMem("res_bgm/be_quiet.wav");
	cheshirebgm2 = LoadWavMem("res_bgm/cheshirebgm2.wav");
	loneliness = LoadWavMem("res_bgm/loneliness.wav");
	midnightmoon = LoadWavMem("res_bgm/midnightmoon.wav");
	queenbgm = LoadWavMem("res_bgm/queenbgm.wav");
	queenbgm2 = LoadWavMem("res_bgm/queenbgm2.wav");
	madhatterbgm = LoadWavMem("res_bgm/madhatterbgm.wav");
	reddress = LoadWavMem("res_bgm/reddress.wav");
	reunion = LoadWavMem("res_bgm/reunion.wav");
	dustwall = LoadWavMem("res_bgm/dustwall.wav");
	farewell = LoadWavMem("res_bgm/farewell.wav");
	BGMSilent = LoadWavMem("res_bgm/Silent.wav");
	Inherited_Hope = LoadWavMem("res_bgm/Inherited_Hope.wav");
	bgmMap1 = LoadWavMem("res_bgm/map1.wav");
	bgmMap2 = LoadWavMem("res_bgm/map2.wav");
	bgmBoss1 = LoadWavMem("res_bgm/boss1.wav");
	bgmBoss2 = LoadWavMem("res_bgm/boss2.wav");
	bgmBoss3 = LoadWavMem("res_bgm/boss3.wav");
	bgmEnd = LoadWavMem("res_bgm/end.wav");
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

// 当たり判定用。2つのboxが当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitBox(
	int x1, int y1, int w1, int h1,		// ひとつめのbox 左上(x,y), 大きさw,h
	int x2, int y2, int w2, int h2		// ふたつめのbox 左上(x,y), 大きさw,h
)
{
	if (x1 < x2 + w2 && x2 < x1 + w1		// x方向の判定
		&& y1 < y2 + h2 && y2 < y1 + h1		// y方向の判定
		)
	{
		// 2つのboxは当たっている
		return 1;
	}

	// 2つのboxは当たっていない
	return 0;
}

// 当たり判定用 2つのboxが当たったかを判定
// distanceでその分離れていても当たるようにすることができる
int IsHitBoxDistance(int x1, int y1, int x2, int y2, int distance) {
	return (abs(x1 - x2) < distance) && (abs(y1 - y2) < distance);
}

// 当たり判定：プレイヤーと敵
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerEnemy(int enemyId) {
	if (IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		en[enemyId].x + en[enemyId].hit_x, en[enemyId].y + en[enemyId].hit_y, en[enemyId].hit_w, en[enemyId].hit_h
	) != 0
		)
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵(行動範囲)
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerEnemyRange(int enemyId) {
	if (IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		en[enemyId].x + en[enemyId].hit_range_x, en[enemyId].y + en[enemyId].hit_range_y, en[enemyId].hit_range_w, en[enemyId].hit_range_h
	) != 0
		)
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack(int enemyId) {
	if (IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].hit_x, enatk[enemyId].y + enatk[enemyId].hit_y, enatk[enemyId].hit_w, enatk[enemyId].hit_h
	) != 0
		)
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack2(int enemyId) {
	if ((IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].hit_x, enatk[enemyId].y + enatk[enemyId].hit_y, enatk[enemyId].hit_w, enatk[enemyId].hit_h
	) != 0
		) || 
		(IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x2 + enatk[enemyId].hit_x, enatk[enemyId].y2 + enatk[enemyId].hit_y, enatk[enemyId].hit_w, enatk[enemyId].hit_h
		) != 0
		) || 
		(IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x3 + enatk[enemyId].hit_x, enatk[enemyId].y3 + enatk[enemyId].hit_y, enatk[enemyId].hit_w, enatk[enemyId].hit_h
		) != 0
		) || 
		(IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x4 + enatk[enemyId].hit_x, enatk[enemyId].y4 + enatk[enemyId].hit_y, enatk[enemyId].hit_w, enatk[enemyId].hit_h
		) != 0
		))
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack3(int enemyId) {
	if ((IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].hit_x, enatk[enemyId].y + enatk[enemyId].hit_y, enatk[enemyId].hit_w, enatk[enemyId].hit_h
	) != 0
		) ||
		(IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x2 + enatk[enemyId].hit_x2, enatk[enemyId].y2 + enatk[enemyId].hit_y2, enatk[enemyId].hit_w2, enatk[enemyId].hit_h2
		) != 0
			) ||
			(IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x3 + enatk[enemyId].hit_x, enatk[enemyId].y3 + enatk[enemyId].hit_y, enatk[enemyId].hit_w, enatk[enemyId].hit_h
			) != 0
				) ||
				(IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x4 + enatk[enemyId].hit_x2, enatk[enemyId].y4 + enatk[enemyId].hit_y2, enatk[enemyId].hit_w2, enatk[enemyId].hit_h2
				) != 0
					))
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack4(int enemyId) {
	if ((IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].range_x, enatk[enemyId].y + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
	) != 0
		) ||
		(IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x2 + enatk[enemyId].range_x2, enatk[enemyId].y2 + enatk[enemyId].range_y2, enatk[enemyId].range_w2, enatk[enemyId].range_h2
		) != 0
			) ||
			(IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x3 + enatk[enemyId].range_x, enatk[enemyId].y3 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) ||
				(IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x4 + enatk[enemyId].range_x2, enatk[enemyId].y4 + enatk[enemyId].range_y2, enatk[enemyId].range_w2, enatk[enemyId].range_h2
				) != 0
					)
		|| (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x5 + enatk[enemyId].range_x, enatk[enemyId].y5 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
			) || (IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x6 + enatk[enemyId].range_x, enatk[enemyId].y6 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) || (IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x7 + enatk[enemyId].range_x, enatk[enemyId].y7 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
				) != 0
					) || (IsHitBox(
						al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
						enatk[enemyId].x8 + enatk[enemyId].range_x, enatk[enemyId].y8 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
					) != 0
						)
		|| (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x9 + enatk[enemyId].range_x, enatk[enemyId].y9 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
			) || (IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x10 + enatk[enemyId].range_x, enatk[enemyId].y10 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) || (IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x11 + enatk[enemyId].range_x, enatk[enemyId].y11 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
				) != 0
					) || (IsHitBox(
						al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
						enatk[enemyId].x12 + enatk[enemyId].range_x, enatk[enemyId].y12 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
					) != 0
						)
		|| (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x13 + enatk[enemyId].range_x, enatk[enemyId].y13 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
			) || (IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x14 + enatk[enemyId].range_x, enatk[enemyId].y14 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) || (IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x15 + enatk[enemyId].range_x, enatk[enemyId].y15 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
				) != 0
					) || (IsHitBox(
						al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
						enatk[enemyId].x16 + enatk[enemyId].range_x, enatk[enemyId].y16 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
					) != 0
						))
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttackRange(int enemyId) {
	if (IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].range_x, enatk[enemyId].y + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
	) != 0
		)
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttackRange2(int enemyId) {
	if ((IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].range_x, enatk[enemyId].y + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
	) != 0
		) || 
	(IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x2 + enatk[enemyId].range_x, enatk[enemyId].y2 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
	) != 0
		) ||
	(IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x3 + enatk[enemyId].range_x, enatk[enemyId].y3 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
		) ||
	(IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x4 + enatk[enemyId].range_x, enatk[enemyId].y4 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
		))
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttackRange3(int enemyId) {
	if ((IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].range_x, enatk[enemyId].y + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
	) != 0
		) ||
		(IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x2 + enatk[enemyId].range_x2, enatk[enemyId].y2 + enatk[enemyId].range_y2, enatk[enemyId].range_w2, enatk[enemyId].range_h2
		) != 0
			) ||
			(IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x3 + enatk[enemyId].range_x, enatk[enemyId].y3 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) ||
				(IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x4 + enatk[enemyId].range_x2, enatk[enemyId].y4 + enatk[enemyId].range_y2, enatk[enemyId].range_w2, enatk[enemyId].range_h2
				) != 0
					))
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttackRange4(int enemyId) {
	if ((IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		enatk[enemyId].x + enatk[enemyId].range_x, enatk[enemyId].y + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
	) != 0
		) ||
		(IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x2 + enatk[enemyId].range_x2, enatk[enemyId].y2 + enatk[enemyId].range_y2, enatk[enemyId].range_w2, enatk[enemyId].range_h2
		) != 0
			) ||
			(IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x3 + enatk[enemyId].range_x, enatk[enemyId].y3 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) ||
				(IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x4 + enatk[enemyId].range_x2, enatk[enemyId].y4 + enatk[enemyId].range_y2, enatk[enemyId].range_w2, enatk[enemyId].range_h2
				) != 0
					)
		|| (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x5 + enatk[enemyId].range_x, enatk[enemyId].y5 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
			) || (IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x6 + enatk[enemyId].range_x, enatk[enemyId].y6 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) || (IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x7 + enatk[enemyId].range_x, enatk[enemyId].y7 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
				) != 0
					) || (IsHitBox(
						al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
						enatk[enemyId].x8 + enatk[enemyId].range_x, enatk[enemyId].y8 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
					) != 0
						)
		|| (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x9 + enatk[enemyId].range_x, enatk[enemyId].y9 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
			) || (IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x10 + enatk[enemyId].range_x, enatk[enemyId].y10 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) || (IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x11 + enatk[enemyId].range_x, enatk[enemyId].y11 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
				) != 0
					) || (IsHitBox(
						al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
						enatk[enemyId].x12 + enatk[enemyId].range_x, enatk[enemyId].y12 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
					) != 0
						)
		|| (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			enatk[enemyId].x13 + enatk[enemyId].range_x, enatk[enemyId].y13 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
		) != 0
			) || (IsHitBox(
				al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				enatk[enemyId].x14 + enatk[enemyId].range_x, enatk[enemyId].y14 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
			) != 0
				) || (IsHitBox(
					al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
					enatk[enemyId].x15 + enatk[enemyId].range_x, enatk[enemyId].y15 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
				) != 0
					) || (IsHitBox(
						al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
						enatk[enemyId].x16 + enatk[enemyId].range_x, enatk[enemyId].y16 + enatk[enemyId].range_y, enatk[enemyId].range_w, enatk[enemyId].range_h
					) != 0
						))
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと調合釜
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerPreparation(int preId)
{
	if (IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		pre[preId].x + pre[preId].hit_x, pre[preId].y + pre[preId].hit_y, pre[preId].hit_w, pre[preId].hit_h
	) != 0
		)
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤーと調合釜
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerAttackPreparation()
{
	for (int i = 0; i < PREPARATION_MAX; i++) {
		if (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			pre[i].x + pre[i].hit_x, pre[i].y + pre[i].hit_y, pre[i].hit_w, pre[i].hit_h
		) != 0
			)
		{
			return 1;
		}
	}
	return 0;
}

// 当たり判定：敵と調合釜(安全範囲)
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyPreparation(int enemyId, int preId)
{
	if (IsHitBox(
		en[enemyId].x + en[enemyId].hit_x, en[enemyId].y + en[enemyId].hit_y, en[enemyId].hit_w, en[enemyId].hit_h,
		pre[preId].x + pre[preId].hit_range_x, pre[preId].y + pre[preId].hit_range_y, pre[preId].hit_range_w, pre[preId].hit_range_h
	) != 0
		)
	{
		return 1;
	}
	return 0;
}

// 当たり判定：プレイヤー攻撃と敵
// 当たっていたらenemyId, 当たっていなかったら-1を返す
int IsHitPlayerAttack(int enemyId) {
	if (IsHitBox(
		atk.x + atk.hit_x, atk.y + atk.hit_y, atk.hit_w, atk.hit_h,
		en[enemyId].x + en[enemyId].hit_x, en[enemyId].y + en[enemyId].hit_y, en[enemyId].hit_w, en[enemyId].hit_h
	) != 0
		)
	{
		return enemyId;
	}
	return -1;
}

// 当たり判定：プレイヤーアイテム攻撃と敵
// 当たっていたらenemyId, 当たっていなかったら-1を返す
int IsHitPlayerItemAttack(int enemyId) {
	if (IsHitBox(
		atkit.x + atkit.hit_x, atkit.y + atkit.hit_y, atkit.hit_w, atkit.hit_h,
		en[enemyId].x + en[enemyId].hit_x, en[enemyId].y + en[enemyId].hit_y, en[enemyId].hit_w, en[enemyId].hit_h
	) != 0
		)
	{
		return enemyId;
	}
	return -1;
}

// 当たり判定：プレイヤーとオブジェクト
// 当たっていたらobjectId, 当たっていなかったら-1を返す
int IsHitPlayerObject(int objectId)
{
	if (IsHitBox(
		al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
		obj[objectId].x + obj[objectId].hit_x, obj[objectId].y + obj[objectId].hit_y, obj[objectId].hit_w, obj[objectId].hit_h
	) != 0
		)
	{
		return objectId;
	}
	return -1;
}

// 当たり判定：プレイヤーとオブジェクト
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerAttackObject()
{
	for (int i = 0; i < OBJECT_MAX; i++) {
		if (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			obj[i].x + obj[i].hit_x, obj[i].y + obj[i].hit_y, obj[i].hit_w, obj[i].hit_h
		) != 0
			)
		{
			return 1;
		}
	}
	return 0;
}

// 当たり判定：プレイヤーとドロップアイテム
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerAttackDrop()
{
	for (int i = 7; i < MATERIAL_NUMBER; i++) {
		if (IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			material[i].x + material[i].hit_x, material[i].y + material[i].hit_y, material[i].hit_w, material[i].hit_h
		) != 0
			)
		{
			return 1;
		}
	}
	return 0;
}

// プレイヤーと敵の当たり処理
void HitCheckPlayerEnemy() {
	// 主人公の当たり判定を行うか？
	if (IsHitProcessPlayer() == 0) { return; }

	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// この敵は使用中か？
		if (en[i].use == 0)
		{	// 未使用
			continue;
		}
		if (IsHitPlayerEnemy(i) != 0) {
			if (check == STATE_NONE) {
				PlayMemBack(seAliceDamage);		// SE再生
				al.hitpoint--;					// 体力を減らす
			}
			if (al.hitpoint <= 0) {
				PlayMemBack(seDead);	// SE再生
				// 60フレームのゲームオーバーまでの間
				gGameoverCount = 60;	// ゲームオーバーまでの時間

				// 主人公を不使用とする
				al.use = 0;

				// BGM再生ストップ
				StopPlayMem(bgmMap1); 
				StopPlayMem(bgmMap2);
				StopPlayMem(bgmBoss1);
				StopPlayMem(bgmBoss2);
				StopPlayMem(bgmBoss3);
			}
			else {
				al.nohit_cnt = 60;		// 無敵時間設定
			}
		}
	}
}

// プレイヤーと敵(行動範囲)の当たり処理
void HitCheckPlayerEnemyRange() {
	int i, j;
	for (i = 0; i < ENEMY_MAX; i++) {
		for (j = 0; j < PREPARATION_MAX; j++) {
			if (IsHitPlayerEnemyRange(i) != 0) {
				if (IsHitEnemyPreparation(i, j) != 0) {
					en[i].state = STATE_NONE;
					if ((en[i].direction == ENEMY_STATE_RIGHT) ||
						(en[i].direction == ENEMY_STATE_LEFT)) {
						en[i].period = 30;
						en[i].period3 = 0;
					}
					if ((en[i].direction == ENEMY_STATE_DOWN) ||
						(en[i].direction == ENEMY_STATE_UP)) {
						en[i].period2 = 10;
						en[i].period3 = 0;
					}
				}
				else {
					if ((en[i].period <= 0) & (en[i].period2 <= 0)) {
						en[i].state = STATE_ONE;
					}
				}
			}
			else {
				en[i].state = STATE_NONE;
			}
		}
	}
}

// プレイヤーと敵攻撃の当たり処理
void HitCheckEnemyAttack() {
	// 主人公の当たり判定を行うか？
	if (IsHitProcessPlayer() == 0) { return; }

	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// この敵は使用中か？
		if (en[i].use == 0)
		{	// 未使用
			continue;
		}
		if (enatk[i].rand == 0) {
			if (en[i].entype == ENEMY_QUEEN) {
				if (IsHitEnemyAttackRange4(i) != 0) {
					if (check == STATE_NONE) {
						PlayMemBack(seAliceDamage);		// SE再生
						al.hitpoint--;					// 体力を減らす
					}
					if (al.hitpoint <= 0) {
						PlayMemBack(seDead);	// SE再生
						// 60フレームのゲームオーバーまでの間
						gGameoverCount = 60;	// ゲームオーバーまでの時間

						// 主人公を不使用とする
						al.use = 0;

						// BGM再生ストップ
						StopPlayMem(bgmMap1);
						StopPlayMem(bgmMap2);
						StopPlayMem(bgmBoss1);
						StopPlayMem(bgmBoss2);
						StopPlayMem(bgmBoss3);
					}
					else {
						al.nohit_cnt = 60;		// 無敵時間設定
					}
				}
			}
			else if (IsHitEnemyAttackRange(i) != 0) {
				if (check == STATE_NONE) {
					PlayMemBack(seAliceDamage);		// SE再生
					al.hitpoint--;					// 体力を減らす
				}
				if (al.hitpoint <= 0) {
					PlayMemBack(seDead);	// SE再生
					// 60フレームのゲームオーバーまでの間
					gGameoverCount = 60;	// ゲームオーバーまでの時間

					// 主人公を不使用とする
					al.use = 0;

					// BGM再生ストップ
					StopPlayMem(bgmMap1);
					StopPlayMem(bgmMap2);
					StopPlayMem(bgmBoss1);
					StopPlayMem(bgmBoss2);
					StopPlayMem(bgmBoss3);
				}
				else {
					al.nohit_cnt = 60;		// 無敵時間設定
				}
			}
		}
		else if (enatk[i].rand == 1) {
			if (IsHitEnemyAttackRange2(i) != 0) {
				if (check == STATE_NONE) {
					PlayMemBack(seAliceDamage);		// SE再生
					al.hitpoint--;					// 体力を減らす
				}
				if (al.hitpoint <= 0) {
					PlayMemBack(seDead);	// SE再生
					// 60フレームのゲームオーバーまでの間
					gGameoverCount = 60;	// ゲームオーバーまでの時間

					// 主人公を不使用とする
					al.use = 0;

					// BGM再生ストップ
					StopPlayMem(bgmMap1);
					StopPlayMem(bgmMap2);
					StopPlayMem(bgmBoss1);
					StopPlayMem(bgmBoss2);
					StopPlayMem(bgmBoss3);
				}
				else {
					al.nohit_cnt = 60;		// 無敵時間設定
				}
			}
		}
		else if (enatk[i].rand == 2) {
			if (IsHitEnemyAttackRange3(i) != 0) {
				if (check == STATE_NONE) {
					PlayMemBack(seAliceDamage);		// SE再生
					al.hitpoint--;					// 体力を減らす
				}
				if (al.hitpoint <= 0) {
					PlayMemBack(seDead);	// SE再生
					// 60フレームのゲームオーバーまでの間
					gGameoverCount = 60;	// ゲームオーバーまでの時間

					// 主人公を不使用とする
					al.use = 0;

					// BGM再生ストップ
					StopPlayMem(bgmMap1);
					StopPlayMem(bgmMap2);
					StopPlayMem(bgmBoss1);
					StopPlayMem(bgmBoss2);
					StopPlayMem(bgmBoss3);
				}
				else {
					al.nohit_cnt = 60;		// 無敵時間設定
				}
			}
		}
	}
}

// プレイヤーの攻撃と敵の当たり処理
void HitCheckPlayerAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// この敵は使用中か？
		if (en[i].use == 0)
		{	// 未使用
			continue;
		}
		// 敵の当たり判定を行うか？
		if (IsHitProcessEnemy(i) == 0) { return; }

		if ((en[i].nohit_cnt <= 0) & (en[i].state_enemy != 1)) {
			if (IsHitPlayerAttack(i) != -1) {
				// ダメージを受けたか
				if (en[i].damagecooltime <= 0) {
					PlayMemBack(seEnemyDamage);		// SE再生
					en[i].damagecooltime = 10;		// 攻撃を受けた時の待ち時間
					enatk[i].select_attack = 0;		// 攻撃のパターンの初期化
					en[i].hp--;					// 敵体力減少
					en[i].damage_point++;
					PutEffect(EFFECTTYPE_ENEMY_DAMAGE, en[i].x + en[i].w / 2, en[i].y + en[i].h / 2, i);
					PutEffect(EFFECTTYPE_DAMAGE, en[i].x + (en[i].w / 6), en[i].y - (en[i].h / 4), i);
				}
				// 敵体力がなくなったら
				if (en[i].hp <= 0) {
					if (en[i].state_enemy != 1) {
						PutEffect(EFFECTTYPE_BOMB, en[i].x + en[i].w / 2, en[i].y + en[i].h / 2, i);
					}
					if ((en[i].entype == ENEMY_MERGE_MATANGO) || (en[i].entype == ENEMY_HEART)) {
						en[i].required = 1;
						required_count++;
						switch (stateStage) {
						case STATE_EP1STAGE_2:
						case STATE_EP1STAGE_3:
							if ((required_count == 2) || (required_count == 4)) {
								wallwait = 600;
							}
							break;
						case STATE_EP2STAGE1_1:
						case STATE_EP2STAGE1_2:
						case STATE_EP2STAGE1_3:
						case STATE_EP2STAGE2_1:
							if ((required_count == 3) || (required_count == 6) || (required_count == 8)) {
								wallwait = 600;
							}
							break;
						}
						
					}
					en[i].use = 0;				// 敵を消す
					if (en[i].entype == ENEMY_MAD_HATTER) {
						en[i].use = 1;
						en[i].state_enemy = 1;
						clearwait = 60;
					}
					if (en[i].entype == ENEMY_QUEEN) {
						en[i].use = 1;
						en[i].state_enemy = 1;
						clearwait = 60;
					}
					if (en[i].entype == ENEMY_MAD_HATTER2) {
						en[i].use = 1;
						en[i].state_enemy = 1;
						clearwait = 60;
					}
					//en[i].respawn_time = 300;
					if (en[i].recipe_no == 0) {
						if ((en[i].entype != ENEMY_MAD_HATTER) || (en[i].entype != ENEMY_QUEEN) || (en[i].entype != ENEMY_MAD_HATTER2)) {
							for (int j = 7; j < 27; j++) {
								if (material[j].use == 0) {
									material[j].use = 1;		// ドロップアイテムを表示
									material[j].enpoz_x = en[i].x;
									material[j].enpoz_y = en[i].y;
									break;
								}
							}
						}
					}
					if (en[i].recipe_no != 0) {
						for (int k = 27; k < MATERIAL_NUMBER; k++) {
							if (material[k].use_recipe == 0) {
								material[k].use_recipe = 1;
								material[k].enpoz_x = en[i].x;
								material[k].enpoz_y = en[i].y;
								if (en[i].recipe_no == 1) {
									recipe1 = en[i].recipe_no;
									break;
								}
								else if (en[i].recipe_no == 2) {
									recipe2 = en[i].recipe_no;
									break;
								}
								else if (en[i].recipe_no == 3) {
									recipe3 = en[i].recipe_no;
									break;
								}
								if (en[i].recipe_no == 4) {
									recipe1 = en[i].recipe_no;
									break;
								}
								else if (en[i].recipe_no == 5) {
									recipe2 = en[i].recipe_no;
									break;
								}
								else if (en[i].recipe_no == 6) {
									recipe3 = en[i].recipe_no;
									break;
								}
							}
						}
					}
				}
				else {
					en[i].nohit_cnt = 60;		// 無敵時間設定
				}
			}
		}
		// ダメージの待ち時間があれば
		if (en[i].damagecooltime > 0) {
			en[i].damagecooltime--;
		}
		else {
			en[i].damagecooltime = 0;
		}
	}
}

// プレイヤーのアイテム攻撃と敵の当たり処理
void HitCheckPlayerItemAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// この敵は使用中か？
		if (en[i].use == 0)
		{	// 未使用
			continue;
		}
		// 敵の当たり判定を行うか？
		if (IsHitProcessEnemy(i) == 0) { return; }

		if (en[i].nohit_cnt <= 0) {
			if (IsHitItemAttack() != 0) {
				if (IsHitPlayerItemAttack(i) != -1) {
					// ダメージを受けたか
					if (en[i].itemdamagecooltime <= 0) {
						PlayMemBack(seEnemyDamage);		// SE再生
						en[i].itemdamagecooltime = 10;	// 攻撃を受けた時の待ち時間
						ItemDamage(i);					// ダメージ処理
						PutEffect(EFFECTTYPE_ENEMY_DAMAGE, en[i].x + en[i].w / 2, en[i].y + en[i].h / 2, i);
					}
					// 敵体力がなくなったら
					if (en[i].hp <= 0) {
						if (en[i].state_enemy != 1) {
							PutEffect(EFFECTTYPE_BOMB, en[i].x + en[i].w / 2, en[i].y + en[i].h / 2, i);
						}
						if ((en[i].entype == ENEMY_MERGE_MATANGO) || (en[i].entype == ENEMY_HEART)) {
							en[i].required = 1;
							required_count++;
							switch (stateStage) {
							case STATE_EP1STAGE_2:
							case STATE_EP1STAGE_3:
								if ((required_count == 2) || (required_count == 4)) {
									wallwait = 600;
								}
								break;
							case STATE_EP2STAGE1_1:
							case STATE_EP2STAGE1_2:
							case STATE_EP2STAGE1_3:
							case STATE_EP2STAGE2_1:
								if ((required_count == 3) || (required_count == 6) || (required_count == 8)) {
									wallwait = 600;
								}
								break;
							}

						}
						en[i].use = 0;				// 敵を消す
						if (en[i].entype == ENEMY_MAD_HATTER) {
							en[i].use = 1;
							en[i].state_enemy = 1;
							clearwait = 60;
						}
						if (en[i].entype == ENEMY_QUEEN) {
							en[i].use = 1;
							en[i].state_enemy = 1;
							clearwait = 60;
						}
						if (en[i].entype == ENEMY_MAD_HATTER2) {
							en[i].use = 1;
							en[i].state_enemy = 1;
							clearwait = 60;
						}
						//en[i].respawn_time = 300;
						if (en[i].recipe_no == 0) {
							if ((en[i].entype != ENEMY_MAD_HATTER) || (en[i].entype != ENEMY_QUEEN) || (en[i].entype != ENEMY_MAD_HATTER2)) {
								for (int j = 7; j < 27; j++) {
									if (material[j].use == 0) {
										material[j].use = 1;		// ドロップアイテムを表示
										material[j].enpoz_x = en[i].x;
										material[j].enpoz_y = en[i].y;
										break;
									}
								}
							}
						}
						if (en[i].recipe_no != 0) {
							for (int k = 27; k < MATERIAL_NUMBER; k++) {
								if (material[k].use_recipe == 0) {
									material[k].use_recipe = 1;
									material[k].enpoz_x = en[i].x;
									material[k].enpoz_y = en[i].y;
									if (en[i].recipe_no == 1) {
										recipe1 = en[i].recipe_no;
										break;
									}
									else if (en[i].recipe_no == 2) {
										recipe2 = en[i].recipe_no;
										break;
									}
									else if (en[i].recipe_no == 3) {
										recipe3 = en[i].recipe_no;
										break;
									}
									if (en[i].recipe_no == 4) {
										recipe1 = en[i].recipe_no;
										break;
									}
									else if (en[i].recipe_no == 5) {
										recipe2 = en[i].recipe_no;
										break;
									}
									else if (en[i].recipe_no == 6) {
										recipe3 = en[i].recipe_no;
										break;
									}
								}
							}
						}
					}
					else {
						en[i].nohit_cnt = 80;		// 無敵時間設定
					}
				}
			}
		}
		// ダメージの待ち時間があれば
		if (en[i].itemdamagecooltime > 0) {
			en[i].itemdamagecooltime--;
		}
		else {
			en[i].itemdamagecooltime = 0;
		}
	}
}

// プレイヤーと調合釜の当たり処理
void HitCheckPlayerPreparation()
{
	for (int i = 0; i < PREPARATION_MAX; i++) {
		// プレイヤーと調合釜の当たり判定
		if (IsHitPlayerPreparation(i) != 0)
		{
			//当たった
			switch (stateStage) {
			case STATE_EP1STAGE:
				obj[8].use = 1;
				break;
			case STATE_EP1STAGE_2:
				obj[16].use = 1;
				break;
			case STATE_EP1STAGE_3:
				obj[22].use = 1;
				break;
			case STATE_EP2STAGE1_1:
				obj[2].use = 1;
				break;
			case STATE_EP2STAGE1_2:
				obj[14].use = 1;
				break;
			case STATE_EP2STAGE1_3:
				obj[9].use = 1;
				break;
			case STATE_EP2STAGE2_1:
				obj[9].use = 1;
				break;
			case STATE_EP2STAGE2_2:
				obj[9].use = 1;
				break;
			}
			// 当たった
			if (flag == STATE_NONE) {
				if (check == STATE_NONE) {
					if (gTrg & KEYIN_X) {
						StopPlayMem(seWalk1);
						StopPlayMem(seWalk2);
						PlayMemBack(seSelect);
						flag = STATE_ONE;
						selectTrg = STATE_ONE;
					}
				}
			}
			if (flag == STATE_ONE) {
				if (gFrameWait <= 0) {
					if (gTrg & KEYIN_Z) {
						PlayMemBack(seCancel);
						flag = STATE_NONE;
						selectTrg = STATE_NONE;
						InitSelect();
					}
				}
			}
			break;
		}
		else {
			switch (stateStage) {
			case STATE_EP1STAGE:
				obj[8].use = 0;
				break;
			case STATE_EP1STAGE_2:
				obj[16].use = 0;
				break;
			case STATE_EP1STAGE_3:
				obj[22].use = 0;
				break;
			case STATE_EP2STAGE1_1:
				obj[2].use = 0;
				break;
			case STATE_EP2STAGE1_2:
				obj[14].use = 0;
				break;
			case STATE_EP2STAGE1_3:
				obj[9].use = 0;
				break;
			case STATE_EP2STAGE2_1:
				obj[9].use = 0;
				break;
			case STATE_EP2STAGE2_2:
				obj[9].use = 0;
				break;
			}
		}
	}
}

// プレイヤーとオブジェクトの当たり処理
void HitCheckPlayerObject()
{
	int i, j;
	for (i = 0; i < OBJECT_MAX; i++) {
		// 所持素材ウィンドウは表示されていないか
		if (check == STATE_NONE) {
				//プレイヤーとオブジェクトの当たり判定
			if (IsHitPlayerObject(i) != -1)
			{
				if (obj[i].gatherlimit > 0) {
					//当たった
					switch (stateStage) {
					case STATE_EP1STAGE:
						obj[7].use = 1;
						break;
					case STATE_EP1STAGE_2:
						obj[15].use = 1;
						break;
					case STATE_EP1STAGE_3:
						obj[21].use = 1;
						break;
					case STATE_EP2STAGE1_1:
						obj[1].use = 1;
						break;
					case STATE_EP2STAGE1_2:
						obj[13].use = 1;
						break;
					case STATE_EP2STAGE1_3:
						obj[8].use = 1;
						break;
					case STATE_EP2STAGE2_1:
						obj[8].use = 1;
						break;
					case STATE_EP2STAGE2_2:
						obj[8].use = 1;
						break;
					}
					switch (stateStage) {
					case STATE_EP1STAGE:
						if (i == 0){
							j = 0;
						}
						else if (i == 1) {
							j = 1;
						}
						else if (i == 2) {
							j = 2;
						}
						else if (i == 3) {
							j = 3;
						}
						else if (i == 4) {
							j = 4;
						}
						else if (i == 5) {
							j = 5;
						}
						else if (i == 6) {
							j = 6;
						}
						break;
					case STATE_EP1STAGE_2:
						if ((i == 0) || (i == 8) || (i == 9)) {
							j = 0;
						}
						else if ((i == 1) || (i == 10)) {
							j = 1;
						}
						else if ((i == 2) || (i == 11)) {
							j = 2;
						}
						else if ((i == 3) || (i == 12)) {
							j = 3;
						}
						else if ((i == 4) || (i == 13) || (i == 14)) {
							j = 4;
						}
						else if (i == 5) {
							j = 5;
						}
						else if ((i == 6) || (i == 7)) {
							j = 6;
						}
						break;
					case STATE_EP1STAGE_3:
						if ((i == 0) || (i == 8) || (i == 9)) {
							j = 0;
						}
						else if ((i == 1) || (i == 10) || (i == 11)) {
							j = 1;
						}
						else if ((i == 2) || (i == 12) || (i == 13)) {
							j = 2;
						}
						else if ((i == 3) || (i == 14) || (i == 15)) {
							j = 3;
						}
						else if ((i == 4) || (i == 16) || (i == 17)) {
							j = 4;
						}
						else if ((i == 5) || (i == 18) || (i == 19)) {
							j = 5;
						}
						else if ((i == 6) || (i == 20) || (i == 7)) {
							j = 6;
						}
						break;
					case STATE_EP2STAGE1_1:
						if (i == 0) {
							j = 6;
						}
						break;
					case STATE_EP2STAGE1_2:
						if ((i == 0) || (i == 1) || (i == 2)) {
							j = 0;
						}
						else if ((i == 3) || (i == 4)) {
							j = 1;
						}
						else if ((i == 5) || (i == 6)) {
							j = 2;
						}
						else if ((i == 7) || (i == 8)) {
							j = 3;
						}
						else if ((i == 9) || (i == 10)) {
							j = 4;
						}
						else if (i == 11) {
							j = 5;
						}
						else if (i == 12) {
							j = 6;
						}
						break;
					case STATE_EP2STAGE1_3:
						if (i == 0) {
							j = 0;
						}
						else if (i == 1) {
							j = 1;
						}
						else if (i == 2) {
							j = 2;
						}
						else if (i == 3) {
							j = 3;
						}
						else if (i == 4) {
							j = 4;
						}
						else if (i == 5) {
							j = 5;
						}
						else if (i == 6) {
							j = 6;
						}
						else {
							j = 7;
						}
						break;
					case STATE_EP2STAGE2_1:
						if (i == 0) {
							j = 0;
						}
						else if (i == 1) {
							j = 1;
						}
						else if (i == 2) {
							j = 2;
						}
						else if (i == 3) {
							j = 3;
						}
						else if (i == 4) {
							j = 4;
						}
						else if (i == 5) {
							j = 5;
						}
						else if (i == 6) {
							j = 6;
						}
						else {
							j = 7;
						}
						break;
					case STATE_EP2STAGE2_2:
						if (i == 0) {
							j = 0;
						}
						else if (i == 1) {
							j = 1;
						}
						else if (i == 2) {
							j = 2;
						}
						else if (i == 3) {
							j = 3;
						}
						else if (i == 4) {
							j = 4;
						}
						else if (i == 5) {
							j = 5;
						}
						else if (i == 6) {
							j = 6;
						}
						else {
							j = 7;
						}
						break;
					}
					if (gFrameWait == 0) {
						GetMaterial(i, j);
					}
					if (obj[i].gatherlimit <= 0) {
						obj[i].getwait = 300;			// 再採取できるまでの時間(5秒)
						obj[i].use = 0;					// ポイントを消す
					}
					break;
				}
			}
			else {
				switch (stateStage) {
				case STATE_EP1STAGE:
					obj[7].use = 0;
					break;
				case STATE_EP1STAGE_2:
					obj[15].use = 0;
					break;
				case STATE_EP1STAGE_3:
					obj[21].use = 0;
					break;
				case STATE_EP2STAGE1_1:
					obj[1].use = 0;
					break;
				case STATE_EP2STAGE1_2:
					obj[13].use = 0;
					break;
				case STATE_EP2STAGE1_3:
					obj[8].use = 0;
					break;
				case STATE_EP2STAGE2_1:
					obj[8].use = 0;
					break;
				case STATE_EP2STAGE2_2:
					obj[8].use = 0;
					break;
				}
			}
		}
	}
}
