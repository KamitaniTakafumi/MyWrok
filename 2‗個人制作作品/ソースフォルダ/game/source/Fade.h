#pragma once
#include "appframe.h"

namespace act {
	class Fade {
	public:
		/**
		 * フェードコンストラクタ
		 */
		Fade();

		/**
		 * フェードデストラクタ
		 */
		virtual ~Fade() = default;

		/**
		 * フェード初期化
		 */
		void Initialize();

		/**
		 * フェードイン処理
		 */
		void FadeIn();

		/**
		 * フェードアウト処理
		 */
		void FadeOut();

		/**
		 * フェードインフラグ処理
		 */
		bool FadeInFlag();

		/**
		 * フェードアウトフラグ処理
		 */
		bool FadeOutFlag();
	private:
		int _FadeIn;	// フェードイン値
		int _FadeOut;	// フェードアウト値
	};
}
