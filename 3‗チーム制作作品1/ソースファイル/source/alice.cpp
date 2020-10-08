#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include    "global.h"   
#include    "alice.h"
#include	"aliceattack.h"
#include	"mapdata_1.h"
#include	"mapdata_2.h"
#include	"HitJudgment.h"
#include	"camera.h"
#include	"Item.h"
#include	"UI.h"
#include	"enemy.h"
#include	"changeroom.h"


// �A���X���~�܂��Ă���摜
int cgAliceIdleUp;
int cgAliceIdleDown;
int cgAliceIdleLeft;
int cgAliceIdleRight;

// �A���X�������摜
int cgAliceUp[4];			// �A���X�����
int cgAliceDown[4];		// �A���X������
int cgAliceLeft[4];		// �A���X������
int cgAliceRight[4];		// �A���X�E����

// �A���X���U�����Ă���摜
int cgAliceAttackUp[6];
int cgAliceAttackDown[6];
int cgAliceAttackLeft[6];
int cgAliceAttackRight[6];

// 
int cgAliceDeathL[2];
int cgAliceDeathR[2];
int cgAliceDeathU[2];
int cgAliceDeathD[2];

// �v���C���[���
struct ALICE al;

// �O���[�o���ϐ�
int imagetime;
int alice_freeze;

// �摜�ǂݍ���
void LoadCgAlice()
{
	// State = Idle
	cgAliceIdleUp = LoadTexture("res/aliceidleup.png");
	cgAliceIdleDown = LoadTexture("res/aliceidledown.png");
	cgAliceIdleLeft = LoadTexture("res/aliceidleleft.png");
	cgAliceIdleRight = LoadTexture("res/aliceidleright.png");

	// State = Walk
	cgAliceUp[0] = LoadTexture("res/alicewalkup_l.png");
	cgAliceUp[1] = LoadTexture("res/aliceidleup.png");
	cgAliceUp[2] = LoadTexture("res/alicewalkup_r.png");
	cgAliceUp[3] = LoadTexture("res/aliceidleup.png");

	cgAliceDown[0] = LoadTexture("res/alicewalkdown_l.png");
	cgAliceDown[1] = LoadTexture("res/aliceidledown.png");
	cgAliceDown[2] = LoadTexture("res/alicewalkdown_r.png");
	cgAliceDown[3] = LoadTexture("res/aliceidledown.png");

	cgAliceLeft[0] = LoadTexture("res/alicewalkleft_l.png");
	cgAliceLeft[1] = LoadTexture("res/aliceidleleft.png");
	cgAliceLeft[2] = LoadTexture("res/alicewalkleft_r.png");
	cgAliceLeft[3] = LoadTexture("res/aliceidleleft.png");

	cgAliceRight[0] = LoadTexture("res/alicewalkright_l.png");
	cgAliceRight[1] = LoadTexture("res/aliceidleright.png");
	cgAliceRight[2] = LoadTexture("res/alicewalkright_r.png");
	cgAliceRight[3] = LoadTexture("res/aliceidleright.png");

	// State = attack
	cgAliceAttackUp[0] = LoadTexture("res/aliceattackup.png");
	cgAliceAttackUp[1] = LoadTexture("res/aliceattackup_2.png");
	cgAliceAttackUp[2] = LoadTexture("res/aliceattackup_3.png");
	cgAliceAttackUp[3] = LoadTexture("res/aliceattackup_3_2.png");
	cgAliceAttackUp[4] = LoadTexture("res/aliceattackup_3_3.png");
	cgAliceAttackUp[5] = LoadTexture("res/aliceattackup_3_4.png");

	cgAliceAttackDown[0] = LoadTexture("res/aliceattackdown.png");
	cgAliceAttackDown[1] = LoadTexture("res/aliceattackdown_2.png");
	cgAliceAttackDown[2] = LoadTexture("res/aliceattackdown_3.png");
	cgAliceAttackDown[3] = LoadTexture("res/aliceattackdown_3_2.png");
	cgAliceAttackDown[4] = LoadTexture("res/aliceattackdown_3_3.png");
	cgAliceAttackDown[5] = LoadTexture("res/aliceattackdown_3_4.png");

	cgAliceAttackLeft[0] = LoadTexture("res/aliceattackleft.png");
	cgAliceAttackLeft[1] = LoadTexture("res/aliceattackleft_2.png");
	cgAliceAttackLeft[2] = LoadTexture("res/aliceattackleft_3.png");
	cgAliceAttackLeft[3] = LoadTexture("res/aliceattackleft_3_2.png");
	cgAliceAttackLeft[4] = LoadTexture("res/aliceattackleft_3_3.png");
	cgAliceAttackLeft[5] = LoadTexture("res/aliceattackleft_3_4.png");

	cgAliceAttackRight[0] = LoadTexture("res/aliceattackright.png");
	cgAliceAttackRight[1] = LoadTexture("res/aliceattackright_2.png");
	cgAliceAttackRight[2] = LoadTexture("res/aliceattackright_3.png");
	cgAliceAttackRight[3] = LoadTexture("res/aliceattackright_3_2.png");
	cgAliceAttackRight[4] = LoadTexture("res/aliceattackright_3_3.png");
	cgAliceAttackRight[5] = LoadTexture("res/aliceattackright_3_4.png");

	cgAliceDeathL[0] = LoadTexture("res/aliceidleleft.png");
	cgAliceDeathL[1] = LoadTexture("res/alicedeath.png");

	cgAliceDeathR[0] = LoadTexture("res/aliceidleright.png");
	cgAliceDeathR[1] = LoadTexture("res/alicedeath.png");

	cgAliceDeathD[0] = LoadTexture("res/aliceidledown.png");
	cgAliceDeathD[1] = LoadTexture("res/alicedeath.png");

	cgAliceDeathU[0] = LoadTexture("res/aliceidleup.png");
	cgAliceDeathU[1] = LoadTexture("res/alicedeath.png");
}

