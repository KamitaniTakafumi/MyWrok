/**
 * @file ModeGameover.cpp
 * @brief ����
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "appframe.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeGameover.h"

bool ModeGameover::Initialize() {
	if (!base::Initialize()) { return false; }

	_bg = LoadTexture("res/GameOver.png");
	_start = LoadTexture("res/start.png");
	_startpad = LoadTexture("res/startpad.png");

	return true;
}

bool ModeGameover::Terminate() {
	base::Terminate();

	Release2DGraphs();

	return true;
}

bool ModeGameover::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (KeyJudg(trg, KEYIN_RET) || PadJudg(trg, KEYIN_Z)) {
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeGameover::Render() {
	base::Render();

	DrawMemTh(0, 0, _bg);

	if (gJoyPadNum != 0)		// �p�b�h���ڑ�����Ă��邩�ɂ���ĕ\������摜��ς���
	{
		DrawMemTh(0, 0, _startpad);
	}
	else
	{
		DrawMemTh(0, 0, _start);
	}
	return true;
}

