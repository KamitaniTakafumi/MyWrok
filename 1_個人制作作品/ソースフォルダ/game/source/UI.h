#pragma once
#include "appframe.h"

namespace act {
	class UI {
	public:
		/**
		 * UIコンストラクタ
		 */
		UI();

		/**
		 * UIデストラクタ
		 */
		virtual ~UI() = default;

		/**
		 * UI初期化
		 */
		void Initialize();

		/**
		 * UI描画
		 */
		void Draw(int PlayerLife);
	private:
		int _GhPlayerLife;	// グラフィックハンドル(プレイヤー体力)
		int _PlayerLife;	// プレイヤー体力
	};
}

