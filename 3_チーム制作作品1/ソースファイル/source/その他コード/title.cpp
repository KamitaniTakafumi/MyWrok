/*------------------------------------------------
*  @file title.cpp
*  @brief �^�C�g������
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �w�b�_�[�t�@�C���̃C���N���[�h
------------------------------------------------*/
#include	<Windows.h>
#include	<math.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"title.h"
#include	"script_parser.h"
#include	"episode1S.h"
#include	"episode2S.h"
#include	"episode1L.h"
#include	"episode2L.h"
#include	"global.h"
#include	"HitJudgment.h"
#include	"UI.h"

/*------------------------------------------------
*  �萔��`
------------------------------------------------*/

#define	CURPOS_NUM			2	// �J�[�\���ʒu�̐�
#define CUR_MOVE_FRAME		7	// �J�[�\���ړ��̎���

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

// �摜�f�[�^
int cgTeamLogo;			// �`�[�����S
int	cgTitle;			// �^�C�g��
int cgTitleBg;			// �w�i
int cgCursor;			// �J�[�\��
int cgStartExit;		// �X�^�[�g�A�C�O�W�X�g
int cgChapterselect;	// ��́A���

int selectNumber;			// �I����
int selectMenu;				// �^�C�g���I��
int selectEpisode;			// �͑I��
float	xspan;				// ���h��̕�
int curmove_start_count;	// �J�[�\���ړ��J�n���J�E���g
int curmove_start_pos_y;	// �J�[�\���ړ���
int curmove_end_pos_y;		// �J�[�\���ړ���
int keyflag;				// �^�C�g���X�e�[�g
double bi_alpha = 255;		// �����x
double bo_alpha = 0;		// �����x
int gCamViewX, gCamViewY;	// �J�����ʒu�i��ʍ���j

// �J�[�\�����
struct CURSOR curpos;

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
// �J�[�\���ʒu
int curpos_y_table[] = {
	500,
	600
};

// �����ݒ�
int intoTitle() {

	stateStage = STATE_TITLE;
	selectNumber = 1;
	selectMenu = 0;
	selectEpisode = 0;
	keyflag = 0;
	bi_alpha = 255;
	bo_alpha = 0;

	// �J����������
	gCamViewX = 0;
	gCamViewY = TITLESIZE_H - DISP_H;

	return STATE_TITLE;
}

// �摜�f�[�^�̃��[�h
void LoadCgTitle() {
	cgTeamLogo = LoadTexture("res/TeamLogo.png");
	cgTitle = LoadTexture("res/alche_title.png");
	cgTitleBg = LoadTexture("res/titleBg.png");
	cgCursor = LoadTexture("res/alche_title_icon.png");
	cgStartExit = LoadTexture("res/alche_start_exit.png");
	cgChapterselect = LoadTexture("res/alche_chapter.png");
}

