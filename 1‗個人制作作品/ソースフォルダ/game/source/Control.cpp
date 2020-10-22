/**
 * @file Control.cpp
 * @brief ����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "Control.h"

namespace act {
	/**
	 * �R���g���[���R���X�g���N�^
	 */
	Control::Control()
	{
		for (int i = 0; i < ITEM_MAX; i++)
		{
			item[i] = new Item(i);
		}
	}

	/**
	 * �R���g���[���f�X�g���N�^
	 */
	Control::~Control()
	{
		for (int i = 0; i < ITEM_MAX; i++)
		{
			delete item[i];
		}
	}

	/**
	 * �R���g���[��������
	 */
	bool Control::Initialize()
	{
		player = std::make_unique<Player>();
		player->Initialize();

		return true;
	}

	/**
	 * �ړ�����
	 * @param key �����ꂽ�u�Ԃ̔���
	 * @param trg ��������ςȂ��̔���
	 */
	void Control::Move(int key, int trg)
	{
		player->Move(key, trg);
		for (int i = 0; i < ITEM_MAX; i++)
		{
			item[i]->Move(i);
		}
	}

	/**
	 * �Q�b�^�[(�v���C���[���W)
	 * @param x �v���C���[x���W
	 * @param y �v���C���[y���W
	 */
	void Control::GetPlayerPosition(double* x, double* y)
	{
		double tempx, tempy;

		tempx = player->GetPosX();
		tempy = player->GetPosY();

		*x = tempx;
		*y = tempy;
	}

	/**
	 * �Q�b�^�[(�A�C�e�����W)
	 * @param index �Y����
	 * @param x �A�C�e��x���W
	 * @param y �A�C�e��y���W
	 */
	void Control::GetItemPosition(int index, double* x, double* y)
	{
		double tempx, tempy;
		//�w�肵���Y���̓G�̍��W���擾
		tempx = item[index]->GetPosX();
		tempy = item[index]->GetPosY();

		//���
		*x = tempx;
		*y = tempy;
	}

	/**
	 * �I�u�W�F�N�g�P�ƃI�u�W�F�N�g�Q�̓����蔻��
	 * @param c1 ���a�P
	 * @param c2 ���a�Q
	 * @param cx1 x���W�P
	 * @param cx2 x���W�Q
	 * @param cy1 y���W�P
	 * @param cy2 y���W�Q
	 */
	bool Control::CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2)
	{

		double hlength = c1 + c2;
		double xlength = cx1 - cx2;
		double ylength = cy1 - cy2;

		if (hlength * hlength >= xlength * xlength + ylength * ylength) {
			return true;
		}
		else {
			return false;
		}
	}

	/**
	 * �S�Ă̓����蔻��
	 */
	void Control::CollisionAll()
	{
		double px, py, ix, iy;
		//����L�����ƃA�C�e���Ƃ̓����蔻��
		for (int i = 0; i < ITEM_MAX; ++i) {
			if (item[i]->GetUseFlag() != true) { continue; }
			else
			{
				px = player->GetCollPosX();
				py = player->GetCollPosY();
				ix = item[i]->GetCollPosX();
				iy = item[i]->GetCollPosY();
				if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy))
				{
					item[i]->SetUseFlag();
					if (i >= 50 && i < 100) { player->SetHP(); }
				}
			}
		}
	}

	/**
	 * �v���C���[�̗̑̓`�F�b�N
	 */
	bool Control::CheckPlayerHP()
	{
		if (player->GetHP() == 0)
		{
			return true;
		}

		return false;
	}

	/**
	 * �`�揈��
	 */
	void Control::Draw()
	{
		for (int i = 0; i < ITEM_MAX; i++)
		{
			item[i]->Draw();
		}
		player->Draw();
	}
}
