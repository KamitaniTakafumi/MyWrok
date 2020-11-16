/**
 * @file ModeTitle.cpp
 * @brief タイトル処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"

namespace act {
	bool ModeTitle::Initialize() {
		if (!base::Initialize()) { return false; }

		_bg = LoadTexture("res/title.png");				// 背景
		_start = LoadTexture("res/start.png");			// スタート画像(キーボード)
		_startpad = LoadTexture("res/startpad.png");	// スタート画像(パッド)

		_starttime = timeGetTime();				// 開始時間を得る

		return true;
	}

	bool ModeTitle::Terminate() {
		base::Terminate();

		Release2DGraphs();		// テクスチャ開放

		return true;
	}

	bool ModeTitle::Process() {
		base::Process();
		int key = ApplicationMain::GetInstance()->GetKey();
		int trg = ApplicationMain::GetInstance()->GetTrg();

		// キーボードのリターンキー、もしくはパッドのAボタンが押されたら処理
		if (KeyJudg(trg, KEYIN_RET) || PadJudg(trg, KEYIN_Z))
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

		int t = timeGetTime();			// 現在の経過時間を取得
		_stocktime = t - _starttime;	// モードが始まってからの経過時間を得る

		DrawMem(0, 0, _bg);				// 背景描画

		// 0.5秒に1回点滅させる
		if ((_stocktime % 1000) < 500)
		{
			// パッドが接続されているかによって表示する画像を変える
			if (gJoyPadNum != 0)
			{
				DrawMemTh(0, 0, _startpad);	// スタート画像描画(パッド)
			}
			else
			{
				DrawMemTh(0, 0, _start);	// スタート画像描画(キーボード)
			}
		}

		return true;
	}
}
