#pragma once
/*
 * @file SceneMain.cpp
 * @brief �Q�[�����C������
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "Camera.h"
#include "FbxMesh.h"

#define GRAVITY 2.0f		// �d��

extern CAMERA* camera;		// �J����
extern FbxMeshKM* stage, *stage2;   // �����_�����O����X�e�[�W
extern int gPointCount[4];	// �|�C���g�J�E���g

/*
 * �h���C�o�̏�����
 */
void InitDevice();

/*
 * �Q�[�����C���̏�����
 */
void InitGame();

/*
 * �X�e�[�W�̃����[�X
 */
void ReleaseStage();
/*
*  @brief ���Z�b�g�Q�[��
*  @param mode �Q�[�����[�h
*/
int ResetGame(int mode);

/*
 * ���C���Q�[���̃A�b�v�f�[�g
 */
int MainUpdate();

/*
 * ���C���Q�[���`��
 */
void SceneRender();
