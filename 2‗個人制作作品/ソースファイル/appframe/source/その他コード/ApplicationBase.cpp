
#include "../appframe.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// ��ʃ��[�h�̐ݒ�
	InitWnd(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, "�l�Q�[������");	// ���P

	if (AppWindowed())
	{
		// �E�C���h�E���[�h�̕ύX
		if (!InitApp()) { return false; }	// ���P
	}

	InitBlendState();	// ���P

	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	SAFE_DELETE(_serverMode);
	
	ReleaseD3D();	// ���P
	
	return true;
}


bool ApplicationBase::Input() {
	InitJoyPad(MAX_JOYSTICK_COUNT);		// ���P
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = _key;
	_key = CheckKey(INPUT_MULT);
	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	_trg = (_key ^ keyold) & _key;

	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	HCls();			// ���P
	_serverMode->Render();
	fps();			// ���P
	wait_fanc();	// ���P
	Flip();			// ���P
	_serverMode->RenderFinish();
	return true;
}
