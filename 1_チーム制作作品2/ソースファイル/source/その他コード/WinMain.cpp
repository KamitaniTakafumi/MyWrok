/*
 * @file WinMain.cpp
 * @brief �G���g���[�|�C���g����
 * @author ��J���j
 * @date 2020/02/26
 */

#include "library.h"
#include "game.h"
#include "Framework.h"
#include "dslib.h"
#include "player.h"
#include "SceneMain.h"
#include "object.h"

/*
*  @brief WinMain
*  @param hInstance �C���X�^���X
*  @param hPrevInstance ���g�p(���NULL)
*  @param lpCmdLine �R�}���h���C������
*  @param nCmdShow �E�B���h�E�̕\�����@
*/
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	MSG		msg;	// ���b�Z�[�W

	// �p�b�h�̐ڑ��m�F
	ConnectionPad();

	// �E�C���h�E�쐬
	InitWnd(hInstance, DISP_W, DISP_H, "�O���X�g");

	// �_�C���N�g3D�̏������֐����Ă�
	if (!InitApp()) 
	{ 
		return false; 
	}

	// �Q�[���̏�����
	AppInit();

	//	���C�����[�v
	for (;;) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0)) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			if (UpdateFramework())
			{
				// ����
				FrameInput();

				// ����
				FrameProcess();

				// �`��
				FrameDraw();
			}
		}
	}

	//	�S���	
	ReleaseD3D();
	ReleaseFont();
	ReleasePlayer();
	ReleaseObject();
	DSoundRelease();

	return 0;
}
