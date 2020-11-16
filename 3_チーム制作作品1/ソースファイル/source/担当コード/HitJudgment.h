#pragma once
/*------------------------------------------------
*  @file HitJudgment.cpp
*  @brief �����蔻�菈��
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

// SE�f�[�^

extern int seCursor;		// �J�[�\��
extern int seSelect;		// �Z���N�g
extern int seCancel;		// �L�����Z��
extern int seGetPlant;		// �A�C�e���Q�b�g(�؂̎��n)
extern int seGetRock;		// �A�C�e���Q�b�g(��n)
extern int seGetWater;		// �A�C�e���Q�b�g(���n)
extern int seGetPickup;		// �E��
extern int seCreateItem;	// �A�C�e������
extern int seAliceAttack;	// �v���C���[�U��
extern int seAliceDamage;	// �v���C���[�_���[�W
extern int seEnemyDamage;	// �G�l�~�[�_���[�W
extern int seDead;			// ���S
extern int seRecovery;		// ��
extern int seOpen;			// �I�[�v��
extern int seMove;			// �X�e�[�W�ړ�
extern int seWalk1;			// ����(�X�e�[�W�P)
extern int seWalk2;			// ����(�X�e�[�W�Q)
extern int seBomb;			// �{��
extern int seBomb2;			// �{���Q
extern int seRecipe;		// ���V�s
extern int seFlash;			// �Ђ�߂�
extern int seWallBreak;		// �ǔj��
extern int seBoom;			// �l�C
extern int seBladesound;	// �n
extern int seFootstep;		// ����(����)
extern int seFootstep_run;	// ����(����)
extern int seGetaway;		// ������
extern int seOpendoor;		// �J����
extern int seShock;			// �Ռ�
extern int seSlashsound;	// �a��
extern int seRun;			// ����
extern int seFootstep_heel;	// ����(�q�[��)

// BGM�f�[�^
extern int bgmTitle;		// �^�C�g��
extern int bgmOp01;			// �I�[�v�j���O�P
extern int bgmOp02;			// �I�[�v�j���O�Q
extern int bgmOp03;			// �I�[�v�j���O�R
extern int I_home;			// �X�g�[���[�}���ȂP
extern int DCF;				// �X�g�[���[�}���ȂQ
extern int Lucifer;			// �X�g�[���[�}���ȂR
extern int cheshirebgm;		// �X�g�[���[�}���ȂS
extern int Assault;			// �X�g�[���[�}���ȂT
extern int Be_quiet;		// �X�g�[���[�}���ȂU
extern int cheshirebgm2;	// �X�g�[���[�}���ȂV
extern int loneliness;		// �X�g�[���[�}���ȂW
extern int midnightmoon;	// �X�g�[���[�}���ȂX
extern int queenbgm;		// �X�g�[���[�}���ȂP�O
extern int queenbgm2;		// �X�g�[���[�}���ȂP�P
extern int madhatterbgm;	// �X�g�[���[�}���ȂP�Q
extern int reddress;		// �X�g�[���[�}���ȂP�R
extern int reunion;			// �X�g�[���[�}���ȂP�S
extern int dustwall;		// �X�g�[���[�}���ȂP�T
extern int farewell;		// �X�g�[���[�}���ȂP�U
extern int BGMSilent;		// �X�g�[���[�}���ȂP�V
extern int Inherited_Hope;	// �X�g�[���[�}���ȂP�W
extern int bgmMap1;			// �X�e�[�W�P
extern int bgmMap2;			// �X�e�[�W�Q
extern int bgmBoss1;		// �{�X�P
extern int bgmBoss2;		// �{�X�Q
extern int bgmBoss3;		// �{�X�R
extern int bgmEnd;			// �G���f�B���O

/*-------------------------------------------------
*  �֐��錾
-------------------------------------------------*/

// SE�̓ǂݍ���
void LoadSe();
// BGM�̓ǂݍ���
void LoadBgm();

// �����蔻��p�B2��box�������������𔻒�
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitBox(
	int x1, int y1, int w1, int h1,		// �ЂƂ߂�box ����(x,y), �傫��w,h
	int x2, int y2, int w2, int h2		// �ӂ��߂�box ����(x,y), �傫��w,h
);

// �����蔻��p 2��box�������������𔻒�
// distance�ł��̕�����Ă��Ă�������悤�ɂ��邱�Ƃ��ł���
int IsHitBoxDistance(int x1, int y1, int x2, int y2, int distance);

// �����蔻��F�v���C���[�ƓG
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitPlayerEnemy(int enemyId);

// �����蔻��F�v���C���[�ƓG(�s���͈�)
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitPlayerEnemyRange(int enemyId);

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitEnemyAttack(int enemyId);

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitEnemyAttack2(int enemyId);

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitEnemyAttack3(int enemyId);

// �����蔻��F�v���C���[�ƓG�U��
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitEnemyAttack4(int enemyId);

// �����蔻��F�v���C���[�U���ƓG
// �������Ă�����enemyId, �������Ă��Ȃ�������-1��Ԃ�
int IsHitPlayerAttack(int enemyId);

// �����蔻��F�v���C���[�A�C�e���U���ƓG
// �������Ă�����enemyId, �������Ă��Ȃ�������-1��Ԃ�
int IsHitPlayerItemAttack(int enemyId);

// �����蔻��F�v���C���[�ƃI�u�W�F�N�g
// �������Ă�����objectId, �������Ă��Ȃ�������-1��Ԃ�
int IsHitPlayerObject(int objectId);

// �����蔻��F�v���C���[�ƃI�u�W�F�N�g
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitPlayerAttackObject();

// �����蔻��F�v���C���[�ƒ�����
// �������Ă�����1, �������Ă��Ȃ�������0��Ԃ�
int IsHitPlayerAttackPreparation();

// �����蔻��F�v���C���[�ƃh���b�v�A�C�e��
// �������Ă���1, �������Ă��Ȃ�������0��Ԃ�
int IsHitPlayerAttackDrop();

// �v���C���[�ƓG�̓����菈��
void HitCheckPlayerEnemy();

// �v���C���[�ƓG(�s���͈�)�̓����菈��
void HitCheckPlayerEnemyRange();

// �v���C���[�ƓG�U���̓����菈��
void HitCheckEnemyAttack();

// �v���C���[�̍U���ƓG�̓����菈��
void HitCheckPlayerAttack();

// �v���C���[�̃A�C�e���U���ƓG�̓����菈��
void HitCheckPlayerItemAttack();

// �v���C���[�ƒ������̓����菈��
void HitCheckPlayerPreparation();