#include "Fade.h"

namespace act {
	/**
	 * フェードコンストラクタ
	 */
	Fade::Fade() :
		_FadeIn(0),
		_FadeOut(0) {
	}

	/**
	 * フェード初期化
	 */
	void Fade::Initialize() {
		_FadeIn = 255;
		_FadeOut = 0;
	}

	/**
	 * フェードイン処理
	 */
	void Fade::FadeIn() {
		SetDrawMode(DRAW_ALPHABLEND, _FadeIn);
		DrawFBox(0, 0,
			1280, 720,
			GetColor(NULL, 0, 0, 0));
		if (_FadeIn > 0) {
			_FadeIn -= 5;
		}

	}

	/**
	 * フェードアウト処理
	 */
	void Fade::FadeOut() {
		SetDrawMode(DRAW_ALPHABLEND, _FadeOut);
		DrawFBox(0, 0,
			1280, 720,
			GetColor(NULL, 0, 0, 0));
		if (_FadeOut < 255) {
			_FadeOut += 5;
		}

	}

	/**
	 * フェードインフラグ処理
	 */
	bool Fade::FadeInFlag() {
		if (_FadeIn <= 0) {
			return true;
		}
		return false;
	}

	/**
	 * フェードアウトフラグ処理
	 */
	bool Fade::FadeOutFlag() {
		if (_FadeOut >= 255) {
			return true;
		}
		return false;
	}
}