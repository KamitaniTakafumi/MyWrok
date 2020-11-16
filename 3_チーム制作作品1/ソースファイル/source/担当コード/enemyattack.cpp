/*------------------------------------------------
*  @file enemyattack.cpp
*  @brief ƒXƒe[ƒW‚P‚ÌƒGƒlƒ~[UŒ‚ˆ—
*  @author ã’J‹±jA‚‹´Œ«‘¾
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ƒwƒbƒ_[ƒtƒ@ƒCƒ‹‚ÌƒCƒ“ƒNƒ‹[ƒh
------------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"
#include	"vector.h"

#include	"game.h"
#include    "enemy.h"
#include	"enemyattack.h"
#include	"camera.h"
#include	"HitJudgment.h"
#include	"game_effect.h"

/*-----------------------------------------------
* ƒOƒ[ƒoƒ‹•Ï”éŒ¾
-----------------------------------------------*/

// ‰æ‘œƒf[ƒ^

int cgAttackJudgment_1;		// “–‚½‚è”ÍˆÍ‚P
int cgAttackJudgment_2;		// “–‚½‚è”ÍˆÍ‚Q
int cgAttackJudgment_3;		// “–‚½‚è”ÍˆÍ‚R
int cgAttackJudgment_4;		// “–‚½‚è”ÍˆÍ‚S
int cgAttackJudgment_5;		// “–‚½‚è”ÍˆÍ‚T
int cgAttackJudgment_6;		// “–‚½‚è”ÍˆÍ‚U
int cgAttackJudgment_7;		// “–‚½‚è”ÍˆÍ‚V
int cgAttackJudgment_8;		// “–‚½‚è”ÍˆÍ‚W
int cgAttackJudgment_9;		// “–‚½‚è”ÍˆÍ‚X
int cgAttackJudgment_10;	// “–‚½‚è”ÍˆÍ‚P‚O
int cgAttackJudgment_11;	// “–‚½‚è”ÍˆÍ‚P‚P
int cgAttackJudgment_12;	// “–‚½‚è”ÍˆÍ‚P‚Q
int cgAttackJudgment_13;	// “–‚½‚è”ÍˆÍ‚P‚R
int cgAttackJudgment_14;	// “–‚½‚è”ÍˆÍ‚P‚S
int cgAttackJudgment_15;	// “–‚½‚è”ÍˆÍ‚P‚T

int enemyattackCooltime;		// UŒ‚‚ÌƒN[ƒ‹ƒ^ƒCƒ€

// “GUŒ‚‚Ìî•ñ
struct ENEMYATTACK enatk[ENEMY_MAX];

/*-------------------------------------------------
*  ‰Šú‰»
-------------------------------------------------*/

// ‰æ‘œ“Ç‚İ‚İ
void LoadCgEnemyAttack() {
	cgAttackJudgment_1 = LoadTexture("res/attackjudgment_1.png");
	cgAttackJudgment_2 = LoadTexture("res/attackjudgment_2.png");
	cgAttackJudgment_3 = LoadTexture("res/attackjudgment_3.png");
	cgAttackJudgment_4 = LoadTexture("res/attackjudgment_4.png");
	cgAttackJudgment_5 = LoadTexture("res/attackjudgment_5.png");
	cgAttackJudgment_6 = LoadTexture("res/attackjudgment_6.png");
	cgAttackJudgment_7 = LoadTexture("res/attackjudgment_7.png");
	cgAttackJudgment_8 = LoadTexture("res/attackjudgment_8.png");
}

