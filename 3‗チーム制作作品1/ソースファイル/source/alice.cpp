#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include    "global.h"   
#include    "alice.h"
#include	"aliceattack.h"
#include	"mapdata_1.h"
#include	"mapdata_2.h"
#include	"HitJudgment.h"
#include	"camera.h"
#include	"Item.h"
#include	"UI.h"
#include	"enemy.h"
#include	"changeroom.h"


// アリスが止まっている画像
int cgAliceIdleUp;
int cgAliceIdleDown;
int cgAliceIdleLeft;
int cgAliceIdleRight;

// アリスが歩く画像
int cgAliceUp[4];			// アリス上向き
int cgAliceDown[4];		// アリス下向き
int cgAliceLeft[4];		// アリス左向き
int cgAliceRight[4];		// アリス右向き

// アリスが攻撃している画像
int cgAliceAttackUp[6];
int cgAliceAttackDown[6];
int cgAliceAttackLeft[6];
int cgAliceAttackRight[6];

// 
int cgAliceDeathL[2];
int cgAliceDeathR[2];
int cgAliceDeathU[2];
int cgAliceDeathD[2];

// プレイヤー情報
struct ALICE al;

// グローバル変数
int imagetime;
int alice_freeze;

// 画像読み込み
void LoadCgAlice()
{
	// State = Idle
	cgAliceIdleUp = LoadTexture("res/aliceidleup.png");
	cgAliceIdleDown = LoadTexture("res/aliceidledown.png");
	cgAliceIdleLeft = LoadTexture("res/aliceidleleft.png");
	cgAliceIdleRight = LoadTexture("res/aliceidleright.png");

	// State = Walk
	cgAliceUp[0] = LoadTexture("res/alicewalkup_l.png");
	cgAliceUp[1] = LoadTexture("res/aliceidleup.png");
	cgAliceUp[2] = LoadTexture("res/alicewalkup_r.png");
	cgAliceUp[3] = LoadTexture("res/aliceidleup.png");

	cgAliceDown[0] = LoadTexture("res/alicewalkdown_l.png");
	cgAliceDown[1] = LoadTexture("res/aliceidledown.png");
	cgAliceDown[2] = LoadTexture("res/alicewalkdown_r.png");
	cgAliceDown[3] = LoadTexture("res/aliceidledown.png");

	cgAliceLeft[0] = LoadTexture("res/alicewalkleft_l.png");
	cgAliceLeft[1] = LoadTexture("res/aliceidleleft.png");
	cgAliceLeft[2] = LoadTexture("res/alicewalkleft_r.png");
	cgAliceLeft[3] = LoadTexture("res/aliceidleleft.png");

	cgAliceRight[0] = LoadTexture("res/alicewalkright_l.png");
	cgAliceRight[1] = LoadTexture("res/aliceidleright.png");
	cgAliceRight[2] = LoadTexture("res/alicewalkright_r.png");
	cgAliceRight[3] = LoadTexture("res/aliceidleright.png");

	// State = attack
	cgAliceAttackUp[0] = LoadTexture("res/aliceattackup.png");
	cgAliceAttackUp[1] = LoadTexture("res/aliceattackup_2.png");
	cgAliceAttackUp[2] = LoadTexture("res/aliceattackup_3.png");
	cgAliceAttackUp[3] = LoadTexture("res/aliceattackup_3_2.png");
	cgAliceAttackUp[4] = LoadTexture("res/aliceattackup_3_3.png");
	cgAliceAttackUp[5] = LoadTexture("res/aliceattackup_3_4.png");

	cgAliceAttackDown[0] = LoadTexture("res/aliceattackdown.png");
	cgAliceAttackDown[1] = LoadTexture("res/aliceattackdown_2.png");
	cgAliceAttackDown[2] = LoadTexture("res/aliceattackdown_3.png");
	cgAliceAttackDown[3] = LoadTexture("res/aliceattackdown_3_2.png");
	cgAliceAttackDown[4] = LoadTexture("res/aliceattackdown_3_3.png");
	cgAliceAttackDown[5] = LoadTexture("res/aliceattackdown_3_4.png");

	cgAliceAttackLeft[0] = LoadTexture("res/aliceattackleft.png");
	cgAliceAttackLeft[1] = LoadTexture("res/aliceattackleft_2.png");
	cgAliceAttackLeft[2] = LoadTexture("res/aliceattackleft_3.png");
	cgAliceAttackLeft[3] = LoadTexture("res/aliceattackleft_3_2.png");
	cgAliceAttackLeft[4] = LoadTexture("res/aliceattackleft_3_3.png");
	cgAliceAttackLeft[5] = LoadTexture("res/aliceattackleft_3_4.png");

	cgAliceAttackRight[0] = LoadTexture("res/aliceattackright.png");
	cgAliceAttackRight[1] = LoadTexture("res/aliceattackright_2.png");
	cgAliceAttackRight[2] = LoadTexture("res/aliceattackright_3.png");
	cgAliceAttackRight[3] = LoadTexture("res/aliceattackright_3_2.png");
	cgAliceAttackRight[4] = LoadTexture("res/aliceattackright_3_3.png");
	cgAliceAttackRight[5] = LoadTexture("res/aliceattackright_3_4.png");

	cgAliceDeathL[0] = LoadTexture("res/aliceidleleft.png");
	cgAliceDeathL[1] = LoadTexture("res/alicedeath.png");

	cgAliceDeathR[0] = LoadTexture("res/aliceidleright.png");
	cgAliceDeathR[1] = LoadTexture("res/alicedeath.png");

	cgAliceDeathD[0] = LoadTexture("res/aliceidledown.png");
	cgAliceDeathD[1] = LoadTexture("res/alicedeath.png");

	cgAliceDeathU[0] = LoadTexture("res/aliceidleup.png");
	cgAliceDeathU[1] = LoadTexture("res/alicedeath.png");
}

