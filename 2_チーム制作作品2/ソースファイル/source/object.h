#pragma once
/*
 * @file object.cpp
 * @brief �I�u�W�F�N�g����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#define MAX_OBJECT 16		// �I�u�W�F�N�g�ő吔
#define MAX_GIMMICK 13		// �M�~�b�N�ő吔

struct GIMMICK// �M�~�b�N�\����
{
	D3DXVECTOR3 Position;
	float Radius;
};

struct OBJECT// �I�u�W�F�N�g�\����
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	int use;
	float Radius;
	D3DXVECTOR3 Scale;
	int GetLimitCount;	// �Q�b�g�ł����
	int obj_name;
	int ReGetTime;		// �Q�b�g�ł���܂ł̎���
};

enum OBUJECT_NAME	// �I�u�W�F�N�g��
{
	OBJ_TREE,
	OBJ_WOOD,
	OBJ_ROCK,
	OBJ_BOX,
};

// �I�u�W�F�N�g���
extern FbxMeshKM* Object[4];
extern OBJECT Obj[MAX_OBJECT];
// �M�~�b�N���
extern GIMMICK Gim[MAX_GIMMICK];

/*
 * �I�u�W�F�N�g������
 */
void InitObject();
/*
 * �I�u�W�F�N�g�����[�X
 */
void ReleaseObject();
/*
 * �I�u�W�F�N�g���Z�b�g
 */
void ResetObject();
/*
 * �I�u�W�F�N�g�`��
 */
void DrawObject();
