#pragma once
/*------------------------------------------------
*  @file title.cpp
*  @brief タイトル処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  定数定義
------------------------------------------------*/

// マップスクロール関連
#define	TITLESIZE_W		(DISP_W)		// マップ全体の大きさ(pixel)
#define	TITLESIZE_H		10000

#define	BGSIZE_W		320		// マップチップ画像の大きさ(pixel)
#define	BGSIZE_H		320

#define	SCROLL_SPEED	1		// スクロール速度

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

extern int gCamViewX, gCamViewY;		// カメラ位置（画面左上）

/*------------------------------------------------
*  構造体定義
------------------------------------------------*/

// カーソルの構造体
struct CURSOR {
	int x, y;	// 座標
};

// カーソル情報
extern struct CURSOR curpos;

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// タイトルに入る
int intoTitle();
// タイトル選択
int titleSelect();
// カーソル初期設定
void cursorInit();
// タイトル画像読み込み
void LoadCgTitle();
// タイトルの表示
void DrawTitle();
// カーソル表示
void DrawCursor();
// 背景表示
void DrawBg();
// 背景処理
void BgScroll();
// 背景描画
void DrawScrollBg();
// フェードイン
void blackfadein();
// フェードアウト
void blackfadeout();
// 描画
void DrawTitleProcess();
