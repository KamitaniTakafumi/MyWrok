/*
 * @file game.cpp
 * @brief �Q�[������
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "Framework.h"
#include "dslib.h"
#include "SceneMain.h"
#include "title.h"
#include "result.h"
#include "pose.h"
#include "load.h"
#include "Fade.h"

GAMEMODE gGameMode;		// �Q�[�����[�h���

/*
 * ������
 */
void AppInit()
{
	InitFade();	// �t�F�[�h������
	InitLoad();	// ���[�h������
	InitFont();	// �t�H���g������
}

/*
 * �t���[�������F����
 */
void FrameInput()
{
	// �L�[�̓��́A�g���K���͂𓾂�
	InKey();
}

/*
 * �t���[�������F�v�Z
 */
void FrameProcess()
{
	// �Q�[���J��
	switch (gGameMode.Mode)
	{
	case GAME_LOAD:
		Load();
		break;
	case GAME_TITLE:
		SelectTitle();
		break;
	case GAME_IN:
		MainUpdate();
		break;
	case GAME_RESULT:
		UpdateResult();
		break;
	case GAME_POSE:
		PoseMenu();
		break;
	default:
		break;
	}
}

/*
 * �t���[�������F�`��
 */
void FrameDraw() 
{
	// �`��J��
	switch (gGameMode.Mode)
	{
	case GAME_LOAD:
		DrawLoad();
		break;
	case GAME_TITLE:
		DrawTitle();
		break;
	case GAME_IN:
		RenderFramework();
		break;
	case GAME_RESULT:
		DrawResult();
		break;
	case GAME_POSE:
		DrawPose();
		break;
	default:
		break;
	}
}

