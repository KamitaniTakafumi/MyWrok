#pragma once
/*------------------------------------------------
*  @file HitJudgment.cpp
*  @brief 当たり判定処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// SEデータ

extern int seCursor;		// カーソル
extern int seSelect;		// セレクト
extern int seCancel;		// キャンセル
extern int seGetPlant;		// アイテムゲット(木の実系)
extern int seGetRock;		// アイテムゲット(岩系)
extern int seGetWater;		// アイテムゲット(水系)
extern int seGetPickup;		// 拾う
extern int seCreateItem;	// アイテム調合
extern int seAliceAttack;	// プレイヤー攻撃
extern int seAliceDamage;	// プレイヤーダメージ
extern int seEnemyDamage;	// エネミーダメージ
extern int seDead;			// 死亡
extern int seRecovery;		// 回復
extern int seOpen;			// オープン
extern int seMove;			// ステージ移動
extern int seWalk1;			// 歩き(ステージ１)
extern int seWalk2;			// 歩き(ステージ２)
extern int seBomb;			// ボム
extern int seBomb2;			// ボム２
extern int seRecipe;		// レシピ
extern int seFlash;			// ひらめき
extern int seWallBreak;		// 壁破壊
extern int seBoom;			// 人気
extern int seBladesound;	// 刃
extern int seFootstep;		// 足音(歩き)
extern int seFootstep_run;	// 足音(走り)
extern int seGetaway;		// 逃げる
extern int seOpendoor;		// 開ける
extern int seShock;			// 衝撃
extern int seSlashsound;	// 斬る
extern int seRun;			// 走る
extern int seFootstep_heel;	// 足音(ヒール)

// BGMデータ
extern int bgmTitle;		// タイトル
extern int bgmOp01;			// オープニング１
extern int bgmOp02;			// オープニング２
extern int bgmOp03;			// オープニング３
extern int I_home;			// ストーリー挿入曲１
extern int DCF;				// ストーリー挿入曲２
extern int Lucifer;			// ストーリー挿入曲３
extern int cheshirebgm;		// ストーリー挿入曲４
extern int Assault;			// ストーリー挿入曲５
extern int Be_quiet;		// ストーリー挿入曲６
extern int cheshirebgm2;	// ストーリー挿入曲７
extern int loneliness;		// ストーリー挿入曲８
extern int midnightmoon;	// ストーリー挿入曲９
extern int queenbgm;		// ストーリー挿入曲１０
extern int queenbgm2;		// ストーリー挿入曲１１
extern int madhatterbgm;	// ストーリー挿入曲１２
extern int reddress;		// ストーリー挿入曲１３
extern int reunion;			// ストーリー挿入曲１４
extern int dustwall;		// ストーリー挿入曲１５
extern int farewell;		// ストーリー挿入曲１６
extern int BGMSilent;		// ストーリー挿入曲１７
extern int Inherited_Hope;	// ストーリー挿入曲１８
extern int bgmMap1;			// ステージ１
extern int bgmMap2;			// ステージ２
extern int bgmBoss1;		// ボス１
extern int bgmBoss2;		// ボス２
extern int bgmBoss3;		// ボス３
extern int bgmEnd;			// エンディング

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// SEの読み込み
void LoadSe();
// BGMの読み込み
void LoadBgm();

// 当たり判定用。2つのboxが当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitBox(
	int x1, int y1, int w1, int h1,		// ひとつめのbox 左上(x,y), 大きさw,h
	int x2, int y2, int w2, int h2		// ふたつめのbox 左上(x,y), 大きさw,h
);

// 当たり判定用 2つのboxが当たったかを判定
// distanceでその分離れていても当たるようにすることができる
int IsHitBoxDistance(int x1, int y1, int x2, int y2, int distance);

// 当たり判定：プレイヤーと敵
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerEnemy(int enemyId);

// 当たり判定：プレイヤーと敵(行動範囲)
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerEnemyRange(int enemyId);

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack(int enemyId);

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack2(int enemyId);

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack3(int enemyId);

// 当たり判定：プレイヤーと敵攻撃
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitEnemyAttack4(int enemyId);

// 当たり判定：プレイヤー攻撃と敵
// 当たっていたらenemyId, 当たっていなかったら-1を返す
int IsHitPlayerAttack(int enemyId);

// 当たり判定：プレイヤーアイテム攻撃と敵
// 当たっていたらenemyId, 当たっていなかったら-1を返す
int IsHitPlayerItemAttack(int enemyId);

// 当たり判定：プレイヤーとオブジェクト
// 当たっていたらobjectId, 当たっていなかったら-1を返す
int IsHitPlayerObject(int objectId);

// 当たり判定：プレイヤーとオブジェクト
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerAttackObject();

// 当たり判定：プレイヤーと調合釜
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitPlayerAttackPreparation();

// 当たり判定：プレイヤーとドロップアイテム
// 当たっていた1, 当たっていなかったら0を返す
int IsHitPlayerAttackDrop();

// プレイヤーと敵の当たり処理
void HitCheckPlayerEnemy();

// プレイヤーと敵(行動範囲)の当たり処理
void HitCheckPlayerEnemyRange();

// プレイヤーと敵攻撃の当たり処理
void HitCheckEnemyAttack();

// プレイヤーの攻撃と敵の当たり処理
void HitCheckPlayerAttack();

// プレイヤーのアイテム攻撃と敵の当たり処理
void HitCheckPlayerItemAttack();

// プレイヤーと調合釜の当たり処理
void HitCheckPlayerPreparation();