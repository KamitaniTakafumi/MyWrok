/*
** WinMain
*/

//
// include ��
//

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "amgame.h"
#include "game.h"
#include "AmHelper.h"




//
// WinMain(). �v���O�����N���֐�
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	//
	// AM���C�u�����̏�����
	//

	SetGlobalMode( AMMODE_WINDOWED );	// ������R�����g�A�E�g����ƃt���X�N���[���œ���
	SetAMDebugMode(AMDEBUG_ALL_OFF);
	SetGraphMode( DISP_W, DISP_H, 32 );
	if ( !InitGraph( hInstance ) ) 
	{	// ���C�u�������������s
		return -1;
	}
	if (InitSound(0) < 0)
	{	// �T�E���h���������s
		EndGraph();
		return -1;
	}

	srand( (unsigned int)time( NULL ) );


	//
	// �v���O�����̏�����
	//

	AppInit();




	// �P�t���[�����[�v /////////////////////////////
	while( ProcessEvent() )
	{
		//
		// ����
		//

		FrameInput();


		//
		// �v�Z�E����
		//

		FrameProcess();


		//
		// �`��
		//

		FrameDraw();

	}

	//
	// �v���O�����̉��
	//

	AppRelease();


	//
	// AM���C�u�����̉��
	//

	EndGraph();

	return 0;
}
