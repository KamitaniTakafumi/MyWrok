#pragma once
/*------------------------------------------------
*  @file enemy1.cpp , enemy2.cpp
*  @brief �G�l�~�[����
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �w�b�_�[�t�@�C���̃C���N���[�h
------------------------------------------------*/
#include "vector.h"

/*------------------------------------------------
*  �萔��`
------------------------------------------------*/

// �ő�G��
#define ENEMY_MAX 15

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

extern int cgCaterpiller[3 * 4];	// ��
extern int cgHatter[4 * 4];			// �}�b�h�n�b�^�[
extern int hattbl[];				// �`��e�[�u��(�}�b�h�n�b�^�[)

/*------------------------------------------------
*  �\���̒�`
------------------------------------------------*/

// �G�l�~�[�̍\����
struct ENEMY {
	int use;
	int state;      // ���
	int direction;  // ����
	int entype;		// �G�̎��
	double	x, y;	// ���W
	int	w, h;		// �傫��
	int	spd;		// �ړ����x
	int drc;        // �ړ�����
	Vector2 d;		// �P�ʃx�N�g��
	int period;		// �G�����ړ�(���E)
	int period2;	// �G�����ړ�(�㉺)
	int period3;	// �G�����ړ�(�}�b�v�ǂɓ��������甽�΂�����)
	int period4;	// �G�ǔ��ړ�
	int	hit_x, hit_y, hit_w, hit_h;  //�����蔻��
	int	hit_range_x, hit_range_y, hit_range_w, hit_range_h;  //�����蔻��(�s���͈�)
	int hp;			// �G�̗̑�
	int nohit_cnt;	// ���G����
	int damagecooltime;			// �_���[�W���󂯂Ă��瓮����܂ł̎���
	int itemdamagecooltime;		// �A�C�e���_���[�W���󂯂Ă��瓮����܂ł̎���
	int anim_count;				// ���[�V��������
	int damage_point;			// �_���[�W��
	int damage_critical_point;	// �_���[�W��(�L���A�s��)
	int required;				// �K�{�����G
	int max_hp;			// �ő�HP
	int state_enemy;	// �{�X������ł������Ȃ��悤�ɂ���
	int recipe_no;		// �G�����Ƃ����V�s�̎��
};

// �G�l�~�[���
extern struct ENEMY en[ENEMY_MAX];

// �G�̎��
enum ENEMYTYPE{
	ENEMY_CATERPILLAR,		// ��
	ENEMY_MATANGO,			// �}�^���S
	ENEMY_MERGE_MATANGO,	// �}�[�W�}�^���S
	ENEMY_WOLF,				// �T
	ENEMY_MAD_HATTER,		// �}�b�h�n�b�^�[

	ENEMY_HEART,			// �g�����v��(�n�[�g)
	ENEMY_DIA,				// �g�����v��(�_�C��)
	ENEMY_CLOVER,			// �g�����v��(�N���[�o�[)
	ENEMY_SPADE,			// �g�����v��(�X�y�[�h)
	ENEMY_QUEEN,			// �n�[�g�̏���
	ENEMY_MAD_HATTER2,		// �}�b�h�n�b�^�[
};

enum enemy_state {

	ENUM_EMPTY,		// 0�̂��ߎg��Ȃ��悤�ɂ���

	ENEMY_STATE_DOWN,	// �G�ړ�(��)
	ENEMY_STATE_UP,		// �G�ړ�(��)
	ENEMY_STATE_RIGHT,	// �G�ړ�(�E)
	ENEMY_STATE_LEFT,	// �G�ړ�(��)
	
	ENEMY_STATE_ATTACK_DOWN,	// �G�U��(��)
	ENEMY_STATE_ATTACK_UP,		// �G�U��(��)
	ENEMY_STATE_ATTACK_RIGHT,	// �G�U��(�E)
	ENEMY_STATE_ATTACK_LEFT,	// �G�U��(��)
};

/*-------------------------------------------------
*  �֐��錾
-------------------------------------------------*/

// ���`�⊮�ɂ�铙���ړ�
// start -> end �ɒl�������ꍇ�A cnt/max ���̈ʒu��Ԃ�
int LerpN(int cnt, int max, int start, int end);
// �G�摜�̓ǂݍ���
void LoadCgEnemy();
// �G�摜�̓ǂݍ���(�X�e�[�W�Q)
void LoadCgEnemy2();
// �G�l�~�[������
void InitEnemy();
// �G�l�~�[������(�X�e�[�W�Q)
void InitEnemy2();
// �G�l�~�[�ړ�
void EnemyMove();
// �G�l�~�[�ړ�(�X�e�[�W�Q)
void EnemyMove2();
// �����蔻����s�����H
// �Ԓl�F
//   1 = �s��
//   0 = �s��Ȃ�
int IsHitProcessEnemy(int enemyId);
// �G�l�~�[�`��
void DrawEnemy();
// �G�l�~�[�`��(�X�e�[�W�Q)
void DrawEnemy2();
// �G�̗͕̑`��(�{�X�̂�)
void DrawEnemyHitpoint();
// �G�̗͕̑`��(�{�X�̂݁A�X�e�[�W�Q)
void DrawEnemyHitpoint2();