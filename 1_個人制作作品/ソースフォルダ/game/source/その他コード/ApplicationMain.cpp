/**
 * @file ApplicationMain.cpp
 * @brief アプリケーション処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"

namespace act {
	// 実体
	ApplicationMain				g_oApplicationMain;

	/**
	 * 起動時初期化
	 * @param hInstance インスタンスハンドル
	 */
	bool ApplicationMain::Initialize(HINSTANCE hInstance) {
		if (!base::Initialize(hInstance)) { return false; }

		// モードの登録
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");

		return true;
	}

	/**
	 * 解放
	 * @return 問題なければtrue
	 */
	bool ApplicationMain::Terminate() {
		base::Terminate();
		return true;
	}

	/**
	 * キー入力
	 * @return 問題なければtrue
	 */
	bool ApplicationMain::Input() {
		base::Input();
		return true;
	}

	/**
	 * フレーム処理
	 * @return 問題なければtrue
	 */
	bool ApplicationMain::Process() {
		base::Process();
		return true;
	}

	/**
	 * 描画
	 * @return 問題なければtrue
	 */
	bool ApplicationMain::Render() {
		base::Render();
		return true;
	}
}