// ‰Šú‰»
void InitEnemyAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		enatk[i].use = 0;
		enatk[i].x = 0;
		enatk[i].y = 0;
		enatk[i].x2 = 0;
		enatk[i].y2 = 0;
		enatk[i].x3 = 0;
		enatk[i].y3 = 0;
		enatk[i].x4 = 0;
		enatk[i].y4 = 0;
		enatk[i].hit_x = 0;
		enatk[i].hit_y = 0;
		enatk[i].hit_w = 0;
		enatk[i].hit_h = 0;
		enatk[i].hit_x2 = 0;
		enatk[i].hit_y2 = 0;
		enatk[i].hit_w2 = 0;
		enatk[i].hit_h2 = 0;
		enatk[i].range_x = 0;
		enatk[i].range_y = 0;
		enatk[i].range_w = 0;
		enatk[i].range_h = 0;
		enatk[i].range_x2 = 0;
		enatk[i].range_y2 = 0;
		enatk[i].range_w2 = 0;
		enatk[i].range_h2 = 0;
		enatk[i].attack_time = 0;
		enatk[i].attack_state = 0;
		enatk[i].select_attack = 0;
		enatk[i].rand = 0;
	}
	enemyattackCooltime = 0;
}

/*-------------------------------------------------
*  XV
-------------------------------------------------*/

