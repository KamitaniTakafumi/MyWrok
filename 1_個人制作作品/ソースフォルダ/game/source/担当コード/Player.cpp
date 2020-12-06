/**
 * @file Player.cpp
 * @brief ����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "Player.h"
#include "Control.h"

namespace act {
	/**
	 * Player�R���X�g���N�^
	 */
	Player::Player() :
		_PlayerX(0), _PlayerY(0), _GhPlayer{ 0 }, _Subscript(0),
		_PlayerWidth(0), _PlayerHeight(0), _Life(0), _CharaState(0)	{
	}

	/**
	 * �v���C���[������
	 */
	void Player::Initialize() {
		_PlayerWidth = 80;
		_PlayerHeight = 80;
		_PlayerX = (WINDOW_WIDTH - _PlayerWidth) / 2;
		_PlayerY = WINDOW_HEIGHT - _PlayerHeight;
		_Subscript = 6;

		_Life = PLAYER_HP;

		//�摜�ǂݍ���
		LoadBlkTexture("res/sample01.png", 80, 80, 3, 4, 12, _GhPlayer);
		
		_CharaState = LOOK_RIGHT;
	}

	/**
	 * �ړ�����
	 * @param key �������u�Ԃ̔���
	 * @param trg ��������ςȂ��̔���
	 */
	void Player::Move(int key, int trg) {
		// �ړ�����
		if (KeyJudg(key, KEYIN_D) || PadJudg(key, KEYIN_RIGHT)) {
			_PlayerX += PLAYER_SPEED;
			_CharaState = LOOK_RIGHT;
		}
		if (KeyJudg(key, KEYIN_A) || PadJudg(key, KEYIN_LEFT)) {
			_PlayerX -= PLAYER_SPEED;
			_CharaState = LOOK_LEFT;
		}

		// ��ʊO����
		if (_PlayerX < 0) { _PlayerX = 0; }
		if (_PlayerX > WINDOW_WIDTH - _PlayerWidth) { _PlayerX = WINDOW_WIDTH - _PlayerWidth; }

		// �L�����̌����œY������ς���
		// �E����
		if (_CharaState == LOOK_RIGHT) {
			if ((_Subscript >= 3) && (_Subscript < 6)) {
				_Subscript = 6;
			}
		}
		// ������
		else if (_CharaState == LOOK_LEFT) {
			if ((_Subscript >= 6) && (_Subscript < 9)) {
				_Subscript = 3;
			}
		}

		// ���ԂœY������ς���
		if ((gFpsCount % ((int)FRAME_NUM_PER_SEC / 2)) == 0) {
			_Subscript++;	// �Y������ς���

			// �L�������E����
			if (_CharaState == LOOK_RIGHT) {
				// �Y�������͈͂��z������߂�
				if (_Subscript >= 9) {
					_Subscript = 6;
				}
			}
			// �L������������
			else if (_CharaState == LOOK_LEFT) {
				// �Y�������͈͂��z������߂�
				if (_Subscript >= 6) {
					_Subscript = 3;
				}
			}
		}

		SetPosX(_PlayerX);
	}

	/**
	 * �`�揈��
	 */
	void Player::Draw() {
		// ���C�t���c���Ă���΃v���C���[�`��
		if (_Life > 0) {
			DrawMemTh(_PlayerX, _PlayerY, _GhPlayer[_Subscript]);
		}
#ifdef _DEBUG
		DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (PLAYER_COLLISION * 2),
			GetCollPosY() + (PLAYER_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif // _DEBUG
	}
}
