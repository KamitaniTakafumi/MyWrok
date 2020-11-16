/*------------------------------------------------
*  @file episode1S.cpp
*  @brief �X�g�[���[�p�[�g1_1
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
#include	"episode1S.h"
#include	"episode1L.h"
#include	"mapdata_1.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"
#include	"recipe.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int Skipflag;			// �X�L�b�v�t���O
int bi_alpha_ep1s_fi;	// �t�F�[�h�C��
int bi_alpha_ep1s_fo;	// �t�F�[�h�A�E�g

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// ������
int IntoEpisode1S() {
	Skipflag = 0;
	ScriptCreate();
	initblackin_ep1s();
	return STATE_EP1STORY;
}

// �t�F�[�h������
void initblackin_ep1s() {
	bi_alpha_ep1s_fi = 0;
	bi_alpha_ep1s_fo = 255;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
int Episode1_Story() {

	// �Q�[���̍X�V
	ScriptUpdate();

	// �L�[���͂̍X�V
	InputMgrUpdate();

	// ����̃{�^���������ꂽ��t���O�𗧂Ă�
	if (gTrg & KEYIN_Q){
		Skipflag = 1;
	}

	// �X�L�b�v�t���O����������X�g�[���[�I��
	if (Skipflag == 1)
	{
		Endflag += 1;
	}

	// �X�g�[���[���I�������t�F�[�h�A�E�g���Ă���
	if (Endflag > 1) {
		bi_alpha_ep1s_fi += 15;
	}

	if (Endflag == 30) {
		ScriptDestroy();
		StopAllEpisodeMusic();
		bi_alpha_ep1s_fi = 0;
		bi_alpha_ep1s_fo = 0;
		switch (bgstage) {
		case STATE_EP1STAGE:
			required_count = 0;
			wallflag = 0;
			stateStage = STATE_EP1STAGE;	// 1�͂̃X�e�[�W�ɔ��
			break;
		case STATE_EP1STAGE_2:
			required_count = 0;
			wallflag = 0;
			stateStage = STATE_EP1STAGE_2;	// 2�X�e�[�W�Ɉړ�
			break;
		case STATE_EP1STAGE_3:
			required_count = 2;
			wallflag = 1;
			stateStage = STATE_EP1STAGE_3;	// 3�X�e�[�W�Ɉړ�
			break;
		case STATE_EP1STAGE_4:
			required_count = 4;
			wallflag = 2;
			stateStage = STATE_EP1STAGE_3;
			break;
		}
		return IntoEpisode1L();
	}

	return STATE_EP1STORY;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �e�L�X�g�`��
void DrawStoryTexte1() {
	DrawString((DISP_W / 2), 100, "��1��", GetColor(0, 0, 0));
}

// �t�F�[�h�A�E�g
void blackfadeout_ep1s() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep1s_fo > 0) {
		bi_alpha_ep1s_fo -= 15;
	}

}

// �t�F�[�h�C��
void blackfadein_ep1s() {
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// �X�g�[���[�p�[�g�̕`��
void DrawEp1SProcess() {

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// ��ʂ�����
	HCls();

	// �Q�[���̕`��
	ScriptRender();

	// �t�F�[�h�C���E�A�E�g�`��
	blackfadein_ep1s();
	blackfadeout_ep1s();

	// �X�V
	Flip();

}