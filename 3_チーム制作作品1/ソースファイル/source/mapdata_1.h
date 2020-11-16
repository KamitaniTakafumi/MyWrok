#pragma once


// �}�b�v�̃T�C�Y(�`�b�v��)
// <layer name = "�^�C���E���C���[1" width = "64" height = "36">

// �X�e�[�W1 �}�b�v�T�C�Y
#define MAPSIZE_W 64
#define MAPSIZE_H 36

#define MAPSIZE_W_2 64
#define MAPSIZE_H_2 54

#define MAPSIZE_W_3 70
#define MAPSIZE_H_3 60

#define MAPSIZE_W_4 37
#define MAPSIZE_H_4 28

// ���C���[��

// �X�e�[�W1 ���C���[
#define MAPSIZE_LAYER 23
#define MAPSIZE_LAYER_HD 2
#define MAPSIZE_LAYER_2 24
#define MAPSIZE_LAYER_2_LM 2
#define MAPSIZE_LAYER_2_HD 3
#define MAPSIZE_LAYER_3 22
#define MAPSIZE_LAYER_3_LM 2
#define MAPSIZE_LAYER_3_HD 5
#define MAPSIZE_LAYER_4 12
#define MAPSIZE_LAYER_4_HD 2

// �`�b�v�摜��
//  <tileset firstgid="1" name="Tile" tilewidth="40" tileheight="40" tilecount="150" columns="15">

// �`�b�v��
#define CHIPCOUNT 225		// tilecount
#define CHIPCOUNT_W 15		// columns
#define CHIPCOUNT_H (CHIPCOUNT / CHIPCOUNT_W)	// �v�Z�ŏo��


// �`�b�v�̃T�C�Y�ipixel���j
#define	CHIPSIZE_W	40
#define	CHIPSIZE_H	40

//
// �O���[�o���ϐ��錾
//

// Episode01 �X�e�[�W�}�b�v�`�b�v

extern int nMap[MAPSIZE_LAYER * MAPSIZE_W * MAPSIZE_H];
extern int nMaphd[MAPSIZE_LAYER_HD * MAPSIZE_W * MAPSIZE_H];
extern int nMap2[MAPSIZE_LAYER_2 * MAPSIZE_W_2 * MAPSIZE_H_2];
extern int nMap2lm[MAPSIZE_LAYER_2_LM * MAPSIZE_W_2 * MAPSIZE_H_2];
extern int nMap2hd[MAPSIZE_LAYER_2_HD * MAPSIZE_W_2 * MAPSIZE_H_2];
extern int nMap3[MAPSIZE_LAYER_3 * MAPSIZE_W_3 * MAPSIZE_H_3];
extern int nMap3lm[MAPSIZE_LAYER_3_LM * MAPSIZE_W_3 * MAPSIZE_H_3];
extern int nMap3hd[MAPSIZE_LAYER_3_HD * MAPSIZE_W_3 * MAPSIZE_H_3];
extern int nMap4[MAPSIZE_LAYER_4 * MAPSIZE_W_4 * MAPSIZE_H_4];
extern int nMap4hd[MAPSIZE_LAYER_4_HD * MAPSIZE_W_4 * MAPSIZE_H_4];

extern int cgChip[CHIPCOUNT];



void LoadCgMapChip_1();


// �X�e�[�W1�}�b�v

void DrawMapChip_1();
void DrawMapChiphd_1 ();

void DrawMapChip_2();
void DrawMapChiplm_2();
void DrawMapChiphd_2 ();

void DrawMapChip_3();
void DrawMapChiplm_3();
void DrawMapChiphd_3 ();

void DrawMapChip_4();
void DrawMapChiphd_4 ();