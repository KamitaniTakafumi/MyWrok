/*
 * @file title.cpp
 * @brief �^�C�g������
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "dslib.h"
#include "Framework.h"
#include "player.h"
#include "Texture.h"

int gStartSelectNumber;	// �Z���N�g
int gStartStateNumber;	// ���

/*
 * �^�C�g��������
 */
void InitTitle()
{
	gStartSelectNumber = 0;
	gStartStateNumber = 0;
}

/*
 * �^�C�g���Z���N�g
 */
int SelectTitle()
{
	// �ŏ��̉��
	if (gStartStateNumber == 0)
	{
		if (gTrg1 & KEYIN_Z)
		{
			StartSE(DECISION);		// SE�Đ�
			gStartStateNumber = 1;
		}
	}
	// �I�����
	else if (gStartStateNumber == 1)
	{
		// �Z���N�g���ړ�
		if (gTrg1 & KEYIN_RIGHT)
		{
			StartSE(SELECT);		// SE�Đ�
			gStartSelectNumber++;
		}
		if (gTrg1 & KEYIN_LEFT)
		{
			StartSE(SELECT);		// SE�Đ�
			gStartSelectNumber--;
		}
		// �Z���N�g�̃��[�v
		if (gStartSelectNumber >= 2)
		{
			gStartSelectNumber = 0;
		}
		if (gStartSelectNumber < 0)
		{
			gStartSelectNumber = 1;
		}
		// �Q�[����ʂɈړ�
		if ((gTrg1 & KEYIN_Z) && gStartSelectNumber == 0)
		{
			StartSE(DECISION);		// SE�Đ�
			gGameMode.Mode = GAME_LOAD;
			gGameMode.OutMode = GAME_TITLE;
			DSoundStop(sndTitle);
			gStartSelectNumber = 0;
			gStartStateNumber = 0;

			return GAME_LOAD;
		}
		// �Q�[���I��
		else if ((gTrg1 & KEYIN_Z) && gStartSelectNumber == 1)
		{
			StartSE(DECISION);		// SE�Đ�
			exit((gTrg1 & KEYIN_Z));
		}
		if (gTrg1 & KEYIN_X)
		{
			StartSE(CANCEL);		// SE�Đ�
			gStartStateNumber = 0;
		}
	}

	return GAME_TITLE;
}

/*
 * �^�C�g���`��
 */
void DrawTitle()
{
	BeginScene();
	if (gStartStateNumber == 0)
	{
		DrawOutGame(0, 0, TITLE);			// �^�C�g���w�i
		DrawOutGame(420, 350, HAZIMERU);	// �Ŕ�(�n�߂�)
	}
	else if (gStartStateNumber == 1)
	{
		DrawOutGame(0, 0, LOBBY);			// �^�C�g���w�i
		// �ǂ��I��ł��邩
		if (gStartSelectNumber == 0)
		{
			DrawOutGame(120, 400 - 50, START);	// �Ŕ�(�v���C)
			DrawOutGame(750, 400, END);			// �Ŕ�(�I���)
		}
		else if (gStartSelectNumber == 1)
		{
			DrawOutGame(120, 400, START);		// �Ŕ�(�v���C)
			DrawOutGame(750, 400 - 50, END);	// �Ŕ�(�I���)
		}
	}
	EndScene();
	frm.dwRCurFrame++;	//	�`��t���[�����X�V
}