/*------------------------------------------------
*  @file enemy2.cpp
*  @brief �X�e�[�W2�̃G�l�~�[����
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
#include	"global.h"

#include    "alice.h"
#include    "enemy.h"
#include	"camera.h"
#include	"mapdata_2.h"
#include	"HitJudgment.h"
#include	"enemyattack.h"
#include	"recipe.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

// �摜�f�[�^

int cgHeart[4 * 3];					// �n�[�g��
int cgDia[4 * 3];					// �_�C�A��
int cgClover[4 * 3];				// �N���[�o�[��
int cgSpade[4 * 3];					// �X�y�[�h��
int cgQueen[4 * 4];					// �n�[�g�̏���
int cgQueenDead;					// �n�[�g�̏���(���S)
int cgHatterDead;					// �}�b�h�n�b�^�[(���S)
int hearttbl[] = { 0, 1, 2 };		// �`��e�[�u��(�n�[�g��)
int diatbl[] = { 0, 1, 2 };			// �`��e�[�u��(�_�C�A��)
int clovertbl[] = { 0, 1, 2 };		// �`��e�[�u��(�N���[�o�[��)
int spadetbl[] = { 0, 1, 2 };		// �`��e�[�u��(�X�y�[�h��)
int queentbl[] = { 0, 1, 2, 3 };	// �`��e�[�u��(�n�[�g�̏���)
int cgHeartAttack;					// �n�[�g���U��
int cgDiaAttack;					// �_�C�A���U��
int cgCloverAttack;					// �N���[�o�[���U��
int cgSpadeAttack;					// �X�y�[�h���U��
int cgHeartF;						// �����o��(�n�[�g��)
int cgDiaF;							// �����o��(�_�C�A��)
int cgCloverF;						// �����o��(�N���[�o�[��)
int cgSpadeF;						// �����o��(�X�y�[�h��)

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// �G�摜�̓ǂݍ���(�X�e�[�W�Q)
void LoadCgEnemy2()
{
	LoadBlkTexture("res/trumpsoldiershart_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgHeart);
	LoadBlkTexture("res/trumpsoldiersdiamond_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgDia);
	LoadBlkTexture("res/trumpsoldierclovershart_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgClover);
	LoadBlkTexture("res/trumpsoldiersspade_all_sheet.png", 40, 60, 3, 4, 3 * 4, cgSpade);
	LoadBlkTexture("res/queen.png", 40, 80, 4, 4, 4 * 4, cgQueen);
	LoadBlkTexture("res/madhatter_sheet.png", 40, 80, 4, 4, 4 * 4, cgHatter);

	cgHeartAttack = LoadTexture("res/hart_kougeki.png");
	cgDiaAttack = LoadTexture("res/diamond_kougeki.png");
	cgCloverAttack = LoadTexture("res/clover_kougeki.png");
	cgSpadeAttack = LoadTexture("res/spade_kougwki.png");

	cgHeartF = LoadTexture("res/heartF.png");
	cgDiaF = LoadTexture("res/diaF.png");
	cgCloverF = LoadTexture("res/cloverF.png");
	cgSpadeF = LoadTexture("res/spadeF.png");

	cgQueenDead = LoadTexture("res/queenend.png");
	cgHatterDead = LoadTexture("res/madhatterend.png");
}

/*
*  @brief �G�̊�{���
*  @param enemyId �G�̎��ʔԍ�
*  @param enemytype �G�̎��
*/
void EnemyDef2(int enemyId, int enemytype) {
	switch (enemytype) {
	case ENEMY_HEART:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 8;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		en[enemyId].required = 0;
		break;
	case ENEMY_DIA:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 5;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_CLOVER:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 5;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_SPADE:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 5;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_QUEEN:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 40;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -1160;
		en[enemyId].hit_range_y = -1160;
		en[enemyId].hit_range_w = 2360;
		en[enemyId].hit_range_h = 2360;
		en[enemyId].hp = 50;
		en[enemyId].max_hp = 50;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_MAD_HATTER2:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 4;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 40;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -1160;
		en[enemyId].hit_range_y = -1160;
		en[enemyId].hit_range_w = 2360;
		en[enemyId].hit_range_h = 2360;
		en[enemyId].hp = 80;
		en[enemyId].max_hp = 80;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	}
}

