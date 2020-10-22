/**
 * @file ApplicationMain.cpp
 * @brief �A�v���P�[�V��������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"

namespace act {
	// ����
	ApplicationMain				g_oApplicationMain;

	/**
	 * �N����������
	 * @param hInstance �C���X�^���X�n���h��
	 */
	bool ApplicationMain::Initialize(HINSTANCE hInstance) {
		if (!base::Initialize(hInstance)) { return false; }

		// ���[�h�̓o�^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");

		return true;
	}

	/**
	 * ���
	 * @return ���Ȃ����true
	 */
	bool ApplicationMain::Terminate() {
		base::Terminate();
		return true;
	}

	/**
	 * �L�[����
	 * @return ���Ȃ����true
	 */
	bool ApplicationMain::Input() {
		base::Input();
		return true;
	}

	/**
	 * �t���[������
	 * @return ���Ȃ����true
	 */
	bool ApplicationMain::Process() {
		base::Process();
		return true;
	}

	/**
	 * �`��
	 * @return ���Ȃ����true
	 */
	bool ApplicationMain::Render() {
		base::Render();
		return true;
	}
}
