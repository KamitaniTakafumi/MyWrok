#pragma once
/*
*  @file game.cpp
*  @brief �Q�[������
*  @author ��J���j
*  @date 2020 / 02 / 26
*/

struct GAMEMODE// �Q�[�����[�h�\����
{
	int Mode;			// ���݂̃��[�h
	int OutMode;		// �O�̃��[�h
};

extern GAMEMODE gGameMode;// �Q�[�����[�h���

enum STATEGAMEMODE// �Q�[�����[�h�̏��
{
	GAME_LOAD,
	GAME_LOGO,
	GAME_TITLE,
	GAME_IN,
	GAME_POSE,
	GAME_RESULT,
	GAME_OVER,
	GAME_ENDROLL,
	GAME_NUM
};

/*
*  ������
*/
void AppInit();

/*
*	�t���[�������F����
*/
void FrameInput();

/*
*	�t���[�������F�v�Z
*/
void FrameProcess();

/*
*	�t���[�������F�`��
*/
void FrameDraw();
