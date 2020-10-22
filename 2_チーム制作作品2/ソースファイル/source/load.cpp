/*
 * @file load.cpp
 * @brief ロード処理
 * @author 上谷恭史
 * @date 2020 / 02 / 27
 */

#include "library.h"
#include "game.h"
#include "Texture.h"
#include "Framework.h"
#include "dslib.h"
#include "SceneMain.h"
#include "title.h"
#include "result.h"
#include "pose.h"
#include "player.h"
#include "Fade.h"

KT_2DPIC_INFO load, teamlogo;				// 画像情報
static int gFrame1;							// 初期化切り替え
static int gLoadSecond;						// ロード時間
static int gFadeFlag;						// フェード切り替え
static int gTimeStock, gTimeStock2;			// 時間の保存
static int gLoadFlag;						// ロード切り替え
static int gWaitTime;						// 待ち時間

/*
 * 初期化
 */
void InitLoad()
{
	gFrame1 = 0;
	gLoadSecond = 5000;
	gFadeFlag = 0;
	gTimeStock = 0;
	gTimeStock2 = 0;
	gLoadFlag = 0;
	gWaitTime = 60;
	gGameMode.Mode = GAME_LOAD;
	gGameMode.OutMode = GAME_LOAD;
	load = CreateTexture("res/load/loading.png");
	teamlogo = CreateTexture("res/load/team_logo.png");
	CreateSprit();
}

/*
 * 更新
 */
void Load()
{
	if (gWaitTime >= 0)
	{
		gWaitTime--;
	}
	else
	{
		if (gGameMode.OutMode == GAME_LOAD)
		{
			if (gLoadFlag == 0)
			{
				if (gFadeFlag == 0)
				{
					if (FadeInFlag() == true)
					{
						gFadeFlag = 1;
						gTimeStock = GetTickCount();
					}
				}

				if (gFadeFlag == 1)
				{
					while (true)
					{
						if (gFrame1 < 4)
						{
							if (gFrame1 == 0)
							{
								InitSound();					// サウンド初期化
							}
							else if (gFrame1 == 1)
							{
								InitTitle();					// タイトル初期化
							}
							else if (gFrame1 == 2)
							{
								InitPose();						// ポーズ初期化
								ReadTexture();		// テクスチャ

							}
							else if (gFrame1 == 3)
							{
								ReadTexture();		// テクスチャ
							}
							gFrame1++;
						}

						gTimeStock2 = GetTickCount() - gTimeStock;
						if (gTimeStock2 > gLoadSecond)
						{
							gFadeFlag = 2;
							break;
						}

					}
				}

				if (gFadeFlag == 2)
				{
					if (FadeOutFlag() == true)
					{
						gFadeFlag = 0;
						gLoadFlag = 1;
						InitFade();
						gWaitTime = 60;
					}
				}
			}
			else
			{
				if (gFadeFlag == 0)
				{
					if (FadeInFlag() == true)
					{
						gFadeFlag = 1;
						gTimeStock = GetTickCount();
					}
				}

				if (gFadeFlag == 1)
				{
					while (true)
					{
						if (gFrame1 < 5)
						{
							if (gFrame1 == 0)
							{
								InitSound();					// サウンド初期化
							}
							else if (gFrame1 == 1)
							{
								InitTitle();					// タイトル初期化
							}
							else if (gFrame1 == 2)
							{
								InitPose();						// ポーズ初期化
							}
							else if (gFrame1 == 3)
							{
								ReadTexture();					// テクスチャ
							}
							else if (gFrame1 == 4)
							{
								InitPlayer();					// プレイヤー
								gGameMode.Mode = GAME_TITLE;	// ゲームモードをタイトルにする
							}
							gFrame1++;
						}
						gTimeStock2 = GetTickCount() - gTimeStock;
						if (gTimeStock2 > gLoadSecond)
						{
							gFadeFlag = 2;
							break;
						}

					}
				}

				if (gFadeFlag == 2)
				{
					if (FadeOutFlag() == true)
					{
						gFadeFlag = 0;
						gLoadFlag = 1;
						InitFade();
						gWaitTime = 60;
					}
				}
			}

			if (gFrame1 == 5)
			{
				gFrame1 = 0;
				gFadeFlag = 0;
				gLoadFlag = 1;
				InitFade();
				gWaitTime = 60;
				// 曲データ演奏開始
				DSoundPlay(sndTitle, TRUE);

			}
		}
		else if (gGameMode.OutMode == GAME_TITLE)
		{
			if (gFadeFlag == 0)
			{
				if (FadeInFlag() == true)
				{
					gFadeFlag = 1;
					gTimeStock = GetTickCount();
				}
			}

			if (gFadeFlag == 1)
			{
				while (true)
				{
					if (gFrame1 < 1)
					{
						if (gFrame1 == 0)
						{
							InitGame();						// メインゲーム初期化
						}
						gFrame1++;
					}

					gTimeStock2 = GetTickCount() - gTimeStock;
					if (gTimeStock2 > gLoadSecond)
					{
						gFadeFlag = 2;
						break;
					}
				}

			}

			if (gFadeFlag == 2)
			{
				if (FadeOutFlag() == true)
				{
					gFadeFlag = 0;
					gLoadFlag = 1;
					InitFade();
					gWaitTime = 60;
				}
			}

			if (gFrame1 == 1)
			{
				gFrame1 = 0;
				gFadeFlag = 0;
				gLoadFlag = 1;
				InitFade();
				gWaitTime = 60;
				// 曲データ演奏開始
				DSoundPlay(sndBgm, TRUE);

			}
		}
	}
}

/*
 * ロード画面描画
 */
void DrawLoad()
{
	BeginScene();
	if (gLoadFlag == 0)
	{
		DrawTexture(0, 0, &teamlogo, teamlogo.texture, DRAW_NOBLEND);	// 画像描画(チームロゴ)
	}
	else
	{
		DrawTexture(0, 0, &load, load.texture, DRAW_NOBLEND);	// 画像描画(ロード)
	}

	if (gFadeFlag == 0)
	{
		WhiteFadeIn();	// フェードイン
	}
	else if (gFadeFlag == 2)
	{
		WhiteFadeOut();	// フェードアウト
	}
	EndScene();
	frm.dwRCurFrame++;	//	描画フレーム数更新
}
