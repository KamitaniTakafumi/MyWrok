#pragma once
/*
 * @file Framework.cpp
 * @brief �t���[�����[�N����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include	"library.h"
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#define	FPS_60		0	//	�Œ�U�O�t���[��
#define	FPS_30		1	//	�Œ�R�O�t���[��
#define	FPS_FLEX	2	//	�σt���[��

/*------------------------------------------------
*  �t���[�����[�N�\����
------------------------------------------------*/
struct Framework
{
	int bRender;
	unsigned char FPSMode;		//	�t���[�����䃂�[�h
	unsigned long dwGameFrame;	//	�N������̃t���[����
	unsigned long dwFrameTime;
	unsigned long dwFPS;			//	�����t���[�����[�g
	unsigned long dwRenderFPS;	//	�`��t���[�����[�g
	unsigned long dwCurFrame;		//	�����J�E���^
	unsigned long dwRCurFrame;	//	�`��J�E���^
};

// �t���[�����[�N���
extern struct Framework frm;

/*
*  @brief �t���[�����[�N������
*  @param InitFPSMode FPS���[�h
*/
void InitFramework(int InitFPSMode);
// �t���[�����[�N�A�b�v�f�[�g
int UpdateFramework();
// �t���[�����[�N�`��
void RenderFramework();

#endif