// �J�[�\��������
void cursorInit() {

	// �J����������
	gCamViewX = 0;
	gCamViewY = TITLESIZE_H - DISP_H;

	// ���j���[�I���̏�����
	selectNumber = 1;
	selectMenu = 0;

	// �J�[�\���ʒu�̏����ݒ�
	curpos.x = 510;
	curpos.y = curpos_y_table[selectMenu];
	xspan = 2;
	curmove_start_pos_y = curpos_y_table[selectMenu];
	curmove_end_pos_y = curpos_y_table[selectMenu];

	PlayMemLoop(bgmTitle);			  // BGM�Đ��X�^�[�g
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/

// �����ړ�
int LerpL(int cnt, int max, int start, int end) {
	int n;
	if (cnt >= max) {
		n = end;
	}
	else {
		n = start + (end - start) * (((max * 2 - cnt + 1) * cnt) / 2) / (((max + 1) * max) / 2);
	}
	return n;
}

// �^�C�g���I�����
int titleSelect() {
	/* �^�C�g���I����ʂ̐ݒ� */

	BgScroll();	// �w�i�𓮂���

	float rad = ((float)gFrameCount * (xspan)) * PI / 45;
	curpos.x = curpos.x + (int)(sin(rad) * xspan);

	// ��A���ɓ������đI�� 
	// �n�߂邩�Q�[������邩��I�� 
	if (selectNumber == 1) {
		int curpos_backup = selectMenu;
		if (gTrg & KEYIN_DOWN) {
			PlayMemBack(seCursor);
			selectMenu++;
		}
		if (gTrg & KEYIN_UP) {
			PlayMemBack(seCursor);
			selectMenu--;
		}

		selectMenu = (selectMenu + CURPOS_NUM) % CURPOS_NUM;

		if (curpos_backup != selectMenu) {
			// �ړ����n�܂����̂ŃA�j���[�V�����p�̒l���Z�b�g����
			curmove_start_count = gFrameCount;
			curmove_start_pos_y = curpos_y_table[curpos_backup];
			curmove_end_pos_y = curpos_y_table[selectMenu];
		}

		// �J�[�\���ʒu�v�Z
		curpos.y = LerpL(gFrameCount - curmove_start_count, CUR_MOVE_FRAME, curmove_start_pos_y, curmove_end_pos_y);

		if (gTrg & KEYIN_X) {
			PlayMemBack(seSelect);
			if (selectMenu == 0) {
				selectNumber = 2;	// �͑I���Ɉڂ�
				selectEpisode = 0;
				curpos.y = curpos_y_table[selectEpisode];
				curmove_start_pos_y = curpos_y_table[selectEpisode];
				curmove_end_pos_y = curpos_y_table[selectEpisode];
			}
			if (selectMenu == 1) {
				exit(0);			// ��ʂ����
			}
		}
		return STATE_TITLE;
	}

	/* �͑I�� */
	// ��͂���͂�I��
	if (selectNumber == 2) {
		int curpos_backup = selectEpisode;

		if (keyflag == 0) {
			if (gTrg & KEYIN_DOWN) {
				PlayMemBack(seCursor);
				selectEpisode++;
			}
			if (gTrg & KEYIN_UP) {
				PlayMemBack(seCursor);
				selectEpisode--;
			}
		}

		selectEpisode = (selectEpisode + CURPOS_NUM) % CURPOS_NUM;

		if (curpos_backup != selectEpisode) {
			// �ړ����n�܂����̂ŃA�j���[�V�����p�̒l���Z�b�g����
			curmove_start_count = gFrameCount;
			curmove_start_pos_y = curpos_y_table[curpos_backup];
			curmove_end_pos_y = curpos_y_table[selectEpisode];
		}

		// �J�[�\���ʒu�v�Z
		curpos.y = LerpL(gFrameCount - curmove_start_count, CUR_MOVE_FRAME, curmove_start_pos_y, curmove_end_pos_y);

		/* �X�e�[�W�ړ� */
		if (gTrg & KEYIN_X) {
			PlayMemBack(seSelect);
			if (keyflag == 0) {
				keyflag++;
			}
		}

		// 1�͂�I��
		if (selectEpisode == 0) {
			if (bo_alpha >= 255) {
				// BGM�Đ��X�g�b�v
				stateStage = STATE_EP1STORY;
				cursorInit();
				StopPlayMem(bgmTitle);
				ScriptDestroy();
				return IntoEpisode1S();		// �X�g�[���[�ɔ��
			}
		}
		// 2�͂�I��
		if (selectEpisode == 1) {
			if (clearflag < 1) {
				keyflag = 0;
			}
			else if (clearflag >= 1) {
				if (bo_alpha >= 255) {
					// BGM�Đ��X�g�b�v
					stateStage = STATE_EP2STORY;
					cursorInit();
					StopPlayMem(bgmTitle);
					return IntoEpisode2S();		// �X�g�[���[�ɔ��
				}
			}
		}

		// Escape�L�[�őO�̑I���ɖ߂�
		if (gTrg & KEYIN_Z) {
			if (keyflag == 0) {
				PlayMemBack(seCancel);
				if (selectNumber == 2) {
					selectNumber = 1;
					selectMenu = 0;
					curpos.y = curpos_y_table[selectMenu];
					curmove_start_pos_y = curpos_y_table[selectMenu];
					curmove_end_pos_y = curpos_y_table[selectMenu];
				}
			}
		}
	}
	return STATE_TITLE;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/

// �^�C�g���̕\��
void DrawTitle() {
	if (selectNumber == 1) {
		DrawMemTh(500, 460, cgStartExit);
	}
	if (selectNumber == 2) {
		DrawMemTh(500, 460, cgChapterselect);
	}
}

//	�J�[�\���̕\��
void DrawCursor() {
	DrawMemTh(curpos.x, curpos.y, cgCursor);
}

// �w�i�̕\��
void DrawBg() {
	DrawMemTh(420, 80, cgTitle);
	DrawMemTh(DISP_W - 320, DISP_H - 160, cgTeamLogo);
}

// �t�F�[�h�C��
void blackfadein() {
	// ��`

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha > 0) {
		bi_alpha -= 15;
	}
}

// �t�F�[�h�A�E�g
void blackfadeout() {
	// ��`

	SetDrawMode(AMDRAW_ALPHABLEND, bo_alpha);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (keyflag == 1) {
		if (bo_alpha < 255) {
			bo_alpha += 3;
		}
	}

}

// �w�i����
void BgScroll()
{
	gCamViewY -= SCROLL_SPEED;
}

// �w�i�`��
void DrawScrollBg()
{
	// �w�i�i�`�b�v�Ƃ��ē����摜����ׂĕ`�悷��j
	int x, y;
	for (y = 0; y < (TITLESIZE_H / BGSIZE_H) + 1; y++)
	{
		int pos_y = y * BGSIZE_H - gCamViewY;

		if (gCamViewY < 0) {
			gCamViewY = TITLESIZE_H - DISP_H;
		}

		// ��ʓ��ɉ摜�͈͂������Ă��邩�m�F�i�������p�j
		if (0 <= pos_y + BGSIZE_H && pos_y < DISP_H)
		{
			for (x = 0; x < (TITLESIZE_W / BGSIZE_W) + 1; x++)
			{
				int pos_x = x * BGSIZE_W - gCamViewX;
				// ��ʓ��ɉ摜�͈͂������Ă��邩�m�F�i�������p�j
				if (0 <= pos_x + BGSIZE_W && pos_x < DISP_W)
				{
					DrawMemTh(pos_x, pos_y, cgTitleBg);
				}
			}
		}
	}
}

// �`��
void DrawTitleProcess() {

	// ��ʂ�����
	HCls();

	//SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// �w�i
	DrawScrollBg(); // �^�C�g���w�i���X�N���[������

	// �摜 ////////////
	DrawBg();
	DrawTitle();	// �^�C�g���摜
	DrawCursor();	// �^�C�g���J�[�\��
	blackfadein();	// �t�F�[�h�C��
	blackfadeout();	// �t�F�[�h�A�E�g

	// �X�V
	Flip();

}