// �v���C���[��񏉊���
void InitAlice()
{
	imagetime = 0;
	alice_freeze = 0;
	al.use = 1;
	al.w = 40;
	al.h = 80;
	switch (stateStage) {
	case STATE_EP1STAGE:
		al.x = 200;
		al.y = 1200;
		break;
	case STATE_EP1STAGE_2:
		al.x = 2320;	// �X�e�[�W�Q�����ʒu
		al.y = 40 * 50;	// �X�e�[�W�Q�����ʒu
		break;
	case STATE_EP1STAGE_3:
		if (bgstage == STATE_EP1STAGE_3) {
			al.x = 1400;	// �X�e�[�W�R�����ʒu
			al.y = 2320;	// �X�e�[�W�R�����ʒu
		}
		else {
			al.x = 160;		// �{�X�X�e�[�W��O
			al.y = 80;		// �{�X�X�e�[�W��O
		}
		break;
	case STATE_EP1STAGE_4:
		al.x = 720;
		al.y = 1040;
		break;
	}
	//al.x = 2040;		// �����q�̉�(�J���p)
	//al.y = 960;			// �����q�̉�(�J���p)
	al.spd = 5;
	al.state = ALICE_STATE_IDLE_DOWN;
	al.hit_x = 4;
	al.hit_y = 44;
	al.hit_w = 32;
	al.hit_h = 32;
	al.hitpoint = 6;
	//al.hitpoint = 100;		// ���ȂȂ��悤��(�J���p)
	al.nohit_cnt = 0;
}

void freezeAlice() {
	// �A���X�𓮂��Ȃ�����
	alice_freeze = 1;
}

