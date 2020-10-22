#pragma once
#include "appframe.h"

namespace act {
	class Fade {
	public:
		/**
		 * �t�F�[�h�R���X�g���N�^
		 */
		Fade();

		/**
		 * �t�F�[�h�f�X�g���N�^
		 */
		virtual ~Fade() = default;

		/**
		 * �t�F�[�h������
		 */
		void Initialize();

		/**
		 * �t�F�[�h�C������
		 */
		void FadeIn();

		/**
		 * �t�F�[�h�A�E�g����
		 */
		void FadeOut();

		/**
		 * �t�F�[�h�C���t���O����
		 */
		bool FadeInFlag();

		/**
		 * �t�F�[�h�A�E�g�t���O����
		 */
		bool FadeOutFlag();
	private:
		int _FadeIn;	// �t�F�[�h�C���l
		int _FadeOut;	// �t�F�[�h�A�E�g�l
	};
}
