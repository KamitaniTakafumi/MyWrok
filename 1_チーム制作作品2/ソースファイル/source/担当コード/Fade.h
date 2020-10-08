#pragma once
/*
 * @file Fade.cpp
 * @brief フェード処理
 * @author 上谷恭史
 * @date 2020 / 03 / 21
 */

// フェード初期化
void InitFade();
// フェードインが終わったか
extern bool FadeInFlag();
// フェードアウトが終わったか
extern bool FadeOutFlag();
// ホワイトフェードイン
void WhiteFadeIn();
// ホワイトフェードアウト
void WhiteFadeOut();
