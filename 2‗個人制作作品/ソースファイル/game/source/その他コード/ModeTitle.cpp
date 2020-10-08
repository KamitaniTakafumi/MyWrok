
#include "appframe.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeGame.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	_cg = LoadTexture("res/title.png");				// ���P
	_start = LoadTexture("res/start.png");			// ���P
	_startpad = LoadTexture("res/startpad.png");	// ���P

	_starttime = timeGetTime();				// �J�n���Ԃ𓾂� ���P

	return true;
}

bool ModeTitle::Terminate() {
	base::Terminate();

	Release2DGraphs();		// ���P

	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if(KeyJudg(trg, KEYIN_RET) || PadJudg(trg, KEYIN_Z))	// ���P
	{
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();

	// ���P ��������
	int t = timeGetTime();			// ���݂̌o�ߎ��Ԃ��擾
	_stocktime = t - _starttime;	// ���[�h���n�܂��Ă���̌o�ߎ��Ԃ𓾂�

	DrawMem(0, 0, _cg);

	if ((_stocktime % 1000) < 500)	// 0.5�b��1��_�ł�����
	{
		if (gJoyPadNum != 0)		// �p�b�h���ڑ�����Ă��邩�ɂ���ĕ\������摜��ς���
		{
			DrawMemTh(0, 0, _startpad);
		}
		else
		{
			DrawMemTh(0, 0, _start);
		}
	}
	// ���P �����܂�

	return true;
}

