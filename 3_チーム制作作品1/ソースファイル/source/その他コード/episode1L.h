#pragma once
/*------------------------------------------------
*  @file episode1L.cpp
*  @brief メインゲーム処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

extern int fadein;				// フェードイン
extern int fadeout;				// フェードアウト
extern int OperationFlag;		// フラグ

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// 画像読み込み、初期化
int IntoEpisode1L();
// 画像読み込み、初期化
int IntoEpisode1L_Re();
// 画像読み込み、初期化
int IntoEpisode1L_4();
// メインゲームの中身
int Episode1_Stage();
// メインゲームの描画
void DrawEp1LProcess();