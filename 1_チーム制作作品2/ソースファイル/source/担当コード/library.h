/*
 * @file library.cpp
 * @brief ���C�u��������
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include "FbxMesh.h"


#ifndef __IEXTREME_H__
#define __IEXTREME_H__

#define _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_DEPRECATE

#define OK					0	// ����I��
#define ERRORCODE			-1	// �G���[
#define ERR_NOHARDWARE		-2	// �n�[�h�E�F�A�G���[
#define ERR_PAD				-3	// �p�b�h�G���[
#define ERR_CHAR			-4	// �L�����N�^�[�G���[

#define SAFE_RELEASE(p)	{ if(p)	{ (p)->Release();(p)=NULL; } }
#define MODE_WINDOWED			0x0001							// �E�B���h�E���[�h�w��

// �L�[�萔
#define KEYIN_2					0x0001					// �Q�L�[�`�F�b�N�}�X�N
#define KEYIN_DOWN				0x0001					// ���L�[�`�F�b�N�}�X�N
#define KEYIN_4					0x0002					// �S�L�[�`�F�b�N�}�X�N
#define KEYIN_LEFT				0x0002					// ���L�[�`�F�b�N�}�X�N
#define KEYIN_6					0x0004					// �U�L�[�`�F�b�N�}�X�N
#define KEYIN_RIGHT				0x0004					// ���L�[�`�F�b�N�}�X�N
#define KEYIN_8					0x0008					// �W�L�[�`�F�b�N�}�X�N
#define KEYIN_UP				0x0008					// ���L�[�`�F�b�N�}�X�N
#define KEYIN_SPC				0x0010					// �X�y�[�X�`�F�b�N�}�X�N
#define KEYIN_ESC				0x0020					// �����߃`�F�b�N�}�X�N
#define KEYIN_START				0x0020					// �X�^�[�g�L�[�`�F�b�N�}�X�N
#define KEYIN_SFT				0x0040					// �V�t�g�`�F�b�N�}�X�N
#define KEYIN_RET				0x0080					// ���^�[���`�F�b�N�}�X�N
#define KEYIN_Z					0x0100					// �y�`�F�b�N�}�X�N
#define KEYIN_X					0x0200					// �w�`�F�b�N�}�X�N
#define KEYIN_C					0x0400					// �b�`�F�b�N�}�X�N
#define KEYIN_A					0x0800					// �`�`�F�b�N�}�X�N
#define KEYIN_S					0x1000					// �r�`�F�b�N�}�X�N
#define KEYIN_D					0x2000					// �c�`�F�b�N�}�X�N
#define KEYIN_Q					0x4000					// �p�`�F�b�N�}�X�N
#define KEYIN_W					0x8000					// �v�`�F�b�N�}�X�N

#define PICTURE_NAME_MAX 200		//�摜�t�@�C�����̍ő啶����
#define PICTURE_MAX 2000			//�摜�ǂݍ��ݍő吔
#define PICTURE_BLOCK_MAX 2000		//�摜�o�^�ő吔

#define PIC_HANDLE_HEAD 0x10000000	//�n���h���̓�
#define PICTURE_LR 0x00000002		//���E���]�t���O
#define PICTURE_UD 0x00000004		//�㉺���]�t���O

// �ڑ��\�W���C�X�e�B�b�N��
#define MAX_JOYSTICK_COUNT	4

#define JOYSTICKID3 2
#define JOYSTICKID4 3

// �Q�[������
#define GAME_TIME 120

#define MAX_POINT_NUM		640								// �`��ő�_��
#define AM_MAX_RECT_NUM			( MAX_POINT_NUM / 2 )		// �`��ő咷���`��

// ��ʃT�C�Y
#define DISP_W		1280
#define DISP_H		720

// �u�����h���[�h
#define DRAW_NOBLEND		0x0004	// �u�����h�Ȃ�
#define DRAW_ALPHABLEND		0x0008	// �A���t�@�u�����f�B���O
#define DRAW_ADDBLEND		0x0010	// ���Z�u�����f�B���O

extern D3DFORMAT	gScreenFormat;
extern int			gScreenWidth;
extern int			gScreenHeight;

extern IDirect3DDevice9*	gDevice;
extern HWND					gWindow;

bool InitD3D(HWND hWnd, bool bFullScreen);
void ReleaseD3D();
void BeginScene();
void EndScene();

/** �E�C���h�E�쐬
 disp_w, disp_h : ��ʃT�C�Y
 WindowName		: �E�C���h�E�̖��O
*/
void InitWnd(HINSTANCE hInst, int disp_w, int disp_h, LPSTR WindowName);
bool InitApp();
void ReleaseFont();

