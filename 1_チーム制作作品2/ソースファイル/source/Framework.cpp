/*
 * @file Framework.cpp
 * @brief �t���[�����[�N����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include	"library.h"
#include	"Framework.h"
#include	"time.h"
#include	"SceneMain.h"

struct Framework frm;	// �t���[�����[�N���

/*
*  @brief �t���[�����[�N������
*  @param InitFPSMode FPS���[�h
*/
void InitFramework(int InitFPSMode)
{
	frm.FPSMode = InitFPSMode;

	frm.dwGameFrame = 0;

	frm.dwFrameTime = clock();
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/
int UpdateFramework()
{
	static unsigned long dwSec = 0;
	unsigned long CurrentTime = clock() * 10;

	//	�t���[������
	if (CurrentTime < frm.dwFrameTime + 167) return false;

	//	�o�ߎ���
	unsigned long dTime = CurrentTime - frm.dwFrameTime;
	if (dTime > 2000) frm.dwFrameTime = CurrentTime;

	//	�X�L�b�v�^�C�v 
	switch (frm.FPSMode) {
	case FPS_60:	frm.bRender = TRUE;	break;
	case FPS_30:	if (frm.dwGameFrame & 0x01) frm.bRender = TRUE; else frm.bRender = FALSE;
		break;
	case FPS_FLEX:	if (dTime > 167 * 2) frm.bRender = FALSE; else frm.bRender = TRUE;
		break;
	}

	//	�t���[�����ԍX�V
	if (GetKeyState(VK_LCONTROL) < 0) frm.dwFrameTime += 300;
	frm.dwFrameTime += 167;

	//	�b�ԃt���[�����ۑ�
	if (dwSec < CurrentTime) {
		frm.dwFPS = frm.dwCurFrame;
		frm.dwRenderFPS = frm.dwRCurFrame;
		frm.dwCurFrame = frm.dwRCurFrame = 0;
		dwSec += 10000;
	}
	frm.dwCurFrame++;	//	�t���[�����X�V
	frm.dwGameFrame++;	//	�Q�[���t���[�����X�V

	return true;
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/
void RenderFramework()
{
	if (!frm.bRender) return;
	//	�V�[���J�n
	BeginScene();
	//	�V�[���`��
	SceneRender();

	//	�t���[���\��
#ifdef _DEBUG
	DrawString(10, 10, GetColor(255, 255, 255, 0), "FPS %03d / %03d\n", frm.dwFPS, frm.dwRenderFPS);
#endif

	// �V�[���I��
	EndScene();

	frm.dwRCurFrame++;	//	�`��t���[�����X�V
}
