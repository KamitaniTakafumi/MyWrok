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
	Player::Player()
	{
		//�摜�ǂݍ���
		LoadBlkTexture("res/sample01.png", 80, 80, 3, 4, 12, _ghplayer);
		_ghhp = LoadTexture("res/heartP.png");
	}

	/**
	 * Player�f�X�g���N�^
	 */
	Player::~Player()
	{
	}

	bool Player::Initialize()
	{
		_width = 80;
		_height = 80;
		_x = (WINDOW_WIDTH - _width) / 2;
		_y = WINDOW_HEIGHT - _height;
		_suffix = 6;

		_life = PLAYER_HP;

		_charastate = LOOK_RIGHT;
		return false;
	}

	/**
	 * �ړ�����
	 * @param key �������u�Ԃ̔���
	 * @param trg ��������ςȂ��̔���
	 */
	void Player::Move(int key, int trg)
	{
		// �ړ�����
		if (KeyJudg(key, KEYIN_D) || PadJudg(key, KEYIN_RIGHT))
		{
			_x += PLAYER_SPEED;
			_charastate = LOOK_RIGHT;
		}
		if (KeyJudg(key, KEYIN_A) || PadJudg(key, KEYIN_LEFT))
		{
			_x -= PLAYER_SPEED;
			_charastate = LOOK_LEFT;
		}

		// ��ʊO����
		if (_x < 0) { _x = 0; }
		if (_x > WINDOW_WIDTH - _width) { _x = WINDOW_WIDTH - _width; }

		// �L�����̌����œY������ς���
		if (_charastate == LOOK_RIGHT)
		{
			// �E����
			if ((_suffix >= 3) && (_suffix < 6))
			{
				_suffix = 6;
			}
		}
		else if (_charastate == LOOK_LEFT)
		{
			// ������
			if ((_suffix >= 6) && (_suffix < 9))
			{
				_suffix = 3;
			}
		}

		// ���ԂœY������ς���
		if ((gFpsCount % ((int)FRAME_NUM_PER_SEC / 2)) == 0)
		{
			_suffix++;	// �Y������ς���

			// �L�������E����
			if (_charastate == LOOK_RIGHT)
			{
				// �Y�������͈͂��z������߂�
				if (_suffix >= 9)
				{
					_suffix = 6;
				}
			}
			// �L������������
			else if (_charastate == LOOK_LEFT)
			{
				// �Y�������͈͂��z������߂�
				if (_suffix >= 6)
				{
					_suffix = 3;
				}
			}
		}

		SetPosX(_x);
	}

	/**
	 * �`�揈��
	 */
	void Player::Draw()
	{
		// ���C�t���c���Ă���΃v���C���[�`��
		if (_life > 0)
		{
			DrawMemTh(_x, _y, _ghplayer[_suffix]);
		}
		// ���C�t�`��
		if (_life > 0)
		{
			DrawMemTh(0, 0, _ghhp);
		}
		if (_life > 1)
		{
			DrawMemTh(40, 0, _ghhp);
		}
		if (_life > 2)
		{
			DrawMemTh(80, 0, _ghhp);
		}
#ifdef _DEBUG
		DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (PLAYER_COLLISION * 2),
			GetCollPosY() + (PLAYER_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif // _DEBUG
	}
}
