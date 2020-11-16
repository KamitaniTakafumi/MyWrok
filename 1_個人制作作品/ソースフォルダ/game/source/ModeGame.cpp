/**
 * @file ModeGame.cpp
 * @brief �C���Q�[������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "ApplicationMain.h"
#include "ModeGame.h"

namespace act {
	/**
	 * �C���Q�[��������
	 */
	bool ModeGame::Initialize() {
		if (!base::Initialize()) { return false; }

		chara = std::make_unique<Control>();
		chara->Initialize();

		fade = std::make_unique<Fade>();
		fade->Initialize();

		_bg = LoadTexture("res/stage.png");
		return true;
	}

	/**
	 * �C���Q�[���J��
	 */
	bool ModeGame::Terminate() {
		base::Terminate();

		Release2DGraphs();	// �e�N�X�`���J��

		return true;
	}

	/**
	 * �C���Q�[������
	 */
	bool ModeGame::Process() {
		base::Process();
		int key = ApplicationMain::GetInstance()->GetKey();
		int trg = ApplicationMain::GetInstance()->GetTrg();
		
		// �v���C���[�̗̑͂�0�Ȃ�Q�[���I�[�o�[
		if (chara->CheckPlayerHP() == true)
		{
			if (fade->FadeOutFlag() == true)
			{
				// ���̃��[�h���폜�\��
				ModeServer::GetInstance()->Del(this);
				// ���̃��[�h��o�^
				ModeServer::GetInstance()->Add(new ModeGameover(), 1, "gameover");
			}
			return true;
		}
		chara->Move(key, trg);	// �ړ�����
		chara->CollisionAll();	// �����蔻��

		return true;
	}

	/**
	 * �C���Q�[���`��
	 */
	bool ModeGame::Render() {
		base::Render();
		DrawMem(0, 0, _bg);	// �w�i�`��
		chara->Draw();		// �L�����`��
		if (chara->CheckPlayerHP() == true) {
			fade->FadeOut();
		}

		return true;
	}
}

