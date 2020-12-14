/**
 * @file ApplicationMain.h
 * @brief �A�v���P�[�V��������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "appframe.h"

namespace act {
	class ApplicationMain : public ApplicationBase {
		typedef ApplicationBase base;
	public:
		/**
		 * �N����������
		 * @param hInstance �C���X�^���X�n���h��
		 */
		virtual bool Initialize(HINSTANCE hInstance);

		/**
		 * ���
		 * @return ���Ȃ����true
		 */
		virtual bool Terminate();

		/**
		 * �L�[����
		 * @return ���Ȃ����true
		 */
		virtual bool Input();

		/**
		 * �t���[������
		 * @return ���Ȃ����true
		 */
		virtual bool Process();

		/**
		 * �`��
		 * @return ���Ȃ����true
		 */
		virtual bool Render();

		/**
		 * �A�v���P�[�V�����E�B���h�E
		 * @return ���Ȃ����true
		 */
		virtual bool AppWindowed() { return true; }

		/**
		 * �E�B���h�E�T�C�Y(����)
		 * @return 1280
		 */
		virtual int DispSizeW() { return 1280; }

		/**
		 * �E�B���h�E�T�C�Y(����)
		 * @return 720
		 */
		virtual int DispSizeH() { return 720; }

	protected:

	};
}
