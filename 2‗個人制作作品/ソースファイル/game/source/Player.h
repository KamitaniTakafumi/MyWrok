/**
 * @file Player.cpp
 * @brief ����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#pragma once

/**
 * �L�����̌���
 */
enum PlayerState
{
	LOOK_RIGHT,
	LOOK_LEFT,
};

class Player
{
public:
	Player();
	virtual ~Player();

	int GetPosX() { return _x; }
	int GetPosY() { return _y; }
	int GetHP() { return _life; }

	// �����蔻��p�̃|�W�V�����擾
	int GetCollPosX() { return _x + (_width / 2) - PLAYER_COLLISION; }
	int GetCollPosY() { return _y + (_height / 2); }
	
	int SetPosX(int x) { return _x = x; }
	int SetPosY(int y) { return _y = y; }
	int SetHP() { return _life--; }

	void Move(int key, int trg);
	void Draw();
private:
	int _x, _y;				// x���W,y���W
	int _graphnum;			// �����摜��
	int _ghplayer[12];		// �O���t�B�b�N�n���h���i�[�p�z��i�v���C���[�j
	int _ghhp;				// �O���t�B�b�N�n���h���i�q�b�g�|�C���g�j
	int _suffix;			// �Y�����ԍ�
	int _width, _height;	// �摜��
	int _life;				// �����Ă邩�ǂ����̃t���O
	int _charastate;		// �L�����̏��
};
