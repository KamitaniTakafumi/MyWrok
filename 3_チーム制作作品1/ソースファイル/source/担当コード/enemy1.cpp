/*------------------------------------------------
*  @file enemy1.cpp
*  @brief �X�e�[�W�P�̃G�l�~�[����
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
#include	"mapdata_1.h"
#include	"HitJudgment.h"
#include	"enemyattack.h"
#include	"recipe.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

// �摜�f�[�^

int cgCaterpiller[3 * 4];			// ��
int cgMatango[2 * 4];				// �}�^���S
int mtngtbl[] = { 0, 1 };			// �`��e�[�u��(�}�^���S)
int catptbl[] = { 0, 1 };			// �`��e�[�u��(��)
int catpatctbl[] = { 2, 0 };		// �`��e�[�u��(�𒎍U��)
int cgMergematango[2 * 4];			// �}�[�W�}�^���S�U��
int Mmtngtbl[] = { 0, 1 };			// �`��e�[�u��(�}�[�W�}�^���S)
int cgWolf[3 * 4];					// �T
int wolftbl[] = { 0, 1, 2 };		// �`��e�[�u��(�T)
int cgHatter[4 * 4];				// �}�b�h�n�b�^�[
int hattbl[] = { 0, 1, 2, 3 };		// �`��e�[�u��(�}�b�h�n�b�^�[)
int cgMatangeAttack;				// �}�^���S�U��
int cgWolfAttack[3 * 1];			// �T�U��
int wolfattacktbl[] = { 0, 1, 2 };	// �`��e�[�u��(�T�U��)

// �G�l�~�[���
struct ENEMY en[ENEMY_MAX];

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// �G�摜�̓ǂݍ���
void LoadCgEnemy()
{
	cgMatangeAttack = LoadTexture("res/matango_spore.png");
	LoadBlkTexture("res/wolf_attack.png", 40, 40, 3, 1, 3 * 1, cgWolfAttack);
	LoadBlkTexture("res/caterpillar.png", 40, 40, 3, 4, 3 * 4, cgCaterpiller);
	LoadBlkTexture("res/matango_sheet.png", 40, 60, 2, 4, 2 * 4, cgMatango);
	LoadBlkTexture("res/merge_matango_sheet.png", 40, 60, 2, 4, 2 * 4, cgMergematango);
	LoadBlkTexture("res/wolf.png", 60, 60, 3, 4, 3 * 4, cgWolf);
	LoadBlkTexture("res/madhatter_sheet.png", 40, 80, 4, 4, 4 * 4, cgHatter);
}

/*
*  @brief �G�̊�{���
*  @param enemyId �G�̎��ʔԍ�
*  @param enemytype �G�̎��
*/
void EnemyDef(int enemyId, int enemytype) {
	// �G�̎�ނ��Ƃɏ���������
	switch (enemytype) {
	case ENEMY_CATERPILLAR:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 40;
		en[enemyId].spd = 1;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 0;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 1;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_MATANGO:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 60;
		en[enemyId].spd = 3;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 3;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_MERGE_MATANGO:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 60;
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
		en[enemyId].required = 0;
		break;
	case ENEMY_WOLF:
		en[enemyId].use = 1;
		en[enemyId].w = 60;
		en[enemyId].h = 60;
		en[enemyId].spd = 4;
		en[enemyId].hit_x = 10;
		en[enemyId].hit_y = 20;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -240;
		en[enemyId].hit_range_y = -240;
		en[enemyId].hit_range_w = 520;
		en[enemyId].hit_range_h = 520;
		en[enemyId].hp = 3;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	case ENEMY_MAD_HATTER:
		en[enemyId].use = 1;
		en[enemyId].w = 40;
		en[enemyId].h = 80;
		en[enemyId].spd = 4;
		en[enemyId].hit_x = 0;
		en[enemyId].hit_y = 40;
		en[enemyId].hit_w = 40;
		en[enemyId].hit_h = 40;
		en[enemyId].hit_range_x = -800;
		en[enemyId].hit_range_y = -800;
		en[enemyId].hit_range_w = 1640;
		en[enemyId].hit_range_h = 1640;
		en[enemyId].hp = 50;
		en[enemyId].max_hp = 50;
		en[enemyId].damage_point = 0;
		en[enemyId].damage_critical_point = 0;
		break;
	}
}

