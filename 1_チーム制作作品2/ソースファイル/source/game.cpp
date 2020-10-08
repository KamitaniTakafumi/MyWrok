/*
 * @file game.cpp
 * @brief ゲーム処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "Framework.h"
#include "dslib.h"
#include "SceneMain.h"
#include "title.h"
#include "result.h"
#include "pose.h"
#include "load.h"
#include "Fade.h"

GAMEMODE gGameMode;		// ゲームモード情報

/*
 * 初期化
 */
void AppInit()
{
	InitFade();	// フェード初期化
	InitLoad();	// ロード初期化
	InitFont();	// フォント初期化
}

/*
 * フレーム処理：入力
 */
void FrameInput()
{
	// キーの入力、トリガ入力を得る
	InKey();
}

/*
 * フレーム処理：計算
 */
void FrameProcess()
{
	// ゲーム遷移
	switch (gGameMode.Mode)
	{
	case GAME_LOAD:
		Load();
		break;
	case GAME_TITLE:
		SelectTitle();
		break;
	case GAME_IN:
		MainUpdate();
		break;
	case GAME_RESULT:
		UpdateResult();
		break;
	case GAME_POSE:
		PoseMenu();
		break;
	default:
		break;
	}
}

/*
 * フレーム処理：描画
 */
void FrameDraw() 
{
	// 描画遷移
	switch (gGameMode.Mode)
	{
	case GAME_LOAD:
		DrawLoad();
		break;
	case GAME_TITLE:
		DrawTitle();
		break;
	case GAME_IN:
		RenderFramework();
		break;
	case GAME_RESULT:
		DrawResult();
		break;
	case GAME_POSE:
		DrawPose();
		break;
	default:
		break;
	}
}

