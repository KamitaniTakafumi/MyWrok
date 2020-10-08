/*
 * @file title.cpp
 * @brief タイトル処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "dslib.h"
#include "Framework.h"
#include "player.h"
#include "Texture.h"

int gStartSelectNumber;	// セレクト
int gStartStateNumber;	// 状態

/*
 * タイトル初期化
 */
void InitTitle()
{
	gStartSelectNumber = 0;
	gStartStateNumber = 0;
}

/*
 * タイトルセレクト
 */
int SelectTitle()
{
	// 最初の画面
	if (gStartStateNumber == 0)
	{
		if (gTrg1 & KEYIN_Z)
		{
			StartSE(DECISION);		// SE再生
			gStartStateNumber = 1;
		}
	}
	// 選択画面
	else if (gStartStateNumber == 1)
	{
		// セレクトを移動
		if (gTrg1 & KEYIN_RIGHT)
		{
			StartSE(SELECT);		// SE再生
			gStartSelectNumber++;
		}
		if (gTrg1 & KEYIN_LEFT)
		{
			StartSE(SELECT);		// SE再生
			gStartSelectNumber--;
		}
		// セレクトのループ
		if (gStartSelectNumber >= 2)
		{
			gStartSelectNumber = 0;
		}
		if (gStartSelectNumber < 0)
		{
			gStartSelectNumber = 1;
		}
		// ゲーム画面に移動
		if ((gTrg1 & KEYIN_Z) && gStartSelectNumber == 0)
		{
			StartSE(DECISION);		// SE再生
			gGameMode.Mode = GAME_LOAD;
			gGameMode.OutMode = GAME_TITLE;
			DSoundStop(sndTitle);
			gStartSelectNumber = 0;
			gStartStateNumber = 0;

			return GAME_LOAD;
		}
		// ゲーム終了
		else if ((gTrg1 & KEYIN_Z) && gStartSelectNumber == 1)
		{
			StartSE(DECISION);		// SE再生
			exit((gTrg1 & KEYIN_Z));
		}
		if (gTrg1 & KEYIN_X)
		{
			StartSE(CANCEL);		// SE再生
			gStartStateNumber = 0;
		}
	}

	return GAME_TITLE;
}

/*
 * タイトル描画
 */
void DrawTitle()
{
	BeginScene();
	if (gStartStateNumber == 0)
	{
		DrawOutGame(0, 0, TITLE);			// タイトル背景
		DrawOutGame(420, 350, HAZIMERU);	// 看板(始める)
	}
	else if (gStartStateNumber == 1)
	{
		DrawOutGame(0, 0, LOBBY);			// タイトル背景
		// どれを選んでいるか
		if (gStartSelectNumber == 0)
		{
			DrawOutGame(120, 400 - 50, START);	// 看板(プレイ)
			DrawOutGame(750, 400, END);			// 看板(終わる)
		}
		else if (gStartSelectNumber == 1)
		{
			DrawOutGame(120, 400, START);		// 看板(プレイ)
			DrawOutGame(750, 400 - 50, END);	// 看板(終わる)
		}
	}
	EndScene();
	frm.dwRCurFrame++;	//	描画フレーム数更新
}