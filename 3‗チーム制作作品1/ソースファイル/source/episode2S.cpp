/*------------------------------------------------
*  @file episode2S.cpp
*  @brief �X�g�[���[�p�[�g2_1
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �w�b�_�[�t�@�C���̃C���N���[�h
------------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include <stdint.h>
#include <crtdbg.h>
#include	"script_parser.h"
#include "input_manager.h"
#include "camera.h"
#include	"game.h"
#include	"episode2S.h"
#include	"episode2L.h"
#include	"mapdata_1.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int Skipflag4;			// �X�L�b�v�t���O
int bi_alpha_ep2s_fi;	// �t�F�[�h�C��
int bi_alpha_ep2s_fo;	// �t�F�[�h�A�E�g

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// ������
int IntoEpisode2S()
{
	Skipflag4 = 0;
	ScriptCreate();
	initblackin_ep2s();
	return STATE_EP2STORY;
}

// �t�F�[�h������
void initblackin_ep2s()
{
	bi_alpha_ep2s_fi = 0;
	bi_alpha_ep2s_fo = 255;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
int Episode2_Story()
{

	// �Q�[���̍X�V
	ScriptUpdate();

	// �L�[���͂̍X�V
	InputMgrUpdate();

	// ����̃{�^���������ꂽ��t���O�𗧂Ă�
	if (gTrg & KEYIN_Q)
	{
		Skipflag4 = 1;
	}

	// �X�L�b�v�t���O����������X�g�[���[�I��
	if (Skipflag4 == 1)
	{
		Endflag += 1;
	}

	// �X�g�[���[���I�������t�F�[�h�A�E�g���Ă���
	if (Endflag > 1)
	{
		bi_alpha_ep2s_fi += 15;
	}

	if (Endflag == 30)
	{
		StopAllEpisodeMusic();
		bi_alpha_ep2s_fi = 0;
		bi_alpha_ep2s_fo = 0;
		switch (bgstage2)
		{
		case STATE_EP2STAGE1_1:
			required_count = 0;
			wallflag = 2;
			//required_count = 8;		// �ǂ�����(�J���p)
			stateStage = STATE_EP2STAGE1_1;		// 1�͂̃X�e�[�W�ɔ��(�J���p)
			break;
		case STATE_EP2STAGE1_2:
			required_count = 0;
			wallflag = 2;
			stateStage = STATE_EP2STAGE1_1;		// 1�͂̃X�e�[�W�ɔ��(�J���p)
			break;
		case STATE_EP2STAGE1_3:
			required_count = 6;
			wallflag = 4;
			stateStage = STATE_EP2STAGE1_3;		// 1�͂̃X�e�[�W�ɔ��(�J���p)
			break;
		case STATE_EP2STAGE2_1:
			required_count = 3;
			wallflag = 3;
			stateStage = STATE_EP2STAGE2_1;	// 2�X�e�[�W�Ɉړ�(�J���p)
			break;
		case STATE_EP2STAGE2_2:
			required_count = 8;
			wallflag = 5;
			stateStage = STATE_EP2STAGE2_2;	// 2�X�e�[�W�Ɉړ�(�J���p)
			break;
		case STATE_EP2STAGE_3:
			required_count = 8;
			wallflag = 5;
			stateStage = STATE_EP2STAGE2_2;	// 3�X�e�[�W�Ɉړ�(�J���p)
			break;
		}
		return IntoEpisode2L();
	}

	return STATE_EP2STORY;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �t�F�[�h�A�E�g
void blackfadeout_ep2s()
{

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2s_fo > 0)
	{
		bi_alpha_ep2s_fo -= 15;
	}

}

// �t�F�[�h�C��
void blackfadein_ep2s()
{
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// �X�g�[���[�p�[�g�̕`��
void DrawEp2SProcess()
{

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// ��ʂ�����
	HCls();

	// �Q�[���̕`��
	ScriptRender();

	// �t�F�[�h�C���E�A�E�g�`��
	blackfadein_ep2s();
	blackfadeout_ep2s();

	// �X�V
	Flip();

}