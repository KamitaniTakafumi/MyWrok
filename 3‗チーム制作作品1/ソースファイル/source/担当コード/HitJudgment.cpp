/*------------------------------------------------
*  @file HitJudgment.cpp
*  @brief �����蔻�菈��
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �w�b�_�[�t�@�C���̃C���N���[�h
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
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int selectTrg = STATE_NONE;		// �L�[���͂̔���
int flag = STATE_NONE;			// �q�b�g�������̔���t���O

// SE�f�[�^

int seCursor;		// �J�[�\��
int seSelect;		// �Z���N�g
int seCancel;		// �L�����Z��
int seGetPlant;		// �A�C�e���Q�b�g(�؂̎��n)
int seGetRock;		// �A�C�e���Q�b�g(��n)
int seGetWater;		// �A�C�e���Q�b�g(���n)
int seGetPickup;	// �E��
int seCreateItem;	// �A�C�e������
int seAliceAttack;	// �v���C���[�U��
int seAliceDamage;	// �v���C���[�_���[�W
int seEnemyDamage;	// �G�l�~�[�_���[�W
int seDead;			// ���S
int seRecovery;		// ��
int seOpen;			// �I�[�v��
int seMove;			// �X�e�[�W�ړ�
int seWalk1;		// ����(�X�e�[�W�P)
int seWalk2;		// ����(�X�e�[�W�Q)
int seBomb;			// �{��
int seBomb2;		// �{���Q
int seRecipe;		// ���V�s
int seFlash;		// �Ђ�߂�
int seWallBreak;	// �ǔj��
int seBoom;			// �l�C
int seBladesound;	// �n
int seFootstep;		// ����(����)
int seFootstep_run;	// ����(����)
int seGetaway;		// ������
int seOpendoor;		// �J����
int seShock;		// �Ռ�
int seSlashsound;	// �a��
int seRun;			// ����
int seFootstep_heel;// ����(�q�[��)

// BGM�f�[�^
int bgmTitle;		// �^�C�g��
int bgmOp01;		// �I�[�v�j���O�P
int bgmOp02;		// �I�[�v�j���O�Q
int bgmOp03;		// �I�[�v�j���O�R
int I_home;			// �X�g�[���[�}���ȂP
int DCF;			// �X�g�[���[�}���ȂQ
int Lucifer;		// �X�g�[���[�}���ȂR
int cheshirebgm;	// �X�g�[���[�}���ȂS
int Assault;		// �X�g�[���[�}���ȂT
int Be_quiet;		// �X�g�[���[�}���ȂU
int cheshirebgm2;	// �X�g�[���[�}���ȂV
int loneliness;		// �X�g�[���[�}���ȂW
int midnightmoon;	// �X�g�[���[�}���ȂX
int queenbgm;		// �X�g�[���[�}���ȂP�O
int queenbgm2;		// �X�g�[���[�}���ȂP�P
int madhatterbgm;	// �X�g�[���[�}���ȂP�Q
int reddress;		// �X�g�[���[�}���ȂP�R
int reunion;		// �X�g�[���[�}���ȂP�S
int dustwall;		// �X�g�[���[�}���ȂP�T
int farewell;		// �X�g�[���[�}���ȂP�U
int BGMSilent;		// �X�g�[���[�}���ȂP�V
int Inherited_Hope;	// �X�g�[���[�}���ȂP�W
int bgmMap1;		// �X�e�[�W�P
int bgmMap2;		// �X�e�[�W�Q
int bgmBoss1;		// �{�X�P
int bgmBoss2;		// �{�X�Q
int bgmBoss3;		// �{�X�R
int bgmEnd;			// �G���f�B���O

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
// SE�̓ǂݍ���
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

// BGM�̓ǂݍ���
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
*  �X�V
-------------------------------------------------*/

// �����蔻��p�B2��box�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitBox(
	int x1, int y1, int w1, int h1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
	int x2, int y2, int w2, int h2		// �ӂ��߂�box ����(x,y), �傫��w,h
)
{
	if (x1 < x2 + w2 && x2 < x1 + w1		// x�����̔���
		&& y1 < y2 + h2 && y2 < y1 + h1		// y�����̔���
		)
	{
		// 2��box�͓������Ă���
		return 1;
	}

	// 2��box�͓������Ă��Ȃ�
	return 0;
}

// �����蔻��p 2��box�������������𔻒�
// distance�ł��̕�����Ă��Ă�������悤�ɂ��邱�Ƃ��ł���
int IsHitBoxDistance(int x1, int y1, int x2, int y2, int distance) {
	return (abs(x1 - x2) < distance) && (abs(y1 - y2) < distance);
}

// �����蔻��F�v���C���[�ƓG
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG(�s���͈�)
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƒ�����
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƒ�����
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�G�ƒ�����(���S�͈�)
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�U���ƓG
// �������Ă�����enemyId, �������Ă��Ȃ�������-1��Ԃ�
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

// �����蔻��F�v���C���[�A�C�e���U���ƓG
// �������Ă�����enemyId, �������Ă��Ȃ�������-1��Ԃ�
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

