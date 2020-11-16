/**
 * @file ModeGame.cpp
 * @brief インゲーム処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeGame.h"

namespace act {
	/**
	 * インゲーム初期化
	 */
	bool ModeGame::Initialize() {
		if (!base::Initialize()) { return false; }

		chara = std::make_unique<Control>();
		chara->Initialize();

		fade = std::make_unique<Fade>();
		fade->Initialize();

		_bg = LoadTexture("res/stage.png");
		return true;
	}

	/**
	 * インゲーム開放
	 */
	bool ModeGame::Terminate() {
		base::Terminate();

		Release2DGraphs();	// テクスチャ開放

		return true;
	}

	/**
	 * インゲーム処理
	 */
	bool ModeGame::Process() {
		base::Process();
		int key = ApplicationMain::GetInstance()->GetKey();
		int trg = ApplicationMain::GetInstance()->GetTrg();
		
		// プレイヤーの体力が0ならゲームオーバー
		if (chara->CheckPlayerHP() == true)
		{
			if (fade->FadeOutFlag() == true)
			{
				// このモードを削除予約
				ModeServer::GetInstance()->Del(this);
				// 次のモードを登録
				ModeServer::GetInstance()->Add(new ModeGameover(), 1, "gameover");
			}
			return true;
		}
		chara->Move(key, trg);	// 移動処理
		chara->CollisionAll();	// 当たり判定

		return true;
	}

	/**
	 * インゲーム描画
	 */
	bool ModeGame::Render() {
		base::Render();
		DrawMem(0, 0, _bg);	// 背景描画
		chara->Draw();		// キャラ描画
		if (chara->CheckPlayerHP() == true) {
			fade->FadeOut();
		}

		return true;
	}
}