// �G�l�~�[������
void InitEnemy()
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
	// �X�e�[�W���Ƃɏo��������G��ς���
	switch (stateStage) {
	case STATE_EP1STAGE:
		i = 0;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 1640;
		en[i].y = 760;
		EnemyDef(i, en[i].entype);

		i = 1;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 1640;
		en[i].y = 240;
		EnemyDef(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 2080;
		en[i].y = 160;
		EnemyDef(i, en[i].entype);

		break;
	case STATE_EP1STAGE_2:
		i = 0;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 2040;
		en[i].y = 1560;
		EnemyDef(i, en[i].entype);

		i = 1;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 1440;
		en[i].y = 1840;
		EnemyDef(i, en[i].entype);

		i = 2;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 960;
		en[i].y = 1760;
		EnemyDef(i, en[i].entype);

		i = 3;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 2240;
		en[i].y = 1200;
		EnemyDef(i, en[i].entype);

		i = 4;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 2000;
		en[i].y = 920;
		EnemyDef(i, en[i].entype);

		i = 5;
		en[i].entype = ENEMY_WOLF;
		en[i].x = 1240;
		en[i].y = 800;
		EnemyDef(i, en[i].entype);

		i = 6;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 720;
		en[i].y = 1200;
		EnemyDef(i, en[i].entype);

		i = 7;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_MERGE_MATANGO;
			en[i].x = 40 * 43;
			en[i].y = 40 * 29;
			en[i].recipe_no = 1;
			EnemyDef(i, en[i].entype);
		}

		i = 8;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 240;
		en[i].y = 920;
		EnemyDef(i, en[i].entype);

		i = 9;
		en[i].entype = ENEMY_WOLF;
		en[i].x = 360;
		en[i].y = 280;
		EnemyDef(i, en[i].entype);

		i = 10;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 880;
		en[i].y = 560;
		EnemyDef(i, en[i].entype);

		i = 11;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 1400;
		en[i].y = 440;
		EnemyDef(i, en[i].entype);

		i = 12;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_MERGE_MATANGO;
			en[i].x = 1520;
			en[i].y = 240;
			en[i].recipe_no = 2;
			EnemyDef(i, en[i].entype);
		}

		break;
	case STATE_EP1STAGE_3:
		i = 0;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 800;
		en[i].y = 1640;
		EnemyDef(i, en[i].entype);

		i = 1;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 640;
		en[i].y = 1920;
		EnemyDef(i, en[i].entype);

		i = 2;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_MERGE_MATANGO;
			en[i].x = 440;
			en[i].y = 2240;
			en[i].recipe_no = 3;
			EnemyDef(i, en[i].entype);
		}

		i = 3;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 240;
		en[i].y = 1720;
		EnemyDef(i, en[i].entype);

		i = 4;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 680;
		en[i].y = 1320;
		EnemyDef(i, en[i].entype);

		i = 5;
		en[i].entype = ENEMY_WOLF;
		en[i].x = 1520;
		en[i].y = 1160;
		EnemyDef(i, en[i].entype);

		i = 6;
		en[i].entype = ENEMY_WOLF;
		en[i].x = 1880;
		en[i].y = 640;
		EnemyDef(i, en[i].entype);

		i = 7;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 2120;
		en[i].y = 920;
		EnemyDef(i, en[i].entype);

		i = 8;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 2600;
		en[i].y = 880;
		EnemyDef(i, en[i].entype);

		i = 9;
		en[i].entype = ENEMY_MATANGO;
		en[i].x = 2440;
		en[i].y = 160;
		EnemyDef(i, en[i].entype);

		i = 10;
		if (en[i].required == 1) {
			en[i].use = 0;
		}
		else {
			en[i].entype = ENEMY_MERGE_MATANGO;
			en[i].x = 2280;
			en[i].y = 240;
			EnemyDef(i, en[i].entype);
		}

		i = 11;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 1800;
		en[i].y = 200;
		EnemyDef(i, en[i].entype);

		i = 12;
		en[i].entype = ENEMY_WOLF;
		en[i].x = 1240;
		en[i].y = 200;
		EnemyDef(i, en[i].entype);

		i = 13;
		en[i].entype = ENEMY_CATERPILLAR;
		en[i].x = 1080;
		en[i].y = 680;
		EnemyDef(i, en[i].entype);

		break;
	case STATE_EP1STAGE_4:
		i = 0;
		en[i].entype = ENEMY_MAD_HATTER;
		en[i].x = 720;
		en[i].y = 440;
		EnemyDef(i, en[i].entype);

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
int CheckHitMapChipEnemy(int x, int y)
{
	if (stateStage == STATE_EP1STAGE) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W && 0 <= y && y < MAPSIZE_H)
		{	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap[y *MAPSIZE_W + x];

			// ������ID���ǂ������`�F�b�N
			int idtable[] =
			{
				103,-1		// �Ō�
			};
			int i = 0;
			while (idtable[i] != -1)
			{
				if (chip_no == idtable[i])
				{
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
int CheckHitMapChipEnemy2(int x, int y)
{
	if (stateStage == STATE_EP1STAGE_2) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W_2 && 0 <= y && y < MAPSIZE_H_2)
		{	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap2[y *MAPSIZE_W_2 + x];

			// ������ID���ǂ������`�F�b�N
			int idtable[] =
			{
				251,-1		// �Ō�
			};
			int i = 0;
			while (idtable[i] != -1)
			{
				if (chip_no == idtable[i])
				{
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
int CheckHitMapChipEnemy3(int x, int y)
{
	if (stateStage == STATE_EP1STAGE_3) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W_3 && 0 <= y && y < MAPSIZE_H_3)
		{	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap3[y *MAPSIZE_W_3 + x];

			// ������ID���ǂ������`�F�b�N
			int idtable[] =
			{
				101,-1		// �Ō�
			};
			int i = 0;
			while (idtable[i] != -1)
			{
				if (chip_no == idtable[i])
				{
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
int CheckHitMapChipEnemy4(int x, int y)
{
	if (stateStage == STATE_EP1STAGE_4) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W_4 && 0 <= y && y < MAPSIZE_H_4)
		{	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap4[y *MAPSIZE_W_4 + x];

			// ������ID���ǂ������`�F�b�N
			int idtable[] =
			{
				101,-1		// �Ō�
			};
			int i = 0;
			while (idtable[i] != -1)
			{
				if (chip_no == idtable[i])
				{
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
int IsHitMapChipEnemy(int i, int mx, int my)
{
	if (stateStage == STATE_EP1STAGE) {
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
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
			{
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
				{
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no = CheckHitMapChipEnemy(x, y);
					if (chip_no != 0)
					{	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0)
						{	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0)
						{	// �E�ɓ����Ă����̂ŁA���ɕ␳
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0)
						{	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
						}
						if (my < 0)
						{	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
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
int IsHitMapChipEnemy2(int i, int mx, int my)
{
	if (stateStage == STATE_EP1STAGE_2) {
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
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
			{
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
				{
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no2 = CheckHitMapChipEnemy2(x, y);
					if (chip_no2 != 0)
					{	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0)
						{	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0)
						{	// �E�ɓ����Ă����̂ŁA���ɕ␳
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0)
						{	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
						}
						if (my < 0)
						{	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
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
int IsHitMapChipEnemy3(int i, int mx, int my)
{
	if (stateStage == STATE_EP1STAGE_3) {
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
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
			{
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
				{
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no3 = CheckHitMapChipEnemy3(x, y);
					if (chip_no3 != 0)
					{	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0)
						{	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0)
						{	// �E�ɓ����Ă����̂ŁA���ɕ␳
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0)
						{	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
						}
						if (my < 0)
						{	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
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
int IsHitMapChipEnemy4(int i, int mx, int my)
{
	if (stateStage == STATE_EP1STAGE_4) {
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
			for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
			{
				for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
				{
					// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
					// ���̈ʒu�̃`�b�v�͓����邩�H
					int chip_no4 = CheckHitMapChipEnemy4(x, y);
					if (chip_no4 != 0)
					{	// ���̃`�b�v�Ɠ��������B
						// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
						if (mx < 0)
						{	// ���ɓ����Ă����̂ŁA�E�ɕ␳
							if (en[i].period3 > 0) {
								en[i].period3 = 0;
							}
							en[i].x = x * CHIPSIZE_W + CHIPSIZE_W - (en[i].hit_x);
						}
						if (mx > 0)
						{	// �E�ɓ����Ă����̂ŁA���ɕ␳
							if (en[i].period3 < 180 & en[i].period3 > 60) {
								en[i].period3 = 180;
							}
							en[i].x = x * CHIPSIZE_W - (en[i].hit_x + en[i].hit_w);
						}
						if (my > 0)
						{	// ���ɓ����Ă����̂ŁA��ɕ␳
							en[i].y = y * CHIPSIZE_H - (en[i].hit_y + en[i].hit_h);
						}
						if (my < 0)
						{	// ��ɓ����Ă����̂ŁA���ɕ␳
							en[i].y = y * CHIPSIZE_H + CHIPSIZE_H - (en[i].hit_y);
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

// �G�l�~�[�ړ�
void EnemyMove()
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
					// �E�Ɉړ�
					if (en[i].period3 > 240) {
						en[i].direction = ENEMY_STATE_RIGHT;
						en[i].x += en[i].spd;
						IsHitMapChipEnemy(j, 1, 0);
						IsHitMapChipEnemy2(j, 1, 0);
						IsHitMapChipEnemy3(j, 1, 0);
						IsHitMapChipEnemy4(j, 1, 0);
					}
					// ���Ɉړ�
					else if(en[i].period3 < 180 & en[i].period3 > 60){
						en[i].direction = ENEMY_STATE_LEFT;
						en[i].x -= en[i].spd;
						IsHitMapChipEnemy(j, -1, 0);
						IsHitMapChipEnemy2(j, -1, 0);
						IsHitMapChipEnemy3(j, -1, 0);
						IsHitMapChipEnemy4(j, -1, 0);
					}
					else if ((en[i].period3 < 240 & en[i].period3 > 180) || (en[i].period3 < 60 & en[i].period3 > 0)) {
						if (en[i].direction == ENEMY_STATE_RIGHT) {
							IsHitMapChipEnemy(j, 1, 0);
							IsHitMapChipEnemy2(j, 1, 0);
							IsHitMapChipEnemy3(j, 1, 0);
							IsHitMapChipEnemy4(j, 1, 0);
						}
						else {
							IsHitMapChipEnemy(j, -1, 0);
							IsHitMapChipEnemy2(j, -1, 0);
							IsHitMapChipEnemy3(j, -1, 0);
							IsHitMapChipEnemy4(j, -1, 0);
						}
					}
					AttackCooldinate(i);	// �U������̍X�V
				}
				// �v���C���[���s���͈͂ɓ�����
				if (en[i].state == STATE_ONE) {
					if ((en[i].direction == ENEMY_STATE_DOWN) ||
						(en[i].direction == ENEMY_STATE_UP) ||
						(en[i].direction == ENEMY_STATE_RIGHT) ||
						(en[i].direction == ENEMY_STATE_LEFT)) {
						if (en[i].period4 > 0){
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
							IsHitMapChipEnemy(j, 1, 0);
							IsHitMapChipEnemy2(j, 1, 0);
							IsHitMapChipEnemy3(j, 1, 0);
							IsHitMapChipEnemy4(j, 1, 0);
						}
						else if (en[i].d.x < 0) {
							// ���Ɉړ�
							en[i].direction = ENEMY_STATE_LEFT;
							en[i].x += en[i].d.x;
							IsHitMapChipEnemy(j, -1, 0);
							IsHitMapChipEnemy2(j, -1, 0);
							IsHitMapChipEnemy3(j, -1, 0);
							IsHitMapChipEnemy4(j, -1, 0);
						}
						else if (en[i].d.y > 0) {
							// ���Ɉړ�
							en[i].direction = ENEMY_STATE_DOWN;
							en[i].y += en[i].d.y;
							IsHitMapChipEnemy(j, 0, 1);
							IsHitMapChipEnemy2(j, 0, 1);
							IsHitMapChipEnemy3(j, 0, 1);
							IsHitMapChipEnemy4(j, 0, 1);
						}
						else if (en[i].d.y < 0) {
							// ��Ɉړ�
							en[i].direction = ENEMY_STATE_UP;
							en[i].y += en[i].d.y;
							IsHitMapChipEnemy(j, 0, -1);
							IsHitMapChipEnemy2(j, 0, -1);
							IsHitMapChipEnemy3(j, 0, -1);
							IsHitMapChipEnemy4(j, 0, -1);
						}
					}
					AttackCooldinate(i);	// �U������̍X�V
				}
			}
			// ���G�J�E���^�̏���
			if (en[i].nohit_cnt > 0){
				en[i].nohit_cnt--;
			}
		}
	}
}

// �����蔻����s�����H
// �Ԓl�F
//   1 = �s��
//   0 = �s��Ȃ�
int IsHitProcessEnemy(int enemyId)
{
	if (en[enemyId].use == STATE_NONE) { return 0; }
	if (en[enemyId].nohit_cnt >= 20) { return 0; }
	return 1;
}

// ���`�⊮�ɂ�铙���ړ�
// start -> end �ɒl�������ꍇ�A cnt/max ���̈ʒu��Ԃ�
int LerpN(int cnt, int max, int start, int end) {
	int n;
	if (cnt >= max) {
		n = end;
	}
	else {
		n = (start + (end - start) * cnt / max);
	}
	return (int)n;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �G�l�~�[�`��
void DrawEnemy() {
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
			case ENEMY_CATERPILLAR:
				// ������
				if (en[i].direction == ENEMY_STATE_DOWN)
				{
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[2 * 3 + catptbl[(en[i].anim_count / 8) % 2]]);
				}
				// �����
				if (en[i].direction == ENEMY_STATE_UP)
				{
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[0 * 3 + catptbl[(en[i].anim_count / 8) % 2]]);
				}
				// �E����
				if (en[i].direction == ENEMY_STATE_RIGHT)
				{
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[1 * 3 + catptbl[(en[i].anim_count / 8) % 2]]);
				}
				// ������
				if (en[i].direction == ENEMY_STATE_LEFT)
				{
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[3 * 3 + catptbl[(en[i].anim_count / 8) % 2]]);
				}
				if ((enatk[i].attack_time >= 0) & (en[i].direction == ENEMY_STATE_ATTACK_DOWN)) {
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[2 * 3 + catpatctbl[(en[i].anim_count / 8) % 3]]);
				}
				if ((enatk[i].attack_time >= 0) & (en[i].direction == ENEMY_STATE_ATTACK_UP)) {
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[0 * 3 + catpatctbl[(en[i].anim_count / 8) % 3]]);
				}
				if ((enatk[i].attack_time >= 0) & (en[i].direction == ENEMY_STATE_ATTACK_RIGHT)) {
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[1 * 3 + catpatctbl[(en[i].anim_count / 8) % 3]]);
				}
				if ((enatk[i].attack_time >= 0) & (en[i].direction == ENEMY_STATE_ATTACK_LEFT)) {
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgCaterpiller[3 * 3 + catpatctbl[(en[i].anim_count / 8) % 3]]);
				}
				break;
			case ENEMY_MATANGO:
				// ������
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMatango[0 * 2 + mtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				// �����
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMatango[3 * 2 + mtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				// �E����
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMatango[2 * 2 + mtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				// ������
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMatango[1 * 2 + mtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				break;
			case ENEMY_MERGE_MATANGO:
				// ������
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 120) - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMergematango[0 * 2 + Mmtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				// �����
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 120) - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 80) - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh(enatk[i].x - cv.view_x, (enatk[i].y + 40) - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMergematango[3 * 2 + Mmtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				// �E����
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh((enatk[i].x + 120) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMergematango[2 * 2 + Mmtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				// ������
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 29) {
						DrawMemTh((enatk[i].x + 120) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 28) {
						DrawMemTh((enatk[i].x + 80) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 27) {
						DrawMemTh((enatk[i].x + 40) - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgMatangeAttack);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgMergematango[1 * 2 + Mmtngtbl[(en[i].anim_count / 8) % 2]]);
				}
				break;
			case ENEMY_WOLF:
				// ������
				if ((en[i].direction == ENEMY_STATE_DOWN) || (en[i].direction == ENEMY_STATE_ATTACK_DOWN))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[0]]);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[1]]);
					}
					else if (enemyattackCooltime >= 24) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[2]]);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgWolf[0 * 3 + wolftbl[(en[i].anim_count / 8) % 3]]);
				}
				// �����
				if ((en[i].direction == ENEMY_STATE_UP) || (en[i].direction == ENEMY_STATE_ATTACK_UP))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[0]]);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[1]]);
					}
					else if (enemyattackCooltime >= 24) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[2]]);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgWolf[3 * 3 + wolftbl[(en[i].anim_count / 8) % 3]]);
				}
				// �E����
				if ((en[i].direction == ENEMY_STATE_RIGHT) || (en[i].direction == ENEMY_STATE_ATTACK_RIGHT))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[0]]);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[1]]);
					}
					else if (enemyattackCooltime >= 24) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[2]]);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgWolf[2 * 3 + wolftbl[(en[i].anim_count / 8) % 3]]);
				}
				// ������
				if ((en[i].direction == ENEMY_STATE_LEFT) || (en[i].direction == ENEMY_STATE_ATTACK_LEFT))
				{
					if (enemyattackCooltime >= 28) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[0]]);
					}
					else if (enemyattackCooltime >= 26) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[1]]);
					}
					else if (enemyattackCooltime >= 24) {
						DrawMemTh(enatk[i].x - cv.view_x, enatk[i].y - cv.view_y, cgWolfAttack[0 * 3 + wolfattacktbl[2]]);
					}
					DrawMemTh(en[i].x - cv.view_x, en[i].y - cv.view_y, cgWolf[1 * 3 + wolftbl[(en[i].anim_count / 8) % 3]]);
				}
				break;
			case ENEMY_MAD_HATTER:
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

				break;
			default:
				break;
			}
		}
	}
}

// �G�̗͕̑`��(�{�X�̂�)
void DrawEnemyHitpoint() {
	switch (stateStage) {
	case STATE_EP1STAGE_4:
		int i = 0;
		// �G�������Ă����
		if (en[i].use == 1) {
			if (en[i].state_enemy != 1) {
				RECT rc = { en[i].x - 40, en[i].y - 20, en[i].x + (320 - 240), en[i].y };		// left, top, right, bottom
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