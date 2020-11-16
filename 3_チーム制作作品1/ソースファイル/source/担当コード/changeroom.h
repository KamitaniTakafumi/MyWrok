#pragma once
/*------------------------------------------------
*  @file changeroom.cpp
*  @brief ステージ移動処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// 初期設定
void initblackin_ep1 ();
// 初期設定
void initblackin_ep2();
// 初期設定
void initblackin_ep3();
// 画面を切り替える
void changeroom ();
// 壁破壊
void wallbreak();
// 壁破壊(ステージ２)
void wallbreak2();
// 画面を明るくしていく
void blackfadein_ep1 ();
// 画面を明るくしていく
void blackfadein_ep2();
// 画面を明るくしていく
void blackfadein_ep3();
// 画面を暗くしていく
void operationfadeout();
// 画面を暗くしていく
void blackfadeout_ep1 ();
// 画面を暗くしていく
void blackfadeout_ep2();
// 画面を暗くしていく
void blackfadeout_ep3();
// 素材獲得時のフェードイン、アウト
void Systemfadein_out();
// 調合時のフェードイン
void FirstCreatefadein();