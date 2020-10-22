/*
 * @file SceneMain.cpp
 * @brief ゲームメイン処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "FbxMesh.h"
#include "Camera.h"
#include "SceneMain.h"
#include "library.h"
#include "dslib.h"
#include "game.h"
#include "Texture.h"
#include "player.h"
#include "CollsionDetection.h"
#include "object.h"
#include "result.h"
#include "Fade.h"

#define _USE_MATH_DEFINES
#include <math.h>

DWORD gBeforeTime;	// 前回の時間
DWORD gCurrentTime;	// 今回の時間
float gDeltaTime;	// 経過時間(ゲーム全体で共有)
int gPointCount[4];	// ポイントカウント
int *gpPointCount;			// ポイントカウントポインタ
int gGameTime;		// 試合時間
int gFrameCount;	// １フレームのカウント
int gTimeMinute;	// 試合時間(分)
int gTimeSecond;	// 試合時間(秒)
int gOperationFlag;	// 操作説明
int gWaitTime;		// 待ち時間

FbxMeshKM* stage, *stage2, *wall;   // レンダリングするステージ

FbxMeshKM* home[MAX_JOYSTICK_COUNT];	// スタート地点情報

/*
 * ドライバの初期化
 */
void InitDevice()
{
	//	環境設定
	gDevice->SetRenderState(D3DRS_AMBIENT, 0x808080);		// アンビエイト光(環境光)
	gDevice->SetRenderState(D3DRS_LIGHTING, false);			// ライトfalse
	//	フォグ
	gDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

/*
 * ゲームメインの初期化
 */
void InitGame()
{
	int i;
	// ポイントの初期化
	for (i = 0; i < gJoyPadNum; i++)
	{
		gPointCount[i] = 0;
	}
	
	// ステージの初期化
	stage = new FbxMeshKM();
	stage->Create("Assets/map/map15_1.fbx");
	stage->rotation = D3DXVECTOR3(0, 0, 0);
	stage->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	stage->Update();

	stage2 = new FbxMeshKM();
	stage2->Create("Assets/map/map15_2.fbx");
	stage2->rotation = D3DXVECTOR3(0, 0, 0);
	stage2->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	stage2->Update();

	wall = new FbxMeshKM();
	wall->Create("Assets/map/sumon_stage.fbx");
	wall->position = D3DXVECTOR3(0.0f, -150.0f, -1500.0f);
	wall->scale = D3DXVECTOR3(130.0f, 130.0f, 130.0f);
	wall->Update();

	// 家読み込み
	for (i = 0; i < gJoyPadNum; i++)
	{
		home[i] = new FbxMeshKM();
		if (i == 0)
		{
			home[i]->Create("Assets/home/player1/ie_br.fbx");
			home[i]->position = D3DXVECTOR3(1030.0f, 290.0f, -1660.0f);
			home[i]->rotation = D3DXVECTOR3(0.0f, -1.5f, 0.0f);
			home[i]->scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		}
		else if (i == 1)
		{
			home[i]->Create("Assets/home/player2/ie_ora.fbx");
			home[i]->position = D3DXVECTOR3(-1030.0f, 290.0f, -1660.0f);
			home[i]->rotation = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
			home[i]->scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		}
		else if (i == 2)
		{
			home[i]->Create("Assets/home/player3/ie_re.fbx");
			home[i]->position = D3DXVECTOR3(1030.0f, 5.0f, -150.0f);
			home[i]->rotation = D3DXVECTOR3(0.0f, -1.5f, 0.0f);
			home[i]->scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		}
		else if (i == 3)
		{
			home[i]->Create("Assets/home/player4/ie_ye.fbx");
			home[i]->position = D3DXVECTOR3(-1030.0f, 5.0f, -150.0f);
			home[i]->rotation = D3DXVECTOR3(0.0f, 1.5f, 0.0f);
			home[i]->scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		}
		home[i]->Update();
	}

	InitCamera();		//	カメラ初期化

	InitObject();		// オブジェクト

	// フレームカウント初期化
	for (i = 0; i < 5; i++)
	{
		gFrameCount = 0;
	}
	gGameTime = GAME_TIME;		// 試合時間

	gOperationFlag = 1;
	gWaitTime = 180;

	//	初期化の最後
	gBeforeTime = timeGetTime();

	gGameMode.Mode = GAME_IN;
}

/*
 * ステージのリリース
 */
void ReleaseStage()
{
	delete stage;
	delete stage2;
	delete wall;
}


/*
*  @brief リセットゲーム
*  @param mode ゲームモード
*/
int ResetGame(int mode)
{
	int i;
	gGameMode.Mode = mode;

	// プレイヤーの初期化
	for (i = 0; i < gJoyPadNum; i++)
	{
		ResetPlayer(i);
		gPointCount[i] = 0;
	}

	// オブジェクトの初期化
	ResetObject();

	// テクスチャの初期化
	ResetTexture();

	gFrameCount = 0;
	gGameTime = GAME_TIME;		// 試合時間の代入

	if (mode == GAME_RESULT)
	{
		DSoundStop(sndBgm);
		// 曲データ演奏開始
		DSoundPlay(sndResult, TRUE);
	}
	if (mode == GAME_TITLE)
	{
		DSoundStop(sndBgm);
		// 曲データ演奏開始
		DSoundPlay(sndTitle, TRUE);
	}
	return mode;
}

/*
 * メインゲームのアップデート
 */
int MainUpdate()
{
	int i;

	if ((gOperationFlag == 1) || (gOperationFlag == 2) || (gOperationFlag == 3))
	{
		if (gOperationFlag == 1)
		{
			if (gTrg1 & KEYIN_RIGHT)
			{
				gOperationFlag = 2;
			}
		}
		else if (gOperationFlag == 2)
		{
			if (gTrg1 & KEYIN_RIGHT)
			{
				gOperationFlag = 3;
			}
		}
		else if (gOperationFlag == 3)
		{
			gWaitTime--;
			if (gWaitTime < 0)
			{
				gOperationFlag = 0;
				gWaitTime = 5;
			}
		}

		return GAME_IN;
	}

	gFrameCount++;	// 試合時間のフレームカウントアップ
	// 試合が終わったかどうかの有無
	if ((gFrameCount / 60) == 1)
	{
		gGameTime--;			// 試合時間を減らす
		gFrameCount = 0;
		if (gGameTime < 0)
		{
			gOperationFlag = 4;
			if (gWaitTime < 0)
			{
				gOperationFlag = 0;
				gWaitTime = 180;
				for (i = 0; i < gJoyPadNum; i++)
				{
					gResultPoint[i] = gPointCount[i];
				}
				ResetGame(GAME_RESULT);

				return GAME_RESULT;
			}
			else
			{
				gWaitTime--;
				return GAME_IN;
			}
		}
	}

	float deltaTime = 1.0f / 60.0f;			// アニメーションタイム
	// キャラごとの時間計算
	for (i = 0; i < gJoyPadNum; i++)
	{
		Player[i]->DamageTime--;		// ダメージクールタイム
		Player[i]->RespawnTime--;		// リスポーンタイム
		Player[i]->motionTime--;		// モーション時間
		PlayerWeapon[i]->DamageTime--;		// ダメージクールタイム
		PlayerWeapon[i]->RespawnTime--;		// リスポーンタイム
		PlayerWeapon[i]->motionTime--;		// モーション時間
		// モーションをidleに戻す
		if (Player[i]->use == 1)
		{
			if ((Player[i]->motionTime < 0 && Player[i]->CharState == CHAR_ATTACK) ||
				(Player[i]->motionTime < 0 && Player[i]->CharState == CHAR_HIT) ||
				(Player[i]->motionTime < 0 && Player[i]->CharState == CHAR_PICK))
			{
				Player[i]->CharState = CHAR_IDLE;
			}
			// キャラを武器持ちに変える
			else if (Player[i]->motionTime < 0 && Player[i]->CharState == CHAR_CREATE)
			{
				Player[i]->use = 0;
				PlayerWeapon[i]->use = 1;
				PlayerWeapon[i]->AttackNum = 3;
				PlayerWeapon[i]->HitPoint = Player[i]->HitPoint;
				PlayerWeapon[i]->position = Player[i]->position;
				PlayerWeapon[i]->CharState = CHAR_IDLE;
			}
		}
		else
		{
			if ((PlayerWeapon[i]->motionTime < 0 && Player[i]->CharState == CHAR_ATTACK) ||
				(PlayerWeapon[i]->motionTime < 0 && Player[i]->CharState == CHAR_HIT) ||
				(PlayerWeapon[i]->motionTime < 0 && Player[i]->CharState == CHAR_PICK))
			{
				PlayerWeapon[i]->CharState = CHAR_IDLE;
			}
		}

		// リスポーン
		if ((Player[i]->use == 0) && (PlayerWeapon[i]->use == 0))
		{
			if (Player[i]->RespawnTime <= 0)
			{
				Player[i]->use = 1;
				if (i == 0)
				{
					Player[0]->position = D3DXVECTOR3(880, 290, -1650);
				}
				else if (i == 1)
				{
					Player[1]->position = D3DXVECTOR3(-860, 290, -1650);
				}
				else if (i == 2)
				{
					Player[2]->position = D3DXVECTOR3(880, 5, -150);
				}
				else if (i == 3)
				{
					Player[3]->position = D3DXVECTOR3(-860, 5, -150);
				}
			}
		}
	}
	// オブジェクトからアイテムをゲットできるまでの時間
	for (i = 0; i < MAX_OBJECT; i++)
	{
		if (Obj[i].GetLimitCount <= 0)
		{
			Obj[i].ReGetTime--;
			if (Obj[i].ReGetTime < 0 && Obj[i].use == 0)
			{
				Obj[i].use = 1;
				if (Obj[i].obj_name == OBJ_BOX || Obj[i].obj_name == OBJ_TREE)
				{
					Obj[i].GetLimitCount = 1;
				}
				else
				{
					Obj[i].GetLimitCount = 3;
				}
			}
		}
	}
	// ビックリマークを消す
	for (i = 0; i < MAX_SURPRISED; i++)
	{
		surprised[i].use = 0;
	}
	// はてなマークを消す
	for (i = 0; i < MAX_QUESTION; i++)
	{
		question[i].use = 0;
	}

	D3DXVECTOR3 forward = GetForward(&cv);
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);
	D3DXVECTOR3 right = GetRight(&cv);
	
	gTimeMinute = gGameTime / 60;		// 試合時間(分)
	gTimeSecond = gGameTime % 60;		// 試合時間(秒)

	// キャラ移動
	for (i = 0; i < gJoyPadNum; i++)
	{
		gpPointCount = &gPointCount[i];		// ポイントのポインタを代入

		// プレイヤー(武器なし)
		if (Player[i]->use == 1)
		{
			if (i == 0)
			{
				CollsionDetection(i, gpPointCount, gKey1, gTrg1);	// 当たり判定
				ControllPlayer(i, gKey1, gTrg1);			// キャラ移動
			}
			else if (i == 1)
			{
				CollsionDetection(i, gpPointCount, gKey2, gTrg2);	// 当たり判定
				ControllPlayer(i, gKey2, gTrg2);			// キャラ移動
			}
			else if (i == 2)
			{
				CollsionDetection(i, gpPointCount, gKey3, gTrg3);	// 当たり判定
				ControllPlayer(i, gKey3, gTrg3);			// キャラ移動
			}
			else
			{
				CollsionDetection(i, gpPointCount, gKey4, gTrg4);	// 当たり判定
				ControllPlayer(i, gKey4, gTrg4);			// キャラ移動
			}
		}
		// プレイヤー(武器あり)
		else if (PlayerWeapon[i]->use == 1)
		{
			if (i == 0)
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey1, gTrg1);	// 当たり判定
				ControllPlayerWeapon(i, gKey1, gTrg1);			// キャラ移動
			}
			else if (i == 1)
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey2, gTrg2);	// 当たり判定
				ControllPlayerWeapon(i, gKey2, gTrg2);			// キャラ移動
			}
			else if (i == 2)
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey3, gTrg3);	// 当たり判定
				ControllPlayerWeapon(i, gKey3, gTrg3);			// キャラ移動
			}
			else
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey4, gTrg4);	// 当たり判定
				ControllPlayerWeapon(i, gKey4, gTrg4);			// キャラ移動
			}
		}
		// 川に落ちたら初期位置にリスポーン
		if (Player[i]->position.y <= -100)
		{
			gPointCount[i] -= 300;			// ポイントを300減らす
			Player[i]->HitPoint -= 3;		// 体力を3減らす
			if (i == 0)
			{
				Player[0]->position = D3DXVECTOR3(880, 290, -1650);
			}
			else if (i == 1)
			{
				Player[1]->position = D3DXVECTOR3(-860, 290, -1650);
			}
			else if (i == 2)
			{
				Player[2]->position = D3DXVECTOR3(880, 5, -150);
			}
			else if (i == 3)
			{
				Player[3]->position = D3DXVECTOR3(-860, 5, -150);
			}
		}
		// ポイントが０以下にならないように
		if (gPointCount[i] <= 0)
		{
			gPointCount[i] = 0;
		}
	}

	if (gTrg1 & KEYIN_W)
	{
		gGameMode.Mode = GAME_POSE;
		return GAME_POSE;
	}

	//	ビュー行列設定
	SetPosition(&cv, cv.pos);
	SetRotation(&cv, cv.angle);
	UpdateCamera(&cv);

	// アニメーション
	for (i = 0; i < gJoyPadNum; i++)
	{
		// プレイヤー(武器なし)
		if (Player[i]->use == 1)
		{
			Player[i]->Update();
			Player[i]->Animate(deltaTime);
		}
		// プレイヤー(武器あり)
		else if (PlayerWeapon[i]->use == 1)
		{
			PlayerWeapon[i]->Update();
			PlayerWeapon[i]->Animate(deltaTime);
		}
	}

	//	投影行列設定
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, 1.0f, (float)gScreenWidth / (float)gScreenHeight, 0.2f, 3000.0f);
	gDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	return GAME_IN;
}


