/*------------------------------------------------
*  @file episode1S2.cpp
*  @brief �X�g�[���[�p�[�g1_2
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
#include	"changeroom.h"
#include	"episode1S2.h"
#include	"episode1L.h"
#include	"mapdata_1.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h" 
#include	"mapdata_1.h"
#include	"HitJudgment.h"
#include	"camera.h"
#include	"Item.h"
#include	"UI.h"
#include	"enemy.h"
#include	"preparation.h"
#include	"Object.h"
#include	"Material.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int Skipflag2;			// �X�L�b�v�t���O
int bi_alpha_ep1s2_fi;	// �t�F�[�h�C��
int bi_alpha_ep1s2_fo;	// �t�F�[�h�A�E�g

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// ������
int IntoEpisode1S2() {
	Skipflag2 = 0;
	ScriptCreate();
	initblackin_ep1s2();
	return STATE_EP1STORY2;
}

// �t�F�[�h������
void initblackin_ep1s2() {
	Skipflag2 = 0;
	bi_alpha_ep1s2_fi = 0;
	bi_alpha_ep1s2_fo = 255;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
int Episode1_Story2() {

	// �Q�[���̍X�V
	ScriptUpdate();

	// �L�[���͂̍X�V
	InputMgrUpdate();

	// ����̃{�^���������ꂽ��t���O�𗧂Ă�
	if (gTrg & KEYIN_Q)
	{
		Skipflag2 = 1;
	}

	// �X�L�b�v�t���O����������X�g�[���[�I��
	if (Skipflag2 == 1)
	{
		Endflag += 1;
	}

	// �X�g�[���[���I�������t�F�[�h�A�E�g���Ă���
	if (Endflag > 1)
	{
		bi_alpha_ep1s2_fi += 15;
	}

	if (Endflag == 30)
	{
		//ScriptDestroy();
		StopAllEpisodeMusic();
		bi_alpha_ep1s2_fi = 0;
		bi_alpha_ep1s2_fo = 0;
		return IntoEpisode1L_4();
	}
	return STATE_EP1STORY2;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �t�F�[�h�A�E�g
void blackfadeout_ep1s2() {

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s2_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep1s2_fo > 0) {
		bi_alpha_ep1s2_fo -= 15;
	}

}

// �t�F�[�h�C��
void blackfadein_ep1s2() {

		SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep1s2_fi);
		DrawFBox(0, 0,
			1280, 720,
			GetColor(0, 0, 0));

}

// �X�g�[���[�p�[�g�̕`��
void DrawEp1S2Process() {

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// ��ʂ�����
	HCls();

	// �Q�[���̕`��
	ScriptRender();

	// �t�F�[�h�C���E�A�E�g�`��
	blackfadein_ep1s2();
	blackfadeout_ep1s2();

	// �X�V
	Flip();

}