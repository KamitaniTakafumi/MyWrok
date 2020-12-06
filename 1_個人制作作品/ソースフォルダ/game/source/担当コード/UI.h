#pragma once
#include "appframe.h"

namespace act {
	class UI {
	public:
		/**
		 * UI�R���X�g���N�^
		 */
		UI();

		/**
		 * UI�f�X�g���N�^
		 */
		virtual ~UI() = default;

		/**
		 * UI������
		 */
		void Initialize();

		/**
		 * UI�`��
		 */
		void Draw(int PlayerLife);
	private:
		int _GhPlayerLife;	// �O���t�B�b�N�n���h��(�v���C���[�̗�)
		int _PlayerLife;	// �v���C���[�̗�
	};
}