// �����蔻��F�v���C���[�ƃI�u�W�F�N�g
// �������Ă�����objectId, �������Ă��Ȃ�������-1��Ԃ�
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

// �����蔻��F�v���C���[�ƃI�u�W�F�N�g
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �����蔻��F�v���C���[�ƃh���b�v�A�C�e��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
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

// �v���C���[�ƓG�̓����菈��
void HitCheckPlayerEnemy() {
	// ��l���̓����蔻����s�����H
	if (IsHitProcessPlayer() == 0) { return; }

	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// ���̓G�͎g�p�����H
		if (en[i].use == 0)
		{	// ���g�p
			continue;
		}
		if (IsHitPlayerEnemy(i) != 0) {
			if (check == STATE_NONE) {
				PlayMemBack(seAliceDamage);		// SE�Đ�
				al.hitpoint--;					// �̗͂����炷
			}
			if (al.hitpoint <= 0) {
				PlayMemBack(seDead);	// SE�Đ�
				// 60�t���[���̃Q�[���I�[�o�[�܂ł̊�
				gGameoverCount = 60;	// �Q�[���I�[�o�[�܂ł̎���

				// ��l����s�g�p�Ƃ���
				al.use = 0;

				// BGM�Đ��X�g�b�v
				StopPlayMem(bgmMap1); 
				StopPlayMem(bgmMap2);
				StopPlayMem(bgmBoss1);
				StopPlayMem(bgmBoss2);
				StopPlayMem(bgmBoss3);
			}
			else {
				al.nohit_cnt = 60;		// ���G���Ԑݒ�
			}
		}
	}
}

// �v���C���[�ƓG(�s���͈�)�̓����菈��
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

// �v���C���[�ƓG�U���̓����菈��
void HitCheckEnemyAttack() {
	// ��l���̓����蔻����s�����H
	if (IsHitProcessPlayer() == 0) { return; }

	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// ���̓G�͎g�p�����H
		if (en[i].use == 0)
		{	// ���g�p
			continue;
		}
		if (enatk[i].rand == 0) {
			if (en[i].entype == ENEMY_QUEEN) {
				if (IsHitEnemyAttackRange4(i) != 0) {
					if (check == STATE_NONE) {
						PlayMemBack(seAliceDamage);		// SE�Đ�
						al.hitpoint--;					// �̗͂����炷
					}
					if (al.hitpoint <= 0) {
						PlayMemBack(seDead);	// SE�Đ�
						// 60�t���[���̃Q�[���I�[�o�[�܂ł̊�
						gGameoverCount = 60;	// �Q�[���I�[�o�[�܂ł̎���

						// ��l����s�g�p�Ƃ���
						al.use = 0;

						// BGM�Đ��X�g�b�v
						StopPlayMem(bgmMap1);
						StopPlayMem(bgmMap2);
						StopPlayMem(bgmBoss1);
						StopPlayMem(bgmBoss2);
						StopPlayMem(bgmBoss3);
					}
					else {
						al.nohit_cnt = 60;		// ���G���Ԑݒ�
					}
				}
			}
			else if (IsHitEnemyAttackRange(i) != 0) {
				if (check == STATE_NONE) {
					PlayMemBack(seAliceDamage);		// SE�Đ�
					al.hitpoint--;					// �̗͂����炷
				}
				if (al.hitpoint <= 0) {
					PlayMemBack(seDead);	// SE�Đ�
					// 60�t���[���̃Q�[���I�[�o�[�܂ł̊�
					gGameoverCount = 60;	// �Q�[���I�[�o�[�܂ł̎���

					// ��l����s�g�p�Ƃ���
					al.use = 0;

					// BGM�Đ��X�g�b�v
					StopPlayMem(bgmMap1);
					StopPlayMem(bgmMap2);
					StopPlayMem(bgmBoss1);
					StopPlayMem(bgmBoss2);
					StopPlayMem(bgmBoss3);
				}
				else {
					al.nohit_cnt = 60;		// ���G���Ԑݒ�
				}
			}
		}
		else if (enatk[i].rand == 1) {
			if (IsHitEnemyAttackRange2(i) != 0) {
				if (check == STATE_NONE) {
					PlayMemBack(seAliceDamage);		// SE�Đ�
					al.hitpoint--;					// �̗͂����炷
				}
				if (al.hitpoint <= 0) {
					PlayMemBack(seDead);	// SE�Đ�
					// 60�t���[���̃Q�[���I�[�o�[�܂ł̊�
					gGameoverCount = 60;	// �Q�[���I�[�o�[�܂ł̎���

					// ��l����s�g�p�Ƃ���
					al.use = 0;

					// BGM�Đ��X�g�b�v
					StopPlayMem(bgmMap1);
					StopPlayMem(bgmMap2);
					StopPlayMem(bgmBoss1);
					StopPlayMem(bgmBoss2);
					StopPlayMem(bgmBoss3);
				}
				else {
					al.nohit_cnt = 60;		// ���G���Ԑݒ�
				}
			}
		}
		else if (enatk[i].rand == 2) {
			if (IsHitEnemyAttackRange3(i) != 0) {
				if (check == STATE_NONE) {
					PlayMemBack(seAliceDamage);		// SE�Đ�
					al.hitpoint--;					// �̗͂����炷
				}
				if (al.hitpoint <= 0) {
					PlayMemBack(seDead);	// SE�Đ�
					// 60�t���[���̃Q�[���I�[�o�[�܂ł̊�
					gGameoverCount = 60;	// �Q�[���I�[�o�[�܂ł̎���

					// ��l����s�g�p�Ƃ���
					al.use = 0;

					// BGM�Đ��X�g�b�v
					StopPlayMem(bgmMap1);
					StopPlayMem(bgmMap2);
					StopPlayMem(bgmBoss1);
					StopPlayMem(bgmBoss2);
					StopPlayMem(bgmBoss3);
				}
				else {
					al.nohit_cnt = 60;		// ���G���Ԑݒ�
				}
			}
		}
	}
}

