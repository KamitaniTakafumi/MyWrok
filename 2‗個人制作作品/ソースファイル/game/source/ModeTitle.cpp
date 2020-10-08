
#include "appframe.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = LoadTexture("res/title.png");				// ※１
	_start = LoadTexture("res/start.png");			// ※１
	_startpad = LoadTexture("res/startpad.png");	// ※１

	_starttime = timeGetTime();				// 開始時間を得る ※１

	return true;
}

bool ModeTitle::Terminate() {
	base::Terminate();

	Release2DGraphs();		// ※１

	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if(KeyJudg(trg, KEYIN_RET) || PadJudg(trg, KEYIN_Z))	// ※１
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
		// 次のモードを登録
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();

	// ※１ ここから
	int t = timeGetTime();			// 現在の経過時間を取得
	_stocktime = t - _starttime;	// モードが始まってからの経過時間を得る

	DrawMem(0, 0, _cg);

	if ((_stocktime % 1000) < 500)	// 0.5秒に1回点滅させる
	{
		if (gJoyPadNum != 0)		// パッドが接続されているかによって表示する画像を変える
		{
			DrawMemTh(0, 0, _startpad);
		}
		else
		{
			DrawMemTh(0, 0, _start);
		}
	}
	// ※１ ここまで

	return true;
}

