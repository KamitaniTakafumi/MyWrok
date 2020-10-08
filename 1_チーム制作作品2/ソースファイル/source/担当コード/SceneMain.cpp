/*
 * @file SceneMain.cpp
 * @brief �Q�[�����C������
 * @author ��J���j
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

DWORD gBeforeTime;	// �O��̎���
DWORD gCurrentTime;	// ����̎���
float gDeltaTime;	// �o�ߎ���(�Q�[���S�̂ŋ��L)
int gPointCount[4];	// �|�C���g�J�E���g
int *gpPointCount;			// �|�C���g�J�E���g�|�C���^
int gGameTime;		// ��������
int gFrameCount;	// �P�t���[���̃J�E���g
int gTimeMinute;	// ��������(��)
int gTimeSecond;	// ��������(�b)
int gOperationFlag;	// �������
int gWaitTime;		// �҂�����

FbxMeshKM* stage, *stage2, *wall;   // �����_�����O����X�e�[�W

FbxMeshKM* home[MAX_JOYSTICK_COUNT];	// �X�^�[�g�n�_���

/*
 * �h���C�o�̏�����
 */
void InitDevice()
{
	//	���ݒ�
	gDevice->SetRenderState(D3DRS_AMBIENT, 0x808080);		// �A���r�G�C�g��(����)
	gDevice->SetRenderState(D3DRS_LIGHTING, false);			// ���C�gfalse
	//	�t�H�O
	gDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

/*
 * �Q�[�����C���̏�����
 */
void InitGame()
{
	int i;
	// �|�C���g�̏�����
	for (i = 0; i < gJoyPadNum; i++)
	{
		gPointCount[i] = 0;
	}
	
	// �X�e�[�W�̏�����
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

	// �Ɠǂݍ���
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

	InitCamera();		//	�J����������

	InitObject();		// �I�u�W�F�N�g

	// �t���[���J�E���g������
	for (i = 0; i < 5; i++)
	{
		gFrameCount = 0;
	}
	gGameTime = GAME_TIME;		// ��������

	gOperationFlag = 1;
	gWaitTime = 180;

	//	�������̍Ō�
	gBeforeTime = timeGetTime();

	gGameMode.Mode = GAME_IN;
}

/*
 * �X�e�[�W�̃����[�X
 */
void ReleaseStage()
{
	delete stage;
	delete stage2;
	delete wall;
}


/*
*  @brief ���Z�b�g�Q�[��
*  @param mode �Q�[�����[�h
*/
int ResetGame(int mode)
{
	int i;
	gGameMode.Mode = mode;

	// �v���C���[�̏�����
	for (i = 0; i < gJoyPadNum; i++)
	{
		ResetPlayer(i);
		gPointCount[i] = 0;
	}

	// �I�u�W�F�N�g�̏�����
	ResetObject();

	// �e�N�X�`���̏�����
	ResetTexture();

	gFrameCount = 0;
	gGameTime = GAME_TIME;		// �������Ԃ̑��

	if (mode == GAME_RESULT)
	{
		DSoundStop(sndBgm);
		// �ȃf�[�^���t�J�n
		DSoundPlay(sndResult, TRUE);
	}
	if (mode == GAME_TITLE)
	{
		DSoundStop(sndBgm);
		// �ȃf�[�^���t�J�n
		DSoundPlay(sndTitle, TRUE);
	}
	return mode;
}

/*
 * ���C���Q�[���̃A�b�v�f�[�g
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

	gFrameCount++;	// �������Ԃ̃t���[���J�E���g�A�b�v
	// �������I��������ǂ����̗L��
	if ((gFrameCount / 60) == 1)
	{
		gGameTime--;			// �������Ԃ����炷
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

	float deltaTime = 1.0f / 60.0f;			// �A�j���[�V�����^�C��
	// �L�������Ƃ̎��Ԍv�Z
	for (i = 0; i < gJoyPadNum; i++)
	{
		Player[i]->DamageTime--;		// �_���[�W�N�[���^�C��
		Player[i]->RespawnTime--;		// ���X�|�[���^�C��
		Player[i]->motionTime--;		// ���[�V��������
		PlayerWeapon[i]->DamageTime--;		// �_���[�W�N�[���^�C��
		PlayerWeapon[i]->RespawnTime--;		// ���X�|�[���^�C��
		PlayerWeapon[i]->motionTime--;		// ���[�V��������
		// ���[�V������idle�ɖ߂�
		if (Player[i]->use == 1)
		{
			if ((Player[i]->motionTime < 0 && Player[i]->CharState == CHAR_ATTACK) ||
				(Player[i]->motionTime < 0 && Player[i]->CharState == CHAR_HIT) ||
				(Player[i]->motionTime < 0 && Player[i]->CharState == CHAR_PICK))
			{
				Player[i]->CharState = CHAR_IDLE;
			}
			// �L�����𕐊펝���ɕς���
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

		// ���X�|�[��
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
	// �I�u�W�F�N�g����A�C�e�����Q�b�g�ł���܂ł̎���
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
	// �r�b�N���}�[�N������
	for (i = 0; i < MAX_SURPRISED; i++)
	{
		surprised[i].use = 0;
	}
	// �͂Ăȃ}�[�N������
	for (i = 0; i < MAX_QUESTION; i++)
	{
		question[i].use = 0;
	}

	D3DXVECTOR3 forward = GetForward(&cv);
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);
	D3DXVECTOR3 right = GetRight(&cv);
	
	gTimeMinute = gGameTime / 60;		// ��������(��)
	gTimeSecond = gGameTime % 60;		// ��������(�b)

	// �L�����ړ�
	for (i = 0; i < gJoyPadNum; i++)
	{
		gpPointCount = &gPointCount[i];		// �|�C���g�̃|�C���^����

		// �v���C���[(����Ȃ�)
		if (Player[i]->use == 1)
		{
			if (i == 0)
			{
				CollsionDetection(i, gpPointCount, gKey1, gTrg1);	// �����蔻��
				ControllPlayer(i, gKey1, gTrg1);			// �L�����ړ�
			}
			else if (i == 1)
			{
				CollsionDetection(i, gpPointCount, gKey2, gTrg2);	// �����蔻��
				ControllPlayer(i, gKey2, gTrg2);			// �L�����ړ�
			}
			else if (i == 2)
			{
				CollsionDetection(i, gpPointCount, gKey3, gTrg3);	// �����蔻��
				ControllPlayer(i, gKey3, gTrg3);			// �L�����ړ�
			}
			else
			{
				CollsionDetection(i, gpPointCount, gKey4, gTrg4);	// �����蔻��
				ControllPlayer(i, gKey4, gTrg4);			// �L�����ړ�
			}
		}
		// �v���C���[(���킠��)
		else if (PlayerWeapon[i]->use == 1)
		{
			if (i == 0)
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey1, gTrg1);	// �����蔻��
				ControllPlayerWeapon(i, gKey1, gTrg1);			// �L�����ړ�
			}
			else if (i == 1)
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey2, gTrg2);	// �����蔻��
				ControllPlayerWeapon(i, gKey2, gTrg2);			// �L�����ړ�
			}
			else if (i == 2)
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey3, gTrg3);	// �����蔻��
				ControllPlayerWeapon(i, gKey3, gTrg3);			// �L�����ړ�
			}
			else
			{
				CollsionDetectionWeapon(i, gpPointCount, gKey4, gTrg4);	// �����蔻��
				ControllPlayerWeapon(i, gKey4, gTrg4);			// �L�����ړ�
			}
		}
		// ��ɗ������珉���ʒu�Ƀ��X�|�[��
		if (Player[i]->position.y <= -100)
		{
			gPointCount[i] -= 300;			// �|�C���g��300���炷
			Player[i]->HitPoint -= 3;		// �̗͂�3���炷
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
		// �|�C���g���O�ȉ��ɂȂ�Ȃ��悤��
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

	//	�r���[�s��ݒ�
	SetPosition(&cv, cv.pos);
	SetRotation(&cv, cv.angle);
	UpdateCamera(&cv);

	// �A�j���[�V����
	for (i = 0; i < gJoyPadNum; i++)
	{
		// �v���C���[(����Ȃ�)
		if (Player[i]->use == 1)
		{
			Player[i]->Update();
			Player[i]->Animate(deltaTime);
		}
		// �v���C���[(���킠��)
		else if (PlayerWeapon[i]->use == 1)
		{
			PlayerWeapon[i]->Update();
			PlayerWeapon[i]->Animate(deltaTime);
		}
	}

	//	���e�s��ݒ�
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, 1.0f, (float)gScreenWidth / (float)gScreenHeight, 0.2f, 3000.0f);
	gDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	return GAME_IN;
}


/*
 * ���C���Q�[���`��
 */
void SceneRender()
{
	int i;
	gDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFF606060, 1.0f, 0);
	stage->Render();		// �X�e�[�W�`��
	wall->Render();			// �Ǖ`��
	
	for (i = 0; i < gJoyPadNum; i++)
	{
		home[i]->Render();	// �ƕ`��
	}

	DrawUI();			// UI�`��

	DrawPlayer();		// �v���C���[

	// �I�u�W�F�N�g
	DrawObject();

	// �t���O
	DrawFlag();

	// �A�C�e��
	DrawItem();

	// �}�[�N
	DrawMark();

	for (i = 0; i < gJoyPadNum; i++)
	{
		DrawPoint(i, gPointCount[i], GAME_IN);		// �|�C���g
		DrawHitPoint(i, Player[i]->HitPoint);		// �̗�
	}

	DrawTime(gTimeMinute, gTimeSecond);			// ����

	// ��������A���}
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
