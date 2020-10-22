/*
 * @file CollsionDetection.cpp
 * @brief �����蔻�菈��
 * @author ��J���j
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
 * �L�����ƃI�u�W�F�N�g�̏Փˌ��o
 * @param *pThingA �L����
 * @param *pThingB �I�u�W�F�N�g
 */
BOOL Collision(FbxMeshKM* pThingA, OBJECT pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB.Position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB.Radius)
	{
		return true;
	}
	return false;
}

/*
 * �L�����ƃe�N�X�`���̏Փˌ��o
 * @param *pThingA �L����
 * @param *pThingB �e�N�X�`��
 */
BOOL Collision2(FbxMeshKM* pThingA, TEXTURE* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB->Position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB->Radius)
	{
		return true;
	}
	return false;
}

/*
 * �L�����ƃM�~�b�N�̏Փˌ��o
 * @param *pThingA �L����
 * @param *pThingB �M�~�b�N
 */
BOOL Collision3(FbxMeshKM* pThingA, GIMMICK* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB->Position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB->Radius)
	{
		return true;
	}
	return false;
}

/*
 * �L�������m�̏Փˌ��o
 * @param *pThingA �L�����P
 * @param *pThingB �L�����Q
 */
BOOL Collision4(FbxMeshKM* pThingA, FbxMeshKM* pThingB)
{
	//�Q�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vLength = pThingB->position - pThingA->position;
	FLOAT fLength = D3DXVec3Length(&vLength);
	if (fLength <= pThingA->Radius + pThingB->Radius)
	{
		return true;
	}
	return false;
}

/*
 * �M�~�b�N�Ƃ̓����蔻��
 * @param i �v���C���[�̎��ʔԍ�
 * @param type �v���C���[�̏��
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
 * �{�^�����N���b�N������
 * @param num �ǂ̃p�b�h�������ꂽ��
 * @param g_trg �v���C���[�̃{�^������
 * @param obj_name �I�u�W�F�N�g�̖��O
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
 * �A�C�e���h���b�v
 * @param i �I�u�W�F�N�g�̓Y����
 * @param num �ǂ̃p�b�h�������ꂽ��
 * @param g_trg �v���C���[�̃{�^������
 * @param *point �|�C���g�̃|�C���^
 */
