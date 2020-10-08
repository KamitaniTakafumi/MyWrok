/*------------------------------------------------
*  @file gameover.cpp
*  @brief �Q�[���I�[�o�[����
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
#include	"gameover.h"
#include	"global.h"
#include	"HitJudgment.h"
#include	"script_parser.h"
#include	"title.h"
#include	"enemy.h"
#include	"episode1L.h"
#include	"episode2L.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

// �摜�f�[�^

int cgGameOver;			// �Q�[���I�[�o�[
int cgBack;				// �o�b�N

int GameOverAlpha;		// ���l(�Q�[���I�[�o�[)
int GameOverAlpha2;		// ���l(�o�b�N)

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
void LoadCgGameOver() {
	cgGameOver = LoadTexture("res/GameOver.png");
	cgBack = LoadTexture("res/back.png");
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/

// �Q�[���I�[�o�[�ɂȂ�����^�C�g���ɖ߂�
void GameOverProcess() {
	// ���l���v���X
	if (GameOverAlpha < 200) {

		GameOverAlpha += 5;

	}

	// �Q�[���I�[�o�[
	if (GameOverAlpha >= 200) {
		GameOverAlpha2 += 15;
		if (GameOverAlpha2 > 255) {
			// �R���e�B�j���[�{�^����������
			if (gTrg & KEYIN_X) {
				// ���̃X�e�[�W����n�߂�
				GameOverAlpha = 0;
				StopPlayMem(seDead);
				if (continueflag == 1) {
					stateStage = bgstage;
					if (stateStage == STATE_EP1STAGE_4) {
						stateStage = STATE_EP1STAGE_3;
					}
					IntoEpisode1L_Re();
				}
				else if (continueflag == 2) {
					stateStage = bgstage2;
					if (stateStage == STATE_EP2STAGE1_2) {
						stateStage = STATE_EP2STAGE1_1;
					}
					if (stateStage == STATE_EP2STAGE_3) {
						stateStage = STATE_EP2STAGE2_2;
					}
					IntoEpisode2L_Re();
				}
			}
			// �I���{�^����������
			if (gTrg & KEYIN_Z) {
				// �^�C�g���ɖ߂�
				int i;
				for (i = 0; i < ENEMY_MAX; i++) {
					en[i].required = 0;
				}
				GameOverAlpha = 0;
				StopPlayMem(seDead);
				PlayMemLoop(bgmTitle);			  // BGM�Đ��X�^�[�g
				ScriptDestroy();
				stateStage = STATE_TITLE;
				intoTitle();
			}
		}
	}
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// ��ʑS�̂ɍ��̔�����Box��킹��
void DrawGameOverBackground() {
	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_ALPHABLEND, GameOverAlpha);
	DrawFBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
}

// ���S
void DrawGameOverLogo() {
	SetDrawMode(AMDRAW_ALPHABLEND, GameOverAlpha2);
	DrawMemTh((DISP_W - 640) / 2, 120, cgGameOver);
	if (GameOverAlpha2 >= 255) {

		DrawMemTh((DISP_W - 640) - 150, 500, cgBack);
	}
}

// �Q�[���I�[�o�[�`��
void DrawGameOver() {
	if (stateStage == GAME_OVER)
	{
		DrawGameOverBackground();
		DrawGameOverLogo();

	}
	else if (stateStage == GAME_OVER2)
	{
		DrawGameOverBackground();
		DrawGameOverLogo();

	}
}