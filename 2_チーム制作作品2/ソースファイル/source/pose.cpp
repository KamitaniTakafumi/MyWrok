/*
 * @file pose.cpp
 * @brief �|�[�Y����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "SceneMain.h"
#include "Framework.h"
#include "player.h"
#include "object.h"
#include "Texture.h"
#include "title.h"

int gPoseSelectNumber;					// �Z���N�g

/*
 * ������
 */
void InitPose()
{
	gPoseSelectNumber = 0;
}

/*
 * �X�V
 */
int PoseMenu()
{
	// �Z���N�g���ړ�
	if (gTrg1 & KEYIN_RIGHT)
	{
		gPoseSelectNumber++;
	}
	if (gTrg1 & KEYIN_LEFT)
	{
		gPoseSelectNumber--;
	}
	// �Z���N�g�̃��[�v
	if (gPoseSelectNumber >= 2)
	{
		gPoseSelectNumber = 0;
	}
	if (gPoseSelectNumber < 0)
	{
		gPoseSelectNumber = 1;
	}
	// �Q�[����ʂɖ߂�
	if ((gTrg1 & KEYIN_Z) && gPoseSelectNumber == 0)
	{
		gGameMode.Mode = GAME_IN;
		gPoseSelectNumber = 0;

		return GAME_IN;
	}
	if ((gTrg1 & KEYIN_Z) && gPoseSelectNumber == 1)
	{
		ResetGame(GAME_TITLE);
		gPoseSelectNumber = 0;

		return GAME_TITLE;
	}

	return GAME_POSE;
}

/*
 * �`��
 */
void DrawPose()
{
	int i = 0, j = 0;

	BeginScene();
	// �w�i�`��
	DrawOutGame(0, 0, POSE);			// �^�C�g���w�i
	// �I��`��
	if (gPoseSelectNumber == 0)
	{
		j = j - 50;
	}
	else if (gPoseSelectNumber == 1)
	{
		i = i - 50;
	}
	DrawOutGame(200, 360 - i, BACK);			// �^�C�g���w�i
	DrawOutGame(660, 360 - j, TITLEBACK);			// �^�C�g���w�i

	EndScene();
	frm.dwRCurFrame++;	//	�`��t���[�����X�V
}
