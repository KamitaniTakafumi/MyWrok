#pragma once
/*------------------------------------------------
*  @file episode1S.cpp
*  @brief ストーリーパート1_1
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// フェード初期化
void initblackin_ep1s();
// Episode1のストーリに飛ばす
int IntoEpisode1S();
// Episode1の設定
int Episode1_Story();
// テキストの表示
void DrawStoryTexte1();
// フェードイン
void blackfadein_ep1s();
// フェードアウト
void blackfadeout_ep1s();
// ストーリーパートの描画
void DrawEp1SProcess();