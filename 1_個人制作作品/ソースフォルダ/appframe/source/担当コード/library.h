/**
 * @file library.cpp
 * @brief ���C�u��������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include "../appframe.h"


#ifndef __IEXTREME_H__
#define __IEXTREME_H__

#define _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_DEPRECATE

#define OK			1	// ����I��
#define DISPERROR	-1	// ��ʕ`��G���[
#define PADERROR	-2	// �p�b�h�G���[
#define BOXERROR	-3	// ��`�`��G���[
#define FONTERROR	-4	// �t�H���g�G���[
#define INPUTERROR	-5	// ���̓G���[

//#define MODE_DEBUG	// �f�o�b�O���[�h

#define PICTURE_NAME_MAX	200		//�摜�t�@�C�����̍ő啶����
#define PICTURE_MAX			2000	//�摜�ǂݍ��ݍő吔
#define PICTURE_BLOCK_MAX	2000	//�摜�o�^�ő吔

#define MAX_POINT_NUM	640		// �`��ő�_��
#define MAX_RECT_NUM	( MAX_POINT_NUM / 2 )	// �`��ő咷���`��

#define MAX_JOYSTICK_COUNT	4	// �ڑ��\�W���C�X�e�B�b�N��

#define JOYSTICKID3	2	// �W���C�X�e�B�b�N3
#define JOYSTICKID4	3	// �W���C�X�e�B�b�N4

// �I�u�W�F�N�g�����S�ɊJ��
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

// Window�T�C�Y
#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

#define MAX_UNIT_PICTURES	2000	// �ő�P�ʃs�N�`����
#define MAX_USER_PICTURES	5000	// �ő僆�[�U�s�N�`����

#define MAX_EVENTS	10	// �ő�ꊇ�����C�x���g��

#define PIC2D_HANDLE_HEAD	0x10000000	// 2D�s�N�`���n���h���w�b�_

#define HANDLE_HEAD_MASK	0xff000000	// �n���h���w�b�_�}�X�N�l

#define DRAWPIC_LR			0x0001	// �`�捶�E���]�t���O
#define DRAWPIC_PICALPHA	0x0002	// �G�̃A���t�@�l�ŃA���t�@�u�����h
#define DRAWPIC_AVEALPHA	0x0004	// ���σA���t�@�u�����h
#define DRAWPIC_ADDALPHA	0x0008	// ���Z�u�����h

#define PICTURE_LR	0x0001	// ���E���]�t���O

#define DRAW_NOBLEND	0x0004	// �u�����h�Ȃ�
#define DRAW_ALPHABLEND	0x0008	// �A���t�@�u�����f�B���O
#define DRAW_ADDBLEND	0x0010	// ���Z�u�����f�B���O

#define MAX_BLEND_FACTOR	255	// �u�����h�t�@�N�^�ő�l
#define MAX_COLOR_FACTOR	255	// �F�t�@�N�^�ő�l

#define D3DFVF_2DTEX	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	// 2D�e�N�X�`�����_�t�H�[�}�b�g

#define MAX_PICTURE_NAME	200	// �ő�G�t�@�C������

// �L�[���̓��[�h
#define INPUT_MULT			0	// �}���`�v���b�N�X����
#define INPUT_KEYBOARD		1	// �L�[�{�[�h����
#define INPUT_PAD1			2	// �p�b�h�P����
#define INPUT_PAD2			3	// �p�b�h�Q����
#define INPUT_PAD3			4	// �p�b�h�R����
#define INPUT_PAD4			5	// �p�b�h�S����

// �L�[�萔
#define KEYIN_2			0x0001		// �Q�L�[�`�F�b�N�}�X�N
#define KEYIN_DOWN		0x0001		// ���L�[�`�F�b�N�}�X�N
#define KEYIN_4			0x0002		// �S�L�[�`�F�b�N�}�X�N
#define KEYIN_LEFT		0x0002		// ���L�[�`�F�b�N�}�X�N
#define KEYIN_6			0x0004		// �U�L�[�`�F�b�N�}�X�N
#define KEYIN_RIGHT		0x0004		// ���L�[�`�F�b�N�}�X�N
#define KEYIN_8			0x0008		// �W�L�[�`�F�b�N�}�X�N
#define KEYIN_UP		0x0008		// ���L�[�`�F�b�N�}�X�N
#define KEYIN_SPC		0x0010		// �X�y�[�X�`�F�b�N�}�X�N
#define KEYIN_ESC		0x0020		// �����߃`�F�b�N�}�X�N
#define KEYIN_START		0x0020		// �X�^�[�g�L�[�`�F�b�N�}�X�N
#define KEYIN_SFT		0x0040		// �V�t�g�`�F�b�N�}�X�N
#define KEYIN_RET		0x0080		// ���^�[���`�F�b�N�}�X�N
#define KEYIN_Z			0x0100		// �y�`�F�b�N�}�X�N(�p�b�hA)
#define KEYIN_X			0x0200		// �w�`�F�b�N�}�X�N(�p�b�hB)
#define KEYIN_C			0x0400		// �b�`�F�b�N�}�X�N(�p�b�hX)
#define KEYIN_A			0x0800		// �`�`�F�b�N�}�X�N(�p�b�hY)
#define KEYIN_S			0x1000		// �r�`�F�b�N�}�X�N(�p�b�hLB)
#define KEYIN_D			0x2000		// �c�`�F�b�N�}�X�N(�p�b�hRB)
#define KEYIN_Q			0x4000		// �p�`�F�b�N�}�X�N(�p�b�hBACK)
#define KEYIN_W			0x8000		// �v�`�F�b�N�}�X�N(�p�b�hSTART)

#define MAX_FPS		60	// �ő�FPS
//#define DRAW_FPS		// FPS�`��̗L��


bool InitD3D(HWND hWnd, bool bFullScreen);
void ReleaseD3D();
void BeginScene();
void EndScene();

/** �E�C���h�E�쐬
 disp_w, disp_h : ��ʃT�C�Y
 WindowName		: �E�C���h�E�̖��O
*/
void InitWnd(HINSTANCE hInst, int disp_w, int disp_h, LPSTR WindowName);
extern int ProcessEvent();
bool InitApp();
void ReleaseFont();



