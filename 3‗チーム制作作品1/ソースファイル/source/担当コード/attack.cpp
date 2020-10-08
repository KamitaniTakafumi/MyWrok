#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"alice.h"
#include	"attack.h"
#include	"camera.h"
#include	"HitJudgment.h"
#include	"Item.h"

// 画像データ
int cgAttackEffL;		// 何枚かのアニメになる予定
int cgAttackEffR;		
int cgAttackEffUp;		
int cgAttackEffDown;	
int cgItemAttackEffL;
int cgItemAttackEffR;
int cgItemAttackEffUp;
int cgItemAttackEffDown;

// 攻撃情報
struct ATTACK atk;
struct ATTACKITEM atkit;

// グローバル変数
int attackCooltime;		// 攻撃のクールタイム

// 画像読み込み
void LoadAttackEff() {
	cgAttackEffL = LoadTexture("res/attackeffL.png");
	cgAttackEffR = LoadTexture("res/attackeffR.png");
	cgAttackEffUp = LoadTexture("res/attackeffUp.png");
	cgAttackEffDown = LoadTexture("res/attackeffDown.png");
	cgItemAttackEffL = LoadTexture("res/itematkeffleft.png");
	cgItemAttackEffR = LoadTexture("res/itematkeffright.png");
	cgItemAttackEffUp = LoadTexture("res/itematkeffup.png");
	cgItemAttackEffDown = LoadTexture("res/itematkeffdown.png");
}

// 攻撃の初期化
void InitAttack() {
	atk.use = 0;
}

// アリスが攻撃を行った
void playerAttack() {
	if (atk.use == 0) {
		// 使ってないのでここで使う
		atk.use = 1;
		attackCooltime = 30;	// クールタイムの長さ(60 flames = 1秒)
		if ((al.state == ALICE_STATE_ATTACK_LEFT) || (al.state == ALICE_STATE_ATTACK_RIGHT)) {
			atk.w = 40;
			atk.h = 120;
		}
		if ((al.state == ALICE_STATE_ATTACK_UP) || (al.state == ALICE_STATE_ATTACK_DOWN)) {
			atk.w = 120;
			atk.h = 40;
		}
		// 攻撃情報の初期化
		if (al.state == ALICE_STATE_ATTACK_LEFT) {
			atk.x = al.x - atk.w;
			atk.y = al.y - (atk.h / 6);
			atk.hit_x = 8;
			atk.hit_y = 8;
			atk.hit_w = 24;
			atk.hit_h = 104;
		}
		if(al.state == ALICE_STATE_ATTACK_RIGHT) {
			atk.x = al.x + atk.w;
			atk.y = al.y - (atk.h / 6);
			atk.hit_x = 8;
			atk.hit_y = 8;
			atk.hit_w = 24;
			atk.hit_h = 104;
		}
		if(al.state == ALICE_STATE_ATTACK_UP) {
			atk.x = al.x - (atk.w / 3);
			atk.y = al.y - atk.h;
			atk.hit_x = 8;
			atk.hit_y = 8;
			atk.hit_w = 104;
			atk.hit_h = 24;
		}
		if(al.state == ALICE_STATE_ATTACK_DOWN) {
			atk.x = al.x - (atk.w / 3);
			atk.y = al.y + al.h;
			atk.hit_x = 8;
			atk.hit_y = 8;
			atk.hit_w = 104;
			atk.hit_h = 24;
		}
		PlayMemBack(seAliceAttack);
	}

}
/*
void PlayerItemAttack() {
	if (atkit.use == 0) {
		// 使ってないのでここで使う
		atkit.use = 1;
		attackCooltime = 30;	// クールタイムの長さ(60 flames = 1秒)

		item->number--;
		if ((al.state == ALICE_STATE_ITEM_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) || (al.state == ALICE_STATE_ITEM_ATTACK_UP) || (al.state == ALICE_STATE_ITEM_ATTACK_DOWN)) {
			atkit.w = 160;
			atkit.h = 160;
		}
		// 攻撃情報の初期化
		if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
			atkit.x = al.x - atkit.w;
			atkit.y = al.y;
			atkit.hit_x = 0;
			atkit.hit_y = 0;
			atkit.hit_w = 120;
			atkit.hit_h = 120;
		}
		if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
			atkit.x = al.x + atkit.w;
			atkit.y = al.y;
			atkit.hit_x = 0;
			atkit.hit_y = 0;
			atkit.hit_w = 120;
			atkit.hit_h = 120;
		}
		if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
			atkit.x = al.x - (atkit.w / 3);
			atkit.y = al.y - atkit.h;
			atkit.hit_x = 0;
			atkit.hit_y = 0;
			atkit.hit_w = 120;
			atkit.hit_h = 120;
		}
		if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
			atkit.x = al.x - (atkit.w / 3);
			atkit.y = al.y + (atkit.h / 3 * 6);
			atkit.hit_x = 0;
			atkit.hit_y = 0;
			atkit.hit_w = 120;
			atkit.hit_h = 120;
		}
		PlayMemBack(seAliceAttack);
	}

}
*/

// 攻撃のクールタイムを減らす
void AttackCooltime() {
	if ((atk.use == 1) || (atkit.use == 1)) {
		attackCooltime --;
		if (attackCooltime < 0) {

			if((al.state == ALICE_STATE_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_LEFT)) {
				al.state = ALICE_STATE_LEFT;
			}
			if((al.state == ALICE_STATE_ATTACK_RIGHT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT)) {
				al.state = ALICE_STATE_RIGHT;
			}
			if((al.state == ALICE_STATE_ATTACK_UP) || (al.state == ALICE_STATE_ITEM_ATTACK_UP)) {
				al.state = ALICE_STATE_UP;
			}
			if((al.state == ALICE_STATE_ATTACK_DOWN) || (al.state == ALICE_STATE_ITEM_ATTACK_DOWN)) {
				al.state = ALICE_STATE_DOWN;
			}
			atk.x = 0;
			atk.y = 0;
			atk.hit_x = 0;
			atk.hit_y = 0;
			atk.hit_w = 0;
			atk.hit_h = 0;

			atkit.x = 0;
			atkit.y = 0;
			atkit.hit_x = 0;
			atkit.hit_y = 0;
			atkit.hit_w = 0;
			atkit.hit_h = 0;

			attackCooltime = 0;
			atk.use = 0;
		}
	}
}

// 攻撃エフェクトの描画
void DrawAtkEff() {
	if (atk.use == 1) {
		if (al.state == ALICE_STATE_ATTACK_LEFT) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgAttackEffL);
		}
		if(al.state == ALICE_STATE_ATTACK_RIGHT) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgAttackEffR);
		}
		if(al.state == ALICE_STATE_ATTACK_UP) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgAttackEffUp);
		}
		if(al.state == ALICE_STATE_ATTACK_DOWN) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgAttackEffDown);
		}
	}/*
	if (atkit.use == 1) {
		if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgItemAttackEffL);
		}
		if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgItemAttackEffR);
		}
		if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgItemAttackEffUp);
		}
		if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
			DrawMemTh(atk.x - cv.view_x, atk.y - cv.view_y, cgItemAttackEffDown);
		}
	}*/
}