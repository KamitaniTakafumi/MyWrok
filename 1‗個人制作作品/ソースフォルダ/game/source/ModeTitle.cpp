/**
 * @file ModeTitle.cpp
 * @brief �^�C�g������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeTitle.h"

namespace act {
	bool ModeTitle::Initialize() {
		if (!base::Initialize()) { return false; }

		_bg = LoadTexture("res/title.png");				// �w�i
		_start = LoadTexture("res/start.png");			// �X�^�[�g�摜(�L�[�{�[�h)
		_startpad = LoadTexture("res/startpad.png");	// �X�^�[�g�摜(�p�b�h)

		_starttime = timeGetTime();				// �J�n���Ԃ𓾂�

		return true;
	}

	bool ModeTitle::Terminate() {
		base::Terminate();

		Release2DGraphs();		// �e�N�X�`���J��

		return true;
	}

	bool ModeTitle::Process() {
		base::Process();
		int key = ApplicationMain::GetInstance()->GetKey();
		int trg = ApplicationMain::GetInstance()->GetTrg();

		// �L�[�{�[�h�̃��^�[���L�[�A�������̓p�b�h��A�{�^���������ꂽ�珈��
		if (KeyJudg(trg, KEYIN_RET) || PadJudg(trg, KEYIN_Z))
		{
			// ���̃��[�h���폜�\��
			ModeServer::GetInstance()->Del(this);
			// ���̃��[�h��o�^
			ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
		}

		return true;
	}

	bool ModeTitle::Render() {
		base::Render();

		int t = timeGetTime();			// ���݂̌o�ߎ��Ԃ��擾
		_stocktime = t - _starttime;	// ���[�h���n�܂��Ă���̌o�ߎ��Ԃ𓾂�

		DrawMem(0, 0, _bg);				// �w�i�`��

		// 0.5�b��1��_�ł�����
		if ((_stocktime % 1000) < 500)
		{
			// �p�b�h���ڑ�����Ă��邩�ɂ���ĕ\������摜��ς���
			if (gJoyPadNum != 0)
			{
				DrawMemTh(0, 0, _startpad);	// �X�^�[�g�摜�`��(�p�b�h)
			}
			else
			{
				DrawMemTh(0, 0, _start);	// �X�^�[�g�摜�`��(�L�[�{�[�h)
			}
		}

		return true;
	}
}