void releaseAlice() {
	// �A���X�𓮂���悤�ɂ���
	alice_freeze = 0;
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int CheckHitMapChipAlice(int x, int y)
{
	if (stateStage == STATE_EP1STAGE) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W && 0 <= y && y < MAPSIZE_H) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap[y *MAPSIZE_W + x];

			// ������ID���ǂ������`�F�b�N
			int idtable[] =
			{
				103,-1		// �Ō�
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
int CheckHitMapChipAlice2(int x, int y) {
	if (stateStage == STATE_EP1STAGE_2) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W_2 && 0 <= y && y < MAPSIZE_H_2) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap2[y *MAPSIZE_W_2 + x];
			int chip_no2 = nMap2lm[y *MAPSIZE_W_2 + x];

			if (required_count < 2) {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					102,251,-1		// �Ō�
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
					251,-1		// �Ō�
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
int CheckHitMapChipAlice3(int x, int y) {
	if (stateStage == STATE_EP1STAGE_3) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W_3 && 0 <= y && y < MAPSIZE_H_3) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap3[y *MAPSIZE_W_3 + x];
			int chip_no2 = nMap3lm[y *MAPSIZE_W_3 + x];

			if (required_count < 4) {
				// ������ID���ǂ������`�F�b�N
				int idtable[] =
				{
					101,102,-1		// �Ō�
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
int CheckHitMapChipAlice4(int x, int y) {
	if (stateStage == STATE_EP1STAGE_4) {
		// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
		if (0 <= x && x < MAPSIZE_W_4 && 0 <= y && y < MAPSIZE_H_4) {	// �݂͂łĂ��Ȃ�

			// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
			// ���݁A���C���[�͍l������Ă��Ȃ�
			int chip_no = nMap4[y *MAPSIZE_W_4 + x];

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
int IsHitMapChipAlice(int i, int mx, int my)
{
	if (stateStage == STATE_EP1STAGE) {
		int x, y;

		// �L������`���쐬����
		int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
				// ���̈ʒu�̃`�b�v�͓����邩�H
				int chip_no = CheckHitMapChipAlice(x, y);
				if (chip_no != 0) {	// ���̃`�b�v�Ɠ��������B
					// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
					if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// ���������̂Ŗ߂�
					return 1;
				}
			}
		}

		// ������Ȃ�����
		return 0;
	}
}

int IsHitMapChipAlice2(int i, int mx, int my) {
	if (stateStage == STATE_EP1STAGE_2) {
		int x, y;

		// �L������`���쐬����
		int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
				// ���̈ʒu�̃`�b�v�͓����邩�H
				int chip_no2 = CheckHitMapChipAlice2(x, y);
				if (chip_no2 != 0) {	// ���̃`�b�v�Ɠ��������B
					// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
					if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// ���������̂Ŗ߂�
					return 1;
				}
			}
		}

		// ������Ȃ�����
		return 0;
	}
}

int IsHitMapChipAlice3(int i, int mx, int my) {
	if (stateStage == STATE_EP1STAGE_3) {
		int x, y;

		// �L������`���쐬����
		int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
				// ���̈ʒu�̃`�b�v�͓����邩�H
				int chip_no3 = CheckHitMapChipAlice3(x, y);
				if (chip_no3 != 0) {	// ���̃`�b�v�Ɠ��������B
					// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
					if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// ���������̂Ŗ߂�
					return 1;
				}
			}
		}

		// ������Ȃ�����
		return 0;
	}
}

int IsHitMapChipAlice4(int i, int mx, int my) {
	if (stateStage == STATE_EP1STAGE_4) {
		int x, y;

		// �L������`���쐬����
		int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
		l = al.x + al.hit_x;
		t = al.y + al.hit_y;
		r = al.x + al.hit_x + al.hit_w - 1;
		b = al.y + al.hit_y + al.hit_h - 1;

		// �L�����̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
		for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++) {
			for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++) {
				// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
				// ���̈ʒu�̃`�b�v�͓����邩�H
				int chip_no4 = CheckHitMapChipAlice4(x, y);
				if (chip_no4 != 0) {	// ���̃`�b�v�Ɠ��������B
					// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
					if (mx < 0) {	// ���ɓ����Ă����̂ŁA�E�ɕ␳
						al.x = x * CHIPSIZE_W + CHIPSIZE_W - (al.hit_x);
					}
					if (mx > 0) {	// �E�ɓ����Ă����̂ŁA���ɕ␳
						al.x = x * CHIPSIZE_W - (al.hit_x + al.hit_w);
					}
					if (my > 0) {	// ���ɓ����Ă����̂ŁA��ɕ␳
						al.y = y * CHIPSIZE_H - (al.hit_y + al.hit_h);
					}
					if (my < 0) {	// ��ɓ����Ă����̂ŁA���ɕ␳
						al.y = y * CHIPSIZE_H + CHIPSIZE_H - (al.hit_y);
					}
					// ���������̂Ŗ߂�
					return 1;
				}
			}
		}

		// ������Ȃ�����
		return 0;
	}
}

