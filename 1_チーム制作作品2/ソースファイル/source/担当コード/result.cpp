/*
 * @file result.cpp
 * @brief リザルト処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "dslib.h"
#include "Framework.h"
#include "player.h"
#include "SceneMain.h"
#include "Texture.h"

int gResultPoint[4];	// 試合点数

/*
 * 更新
 */
int UpdateResult()
{
	if (gTrg1 & KEYIN_Z)
	{
		gGameMode.Mode = GAME_TITLE;
		DSoundStop(sndResult);

		// 曲データ演奏開始
		DSoundPlay(sndTitle, TRUE);

		ReleaseStage();				// ステージのリリース

		return GAME_TITLE;
	}

	return GAME_RESULT;
}

/*
 * 描画
 */
void DrawResult()
{
	int i;
	BeginScene();
	DrawOutGame(0, 0, RESULT);// 背景描画
	// 試合点数描画
	for (i = 0; i < gJoyPadNum; i++)
	{
		DrawPoint(i, gResultPoint[i], GAME_RESULT);
	}

	EndScene();
	frm.dwRCurFrame++;	//	描画フレーム数更新
}
