#pragma once
//
// �萔�E�\���̒�`
//
struct ATTACK
{
	int		use;						// ���̔z����g�p���邩�̊m�F( 0:���g�p 1:�g�p�� ) 
	int		x, y;						// ���W
	int		w, h;						// �傫��
	int		hit_x, hit_y, hit_w, hit_h;	// �����蔻��
};

struct ATTACKITEM
{
	int		use;						// ���̔z����g�p���邩�̊m�F( 0:���g�p 1:�g�p�� ) 
	int		x, y;						// ���W
	int		w, h;						// �傫��
	int		hit_x, hit_y, hit_w, hit_h;	// �����蔻��
	int		item_no;					// 
};

//
// �O���[�o���ϐ��錾
//
extern struct ATTACK atk;
extern struct ATTACKITEM atkit;

void LoadAttackEff();				// �U���G�t�F�N�g�̃��[�h

void InitAttack();					// �U���̏����ݒ�

void playerAttack();				// �v���C���[�̍U��

void PlayerItemAttack(int itemId);	// �v���C���[�̃A�C�e���U��

void AttackCooltime();				// �U���̃N�[���^�C��
