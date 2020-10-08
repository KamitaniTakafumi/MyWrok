/*------------------------------------------------
*  @file enemyattack2.cpp
*  @brief �X�e�[�W�Q�̃G�l�~�[�U������
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �w�b�_�[�t�@�C���̃C���N���[�h
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

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// �摜�ǂݍ���(�X�e�[�W�Q)
void LoadCgEnemyAttack2() {
	cgAttackJudgment_1 = LoadTexture("res/attackjudgment_1.png");
	cgAttackJudgment_2 = LoadTexture("res/attackjudgment_2.png");
	cgAttackJudgment_3 = LoadTexture("res/attackjudgment_3.png");
	cgAttackJudgment_7 = LoadTexture("res/attackjudgment_7.png");
	cgAttackJudgment_8 = LoadTexture("res/attackjudgment_8.png");
	cgAttackJudgment_9 = LoadTexture("res/attackjudgment_9.png");
	cgAttackJudgment_10 = LoadTexture("res/attackjudgment_10.png");
	cgAttackJudgment_11 = LoadTexture("res/attackjudgment_11.png");
	cgAttackJudgment_12 = LoadTexture("res/attackjudgment_12.png");
	cgAttackJudgment_13 = LoadTexture("res/attackjudgment_13.png");
	cgAttackJudgment_14 = LoadTexture("res/attackjudgment_14.png");
	cgAttackJudgment_15 = LoadTexture("res/attackjudgment_15.png");
}

// ������(�X�e�[�W�Q)
void InitEnemyAttack2() {
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
*  �X�V
-------------------------------------------------*/

