/*
 * @file player.cpp
 * @brief プレイヤー処理
 * @author 上谷恭史
 * @date 2020 / 02 / 27
 */

#include "library.h"
#include "game.h"
#include "SceneMain.h"
#include "Camera.h"
#include "Texture.h"
#include "player.h"
#include "CollsionDetection.h"
#include "dslib.h"

#define _USE_MATH_DEFINES
#include <math.h>

// プレイヤー情報
FbxMeshKM* Player[MAX_JOYSTICK_COUNT];
// 武器プレイヤー情報
FbxMeshKM* PlayerWeapon[MAX_JOYSTICK_COUNT];

float gAngle[4] = { 0.0f };
int gPushNum[4] = { 0 };
// カメラ極座標(r, θ, φ)
D3DXVECTOR3 gCamPolarCoord(500.0f, 70.0f * M_PI*2.0f / 360.0f, 3.1416f * 3.0f / 2.0f);
D3DXVECTOR3 gKnockBack;

/*
 * 初期化
 */
void InitPlayer()
{
	int i;
	for (i = 0; i < gJoyPadNum; i++)
	{
		Player[i] = new FbxMeshKM();
		PlayerWeapon[i] = new FbxMeshKM();
		// プレイヤー１
		if (i == 0)
		{
			Player[0]->Create("Assets/chara/player2/char_p.fbx");
			Player[0]->position = D3DXVECTOR3(880, 290, -1650);
			Player[0]->padnumber = INPUT_PAD1;			// キャラにパッドを対応させる
			PlayerWeapon[0]->Create("Assets/chara/player2/char_p_a.fbx");
			PlayerWeapon[0]->padnumber = INPUT_PAD1;	// キャラにパッドを対応させる
		}
		// プレイヤー２
		else if (i == 1)
		{
			Player[1]->Create("Assets/chara/player4/char_t.fbx");
			Player[1]->position = D3DXVECTOR3(-860, 290, -1650);
			Player[1]->padnumber = INPUT_PAD2;			// キャラにパッドを対応させる
			PlayerWeapon[1]->Create("Assets/chara/player4/char_t_a.fbx");
			PlayerWeapon[1]->padnumber = INPUT_PAD2;	// キャラにパッドを対応させる
		}
		// プレイヤー３
		else if (i == 2)
		{
			Player[2]->Create("Assets/chara/player1/char_g.fbx");
			Player[2]->position = D3DXVECTOR3(880, 5, -150);
			Player[2]->padnumber = INPUT_PAD3;			// キャラにパッドを対応させる
			PlayerWeapon[2]->Create("Assets/chara/player1/char_g_a.fbx");
			PlayerWeapon[2]->padnumber = INPUT_PAD3;	// キャラにパッドを対応させる
		}
		// プレイヤー４
		else if (i == 3)
		{
			Player[3]->Create("Assets/chara/player3/char_pn.fbx");
			Player[3]->position = D3DXVECTOR3(-860, 5, -150);
			Player[3]->padnumber = INPUT_PAD4;			// キャラにパッドを対応させる
			PlayerWeapon[3]->Create("Assets/chara/player3/char_pn_a.fbx");
			PlayerWeapon[3]->padnumber = INPUT_PAD4;	// キャラにパッドを対応させる
		}
		Player[i]->AddMotion("idle", "Assets/chara/char_walk.fbx");		// モーション(歩き)
		Player[i]->AddMotion("throw", "Assets/chara/char_throw.fbx");	// モーション(投げ)
		Player[i]->AddMotion("hit", "Assets/chara/char_hit.fbx");		// モーション(ダメージ)
		Player[i]->AddMotion("create", "Assets/chara/char_create.fbx");	// モーション(クリエイト)
		Player[i]->AddMotion("pick", "Assets/chara/char_pick.fbx");		// モーション(拾う)
		Player[i]->Play("idle");										// モーション再生
		Player[i]->CharState = CHAR_IDLE;								// キャラのステートをIDOLにする
		Player[i]->Radius = 50.0f;										// キャラ半径
		Player[i]->rotation = D3DXVECTOR3(0, 0, 0);						// キャラの回転
		Player[i]->scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);				// キャラの大きさ
		Player[i]->HitPoint = 10;										// 体力
		Player[i]->RespawnTime = 0;										// リスポーン時間
		Player[i]->DamageTime = 0;										// ダメージ時間
		Player[i]->use = 1;												// 使用の有無
		PlayerWeapon[i]->rotation = D3DXVECTOR3(0, 0, 0);
		PlayerWeapon[i]->scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
		PlayerWeapon[i]->AttackNum = 0;
		PlayerWeapon[i]->Radius = 50.0f;
		PlayerWeapon[i]->use = 0;
		Player[i]->Update();
	}
}

