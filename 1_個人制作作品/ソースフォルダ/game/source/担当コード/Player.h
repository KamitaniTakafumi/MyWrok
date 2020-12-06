/**
 * @file Player.h
 * @brief ����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"

namespace act {
	class Player {
	public:
		/**
		 * Player�R���X�g���N�^
		 */
		Player();

		/**
		 * Player�f�X�g���N�^
		 */
		virtual ~Player() = default;

		/**
		 * �v���C���[������
		 */
		void Initialize();

		/**
		 * �Q�b�^�[(x���W)
		 * @return x���W
		 */
		int GetPosX() { return _PlayerX; }

		/**
		 * �Q�b�^�[(y���W)
		 * @return y���W
		 */
		int GetPosY() { return _PlayerY; }

		/**
		 * �Q�b�^�[(�̗�)
		 * @return �̗�
		 */
		int GetHP() { return _Life; }

		/**
		 * �����蔻��p��x���W�擾
		 * @return x���W
		 */
		int GetCollPosX() { return _PlayerX + (_PlayerWidth / 2) - PLAYER_COLLISION; }

		/**
		 * �����蔻��p��y���W�擾
		 * @return y���W
		 */
		int GetCollPosY() { return _PlayerY + (_PlayerHeight / 2); }

		/**
		 * �Z�b�^�[(x���W)
		 * @param x x���W
		 * @return x���W
		 */
		int SetPosX(int x) { return _PlayerX = x; }

		/**
		 * �Z�b�^�[(y���W)
		 * @param y y���W
		 * @return y���W
		 */
		int SetPosY(int y) { return _PlayerY = y; }

		/**
		 * �Z�b�^�[(�̗�)
		 * @return �̗�-1
		 */
		int SetHP() { return _Life--; }

		/**
		 * �ړ�����
		 * @param key �������u�Ԃ̔���
		 * @param trg ��������ςȂ��̔���
		 */
		void Move(int key, int trg);

		/**
		 * �`�揈��
		 */
		void Draw();
	private:
		 // �L�����̌���
		enum PlayerState {
			LOOK_RIGHT,
			LOOK_LEFT,
		};

		int _PlayerX, _PlayerY;				// x���W,y���W
		int _GhPlayer[12];					// �O���t�B�b�N�n���h���i�[�p�z��i�v���C���[�j
		int _Subscript;						// �Y�����ԍ�
		int _PlayerWidth, _PlayerHeight;	// �摜��
		int _Life;							// �����Ă邩�ǂ����̃t���O
		int _CharaState;					// �L�����̏��
	};
}