// �v���C���[�̍U���ƓG�̓����菈��
void HitCheckPlayerAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// ���̓G�͎g�p�����H
		if (en[i].use == 0)
		{	// ���g�p
			continue;
		}
		// �G�̓����蔻����s�����H
		if (IsHitProcessEnemy(i) == 0) { return; }

		if ((en[i].nohit_cnt <= 0) & (en[i].state_enemy != 1)) {
			if (IsHitPlayerAttack(i) != -1) {
				// �_���[�W���󂯂���
				if (en[i].damagecooltime <= 0) {
					PlayMemBack(seEnemyDamage);		// SE�Đ�
					en[i].damagecooltime = 10;		// �U�����󂯂����̑҂�����
					enatk[i].select_attack = 0;		// �U���̃p�^�[���̏�����
					en[i].hp--;					// �G�̗͌���
					en[i].damage_point++;
					PutEffect(EFFECTTYPE_ENEMY_DAMAGE, en[i].x + en[i].w / 2, en[i].y + en[i].h / 2, i);
					PutEffect(EFFECTTYPE_DAMAGE, en[i].x + (en[i].w / 6), en[i].y - (en[i].h / 4), i);
				}
				// �G�̗͂��Ȃ��Ȃ�����
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
					en[i].use = 0;				// �G������
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
									material[j].use = 1;		// �h���b�v�A�C�e����\��
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
					en[i].nohit_cnt = 60;		// ���G���Ԑݒ�
				}
			}
		}
		// �_���[�W�̑҂����Ԃ������
		if (en[i].damagecooltime > 0) {
			en[i].damagecooltime--;
		}
		else {
			en[i].damagecooltime = 0;
		}
	}
}

// �v���C���[�̃A�C�e���U���ƓG�̓����菈��
void HitCheckPlayerItemAttack() {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		// ���̓G�͎g�p�����H
		if (en[i].use == 0)
		{	// ���g�p
			continue;
		}
		// �G�̓����蔻����s�����H
		if (IsHitProcessEnemy(i) == 0) { return; }

		if (en[i].nohit_cnt <= 0) {
			if (IsHitItemAttack() != 0) {
				if (IsHitPlayerItemAttack(i) != -1) {
					// �_���[�W���󂯂���
					if (en[i].itemdamagecooltime <= 0) {
						PlayMemBack(seEnemyDamage);		// SE�Đ�
						en[i].itemdamagecooltime = 10;	// �U�����󂯂����̑҂�����
						ItemDamage(i);					// �_���[�W����
						PutEffect(EFFECTTYPE_ENEMY_DAMAGE, en[i].x + en[i].w / 2, en[i].y + en[i].h / 2, i);
					}
					// �G�̗͂��Ȃ��Ȃ�����
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
						en[i].use = 0;				// �G������
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
										material[j].use = 1;		// �h���b�v�A�C�e����\��
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
						en[i].nohit_cnt = 80;		// ���G���Ԑݒ�
					}
				}
			}
		}
		// �_���[�W�̑҂����Ԃ������
		if (en[i].itemdamagecooltime > 0) {
			en[i].itemdamagecooltime--;
		}
		else {
			en[i].itemdamagecooltime = 0;
		}
	}
}

// �v���C���[�ƒ������̓����菈��
void HitCheckPlayerPreparation()
{
	for (int i = 0; i < PREPARATION_MAX; i++) {
		// �v���C���[�ƒ������̓����蔻��
		if (IsHitPlayerPreparation(i) != 0)
		{
			//��������
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
			// ��������
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

// �v���C���[�ƃI�u�W�F�N�g�̓����菈��
void HitCheckPlayerObject()
{
	int i, j;
	for (i = 0; i < OBJECT_MAX; i++) {
		// �����f�ރE�B���h�E�͕\������Ă��Ȃ���
		if (check == STATE_NONE) {
				//�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
			if (IsHitPlayerObject(i) != -1)
			{
				if (obj[i].gatherlimit > 0) {
					//��������
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
						obj[i].getwait = 300;			// �č̎�ł���܂ł̎���(5�b)
						obj[i].use = 0;					// �|�C���g������
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