// プレイヤー情報初期化
void InitAlice()
{
	imagetime = 0;
	alice_freeze = 0;
	al.use = 1;
	al.w = 40;
	al.h = 80;
	switch (stateStage) {
	case STATE_EP1STAGE:
		al.x = 200;
		al.y = 1200;
		break;
	case STATE_EP1STAGE_2:
		al.x = 2320;	// ステージ２初期位置
		al.y = 40 * 50;	// ステージ２初期位置
		break;
	case STATE_EP1STAGE_3:
		if (bgstage == STATE_EP1STAGE_3) {
			al.x = 1400;	// ステージ３初期位置
			al.y = 2320;	// ステージ３初期位置
		}
		else {
			al.x = 160;		// ボスステージ手前
			al.y = 80;		// ボスステージ手前
		}
		break;
	case STATE_EP1STAGE_4:
		al.x = 720;
		al.y = 1040;
		break;
	}
	//al.x = 2040;		// 調合窯の横(開発用)
	//al.y = 960;			// 調合窯の横(開発用)
	al.spd = 5;
	al.state = ALICE_STATE_IDLE_DOWN;
	al.hit_x = 4;
	al.hit_y = 44;
	al.hit_w = 32;
	al.hit_h = 32;
	al.hitpoint = 6;
	//al.hitpoint = 100;		// 死なないように(開発用)
	al.nohit_cnt = 0;
}

void freezeAlice() {
	// アリスを動けなくする
	alice_freeze = 1;
}

