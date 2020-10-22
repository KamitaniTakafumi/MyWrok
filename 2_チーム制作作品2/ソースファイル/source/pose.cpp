/*
 * @file pose.cpp
 * @brief ƒ|[ƒYˆ—
 * @author ã’J‹±Žj
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

int gPoseSelectNumber;					// ƒZƒŒƒNƒg

/*
 * ‰Šú‰»
 */
void InitPose()
{
	gPoseSelectNumber = 0;
}

/*
 * XV
 */
int PoseMenu()
{
	// ƒZƒŒƒNƒg‚ðˆÚ“®
	if (gTrg1 & KEYIN_RIGHT)
	{
		gPoseSelectNumber++;
	}
	if (gTrg1 & KEYIN_LEFT)
	{
		gPoseSelectNumber--;
	}
	// ƒZƒŒƒNƒg‚Ìƒ‹[ƒv
	if (gPoseSelectNumber >= 2)
	{
		gPoseSelectNumber = 0;
	}
	if (gPoseSelectNumber < 0)
	{
		gPoseSelectNumber = 1;
	}
	// ƒQ[ƒ€‰æ–Ê‚É–ß‚é
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
 * •`‰æ
 */
void DrawPose()
{
	int i = 0, j = 0;

	BeginScene();
	// ”wŒi•`‰æ
	DrawOutGame(0, 0, POSE);			// ƒ^ƒCƒgƒ‹”wŒi
	// ‘I‘ð•`‰æ
	if (gPoseSelectNumber == 0)
	{
		j = j - 50;
	}
	else if (gPoseSelectNumber == 1)
	{
		i = i - 50;
	}
	DrawOutGame(200, 360 - i, BACK);			// ƒ^ƒCƒgƒ‹”wŒi
	DrawOutGame(660, 360 - j, TITLEBACK);			// ƒ^ƒCƒgƒ‹”wŒi

	EndScene();
	frm.dwRCurFrame++;	//	•`‰æƒtƒŒ[ƒ€”XV
}
