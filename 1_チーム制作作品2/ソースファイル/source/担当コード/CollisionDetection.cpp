/*
 * @file CollsionDetection.cpp
 * @brief 当たり判定処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "SceneMain.h"
#include "player.h"
#include "CollsionDetection.h"
#include "Texture.h"
#include "object.h"
#include "dslib.h"

/*
 * キャラとオブジェクトの衝突検出
 * @param *pThingA キャラ
 * @param *pThingB オブジェクト
 */
BOOL Collision(FbxMeshKM* pThingA, OBJECT pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pThingB.Position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB.Radius)
	{
		return true;
	}
	return false;
}

/*
 * キャラとテクスチャの衝突検出
 * @param *pThingA キャラ
 * @param *pThingB テクスチャ
 */
BOOL Collision2(FbxMeshKM* pThingA, TEXTURE* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pThingB->Position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB->Radius)
	{
		return true;
	}
	return false;
}

/*
 * キャラとギミックの衝突検出
 * @param *pThingA キャラ
 * @param *pThingB ギミック
 */
BOOL Collision3(FbxMeshKM* pThingA, GIMMICK* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pThingB->Position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB->Radius)
	{
		return true;
	}
	return false;
}

/*
 * キャラ同士の衝突検出
 * @param *pThingA キャラ１
 * @param *pThingB キャラ２
 */
BOOL Collision4(FbxMeshKM* pThingA, FbxMeshKM* pThingB)
{
	//２つの物体の中心間の距離を求める
	D3DXVECTOR3 vLength = pThingB->position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB->Radius)
	{
		return true;
	}
	return false;
}

/*
 * ギミックとの当たり判定
 * @param i プレイヤーの識別番号
 * @param type プレイヤーの状態
 * @return true or false
 */
bool PlayerGimmickHit(int i, int type)
{
	if (type == 0)
	{
		for (int j = 0; j < MAX_GIMMICK; j++)
		{
			if (Collision3(Player[i], &Gim[j]) != false)
			{
				return true;
			}
		}
	}
	else
	{
		for (int j = 0; j < MAX_GIMMICK; j++)
		{
			if (Collision3(PlayerWeapon[i], &Gim[j]) != false)
			{
				return true;
			}
		}
	}
	return false;
}

/*
 * ボタンをクリックしたか
 * @param num どのパッドが押されたか
 * @param g_trg プレイヤーのボタン判定
 * @param obj_name オブジェクトの名前
 * @return true or false
 */
bool ClickButton(int num, int g_trg, int obj_name)
{
	if (obj_name == OBJ_BOX)
	{
		if ((g_trg & KEYIN_X) && (Player[num]->CharState != CHAR_ATTACK) && (Player[num]->CharState != CHAR_CREATE))
		{
			return true;
		}
	}
	else
	{
		if ((g_trg & KEYIN_A) && (Player[num]->CharState != CHAR_ATTACK))
		{
			return true;
		}
	}
	return false;
}

/*
 * アイテムドロップ
 * @param i オブジェクトの添え字
 * @param num どのパッドが押されたか
 * @param g_trg プレイヤーのボタン判定
 * @param *point ポイントのポインタ
 */