// �G�l�~�[������(�X�e�[�W�Q)
void InitEnemy2()
{
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		en[i].use = 0;
		en[i].state = STATE_NONE;
		en[i].direction = ENEMY_STATE_DOWN;
		en[i].nohit_cnt = 0;
		en[i].damagecooltime = 0;
		en[i].itemdamagecooltime = 0;
		en[i].period = 0;
		en[i].period2 = 0;
		en[i].period3 = 0;
		en[i].period4 = 0;
		en[i].state_enemy = 0;
		en[i].recipe_no = 0;
	}

	if (stateStage == STATE_EP2STAGE2_1) {
		i = 1;
		en[i].required = 1;
		i = 3;
		en[i].required = 1;
		i = 6;
		en[i].required = 1;
	}
	else if (stateStage == STATE_EP2STAGE1_3) {
		i = 1;
		en[i].required = 1;
		i = 3;
		en[i].required = 1;
		i = 4;
		en[i].required = 1;
		i = 6;
		en[i].required = 1;
		i = 11;
		en[i].required = 1;
		i = 14;
		en[i].required = 1;
	}

	// �X�e�[�W���Ƃɏo��������G��ς���
	switch (stateStage) {
		// ���1�X�e�[�W
	case STATE_EP2STAGE1_1:
		i = 0;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 54;
		en[i].y = 40 * 55;
		EnemyDef2(i, en[i].entype);

		i = 1;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 14;
		en[i].y = 40 * 55;
		EnemyDef2(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 9;
		en[i].y = 40 * 55;
		EnemyDef2(i, en[i].entype);

		i = 3;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 14;
			en[i].y = 40 * 45;
			EnemyDef2(i, en[i].entype);
		}

		i = 4;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 9;
		en[i].y = 40 * 45;
		EnemyDef2(i, en[i].entype);

		i = 5;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 15;
		en[i].y = 40 * 25;
		EnemyDef2(i, en[i].entype);

		i = 6;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 10;
			en[i].y = 40 * 25;
			en[i].recipe_no = 5;
			EnemyDef2(i, en[i].entype);
		}

		break;
	case STATE_EP2STAGE1_2:

		i = 0;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 49;
		en[i].y = 40 * 49;
		EnemyDef2(i, en[i].entype);

		i = 1;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 49;
			en[i].y = 40 * 32;
			en[i].recipe_no = 4;
			EnemyDef2(i, en[i].entype);
		}

		i = 2;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 33;
		en[i].y = 40 * 33;
		EnemyDef2(i, en[i].entype);

		i = 3;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 33;
		en[i].y = 40 * 21;
		EnemyDef2(i, en[i].entype);

		i = 4;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 11;
		en[i].y = 40 * 33;
		EnemyDef2(i, en[i].entype);

		i = 5;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 11;
		en[i].y = 40 * 20;
		EnemyDef2(i, en[i].entype);

		break;
	case STATE_EP2STAGE1_3:

		i = 0;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 27;
			en[i].y = 40 * 19;
			EnemyDef2(i, en[i].entype);
		}

		i = 1;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 26;
		en[i].y = 40 * 22;
		EnemyDef2(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 29;
		en[i].y = 40 * 20;
		EnemyDef2(i, en[i].entype);

		i = 3;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 36;
		en[i].y = 40 * 14;
		EnemyDef2(i, en[i].entype);

		i = 4;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 48;
		en[i].y = 40 * 5;
		EnemyDef2(i, en[i].entype);

		i = 5;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 52;
			en[i].y = 40 * 5;
			EnemyDef2(i, en[i].entype);
		}

		i = 6;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 44;
		en[i].y = 40 * 8;
		EnemyDef2(i, en[i].entype);

		break;
	case STATE_EP2STAGE2_1:

		i = 0;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 7;
		en[i].y = 40 * 24;
		EnemyDef2(i, en[i].entype);

		i = 1;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 5;
		en[i].y = 40 * 28;
		EnemyDef2(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 10;
		en[i].y = 40 * 30;
		EnemyDef2(i, en[i].entype);

		i = 3;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 20;
		en[i].y = 40 * 24;
		EnemyDef2(i, en[i].entype);

		i = 4;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 22;
			en[i].y = 40 * 29;
			en[i].recipe_no = 6;
			EnemyDef2(i, en[i].entype);
		}

		i = 5;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 26;
		en[i].y = 40 * 22;
		EnemyDef2(i, en[i].entype);

		i = 6;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 35;
		en[i].y = 40 * 23;
		EnemyDef2(i, en[i].entype);

		i = 7;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 37;
		en[i].y = 40 * 26;
		EnemyDef2(i, en[i].entype);

		i = 8;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 40;
		en[i].y = 40 * 30;
		EnemyDef2(i, en[i].entype);

		i = 9;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 6;
		en[i].y = 40 * 39;
		EnemyDef2(i, en[i].entype);

		i = 10;
		en[i].entype = ENEMY_DIA;
		en[i].x = 40 * 9;
		en[i].y = 40 * 42;
		EnemyDef2(i, en[i].entype);

		i = 11;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 7;
			en[i].y = 40 * 45;
			EnemyDef2(i, en[i].entype);
		}

		i = 12;
		en[i].entype = ENEMY_CLOVER;
		en[i].x = 40 * 38;
		en[i].y = 40 * 39;
		EnemyDef2(i, en[i].entype);

		i = 13;
		en[i].entype = ENEMY_SPADE;
		en[i].x = 40 * 36;
		en[i].y = 40 * 43;
		EnemyDef2(i, en[i].entype);

		i = 14;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_HEART;
			en[i].x = 40 * 37;
			en[i].y = 40 * 45;
			EnemyDef2(i, en[i].entype);
		}

		break;
	case STATE_EP2STAGE2_2:
		break;
	case STATE_EP2STAGE_3:

		if (clearflag == 1) {
			i = 0;
			en[i].entype = ENEMY_QUEEN;
			en[i].x = 40 * 18;
			en[i].y = 40 * 8;
			EnemyDef2(i, en[i].entype);
		}

		if (en[0].use == 0) {
			i = 1;
			en[i].entype = ENEMY_MAD_HATTER2;
			en[i].x = 40 * 18;
			en[i].y = 40 * 8;
			EnemyDef2(i, en[i].entype);
		}

		break;
	default:
		break;
	}
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int CheckHitMapChipEnemy_2_1_1(int x, int y)
{
	if (stateStage == STATE_EP2STAGE1_1) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE2_1_1_W && 0 <= y && y < MAPSIZE2_1_1_H) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap_2_1_1[y *MAPSIZE2_1_1_W + x];
			int chip_no2 = nMaplm_2_1_1[y *MAPSIZE2_1_1_W + x];

			if (required_count < 3) {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					101,102,103,104,105,120,-1		// �Ō�
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// ��������
						return chip_no;
					}
					else if (chip_no2 == idtable[i]) {
						// ��������
						return chip_no2;
					}
					i++;
				}
			}
			else {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					101,103,104,105,120,-1		// �Ō�
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// ��������
						return chip_no;
					}
					i++;
				}
			}
		}

		// �������Ă��Ȃ�
		return 0;
	}
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int CheckHitMapChipEnemy_2_1_2(int x, int y)
{
	if (stateStage == STATE_EP2STAGE1_2) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE2_1_2_W && 0 <= y && y < MAPSIZE2_1_2_H) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap_2_1_2[y *MAPSIZE2_1_2_W + x];

			// ������ID���ǂ������`�F�b�N
			int idtable[] =
			{
				101,102,103,104,105,119,120,-1		// �Ō�
			};
			int i = 0;
			while (idtable[i] != -1) {
				if (chip_no == idtable[i]) {
					// ��������
					return chip_no;
				}
				i++;
			}
		}

		// �������Ă��Ȃ�
		return 0;
	}
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int CheckHitMapChipEnemy_2_1_3(int x, int y)
{
	if (stateStage == STATE_EP2STAGE1_3) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE2_1_3_W && 0 <= y && y < MAPSIZE2_1_3_H) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap_2_1_3[y *MAPSIZE2_1_3_W + x];
			int chip_no2 = nMaplm_2_1_3[y *MAPSIZE2_1_3_W + x];

			if (required_count < 8) {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					101,102,118,133,-1		// �Ō�
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// ��������
						return chip_no;
					}
					else if (chip_no2 == idtable[i]) {
						// ��������
						return chip_no2;
					}
					i++;
				}
			}
			else {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					101,118,133,-1		// �Ō�
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// ��������
						return chip_no;
					}
					i++;
				}
			}
		}

		// �������Ă��Ȃ�
		return 0;
	}
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int CheckHitMapChipEnemy_2_2_1(int x, int y)
{
	if (stateStage == STATE_EP2STAGE2_1) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE2_2_1_W && 0 <= y && y < MAPSIZE2_2_1_H) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap_2_2_1[y *MAPSIZE2_2_1_W + x];
			int chip_no2 = nMaplm_2_2_1[y *MAPSIZE2_2_1_W + x];

			if (required_count < 6) {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					101,102,118,119,-1		// �Ō�
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// ��������
						return chip_no;
					}
					else if (chip_no2 == idtable[i]) {
						// ��������
						return chip_no2;
					}
					i++;
				}
			}
			else {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					101,118,119,-1		// �Ō�
				};
				int i = 0;
				while (idtable[i] != -1) {
					if (chip_no == idtable[i]) {
						// ��������
						return chip_no;
					}
					i++;
				}
			}
		}

		// �������Ă��Ȃ�
		return 0;
	}
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int CheckHitMapChipEnemy_2_3(int x, int y)
{
	if (stateStage == STATE_EP2STAGE_3) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE2_3_W && 0 <= y && y < MAPSIZE2_3_H) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap_2_3[y *MAPSIZE2_3_W + x];
			// ������ID���ǂ������`�F�b�N
			int idtable[] =
			{
				101,-1		// �Ō�
			};
			int i = 0;
			while (idtable[i] != -1) {
				if (chip_no == idtable[i]) {
					// ��������
					return chip_no;
				}
				i++;
			}
		}

		// �������Ă��Ȃ�
		return 0;
	}
}

