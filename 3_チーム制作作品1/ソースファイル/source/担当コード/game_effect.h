#pragma once
/*------------------------------------------------
*  @file game_effect.cpp
*  @brief �G�t�F�N�g����
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �萔��`
------------------------------------------------*/

// �G�t�F�N�g�����o����
#define	EFFECT_MAX	(60)

/*------------------------------------------------
*  �\���̒�`
------------------------------------------------*/

// �G�t�F�N�g�\����
struct EFFECT
{
	int	type;		// ���̔z��̃G�t�F�N�g�^�C�v�i0:�g�p���Ȃ��A1�`:��ށj
	int	x, y;		// ���W�B�ʒu�̓G�t�F�N�g�̒��S�ʒu�Ƃ���
	int	w, h;		// �G�t�F�N�g�̑傫��
	int	cnt;		// �J�E���g�B���t���[��+1�����
	int	frame;		// �t���[���B�G�̔ԍ�
	int	mx, my;		// �ړ�����
	int id;			// �G�̔z����
};

// �G�t�F�N�g���
extern struct EFFECT ef[EFFECT_MAX];

// EFFECTTYPE�e��
enum EFFECTTYPE{
	EFFECTTYPE_NONE,			// �g�p���Ȃ�
	EFFECTTYPE_BREAK,			// �ǂ�����
	EFFECTTYPE_ENEMY_DAMAGE,	// �G�_���[�W
	EFFECTTYPE_BOMB,			// ���S
	EFFECTTYPE_DAMAGE,			// �_���[�W
	EFFECTTYPE_CRITICAL,		// �A�C�e���_���[�W
	EFFECTTYPE_ITEM_ATTACK,		// �A�C�e���U��
	EFFECTTYPE_ENEMY_HATTER,	// �}�b�h�n�b�^�[�U��
	EFFECTTYPE_ENEMY_HATTER2,	// �}�b�h�n�b�^�[�U��(����)
	EFFECTTYPE_ENEMY_QUEEN		// �n�[�g�̏����U��
};

/*-------------------------------------------------
*  �֐��錾
-------------------------------------------------*/

// �摜�ǂݍ���
void LoadCgEffect();
// �G�t�F�N�g���̏�����
void InitEffect();
/*
*  @brief �G�t�F�N�g�g�p�̗L��
*  @param effectType �G�t�F�N�g�̎��
*  @param x �`��̍��W
*  @param y �`��̍��W
*  @param Id �A�C�e���A�G�l�~�[�̎���
*/
void PutEffect(int effectType, int x, int y, int Id);
// �G�t�F�N�g�̏���
void ProcessEffect();
// �����蔻����s�����H
// �Ԓl�F
//   1 = �s��
//   0 = �s��Ȃ�
int IsHitItemAttack();
// �G�t�F�N�g�̕`��
void DrawEffect();
