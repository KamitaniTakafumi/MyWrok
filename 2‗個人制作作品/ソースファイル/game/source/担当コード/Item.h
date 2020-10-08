/**
 * @file Item.cpp
 * @brief ����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once

class Item
{
public:
	Item(int i);
	virtual ~Item();

	int GetPosX() { return _x; }
	int GetPosY() { return _y; }
	bool GetUseFlag() { return _use; }

	// �����蔻��p�̃|�W�V�����擾
	int GetCollPosX() { return _x + (_width / 2) - ITEM_COLLISION; }
	int GetCollPosY() { return _y + (_height / 2) - ITEM_COLLISION; }

	int SetPosX(int x) { return _x = x; }
	int SetPosY(int y) { return _y = y; }
	bool SetUseFlag() { return _use = false; }

	bool Move(int i);
	bool Draw();
private:
	void UseItem();
private:
	int _x, _y;				// x���W,y���W
	int _ghitem;			// �O���t�B�b�N�n���h���i�[�p�z��
	int _width, _height;	// �摜��
	bool _use;				// �g���Ă��邩�ǂ����̃t���O
};
