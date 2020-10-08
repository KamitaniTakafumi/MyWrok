#pragma once
//
// �萔�E�\���̒�`
//
struct ALICE
{
	int     use;        // 0:�g�p���Ȃ��@1:�g�p��
	int		x, y;		// ���W
	int		w, h;		// �傫��
	int		spd;		// �ړ����x
	int		state;		// ���
	int	    hit_x, hit_y, hit_w, hit_h;  //�����蔻��
	int		hitpoint;						// �̗�
	int     nohit_cnt;                      // ���G����
	int		move;		// �����̈ړ�
};

enum alice_state {

	//�A���X���~�܂��Ă������
	ALICE_STATE_IDLE_UP,
	ALICE_STATE_IDLE_DOWN,
	ALICE_STATE_IDLE_LEFT,
	ALICE_STATE_IDLE_RIGHT,

	// �A���X�̌����Ă������
	ALICE_STATE_UP,
	ALICE_STATE_DOWN,
	ALICE_STATE_RIGHT,
	ALICE_STATE_LEFT,

	// �A���X���U�����Ă������
	ALICE_STATE_ATTACK_UP,
	ALICE_STATE_ATTACK_DOWN,
	ALICE_STATE_ATTACK_RIGHT,
	ALICE_STATE_ATTACK_LEFT,

	// �A���X���̎悵�Ă������
	ALICE_STATE_GATHERING_UP,
	ALICE_STATE_GATHERING_DOWN,
	ALICE_STATE_GATHERING_RIGHT,
	ALICE_STATE_GATHERING_LEFT,

	// �A���X���A�C�e�����g�p���Ă������
	ALICE_STATE_ITEM_ATTACK_UP,
	ALICE_STATE_ITEM_ATTACK_DOWN,
	ALICE_STATE_ITEM_ATTACK_RIGHT,
	ALICE_STATE_ITEM_ATTACK_LEFT
};

// �v���C���[���
extern struct ALICE al;

// �A���X���~�܂��Ă���摜
extern int cgAliceIdleUp;
extern int cgAliceIdleDown;
extern int cgAliceIdleLeft;
extern int cgAliceIdleRight;

// �A���X�������摜
extern int cgAliceUp[4];			// �A���X�����
extern int cgAliceDown[4];		// �A���X������
extern int cgAliceLeft[4];		// �A���X������
extern int cgAliceRight[4];		// �A���X�E����

// �A���X���U�����Ă���摜
extern int cgAliceAttackUp[6];
extern int cgAliceAttackDown[6];
extern int cgAliceAttackLeft[6];
extern int cgAliceAttackRight[6];

// �A���X�����ꂽ�摜
extern int cgAliceDeathL[2];
extern int cgAliceDeathR[2];
extern int cgAliceDeathU[2];
extern int cgAliceDeathD[2];

// �O���[�o���ϐ�
extern int imagetime;
extern int alice_freeze;

// �摜�ǂݍ���
void LoadCgAlice();
void LoadCgAlice2();

// �v���C���[��񏉊���
void InitAlice();
void InitAlice2();

// �A���X�𓮂��Ȃ�����
void freezeAlice();
void freezeAlice2();

// �A���X�𓮂�����悤�ɂ���
void releaseAlice();
void releaseAlice2();

// �v���C���[����
void ControllAlice();
void ControllAlice2();

// �����蔻����s�����H
// �Ԓl�F
//   1 = �s��
//   0 = �s��Ȃ�
int IsHitProcessPlayer();
int IsHitProcessPlayer2();

// �v���C���[�`��
void DrawAlice();
void DrawAlice2();
