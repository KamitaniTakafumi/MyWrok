#pragma once

// マップのサイズ(チップ数)

// ステージ1 マップサイズ
#define MAPSIZE2_1_1_W 66
#define MAPSIZE2_1_1_H 69
#define MAPSIZE2_1_2_W 59
#define MAPSIZE2_1_2_H 60
#define MAPSIZE2_1_3_W 65
#define MAPSIZE2_1_3_H 27
#define MAPSIZE2_2_1_W 46
#define MAPSIZE2_2_1_H 52
#define MAPSIZE2_2_2_W 32
#define MAPSIZE2_2_2_H 16
#define MAPSIZE2_3_W 37
#define MAPSIZE2_3_H 40

// レイヤー数

// ステージ1 レイヤー
#define MAPSIZE2_1_1_LAYER 6
#define MAPSIZE2_1_1_LAYER_LM 2
#define MAPSIZE2_1_1_LAYER_HD 1
#define MAPSIZE2_1_2_LAYER 8
#define MAPSIZE2_1_2_LAYER_HD 1
#define MAPSIZE2_1_3_LAYER 5
#define MAPSIZE2_1_3_LAYER_LM 2
#define MAPSIZE2_1_3_LAYER_HD 1
#define MAPSIZE2_2_1_LAYER 6
#define MAPSIZE2_2_1_LAYER_LM 2
#define MAPSIZE2_2_1_LAYER_HD 1
#define MAPSIZE2_2_2_LAYER 5
#define MAPSIZE2_3_LAYER 6
#define MAPSIZE2_3_LAYER_HD 1

// チップ個数
#define CHIPCOUNT 225		// tilecount
#define CHIPCOUNT_W 15		// columns
#define CHIPCOUNT_H (CHIPCOUNT / CHIPCOUNT_W)	// 計算で出す

// チップのサイズ（pixel数）
#define	CHIPSIZE_W	40
#define	CHIPSIZE_H	40

//
// グローバル変数宣言
//

// Episode01 ステージマップチップ

extern int nMap_2_1_1[MAPSIZE2_1_1_LAYER * MAPSIZE2_1_1_W * MAPSIZE2_1_1_H];
extern int nMaplm_2_1_1[MAPSIZE2_1_1_LAYER_LM * MAPSIZE2_1_1_W * MAPSIZE2_1_1_H];
extern int nMaphd_2_1_1[MAPSIZE2_1_1_LAYER_HD * MAPSIZE2_1_1_W * MAPSIZE2_1_1_H];
extern int nMap_2_1_2[MAPSIZE2_1_2_LAYER * MAPSIZE2_1_2_W * MAPSIZE2_1_2_H];
extern int nMaphd_2_1_2[MAPSIZE2_1_2_LAYER_HD * MAPSIZE2_1_2_W * MAPSIZE2_1_2_H];
extern int nMap_2_1_3[MAPSIZE2_1_3_LAYER * MAPSIZE2_1_3_W * MAPSIZE2_1_3_H];
extern int nMaplm_2_1_3[MAPSIZE2_1_3_LAYER_LM * MAPSIZE2_1_3_W * MAPSIZE2_1_3_H];
extern int nMaphd_2_1_3[MAPSIZE2_1_3_LAYER_HD * MAPSIZE2_1_3_W * MAPSIZE2_1_3_H];
extern int nMap_2_2_1[MAPSIZE2_2_1_LAYER * MAPSIZE2_2_1_W * MAPSIZE2_2_1_H];
extern int nMaplm_2_2_1[MAPSIZE2_2_1_LAYER_LM * MAPSIZE2_2_1_W * MAPSIZE2_2_1_H];
extern int nMaphd_2_2_1[MAPSIZE2_2_1_LAYER_HD * MAPSIZE2_2_1_W * MAPSIZE2_2_1_H];
extern int nMap_2_2_2[MAPSIZE2_2_2_LAYER * MAPSIZE2_2_2_W * MAPSIZE2_2_2_H];
extern int nMap_2_3[MAPSIZE2_3_LAYER * MAPSIZE2_3_W * MAPSIZE2_3_H];
extern int nMaphd_2_3[MAPSIZE2_3_LAYER_HD * MAPSIZE2_3_W * MAPSIZE2_3_H];

extern int cgChip2[CHIPCOUNT];

void LoadCgMapChip_2();

// ステージ1マップ

void DrawMapChip_2_1_1();
void DrawMapChiplm_2_1_1();
void DrawMapChiphd_2_1_1();
void DrawMapChip_2_1_2();
void DrawMapChiphd_2_1_2();
void DrawMapChip_2_1_3();
void DrawMapChiplm_2_1_3();
void DrawMapChiphd_2_1_3();
void DrawMapChip_2_2_1();
void DrawMapChiplm_2_2_1();
void DrawMapChiphd_2_2_1();
void DrawMapChip_2_2_2();
void DrawMapChip_2_3();
void DrawMapChiphd_2_3();