/*
 * キャラのリリース
 */
void ReleasePlayer()
{
	for (int i = 0; i < gJoyPadNum; i++)
	{
		delete Player[i];
	}

}

/*
*  @brief プレイヤーのリセット
*  @param num プレイヤー識別番号
*/
void ResetPlayer(int num)
{
	// キャラごとに位置をリセット
	if (num == 0)
	{
		Player[0]->position = D3DXVECTOR3(880, 290, -1650);
	}
	else if (num == 1)
	{
		Player[1]->position = D3DXVECTOR3(-860, 290, -1650);
	}
	else if (num == 2)
	{
		Player[2]->position = D3DXVECTOR3(880, 5, -150);
	}
	else if (num == 3)
	{
		Player[3]->position = D3DXVECTOR3(-860, 5, -150);
	}
	PlayerWeapon[num]->use = 0;						// 武器持ちは消す
	PlayerWeapon[num]->AttackNum = 0;				// 攻撃回数をリセット
	Player[num]->rotation = D3DXVECTOR3(0, 0, 0);	// 向きをリセット
	Player[num]->HitPoint = 10;						// 体力をリセット
	Player[num]->use = 1;							// プレイヤーを使用状態にする
	Player[num]->Update();
}

/*
*  @brief モーションを変える
*  @param num プレイヤー識別番号
*  @param chartype キャラの状態
*/
void MotionChange(int num, int chartype)
{
	switch (chartype)
	{
	case CHAR_IDLE:
		Player[num]->CharState = CHAR_IDLE;
		Player[num]->Play("idle");
		break;
	case CHAR_RUN:
		Player[num]->CharState = CHAR_RUN;
		Player[num]->Play("idle");
		break;
	case CHAR_ATTACK:
		Player[num]->CharState = CHAR_ATTACK;
		Player[num]->Play("throw");
		Player[num]->motionTime = 52;
		break;
	case CHAR_PICK:
		Player[num]->CharState = CHAR_PICK;
		Player[num]->Play("pick");
		Player[num]->motionTime = 100;
		break;
	case CHAR_HIT:
		Player[num]->CharState = CHAR_HIT;
		Player[num]->Play("hit");
		Player[num]->motionTime = 42;
		break;
	case CHAR_CREATE:
		Player[num]->CharState = CHAR_CREATE;
		Player[num]->Play("create");
		Player[num]->motionTime = 300;
		break;
	default:
		Player[num]->CharState = ERR_CHAR;
		Player[num]->Play("idle");
		Player[num]->motionTime = 0;
		break;
	}
}

/*
 * ノックバック
 */
static void PlayerKnockBack(FbxMeshKM* p1, FbxMeshKM* p2)
{
	gKnockBack = p1->position - p2->position;
	if (p1->position.x < p2->position.x)
	{
		gKnockBack.x *= -1;
	}
	else if (p1->position.x > p2->position.x)
	{
		gKnockBack.x *= -1;
	}
	if (p1->position.z < p2->position.z)
	{
		gKnockBack.z *= -1;
	}
	else if (p1->position.z > p2->position.z)
	{
		gKnockBack.z *= -1;
	}
	gKnockBack *= 2;
	p2->position += gKnockBack;
}

/*
*  @brief キャラが攻撃を行った
*  @param i キャラの識別番号
*  @param j キャラの識別番号
*  @param type 当たっているキャラ同士の状態
*/
static void PlayerAtttackDetection(int i, int j, int type)
{
	// 武器なしと武器なし
	if (type == NORMAL_NORMAL)
	{
		// プレイヤー１
		if (j == 0)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
		// プレイヤー２
		else if (j == 1)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
		// プレイヤー３
		else if (j == 2)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
		// プレイヤー４
		else if (j == 3)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
	}
	// 武器なしと武器あり
	else if (type == NORMAL_WEAPON)
	{
		// プレイヤー１
		if (j == 0)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
		// プレイヤー２
		else if (j == 1)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
		// プレイヤー３
		else if (j == 2)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
		// プレイヤー４
		else if (j == 3)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
	}
	// 武器ありと武器なし
	else if (type == WEAPON_NORMAL)
	{
	// プレイヤー１
		if (j == 0)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
		// プレイヤー２
		else if (j == 1)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
		// プレイヤー３
		else if (j == 2)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
		// プレイヤー４
		else if (j == 3)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
	}
	// 武器ありと武器あり
	else if (type == WEAPON_WEAPON)
	{
	// プレイヤー１
		if (j == 0)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], PlayerWeapon[j]);
			}
		}
		// プレイヤー２
		else if (j == 1)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], PlayerWeapon[j]);
			}
		}
		// プレイヤー３
		else if (j == 2)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], PlayerWeapon[j]);
			}
		}
		// プレイヤー４
		else if (j == 3)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE再生
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], PlayerWeapon[j]);
			}
		}
	}
}

