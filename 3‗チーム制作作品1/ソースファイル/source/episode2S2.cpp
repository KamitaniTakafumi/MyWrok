/*------------------------------------------------
*  @file episode2S2.cpp
*  @brief �X�g�[���[�p�[�g2_2
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
#include	"episode2S2.h"
#include	"episode2L.h"
#include	"mapdata_2.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int Skipflag5;			// �X�L�b�v�t���O
int bi_alpha_ep2s2_fi;	// �t�F�[�h�C��
int bi_alpha_ep2s2_fo;	// �t�F�[�h�A�E�g

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// ������
int IntoEpisode2S2()
{
	Skipflag5 = 0;
	ScriptCreate();
	initblackin_ep2s2();
	return STATE_EP2STORY2;
}

// �t�F�[�h������
void initblackin_ep2s2() {
	Skipflag5 = 0;
	bi_alpha_ep2s2_fi = 0;
	bi_alpha_ep2s2_fo = 255;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
int Episode2_Story2() {
	// �Q�[���̍X�V
	ScriptUpdate();

	// �L�[���͂̍X�V
	InputMgrUpdate();

	// ����̃{�^���������ꂽ��t���O�𗧂Ă�
	if (gTrg & KEYIN_Q) {
		Skipflag5 = 1;
	}

	// �X�L�b�v�t���O����������X�g�[���[�I��
	if (Skipflag5 == 1) {
		Endflag += 1;
	}

	// �X�g�[���[���I�������t�F�[�h�A�E�g���Ă���
	if (Endflag > 1) {
		bi_alpha_ep2s2_fi += 15;
	}

	if (Endflag == 30) {
		StopAllEpisodeMusic();
		bi_alpha_ep2s2_fi = 0;
		bi_alpha_ep2s2_fo = 0;
		stateStage = STATE_EP2STAGE_3;
		return IntoEpisode2L_3_1();
	}

		return STATE_EP2STORY2;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �t�F�[�h�A�E�g
void blackfadeout_ep2s2()
{

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s2_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2s2_fo > 0)
	{
		bi_alpha_ep2s2_fo -= 15;
	}

}

// �t�F�[�h�C��
void blackfadein_ep2s2()
{
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s2_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// �X�g�[���[�p�[�g�̕`��
void DrawEp2S2Process()
{

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// ��ʂ�����
	HCls();

	// �Q�[���̕`��
	ScriptRender();

	// �t�F�[�h�C���E�A�E�g�`��
	blackfadein_ep2s2();
	blackfadeout_ep2s2();

	// �X�V
	Flip();

}