static void ItemDrop(int i, int num, int g_trg, int* point)
{
	if (Obj[i].obj_name == OBJ_TREE)
	{
		if (i == 0)
		{
			if (ClickButton(num, g_trg, OBJ_TREE) == true)
			{
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(WOOD);		// SE�Đ�
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
				StartSE(ROCK);		// SE�Đ�
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
				StartSE(ROCK);		// SE�Đ�
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
				StartSE(ROCK);		// SE�Đ�
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
				StartSE(ROCK);		// SE�Đ�
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
				StartSE(ROCK);		// SE�Đ�
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
				StartSE(ROCK);		// SE�Đ�
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
					StartSE(CRAFT);		// SE�Đ�
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
					StartSE(CRAFT);		// SE�Đ�
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
 * �L�m�R�̃Q�b�g
 * @param num �ǂ̃p�b�h�������ꂽ��
 * @param g_trg �v���C���[�̃{�^������
 * @param *point �|�C���g�̃|�C���^
 * @param p_name 'p' = ����Ȃ��A'w' = ���킠�� 
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
					StartSE(PICK);		// SE�Đ�
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
					StartSE(PICK);		// SE�Đ�
					MotionChange(num, CHAR_PICK);
					mushroom[i].use = 0;
					*point += 200;
				}
			}
		}

	}
}

/*
 * ����񂲂̃Q�b�g
 * @param num �ǂ̃p�b�h�������ꂽ��
 * @param g_trg �v���C���[�̃{�^������
 * @param *point �|�C���g�̃|�C���^
 * @param p_name 'p' = ����Ȃ��A'w' = ���킠�� 
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
					StartSE(PICK);		// SE�Đ�
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
					StartSE(PICK);		// SE�Đ�
					MotionChange(num, CHAR_PICK);
					goldapple[i].use = 0;
					*point += 500;
				}
			}
		}
	}
}

/*
 * �t���O�̃Q�b�g
 * @param num �ǂ̃p�b�h�������ꂽ��
 * @param g_trg �v���C���[�̃{�^������
 * @param *point �|�C���g�̃|�C���^
 * @param p_name 'p' = ����Ȃ��A'w' = ���킠��
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
					StartSE(PICK);		// SE�Đ�
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
					StartSE(PICK);		// SE�Đ�
					flag[i].use = 0;
					*point += 200;
				}
			}
		}

	}
}

/*
 * @brief �v���C���[��FBX�Ƃ̓����蔻��
 * @param num �v���C���[�̎��ʔԍ�
 * @param *point �|�C���g�̃|�C���^
 * @param g_key �v���C���[�̃{�^������
 * @param g_trg �v���C���[�̃{�^������
 */
int CollsionDetection(int num, int* point, int g_key, int g_trg)
{
	int i;

	// �����蔻��
	D3DXVECTOR3 out, normal;
	if (Player[num]->use == 1)
	{
		D3DXVECTOR3 PposUp(Player[num]->position.x, Player[num]->position.y + 30, Player[num]->position.z - 30);
		D3DXVECTOR3 PposRight(Player[num]->position.x + 30, Player[num]->position.y + 30, Player[num]->position.z);
		// -y(�n��)�����̃��C����
		if (stage2->Raycast2(Player[num]->position, D3DXVECTOR3(0, -1, 0), 4.0f, out, normal) != -1)
		{
			Player[num]->position.y = out.y + 4;
		}
		if (Player[num]->direction[1] == 1)
		{
			// -z����(��)�̃��C����
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
			// -x(��)�����̃��C����
			if (stage2->Raycast2(Player[num]->position, D3DXVECTOR3(-1, 0, 0), 30.0f, out, normal) != -1)
			{
				Player[num]->position.x = out.x + 30;
			}
		}
		if (Player[num]->direction[3] == 1)
		{
			// x(�E)�����̃��C����
			if (stage2->Raycast2(Player[num]->position, D3DXVECTOR3(1, 0, 0), 30.0f, out, normal) != -1)
			{
				Player[num]->position.x = out.x - 30;
			}
			if (stage2->Raycast2(PposRight, D3DXVECTOR3(0, -1, 0), 50.0f, out, normal) != -1)
			{
				Player[num]->position.y = out.y + 8;
			}
		}

		// �}�b�v�O�ɏo�Ȃ��悤��
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
		Player[num]->position.y -= GRAVITY;		// �d�͕t��
	}


	// �I�u�W�F�N�g�̓����蔻��
	if (Player[num]->DamageTime >= 0)
	{
		return false;
	}
	// �L�����ƃI�u�W�F�N�g�̔���
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

	// �A�C�e�����擾�ł��邩
	GetMushroom(num, g_trg, point, 'p');
	GetGoldApple(num, g_trg, point, 'p');
	GetFlag(num, g_trg, point, 'p');
	
	return true;
}

/*
 * @brief ���펝���v���C���[��FBX�Ƃ̓����蔻��
 * @param num �v���C���[�̎��ʔԍ�
 * @param *point �|�C���g�̃|�C���^
 * @param g_key �v���C���[�̃{�^������
 * @param g_trg �v���C���[�̃{�^������
 */
int CollsionDetectionWeapon(int num, int* point, int g_key, int g_trg)
{
	int i;

	// �����蔻��
	D3DXVECTOR3 out, normal;

	D3DXVECTOR3 PposUp(PlayerWeapon[num]->position.x, PlayerWeapon[num]->position.y + 30, PlayerWeapon[num]->position.z - 30);
	D3DXVECTOR3 PposRight(PlayerWeapon[num]->position.x + 30, PlayerWeapon[num]->position.y + 30, PlayerWeapon[num]->position.z);
	// -y(�n��)�����̃��C����
	if (stage->Raycast2(PlayerWeapon[num]->position, D3DXVECTOR3(0, -1, 0), 4.0f, out, normal) != -1)
	{
		PlayerWeapon[num]->position.y = out.y + 4;
	}
	if (PlayerWeapon[num]->direction[1] == 1)
	{
		// -z����(��)�̃��C����
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
		// -x(��)�����̃��C����
		if (stage->Raycast2(PlayerWeapon[num]->position, D3DXVECTOR3(-1, 0, 0), 30.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.x = out.x + 30;
		}
	}
	if (PlayerWeapon[num]->direction[3] == 1)
	{
		// x(�E)�����̃��C����
		if (stage->Raycast2(PlayerWeapon[num]->position, D3DXVECTOR3(1, 0, 0), 30.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.x = out.x - 30;
		}
		if (stage->Raycast2(PposRight, D3DXVECTOR3(0, -1, 0), 50.0f, out, normal) != -1)
		{
			PlayerWeapon[num]->position.y = out.y + 8;
		}
	}

	// �}�b�v�O�ɏo�Ȃ��悤��
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
	PlayerWeapon[num]->position.y -= GRAVITY;		// �d�͕t��

	// �I�u�W�F�N�g�̓����蔻��
	if (PlayerWeapon[num]->DamageTime >= 0)
	{
		return false;
	}
	// �L�����ƃI�u�W�F�N�g�̔���
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

	// �A�C�e�����擾�ł��邩
	GetMushroom(num, g_trg, point, 'w');
	GetGoldApple(num, g_trg, point, 'w');
	GetFlag(num, g_trg, point, 'w');

	return true;
}
