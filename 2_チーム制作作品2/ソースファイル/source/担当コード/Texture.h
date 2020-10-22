#pragma once
/*
 * @file Texteru.cpp
 * @brief �e�N�X�`������
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "library.h"

#define MAX_TEXTURE 51		// �e�N�X�`���̍ő吔
#define MAX_MUSHROOM 36		// �L�m�R�̍ő吔
#define MAX_GOLDAPPLE 2		// ����񂲂̍ő吔
#define MAX_FLAG 4			// �t���O�̍ő吔
#define MAX_SURPRISED 14	// �r�b�N���}�[�N�̍ő吔
#define MAX_QUESTION 2		// �͂Ăȃ}�[�N�̍ő吔

/*
*  �e�N�X�`���̎��
*/
enum TEXTURE_TYPE
{
	STATUS1,
	STATUS2,
	STATUS3,
	STATUS4,
	POINT0,
	POINT1,
	POINT2,
	POINT3,
	POINT4,
	POINT5,

	POINT6,
	POINT7,
	POINT8,
	POINT9,
	TIMEBASE,
	TIME0,
	TIME1,
	TIME2,
	TIME3,
	TIME4,

	TIME5,
	TIME6,
	TIME7,
	TIME8,
	TIME9,
	FLAG1,
	FLAG2,
	FLAG3,
	FLAG4,
	APPLE,

	GOLDAPPLE,
	MUSHROOM,
	SURPRISED,
	QUESTION,
	TITLE,
	END,
	START,
	HAZIMERU,
	LOBBY,
	RESULT,
	LOAD,
	TITLELOGO,
	TEAMLOGO,
	POSE,
	BACK,
	TITLEBACK,

	OPERATION,
	OPERATION2,
	NEXT,
	STARTSIGNAL,
	ENDSIGNAL,
};

/*
*  �e�N�X�`���̍\����
*/
struct TEXTURE
{
	TEXTURE_TYPE type;
	int use;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
	float Radius;
	float x, y;
};

/*
*  ���_�f�[�^�̍\����
*/
struct TLVERTX
{
	float x, y, z;	// �ʒu���
	float rhw;		// ���_�ϊ��l
	D3DCOLOR color;	// ���_�J���[
	float tu, tv;	// �e�N�X�`�����W
};

extern TEXTURE flag[4];							// �t���O
extern TEXTURE mushroom[36];					// ���̂�
extern TEXTURE goldapple[2];					// �����
extern TEXTURE surprised[MAX_SURPRISED];		// �r�b�N���}�[�N
extern TEXTURE question[MAX_QUESTION];			// �͂Ăȃ}�[�N

/*
 * �e�N�X�`���ǂݍ���
 */
void ReadTexture();

/*
 * �e�N�X�`��������
 */
void ResetTexture();
/*
*  @brief �t���O�`��
*  @param num �v���C���[���ʔԍ�
*/
void DropFlag(int num);

/*
 * �t���O�̕`��
 */
void DrawFlag();

/*
 * �}�[�N�̕`��
 */
void DrawMark();
/*
*  @brief �|�C���g�`��
*  @param x ���W
*  @param y ���W
*  @param point �����|�C���g
*/
void DrawEquipmentPoint(float x, float y, int point);
/*
*  @brief ���ԕ`��
*  @param x ���W
*  @param y ���W
*  @param time �����|�C���g
*  @param zero ���ƕb�̋��
*/
void DrawEquipmentTime(float x, float y, int time, int zero);

/*
 * UI�`��
 */
void DrawUI();
/*
*  @brief �����̃|�C���g�`��
*  @param num �v���C���[���ʔԍ�
*  @param point �����̃|�C���g
*  @param mode �Q�[�����[�h
*/
void DrawPoint(int num, int point, int mode);
/*
*  @brief �q�b�g�|�C���g�̕`��
*  @param num �v���C���[���ʔԍ�
*  @param hp �q�b�g�|�C���g
*/
void DrawHitPoint(int num, int hp);
/*
*  @brief �������Ԃ̕`��
*  @param minute ��
*  @param second �b
*/
void DrawTime(int minute, int second);

/*
 * �A�C�e���`��
 */
void DrawItem();

/*
 * �A�E�g�Q�[���̕`��
 */
void DrawOutGame(float x, float y, int drawtype);

/*
 * ��������`��
 */
void DrawOperation(int drawtype);
