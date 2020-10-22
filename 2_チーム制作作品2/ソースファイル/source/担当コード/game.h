#pragma once
/*
*  @file game.cpp
*  @brief ゲーム処理
*  @author 上谷恭史
*  @date 2020 / 02 / 26
*/

struct GAMEMODE// ゲームモード構造体
{
	int Mode;			// 現在のモード
	int OutMode;		// 前のモード
};

extern GAMEMODE gGameMode;// ゲームモード情報

enum STATEGAMEMODE// ゲームモードの状態
{
	GAME_LOAD,
	GAME_LOGO,
	GAME_TITLE,
	GAME_IN,
	GAME_POSE,
	GAME_RESULT,
	GAME_OVER,
	GAME_ENDROLL,
	GAME_NUM
};

/*
*  初期化
*/
void AppInit();

/*
*	フレーム処理：入力
*/
void FrameInput();

/*
*	フレーム処理：計算
*/
void FrameProcess();

/*
*	フレーム処理：描画
*/
void FrameDraw();