// �A���X����
void ControllAlice()
{
	int keyflag = 0;
	int i = 0;
	int j;

	// ��l���g�p���łȂ���Ώ������Ȃ�
	if (al.use == 0) { return; }

	if ((selectTrg == STATE_NONE) & (check == STATE_NONE)) {
		if (alice_freeze == 0) {
		// �L�[���͂𔻒肵�āA��l�����ړ�������
	// �㉺���E�݂̂Ȃ̂Ŏ΂߈ړ����Ȃ��悤�Ƀt���O�ŋK�������Ă�
			if ((al.state == ALICE_STATE_IDLE_UP) ||
				(al.state == ALICE_STATE_IDLE_DOWN) ||
				(al.state == ALICE_STATE_IDLE_RIGHT) ||
				(al.state == ALICE_STATE_IDLE_LEFT) ||
				(al.state == ALICE_STATE_UP) ||
				(al.state == ALICE_STATE_DOWN) ||
				(al.state == ALICE_STATE_RIGHT) ||
				(al.state == ALICE_STATE_LEFT)) {
				// ���Ɉړ�
				if (gKey & KEYIN_LEFT) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_LEFT;
						al.x -= al.spd;
						IsHitMapChipAlice(i, -1, 0);
						IsHitMapChipAlice2(i, -1, 0);
						IsHitMapChipAlice3(i, -1, 0);
						IsHitMapChipAlice4(i, -1, 0);
						keyflag += 1;
						imagetime += 1;
					}
				}
				// �E�Ɉړ�
				if (gKey & KEYIN_RIGHT) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_RIGHT;
						al.x += al.spd;
						IsHitMapChipAlice(i, 1, 0);
						IsHitMapChipAlice2(i, 1, 0);
						IsHitMapChipAlice3(i, 1, 0);
						IsHitMapChipAlice4(i, 1, 0);
						keyflag += 1;
						imagetime += 1;
					}
				}
				// ��Ɉړ�
				if (gKey & KEYIN_UP) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_UP;
						al.y -= al.spd;
						IsHitMapChipAlice(i, 0, -1);
						IsHitMapChipAlice2(i, 0, -1);
						IsHitMapChipAlice3(i, 0, -1);
						IsHitMapChipAlice4(i, 0, -1);
						keyflag += 1;
						imagetime += 1;
					}
				}
				// ���Ɉړ�
				if (gKey & KEYIN_DOWN) {
					if (keyflag <= 0) {
						al.state = ALICE_STATE_DOWN;
						al.y += al.spd;
						IsHitMapChipAlice(i, 0, 1);
						IsHitMapChipAlice2(i, 0, 1);
						IsHitMapChipAlice3(i, 0, 1);
						IsHitMapChipAlice4(i, 0, 1);
						keyflag += 1;
						imagetime += 1;
					}
				}

				if (imagetime == 1) {
					PlayMemLoop(seWalk1);
				}

				// �A���X���~�܂��Ă���Ƃ��~�܂�����Ԃɂ���
				if (!(gKey & KEYIN_UP) && (!(gKey & KEYIN_DOWN)) && (!(gKey & KEYIN_RIGHT)) && (!(gKey & KEYIN_LEFT))) {
					if (al.state == ALICE_STATE_UP) {
						al.state = ALICE_STATE_IDLE_UP;
						imagetime = 0;
					}
					if (al.state == ALICE_STATE_DOWN) {
						al.state = ALICE_STATE_IDLE_DOWN;
						imagetime = 0;
					}
					if (al.state == ALICE_STATE_LEFT) {
						al.state = ALICE_STATE_IDLE_LEFT;
						imagetime = 0;
					}
					if (al.state == ALICE_STATE_RIGHT) {
						al.state = ALICE_STATE_IDLE_RIGHT;
						imagetime = 0;
					}
					StopPlayMem(seWalk1);
				}
			}

			// 1�ȏ�̎��t���O�����Z�b�g
			if (keyflag > 0) {
				keyflag = 0;
			}

			// �����U��
		// �L�[���������Ƃ��ɂ��̕����ɍU��������
		// �A�����Ďg���Ȃ��悤�ɃN�[���^�C����ݒ肳����
		// �܂��U�����͓����Ȃ��悤�ɂ���
			if ((IsHitPlayerAttackPreparation() == 0) & (IsHitPlayerAttackObject() == 0) & (IsHitPlayerAttackDrop() == 0)) {
				if (gTrg & KEYIN_X) {
					if ((al.state == ALICE_STATE_IDLE_UP) ||
						(al.state == ALICE_STATE_IDLE_DOWN) ||
						(al.state == ALICE_STATE_IDLE_RIGHT) ||
						(al.state == ALICE_STATE_IDLE_LEFT) ||
						(al.state == ALICE_STATE_UP) ||
						(al.state == ALICE_STATE_DOWN) ||
						(al.state == ALICE_STATE_RIGHT) ||
						(al.state == ALICE_STATE_LEFT)) {

						if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP)) {
							al.state = ALICE_STATE_ATTACK_UP;
						}
						if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN)) {
							al.state = ALICE_STATE_ATTACK_DOWN;
						}
						if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT)) {
							al.state = ALICE_STATE_ATTACK_RIGHT;
						}
						if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT)) {
							al.state = ALICE_STATE_ATTACK_LEFT;
						}
						playerAttack();
					}
				}
			}

			// �A�C�e���U��
			if (frm[2].move == 0) {
				for (j = 0; j < 6; j++) {
					if ((useit[j].use == 1) & (frm[2].x == useit[j].x - 10)) {
						if (gTrg & KEYIN_A) {
							if ((al.state == ALICE_STATE_IDLE_UP) ||
								(al.state == ALICE_STATE_IDLE_DOWN) ||
								(al.state == ALICE_STATE_IDLE_RIGHT) ||
								(al.state == ALICE_STATE_IDLE_LEFT) ||
								(al.state == ALICE_STATE_UP) ||
								(al.state == ALICE_STATE_DOWN) ||
								(al.state == ALICE_STATE_RIGHT) ||
								(al.state == ALICE_STATE_LEFT)) {

								if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP)) {
									al.state = ALICE_STATE_ITEM_ATTACK_UP;
								}
								if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN)) {
									al.state = ALICE_STATE_ITEM_ATTACK_DOWN;
								}
								if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_RIGHT;
								}
								if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_LEFT;
								}
								PlayerItemAttack(j);
							}
						}
					}
				}
			}
			else if (frm[2].move == 1) {
				for (j = 6; j < 9; j++) {
					if ((useit[j].use == 1) & (frm[2].x == useit[j].x - 10)) {
						if (gTrg & KEYIN_A) {
							if ((al.state == ALICE_STATE_IDLE_UP) ||
								(al.state == ALICE_STATE_IDLE_DOWN) ||
								(al.state == ALICE_STATE_IDLE_RIGHT) ||
								(al.state == ALICE_STATE_IDLE_LEFT) ||
								(al.state == ALICE_STATE_UP) ||
								(al.state == ALICE_STATE_DOWN) ||
								(al.state == ALICE_STATE_RIGHT) ||
								(al.state == ALICE_STATE_LEFT)) {

								if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP)) {
									al.state = ALICE_STATE_ITEM_ATTACK_UP;
								}
								if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN)) {
									al.state = ALICE_STATE_ITEM_ATTACK_DOWN;
								}
								if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_RIGHT;
								}
								if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT)) {
									al.state = ALICE_STATE_ITEM_ATTACK_LEFT;
								}
								PlayerItemAttack(j);
							}
						}
					}
				}
			}
		}
		// ��ʂ̊O�ɏo�Ȃ��悤�ɂ���
		if (stateStage == STATE_EP1STAGE) {
			if (al.y + al.h > 40 * 35) { al.y = 40 * 35 - al.h; }
		}
		else if (stateStage == STATE_EP1STAGE_4) {
			if (al.y + al.h > 40 * 27) { al.y = 40 * 27 - al.h; }
		}

		// ��ʂ�؂�ւ���
		changeroom();

		// ���G�J�E���^�̏���
		if (al.nohit_cnt > 0) {
			al.nohit_cnt--;
		}
	}
}

