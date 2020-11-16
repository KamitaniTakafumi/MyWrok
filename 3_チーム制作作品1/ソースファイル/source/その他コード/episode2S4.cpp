/*------------------------------------------------
*  @file episode2S4.cpp
*  @brief �X�g�[���[�p�[�g2_4
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
#include	"episode2S4.h"
#include	"episode2L.h"
#include	"mapdata_2.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"
#include	"end.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int Skipflag7;			// �X�L�b�v�t���O
int bi_alpha_ep2s4_fi;	// �t�F�[�h�C��
int bi_alpha_ep2s4_fo;	// �t�F�[�h�A�E�g

/*-------------------------------------------------
*  ������
-------------------------------------------------*/

// ������
int IntoEpisode2S4()
{
	Skipflag7 = 0;
	ScriptCreate();
	initblackin_ep2s4();
	return STATE_EP2STORY4;
}

// �t�F�[�h������
void initblackin_ep2s4()
{
	bi_alpha_ep2s4_fi = 0;
	bi_alpha_ep2s4_fo = 255;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
int Episode2_Story4()
{
	// �Q�[���̍X�V
	ScriptUpdate();

	// �L�[���͂̍X�V
	InputMgrUpdate();

	// �X�g�[���[���I�������t�F�[�h�A�E�g���Ă���
	if (Endflag > 1)
	{
		bi_alpha_ep2s4_fi += 5;
	}

	if (Endflag == 60)
	{
		StopAllEpisodeMusic();
		return IntoEnd();
	}

	return STATE_EP2STORY4;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �t�F�[�h�A�E�g
void blackfadeout_ep2s4()
{

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s4_fo);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha_ep2s4_fo > 0)
	{
		bi_alpha_ep2s4_fo -= 15;
	}

}

// �t�F�[�h�C��
void blackfadein_ep2s4()
{
	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha_ep2s4_fi);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
}

// �X�g�[���[�p�[�g�̕`��
void DrawEp2S4Process()
{

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// ��ʂ�����
	HCls();

	// �Q�[���̕`��
	ScriptRender();

	// �t�F�[�h�C���E�A�E�g�`��
	blackfadein_ep2s4();
	blackfadeout_ep2s4();

	// �X�V
	Flip();

}