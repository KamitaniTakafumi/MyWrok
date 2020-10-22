/**
 * @file ModeGameover.h
 * @brief �Q�[���I�[�o�[����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"
#include "ModeTitle.h"
#include "ModeGame.h"

namespace act {
	class ModeGameover : public ModeBase
	{
		typedef ModeBase base;
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

	protected:
		int _bg;			// �w�i
		int _start;			// �X�^�[�g�摜(�L�[�{�[�h)
		int _startpad;		// �X�^�[�g�摜(�p�b�h)
	};
}
