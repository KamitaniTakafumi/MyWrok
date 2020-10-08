/*------------------------------------------------
*  @file episode1S3.cpp
*  @brief �X�g�[���[�p�[�g1_3
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
#include	"episode1S3.h"
#include	"episode2S.h"
#include	"episode2L.h"
#include	"mapdata_1.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int Skipflag3;			// �X�L�b�v�t���O
int bi_alpha_ep1s3_fi;	// �t�F�[�h�C��
int bi_alpha_ep1s3_fo;	// �t�F�[�h�A�E�g

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// ������
int IntoEpisode1S3()
{
	Skipflag3 = 0;
	ScriptCreate();
	initblackin_ep1s3();
	return STATE_EP1STORY3;
}

// �t�F�[�h������
void initblackin_ep1s3()
{
	bi_alpha_ep1s3_fi = 0;
	bi_alpha_ep1s3_fo = 255;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
int Episode1_Story3()
{

	// �Q�[���̍X�V
	ScriptUpdate();

	// �L�[���͂̍X�V
	InputMgrUpdate();

	// ����̃{�^���������ꂽ��t���O�𗧂Ă�
	if (gTrg & KEYIN_Q)
	{
		Skipflag3 = 1;
	}

	// �X�L�b�v�t���O����������X�g�[���[�I��
	if (Skipflag3 == 1)
	{
		Endflag += 1;
	}

	// �X�g�[���[���I�������t�F�[�h�A�E�g���Ă���
	if (Endflag > 1)
	{
		bi_alpha_ep1s3_fi += 15;
	}

	if (Endflag == 30)
	{
		StopAllEpisodeMusic();
		bi_alpha_ep1s3_fi = 0;
		bi_alpha_ep1s3_fo = 0;
		stateStage = STATE_EP2STORY;
		return IntoEpisode2S();
	}

	return STATE_EP1STORY3;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �t�F�[�h�A�E�g
void blackfadeout_ep1s3()
{

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s3_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep1s3_fo > 0)
	{
		bi_alpha_ep1s3_fo -= 15;
	}

}

// �t�F�[�h�C��
void blackfadein_ep1s3()
{
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s3_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// �X�g�[���[�p�[�g�̕`��
void DrawEp1S3Process()
{

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// ��ʂ�����
	HCls();

	// �Q�[���̕`��
	ScriptRender();

	// �t�F�[�h�C���E�A�E�g�`��
	blackfadein_ep1s3();
	blackfadeout_ep1s3();

	// �X�V
	Flip();

}