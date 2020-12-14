/**
 * @file ModeGame.h
 * @brief �C���Q�[������
 * @author ��J���j
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
		 * �C���Q�[��������
		 */
		virtual bool Initialize();

		/**
		 * �C���Q�[���J��
		 */
		virtual bool Terminate();

		/**
		 * �C���Q�[������
		 */
		virtual bool Process();

		/**
		 * �C���Q�[���`��
		 */
		virtual bool Render();
	private:
	protected:
		int _bg;	// �w�i
	};
}
