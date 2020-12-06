/**
 * @file ModeGameover.cpp
 * @brief �Q�[���I�[�o�[����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeGameover.h"

namespace act {
	/**
	 * �C���Q�[��������
	 */
	bool ModeGameover::Initialize() {
		if (!base::Initialize()) { return false; }

		_bg = LoadTexture("res/GameOver.png");			// �w�i
		_start = LoadTexture("res/start.png");			// �X�^�[�g�摜(�L�[�{�[�h)
		_startpad = LoadTexture("res/startpad.png");	// �X�^�[�g�摜(�p�b�h)

		return true;
	}

	/**
	 * �C���Q�[���J��
	 */
	bool ModeGameover::Terminate() {
		base::Terminate();

		Release2DGraphs();		// �e�N�X�`���J��

		return true;
	}

	/**
	 * �C���Q�[������
	 */
	bool ModeGameover::Process() {
		base::Process();
		int key = ApplicationMain::GetInstance()->GetKey();
		int trg = ApplicationMain::GetInstance()->GetTrg();

		// �L�[�{�[�h�̃��^�[���L�[�A�������̓p�b�h��A�{�^���������ꂽ�珈��
		if (KeyJudg(trg, KEYIN_RET) || PadJudg(trg, KEYIN_Z)) {
			// ���̃��[�h���폜�\��
			ModeServer::GetInstance()->Del(this);
			// ���̃��[�h��o�^
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
		}

		return true;
	}

	/**
	 * �C���Q�[���`��
	 */
	bool ModeGameover::Render() {
		base::Render();

		DrawMemTh(0, 0, _bg);	// �w�i�`��

		// �p�b�h���ڑ�����Ă��邩�ɂ���ĕ\������摜��ς���
		if (gJoyPadNum != 0) {
			DrawMemTh(0, 0, _startpad);	// �X�^�[�g�摜�`��(�p�b�h)
		}
		else {
			DrawMemTh(0, 0, _start);	// �X�^�[�g�摜�`��(�L�[�{�[�h)
		}
		return true;
	}
}
