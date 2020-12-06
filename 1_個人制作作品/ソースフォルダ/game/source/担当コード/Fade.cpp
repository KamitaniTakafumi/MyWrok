#include "Fade.h"

namespace act {
	/**
	 * �t�F�[�h�R���X�g���N�^
	 */
	Fade::Fade() :
		_FadeIn(0),
		_FadeOut(0) {
	}

	/**
	 * �t�F�[�h������
	 */
	void Fade::Initialize() {
		_FadeIn = 255;
		_FadeOut = 0;
	}

	/**
	 * �t�F�[�h�C������
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
	 * �t�F�[�h�A�E�g����
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
	 * �t�F�[�h�C���t���O����
	 */
	bool Fade::FadeInFlag() {
		if (_FadeIn <= 0) {
			return true;
		}
		return false;
	}

	/**
	 * �t�F�[�h�A�E�g�t���O����
	 */
	bool Fade::FadeOutFlag() {
		if (_FadeOut >= 255) {
			return true;
		}
		return false;
	}
}