/*
 * @file player.cpp
 * @brief �v���C���[����
 * @author ��J���j
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

// �v���C���[���
FbxMeshKM* Player[MAX_JOYSTICK_COUNT];
// ����v���C���[���
FbxMeshKM* PlayerWeapon[MAX_JOYSTICK_COUNT];

float gAngle[4] = { 0.0f };
int gPushNum[4] = { 0 };
// �J�����ɍ��W(r, ��, ��)
D3DXVECTOR3 gCamPolarCoord(500.0f, 70.0f * M_PI*2.0f / 360.0f, 3.1416f * 3.0f / 2.0f);
D3DXVECTOR3 gKnockBack;

/*
 * ������
 */
void InitPlayer()
{
	int i;
	for (i = 0; i < gJoyPadNum; i++)
	{
		Player[i] = new FbxMeshKM();
		PlayerWeapon[i] = new FbxMeshKM();
		// �v���C���[�P
		if (i == 0)
		{
			Player[0]->Create("Assets/chara/player2/char_p.fbx");
			Player[0]->position = D3DXVECTOR3(880, 290, -1650);
			Player[0]->padnumber = INPUT_PAD1;			// �L�����Ƀp�b�h��Ή�������
			PlayerWeapon[0]->Create("Assets/chara/player2/char_p_a.fbx");
			PlayerWeapon[0]->padnumber = INPUT_PAD1;	// �L�����Ƀp�b�h��Ή�������
		}
		// �v���C���[�Q
		else if (i == 1)
		{
			Player[1]->Create("Assets/chara/player4/char_t.fbx");
			Player[1]->position = D3DXVECTOR3(-860, 290, -1650);
			Player[1]->padnumber = INPUT_PAD2;			// �L�����Ƀp�b�h��Ή�������
			PlayerWeapon[1]->Create("Assets/chara/player4/char_t_a.fbx");
			PlayerWeapon[1]->padnumber = INPUT_PAD2;	// �L�����Ƀp�b�h��Ή�������
		}
		// �v���C���[�R
		else if (i == 2)
		{
			Player[2]->Create("Assets/chara/player1/char_g.fbx");
			Player[2]->position = D3DXVECTOR3(880, 5, -150);
			Player[2]->padnumber = INPUT_PAD3;			// �L�����Ƀp�b�h��Ή�������
			PlayerWeapon[2]->Create("Assets/chara/player1/char_g_a.fbx");
			PlayerWeapon[2]->padnumber = INPUT_PAD3;	// �L�����Ƀp�b�h��Ή�������
		}
		// �v���C���[�S
		else if (i == 3)
		{
			Player[3]->Create("Assets/chara/player3/char_pn.fbx");
			Player[3]->position = D3DXVECTOR3(-860, 5, -150);
			Player[3]->padnumber = INPUT_PAD4;			// �L�����Ƀp�b�h��Ή�������
			PlayerWeapon[3]->Create("Assets/chara/player3/char_pn_a.fbx");
			PlayerWeapon[3]->padnumber = INPUT_PAD4;	// �L�����Ƀp�b�h��Ή�������
		}
		Player[i]->AddMotion("idle", "Assets/chara/char_walk.fbx");		// ���[�V����(����)
		Player[i]->AddMotion("throw", "Assets/chara/char_throw.fbx");	// ���[�V����(����)
		Player[i]->AddMotion("hit", "Assets/chara/char_hit.fbx");		// ���[�V����(�_���[�W)
		Player[i]->AddMotion("create", "Assets/chara/char_create.fbx");	// ���[�V����(�N���G�C�g)
		Player[i]->AddMotion("pick", "Assets/chara/char_pick.fbx");		// ���[�V����(�E��)
		Player[i]->Play("idle");										// ���[�V�����Đ�
		Player[i]->CharState = CHAR_IDLE;								// �L�����̃X�e�[�g��IDOL�ɂ���
		Player[i]->Radius = 50.0f;										// �L�������a
		Player[i]->rotation = D3DXVECTOR3(0, 0, 0);						// �L�����̉�]
		Player[i]->scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);				// �L�����̑傫��
		Player[i]->HitPoint = 10;										// �̗�
		Player[i]->RespawnTime = 0;										// ���X�|�[������
		Player[i]->DamageTime = 0;										// �_���[�W����
		Player[i]->use = 1;												// �g�p�̗L��
		PlayerWeapon[i]->rotation = D3DXVECTOR3(0, 0, 0);
		PlayerWeapon[i]->scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
		PlayerWeapon[i]->AttackNum = 0;
		PlayerWeapon[i]->Radius = 50.0f;
		PlayerWeapon[i]->use = 0;
		Player[i]->Update();
	}
}

