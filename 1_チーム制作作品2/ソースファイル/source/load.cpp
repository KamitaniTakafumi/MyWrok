/*
 * @file load.cpp
 * @brief ���[�h����
 * @author ��J���j
 * @date 2020 / 02 / 27
 */

#include "library.h"
#include "game.h"
#include "Texture.h"
#include "Framework.h"
#include "dslib.h"
#include "SceneMain.h"
#include "title.h"
#include "result.h"
#include "pose.h"
#include "player.h"
#include "Fade.h"

KT_2DPIC_INFO load, teamlogo;				// �摜���
static int gFrame1;							// �������؂�ւ�
static int gLoadSecond;						// ���[�h����
static int gFadeFlag;						// �t�F�[�h�؂�ւ�
static int gTimeStock, gTimeStock2;			// ���Ԃ̕ۑ�
static int gLoadFlag;						// ���[�h�؂�ւ�
static int gWaitTime;						// �҂�����

/*
 * ������
 */
void InitLoad()
{
	gFrame1 = 0;
	gLoadSecond = 5000;
	gFadeFlag = 0;
	gTimeStock = 0;
	gTimeStock2 = 0;
	gLoadFlag = 0;
	gWaitTime = 60;
	gGameMode.Mode = GAME_LOAD;
	gGameMode.OutMode = GAME_LOAD;
	load = CreateTexture("res/load/loading.png");
	teamlogo = CreateTexture("res/load/team_logo.png");
	CreateSprit();
}

/*
 * �X�V
 */
void Load()
{
	if (gWaitTime >= 0)
	{
		gWaitTime--;
	}
	else
	{
		if (gGameMode.OutMode == GAME_LOAD)
		{
			if (gLoadFlag == 0)
			{
				if (gFadeFlag == 0)
				{
					if (FadeInFlag() == true)
					{
						gFadeFlag = 1;
						gTimeStock = GetTickCount();
					}
				}

				if (gFadeFlag == 1)
				{
					while (true)
					{
						if (gFrame1 < 4)
						{
							if (gFrame1 == 0)
							{
								InitSound();					// �T�E���h������
							}
							else if (gFrame1 == 1)
							{
								InitTitle();					// �^�C�g��������
							}
							else if (gFrame1 == 2)
							{
								InitPose();						// �|�[�Y������
								ReadTexture();		// �e�N�X�`��

							}
							else if (gFrame1 == 3)
							{
								ReadTexture();		// �e�N�X�`��
							}
							gFrame1++;
						}

						gTimeStock2 = GetTickCount() - gTimeStock;
						if (gTimeStock2 > gLoadSecond)
						{
							gFadeFlag = 2;
							break;
						}

					}
				}

				if (gFadeFlag == 2)
				{
					if (FadeOutFlag() == true)
					{
						gFadeFlag = 0;
						gLoadFlag = 1;
						InitFade();
						gWaitTime = 60;
					}
				}
			}
			else
			{
				if (gFadeFlag == 0)
				{
					if (FadeInFlag() == true)
					{
						gFadeFlag = 1;
						gTimeStock = GetTickCount();
					}
				}

				if (gFadeFlag == 1)
				{
					while (true)
					{
						if (gFrame1 < 5)
						{
							if (gFrame1 == 0)
							{
								InitSound();					// �T�E���h������
							}
							else if (gFrame1 == 1)
							{
								InitTitle();					// �^�C�g��������
							}
							else if (gFrame1 == 2)
							{
								InitPose();						// �|�[�Y������
							}
							else if (gFrame1 == 3)
							{
								ReadTexture();					// �e�N�X�`��
							}
							else if (gFrame1 == 4)
							{
								InitPlayer();					// �v���C���[
								gGameMode.Mode = GAME_TITLE;	// �Q�[�����[�h���^�C�g���ɂ���
							}
							gFrame1++;
						}
						gTimeStock2 = GetTickCount() - gTimeStock;
						if (gTimeStock2 > gLoadSecond)
						{
							gFadeFlag = 2;
							break;
						}

					}
				}

				if (gFadeFlag == 2)
				{
					if (FadeOutFlag() == true)
					{
						gFadeFlag = 0;
						gLoadFlag = 1;
						InitFade();
						gWaitTime = 60;
					}
				}
			}

			if (gFrame1 == 5)
			{
				gFrame1 = 0;
				gFadeFlag = 0;
				gLoadFlag = 1;
				InitFade();
				gWaitTime = 60;
				// �ȃf�[�^���t�J�n
				DSoundPlay(sndTitle, TRUE);

			}
		}
		else if (gGameMode.OutMode == GAME_TITLE)
		{
			if (gFadeFlag == 0)
			{
				if (FadeInFlag() == true)
				{
					gFadeFlag = 1;
					gTimeStock = GetTickCount();
				}
			}

			if (gFadeFlag == 1)
			{
				while (true)
				{
					if (gFrame1 < 1)
					{
						if (gFrame1 == 0)
						{
							InitGame();						// ���C���Q�[��������
						}
						gFrame1++;
					}

					gTimeStock2 = GetTickCount() - gTimeStock;
					if (gTimeStock2 > gLoadSecond)
					{
						gFadeFlag = 2;
						break;
					}
				}

			}

			if (gFadeFlag == 2)
			{
				if (FadeOutFlag() == true)
				{
					gFadeFlag = 0;
					gLoadFlag = 1;
					InitFade();
					gWaitTime = 60;
				}
			}

			if (gFrame1 == 1)
			{
				gFrame1 = 0;
				gFadeFlag = 0;
				gLoadFlag = 1;
				InitFade();
				gWaitTime = 60;
				// �ȃf�[�^���t�J�n
				DSoundPlay(sndBgm, TRUE);

			}
		}
	}
}

/*
 * ���[�h��ʕ`��
 */
void DrawLoad()
{
	BeginScene();
	if (gLoadFlag == 0)
	{
		DrawTexture(0, 0, &teamlogo, teamlogo.texture, DRAW_NOBLEND);	// �摜�`��(�`�[�����S)
	}
	else
	{
		DrawTexture(0, 0, &load, load.texture, DRAW_NOBLEND);	// �摜�`��(���[�h)
	}

	if (gFadeFlag == 0)
	{
		WhiteFadeIn();	// �t�F�[�h�C��
	}
	else if (gFadeFlag == 2)
	{
		WhiteFadeOut();	// �t�F�[�h�A�E�g
	}
	EndScene();
	frm.dwRCurFrame++;	//	�`��t���[�����X�V
}
