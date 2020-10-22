/*
 * @file result.cpp
 * @brief ���U���g����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "dslib.h"
#include "Framework.h"
#include "player.h"
#include "SceneMain.h"
#include "Texture.h"

int gResultPoint[4];	// �����_��

/*
 * �X�V
 */
int UpdateResult()
{
	if (gTrg1 & KEYIN_Z)
	{
		gGameMode.Mode = GAME_TITLE;
		DSoundStop(sndResult);

		// �ȃf�[�^���t�J�n
		DSoundPlay(sndTitle, TRUE);

		ReleaseStage();				// �X�e�[�W�̃����[�X

		return GAME_TITLE;
	}

	return GAME_RESULT;
}

/*
 * �`��
 */
void DrawResult()
{
	int i;
	BeginScene();
	DrawOutGame(0, 0, RESULT);// �w�i�`��
	// �����_���`��
	for (i = 0; i < gJoyPadNum; i++)
	{
		DrawPoint(i, gResultPoint[i], GAME_RESULT);
	}

	EndScene();
	frm.dwRCurFrame++;	//	�`��t���[�����X�V
}
