/*------------------------------------------------
*  @file end.cpp
*  @brief �G���h���[������
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
#include	"global.h"
#include	"end.h"
#include	"changeroom.h"
#include	"title.h"
#include	"HitJudgment.h"
#include	"episode1L.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

int cgBg;			// �w�i
int cgStaffrole;	// �X�^�b�t���[��
int countend;		// �X�N���[���̎���

// �G���h���[�����
struct END end;

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
int IntoEnd() {
	end.x = 0;
	end.y = 720;
	end.w = 1280;
	end.h = 5400;
	end.vx = 0;
	end.vy = 2;
	end.use = 1;
	countend = 0;
	fadeout = 90;

	cgBg = LoadTexture("res/endbg2.jpg");
	cgStaffrole = LoadTexture("res/staffrole.png");

	initblackin_ep3();

	PlayMemLoop(bgmEnd);			  // BGM�Đ��X�^�[�g
	stateStage = STATE_END;
	return STATE_END;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
void EndRole() {
	// �X�^�b�t���[�����X�N���[������
	end.y -= end.vy;
	countend += end.vy;

	// �Ō�܂ŃX�N���[�����I�������^�C�g���ɖ߂�
	if (countend >= 6800) {
		end.use = 0;
		stateStage = STATE_TITLE;
		clearflag = 0;
		bgstage = STATE_EP1STAGE;
		bgstage2 = STATE_EP2STAGE1_1;
		StopPlayMem(bgmEnd);			  // BGM�Đ��X�^�[�g
		PlayMemLoop(bgmTitle);			  // BGM�Đ��X�^�[�g
		intoTitle();
	}
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/
void DrawEnd() {

	// ��ʂ�����
	HCls();

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// count���I���܂ŕ`��
	if (end.use = 1) {
		DrawMem(0, 0, cgBg);
		SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
		DrawFBox(0, 0, DISP_W, DISP_H, GetColor(255, 255, 255));
		SetDrawMode(AMDRAW_NOBLEND, 0);
		DrawMemTh(end.x, end.y, cgStaffrole);
	}

	// �u���b�N�t�F�[�h�A�E�g
	blackfadein_ep3();
	blackfadeout_ep3();
	operationfadeout();

	Flip();
}
