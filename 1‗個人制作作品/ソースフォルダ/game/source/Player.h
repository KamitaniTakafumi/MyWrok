/**
 * @file Player.h
 * @brief ����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"

namespace act {
	class Player
	{
	public:
		/**
		 * Player�R���X�g���N�^
		 */
		Player();

		/**
		 * Player�f�X�g���N�^
		 */
		virtual ~Player();

		/**
		 * �v���C���[������
		 */
		bool Initialize();

		/**
		 * �Q�b�^�[(x���W)
		 * @return x���W
		 */
		int GetPosX() { return _x; }

		/**
		 * �Q�b�^�[(y���W)
		 * @return y���W
		 */
		int GetPosY() { return _y; }

		/**
		 * �Q�b�^�[(�̗�)
		 * @return �̗�
		 */
		int GetHP() { return _life; }

		/**
		 * �����蔻��p��x���W�擾
		 * @return x���W
		 */
		int GetCollPosX() { return _x + (_width / 2) - PLAYER_COLLISION; }

		/**
		 * �����蔻��p��y���W�擾
		 * @return y���W
		 */
		int GetCollPosY() { return _y + (_height / 2); }

		/**
		 * �Z�b�^�[(x���W)
		 * @param x x���W
		 * @return x���W
		 */
		int SetPosX(int x) { return _x = x; }

		/**
		 * �Z�b�^�[(y���W)
		 * @param y y���W
		 * @return y���W
		 */
		int SetPosY(int y) { return _y = y; }

		/**
		 * �Z�b�^�[(�̗�)
		 * @return �̗�-1
		 */
		int SetHP() { return _life--; }

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

		/**
		 * �L�����̌���
		 */
		enum PlayerState
		{
			LOOK_RIGHT,
			LOOK_LEFT,
		};

		int _x, _y;				// x���W,y���W
		int _ghplayer[12];		// �O���t�B�b�N�n���h���i�[�p�z��i�v���C���[�j
		int _ghhp;				// �O���t�B�b�N�n���h���i�q�b�g�|�C���g�j
		int _suffix;			// �Y�����ԍ�
		int _width, _height;	// �摜��
		int _life;				// �����Ă邩�ǂ����̃t���O
		int _charastate;		// �L�����̏��
	};
}
