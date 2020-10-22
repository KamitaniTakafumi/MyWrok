#include "Fade.h"

namespace act {
	Fade::Fade()
	{
		
	}

	void Fade::Initialize()
	{
		_FadeIn = 255;
		_FadeOut = 0;
	}

	void Fade::FadeIn()
	{
		SetDrawMode(DRAW_ALPHABLEND, _FadeIn);
		DrawFBox(0, 0,
			1280, 720,
			GetColor(NULL, 0, 0, 0));
		if (_FadeIn > 0)
		{
			_FadeIn -= 5;
		}

	}

	void Fade::FadeOut()
	{
		SetDrawMode(DRAW_ALPHABLEND, _FadeOut);
		DrawFBox(0, 0,
			1280, 720,
			GetColor(NULL, 0, 0, 0));
		if (_FadeOut < 255)
		{
			_FadeOut += 5;
		}

	}
	bool Fade::FadeInFlag()
	{
		if (_FadeIn <= 0) {
			return true;
		}
		return false;
	}
	bool Fade::FadeOutFlag()
	{
		if (_FadeOut >= 255) {
			return true;
		}
		return false;
	}
}