// �L�����ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//   i = �L�����ԍ�
//   mx = X�̈ړ�����(�}�C�i�X:0:�v���X)
//   my = Y�̈ړ�����(�}�C�i�X:0:�v���X)
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
int IsHitMapChipEnemy_2_1_1(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE1_1) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// ���̓G�͎g�p�����H
			if (en[i].use == 0)
			{	// ���g�p
				continue;
			}
			// �L������`���쐬����
			int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no = CheckHitMapChipEnemy_2_1_1(x, y);
					if (chip_no != 0) {	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// ���������̂Ŗ߂�
						return 1;
					}
				}
			}
		}
		// ������Ȃ�����
		return 0;
	}
}

// �L�����ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//   i = �L�����ԍ�
//   mx = X�̈ړ�����(�}�C�i�X:0:�v���X)
//   my = Y�̈ړ�����(�}�C�i�X:0:�v���X)
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
int IsHitMapChipEnemy_2_1_2(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE1_2) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// ���̓G�͎g�p�����H
			if (en[i].use == 0)
			{	// ���g�p
				continue;
			}
			// �L������`���쐬����
			int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no = CheckHitMapChipEnemy_2_1_2(x, y);
					if (chip_no != 0) {	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// ���������̂Ŗ߂�
						return 1;
					}
				}
			}
		}
		// ������Ȃ�����
		return 0;
	}
}

