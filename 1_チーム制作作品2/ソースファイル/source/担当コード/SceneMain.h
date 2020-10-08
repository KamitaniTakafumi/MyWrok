#pragma once
/*
 * @file SceneMain.cpp
 * @brief ゲームメイン処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "Camera.h"
#include "FbxMesh.h"

#define GRAVITY 2.0f		// 重力

extern CAMERA* camera;		// カメラ
extern FbxMeshKM* stage, *stage2;   // レンダリングするステージ
extern int gPointCount[4];	// ポイントカウント

/*
 * ドライバの初期化
 */
void InitDevice();

/*
 * ゲームメインの初期化
 */
void InitGame();

/*
 * ステージのリリース
 */
void ReleaseStage();
/*
*  @brief リセットゲーム
*  @param mode ゲームモード
*/
int ResetGame(int mode);

/*
 * メインゲームのアップデート
 */
int MainUpdate();

/*
 * メインゲーム描画
 */
void SceneRender();
