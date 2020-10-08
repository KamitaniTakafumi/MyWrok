#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"camera.h"
#include	"HitJudgment.h"
#include	"Item.h"
#include	"game_effect.h"

// 画像データ	
int cgAliceAttackJudgment_1;
int cgAliceAttackJudgment_2;

// 攻撃情報
struct ATTACK atk;
struct ATTACKITEM atkit;

// グローバル変数
int attackCooltime;		// 攻撃のクールタイム

// 画像読み込み
void LoadAttackEff() {
	cgAliceAttackJudgment_1 = LoadTexture("res/AliceAttackJudgment_1.png");
	cgAliceAttackJudgment_2 = LoadTexture("res/AliceAttackJudgment_2.png");
}

// 攻撃の初期化
void InitAttack() {
	atk.use = 0;
	atkit.use = 0;
}

// アリスが攻撃を行った
void playerAttack() {
	if (atk.use == 0) {
		// 使ってないのでここで使う
		atk.use = 1;
		attackCooltime = 0;	// クールタイムの長さ(60 flames = 1秒)
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
			atk.hit_x = 0;
			atk.hit_y = 0;
			atk.hit_w = 40;
			atk.hit_h = 120;
		}
		if(al.state == ALICE_STATE_ATTACK_RIGHT) {
			atk.x = al.x + atk.w;
			atk.y = al.y - (atk.h / 6);
			atk.hit_x = 0;
			atk.hit_y = 0;
			atk.hit_w = 40;
			atk.hit_h = 120;
		}
		if(al.state == ALICE_STATE_ATTACK_UP) {
			atk.x = al.x - (atk.w / 3);
			atk.y = al.y;
			atk.hit_x = 0;
			atk.hit_y = 0;
			atk.hit_w = 120;
			atk.hit_h = 40;
		}
		if(al.state == ALICE_STATE_ATTACK_DOWN) {
			atk.x = al.x - (atk.w / 3);
			atk.y = al.y + al.h;
			atk.hit_x = 0;
			atk.hit_y = 0;
			atk.hit_w = 120;
			atk.hit_h = 40;
		}
		PlayMemBack(seAliceAttack);
	}

}

