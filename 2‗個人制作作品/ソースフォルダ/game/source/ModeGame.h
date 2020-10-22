/**
 * @file ModeGame.h
 * @brief �C���Q�[������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"
#include "Control.h"
#include "ModeGameover.h"
#include "Fade.h"

namespace act {
	class ModeGame : public ModeBase
	{
		typedef ModeBase base;
	private:
		std::unique_ptr<Control> chara;
		std::unique_ptr<Fade> fade;
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
