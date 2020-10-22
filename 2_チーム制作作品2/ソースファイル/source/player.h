#pragma once
/*
 * @file player.cpp
 * @brief �v���C���[����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "FbxMesh.h"
#include "library.h"

extern FbxMeshKM* Player[MAX_JOYSTICK_COUNT];
extern FbxMeshKM* PlayerWeapon[MAX_JOYSTICK_COUNT];

/*
*  @brief �L�����̏��
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
*  @brief �L�������m�̍U�����
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
*  @brief �v���C���[������
*/
void InitPlayer();

/*
*  @brief �L�����̃����[�X
*/
void ReleasePlayer();
/*
*  @brief �v���C���[�̃��Z�b�g
*  @param num �v���C���[���ʔԍ�
*/
void ResetPlayer(int num);
/*
*  @brief ���[�V������ς���
*  @param num �v���C���[���ʔԍ�
*  @param chartype �L�����̏��
*/
void MotionChange(int num, int chartype);
/*
*  @brief �v���C���[�̍s��
*  @param i �v���C���[���ʔԍ�
*  @param g_key �v���C���[�̃{�^������
*  @param g_trg �v���C���[�̃{�^������
*/
void ControllPlayer(int num, int g_key, int g_trg);
/*
*  @brief ���펝���v���C���[�̍s��
*  @param i �v���C���[���ʔԍ�
*  @param g_key �v���C���[�̃{�^������
*  @param g_trg �v���C���[�̃{�^������
*/
void ControllPlayerWeapon(int num, int g_key, int g_trg);
/*
*  @brief �v���C���[�`��
*/
void DrawPlayer();