// プレイヤーがアイテム攻撃を行った
void PlayerItemAttack(int useitId) {
	if (atkit.use == 0) {
		// 使ってないのでここで使う
		atkit.use = 1;
		attackCooltime = 0;	// クールタイムの長さ(60 flames = 1秒)
		
		if ((useit[useitId].cg == item[0].cg) || (useit[useitId].cg == item[1].cg) || (useit[useitId].cg == item[2].cg) || (useit[useitId].cg == item[3].cg)
			|| (useit[useitId].cg == item[10].cg) || (useit[useitId].cg == item[11].cg) || (useit[useitId].cg == item[12].cg)) {
			if (useit[useitId].cg == item[0].cg) {
				atkit.item_no = 0;
			}
			else if (useit[useitId].cg == item[1].cg) {
				atkit.item_no = 1;
			}
			else if (useit[useitId].cg == item[2].cg) {
				atkit.item_no = 2;
			}
			else if (useit[useitId].cg == item[3].cg) {
				atkit.item_no = 3;
			}
			else if (useit[useitId].cg == item[10].cg) {
				atkit.item_no = 10;
			}
			else if (useit[useitId].cg == item[11].cg) {
				atkit.item_no = 11;
			}
			else if (useit[useitId].cg == item[12].cg) {
				atkit.item_no = 12;
			}
			if ((al.state == ALICE_STATE_ITEM_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) || (al.state == ALICE_STATE_ITEM_ATTACK_UP) || (al.state == ALICE_STATE_ITEM_ATTACK_DOWN)) {
				atkit.w = 160;
				atkit.h = 160;
			}
			// 攻撃情報の初期化
			if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
				atkit.x = al.x - atkit.w;
				atkit.y = al.y;
				atkit.hit_x = 5;
				atkit.hit_y = 5;
				atkit.hit_w = 110;
				atkit.hit_h = 110;
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
				atkit.x = al.x + (atkit.w / 2);
				atkit.y = al.y;
				atkit.hit_x = 5;
				atkit.hit_y = 5;
				atkit.hit_w = 110;
				atkit.hit_h = 110;
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
				atkit.x = al.x - (atkit.w / 4);
				atkit.y = al.y - atkit.h;
				atkit.hit_x = 5;
				atkit.hit_y = 5;
				atkit.hit_w = 110;
				atkit.hit_h = 110;
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
				atkit.x = al.x - (atkit.w / 4);
				atkit.y = al.y + (atkit.h / 4 * 3);
				atkit.hit_x = 5;
				atkit.hit_y = 5;
				atkit.hit_w = 110;
				atkit.hit_h = 110;
			}
			PutEffect(EFFECTTYPE_ITEM_ATTACK, atkit.x, atkit.y, atkit.item_no);
		}
		else if (useit[useitId].cg == item[4].cg) {
			atkit.item_no = 4;
			atkit.x = al.x;
			atkit.y = al.y;
			if (al.hitpoint >= 6) {
				al.hitpoint += 0;
			}
			else if (al.hitpoint <= 5) {
				al.hitpoint += 1;
			}
			PutEffect(EFFECTTYPE_ITEM_ATTACK, atkit.x, atkit.y, atkit.item_no);
			PlayMemBack(seRecovery);
		}
		else if ((useit[useitId].cg == item[6].cg) || (useit[useitId].cg == item[7].cg) || (useit[useitId].cg == item[8].cg) || (useit[useitId].cg == item[9].cg)
			|| (useit[useitId].cg == item[14].cg) || (useit[useitId].cg == item[15].cg) || (useit[useitId].cg == item[16].cg)) {
			if (useit[useitId].cg == item[6].cg) {
				atkit.item_no = 6;
			}
			else if (useit[useitId].cg == item[7].cg) {
				atkit.item_no = 7;
			}
			else if (useit[useitId].cg == item[8].cg) {
				atkit.item_no = 8;
			}
			else if (useit[useitId].cg == item[9].cg) {
				atkit.item_no = 9;
			}
			else if (useit[useitId].cg == item[14].cg) {
				atkit.item_no = 14;
			}
			else if (useit[useitId].cg == item[15].cg) {
				atkit.item_no = 15;
			}
			else if (useit[useitId].cg == item[16].cg) {
				atkit.item_no = 16;
			}
			if ((al.state == ALICE_STATE_ITEM_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT)) {
				atkit.w = 200;
				atkit.h = 40;
			}
			else {
				atkit.w = 40;
				atkit.h = 200;
			}
			// 攻撃情報の初期化
			if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
				atkit.x = al.x - atkit.w;
				atkit.y = al.y + atkit.h;
				atkit.hit_x = 0;
				atkit.hit_y = 0;
				atkit.hit_w = 200;
				atkit.hit_h = 40;
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
				atkit.x = al.x + (atkit.w / 5);
				atkit.y = al.y + atkit.h;
				atkit.hit_x = 0;
				atkit.hit_y = 0;
				atkit.hit_w = 200;
				atkit.hit_h = 40;
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
				atkit.x = al.x;
				atkit.y = al.y - atkit.h;
				atkit.hit_x = 0;
				atkit.hit_y = 0;
				atkit.hit_w = 40;
				atkit.hit_h = 200;
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
				atkit.x = al.x;
				atkit.y = al.y + (atkit.h / 5 * 2);
				atkit.hit_x = 0;
				atkit.hit_y = 0;
				atkit.hit_w = 40;
				atkit.hit_h = 200;
			}
			PutEffect(EFFECTTYPE_ITEM_ATTACK, atkit.x, atkit.y, atkit.item_no);
			PlayMemBack(seAliceAttack);
		}
		else if (useit[useitId].cg == item[5].cg) {
		atkit.item_no = 5;
		atkit.x = al.x;
		atkit.y = al.y;
		if (al.hitpoint >= 6) {
			al.hitpoint += 0;
		}
		else if (al.hitpoint >= 5) {
			al.hitpoint += 1;
		}
		else if (al.hitpoint >= 4) {
			al.hitpoint += 2;
		}
		else if (al.hitpoint <= 3) {
			al.hitpoint += 3;
		}
		PutEffect(EFFECTTYPE_ITEM_ATTACK, atkit.x, atkit.y, atkit.item_no);
		PlayMemBack(seRecovery);
		}
		else if (useit[useitId].cg == item[13].cg) {
		atkit.item_no = 13;
		atkit.x = al.x;
		atkit.y = al.y;
		if (al.hitpoint >= 6) {
			al.hitpoint += 0;
		}
		else if (al.hitpoint >= 5) {
			al.hitpoint += 1;
		}
		else if (al.hitpoint >= 4) {
			al.hitpoint += 2;
		}
		else if (al.hitpoint >= 3) {
			al.hitpoint += 3;
		}
		else if (al.hitpoint >= 2) {
			al.hitpoint += 4;
		}
		else if (al.hitpoint <= 1) {
			al.hitpoint += 5;
		}
		PutEffect(EFFECTTYPE_ITEM_ATTACK, atkit.x, atkit.y, atkit.item_no);
		PlayMemBack(seRecovery);
		}

		useit[useitId].number--;
		if (useit[useitId].cg == item[0].cg) {
			item[0].number--;
		}
		else if (useit[useitId].cg == item[4].cg) {
			item[4].number--;
		}
		else if (useit[useitId].cg == item[5].cg) {
			item[5].number--;
		}
		else if (useit[useitId].cg == item[6].cg) {
			item[6].number--;
		}
		if (useit[useitId].number <= 0) {
			useit[useitId].use = 0;
			useit[useitId].cg = 0;
		}
	}

}

// 攻撃のクールタイムを減らす
void AttackCooltime() {
	if ((atk.use == 1) || (atkit.use == 1)) {
		attackCooltime++;
		if (attackCooltime > 30) {
			if((al.state == ALICE_STATE_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_LEFT)) {
				al.state = ALICE_STATE_IDLE_LEFT;
			}
			if((al.state == ALICE_STATE_ATTACK_RIGHT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT)) {
				al.state = ALICE_STATE_IDLE_RIGHT;
			}
			if((al.state == ALICE_STATE_ATTACK_UP) || (al.state == ALICE_STATE_ITEM_ATTACK_UP)) {
				al.state = ALICE_STATE_IDLE_UP;
			}
			if((al.state == ALICE_STATE_ATTACK_DOWN) || (al.state == ALICE_STATE_ITEM_ATTACK_DOWN)) {
				al.state = ALICE_STATE_IDLE_DOWN;
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
			atkit.use = 0;
			atkit.item_no = 0;
		}
	}
}
