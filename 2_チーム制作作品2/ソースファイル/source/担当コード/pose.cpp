/*
 * @file pose.cpp
 * @brief ポーズ処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "SceneMain.h"
#include "Framework.h"
#include "player.h"
#include "object.h"
#include "Texture.h"
#include "title.h"

int gPoseSelectNumber;					// セレクト

/*
 * 初期化
 */
void InitPose()
{
	gPoseSelectNumber = 0;
}

/*
 * 更新
 */
int PoseMenu()
{
	// セレクトを移動
	if (gTrg1 & KEYIN_RIGHT)
	{
		gPoseSelectNumber++;
	}
	if (gTrg1 & KEYIN_LEFT)
	{
		gPoseSelectNumber--;
	}
	// セレクトのループ
	if (gPoseSelectNumber >= 2)
	{
		gPoseSelectNumber = 0;
	}
	if (gPoseSelectNumber < 0)
	{
		gPoseSelectNumber = 1;
	}
	// ゲーム画面に戻る
	if ((gTrg1 & KEYIN_Z) && gPoseSelectNumber == 0)
	{
		gGameMode.Mode = GAME_IN;
		gPoseSelectNumber = 0;

		return GAME_IN;
	}
	if ((gTrg1 & KEYIN_Z) && gPoseSelectNumber == 1)
	{
		ResetGame(GAME_TITLE);
		gPoseSelectNumber = 0;

		return GAME_TITLE;
	}

	return GAME_POSE;
}

/*
 * 描画
 */
void DrawPose()
{
	int i = 0, j = 0;

	BeginScene();
	// 背景描画
	DrawOutGame(0, 0, POSE);			// タイトル背景
	// 選択描画
	if (gPoseSelectNumber == 0)
	{
		j = j - 50;
	}
	else if (gPoseSelectNumber == 1)
	{
		i = i - 50;
	}
	DrawOutGame(200, 360 - i, BACK);			// タイトル背景
	DrawOutGame(660, 360 - j, TITLEBACK);			// タイトル背景

	EndScene();
	frm.dwRCurFrame++;	//	描画フレーム数更新
}