/*
 * キャラごとの攻撃
 * @param i キャラの識別番号
 */
bool CharaAttack(int i)
{
	if (i != 0)
	{
		if (PlayerWeapon[0]->use != 1)
		{
			if (Player[0]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 0, NORMAL_NORMAL);
			}
		}
		else
		{
			if (PlayerWeapon[0]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 0, NORMAL_WEAPON);
			}
		}
	}
	if (i != 1)
	{
		if (PlayerWeapon[1]->use != 1)
		{
			if (Player[1]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 1, NORMAL_NORMAL);
			}
		}
		else
		{
			if (PlayerWeapon[1]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 1, NORMAL_WEAPON);
			}
		}
	}
	if (i != 2)
	{
		if (PlayerWeapon[2]->use != 1)
		{
			if (Player[2]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 2, NORMAL_NORMAL);
			}
		}
		else
		{
			if (PlayerWeapon[2]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 2, NORMAL_WEAPON);
			}
		}
	}
	if (i != 3)
	{
		if (PlayerWeapon[3]->use != 1)
		{
			if (Player[3]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 3, NORMAL_NORMAL);
			}
		}
		else
		{
			if (PlayerWeapon[3]->DamageTime <= 0)
			{
				PlayerAtttackDetection(i, 3, NORMAL_WEAPON);
			}
		}
	}

	return true;
}

/*
*  @brief キャラが攻撃を行った
*  @param i キャラの識別番号
*  @param type キャラの状態
*  @param g_key プレイヤーのボタン判定
*  @param g_trg プレイヤーのボタン判定
*/
void PlayerAttack(int i, int type, int g_key, int g_trg)
{
	// プレイヤー(武器なし)
	if (type == NORMAL)
	{
		// ダメージ中は攻撃できないように
		if ((Player[i]->DamageTime <= 0) && (PlayerWeapon[i]->DamageTime <= 0))
		{
			// 攻撃
			if ((g_trg & KEYIN_A) && (Player[i]->CharState != CHAR_ATTACK) && (Player[i]->CharState != CHAR_CREATE))
			{
				MotionChange(i, CHAR_ATTACK);
				// プレイヤー攻撃
				CharaAttack(i);
			}
		}
	}
	// プレイヤー(武器あり)
	else
	{
		// ダメージ中は攻撃できないように
		if ((Player[i]->DamageTime <= 0) && (PlayerWeapon[i]->DamageTime <= 0))
		{
			// 攻撃
			if (g_trg & KEYIN_A)
			{
				// プレイヤー攻撃
				CharaAttack(i);
			}
		}
	}
}