// �L�����ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//   i = �L�����ԍ�
//   mx = X�̈ړ�����(�}�C�i�X:0:�v���X)
//   my = Y�̈ړ�����(�}�C�i�X:0:�v���X)
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
int IsHitMapChipEnemy_2_1_3(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE1_3) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// ���̓G�͎g�p�����H
			if (en[i].use == 0)
			{	// ���g�p
				continue;
			}
			// �L������`���쐬����
			int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no = CheckHitMapChipEnemy_2_1_3(x, y);
					if (chip_no != 0) {	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// ���������̂Ŗ߂�
						return 1;
					}
				}
			}
		}
		// ������Ȃ�����
		return 0;
	}
}

// �L�����ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//   i = �L�����ԍ�
//   mx = X�̈ړ�����(�}�C�i�X:0:�v���X)
//   my = Y�̈ړ�����(�}�C�i�X:0:�v���X)
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
int IsHitMapChipEnemy_2_2_1(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE2_1) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// ���̓G�͎g�p�����H
			if (en[i].use == 0)
			{	// ���g�p
				continue;
			}
			// �L������`���쐬����
			int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no = CheckHitMapChipEnemy_2_2_1(x, y);
					if (chip_no != 0) {	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// ���������̂Ŗ߂�
						return 1;
					}
				}
			}
		}
		// ������Ȃ�����
		return 0;
	}
}

