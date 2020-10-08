/*
 * @file dslib.cpp
 * @brief �T�E���h����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#ifndef __DSLIB_H__
#define	__DSLIB_H__

#define MAX_SE 9

extern int sndBgm;		// BGM
extern int sndTitle;	// �^�C�g��BGM
extern int sndResult;	// ���U���gBGM
extern int sndSe[MAX_SE];	// SE[MAX_SE]

/*
*  SE�̎��
*/
enum SE_TYPE
{
	ATTACK,
	CANCEL,
	CRAFT,
	DIE,
	DECISION,
	ROCK,
	SELECT,
	WOOD,
	PICK,
};

// ������
BOOL DSoundInit( HWND hWnd, LPGUID lpGuid );

// ���
BOOL DSoundRelease();

// �T�E���h�̏�����
void InitSound();

/*
*  @brief SE�X�^�[�g
*  @param type SE�̎��ʃ^�C�v
*/
void StartSE(int type);

// wav�t�@�C���̓ǂݍ���
enum {
	DSLF_FLG_DEFAULT = 0,
	DSLF_FLG_STATIC,
	DSLF_FLG_STREAM,
};
int DSoundLoadFile(
	LPSTR szFileName,		// �t�@�C���� or ���\�[�X
	int nChannel,			// �ǂݍ��݃`�����l���ԍ�(-1�ŋ󂢂Ă�`�����l���ɒǉ�)
	DWORD dwFlg				// �t���O DSLF_FLG_xxxx
);

// wav�t�@�C���̉��
BOOL DSoundReleaseChannel( int nChannel );

// �Đ�
BOOL DSoundPlay( int nChannel, BOOL bLoop );

// ��~
void DSoundStop( int nChannel );

// �{�����[���Z�b�g
BOOL DSoundSetVolume( int nChannel,int nVolume );

// �p���Z�b�g
BOOL DSoundSetPan( int nChannel, int nCmd );

// �Đ������H
BOOL DSoundIsStop( int nChannel );



#endif

