/**
 * @file Control.h
 * @brief �R���g���[������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"
#include "Player.h"
#include "Item.h"

namespace act {
	class Control
	{
	private:
		std::unique_ptr<Player> player;
		Item* item[ITEM_MAX];
	public:
		/**
		 * �R���g���[���R���X�g���N�^
		 */
		Control();

		/**
		 * �R���g���[���f�X�g���N�^
		 */
		virtual ~Control();

		/**
		 * �R���g���[��������
		 */
		bool Initialize();

		/**
		 * �ړ�����
		 * @param key �����ꂽ�u�Ԃ̔���
		 * @param trg ��������ςȂ��̔���
		 */
		void Move(int key, int trg);

		/**
		 * �Q�b�^�[(�v���C���[���W)
		 * @param x �v���C���[x���W
		 * @param y �v���C���[y���W
		 */
		void GetPlayerPosition(double* x, double* y);

		/**
		 * �Q�b�^�[(�A�C�e�����W)
		 * @param index �Y����
		 * @param x �A�C�e��x���W
		 * @param y �A�C�e��y���W
		 */
		void GetItemPosition(int index, double* x, double* y);

		/**
		 * �S�Ă̓����蔻��
		 */
		void CollisionAll();

		/**
		 * �v���C���[�̗̑̓`�F�b�N
		 */
		bool CheckPlayerHP();

		/**
		 * �`�揈��
		 */
		void Draw();
	private:
		/**
		 * �I�u�W�F�N�g�P�ƃI�u�W�F�N�g�Q�̓����蔻��
		 * @param c1 ���a�P
		 * @param c2 ���a�Q
		 * @param cx1 x���W�P
		 * @param cx2 x���W�Q
		 * @param cy1 y���W�P
		 * @param cy2 y���W�Q
		 */
		bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	protected:
	};
}
