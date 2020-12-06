/**
 * @file ModeGameover.cpp
 * @brief ゲームオーバー処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeGameover.h"

namespace act {
	/**
	 * インゲーム初期化
	 */
	bool ModeGameover::Initialize() {
		if (!base::Initialize()) { return false; }

		_bg = LoadTexture("res/GameOver.png");			// 背景
		_start = LoadTexture("res/start.png");			// スタート画像(キーボード)
		_startpad = LoadTexture("res/startpad.png");	// スタート画像(パッド)

		return true;
	}

	/**
	 * インゲーム開放
	 */
	bool ModeGameover::Terminate() {
		base::Terminate();

		Release2DGraphs();		// テクスチャ開放

		return true;
	}

	/**
	 * インゲーム処理
	 */
	bool ModeGameover::Process() {
		base::Process();
		int key = ApplicationMain::GetInstance()->GetKey();
		int trg = ApplicationMain::GetInstance()->GetTrg();

		// キーボードのリターンキー、もしくはパッドのAボタンが押されたら処理
		if (KeyJudg(trg, KEYIN_RET) || PadJudg(trg, KEYIN_Z)) {
			// このモードを削除予約
			ModeServer::GetInstance()->Del(this);
			// 次のモードを登録
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
		}

		return true;
	}

	/**
	 * インゲーム描画
	 */
	bool ModeGameover::Render() {
		base::Render();

		DrawMemTh(0, 0, _bg);	// 背景描画

		// パッドが接続されているかによって表示する画像を変える
		if (gJoyPadNum != 0) {
			DrawMemTh(0, 0, _startpad);	// スタート画像描画(パッド)
		}
		else {
			DrawMemTh(0, 0, _start);	// スタート画像描画(キーボード)
		}
		return true;
	}
}