/*
*  @brief プレイヤーの行動
*  @param i プレイヤー識別番号
*  @param g_key プレイヤーのボタン判定
*  @param g_trg プレイヤーのボタン判定
*/
void ControllPlayer(int i, int g_key, int g_trg)
{
	D3DXVECTOR3 forward = GetForward(&cv);
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);
	D3DXVECTOR3 right = GetRight(&cv);

	// 向き情報の初期化
	Player[i]->direction[0] = 0;
	Player[i]->direction[1] = 0;
	Player[i]->direction[2] = 0;
	Player[i]->direction[3] = 0;

	// キャラ移動
	if ((Player[i]->CharState == CHAR_IDLE) ||
		(Player[i]->CharState == CHAR_RUN))
	{
		gAngle[i] = 0.0f;
		gPushNum[i] = 0;

		// 下
		if (g_key & KEYIN_DOWN)
		{
			if (PlayerGimmickHit(i, 0) != false)
			{
				Player[i]->position -= forward * 2.0f;
			}
			else
			{
				Player[i]->position -= forward * 5.0f;
			}
			gAngle[i] += 1.5f;
			gPushNum[i]++;
			if (Player[i]->CharState == CHAR_IDLE)
			{
				MotionChange(i, CHAR_RUN);
			}
			Player[i]->direction[0] = 1;
		}
		// 上
		if (g_key & KEYIN_UP)
		{
			if (PlayerGimmickHit(i, 0) != false)
			{
				Player[i]->position += forward * 2.0f;
			}
			else
			{
				Player[i]->position += forward * 5.0f;
			}
			gAngle[i] += 0.5f;
			gPushNum[i]++;
			if (Player[i]->CharState == CHAR_IDLE)
			{
				MotionChange(i, CHAR_RUN);
			}
			Player[i]->direction[1] = 1;
		}
		// 右
		if (g_key & KEYIN_RIGHT)
		{
			if (PlayerGimmickHit(i, 0) != false)
			{
				Player[i]->position += right * 2.0f;
			}
			else
			{
				Player[i]->position += right * 5.0f;
			}
			gAngle[i] += 1.0f;
			gPushNum[i]++;
			if (Player[i]->CharState == CHAR_IDLE)
			{
				MotionChange(i, CHAR_RUN);
			}
			Player[i]->direction[2] = 1;
		}
		// 左
		if (g_key & KEYIN_LEFT)
		{
			if (PlayerGimmickHit(i, 0) != false)
			{
				Player[i]->position -= right * 2.0f;
			}
			else
			{
				Player[i]->position -= right * 5.0f;
			}
			if (g_key & KEYIN_DOWN) {
				gAngle[i] += 2.0f;
			}
			else {
				gAngle[i] += 0.0f;
			}
			gPushNum[i]++;
			if (Player[i]->CharState == CHAR_IDLE)
			{
				MotionChange(i, CHAR_RUN);
			}
			Player[i]->direction[3] = 1;
		}
		if (gPushNum[i]) {
			Player[i]->rotation.y = (gAngle[i] / (float)gPushNum[i]) * (float)M_PI - gCamPolarCoord.z;
		}
		// 移動していなければキャラのモーションをidleにする
		if (!(g_key & KEYIN_DOWN) &&
			!(g_key & KEYIN_UP) &&
			!(g_key & KEYIN_RIGHT) &&
			!(g_key & KEYIN_LEFT))
		{
			MotionChange(i, CHAR_IDLE);
		}
	}

	// 攻撃
	PlayerAttack(i, NORMAL, g_key, g_trg);

	// リスポーン
	if (Player[i]->HitPoint <= 0)
	{
		StartSE(DIE);		// SE再生
		Player[i]->HitPoint = 10;
		Player[i]->RespawnTime = 300;
		Player[i]->use = 0;
		if (i == 0)
		{
			flag[0].use = 1;
			DropFlag(0);
		}
		else if (i == 1)
		{
			flag[1].use = 1;
			DropFlag(1);
		}
		else if (i == 2)
		{
			flag[2].use = 1;
			DropFlag(2);
		}
		else if (i == 3)
		{
			flag[3].use = 1;
			DropFlag(3);
		}
	}
}