// �L�����ƃ}�b�v�`�b�v�������������̔���A����ѓ��������ꍇ�̏���
// �����F
//   i = �L�����ԍ�
//   mx = X�̈ړ�����(�}�C�i�X:0:�v���X)
//   my = Y�̈ړ�����(�}�C�i�X:0:�v���X)
// �ߒl�F
//   0 : �������ĂȂ�
//   1 : ��������
int IsHitMapChipEnemy_2_3(int i, int mx, int my)
{
	if (stateStage == STATE_EP2STAGE_3) {
		int x, y;

		for (i = 0; i < ENEMY_MAX; i++) {

			// ���̓G�͎g�p�����H
			if (en[i].use == 0)
			{	// ���g�p
				continue;
			}
			// �L������`���쐬����
			int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
			l = en[i].x + en[i].hit_x;
			t = en[i].y + en[i].hit_y;
			r = en[i].x + en[i].hit_x + en[i].hit_w - 1;
			b = en[i].y + en[i].hit_y + en[i].hit_h - 1;

			// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no = CheckHitMapChipEnemy_2_3(x, y);
					if (chip_no != 0) {	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
						}
						if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
						}
						// ���������̂Ŗ߂�
						return 1;
					}
				}
			}
		}
		// ������Ȃ�����
		return 0;
	}
}