/*
*  @brief UŒ‚”»’è‚ÌXV
*  @param enemyId “G‚Ì¯•Ê”Ô†
*/
void AttackCooldinate(int enemyId) {
	// ƒvƒŒƒCƒ„[‚ª“G‚ÌUŒ‚”ÍˆÍ“à‚É“ü‚Á‚Ä‚¢‚é
	if (en[enemyId].state == STATE_ONE) {
		if (enatk[enemyId].use == 0) {
			if ((en[enemyId].direction == ENEMY_STATE_DOWN) ||
				(en[enemyId].direction == ENEMY_STATE_LEFT) ||
				(en[enemyId].direction == ENEMY_STATE_RIGHT) ||
				(en[enemyId].direction == ENEMY_STATE_UP)) {
				// “G‚Ìó‘Ô‚ğUŒ‚ó‘Ô‚É‚·‚é
				if (en[enemyId].direction == ENEMY_STATE_DOWN) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_DOWN;
				}
				if (en[enemyId].direction == ENEMY_STATE_LEFT) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_LEFT;
				}
				if (en[enemyId].direction == ENEMY_STATE_RIGHT) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_RIGHT;
				}
				if (en[enemyId].direction == ENEMY_STATE_UP) {
					en[enemyId].direction = ENEMY_STATE_ATTACK_UP;
				}
			}
			// “G‚²‚Æ‚ÉUŒ‚”»’è‚ğ•Ï‚¦‚é
			switch (en[enemyId].entype)
			{
				// ˆğ’
			case ENEMY_CATERPILLAR:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				break;
				// ƒ}ƒ^ƒ“ƒS
			case ENEMY_MATANGO:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 80;
					enatk[enemyId].rand = 0;
				}
				else {
					enatk[enemyId].w = 80;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 4) * 3;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 50;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 80;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 50;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 80;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w / 2;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 50;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 80;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 50;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 80;
				}
				break;
				// ƒ}[ƒWƒ}ƒ^ƒ“ƒS
			case ENEMY_MERGE_MATANGO:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 160;
					enatk[enemyId].rand = 0;
				}
				else {
					enatk[enemyId].w = 160;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 8) * 3;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 130;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 160;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 130;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 160;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w / 4;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 130;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 160;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 130;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 160;
				}
				break;
				// ˜T
			case ENEMY_WOLF:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x + 10;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 2) * 3;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + (enatk[enemyId].w / 2) * 3;
					enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 2;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x + 10;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 40;
				}
				break;
				// ƒ}ƒbƒhƒnƒbƒ^[
			case ENEMY_MAD_HATTER:
				if (enatk[enemyId].select_attack == 0) {
					if (enatk[enemyId].attack_state == 0) {
						enatk[enemyId].rand = rand() % 3;
					}
					// ‘O•ûUŒ‚
					if (enatk[enemyId].rand == 0) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 120;
							enatk[enemyId].h = 200;
							enatk[enemyId].select_attack = 20;
						}
						else {
							enatk[enemyId].w = 200;
							enatk[enemyId].h = 120;
							enatk[enemyId].select_attack = 20;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w / 3;
							enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 5) * 2;
							enatk[enemyId].x2 = en[enemyId].x;
							enatk[enemyId].y2 = en[enemyId].y + (enatk[enemyId].h / 5) * 2;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 3;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 5) * 2;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 40;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 120;
							enatk[enemyId].range_h = 200;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y = en[enemyId].y;
							enatk[enemyId].x2 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y2 = en[enemyId].y + enatk[enemyId].h / 3;
							enatk[enemyId].x3 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 40;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 120;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
							enatk[enemyId].x = en[enemyId].x + enatk[enemyId].w / 5;
							enatk[enemyId].y = en[enemyId].y;
							enatk[enemyId].x2 = en[enemyId].x + enatk[enemyId].w / 5;
							enatk[enemyId].y2 = en[enemyId].y + enatk[enemyId].h / 3;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 5;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 40;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 120;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w / 3;
							enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].x2 = en[enemyId].x;
							enatk[enemyId].y2 = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 3;
							enatk[enemyId].y3 = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 40;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 120;
							enatk[enemyId].range_h = 200;
						}
					}
					// ”š’eUŒ‚
					else if (enatk[enemyId].rand == 1) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 120;
							enatk[enemyId].h = 120;
							enatk[enemyId].select_attack = 20;
						}
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y = en[enemyId].y - (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].x2 = en[enemyId].x + (enatk[enemyId].w / 3);
							enatk[enemyId].y2 = en[enemyId].y - (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].x3 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].x4 = en[enemyId].x + (enatk[enemyId].w / 3);
							enatk[enemyId].y4 = en[enemyId].y + (enatk[enemyId].h / 3) * 2;
							enatk[enemyId].hit_x = 20;
							enatk[enemyId].hit_y = 20;
							enatk[enemyId].hit_w = 100;
							enatk[enemyId].hit_h = 100;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 120;
							enatk[enemyId].range_h = 120;
						}
					}
					// ƒiƒCƒtUŒ‚
					else if (enatk[enemyId].rand == 2) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 160;
							enatk[enemyId].h = 160;
							enatk[enemyId].select_attack = 20;
						}
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y = en[enemyId].y + enatk[enemyId].h / 4;
							enatk[enemyId].x2 = en[enemyId].x;
							enatk[enemyId].y2 = en[enemyId].y - (enatk[enemyId].h / 4) * 3;
							enatk[enemyId].x3 = en[enemyId].x + enatk[enemyId].w / 4;
							enatk[enemyId].y3 = en[enemyId].y + enatk[enemyId].h / 4;
							enatk[enemyId].x4 = en[enemyId].x;
							enatk[enemyId].y4 = en[enemyId].y + enatk[enemyId].h / 2;
							enatk[enemyId].hit_x = 0;
							enatk[enemyId].hit_y = 0;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 40;
							enatk[enemyId].hit_x2 = 0;
							enatk[enemyId].hit_y2 = 0;
							enatk[enemyId].hit_w2 = 40;
							enatk[enemyId].hit_h2 = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 160;
							enatk[enemyId].range_h = 40;
							enatk[enemyId].range_x2 = 0;
							enatk[enemyId].range_y2 = 0;
							enatk[enemyId].range_w2 = 40;
							enatk[enemyId].range_h2 = 160;
						}
					}
				}
				break;
			default:
				break;
			}
			// UŒ‚‚Ü‚Å‚ÌŠÔ‚ª‚ ‚ê‚Î
			if (enatk[enemyId].attack_time > 0) {
				enatk[enemyId].attack_time--;		// UŒ‚‚Ü‚Å‚ÌŠÔ‚ğŒ¸‚ç‚·
				// UŒ‚‚Ü‚Å‚ÌŠÔ‚ª0‚È‚ç
				if (enatk[enemyId].attack_time == 0) {
					if (en[enemyId].entype == ENEMY_MAD_HATTER) {
						// UŒ‚‚É‚æ‚Á‚ÄƒGƒtƒFƒNƒg‚ğ•Ï‚¦‚é
						if (enatk[enemyId].rand == 0) {
							// ƒGƒtƒFƒNƒgˆ—
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
						}
						else if (enatk[enemyId].rand == 1) {
							// ƒGƒtƒFƒNƒgˆ—
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x4, enatk[enemyId].y4, enemyId);
						}
						else if (enatk[enemyId].rand == 2) {
							// ƒGƒtƒFƒNƒgˆ—
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER, enatk[enemyId].x4, enatk[enemyId].y4, enemyId);
						}
					}
					HitCheckEnemyAttack();			// ƒvƒŒƒCƒ„[‚Æ“GUŒ‚‚Ì“–‚½‚è”»’è
					EnemyAttack(enemyId);			// UŒ‚‚ğs‚Á‚½
				}
			}
			// ƒAƒŠƒX‚ªUŒ‚”ÍˆÍ‚É“ü‚Á‚Ä‚¢‚é‚©
			// UŒ‚‚É‚æ‚Á‚ÄUŒ‚‚ÌƒN[ƒ‹ƒ^ƒCƒ€‚È‚Ç‚ğ•Ï‚¦‚é
			if (enatk[enemyId].rand == 0) {
				if (IsHitEnemyAttack(enemyId)) {
					if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
						if (en[enemyId].entype == ENEMY_MAD_HATTER) {
							enatk[enemyId].attack_time = 20;		// UŒ‚‚Ü‚Å‚ÌŠÔ
							enatk[enemyId].select_attack = 0;		// UŒ‚ƒpƒ^[ƒ“‚Ì‰Šú‰»
						}
						else if ((en[enemyId].entype == ENEMY_CATERPILLAR) || (en[enemyId].entype == ENEMY_WOLF)) {
							enatk[enemyId].attack_time = 10;		// UŒ‚‚Ü‚Å‚ÌŠÔ
						}
						else {
							enatk[enemyId].attack_time = 20;		// UŒ‚‚Ü‚Å‚ÌŠÔ
						}
						enatk[enemyId].attack_state = 1;		// UŒ‚ó‘Ô‚É‚·‚é
					}
				}
			}
			else if (enatk[enemyId].rand == 1) {
				if (IsHitEnemyAttack2(enemyId)) {
					if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
						if (en[enemyId].entype == ENEMY_MAD_HATTER) {
							enatk[enemyId].attack_time = 20;		// UŒ‚‚Ü‚Å‚ÌŠÔ
							enatk[enemyId].select_attack = 0;		// UŒ‚ƒpƒ^[ƒ“‚Ì‰Šú‰»
						}
						else {
							enatk[enemyId].attack_time = 20;		// UŒ‚‚Ü‚Å‚ÌŠÔ
						}
						enatk[enemyId].attack_state = 1;		// UŒ‚ó‘Ô‚É‚·‚é
					}
				}
			}
			else if (enatk[enemyId].rand == 2) {
				if (IsHitEnemyAttack3(enemyId)) {
					if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
						if (en[enemyId].entype == ENEMY_MAD_HATTER) {
							enatk[enemyId].attack_time = 15;		// UŒ‚‚Ü‚Å‚ÌŠÔ
							enatk[enemyId].select_attack = 0;		// UŒ‚ƒpƒ^[ƒ“‚Ì‰Šú‰»
						}
						else {
							enatk[enemyId].attack_time = 20;		// UŒ‚‚Ü‚Å‚ÌŠÔ
						}
						enatk[enemyId].attack_state = 1;		// UŒ‚ó‘Ô‚É‚·‚é
					}
				}
			}

			// “G‚ªUŒ‚ó‘Ô‚É“ü‚Á‚Ä‚¢‚È‚¢
			if (enatk[enemyId].attack_state == 0) {
				if (enatk[enemyId].select_attack > 0) {
					enatk[enemyId].select_attack--;
				}
				// “G‚Ìó‘Ô‚ğŒ³‚É–ß‚·
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					en[enemyId].direction = ENEMY_STATE_DOWN;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					en[enemyId].direction = ENEMY_STATE_LEFT;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					en[enemyId].direction = ENEMY_STATE_RIGHT;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					en[enemyId].direction = ENEMY_STATE_UP;
				}
				// “GUŒ‚”»’è‚Ì‰Šú‰»
				enatk[enemyId].x = 0;
				enatk[enemyId].y = 0;
				enatk[enemyId].x2 = 0;
				enatk[enemyId].y2 = 0;
				enatk[enemyId].x3 = 0;
				enatk[enemyId].y3 = 0;
				enatk[enemyId].x4 = 0;
				enatk[enemyId].y4 = 0;
				enatk[enemyId].hit_x = 0;
				enatk[enemyId].hit_y = 0;
				enatk[enemyId].hit_w = 0;
				enatk[enemyId].hit_h = 0;
				enatk[enemyId].range_x = 0;
				enatk[enemyId].range_y = 0;
				enatk[enemyId].range_w = 0;
				enatk[enemyId].range_h = 0;
				enatk[enemyId].attack_time = 0;
			}
		}
	}
	else {
		// “GUŒ‚”»’è‚Ì‰Šú‰»
		enatk[enemyId].x = 0;
		enatk[enemyId].y = 0;
		enatk[enemyId].hit_x = 0;
		enatk[enemyId].hit_y = 0;
		enatk[enemyId].hit_w = 0;
		enatk[enemyId].hit_h = 0;
		enatk[enemyId].hit_x2 = 0;
		enatk[enemyId].hit_y2 = 0;
		enatk[enemyId].hit_w2 = 0;
		enatk[enemyId].hit_h2 = 0;
		enatk[enemyId].range_x = 0;
		enatk[enemyId].range_y = 0;
		enatk[enemyId].range_w = 0;
		enatk[enemyId].range_h = 0;
		enatk[enemyId].range_x2 = 0;
		enatk[enemyId].range_y2 = 0;
		enatk[enemyId].range_w2 = 0;
		enatk[enemyId].range_h2 = 0;

		enatk[enemyId].attack_state = 0;
		enatk[enemyId].attack_time = 0;
		enemyattackCooltime = 0;
		enatk[enemyId].use = 0;
	}
}

