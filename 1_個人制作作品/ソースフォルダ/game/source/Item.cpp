/**
 * @file Item.cpp
 * @brief �A�C�e������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "appframe.h"
#include "Item.h"

namespace act {
	/**
	 * Item�R���X�g���N�^
	 */
	Item::Item() :
		_x(0), _y(0), _ghitem(0), _width(0), _height(0),
		_speed(0), _use(true), _ItemType(0) {
	}

	/**
	 * �A�C�e��������
	 * @param i �Y����
	 */
	void Item::Initialize(int i) {
		_width = 40;
		_height = 40;

		_x = 0 + 20 * i;
		_y = 0 - _height;

		_speed = 0;

		// �摜�ǂݍ���
		// �A�C�e���ʂɎ�ނ����߂�
		if ((i >= 0) && (i < 10)) { 
			_ItemType = White;
			_ghitem = LoadTexture("res/jewelwhite.png");
		}
		else if ((i >= 10) && (i < 20)) {
			_ItemType = Green;
			_ghitem = LoadTexture("res/jewelgreen.png");
		}
		else if ((i >= 20) && (i < 30)) {
			_ItemType = Blue;
			_ghitem = LoadTexture("res/jewelblue.png");
		}
		else if ((i >= 30) && (i < 40)) {
			_ItemType = Red;
			_ghitem = LoadTexture("res/jewelred.png");
		}
		else if ((i >= 40) && (i < 50)) {
			_ItemType = Gold;
			_ghitem = LoadTexture("res/jewelgold.png");
		}
		else if ((i >= 50) && (i < 100)) {
			_ItemType = HeartBlack;
			_ghitem = LoadTexture("res/heartb.png");
		}

		_use = false;
	}

	/**
	 * �ړ�����
	 * @param i �Y����
	 * @return �A�C�e�����g�p��ԂȂ�true
	 */
	bool Item::Move(int i) {
		// ���Ԋu(60�t���[����1��)�ŏ���
		if ((gFpsCount % (int)FRAME_NUM_PER_SEC) == 0) {
			// �A�C�e�����g�p��ԂȂ�X���[
			if (_use != false) {}
			else {
				// ��ޕʂɗ����ŃA�C�e���̎g�p�����߂�
				JudgmentItem();
			}
		}

		// �A�C�e�����g�p��ԂłȂ���Ώ����𔲂���
		if (_use != true) { return false; }
		else {
			_y = _y + _speed;
			// ��ʊO�ɏo����t���O��߂�
			if (_y > WINDOW_HEIGHT) {
				_use = false;
			}
		}

		return true;
	}

	/**
	 * �t���O����
	 */
	void Item::UseItem() {
		_x = (rand() % WINDOW_WIDTH) - _width;
		_y = 0 - _height;
		_speed = (rand() % 4) + 1;
		_use = true;
	}

	/**
	 *  ��ޕʂ̃A�C�e���g�p����
	 */
	void Item::JudgmentItem() {
		int Probability = 0;	// �A�C�e���̎g�p�m��
		// ��ޕʂɊm�������߂�
		switch (_ItemType) {
		case White:
			Probability = 30;
			break;
		case Green:
			Probability = 25;
			break;
		case Blue:
			Probability = 20;
			break;
		case Red:
			Probability = 15;
			break;
		case Gold:
			Probability = 10;
			break;
		case HeartBlack:
			Probability = 20;
			break;
		default:
			Probability = 0;
			break;
		}

		// �������m�����傫����΃A�C�e�����g�p
		if ((rand() % 100) < Probability) {
			UseItem();
		}
	}

	/**
	 * �`�揈��
	 * @return �A�C�e�����g�p��ԂȂ�true
	 */
	bool Item::Draw() {
		if (_use != true) { return false; }
		else {
			DrawMemTh(_x, _y, _ghitem);
#ifdef _DEBUG
			DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (ITEM_COLLISION * 2),
				GetCollPosY() + (ITEM_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif
		}

		return true;
	}
}
