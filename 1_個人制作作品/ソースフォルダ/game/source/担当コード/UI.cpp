#include "UI.h"

namespace act {

	UI::UI() :
		_GhPlayerLife(0), _PlayerLife(0) {
	}

	void UI::Initialize() {
		_PlayerLife = 0;
		_GhPlayerLife = LoadTexture("res/heartP.png");
	}

	void UI::Draw(int PlayerLife) {
		int PLifeX = 0;
		// ƒ‰ƒCƒt•`‰æ
		for (int i = 0; i < PlayerLife; i++) {
			DrawMemTh(PLifeX, 0, _GhPlayerLife);
			PLifeX += 40;
		}
	}
}