// �G�l�~�[�ړ�(�X�e�[�W�Q)
void EnemyMove2()
{
	int i;
	int j = 0;

	// �ړ����t���O�ŋK��
	if ((selectTrg == STATE_NONE) && (check == STATE_NONE) && (GetRecipe < 1) && (wallwait == 0)) {
		for (i = 0; i < ENEMY_MAX; i++) {
			// ���̓G�͎g�p�����H
			if (en[i].use == 0)
			{	// ���g�p
				continue;
			}
			// �_���[�W��H����Ă��邩
			if ((en[i].damagecooltime <= 0) & (en[i].itemdamagecooltime <= 0) & (enatk[i].use == 0) & (en[i].state_enemy == 0)) {
				// �v���C���[���s���͈͂ɓ����Ă��Ȃ�
				if (en[i].state == STATE_NONE) {
					if (en[i].period > 0) {
						en[i].period--;
					}
					if (en[i].period > 0) {
						// ���Ɉړ�
						if (en[i].direction == ENEMY_STATE_RIGHT) {
							en[i].x -= en[i].spd;
						}
						// �E�Ɉړ�
						if (en[i].direction == ENEMY_STATE_LEFT) {
							en[i].x += en[i].spd;
						}
					}
					if (en[i].period2 > 0) {
						en[i].period2--;
					}
					if (en[i].period2 > 0) {
						// ��Ɉړ�
						if (en[i].direction == ENEMY_STATE_DOWN) {
							en[i].y -= en[i].spd;
						}
						// ���Ɉړ�
						if (en[i].direction == ENEMY_STATE_UP) {
							en[i].y += en[i].spd;
						}
					}
					if (en[i].period3 > 0) {
						en[i].period3--;
					}
					else {
						en[i].period3 = 360;
					}
					// ���Ɉړ�
					if (en[i].period3 > 240) {
						en[i].direction = ENEMY_STATE_DOWN;
						en[i].y += en[i].spd;
						IsHitMapChipEnemy_2_1_1(j, 0, 1);
						IsHitMapChipEnemy_2_1_2(j, 0, 1);
						IsHitMapChipEnemy_2_1_3(j, 0, 1);
						IsHitMapChipEnemy_2_2_1(j, 0, 1);
						IsHitMapChipEnemy_2_3(j, 0, 1);
					}
					// ��Ɉړ�
					else if (en[i].period3 < 180 & en[i].period3 > 60) {
						en[i].direction = ENEMY_STATE_UP;
						en[i].y -= en[i].spd;
						IsHitMapChipEnemy_2_1_1(j, 0, -1);
						IsHitMapChipEnemy_2_1_2(j, 0, -1);
						IsHitMapChipEnemy_2_1_3(j, 0, -1);
						IsHitMapChipEnemy_2_2_1(j, 0, -1);
						IsHitMapChipEnemy_2_3(j, 0, -1);
					}
					else if ((en[i].period3 < 240 & en[i].period3 > 180) || (en[i].period3 < 60 & en[i].period3 > 0)) {
						if (en[i].direction == ENEMY_STATE_DOWN) {
							IsHitMapChipEnemy_2_1_1(j, 0, 1);
							IsHitMapChipEnemy_2_1_2(j, 0, 1);
							IsHitMapChipEnemy_2_1_3(j, 0, 1);
							IsHitMapChipEnemy_2_2_1(j, 0, 1);
							IsHitMapChipEnemy_2_3(j, 0, 1);
						}
						else {
							IsHitMapChipEnemy_2_1_1(j, 0, -1);
							IsHitMapChipEnemy_2_1_2(j, 0, -1);
							IsHitMapChipEnemy_2_1_3(j, 0, -1);
							IsHitMapChipEnemy_2_2_1(j, 0, -1);
							IsHitMapChipEnemy_2_3(j, 0, -1);
						}
					}
				}
				// �v���C���[���s���͈͂ɓ�����
				if (en[i].state == STATE_ONE) {
					if ((en[i].direction == ENEMY_STATE_DOWN) ||
						(en[i].direction == ENEMY_STATE_UP) ||
						(en[i].direction == ENEMY_STATE_RIGHT) ||
						(en[i].direction == ENEMY_STATE_LEFT)) {
						if (en[i].period4 > 0) {
							en[i].period4--;
						}
						else {
							en[i].period4 = 20;

							Vector2 d;
							d.x = al.x - en[i].x;
							d.y = (al.y + 40) - en[i].y;
							Normalize(&d, &d);//����1�P�ʃx�N�g��
							MulVector(&d, &d, en[i].spd);//�X�s�[�h�̒����̃x�N�g��
							// x��y�̍������ׂ�
							if (d.x * d.x > d.y * d.y) {
								d.y = 0;
							}
							else {
								d.x = 0;
							}
							en[i].d = d;
						}
						if (en[i].d.x > 0) {
							// �E�Ɉړ�
							en[i].direction = ENEMY_STATE_RIGHT;
							en[i].x += en[i].d.x;
							IsHitMapChipEnemy_2_1_1(j, 1, 0);
							IsHitMapChipEnemy_2_1_2(j, 1, 0);
							IsHitMapChipEnemy_2_1_3(j, 1, 0);
							IsHitMapChipEnemy_2_2_1(j, 1, 0);
							IsHitMapChipEnemy_2_3(j, 1, 0);
						}
						else if (en[i].d.x < 0) {
							// ���Ɉړ�
							en[i].direction = ENEMY_STATE_LEFT;
							en[i].x += en[i].d.x;
							IsHitMapChipEnemy_2_1_1(j, -1, 0);
							IsHitMapChipEnemy_2_1_2(j, -1, 0);
							IsHitMapChipEnemy_2_1_3(j, -1, 0);
							IsHitMapChipEnemy_2_2_1(j, -1, 0);
							IsHitMapChipEnemy_2_3(j, -1, 0);
						}
						else if (en[i].d.y > 0) {
							// ���Ɉړ�
							en[i].direction = ENEMY_STATE_DOWN;
							en[i].y += en[i].d.y;
							IsHitMapChipEnemy_2_1_1(j, 0, 1);
							IsHitMapChipEnemy_2_1_2(j, 0, 1);
							IsHitMapChipEnemy_2_1_3(j, 0, 1);
							IsHitMapChipEnemy_2_2_1(j, 0, 1);
							IsHitMapChipEnemy_2_3(j, 0, 1);
						}
						else if (en[i].d.y < 0) {
							// ��Ɉړ�
							en[i].direction = ENEMY_STATE_UP;
							en[i].y += en[i].d.y;
							IsHitMapChipEnemy_2_1_1(j, 0, -1);
							IsHitMapChipEnemy_2_1_2(j, 0, -1);
							IsHitMapChipEnemy_2_1_3(j, 0, -1);
							IsHitMapChipEnemy_2_2_1(j, 0, -1);
							IsHitMapChipEnemy_2_3(j, 0, -1);
						}
					}
					AttackCooldinate2(i);	// �U������̍X�V
				}
			}
			// ���G�J�E���^�̏���
			if (en[i].nohit_cnt > 0) {
				en[i].nohit_cnt--;
			}
		}
	}
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �G�l�~�[�`��(�X�e�[�W�Q)
void DrawEnemy2() {
	int i;

	for (i = 0; i < ENEMY_MAX; i++) {
		// ���̓G�͎g�p�����H
		if (en[i].use == 0)
		{	// ���g�p
			continue;
		}
		en[i].anim_count++;
		// ���G���͈��Ԋu�ŕ`�悵�Ȃ�
		if (en[i].nohit_cnt == 0 || (en[i].nohit_cnt % 10) < 7)
		{
			// �G�̃^�C�v�ɂ���ĕ`���ς���
			switch (en[i].entype)
			{
			case ENEMY_HEART:
				// ������
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 120) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 160) - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[0 * 3 + hearttbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				// �����
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 160) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 120) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[1 * 3 + hearttbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				// �E����
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh((enatk[i].x + 120) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh((enatk[i].x + 160) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[3 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				// ������
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh((enatk[i].x + 160) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 120) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					else if (enemyattackCooltime >= 25) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgHeartAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[2 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgHeartF);
				}
				break;
			case ENEMY_DIA:
				// ������
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgDia[0 * 3 + diatbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				// �����
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[1 * 3 + hearttbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				// �E����
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[3 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				// ������
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgDiaAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHeart[2 * 3 + hearttbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgDiaF);
				}
				break;
			case ENEMY_CLOVER:
				// ������
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[0 * 3 + clovertbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				// �����
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[1 * 3 + clovertbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				// �E����
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[3 * 3 + clovertbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				// ������
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgCloverAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgClover[2 * 3 + clovertbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgCloverF);
				}
				break;
			case ENEMY_SPADE:
				// ������
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[0 * 3 + spadetbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				// �����
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[1 * 3 + spadetbl[(en[i].anim_count / 8) % 3]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				// �E����
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[3 * 3 + spadetbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				// ������
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgSpadeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgSpade[2 * 3 + spadetbl[(en[i].anim_count / 8) % 2]]);
					DrawMemTh(en[i].x - cv.view_x, en[i].y - 40 - cv.view_y, cgSpadeF);
				}
				break;
			case ENEMY_QUEEN:
				if (en[i].state_enemy == 0) {
					// ������
					if (en[i].direction == ENEMY_STATE_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[0 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}
					// �����
					if (en[i].direction == ENEMY_STATE_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[3 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}
					// �E����
					if (en[i].direction == ENEMY_STATE_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[2 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}
					// ������
					if (en[i].direction == ENEMY_STATE_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[1 * 4 + queentbl[(en[i].anim_count / 8) % 3]]);
					}

					// �U�����̕`��
					// ������
					if (en[i].direction == ENEMY_STATE_ATTACK_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[0 * 4 + queentbl[3]]);
					}
					// �����
					if (en[i].direction == ENEMY_STATE_ATTACK_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[3 * 4 + queentbl[3]]);
					}
					// �E����
					if (en[i].direction == ENEMY_STATE_ATTACK_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[2 * 4 + queentbl[3]]);
					}
					// ������
					if (en[i].direction == ENEMY_STATE_ATTACK_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgQueen[1 * 4 + queentbl[3]]);
					}
				}
				else {
					DrawMemTh(en[i].x - 20 - cv.view_x, en[i].y + 50 - cv.view_y, cgQueenDead);
				}
				break;
			case ENEMY_MAD_HATTER2:
				if (en[i].state_enemy == 0) {
					// ������
					if (en[i].direction == ENEMY_STATE_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[0 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}
					// �����
					if (en[i].direction == ENEMY_STATE_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[3 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}
					// �E����
					if (en[i].direction == ENEMY_STATE_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[2 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}
					// ������
					if (en[i].direction == ENEMY_STATE_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[1 * 4 + hattbl[(en[i].anim_count / 8) % 3]]);
					}

					// �U�����̕`��
					// ������
					if (en[i].direction == ENEMY_STATE_ATTACK_DOWN)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[0 * 4 + hattbl[3]]);
					}
					// �����
					if (en[i].direction == ENEMY_STATE_ATTACK_UP)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[3 * 4 + hattbl[3]]);
					}
					// �E����
					if (en[i].direction == ENEMY_STATE_ATTACK_RIGHT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[2 * 4 + hattbl[3]]);
					}
					// ������
					if (en[i].direction == ENEMY_STATE_ATTACK_LEFT)
					{
						DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgHatter[1 * 4 + hattbl[3]]);
					}
				}
				else {
					DrawMemTh(en[i].x - 20 - cv.view_x, en[i].y + 50 - cv.view_y, cgHatterDead);
				}
				break;
			default:
				break;
			}
		}
	}
}