/*
*  @brief “G‚ªUŒ‚‚ğs‚Á‚½
*  @param enemyId “G‚Ì¯•Ê”Ô†
*/
void EnemyAttack(int enemyId) {
	if (enatk[enemyId].use == 0) {
		enatk[enemyId].use = 1;			// UŒ‚‚ğg—pó‘Ô‚É‚·‚é
		enemyattackCooltime = 30;		// UŒ‚‚ÌƒN[ƒ‹ƒ^ƒCƒ€‚ğİ’è
	}
}

// “G‚ÌUŒ‚ƒN[ƒ‹ƒ^ƒCƒ€
void EnemyAttackCooltime() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		if (enatk[i].use == 1) {
			enemyattackCooltime--;				// ƒN[ƒ‹ƒ^ƒCƒ€‚ğŒ¸‚ç‚·
			if (enemyattackCooltime < 0) {		// ƒN[ƒ‹ƒ^ƒCƒ€‚ªI‚í‚Á‚½‚ç
				// UŒ‚ó‘Ô‚ğ–ß‚·
				if (en[i].direction == ENEMY_STATE_ATTACK_DOWN) {
					en[i].direction = ENEMY_STATE_DOWN;
				}
				if (en[i].direction == ENEMY_STATE_ATTACK_LEFT) {
					en[i].direction = ENEMY_STATE_LEFT;
				}
				if (en[i].direction == ENEMY_STATE_ATTACK_RIGHT) {
					en[i].direction = ENEMY_STATE_RIGHT;
				}
				if (en[i].direction == ENEMY_STATE_ATTACK_UP) {
					en[i].direction = ENEMY_STATE_UP;
				}
				// “GUŒ‚”»’è‚Ì‰Šú‰»
				enatk[i].x = 0;
				enatk[i].y = 0;
				enatk[i].hit_x = 0;
				enatk[i].hit_y = 0;
				enatk[i].hit_w = 0;
				enatk[i].hit_h = 0;
				enatk[i].hit_x2 = 0;
				enatk[i].hit_y2 = 0;
				enatk[i].hit_w2 = 0;
				enatk[i].hit_h2 = 0;
				enatk[i].range_x = 0;
				enatk[i].range_y = 0;
				enatk[i].range_w = 0;
				enatk[i].range_h = 0;
				enatk[i].range_x2 = 0;
				enatk[i].range_y2 = 0;
				enatk[i].range_w2 = 0;
				enatk[i].range_h2 = 0;

				enatk[i].attack_state = 0;
				enatk[i].attack_time = 0;
				enemyattackCooltime = 0;
				enatk[i].use = 0;
			}
		}
	}
}