// �L�[���̓��[�h
enum PAD_NUMBER
{
	INPUT_MULT,
	INPUT_PAD1,
	INPUT_PAD2,
	INPUT_PAD3,
	INPUT_PAD4
};

struct JOYPAD
{									// �W���C�p�b�h�\����
	UINT		uJoyID;											// �W���C�X�e�B�b�N�h�c
	BOOL		bValid;											// �W���C�X�e�B�b�N�L����
	DWORD		nMinX, nMaxX;									// �X�e�B�b�N�̍ő�A�ŏ��l
	DWORD		nMinY, nMaxY;
	DWORD		nCenterX, nCenterY;								// �����l
	DWORD		nLeft, nRight;									// ���E�������l
	DWORD		nTop, nBottom;									// �㉺�������l
};

extern int CheckKey(int nInputMode);									// �L�[��������Ă��邩�`�F�b�N

/**
 *  1P�`4P�܂ł̃L�[���͎擾
 */
extern void InKey();

/*
 * �R���g���[���[���ڑ�����Ă��邩�̊m�F
 */
extern bool ConnectionPad();

/**
 *  �p�b�h������
 */
extern int InitJoyPad(int nMaxPadNum);								// �p�b�h������

/**
 *  �p�b�h�g�p�I��
 */
extern int EndJoyPad(void);											// �p�b�h�g�p�I��

/**
 *  �P�̃p�b�h���͕t��
 */
extern int AddJoyInput(int nPadIndex, int nKeyState);				// �P�̃p�b�h���͕t��
extern int gJoyPadNum;											// �W���C�p�b�h��

extern int gKeyold1;
extern int gKey1;
extern int gTrg1;

extern int gKeyold2;
extern int gKey2;
extern int gTrg2;

extern int gKeyold3;
extern int gKey3;
extern int gTrg3;

extern int gKeyold4;
extern int gKey4;
extern int gTrg4;

/**
 *�@������g�p������
 */
extern int InitFont();

/**
 *�@������`��
 *�@@param	x,y		�`����W
 *�@@param	color	�F�R�[�h
 *�@@param	fmt		������
 *�@@param	...		(����Ȃ�)�\���������ϐ��Ȃ�
 */
void DrawString(float x, float y, int color, const char *fmt, ...);

/**
 *�@�F�R�[�h�̊l��
 *�@@param	alpha	�A���t�@�l�ANULL������Ǝ����I��255�ɂȂ�
 *�@@param	red		�Ԃ̒l
 *�@@param	green	�΂̒l
 *�@@param	blue	�̒l
 *�@@return	�F�R�[�h��Ԃ�
 */
DWORD GetColor(int alpha, int red, int green, int blue);

// �摜���\����
struct KT_2DPIC_INFO {
	unsigned int					nLeft, nTop;					// �P�ʃs�N�`�����ł̈ʒu
	unsigned int					nWidth, nHeight;				// ���E����
	unsigned int					nRealWidth, nRealHeight;		// ���ۂ́i�����I�ȁj���E����
	IDirect3DTexture9* texture;							// �e�N�X�`��
	HRESULT						hRes;
};

/*
 * 2D�O���t�B�b�N���[�h
 */
KT_2DPIC_INFO CreateTexture(const char *szFileName);

/*
 * �e�N�X�`���X�v���b�g�쐬
 */
bool CreateSprit();

/*
 * �����[�X�X�v���b�g
 */
void RereaseSprit(IDirect3DTexture9* tex);

/*
 * �e�N�X�`���`��
 */
void DrawTexture(float x, float y, KT_2DPIC_INFO* pic, IDirect3DTexture9* tex, int draw_mode);

// 2D���_�\����
struct AM_2DVERTEX {
	float				x, y, z, rhw;							// ���_���W
	DWORD				color;									// ���_�F
	float				tu, tv;									// �e�N�X�`�����W
};

/**
 * �`�惂�[�h�ݒ�
 * @param draw_mode �`�惂�[�h
 * @param nParam	���l
 */
void SetDrawMode(int draw_mode, int nParam);

/*
 * �����`�̕`��
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color);

#endif
