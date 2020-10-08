/*------------------------------------------------
*  @file game.cpp
*  @brief �Q�[���{�̏���
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
#include    "alice.h"
#include    "enemy.h"
#include    "preparation.h"
#include    "HitJudgment.h"
#include	"script_parser.h"
#include    "Material.h"
#include    "Object.h"
#include    "recipe.h"
#include	"title.h"
#include	"episode1S.h"
#include	"episode1S2.h"
#include	"episode1S3.h"
#include	"episode2S.h"
#include	"episode2S2.h"
#include	"episode2S3.h"
#include	"episode2S4.h"
#include	"episode1L.h"
#include	"episode2L.h"
#include	"global.h"
#include	"gameover.h"
#include	"end.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

// �Q�[�����
int stateStage;		// ���݂̃X�e�[�W
int gFrameCount;	// ���t���[��+1����J�E���g
int gKey;			// �L�[���͂̏��
int gTrg;			// �g���K���͂̏��
int gFrameWait;		// �s���������̃N�[���^�C��
int gGameoverCount;	// �Q�[���I�[�o�[���̃J�E���g�_�E��
int check;			// �L�[���͂̔���
int pick;			// �L�[���͂̔���
int bgstage;		// �Q�[���I�[�o�[���ɕ`�悷��X�e�[�W
int bgstage2;		// �Q�[���I�[�o�[���ɕ`�悷��X�e�[�W
int required_count; // �i�ނ̂ɕK�v�ȓ|���G�̃J�E���g
int clearwait;		// �{�X��A�X�g�[���[�p�[�g�ւ̈ڍs����
int clearflag;		// �i�ނ��߂̃t���O�ϐ�
int check_number;	// �A�C�e���������Ă��邩�̃`�F�b�N�ϐ�
int check_number2;	// �A�C�e���������Ă��邩�̃`�F�b�N�ϐ��Q
int wallwait;		// �ǉ󂵑҂�����
int wallflag;		// �ǉ󂵃t���O
int continueflag;	// �R���e�B�j���[�t���O

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
// �A�v���̏�����
// �N������1�񂾂����s�����
void AppInit() {

	stateStage = STATE_TITLE;
	check = STATE_NONE;
	pick = STATE_NONE;
	bgstage = STATE_EP1STAGE;
	bgstage2 = STATE_EP2STAGE1_1;

	// �摜�̓ǂݍ���
	LoadCgTitle();
	LoadCgGameOver();
	LoadSe();
	LoadBgm();

	//�t���[���J�E���g�̏�����
	gFrameCount = 0;
	gFrameWait = 0;
	gGameoverCount = 0;
	clearwait = 0;
	clearflag = 0;
	check_number = 0;
	check_number2 = 0;
	wallwait = 0;
	wallflag = 0;
	continueflag = 0;

	//������
	cursorInit();
}

// �A�v���̉��
// �I������1�񂾂����s�����
void AppRelease() {

}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/

//
// �t���[�������B1�t���[����1�񂸂��s�����
//

// �t���[�������F����
void FrameInput() {
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = gKey;
	gKey = CheckKey(0);
	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	gTrg = (gKey ^ keyold) & gKey;
}

// �t���[�������F�v�Z
void FrameProcess() {

	// ���t���[������
	gFrameCount++;		// �t���[���J�E���g�𑝂₷

	// ��Ԃ��Ƃɏ����𕪂���
	switch (stateStage) {
	case STATE_TITLE:
		titleSelect();
		break;
	case STATE_EP1STORY:
		Episode1_Story();
		break;
	case STATE_EP1STORY2:
		Episode1_Story2();
		break;
	case STATE_EP1STORY3:
		Episode1_Story3();
		break;
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
	case STATE_EP1STAGE_4:
		Episode1_Stage();
		break;
	case STATE_EP2STORY:
		Episode2_Story();
		break;
	case STATE_EP2STORY2:
		Episode2_Story2();
		break;
	case STATE_EP2STORY3:
		Episode2_Story3();
		break;
	case STATE_EP2STORY4:
		Episode2_Story4();
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
	case STATE_EP2STAGE_3:
		Episode2_Stage();
		break;
	case STATE_END:
		EndRole();
		break;
	case GAME_OVER:
	case GAME_OVER2:
		GameOverProcess();
		break;
	default:
		break;
	}
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �t���[�������F�`��
void FrameDraw() {
	// ��Ԃ��Ƃɕ`��𕪂���
	switch (stateStage) {
	case STATE_TITLE:
		DrawTitleProcess();
		break;
	case STATE_EP1STORY:
		DrawEp1SProcess();
		break;
	case STATE_EP1STORY2:
		DrawEp1S2Process();
		break;
	case STATE_EP1STORY3:
		DrawEp1S3Process();
		break;
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
	case STATE_EP1STAGE_4:
		DrawEp1LProcess();
		break;
	case STATE_EP2STORY:
		DrawEp2SProcess();
		break;
	case STATE_EP2STORY2:
		DrawEp2S2Process();
		break;
	case STATE_EP2STORY3:
		DrawEp2S3Process();
		break;
	case STATE_EP2STORY4:
		DrawEp2S4Process();
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
	case STATE_EP2STAGE_3:
		DrawEp2LProcess();
		break;
	case STATE_END:
		DrawEnd();
		break;
	case GAME_OVER:
		if ((bgstage == STATE_EP1STAGE) || (bgstage == STATE_EP1STAGE_2) || (bgstage == STATE_EP1STAGE_3) || (bgstage == STATE_EP1STAGE_4)) {
			DrawEp1LProcess();
		}
		if (stateStage == GAME_OVER) {
			DrawGameOver();
		}
		Flip();
		break;
	case GAME_OVER2:
		if ((bgstage2 == STATE_EP2STAGE1_1) || (bgstage2 == STATE_EP2STAGE1_2) || (bgstage2 == STATE_EP2STAGE1_3) || (bgstage2 == STATE_EP2STAGE2_1) || (bgstage2 == STATE_EP2STAGE2_2) || (bgstage2 == STATE_EP2STAGE_3)) {
			DrawEp2LProcess();
		}
		if (stateStage == GAME_OVER2) {
			DrawGameOver();
		}
		Flip();
		break;
	default:
		break;
	}
}