/*------------------------------------------------------
*  •`‰æ
------------------------------------------------------*/

// “GUŒ‚‚Ì•`‰æ
void DrawEnemyAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		if (en[i].use == 1) {
			// –³“G’†‚Íˆê’èŠÔŠu‚Å•`‰æ‚µ‚È‚¢
			if (en[i].nohit_cnt == 0 || (en[i].nohit_cnt % 10) < 7)
			{
				if (enatk[i].attack_time != 0) {
					// “G‚É‚æ‚Á‚Ä•`‰æ‚ğ•Ï‚¦‚é
					switch (en[i].entype) {
						// ˆğ’
					case ENEMY_CATERPILLAR:
						if (IsHitEnemyAttack != 0) {
							DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
							break;
						}
						// ƒ}ƒ^ƒ“ƒS
					case ENEMY_MATANGO:
						if (IsHitEnemyAttack != 0) {
							if (enatk[i].attack_time > 0) {
								if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_UP)) {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_2);
								}
								else {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_3);
								}
								break;
							}
							break;
						}
						// ƒ}[ƒWƒ}ƒ^ƒ“ƒS
					case ENEMY_MERGE_MATANGO:
						if (IsHitEnemyAttack != 0) {
							if (IsHitPlayerEnemyRange(i) != 0) {
								if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_UP)) {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_4);
								}
								else {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_5);
								}
								break;
							}
							break;
						}
						// ˜T
					case ENEMY_WOLF:
						if (IsHitEnemyAttack != 0) {
							DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
							break;
						}
						// ƒ}ƒbƒhƒnƒbƒ^[
					case ENEMY_MAD_HATTER:
						// ‘O•ûUŒ‚
						if (enatk[i].rand == 0) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_7);
							}
							else {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_8);
							}
						}
						// ”š’eUŒ‚
						else if (enatk[i].rand == 1) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack2 != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_6);
								DrawMemTh(enatk[i].x2 + enatk[i].range_x2 - cv.view_x, enatk[i].y2 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_6);
								DrawMemTh(enatk[i].x3 + enatk[i].range_x - cv.view_x, enatk[i].y3 + enatk[i].range_y - cv.view_y, cgAttackJudgment_6);
								DrawMemTh(enatk[i].x4 + enatk[i].range_x2 - cv.view_x, enatk[i].y4 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_6);
							}
						}
						// ƒiƒCƒtUŒ‚
						else if (enatk[i].rand == 2) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack3 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack3 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack3 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack3 != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_5);
								DrawMemTh(enatk[i].x2 + enatk[i].range_x2 - cv.view_x, enatk[i].y2 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_4);
								DrawMemTh(enatk[i].x3 + enatk[i].range_x - cv.view_x, enatk[i].y3 + enatk[i].range_y - cv.view_y, cgAttackJudgment_5);
								DrawMemTh(enatk[i].x4 + enatk[i].range_x2 - cv.view_x, enatk[i].y4 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_4);
							}
						}
						break;
					}
				}
			}
		}
	}
}