/*
 * �L�����̃����[�X
 */
void ReleasePlayer()
{
	for (int i = 0; i < gJoyPadNum; i++)
	{
		delete Player[i];
	}

}

/*
*  @brief �v���C���[�̃��Z�b�g
*  @param num �v���C���[���ʔԍ�
*/
void ResetPlayer(int num)
{
	// �L�������ƂɈʒu�����Z�b�g
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
	PlayerWeapon[num]->use = 0;						// ���펝���͏���
	PlayerWeapon[num]->AttackNum = 0;				// �U���񐔂����Z�b�g
	Player[num]->rotation = D3DXVECTOR3(0, 0, 0);	// ���������Z�b�g
	Player[num]->HitPoint = 10;						// �̗͂����Z�b�g
	Player[num]->use = 1;							// �v���C���[���g�p��Ԃɂ���
	Player[num]->Update();
}

/*
*  @brief ���[�V������ς���
*  @param num �v���C���[���ʔԍ�
*  @param chartype �L�����̏��
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
 * �m�b�N�o�b�N
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
*  @brief �L�������U�����s����
*  @param i �L�����̎��ʔԍ�
*  @param j �L�����̎��ʔԍ�
*  @param type �������Ă���L�������m�̏��
*/
static void PlayerAtttackDetection(int i, int j, int type)
{
	// ����Ȃ��ƕ���Ȃ�
	if (type == NORMAL_NORMAL)
	{
		// �v���C���[�P
		if (j == 0)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
		// �v���C���[�Q
		else if (j == 1)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
		// �v���C���[�R
		else if (j == 2)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
		// �v���C���[�S
		else if (j == 3)
		{
			if (Collision4(Player[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint--;
				Player[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], Player[j]);
			}
		}
	}
	// ����Ȃ��ƕ��킠��
	else if (type == NORMAL_WEAPON)
	{
		// �v���C���[�P
		if (j == 0)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
		// �v���C���[�Q
		else if (j == 1)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
		// �v���C���[�R
		else if (j == 2)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
		// �v���C���[�S
		else if (j == 3)
		{
			if (Collision4(Player[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				PlayerWeapon[j]->HitPoint--;
				PlayerWeapon[j]->DamageTime = 180;
				PlayerKnockBack(Player[i], PlayerWeapon[j]);
			}
		}
	}
	// ���킠��ƕ���Ȃ�
	else if (type == WEAPON_NORMAL)
	{
	// �v���C���[�P
		if (j == 0)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
		// �v���C���[�Q
		else if (j == 1)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
		// �v���C���[�R
		else if (j == 2)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
		// �v���C���[�S
		else if (j == 3)
		{
			if (Collision4(PlayerWeapon[i], Player[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], Player[j]);
			}
		}
	}
	// ���킠��ƕ��킠��
	else if (type == WEAPON_WEAPON)
	{
	// �v���C���[�P
		if (j == 0)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], PlayerWeapon[j]);
			}
		}
		// �v���C���[�Q
		else if (j == 1)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], PlayerWeapon[j]);
			}
		}
		// �v���C���[�R
		else if (j == 2)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
				MotionChange(j, CHAR_HIT);
				Player[j]->HitPoint -= 3;
				Player[j]->DamageTime = 180;
				PlayerWeapon[i]->AttackNum--;
				PlayerKnockBack(PlayerWeapon[i], PlayerWeapon[j]);
			}
		}
		// �v���C���[�S
		else if (j == 3)
		{
			if (Collision4(PlayerWeapon[i], PlayerWeapon[j]) != false)
			{
				StartSE(ATTACK);		// SE�Đ�
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
 * �L�������Ƃ̍U��
 * @param i �L�����̎��ʔԍ�
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
*  @brief �L�������U�����s����
*  @param i �L�����̎��ʔԍ�
*  @param type �L�����̏��
*  @param g_key �v���C���[�̃{�^������
*  @param g_trg �v���C���[�̃{�^������
*/
void PlayerAttack(int i, int type, int g_key, int g_trg)
{
	// �v���C���[(����Ȃ�)
	if (type == NORMAL)
	{
		// �_���[�W���͍U���ł��Ȃ��悤��
		if ((Player[i]->DamageTime <= 0) && (PlayerWeapon[i]->DamageTime <= 0))
		{
			// �U��
			if ((g_trg & KEYIN_A) && (Player[i]->CharState != CHAR_ATTACK) && (Player[i]->CharState != CHAR_CREATE))
			{
				MotionChange(i, CHAR_ATTACK);
				// �v���C���[�U��
				CharaAttack(i);
			}
		}
	}
	// �v���C���[(���킠��)
	else
	{
		// �_���[�W���͍U���ł��Ȃ��悤��
		if ((Player[i]->DamageTime <= 0) && (PlayerWeapon[i]->DamageTime <= 0))
		{
			// �U��
			if (g_trg & KEYIN_A)
			{
				// �v���C���[�U��
				CharaAttack(i);
			}
		}
	}
}

/*
*  @brief �v���C���[�̍s��
*  @param i �v���C���[���ʔԍ�
*  @param g_key �v���C���[�̃{�^������
*  @param g_trg �v���C���[�̃{�^������
*/
void ControllPlayer(int i, int g_key, int g_trg)
{
	D3DXVECTOR3 forward = GetForward(&cv);
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);
	D3DXVECTOR3 right = GetRight(&cv);

	// �������̏�����
	Player[i]->direction[0] = 0;
	Player[i]->direction[1] = 0;
	Player[i]->direction[2] = 0;
	Player[i]->direction[3] = 0;

	// �L�����ړ�
	if ((Player[i]->CharState == CHAR_IDLE) ||
		(Player[i]->CharState == CHAR_RUN))
	{
		gAngle[i] = 0.0f;
		gPushNum[i] = 0;

		// ��
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
		// ��
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
		// �E
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
		// ��
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
		// �ړ����Ă��Ȃ���΃L�����̃��[�V������idle�ɂ���
		if (!(g_key & KEYIN_DOWN) &&
			!(g_key & KEYIN_UP) &&
			!(g_key & KEYIN_RIGHT) &&
			!(g_key & KEYIN_LEFT))
		{
			MotionChange(i, CHAR_IDLE);
		}
	}

	// �U��
	PlayerAttack(i, NORMAL, g_key, g_trg);

	// ���X�|�[��
	if (Player[i]->HitPoint <= 0)
	{
		StartSE(DIE);		// SE�Đ�
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
*  @brief ���펝���v���C���[�̍s��
*  @param i �v���C���[���ʔԍ�
*  @param g_key �v���C���[�̃{�^������
*  @param g_trg �v���C���[�̃{�^������
*/
void ControllPlayerWeapon(int i, int g_key, int g_trg)
{
	D3DXVECTOR3 forward = GetForward(&cv);
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);
	D3DXVECTOR3 right = GetRight(&cv);

	// �������̏�����
	PlayerWeapon[i]->direction[0] = 0;
	PlayerWeapon[i]->direction[1] = 0;
	PlayerWeapon[i]->direction[2] = 0;
	PlayerWeapon[i]->direction[3] = 0;

	// �L�����ړ�
	if ((PlayerWeapon[i]->CharState == CHAR_IDLE) ||
		(PlayerWeapon[i]->CharState == CHAR_RUN))
	{
		gAngle[i] = 0.0f;
		gPushNum[i] = 0;

		// ��
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
		// ��
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
		// �E
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
		// ��
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
		// �ړ����Ă��Ȃ���΃L�����̃��[�V������idle�ɂ���
		if (!(g_key & KEYIN_DOWN) &&
			!(g_key & KEYIN_UP) &&
			!(g_key & KEYIN_RIGHT) &&
			!(g_key & KEYIN_LEFT))
		{
			PlayerWeapon[i]->CharState = CHAR_IDLE;
		}
	}


	// �U��
	PlayerAttack(i, WEAPON, g_key, g_trg);

	// ���X�|�[��
	if (PlayerWeapon[i]->HitPoint <= 0)
	{
		StartSE(DIE);		// SE�Đ�
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
	// �O��U�������畐�킪����
	if (PlayerWeapon[i]->AttackNum <= 0)
	{
		// ���펝�����畐��Ȃ��փL�������
		PlayerWeapon[i]->use = 0;
		Player[i]->use = 1;
		Player[i]->HitPoint = PlayerWeapon[i]->HitPoint;
		Player[i]->position = PlayerWeapon[i]->position;
		Player[i]->CharState = CHAR_IDLE;
	}

}

/*
 * �v���C���[�`��
 */
void DrawPlayer()
{
	int i;
	for (i = 0; i < gJoyPadNum; i++)
	{
		// ����Ȃ�
		if (Player[i]->use == 1)
		{
			Player[i]->Render();
		}
		// ���펝��
		if(PlayerWeapon[i]->use == 1)
		{
			PlayerWeapon[i]->Render();
		}
	}

}