void releaseAlice() {
	// アリスを動けるようにする
	alice_freeze = 0;
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int CheckHitMapChipAlice(int x, int y)
{
	if (stateStage == STATE_EP1STAGE) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE_W && 0 <= y && y < MAPSIZE_H) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap[y *MAPSIZE_W + x];

			// 当たるIDかどうかをチェック
			int idtable[] =
			{
				103,-1		// 最後
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
int CheckHitMapChipAlice2(int x, int y) {
	if (stateStage == STATE_EP1STAGE_2) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE_W_2 && 0 <= y && y < MAPSIZE_H_2) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap2[y *MAPSIZE_W_2 + x];
			int chip_no2 = nMap2lm[y *MAPSIZE_W_2 + x];

			if (required_count < 2) {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					102,251,-1		// 最後
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
					251,-1		// 最後
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
int CheckHitMapChipAlice3(int x, int y) {
	if (stateStage == STATE_EP1STAGE_3) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE_W_3 && 0 <= y && y < MAPSIZE_H_3) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap3[y *MAPSIZE_W_3 + x];
			int chip_no2 = nMap3lm[y *MAPSIZE_W_3 + x];

			if (required_count < 4) {
				// 当たるIDかどうかをチェック
				int idtable[] =
				{
					101,102,-1		// 最後
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
int CheckHitMapChipAlice4(int x, int y) {
	if (stateStage == STATE_EP1STAGE_4) {
		// マップチップ位置はマップデータからはみ出ているか？
		if (0 <= x && x < MAPSIZE_W_4 && 0 <= y && y < MAPSIZE_H_4) {	// はみでていない

			// マップチップIDが0以外は当たり判定を行う
			// 現在、レイヤーは考慮されていない
			int chip_no = nMap4[y *MAPSIZE_W_4 + x];

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
int IsHitMapChipAlice(int i, int mx, int my)
{
	if (stateStage == STATE_EP1STAGE) {
		int x, y;

		// キャラ矩形を作成する
		int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)は、マップチップの座標（チップ単位）
				// この位置のチップは当たるか？
				int chip_no = CheckHitMapChipAlice(x, y);
				if (chip_no != 0) {	// このチップと当たった。
					// X,Yの移動方向を見て、その反対方向に補正する
					if (mx < 0) {	// 左に動いていたので、右に補正
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// 右に動いていたので、左に補正
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// 下に動いていたので、上に補正
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// 上に動いていたので、下に補正
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// 当たったので戻る
					return 1;
				}
			}
		}

		// 当たらなかった
		return 0;
	}
}

int IsHitMapChipAlice2(int i, int mx, int my) {
	if (stateStage == STATE_EP1STAGE_2) {
		int x, y;

		// キャラ矩形を作成する
		int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)は、マップチップの座標（チップ単位）
				// この位置のチップは当たるか？
				int chip_no2 = CheckHitMapChipAlice2(x, y);
				if (chip_no2 != 0) {	// このチップと当たった。
					// X,Yの移動方向を見て、その反対方向に補正する
					if (mx < 0) {	// 左に動いていたので、右に補正
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// 右に動いていたので、左に補正
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// 下に動いていたので、上に補正
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// 上に動いていたので、下に補正
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// 当たったので戻る
					return 1;
				}
			}
		}

		// 当たらなかった
		return 0;
	}
}

int IsHitMapChipAlice3(int i, int mx, int my) {
	if (stateStage == STATE_EP1STAGE_3) {
		int x, y;

		// キャラ矩形を作成する
		int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)は、マップチップの座標（チップ単位）
				// この位置のチップは当たるか？
				int chip_no3 = CheckHitMapChipAlice3(x, y);
				if (chip_no3 != 0) {	// このチップと当たった。
					// X,Yの移動方向を見て、その反対方向に補正する
					if (mx < 0) {	// 左に動いていたので、右に補正
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// 右に動いていたので、左に補正
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// 下に動いていたので、上に補正
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// 上に動いていたので、下に補正
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// 当たったので戻る
					return 1;
				}
			}
		}

		// 当たらなかった
		return 0;
	}
}

int IsHitMapChipAlice4(int i, int mx, int my) {
	if (stateStage == STATE_EP1STAGE_4) {
		int x, y;

		// キャラ矩形を作成する
		int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)は、マップチップの座標（チップ単位）
				// この位置のチップは当たるか？
				int chip_no4 = CheckHitMapChipAlice4(x, y);
				if (chip_no4 != 0) {	// このチップと当たった。
					// X,Yの移動方向を見て、その反対方向に補正する
					if (mx < 0) {	// 左に動いていたので、右に補正
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// 右に動いていたので、左に補正
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// 下に動いていたので、上に補正
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// 上に動いていたので、下に補正
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// 当たったので戻る
					return 1;
				}
			}
		}

		// 当たらなかった
		return 0;
	}
}

