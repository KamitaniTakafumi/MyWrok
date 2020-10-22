#pragma once
/*
 * @file CollsionDetection.cpp
 * @brief �����蔻�菈��
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "Texture.h"
#include "object.h"

/*
 * �L�������m�̏Փˌ��o
 * @param pThingA �v���C���[
 * @param pThingB �I�u�W�F�N�g
 */
BOOL Collision(FbxMeshKM* pThingA, OBJECT pThingB);
/*
 * �L�����ƃe�N�X�`���̏Փˌ��o
 * @param pThingA �v���C���[�P
 * @param pThingB �e�N�X�`��
 */
BOOL Collision2(FbxMeshKM* pThingA, TEXTURE* pThingB);
/*
 * �L�������m�̏Փˌ��o
 * @param pThingA �v���C���[�P
 * @param pThingB �v���C���[�Q
 */
BOOL Collision4(FbxMeshKM* pThingA, FbxMeshKM* pThingB);
/*
 * �M�~�b�N�Ƃ̓����蔻��
 * @param i �v���C���[�̎��ʔԍ�
 * @param type �v���C���[�̏��
 */
bool PlayerGimmickHit(int i, int type);
/*
 * �v���C���[��FBX�Ƃ̓����蔻��
 * @param num �v���C���[�̎��ʔԍ�
 * @param *point �|�C���g�̃|�C���^
 * @param g_key �v���C���[�̃{�^������
 * @param g_trg �v���C���[�̃{�^������
 */
int CollsionDetection(int num, int* point, int g_key, int g_trg);
/*
 * ���펝���v���C���[��FBX�Ƃ̓����蔻��
 * @param num �v���C���[�̎��ʔԍ�
 * @param *point �|�C���g�̃|�C���^
 * @param g_key �v���C���[�̃{�^������
 * @param g_trg �v���C���[�̃{�^������
 */
int CollsionDetectionWeapon(int num, int* point, int g_key, int g_trg);