static void ItemDrop(int i, int num, int g_trg, int* point)
{
	if (Obj[i].obj_name == OBJ_TREE)
	{
		if (i == 0)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				goldapple[0].use = 1;
				Obj[i].use = 0;
				Obj[i].ReGetTime = 600;
				Obj[i].GetLimitCount--;
			}
			if (Obj[i].use == 1)
			{
				surprised[12].use = 1;
			}
		}
		if (i == 1)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				goldapple[1].use = 1;
				Obj[i].use = 0;
				Obj[i].ReGetTime = 600;
				Obj[i].GetLimitCount--;
			}
			if (Obj[i].use == 1)
			{
				surprised[13].use = 1;
			}
		}

	}
	else if (Obj[i].obj_name == OBJ_WOOD)
	{
		if (i == 2)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				if (mushroom[0].use == 0)
				{
					mushroom[0].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[1].use == 0)
				{
					mushroom[1].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[2].use == 0)
				{
					mushroom[2].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[0].use = 1;
			}

		}
		else if (i == 3)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				if (mushroom[3].use == 0)
				{
					mushroom[3].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[4].use == 0)
				{
					mushroom[4].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[5].use == 0)
				{
					mushroom[5].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[1].use = 1;
			}

		}
		else if (i == 4)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				if (mushroom[6].use == 0)
				{
					mushroom[6].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[7].use == 0)
				{
					mushroom[7].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[8].use == 0)
				{
					mushroom[8].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[2].use = 1;
			}

		}
		else if (i == 5)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				if (mushroom[9].use == 0)
				{
					mushroom[9].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[10].use == 0)
				{
					mushroom[10].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[11].use == 0)
				{
					mushroom[11].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[3].use = 1;
			}
		}
		else if (i == 6)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				if (mushroom[12].use == 0)
				{
					mushroom[12].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[13].use == 0)
				{
					mushroom[13].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[14].use == 0)
				{
					mushroom[14].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[4].use = 1;
			}
		}
		else if (i == 7)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE再生
				if (mushroom[15].use == 0)
				{
					mushroom[15].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[16].use == 0)
				{
					mushroom[16].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[17].use == 0)
				{
					mushroom[17].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[5].use = 1;
			}
		}

	}
	else if (Obj[i].obj_name == OBJ_ROCK)
	{
		if (i == 8)
		{
			if (ClickButton(num, g_trg, OBJ_ROCK) == true)
			{
				StartSE(ROCK);		// SE再生
				if (mushroom[18].use == 0)
				{
					mushroom[18].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[19].use == 0)
				{
					mushroom[19].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[20].use == 0)
				{
					mushroom[20].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[6].use = 1;
			}
		}
		else if (i == 9)
		{
			if (ClickButton(num, g_trg, OBJ_ROCK) == true)
			{
				StartSE(ROCK);		// SE再生
				if (mushroom[21].use == 0)
				{
					mushroom[21].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[22].use == 0)
				{
					mushroom[22].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[23].use == 0)
				{
					mushroom[23].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[7].use = 1;
			}
		}
		else if (i == 10)
		{
			if (ClickButton(num, g_trg, OBJ_ROCK) == true)
			{
				StartSE(ROCK);		// SE再生
				if (mushroom[24].use == 0)
				{
					mushroom[24].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[25].use == 0)
				{
					mushroom[25].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[26].use == 0)
				{
					mushroom[26].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[8].use = 1;
			}
		}
		else if (i == 11)
		{
			if (ClickButton(num, g_trg, OBJ_ROCK) == true)
			{
				StartSE(ROCK);		// SE再生
				if (mushroom[27].use == 0)
				{
					mushroom[27].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[28].use == 0)
				{
					mushroom[28].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[29].use == 0)
				{
					mushroom[29].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[9].use = 1;
			}
		}
		else if (i == 12)
		{
			if (ClickButton(num, g_trg, OBJ_ROCK) == true)
			{
				StartSE(ROCK);		// SE再生
				if (mushroom[30].use == 0)
				{
					mushroom[30].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[31].use == 0)
				{
					mushroom[31].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[32].use == 0)
				{
					mushroom[32].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[10].use = 1;
			}
		}
		else if (i == 13)
		{
			if (ClickButton(num, g_trg, OBJ_ROCK) == true)
			{
				StartSE(ROCK);		// SE再生
				if (mushroom[33].use == 0)
				{
					mushroom[33].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[34].use == 0)
				{
					mushroom[34].use = 1;
					Obj[i].GetLimitCount--;
				}
				else if (mushroom[35].use == 0)
				{
					mushroom[35].use = 1;
					Obj[i].GetLimitCount--;
				}
				if (Obj[i].GetLimitCount <= 0)
				{
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
				}
			}
			if (Obj[i].use == 1)
			{
				surprised[11].use = 1;
			}
		}

	}
	else if (Obj[i].obj_name == OBJ_BOX)
	{
		if (*point >= 300)
		{
			if (i == 14)
			{
				if (ClickButton(num, g_trg, OBJ_BOX) == true)
				{
					StartSE(CRAFT);		// SE再生
					MotionChange(num, CHAR_CREATE);
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
					Obj[i].GetLimitCount--;
					*point -= 300;
				}
				if (Obj[i].use == 1)
				{
					question[0].use = 1;
				}
			}
			else if (i == 15)
			{
				if (ClickButton(num, g_trg, OBJ_BOX) == true)
				{
					StartSE(CRAFT);		// SE再生
					MotionChange(num, CHAR_CREATE);
					Obj[i].use = 0;
					Obj[i].ReGetTime = 600;
					Obj[i].GetLimitCount--;
					*point -= 300;
				}
				if (Obj[i].use == 1)
				{
					question[1].use = 1;
				}
			}
		}
	}
}

/*
 * キノコのゲット
 * @param num どのパッドが押されたか
 * @param g_trg プレイヤーのボタン判定
 * @param *point ポイントのポインタ
 * @param p_name 'p' = 武器なし、'w' = 武器あり 
 */
static void GetMushroom(int num, int g_trg, int* point, char p_name)
{
	for (int i = 0; i < MAX_MUSHROOM; i++)
	{
		if (mushroom[i].use == 0)
		{
			continue;
		}
		if (p_name == 'p')
		{
			if (Collision2(Player[num], &mushroom[i]) != false)
			{
				if (g_trg & KEYIN_C)
				{
					StartSE(PICK);		// SE再生
					MotionChange(num, CHAR_PICK);
					mushroom[i].use = 0;
					*point += 200;
				}
			}
		}
		else
		{
			if (Collision2(PlayerWeapon[num], &mushroom[i]) != false)
			{
				if (g_trg & KEYIN_C)
				{
					StartSE(PICK);		// SE再生
					MotionChange(num, CHAR_PICK);
					mushroom[i].use = 0;
					*point += 200;
				}
			}
		}

	}
}

/*
 * 金りんごのゲット
 * @param num どのパッドが押されたか
 * @param g_trg プレイヤーのボタン判定
 * @param *point ポイントのポインタ
 * @param p_name 'p' = 武器なし、'w' = 武器あり 
 */
static void GetGoldApple(int num, int g_trg, int* point, char p_name)
{
	for (int i = 0; i < MAX_GOLDAPPLE; i++)
	{
		if (goldapple[i].use == 0)
		{
			continue;
		}
		if (p_name == 'p')
		{
			if (Collision2(Player[num], &goldapple[i]) != false)
			{
				if (g_trg & KEYIN_C)
				{
					StartSE(PICK);		// SE再生
					MotionChange(num, CHAR_PICK);
					goldapple[i].use = 0;
					*point += 500;
				}
			}
		}
		else
		{
			if (Collision2(PlayerWeapon[num], &goldapple[i]) != false)
			{
				if (g_trg & KEYIN_C)
				{
					StartSE(PICK);		// SE再生
					MotionChange(num, CHAR_PICK);
					goldapple[i].use = 0;
					*point += 500;
				}
			}
		}
	}
}

/*
 * フラグのゲット
 * @param num どのパッドが押されたか
 * @param g_trg プレイヤーのボタン判定
 * @param *point ポイントのポインタ
 * @param p_name 'p' = 武器なし、'w' = 武器あり
 */
static void GetFlag(int num, int g_trg, int* point, char p_name)
{
	for (int i = 0; i < MAX_FLAG; i++)
	{
		if (flag[i].use == 0)
		{
			continue;
		}
		if (p_name == 'p')
		{
			if (Collision2(Player[num], &flag[i]) != false)
			{
				if (g_trg & KEYIN_C)
				{
					StartSE(PICK);		// SE再生
					flag[i].use = 0;
					*point += 200;
				}
			}
		}
		else
		{
			if (Collision2(PlayerWeapon[num], &flag[i]) != false)
			{
				if (g_trg & KEYIN_C)
				{
					StartSE(PICK);		// SE再生
					flag[i].use = 0;
					*point += 200;
				}
			}
		}

	}
}

/*
 * @brief プレイヤーとFBXとの当たり判定
 * @param num プレイヤーの識別番号
 * @param *point ポイントのポインタ
 * @param g_key プレイヤーのボタン判定
 * @param g_trg プレイヤーのボタン判定
 */
int CollsionDetection(int num, int* point, int g_key, int g_trg)
{
	int i;

	// 当たり判定
	D3DXVECTOR3 out, normal;
	if (Player[num]->use == 1)
	{
		D3DXVECTOR3 PposUp(Player[num]->position.x, Player[num]->position.y + 30, Player[num]->position.z - 30);
		D3DXVECTOR3 PposRight(Player[num]->position.x + 30, Player[num]->position.y + 30, Player[num]->position.z);
		// -y(地面)方向のレイ判定
		if (stage2->Raycast2(Player[num]->position, D3DXVECTOR3(0, -1, 0), 4.0f, out, normal) != -1)
		{
			Player[num]->position.y = out.y + 4;
		}
		if (Player[num]->direction[1] == 1)
		{
			// -z方向(上)のレイ判定
			if (stage2->Raycast2(Player[num]->position, D3DXVECTOR3(0, 0, -1), 30.0f, out, normal) != -1)
			{
				Player[num]->position.z = out.z + 30;
			}
			if (stage2->Raycast2(PposUp, D3DXVECTOR3(0, -1, 0), 50.0f, out, normal) != -1)
			{
				Player[num]->position.y = out.y + 8;
			}
		}
		if (Player[num]->direction[2] == 1)
		{
			// -x(左)方向のレイ判定
			if (stage2->Raycast2(Player[num]->position, D3DXVECTOR3(-1, 0, 0), 30.0f, out, normal) != -1)
			{
				Player[num]->position.x = out.x + 30;
			}
		}
		if (Player[num]->direction[3] == 1)
		{
			// x(右)方向のレイ判定
			if (stage2->Raycast2(Player[num]->position, D3DXVECTOR3(1, 0, 0), 30.0f, out, normal) != -1)
			{
				Player[num]->position.x = out.x - 30;
			}
			if (stage2->Raycast2(PposRight, D3DXVECTOR3(0, -1, 0), 50.0f, out, normal) != -1)
			{
				Player[num]->position.y = out.y + 8;
			}
		}

		// マップ外に出ないように
		if (Player[num]->position.x >= 1100)
		{
			if (Player[num]->DamageTime <= 0)
			{
				Player[num]->HitPoint -= 2;
				Player[num]->DamageTime = 300;
				*point -= 300;
			}
			if (Player[num]->position.x >= 1200)
			{
				Player[num]->position.x -= 5;
			}
		}
		if (Player[num]->position.x <= -1100)
		{
			if (Player[num]->DamageTime <= 0)
			{
				Player[num]->HitPoint -= 2;
				Player[num]->DamageTime = 300;
				*point -= 300;
			}
			if (Player[num]->position.x <= -1200)
			{
				Player[num]->position.x = out.x + 5;
			}
		}
		if (Player[num]->position.z >= -50)
		{
			if (Player[num]->DamageTime <= 0)
			{
				Player[num]->HitPoint -= 2;
				Player[num]->DamageTime = 300;
				*point -= 300;
			}
			if (Player[num]->position.z >= 0)
			{
				Player[num]->position.z = out.z - 5;
			}
		}
		Player[num]->position.y -= GRAVITY;		// 重力付加
	}


	// オブジェクトの当たり判定
	if (Player[num]->DamageTime >= 0)
	{
		return false;
	}
	// キャラとオブジェクトの判定
	for (i = 0; i < MAX_OBJECT; i++)
	{
		if (Obj[i].use == 0)
		{
			continue;
		}
		if (Collision(Player[num], Obj[i]) != false)
		{
			ItemDrop(i, num, g_trg, point);
		}
	}

	// アイテムが取得できるか
	GetMushroom(num, g_trg, point, 'p');
	GetGoldApple(num, g_trg, point, 'p');
	GetFlag(num, g_trg, point, 'p');
	
	return true;
}

/*
 * @brief 武器持ちプレイヤーとFBXとの当たり判定
 * @param num プレイヤーの識別番号
 * @param *point ポイントのポインタ
 * @param g_key プレイヤーのボタン判定
 * @param g_trg プレイヤーのボタン判定
 */
int CollsionDetectionWeapon(int num, int* point, int g_key, int g_trg)
{
	int i;

	// 当たり判定
	D3DXVECTOR3 out, normal;

	D3DXVECTOR3 PposUp(PlayerWeapon[num]->position.x, PlayerWeapon[num]->position.y + 30, PlayerWeapon[num]->position.z - 30);
	D3DXVECTOR3 PposRight(PlayerWeapon[num]->position.x + 30, PlayerWeapon[num]->position.y + 30, PlayerWeapon[num]->position.z);
	// -y(地面)方向のレイ判定
	if (stage->Raycast2(PlayerWeapon[num]->position, D3DXVECTOR3(0, -1, 0), 4.0f, out, normal) != -1)
	{
		PlayerWeapon[num]->position.y = out.y + 4;
	}
	if (PlayerWeapon[num]->direction[1] == 1)
	{
		// -z方向(上)のレイ判定
		if (stage->Raycast2(PlayerWeapon[num]->position, D3DXVECTOR3(0, 0, -1), 30.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.z = out.z + 30;
		}
		if (stage->Raycast2(PposUp, D3DXVECTOR3(0, -1, 0), 50.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.y = out.y + 8;
		}
	}
	if (PlayerWeapon[num]->direction[2] == 1)
	{
		// -x(左)方向のレイ判定
		if (stage->Raycast2(PlayerWeapon[num]->position, D3DXVECTOR3(-1, 0, 0), 30.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.x = out.x + 30;
		}
	}
	if (PlayerWeapon[num]->direction[3] == 1)
	{
		// x(右)方向のレイ判定
		if (stage->Raycast2(PlayerWeapon[num]->position, D3DXVECTOR3(1, 0, 0), 30.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.x = out.x - 30;
		}
		if (stage->Raycast2(PposRight, D3DXVECTOR3(0, -1, 0), 50.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.y = out.y + 8;
		}
	}

	// マップ外に出ないように
	if (PlayerWeapon[num]->position.x >= 1100)
	{
		if (PlayerWeapon[num]->DamageTime <= 0)
		{
			PlayerWeapon[num]->HitPoint -= 2;
			PlayerWeapon[num]->DamageTime = 300;
			point -= 300;
		}
		if (PlayerWeapon[num]->position.x >= 1200)
		{
			PlayerWeapon[num]->position.x -= 5;
		}
	}
	if (PlayerWeapon[num]->position.x <= -1100)
	{
		if (PlayerWeapon[num]->DamageTime <= 0)
		{
			PlayerWeapon[num]->HitPoint -= 2;
			PlayerWeapon[num]->DamageTime = 300;
			point -= 300;
		}
		if (PlayerWeapon[num]->position.x <= -1200)
		{
			PlayerWeapon[num]->position.x = out.x + 5;
		}
	}
	if (PlayerWeapon[num]->position.z >= -50)
	{
		if (PlayerWeapon[num]->DamageTime <= 0)
		{
			PlayerWeapon[num]->HitPoint -= 2;
			PlayerWeapon[num]->DamageTime = 300;
			point -= 300;
		}
		if (PlayerWeapon[num]->position.z >= 0)
		{
			PlayerWeapon[num]->position.z = out.z - 5;
		}
	}
	PlayerWeapon[num]->position.y -= GRAVITY;		// 重力付加

	// オブジェクトの当たり判定
	if (PlayerWeapon[num]->DamageTime >= 0)
	{
		return false;
	}
	// キャラとオブジェクトの判定
	for (i = 0; i < MAX_OBJECT; i++)
	{
		if (Obj[i].use == 0)
		{
			continue;
		}
		if (Collision(PlayerWeapon[num], Obj[i]) != false)
		{
			ItemDrop(i, num, g_trg, point);
		}
	}

	// アイテムが取得できるか
	GetMushroom(num, g_trg, point, 'w');
	GetGoldApple(num, g_trg, point, 'w');
	GetFlag(num, g_trg, point, 'w');

	return true;
}