/*
 * メインゲーム描画
 */
void SceneRender()
{
	int i;
	gDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFF606060, 1.0f, 0);
	stage->Render();		// ステージ描画
	wall->Render();			// 壁描画
	
	for (i = 0; i < gJoyPadNum; i++)
	{
		home[i]->Render();	// 家描画
	}

	DrawUI();			// UI描画

	DrawPlayer();		// プレイヤー

	// オブジェクト
	DrawObject();

	// フラグ
	DrawFlag();

	// アイテム
	DrawItem();

	// マーク
	DrawMark();

	for (i = 0; i < gJoyPadNum; i++)
	{
		DrawPoint(i, gPointCount[i], GAME_IN);		// ポイント
		DrawHitPoint(i, Player[i]->HitPoint);		// 体力
	}

	DrawTime(gTimeMinute, gTimeSecond);			// 時間

	// 操作説明、合図
	if (gOperationFlag == 1)
	{
		DrawOperation(OPERATION);
		DrawOperation(NEXT);
	}
	else if (gOperationFlag == 2)
	{
		DrawOperation(OPERATION2);
		DrawOperation(NEXT);
	}
	else if (gOperationFlag == 3)
	{
		DrawOperation(STARTSIGNAL);
	}
	else if (gOperationFlag == 4)
	{
		DrawOperation(ENDSIGNAL);
	}

	WhiteFadeIn();
}
