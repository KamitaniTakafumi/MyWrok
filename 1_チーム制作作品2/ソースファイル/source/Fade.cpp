/*
 * @file Fade.cpp
 * @brief �t�F�[�h����
 * @author ��J���j
 * @date 2020 / 03 / 21
 */

#include "library.h"
#include "game.h"
#include "SceneMain.h"

int gFadeIn;			// �t�F�[�h�C��
int gFadeOut;		// �t�F�[�h�A�E�g

void InitFade()// �t�F�[�h������
{
	gFadeIn = 255;
	gFadeOut = 0;
}

// �t�F�[�h�C�����I�������
bool FadeInFlag()
{
	if (gFadeIn > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// �t�F�[�h�A�E�g���I�������
bool FadeOutFlag()
{
	if (gFadeOut < 255)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// �u���b�N�t�F�[�h�C��
void WhiteFadeIn()
{
	SetDrawMode(DRAW_ALPHABLEND, gFadeIn);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(NULL, 0, 0, 0));
	if (gFadeIn > 0)
	{
		gFadeIn -= 15;
	}

}

// �u���b�N�t�F�[�h�A�E�g
void WhiteFadeOut()
{
	SetDrawMode(DRAW_ALPHABLEND, gFadeOut);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(NULL, 0, 0, 0));
	if (gFadeOut < 255)
	{
		gFadeOut += 15;
	}

}