// �W���C�p�b�h�\����
struct JOYPAD
{
	UINT		uJoyID;					// �W���C�X�e�B�b�N�h�c
	BOOL		bValid;					// �W���C�X�e�B�b�N�L����
	DWORD		nMinX, nMaxX;			// �X�e�B�b�N�̍ő�A�ŏ��l
	DWORD		nMinY, nMaxY;
	DWORD		nCenterX, nCenterY;		// �����l
	DWORD		nLeft, nRight;			// ���E�������l
	DWORD		nTop, nBottom;			// �㉺�������l
};

extern int CheckKey(int nInputMode);	// �L�[��������Ă��邩�`�F�b�N
extern void InKey();
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

/**
 * �L�[����
 * @parme nPushKey �����ꂽ�L�[
 * @parme nJudgKey ���肵�����L�[
 */
extern bool KeyJudg(int nPushKey, int nJudgKey);

/**
 * �p�b�h����
 * @parme nPushPad �����ꂽ�{�^��
 * @parme nJudgPad ���肵�����{�^��
 */
extern bool PadJudg(int nPushPad, int nJudgPad);

extern int gJoyPadNum;	// �W���C�p�b�h��

/**
 * ������g�p������
 */
extern int InitFont();

/**
 * ������`��
 * @param x,y	�`����W
 * @param color	�F�R�[�h
 * @param fmt	������
 * @param ...	�\���������ϐ��Ȃ�
 */
extern void DrawString(float x, float y, int color, const char *fmt, ...);
DWORD GetColor(int alpha, int red, int green, int blue);


/**
 * �摜���\����
 */
struct TEX_2DPIC_INFO {
	int					nWidth, nHeight;						// ���E����
	int					nRealWidth, nRealHeight;				// ���ۂ́i�����I�ȁj���E����
	int					nBitDepth, nRealDepth;					// ���̃r�b�g�f�v�X�Ǝ��ۂ̃r�b�g�f�v�X
};

/**
 * �P�ʃs�N�`���\����
 */
struct TEX_UNIT_PICTURE {
	TEX_2DPIC_INFO				a2PicInfo;						// �s�N�`�����
	LPDIRECT3DTEXTURE9		pPicture;						// �s�N�`��
	char						szFileName[PICTURE_NAME_MAX];	// �s�N�`���t�@�C����
};

/**
 * ���[�U�s�N�`���\����
 */
struct TEX_USER_PICTURE {
	TEX_UNIT_PICTURE				*pUnitPic;						// �P�ʃs�N�`��
	int							nLeft, nTop;					// �P�ʃs�N�`�����ł̈ʒu
	int							nWidth, nHeight;				// ���ƍ���
	int							bFlags;							// �����t���O
};

extern int LoadTexture(char *szFileName);
extern int LoadBlkTexture(char *szFileName, int nXSize, int nYSize,
	int nXNum, int nYNum, int nAllNum, int *phHandleBuf);
extern int Release2DGraphs(void);
extern int InitBlendState(void);

/**
 * �u�����h�X�e�[�g�\����
 */
struct BLEND_STATE {
	int					nBlendMode;								// �u�����h���[�h
	int					nBlendFactor;							// �u�����h�t�@�N�^
	int					nBrRed, nBrGreen, nBrBlue;				// �΁E�ԁE�̖��邳
};

extern int SetDrawMode(int nDrawMode, int nParam);
extern int DrawMem(int x, int y, int hPicture);
extern int DrawMemTh(int x, int y, int hPicture);

extern int HCls(void);	// ��ʃN���A
extern int Flip(void);	// ��ʍX�V����

/**
 * 2D���_�\����
 */
struct BOX_2DVERTEX {
	float	x, y, z, rhw;	// ���_���W
	DWORD	color;			// ���_�F
	float	tu, tv;			// �e�N�X�`�����W
};

/**
 * �_�f�[�^
 */
struct POINT_DATA {
	int				x, y, z;	// ���W
	unsigned int	nColor;		// �F
};

/**
 * 2D���_�\����
 */
struct POINTVERTEX {
	float	x, y, z, rhw;	// ���_���W
	int		color;			// ���_�F
};

/**
 * �����`�̕`��
 * @parme x1 �E��x���W
 * @parme y1 �E��y���W
 * @parme x2 ����x���W
 * @parme y2 ����y���W
 * @parme color �F�R�[�h
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color);


extern int gFpsCount;

extern void fps();
extern void wait_fanc();

#endif