/*
*  @brief 武器持ちプレイヤーの行動
*  @param i プレイヤー識別番号
*  @param g_key プレイヤーのボタン判定
*  @param g_trg プレイヤーのボタン判定
*/
void ControllPlayerWeapon(int i, int g_key, int g_trg)
{
	D3DXVECTOR3 forward = GetForward(&cv);
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);
	D3DXVECTOR3 right = GetRight(&cv);

	// 向き情報の初期化
	PlayerWeapon[i]->direction[0] = 0;
	PlayerWeapon[i]->direction[1] = 0;
	PlayerWeapon[i]->direction[2] = 0;
	PlayerWeapon[i]->direction[3] = 0;

	// キャラ移動
	if ((PlayerWeapon[i]->CharState == CHAR_IDLE) ||
		(PlayerWeapon[i]->CharState == CHAR_RUN))
	{
		gAngle[i] = 0.0f;
		gPushNum[i] = 0;

		// 下
		if (g_key & KEYIN_DOWN)
		{
			if (PlayerGimmickHit(i, 1) != false)
			{
				PlayerWeapon[i]->position -= forward * 2.0f;
			}
			else
			{
				PlayerWeapon[i]->position -= forward * 5.0f;
			}
			gAngle[i] += 1.5f;
			gPushNum[i]++;
			if (PlayerWeapon[i]->CharState == CHAR_IDLE)
			{
				PlayerWeapon[i]->CharState = CHAR_RUN;
			}
			PlayerWeapon[i]->direction[0] = 1;
		}
		// 上
		if (g_key & KEYIN_UP)
		{
			if (PlayerGimmickHit(i, 1) != false)
			{
				PlayerWeapon[i]->position += forward * 2.0f;
			}
			else
			{
				PlayerWeapon[i]->position += forward * 5.0f;
			}
			gAngle[i] += 0.5f;
			gPushNum[i]++;
			if (PlayerWeapon[i]->CharState == CHAR_IDLE)
			{
				PlayerWeapon[i]->CharState = CHAR_RUN;
			}
			PlayerWeapon[i]->direction[1] = 1;
		}
		// 右
		if (g_key & KEYIN_RIGHT)
		{
			if (PlayerGimmickHit(i, 1) != false)
			{
				PlayerWeapon[i]->position += right * 2.0f;
			}
			else
			{
				PlayerWeapon[i]->position += right * 5.0f;
			}
			gAngle[i] += 1.0f;
			gPushNum[i]++;
			if (PlayerWeapon[i]->CharState == CHAR_IDLE)
			{
				PlayerWeapon[i]->CharState = CHAR_RUN;
			}
			PlayerWeapon[i]->direction[2] = 1;
		}
		// 左
		if (g_key & KEYIN_LEFT)
		{
			if (PlayerGimmickHit(i, 1) != false)
			{
				PlayerWeapon[i]->position -= right * 2.0f;
			}
			else
			{
				PlayerWeapon[i]->position -= right * 5.0f;
			}
			if (g_key & KEYIN_DOWN) {
				gAngle[i] += 2.0f;
			}
			else {
				gAngle[i] += 0.0f;
			}
			gPushNum[i]++;
			if (PlayerWeapon[i]->CharState == CHAR_IDLE)
			{
				PlayerWeapon[i]->CharState = CHAR_RUN;
			}
			PlayerWeapon[i]->direction[3] = 1;
		}
		if (gPushNum[i]) {
			PlayerWeapon[i]->rotation.y = (gAngle[i] / (float)gPushNum[i]) * (float)M_PI - gCamPolarCoord.z;
		}
		// 移動していなければキャラのモーションをidleにする
		if (!(g_key & KEYIN_DOWN) &&
			!(g_key & KEYIN_UP) &&
			!(g_key & KEYIN_RIGHT) &&
			!(g_key & KEYIN_LEFT))
		{
			PlayerWeapon[i]->CharState = CHAR_IDLE;
		}
	}


	// 攻撃
	PlayerAttack(i, WEAPON, g_key, g_trg);

	// リスポーン
	if (PlayerWeapon[i]->HitPoint <= 0)
	{
		StartSE(DIE);		// SE再生
		PlayerWeapon[i]->HitPoint = 10;
		PlayerWeapon[i]->RespawnTime = 300;
		PlayerWeapon[i]->use = 0;
		if (i == 0)
		{
			flag[0].use = 1;
			DropFlag(0);
		}
		else if (i == 1)
		{
			flag[1].use = 1;
			DropFlag(1);
		}
		else if (i == 2)
		{
			flag[2].use = 1;
			DropFlag(2);
		}
		else if (i == 3)
		{
			flag[3].use = 1;
			DropFlag(3);
		}
	}
	if (PlayerWeapon[i]->use == 0)
	{
		if (Player[i]->RespawnTime <= 0)
		{
			PlayerWeapon[i]->use = 1;
			if (i == 0)
			{
				PlayerWeapon[0]->position = D3DXVECTOR3(880, 290, -1650);
			}
			else if (i == 1)
			{
				PlayerWeapon[1]->position = D3DXVECTOR3(-860, 290, -1650);
			}
			else if (i == 2)
			{
				PlayerWeapon[2]->position = D3DXVECTOR3(880, 5, -150);
			}
			else if (i == 3)
			{
				PlayerWeapon[3]->position = D3DXVECTOR3(-860, 5, -150);
			}
		}
	}
	// 三回攻撃したら武器が壊れる
	if (PlayerWeapon[i]->AttackNum <= 0)
	{
		// 武器持ちから武器なしへキャラ交代
		PlayerWeapon[i]->use = 0;
		Player[i]->use = 1;
		Player[i]->HitPoint = PlayerWeapon[i]->HitPoint;
		Player[i]->position = PlayerWeapon[i]->position;
		Player[i]->CharState = CHAR_IDLE;
	}

}

/*
 * プレイヤー描画
 */
void DrawPlayer()
{
	int i;
	for (i = 0; i < gJoyPadNum; i++)
	{
		// 武器なし
		if (Player[i]->use == 1)
		{
			Player[i]->Render();
		}
		// 武器持ち
		if(PlayerWeapon[i]->use == 1)
		{
			PlayerWeapon[i]->Render();
		}
	}

}
