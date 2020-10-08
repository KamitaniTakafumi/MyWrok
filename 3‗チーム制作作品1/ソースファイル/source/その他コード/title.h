#pragma once
/*------------------------------------------------
*  @file title.cpp
*  @brief �^�C�g������
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �萔��`
------------------------------------------------*/

// �}�b�v�X�N���[���֘A
#define	TITLESIZE_W		(DISP_W)		// �}�b�v�S�̂̑傫��(pixel)
#define	TITLESIZE_H		10000

#define	BGSIZE_W		320		// �}�b�v�`�b�v�摜�̑傫��(pixel)
#define	BGSIZE_H		320

#define	SCROLL_SPEED	1		// �X�N���[�����x

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

extern int gCamViewX, gCamViewY;		// �J�����ʒu�i��ʍ���j

/*------------------------------------------------
*  �\���̒�`
------------------------------------------------*/

// �J�[�\���̍\����
struct CURSOR {
	int x, y;	// ���W
};

// �J�[�\�����
extern struct CURSOR curpos;

/*-------------------------------------------------
*  �֐��錾
-------------------------------------------------*/

// �^�C�g���ɓ���
int intoTitle();
// �^�C�g���I��
int titleSelect();
// �J�[�\�������ݒ�
void cursorInit();
// �^�C�g���摜�ǂݍ���
void LoadCgTitle();
// �^�C�g���̕\��
void DrawTitle();
// �J�[�\���\��
void DrawCursor();
// �w�i�\��
void DrawBg();
// �w�i����
void BgScroll();
// �w�i�`��
void DrawScrollBg();
// �t�F�[�h�C��
void blackfadein();
// �t�F�[�h�A�E�g
void blackfadeout();
// �`��
void DrawTitleProcess();
