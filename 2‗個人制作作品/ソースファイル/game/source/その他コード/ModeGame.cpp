
#include "appframe.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameover.h"
#include "Control.h"

Control* chara;		// ¦‚P

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	chara = new Control;		// ¦‚P
	_bg = LoadTexture("res/stage.png");		// ¦‚P
	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	delete chara;		// ¦‚P
	Release2DGraphs();	// ¦‚P

	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	if (chara->CheckPlayerHP() == true)		// ¦‚P
	{
		// ‚±‚Ìƒ‚[ƒh‚ğíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// Ÿ‚Ìƒ‚[ƒh‚ğ“o˜^
		ModeServer::GetInstance()->Add(new ModeGameover(), 1, "gameover");
		return true;
	}
	chara->Move(key, trg);		// ¦‚P
	chara->CollisionAll();		// ¦‚P

	return true;
}

bool ModeGame::Render() {
	base::Render();
	DrawMem(0, 0, _bg);		// ¦‚P
	chara->Draw();			// ¦‚P

	return true;
}