// �G�̗͕̑`��(�{�X�̂݁A�X�e�[�W�Q)
void DrawEnemyHitpoint2() {
	switch (stateStage) {
	case STATE_EP2STAGE_3:
		// �n�[�g�̏���
		int i = 0;
		// �G�������Ă����
		if (en[i].use == 1) {
			if (en[i].state_enemy != 1) {
				RECT rc = { en[i].x - 40, en[i].y - 40, en[i].x + (320 - 240), en[i].y - 20 };		// left, top, right, bottom
				int w_max = rc.right - rc.left;		// �o�[�̉����T�C�Y

				// �܂����n�Ƃ��ĐԂœh��Ԃ�
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.right - cv.view_x, rc.bottom - cv.view_y, GetColor(255, 0, 0));

				// HP�ʂ̉����T�C�Y�͂������v�Z
				int w = LerpN(en[i].hp, en[i].max_hp, 0, w_max);

				// HP�ʂ�΂œh��Ԃ�
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.left + w - cv.view_x, rc.bottom - cv.view_y, GetColor(0, 192, 0));

				// ���l��\���i�e�����j
				//DrawPrintf(rc.left + 4 + 1 - cv.view_x, rc.top + 4 + 1 - cv.view_y, GetColor(0, 0, 0), "%d / %d", en[i].hp, en[i].max_hp);
				//DrawPrintf(rc.left + 4 - cv.view_x, rc.top + 4 - cv.view_y, GetColor(255, 255, 255), "%d / %d", en[i].hp, en[i].max_hp);
			}
		}
		
		// �}�b�h�n�b�^�[
		i = 1;
		if (en[i].use == 1) {
			if (en[i].state_enemy != 1) {
				RECT rc = { en[i].x - 40, en[i].y - 40, en[i].x + (320 - 240), en[i].y - 20 };		// left, top, right, bottom
				int w_max = rc.right - rc.left;		// �o�[�̉����T�C�Y

				// �܂����n�Ƃ��ĐԂœh��Ԃ�
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.right - cv.view_x, rc.bottom - cv.view_y, GetColor(255, 0, 0));

				// HP�ʂ̉����T�C�Y�͂������v�Z
				int w = LerpN(en[i].hp, en[i].max_hp, 0, w_max);

				// HP�ʂ�΂œh��Ԃ�
				DrawFBox(rc.left - cv.view_x, rc.top - cv.view_y, rc.left + w - cv.view_x, rc.bottom - cv.view_y, GetColor(0, 192, 0));

			}
		}
		break;
	}
}