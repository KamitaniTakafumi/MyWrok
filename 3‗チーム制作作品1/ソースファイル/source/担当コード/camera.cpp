/*------------------------------------------------
*  @file camera.cpp
*  @brief �J��������
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
#include	"title.h"
#include	"episode1S.h"
#include	"episode1L.h"
#include	"mapdata_1.h"
#include	"mapdata_2.h"
#include	"Object.h"
#include	"alice.h"
#include	"global.h"
#include	"camera.h"

/*-------------------------------------------------
*  �O���[�o���ϐ�
-------------------------------------------------*/

// �J�������
struct CAMERAVIEW cv;

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
void cameraInit() {
	cv.view_x = 0;
	cv.view_y = 0;
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
void cameraProcess() {
	// ��l���ʒu����̃J�������W����
	cv.view_x = al.x - (DISP_W / 2);		// ��ʂ̉������ɃL������u��
	cv.view_y = al.y - (DISP_H / 2);		// ��ʂ̏c�����ɃL������u��

	// �J�������}�b�v�f�[�^�𒴂��Ȃ��悤�ɂ���
	switch (stateStage) {
	case STATE_EP1STAGE:	// �X�e�[�W1_1
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP1STAGE_2:	// �X�e�[�W1_2
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W_2 * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W_2 * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H_2 * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H_2 * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP1STAGE_3:	// �X�e�[�W1_3
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W_3 * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W_3 * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H_3 * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H_3 * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP1STAGE_4:	// �X�e�[�W1_4
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W_4 * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W_4 * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H_4 * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H_4 * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE1_1:	// �X�e�[�W2_1_1
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_1_1_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_1_1_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_1_1_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_1_1_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE1_2:	// �X�e�[�W2_1_2
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_1_2_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_1_2_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_1_2_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_1_2_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE1_3:	// �X�e�[�W2_1_3
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_1_3_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_1_3_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_1_3_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_1_3_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE2_1:	// �X�e�[�W2_2_1
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_2_1_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_2_1_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_2_1_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_2_1_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE2_2:	// �X�e�[�W2_2_2
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_2_2_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_2_2_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_2_2_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_2_2_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE_3:	// �X�e�[�W2_3
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_3_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_3_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_3_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_3_H * CHIPSIZE_H - DISP_H; }
		break;
	}
}

// �J�������猩�����W�ɕύX�i���[���h���W���r���[���W�j
void worldToView() {
	int x, y;
	x = al.x - cv.view_x;
	y = al.y - cv.view_y;
}