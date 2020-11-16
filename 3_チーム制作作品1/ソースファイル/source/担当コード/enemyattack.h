#pragma once
/*------------------------------------------------
*  @file enemyattack.cpp , enemyattack.cpp
*  @brief �G�l�~�[�U������
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/
extern int cgAttackJudgment_1;		// ������͈͂P
extern int cgAttackJudgment_2;		// ������͈͂Q
extern int cgAttackJudgment_3;		// ������͈͂R
extern int cgAttackJudgment_7;		// ������͈͂V
extern int cgAttackJudgment_8;		// ������͈͂W
extern int cgAttackJudgment_9;		// ������͈͂X
extern int cgAttackJudgment_10;		// ������͈͂P�O
extern int cgAttackJudgment_11;		// ������͈͂P�P
extern int cgAttackJudgment_12;		// ������͈͂P�Q
extern int cgAttackJudgment_13;		// ������͈͂P�R
extern int cgAttackJudgment_14;		// ������͈͂P�S
extern int cgAttackJudgment_15;		// ������͈͂P�T
extern int enemyattackCooltime;		// �U���̃N�[���^�C��

/*------------------------------------------------
*  �\���̒�`
------------------------------------------------*/

// �G�U���̍\����
struct ENEMYATTACK {
	int		use;									// ���̔z����g�p���邩�̊m�F( 0:���g�p 1:�g�p�� ) 
	double		x, y;								// x, y���W
	double		x2, y2;								// x, y���W
	double		x3, y3;								// x, y���W
	double		x4, y4;								// x, y���W
	double		x5, y5;								// x, y���W
	double		x6, y6;								// x, y���W
	double		x7, y7;								// x, y���W
	double		x8, y8;								// x, y���W
	double		x9, y9;								// x, y���W
	double		x10, y10;							// x, y���W
	double		x11, y11;							// x, y���W
	double		x12, y12;							// x, y���W
	double		x13, y13;							// x, y���W
	double		x14, y14;							// x, y���W
	double		x15, y15;							// x, y���W
	double		x16, y16;							// x, y���W
	double		w, h;								// �傫��
	double		w2, h2;								// �傫��
	double		hit_x, hit_y, hit_w, hit_h;			// �����蔻��
	double	hit_x2, hit_y2, hit_w2, hit_h2;			// �����蔻��
	double	range_x, range_y, range_w, range_h;		// �U���͈�
	double	range_x2, range_y2, range_w2, range_h2;	// �U���͈�
	int		rand;									// �U���p�^�[��
	int		attack_time;							// �U���܂ł̎���
	int		attack_state;							// �U����Ԃ̗L��
	int		select_attack;							// �U���p�^�[���̏�Ԉێ�
};

extern struct ENEMYATTACK enatk[ENEMY_MAX];

/*-------------------------------------------------
*  �֐��錾
-------------------------------------------------*/

// �摜�ǂݍ���
void LoadCgEnemyAttack();
// �摜�ǂݍ���(�X�e�[�W�Q)
void LoadCgEnemyAttack2();
// ������
void InitEnemyAttack();
// ������(�X�e�[�W�Q)
void InitEnemyAttack2();
/*
*  @brief �U������̍X�V
*  @param enemyId �G�̎��ʔԍ�
*/
void AttackCooldinate(int enemyId);
/*
*  @brief �U������̍X�V(�X�e�[�W�Q)
*  @param enemyId �G�̎��ʔԍ�
*/
void AttackCooldinate2(int enemyId);
/*
*  @brief �G���U�����s����
*  @param enemyId �G�̎��ʔԍ�
*/
void EnemyAttack(int enemyId);
// �G�̍U���N�[���^�C��
void EnemyAttackCooltime();
// �G�U���̕`��
void DrawEnemyAttack();
// �G�U���̕`��(�X�e�[�W�Q)
void DrawEnemyAttack2();