// アリス操作
void ControllAlice()
{
	int keyflag = 0;
	int i = 0;
	int j;

	// 主人公使用中でなければ処理しない
	if (al.use == 0) { return; }

	if ((selectTrg == STATE_NONE) & (check == STATE_NONE)) {
		if (alice_freeze == 0) {
		// キー入力を判定して、主人公を移動させる
	// 上下左右のみなので斜め移動しないようにフラグで規制させてる
			if ((al.state == ALICE_STATE_IDLE_UP) ||
				(al.state == ALICE_STATE_IDLE_DOWN) ||
				(al.state == ALICE_STATE_IDLE_RIGHT) ||
				(al.state == ALICE_STATE_IDLE_LEFT) ||
				(al.state == ALICE_STATE_UP) ||
				(al.state == ALICE_STATE_DOWN) ||
				(al.state == ALICE_STATE_RIGHT) ||
				(al.state == ALICE_STATE_LEFT)) {
				// 左に移動
				if (gKey & KEYIN_LEFT) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_LEFT;
						al.x -= al.spd;
						IsHitMapChipAlice(i, -1, 0);
						IsHitMapChipAlice2(i, -1, 0);
						IsHitMapChipAlice3(i, -1, 0);
						IsHitMapChipAlice4(i, -1, 0);
						keyflag += 1;
						imagetime += 1;
					}
				}
				// 右に移動
				if (gKey & KEYIN_RIGHT) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_RIGHT;
						al.x += al.spd;
						IsHitMapChipAlice(i, 1, 0);
						IsHitMapChipAlice2(i, 1, 0);
						IsHitMapChipAlice3(i, 1, 0);
						IsHitMapChipAlice4(i, 1, 0);
						keyflag += 1;
						imagetime += 1;
					}
				}
				// 上に移動
				if (gKey & KEYIN_UP) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_UP;
						al.y -= al.spd;
						IsHitMapChipAlice(i, 0, -1);
						IsHitMapChipAlice2(i, 0, -1);
						IsHitMapChipAlice3(i, 0, -1);
						IsHitMapChipAlice4(i, 0, -1);
						keyflag += 1;
						imagetime += 1;
					}
				}
				// 下に移動
				if (gKey & KEYIN_DOWN) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_DOWN;
						al.y += al.spd;
						IsHitMapChipAlice(i, 0, 1);
						IsHitMapChipAlice2(i, 0, 1);
						IsHitMapChipAlice3(i, 0, 1);
						IsHitMapChipAlice4(i, 0, 1);
						keyflag += 1;
						imagetime += 1;
					}
				}

				if (imagetime == 1) {
					PlayMemLoop(seWalk1);
				}

				// アリスが止まっているとき止まった状態にする
				if (!(gKey & KEYIN_UP) && (!(gKey & KEYIN_DOWN)) && (!(gKey & KEYIN_RIGHT)) && (!(gKey & KEYIN_LEFT))) {
					if (al.state == ALICE_STATE_UP) {
						al.state = ALICE_STATE_IDLE_UP;
						imagetime = 0;
					}
					if (al.state == ALICE_STATE_DOWN) {
						al.state = ALICE_STATE_IDLE_DOWN;
						imagetime = 0;
					}
					if (al.state == ALICE_STATE_LEFT) {
						al.state = ALICE_STATE_IDLE_LEFT;
						imagetime = 0;
					}
					if (al.state == ALICE_STATE_RIGHT) {
						al.state = ALICE_STATE_IDLE_RIGHT;
						imagetime = 0;
					}
					StopPlayMem(seWalk1);
				}
			}

			// 1以上の時フラグをリセット
			if (keyflag > 0) {
				keyflag = 0;
			}

			// 物理攻撃
		// キーを押したときにその方向に攻撃させる
		// 連続して使えないようにクールタイムを設定させる
		// また攻撃中は動けないようにする
			if ((IsHitPlayerAttackPreparation() == 0) & (IsHitPlayerAttackObject() == 0) & (IsHitPlayerAttackDrop() == 0)) {
				if (gTrg & KEYIN_X) {
					if ((al.state == ALICE_STATE_IDLE_UP) ||
						(al.state == ALICE_STATE_IDLE_DOWN) ||
						(al.state == ALICE_STATE_IDLE_RIGHT) ||
						(al.state == ALICE_STATE_IDLE_LEFT) ||
						(al.state == ALICE_STATE_UP) ||
						(al.state == ALICE_STATE_DOWN) ||
						(al.state == ALICE_STATE_RIGHT) ||
						(al.state == ALICE_STATE_LEFT)) {

						if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP)) {
							al.state = ALICE_STATE_ATTACK_UP;
						}
						if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN)) {
							al.state = ALICE_STATE_ATTACK_DOWN;
						}
						if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT)) {
							al.state = ALICE_STATE_ATTACK_RIGHT;
						}
						if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT)) {
							al.state = ALICE_STATE_ATTACK_LEFT;
						}
						playerAttack();
					}
				}
			}

			// アイテム攻撃
			if (frm[2].move == 0) {
				for (j = 0; j < 6; j++) {
					if ((useit[j].use == 1) & (frm[2].x == useit[j].x - 10)) {
						if (gTrg & KEYIN_A) {
							if ((al.state == ALICE_STATE_IDLE_UP) ||
								(al.state == ALICE_STATE_IDLE_DOWN) ||
								(al.state == ALICE_STATE_IDLE_RIGHT) ||
								(al.state == ALICE_STATE_IDLE_LEFT) ||
								(al.state == ALICE_STATE_UP) ||
								(al.state == ALICE_STATE_DOWN) ||
								(al.state == ALICE_STATE_RIGHT) ||
								(al.state == ALICE_STATE_LEFT)) {

								if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP)) {
									al.state = ALICE_STATE_ITEM_ATTACK_UP;
								}
								if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN)) {
									al.state = ALICE_STATE_ITEM_ATTACK_DOWN;
								}
								if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_RIGHT;
								}
								if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_LEFT;
								}
								PlayerItemAttack(j);
							}
						}
					}
				}
			}
			else if (frm[2].move == 1) {
				for (j = 6; j < 9; j++) {
					if ((useit[j].use == 1) & (frm[2].x == useit[j].x - 10)) {
						if (gTrg & KEYIN_A) {
							if ((al.state == ALICE_STATE_IDLE_UP) ||
								(al.state == ALICE_STATE_IDLE_DOWN) ||
								(al.state == ALICE_STATE_IDLE_RIGHT) ||
								(al.state == ALICE_STATE_IDLE_LEFT) ||
								(al.state == ALICE_STATE_UP) ||
								(al.state == ALICE_STATE_DOWN) ||
								(al.state == ALICE_STATE_RIGHT) ||
								(al.state == ALICE_STATE_LEFT)) {

								if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP)) {
									al.state = ALICE_STATE_ITEM_ATTACK_UP;
								}
								if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN)) {
									al.state = ALICE_STATE_ITEM_ATTACK_DOWN;
								}
								if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_RIGHT;
								}
								if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_LEFT;
								}
								PlayerItemAttack(j);
							}
						}
					}
				}
			}
		}
		// 画面の外に出ないようにする
		if (stateStage == STATE_EP1STAGE) {
			if (al.y + al.h > 40 * 35) { al.y = 40 * 35 - al.h; }
		}
		else if (stateStage == STATE_EP1STAGE_4) {
			if (al.y + al.h > 40 * 27) { al.y = 40 * 27 - al.h; }
		}

		// 画面を切り替える
		changeroom();

		// 無敵カウンタの処理
		if (al.nohit_cnt > 0) {
			al.nohit_cnt--;
		}
	}
}

