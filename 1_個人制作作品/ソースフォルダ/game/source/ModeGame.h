/**
 * @file ModeGame.h
 * @brief ƒCƒ“ƒQ[ƒ€ˆ—
 * @author ã’J‹±j
 * @date 2020 / 08 / 25
 */

#pragma once
#include "Control.h"
#include "Fade.h"
#include "UI.h"

namespace act {
	class ModeGame : public ModeBase {
		typedef ModeBase base;
	private:
		std::unique_ptr<Control> chara;
		std::unique_ptr<Fade> fade;
		std::unique_ptr<UI> ui;
	public:
		/**
		 * ƒCƒ“ƒQ[ƒ€‰Šú‰»
		 */
		virtual bool Initialize();

		/**
		 * ƒCƒ“ƒQ[ƒ€ŠJ•ú
		 */
		virtual bool Terminate();

		/**
		 * ƒCƒ“ƒQ[ƒ€ˆ—
		 */
		virtual bool Process();

		/**
		 * ƒCƒ“ƒQ[ƒ€•`‰æ
		 */
		virtual bool Render();
	private:
	protected:
		int _bg;	// ”wŒi
	};
}
