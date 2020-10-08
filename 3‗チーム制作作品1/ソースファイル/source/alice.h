#pragma once
//
// 定数・構造体定義
//
struct ALICE
{
	int     use;        // 0:使用しない　1:使用中
	int		x, y;		// 座標
	int		w, h;		// 大きさ
	int		spd;		// 移動速度
	int		state;		// 状態
	int	    hit_x, hit_y, hit_w, hit_h;  //当たり判定
	int		hitpoint;						// 体力
	int     nohit_cnt;                      // 無敵時間
	int		move;		// 部屋の移動
};

enum alice_state {

	//アリスが止まっている方向
	ALICE_STATE_IDLE_UP,
	ALICE_STATE_IDLE_DOWN,
	ALICE_STATE_IDLE_LEFT,
	ALICE_STATE_IDLE_RIGHT,

	// アリスの向いている方向
	ALICE_STATE_UP,
	ALICE_STATE_DOWN,
	ALICE_STATE_RIGHT,
	ALICE_STATE_LEFT,

	// アリスが攻撃している方向
	ALICE_STATE_ATTACK_UP,
	ALICE_STATE_ATTACK_DOWN,
	ALICE_STATE_ATTACK_RIGHT,
	ALICE_STATE_ATTACK_LEFT,

	// アリスが採取している方向
	ALICE_STATE_GATHERING_UP,
	ALICE_STATE_GATHERING_DOWN,
	ALICE_STATE_GATHERING_RIGHT,
	ALICE_STATE_GATHERING_LEFT,

	// アリスがアイテムを使用している方向
	ALICE_STATE_ITEM_ATTACK_UP,
	ALICE_STATE_ITEM_ATTACK_DOWN,
	ALICE_STATE_ITEM_ATTACK_RIGHT,
	ALICE_STATE_ITEM_ATTACK_LEFT
};

// プレイヤー情報
extern struct ALICE al;

// アリスが止まっている画像
extern int cgAliceIdleUp;
extern int cgAliceIdleDown;
extern int cgAliceIdleLeft;
extern int cgAliceIdleRight;

// アリスが歩く画像
extern int cgAliceUp[4];			// アリス上向き
extern int cgAliceDown[4];		// アリス下向き
extern int cgAliceLeft[4];		// アリス左向き
extern int cgAliceRight[4];		// アリス右向き

// アリスが攻撃している画像
extern int cgAliceAttackUp[6];
extern int cgAliceAttackDown[6];
extern int cgAliceAttackLeft[6];
extern int cgAliceAttackRight[6];

// アリスがやられた画像
extern int cgAliceDeathL[2];
extern int cgAliceDeathR[2];
extern int cgAliceDeathU[2];
extern int cgAliceDeathD[2];

// グローバル変数
extern int imagetime;
extern int alice_freeze;

// 画像読み込み
void LoadCgAlice();
void LoadCgAlice2();

// プレイヤー情報初期化
void InitAlice();
void InitAlice2();

// アリスを動けなくする
void freezeAlice();
void freezeAlice2();

// アリスを動かせるようにする
void releaseAlice();
void releaseAlice2();

// プレイヤー操作
void ControllAlice();
void ControllAlice2();

// 当たり判定を行うか？
// 返値：
//   1 = 行う
//   0 = 行わない
int IsHitProcessPlayer();
int IsHitProcessPlayer2();

// プレイヤー描画
void DrawAlice();
void DrawAlice2();