// 当たり判定を行うか？
// 返値：
//   1 = 行う
//   0 = 行わない
int IsHitProcessPlayer()
{
	if (al.use == 0) { return 0; }
	if (al.nohit_cnt > 0) { return 0; }
	return 1;
}

// アリスの描画
void DrawAlice()
{
	// 主人公使用中でなければ処理しない
	if (al.use == 0) {
		if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT) || (al.state == ALICE_STATE_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) || (al.state == ALICE_STATE_GATHERING_LEFT)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathL[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathL[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathL[1]);
			}
		}
		if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT) || (al.state == ALICE_STATE_ATTACK_RIGHT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) || (al.state == ALICE_STATE_GATHERING_RIGHT)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathR[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathR[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathR[1]);
			}
		}
		if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP) || (al.state == ALICE_STATE_ATTACK_UP) || (al.state == ALICE_STATE_ITEM_ATTACK_UP) || (al.state == ALICE_STATE_GATHERING_UP)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathU[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathU[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathU[1]);
			}
		}
		if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN) || (al.state == ALICE_STATE_ATTACK_DOWN) || (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) || (al.state == ALICE_STATE_GATHERING_DOWN)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathD[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathD[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathD[1]);
			}
		}
	}

	if (al.use == 1) {
		// 無敵中は一定間隔で描画しない
		if (al.nohit_cnt == 0 || (al.nohit_cnt % 10) < 7)
		{
			if (al.state == ALICE_STATE_IDLE_UP) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleUp);
			}
			if (al.state == ALICE_STATE_IDLE_DOWN) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleDown);
			}
			if (al.state == ALICE_STATE_IDLE_LEFT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleLeft);
			}
			if (al.state == ALICE_STATE_IDLE_RIGHT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleRight);
			}

			if ((al.state == ALICE_STATE_UP) || (al.state == ALICE_STATE_GATHERING_UP)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceUp[(imagetime / 8) % 4]);
			}
			if ((al.state == ALICE_STATE_DOWN) || (al.state == ALICE_STATE_GATHERING_DOWN)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDown[(imagetime / 8) % 4]);
			}
			if ((al.state == ALICE_STATE_LEFT) || (al.state == ALICE_STATE_GATHERING_LEFT)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceLeft[(imagetime / 8) % 4]);
			}
			if ((al.state == ALICE_STATE_RIGHT) || (al.state == ALICE_STATE_GATHERING_RIGHT)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceRight[(imagetime / 8) % 4]);
			}

			if (al.state == ALICE_STATE_ATTACK_UP) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackUp[(attackCooltime / 5) % 6]);
			}
			if (al.state == ALICE_STATE_ATTACK_DOWN) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackDown[(attackCooltime / 5) % 6]);
			}
			if (al.state == ALICE_STATE_ATTACK_LEFT) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackLeft[(attackCooltime / 5) % 6]);
			}
			if (al.state == ALICE_STATE_ATTACK_RIGHT) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackRight[(attackCooltime / 5) % 6]);
			}

			if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleUp);
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleDown);
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleLeft);
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleRight);
			}
		}
	}
}
