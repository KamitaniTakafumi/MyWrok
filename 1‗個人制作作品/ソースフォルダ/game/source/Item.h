/**
 * @file Item.h
 * @brief �A�C�e������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"

namespace act {
	class Item
	{
	public:
		/**
		 * Item�R���X�g���N�^
		 */
		Item(int i);

		/**
		 * Item�f�X�g���N�^
		 */
		virtual ~Item();

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
		 * �Q�b�^�[(�t���O)
		 * @return �t���O
		 */
		bool GetUseFlag() { return _use; }

		/**
		 * �����蔻��p��x���W�擾
		 * @return x���W
		 */
		int GetCollPosX() { return _x + (_width / 2) - ITEM_COLLISION; }

		/**
		 * �����蔻��p��y���W�擾
		 * @return y���W
		 */
		int GetCollPosY() { return _y + (_height / 2) - ITEM_COLLISION; }

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
		 * �Z�b�^�[(�t���O)
		 * @return �t���O
		 */
		bool SetUseFlag() { 
			if (_use == true) { _use = false; }
			return _use;
		}

		/**
		 * �ړ�����
		 * @param i �Y����
		 * @return �A�C�e�����g�p��ԂȂ�true
		 */
		bool Move(int i);

		/**
		 * �`�揈��
		 * @return �A�C�e�����g�p��ԂȂ�true
		 */
		bool Draw();
	private:
		/**
		 * �t���O����
		 */
		void UseItem();
	private:
		enum ItemType {
			WHITE_JEWEL,
			GREEN_JEWEL,
			BLUE_JEWEL,
			RED_JEWEL,
			GOLD_JEWEL,
			BLACK_HEART,
		};

		int _x, _y;				// x���W,y���W
		int _ghitem[6];			// �O���t�B�b�N�n���h���i�[�p�z��
		int _width, _height;	// �摜��
		int _speed;				// �����X�s�[�h
		int _itemtype;
		bool _use;				// �g���Ă��邩�ǂ����̃t���O
	};
}
