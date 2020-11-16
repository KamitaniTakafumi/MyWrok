/*------------------------------------------------
*  @file camera.cpp
*  @brief カメラ処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ヘッダーファイルのインクルード
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
*  グローバル変数
-------------------------------------------------*/

// カメラ情報
struct CAMERAVIEW cv;

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
void cameraInit() {
	cv.view_x = 0;
	cv.view_y = 0;
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/
void cameraProcess() {
	// 主人公位置からのカメラ座標決定
	cv.view_x = al.x - (DISP_W / 2);		// 画面の横中央にキャラを置く
	cv.view_y = al.y - (DISP_H / 2);		// 画面の縦中央にキャラを置く

	// カメラがマップデータを超えないようにする
	switch (stateStage) {
	case STATE_EP1STAGE:	// ステージ1_1
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP1STAGE_2:	// ステージ1_2
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W_2 * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W_2 * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H_2 * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H_2 * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP1STAGE_3:	// ステージ1_3
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W_3 * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W_3 * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H_3 * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H_3 * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP1STAGE_4:	// ステージ1_4
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE_W_4 * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE_W_4 * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE_H_4 * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE_H_4 * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE1_1:	// ステージ2_1_1
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_1_1_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_1_1_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_1_1_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_1_1_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE1_2:	// ステージ2_1_2
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_1_2_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_1_2_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_1_2_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_1_2_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE1_3:	// ステージ2_1_3
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_1_3_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_1_3_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_1_3_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_1_3_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE2_1:	// ステージ2_2_1
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_2_1_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_2_1_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_2_1_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_2_1_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE2_2:	// ステージ2_2_2
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_2_2_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_2_2_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_2_2_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_2_2_H * CHIPSIZE_H - DISP_H; }
		break;
	case STATE_EP2STAGE_3:	// ステージ2_3
		if (cv.view_x < 0) { cv.view_x = 0; }
		if (cv.view_x > MAPSIZE2_3_W * CHIPSIZE_W - DISP_W) { cv.view_x = MAPSIZE2_3_W * CHIPSIZE_W - DISP_W; }
		if (cv.view_y < 0) { cv.view_y = 0; }
		if (cv.view_y > MAPSIZE2_3_H * CHIPSIZE_H - DISP_H) { cv.view_y = MAPSIZE2_3_H * CHIPSIZE_H - DISP_H; }
		break;
	}
}

// カメラから見た座標に変更（ワールド座標→ビュー座標）
void worldToView() {
	int x, y;
	x = al.x - cv.view_x;
	y = al.y - cv.view_y;
}