/*
*  @brief �U������̍X�V(�X�e�[�W�Q)
*  @param enemyId �G�̎��ʔԍ�
*/
void AttackCooldinate2(int enemyId) {
	if (en[enemyId].state == STATE_ONE) {
		if (enatk[enemyId].use == 0) {
			if ((en[enemyId].direction == ENEMY_STATE_DOWN) ||
				(en[enemyId].direction == ENEMY_STATE_LEFT) ||
				(en[enemyId].direction == ENEMY_STATE_RIGHT) ||
				(en[enemyId].direction == ENEMY_STATE_UP)) {
				// �G�̏�Ԃ��U����Ԃɂ���
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
			// �G���ƂɍU�������ς���
			switch (en[enemyId].entype)
			{
				// �g�����v��(�n�[�g)
			case ENEMY_HEART:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 200;
					enatk[enemyId].rand = 0;
				}
				else {
					enatk[enemyId].w = 200;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 10) * 3;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 170;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 200;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + 20;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 170;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 200;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + (enatk[enemyId].w / 5);
					enatk[enemyId].y = en[enemyId].y + 20;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 170;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 200;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 170;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 200;
				}
				break;
				// �g�����v��(�_�C��)
			case ENEMY_DIA:
				if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
					(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
					enatk[enemyId].w = 40;
					enatk[enemyId].h = 120;
					enatk[enemyId].rand = 0;
				}
				else {
					enatk[enemyId].w = 120;
					enatk[enemyId].h = 40;
					enatk[enemyId].rand = 0;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 2);
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 90;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 120;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
					enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
					enatk[enemyId].y = en[enemyId].y + 20;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 90;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 120;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
					enatk[enemyId].x = en[enemyId].x + (enatk[enemyId].w / 3);
					enatk[enemyId].y = en[enemyId].y + 20;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 90;
					enatk[enemyId].hit_h = 10;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 120;
					enatk[enemyId].range_h = 40;
				}
				if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
					enatk[enemyId].x = en[enemyId].x;
					enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
					enatk[enemyId].hit_x = 15;
					enatk[enemyId].hit_y = 15;
					enatk[enemyId].hit_w = 10;
					enatk[enemyId].hit_h = 90;
					enatk[enemyId].range_x = 0;
					enatk[enemyId].range_y = 0;
					enatk[enemyId].range_w = 40;
					enatk[enemyId].range_h = 120;
				}
				break;
				// �g�����v��(�N���[�o�[)
			case ENEMY_CLOVER:
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
					enatk[enemyId].y = en[enemyId].y + 20;
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
					enatk[enemyId].y = en[enemyId].y + 20;
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
				// �g�����v��(�X�y�[�h)
			case ENEMY_SPADE:
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
					enatk[enemyId].y = en[enemyId].y + 20;
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
					enatk[enemyId].x = en[enemyId].x + (enatk[enemyId].w / 2);
					enatk[enemyId].y = en[enemyId].y + 20;
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
				// �n�[�g�̏���
			case ENEMY_QUEEN:
				if (enatk[enemyId].select_attack == 0) {
					if (enatk[enemyId].attack_state == 0) {
						enatk[enemyId].rand = rand() % 3;
					}
					// �n�[�g�����U��
					if (enatk[enemyId].rand == 0) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 40;
							enatk[enemyId].h = 40;
							enatk[enemyId].select_attack = 20;
						}
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].x = en[enemyId].x - (enatk[enemyId].w * 4);
							enatk[enemyId].y = en[enemyId].y - (enatk[enemyId].h * 3);
							enatk[enemyId].x2 = en[enemyId].x - (enatk[enemyId].w * 3);
							enatk[enemyId].y2 = en[enemyId].y - (enatk[enemyId].h * 2);
							enatk[enemyId].x3 = en[enemyId].x - (enatk[enemyId].w * 2);
							enatk[enemyId].y3 = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].x4 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y4 = en[enemyId].y;

							enatk[enemyId].x5 = en[enemyId].x + enatk[enemyId].w;
							enatk[enemyId].y5 = en[enemyId].y;
							enatk[enemyId].x6 = en[enemyId].x + (enatk[enemyId].w * 2);
							enatk[enemyId].y6 = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].x7 = en[enemyId].x + (enatk[enemyId].w * 3);
							enatk[enemyId].y7 = en[enemyId].y - (enatk[enemyId].h * 2);
							enatk[enemyId].x8 = en[enemyId].x + (enatk[enemyId].w * 4);
							enatk[enemyId].y8 = en[enemyId].y - (enatk[enemyId].h * 3);

							enatk[enemyId].x9 = en[enemyId].x - (enatk[enemyId].w * 4);
							enatk[enemyId].y9 = en[enemyId].y + (enatk[enemyId].h * 5);
							enatk[enemyId].x10 = en[enemyId].x - (enatk[enemyId].w * 3);
							enatk[enemyId].y10 = en[enemyId].y + (enatk[enemyId].h * 4);
							enatk[enemyId].x11 = en[enemyId].x - (enatk[enemyId].w * 2);
							enatk[enemyId].y11 = en[enemyId].y + (enatk[enemyId].h * 3);
							enatk[enemyId].x12 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y12 = en[enemyId].y + (enatk[enemyId].h * 2);

							enatk[enemyId].x13 = en[enemyId].x + enatk[enemyId].w;
							enatk[enemyId].y13 = en[enemyId].y + (enatk[enemyId].h * 2);
							enatk[enemyId].x14 = en[enemyId].x + (enatk[enemyId].w * 2);
							enatk[enemyId].y14 = en[enemyId].y + (enatk[enemyId].h * 3);
							enatk[enemyId].x15 = en[enemyId].x + (enatk[enemyId].w * 3);
							enatk[enemyId].y15 = en[enemyId].y + (enatk[enemyId].h * 4);
							enatk[enemyId].x16 = en[enemyId].x + (enatk[enemyId].w * 4);
							enatk[enemyId].y16 = en[enemyId].y + (enatk[enemyId].h * 5);

							enatk[enemyId].hit_x = 5;
							enatk[enemyId].hit_y = 5;
							enatk[enemyId].hit_w = 30;
							enatk[enemyId].hit_h = 30;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 40;
							enatk[enemyId].range_h = 40;
						}
					}
					// ��(�O��)�U��
					else if (enatk[enemyId].rand == 1) {
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
					// ��(�͈�)�U��
					else if (enatk[enemyId].rand == 2) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 280;
							enatk[enemyId].h = 280;
							enatk[enemyId].select_attack = 20;
						}
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].x = en[enemyId].x - (enatk[enemyId].w / 7) * 3;
							enatk[enemyId].y = en[enemyId].y - (enatk[enemyId].h / 7) * 2;
							enatk[enemyId].hit_x = 60;
							enatk[enemyId].hit_y = 60;
							enatk[enemyId].hit_w = 160;
							enatk[enemyId].hit_h = 160;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 280;
							enatk[enemyId].range_h = 280;
						}
					}
				}
				break;
				// �}�b�h�n�b�^�[
			case ENEMY_MAD_HATTER2:
				if (enatk[enemyId].select_attack == 0) {
					if (enatk[enemyId].attack_state == 0) {
						enatk[enemyId].rand = rand() % 3;
					}
					// �O���U��
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
					// ���e�U��
					else if (enatk[enemyId].rand == 1) {
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
							// �E��
							enatk[enemyId].x = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y = en[enemyId].y - (enatk[enemyId].h / 4) * 3;
							// ����
							enatk[enemyId].x2 = en[enemyId].x + (enatk[enemyId].w / 4);
							enatk[enemyId].y2 = en[enemyId].y - (enatk[enemyId].h / 4) * 3;
							// �E��
							enatk[enemyId].x3 = en[enemyId].x - enatk[enemyId].w;
							enatk[enemyId].y3 = en[enemyId].y + (enatk[enemyId].h / 4) * 2;
							// ����
							enatk[enemyId].x4 = en[enemyId].x + (enatk[enemyId].w / 4);
							enatk[enemyId].y4 = en[enemyId].y + (enatk[enemyId].h / 4) * 2;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 80;
							enatk[enemyId].hit_h = 80;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 160;
							enatk[enemyId].range_h = 160;
						}
					}
					// �X�q�U��
					else if (enatk[enemyId].rand == 2) {
						if ((en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) ||
							(en[enemyId].direction == ENEMY_STATE_ATTACK_UP)) {
							enatk[enemyId].w = 200;
							enatk[enemyId].h = 200;
							enatk[enemyId].select_attack = 20;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_DOWN) {
							enatk[enemyId].x = en[enemyId].x - (enatk[enemyId].w / 5) * 2;
							enatk[enemyId].y = en[enemyId].y + (enatk[enemyId].h / 5) * 3;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 200;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_LEFT) {
							enatk[enemyId].x = en[enemyId].x - (enatk[enemyId].w / 5) * 6;
							enatk[enemyId].y = en[enemyId].y - (enatk[enemyId].h / 5);
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 200;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_RIGHT) {
							enatk[enemyId].x = en[enemyId].x + (enatk[enemyId].w / 5) * 2;
							enatk[enemyId].y = en[enemyId].y - (enatk[enemyId].h / 5);
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 200;
						}
						if (en[enemyId].direction == ENEMY_STATE_ATTACK_UP) {
							enatk[enemyId].x = en[enemyId].x - (enatk[enemyId].w / 5) * 2;
							enatk[enemyId].y = en[enemyId].y - enatk[enemyId].h;
							enatk[enemyId].hit_x = 40;
							enatk[enemyId].hit_y = 40;
							enatk[enemyId].hit_w = 120;
							enatk[enemyId].hit_h = 120;
							enatk[enemyId].range_x = 0;
							enatk[enemyId].range_y = 0;
							enatk[enemyId].range_w = 200;
							enatk[enemyId].range_h = 200;
						}
					}
				}
				break;
			default:
				break;
			}
			// �U���܂ł̎��Ԃ������
			if (enatk[enemyId].attack_time > 0) {
				enatk[enemyId].attack_time--;		// �U���܂ł̎��Ԃ����炷
				// �U���܂ł̎��Ԃ�0�Ȃ�
				if (enatk[enemyId].attack_time == 0) {
					if (en[enemyId].entype == ENEMY_MAD_HATTER2) {
						// �U���ɂ���ăG�t�F�N�g��ς���
						if (enatk[enemyId].rand == 0) {
							// �G�t�F�N�g����
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
						}
						else if (enatk[enemyId].rand == 1) {
							// �G�t�F�N�g����
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x4, enatk[enemyId].y4, enemyId);
						}
						else if (enatk[enemyId].rand == 2) {
							// �G�t�F�N�g����
							PutEffect(EFFECTTYPE_ENEMY_HATTER2, enatk[enemyId].x, enatk[enemyId].y, enemyId);
						}
					}
					if (en[enemyId].entype == ENEMY_QUEEN) {
						if (enatk[enemyId].rand == 0) {
							// �G�t�F�N�g����
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x4, enatk[enemyId].y4, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x5, enatk[enemyId].y5, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x6, enatk[enemyId].y6, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x7, enatk[enemyId].y7, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x8, enatk[enemyId].y8, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x9, enatk[enemyId].y9, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x10, enatk[enemyId].y10, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x11, enatk[enemyId].y11, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x12, enatk[enemyId].y12, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x13, enatk[enemyId].y13, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x14, enatk[enemyId].y14, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x15, enatk[enemyId].y15, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x16, enatk[enemyId].y16, enemyId);
						}
						else if (enatk[enemyId].rand == 1) {
							// �G�t�F�N�g����
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x2, enatk[enemyId].y2, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x3, enatk[enemyId].y3, enemyId);
						}
						else if (enatk[enemyId].rand == 2) {
							// �G�t�F�N�g����
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x + 120, enatk[enemyId].y, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x, enatk[enemyId].y + 120, enemyId);
							PutEffect(EFFECTTYPE_ENEMY_QUEEN, enatk[enemyId].x + 120, enatk[enemyId].y + 120, enemyId);
						}
					}
					HitCheckEnemyAttack();			// �v���C���[�ƓG�U���̓����蔻��
					EnemyAttack(enemyId);			// �U�����s����
				}
			}
			// �A���X���U���͈͂ɓ����Ă��邩
			// �U���ɂ���čU���̃N�[���^�C���Ȃǂ�ς���
			if (enatk[enemyId].rand == 0) {
				if (en[enemyId].entype == ENEMY_QUEEN) {
					if (IsHitEnemyAttack4(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 10;		// �U���܂ł̎���
							enatk[enemyId].select_attack = 0;		// �U���p�^�[���̏�����
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
				else if(en[enemyId].entype == ENEMY_MAD_HATTER2) {
					if (IsHitEnemyAttack(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 20;		// �U���܂ł̎���
							enatk[enemyId].select_attack = 0;		// �U���p�^�[���̏�����
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
				else if (en[enemyId].entype == ENEMY_CLOVER) {
					if (IsHitEnemyAttack(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 10;		// �U���܂ł̎���
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
				else {
					if (IsHitEnemyAttack(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 20;		// �U���܂ł̎���
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
			}
			else if (enatk[enemyId].rand == 1) {
				if (en[enemyId].entype == ENEMY_QUEEN) {
					if (IsHitEnemyAttack(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 20;		// �U���܂ł̎���
							enatk[enemyId].select_attack = 0;		// �U���p�^�[���̏�����
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
				else if (en[enemyId].entype == ENEMY_MAD_HATTER2) {
					if (IsHitEnemyAttack2(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 25;		// �U���܂ł̎���
							enatk[enemyId].select_attack = 0;		// �U���p�^�[���̏�����
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
			}
			else if (enatk[enemyId].rand == 2) {
				if (en[enemyId].entype == ENEMY_QUEEN) {
					if (IsHitEnemyAttack(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 25;		// �U���܂ł̎���
							enatk[enemyId].select_attack = 0;		// �U���p�^�[���̏�����
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
				else if (en[enemyId].entype == ENEMY_MAD_HATTER2) {
					if (IsHitEnemyAttack(enemyId)) {
						if ((enatk[enemyId].attack_time <= 0) & (enemyattackCooltime <= 0)) {
							enatk[enemyId].attack_time = 25;		// �U���܂ł̎���
							enatk[enemyId].select_attack = 0;		// �U���p�^�[���̏�����
							enatk[enemyId].attack_state = 1;		// �U����Ԃɂ���
						}
					}
				}
			}
			// �G���U����Ԃɓ����Ă��Ȃ�
			if (enatk[enemyId].attack_state == 0) {
				if (enatk[enemyId].select_attack > 0) {
					enatk[enemyId].select_attack--;
				}
				// �G�̏�Ԃ����ɖ߂�
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
				// �G�U������̏�����
				enatk[enemyId].x = 0;
				enatk[enemyId].y = 0;
				enatk[enemyId].x2 = 0;
				enatk[enemyId].y2 = 0;
				enatk[enemyId].x3 = 0;
				enatk[enemyId].y3 = 0;
				enatk[enemyId].x4 = 0;
				enatk[enemyId].y4 = 0;
				enatk[enemyId].x5 = 0;
				enatk[enemyId].y5 = 0;
				enatk[enemyId].x6 = 0;
				enatk[enemyId].y6 = 0;
				enatk[enemyId].x7 = 0;
				enatk[enemyId].y7 = 0;
				enatk[enemyId].x8 = 0;
				enatk[enemyId].y8 = 0;
				enatk[enemyId].x9 = 0;
				enatk[enemyId].y9 = 0;
				enatk[enemyId].x10 = 0;
				enatk[enemyId].y10 = 0;
				enatk[enemyId].x11 = 0;
				enatk[enemyId].y11 = 0;
				enatk[enemyId].x12 = 0;
				enatk[enemyId].y12 = 0;
				enatk[enemyId].x13 = 0;
				enatk[enemyId].y13 = 0;
				enatk[enemyId].x14 = 0;
				enatk[enemyId].y14 = 0;
				enatk[enemyId].x15 = 0;
				enatk[enemyId].y15 = 0;
				enatk[enemyId].x16 = 0;
				enatk[enemyId].y16 = 0;
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
				enatk[enemyId].attack_time = 0;
			}
		}
	}
	else {
	// �G�U������̏�����
	enatk[enemyId].x = 0;
	enatk[enemyId].y = 0;
	enatk[enemyId].x2 = 0;
	enatk[enemyId].y2 = 0;
	enatk[enemyId].x3 = 0;
	enatk[enemyId].y3 = 0;
	enatk[enemyId].x4 = 0;
	enatk[enemyId].y4 = 0;
	enatk[enemyId].x5 = 0;
	enatk[enemyId].y5 = 0;
	enatk[enemyId].x6 = 0;
	enatk[enemyId].y6 = 0;
	enatk[enemyId].x7 = 0;
	enatk[enemyId].y7 = 0;
	enatk[enemyId].x8 = 0;
	enatk[enemyId].y8 = 0;
	enatk[enemyId].x9 = 0;
	enatk[enemyId].y9 = 0;
	enatk[enemyId].x10 = 0;
	enatk[enemyId].y10 = 0;
	enatk[enemyId].x11 = 0;
	enatk[enemyId].y11 = 0;
	enatk[enemyId].x12 = 0;
	enatk[enemyId].y12 = 0;
	enatk[enemyId].x13 = 0;
	enatk[enemyId].y13 = 0;
	enatk[enemyId].x14 = 0;
	enatk[enemyId].y14 = 0;
	enatk[enemyId].x15 = 0;
	enatk[enemyId].y15 = 0;
	enatk[enemyId].x16 = 0;
	enatk[enemyId].y16 = 0;
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

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �G�U���̕`��(�X�e�[�W�Q)
void DrawEnemyAttack2() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		if (en[i].use == 1) {
			// ���G���͈��Ԋu�ŕ`�悵�Ȃ�
			if (en[i].nohit_cnt == 0 || (en[i].nohit_cnt % 10) < 7)
			{
				if (enatk[i].attack_time != 0) {
					// �G�ɂ���ĕ`���ς���
					switch (en[i].entype) {
						// �g�����v��(�n�[�g)
					case ENEMY_HEART:
						if (IsHitEnemyAttack != 0) {
							if (enatk[i].attack_time > 0) {
								if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_UP)) {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_12);
								}
								else {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_13);
								}
							}
							break;
						}
						// �g�����v��(�_�C��)
					case ENEMY_DIA:
						if (IsHitEnemyAttack != 0) {
							if (enatk[i].attack_time > 0) {
								if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_UP)) {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_14);
								}
								else {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_15);
								}
								break;
							}
							break;
						}
						// �g�����v��(�N���[�o�[)
					case ENEMY_CLOVER:
						if (IsHitEnemyAttack != 0) {
							if (enatk[i].attack_time > 0) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								break;
							}
						}
						// �g�����v��(�X�y�[�h)
					case ENEMY_SPADE:
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
						}
						// �n�[�g�̏���
					case ENEMY_QUEEN:
						// �n�[�g�����U��
						if (enatk[i].rand == 0) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack4 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack4 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack4 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack4 != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x2 + enatk[i].range_x - cv.view_x, enatk[i].y2 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x3 + enatk[i].range_x - cv.view_x, enatk[i].y3 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x4 + enatk[i].range_x - cv.view_x, enatk[i].y4 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x5 + enatk[i].range_x - cv.view_x, enatk[i].y5 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x6 + enatk[i].range_x - cv.view_x, enatk[i].y6 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x7 + enatk[i].range_x - cv.view_x, enatk[i].y7 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x8 + enatk[i].range_x - cv.view_x, enatk[i].y8 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x9 + enatk[i].range_x - cv.view_x, enatk[i].y9 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x10 + enatk[i].range_x - cv.view_x, enatk[i].y10 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x11 + enatk[i].range_x - cv.view_x, enatk[i].y11 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x12 + enatk[i].range_x - cv.view_x, enatk[i].y12 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x13 + enatk[i].range_x - cv.view_x, enatk[i].y13 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x14 + enatk[i].range_x - cv.view_x, enatk[i].y14 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x15 + enatk[i].range_x - cv.view_x, enatk[i].y15 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
								DrawMemTh(enatk[i].x16 + enatk[i].range_x - cv.view_x, enatk[i].y16 + enatk[i].range_y - cv.view_y, cgAttackJudgment_1);
							}
						}
						// ��(�O��)�U��
						else if (enatk[i].rand == 1) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_7);
							}
							else {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_8);
							}
						}
						// ��(�͈�)�U��
						else if (enatk[i].rand == 2) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_11);
							}
						}
						break;
						// �}�b�h�n�b�^�[
					case ENEMY_MAD_HATTER2:
						// �O���U��
						if (enatk[i].rand == 0) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack != 0)) {
								if ((en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack != 0) ||
									(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack != 0)) {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_7);
								}
								else {
									DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_8);
								}
							}
						}
						// ���e�U��
						else if (enatk[i].rand == 1) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack2 != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack2 != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_9);
								DrawMemTh(enatk[i].x2 + enatk[i].range_x2 - cv.view_x, enatk[i].y2 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_9);
								DrawMemTh(enatk[i].x3 + enatk[i].range_x - cv.view_x, enatk[i].y3 + enatk[i].range_y - cv.view_y, cgAttackJudgment_9);
								DrawMemTh(enatk[i].x4 + enatk[i].range_x2 - cv.view_x, enatk[i].y4 + enatk[i].range_y2 - cv.view_y, cgAttackJudgment_9);
							}
						}
						// �X�q�U��
						else if (enatk[i].rand == 2) {
							if ((en[i].direction == ENEMY_STATE_ATTACK_LEFT) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_RIGHT) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_DOWN) & (IsHitEnemyAttack != 0) ||
								(en[i].direction == ENEMY_STATE_ATTACK_UP) & (IsHitEnemyAttack != 0)) {
								DrawMemTh(enatk[i].x + enatk[i].range_x - cv.view_x, enatk[i].y + enatk[i].range_y - cv.view_y, cgAttackJudgment_10);
							}
						}
						break;
					}
				}
			}
		}
	}
}