// �����蔻����s�����H
// �Ԓl�F
//   1 = �s��
//   0 = �s��Ȃ�
int IsHitProcessPlayer()
{
	if (al.use == 0) { return 0; }
	if (al.nohit_cnt > 0) { return 0; }
	return 1;
}

// �A���X�̕`��
void DrawAlice()
{
	// ��l���g�p���łȂ���Ώ������Ȃ�
	if (al.use == 0) {
		if ((al.state == ALICE_STATE_IDLE_LEFT) || (al.state == ALICE_STATE_LEFT) || (al.state == ALICE_STATE_ATTACK_LEFT) || (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) || (al.state == ALICE_STATE_GATHERING_LEFT)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathL[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathL[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathL[1]);
			}
		}
		if ((al.state == ALICE_STATE_IDLE_RIGHT) || (al.state == ALICE_STATE_RIGHT) || (al.state == ALICE_STATE_ATTACK_RIGHT) || (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) || (al.state == ALICE_STATE_GATHERING_RIGHT)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathR[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathR[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathR[1]);
			}
		}
		if ((al.state == ALICE_STATE_IDLE_UP) || (al.state == ALICE_STATE_UP) || (al.state == ALICE_STATE_ATTACK_UP) || (al.state == ALICE_STATE_ITEM_ATTACK_UP) || (al.state == ALICE_STATE_GATHERING_UP)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathU[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathU[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathU[1]);
			}
		}
		if ((al.state == ALICE_STATE_IDLE_DOWN) || (al.state == ALICE_STATE_DOWN) || (al.state == ALICE_STATE_ATTACK_DOWN) || (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) || (al.state == ALICE_STATE_GATHERING_DOWN)) {
			if (gGameoverCount >= 50) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDeathD[0]);
			}
			else if (gGameoverCount >= 40) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathD[1]);
			}
			else if (gGameoverCount >= 0) {
				DrawMemTh(al.x - 40 - cv.view_x, al.y + 50 - cv.view_y, cgAliceDeathD[1]);
			}
		}
	}

	if (al.use == 1) {
		// ���G���͈��Ԋu�ŕ`�悵�Ȃ�
		if (al.nohit_cnt == 0 || (al.nohit_cnt % 10) < 7)
		{
			if (al.state == ALICE_STATE_IDLE_UP) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleUp);
			}
			if (al.state == ALICE_STATE_IDLE_DOWN) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleDown);
			}
			if (al.state == ALICE_STATE_IDLE_LEFT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleLeft);
			}
			if (al.state == ALICE_STATE_IDLE_RIGHT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleRight);
			}

			if ((al.state == ALICE_STATE_UP) || (al.state == ALICE_STATE_GATHERING_UP)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceUp[(imagetime / 8) % 4]);
			}
			if ((al.state == ALICE_STATE_DOWN) || (al.state == ALICE_STATE_GATHERING_DOWN)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceDown[(imagetime / 8) % 4]);
			}
			if ((al.state == ALICE_STATE_LEFT) || (al.state == ALICE_STATE_GATHERING_LEFT)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceLeft[(imagetime / 8) % 4]);
			}
			if ((al.state == ALICE_STATE_RIGHT) || (al.state == ALICE_STATE_GATHERING_RIGHT)) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceRight[(imagetime / 8) % 4]);
			}

			if (al.state == ALICE_STATE_ATTACK_UP) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackUp[(attackCooltime / 5) % 6]);
			}
			if (al.state == ALICE_STATE_ATTACK_DOWN) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackDown[(attackCooltime / 5) % 6]);
			}
			if (al.state == ALICE_STATE_ATTACK_LEFT) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackLeft[(attackCooltime / 5) % 6]);
			}
			if (al.state == ALICE_STATE_ATTACK_RIGHT) {
				DrawMemTh(al.x - 20 - cv.view_x, al.y - cv.view_y, cgAliceAttackRight[(attackCooltime / 5) % 6]);
			}

			if (al.state == ALICE_STATE_ITEM_ATTACK_UP) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleUp);
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_DOWN) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleDown);
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_LEFT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleLeft);
			}
			if (al.state == ALICE_STATE_ITEM_ATTACK_RIGHT) {
				DrawMemTh(al.x - cv.view_x, al.y - cv.view_y, cgAliceIdleRight);
			}
		}
	}
}
