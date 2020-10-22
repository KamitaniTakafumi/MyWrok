#pragma once
/*
 * @file player.cpp
 * @brief プレイヤー処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "FbxMesh.h"
#include "library.h"

extern FbxMeshKM* Player[MAX_JOYSTICK_COUNT];
extern FbxMeshKM* PlayerWeapon[MAX_JOYSTICK_COUNT];

/*
*  @brief キャラの状態
*/
enum CHAR_STATE
{
	CHAR_IDLE,
	CHAR_MOVE,
	CHAR_RUN,
	CHAR_PICK,
	CHAR_ATTACK,
	CHAR_CREATE,
	CHAR_HIT,
	CHAR_NUM
};

/*
*  @brief キャラ同士の攻撃状態
*/
enum HITATTACK_TYPE
{
	NORMAL,
	WEAPON,
	NORMAL_NORMAL,
	NORMAL_WEAPON,
	WEAPON_NORMAL,
	WEAPON_WEAPON,
};

/*
*  @brief プレイヤー初期化
*/
void InitPlayer();

/*
*  @brief キャラのリリース
*/
void ReleasePlayer();
/*
*  @brief プレイヤーのリセット
*  @param num プレイヤー識別番号
*/
void ResetPlayer(int num);
/*
*  @brief モーションを変える
*  @param num プレイヤー識別番号
*  @param chartype キャラの状態
*/
void MotionChange(int num, int chartype);
/*
*  @brief プレイヤーの行動
*  @param i プレイヤー識別番号
*  @param g_key プレイヤーのボタン判定
*  @param g_trg プレイヤーのボタン判定
*/
void ControllPlayer(int num, int g_key, int g_trg);
/*
*  @brief 武器持ちプレイヤーの行動
*  @param i プレイヤー識別番号
*  @param g_key プレイヤーのボタン判定
*  @param g_trg プレイヤーのボタン判定
*/
void ControllPlayerWeapon(int num, int g_key, int g_trg);
/*
*  @brief プレイヤー描画
*/
void DrawPlayer();