/*
 * @file Fade.cpp
 * @brief フェード処理
 * @author 上谷恭史
 * @date 2020 / 03 / 21
 */

#include "library.h"
#include "game.h"
#include "SceneMain.h"

int gFadeIn;			// フェードイン
int gFadeOut;		// フェードアウト

void InitFade()// フェード初期化
{
	gFadeIn = 255;
	gFadeOut = 0;
}

// フェードインが終わったか
bool FadeInFlag()
{
	if (gFadeIn > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// フェードアウトが終わったか
bool FadeOutFlag()
{
	if (gFadeOut < 255)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// ブラックフェードイン
void WhiteFadeIn()
{
	SetDrawMode(DRAW_ALPHABLEND, gFadeIn);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(NULL, 0, 0, 0));
	if (gFadeIn > 0)
	{
		gFadeIn -= 15;
	}

}

// ブラックフェードアウト
void WhiteFadeOut()
{
	SetDrawMode(DRAW_ALPHABLEND, gFadeOut);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(NULL, 0, 0, 0));
	if (gFadeOut < 255)
	{
		gFadeOut += 15;
	}

}
