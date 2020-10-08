#pragma once
/*------------------------------------------------
*  @file episode2S.cpp
*  @brief ストーリーパート2_1
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// フェード初期化
void initblackin_ep2s();
// Episode2のストーリに飛ばす
int IntoEpisode2S();
// Episode2の設定
int Episode2_Story();
// フェードイン
void blackfadein_ep2s();
// フェードアウト
void blackfadeout_ep2s();
// ストーリーパートの描画
void DrawEp2SProcess();