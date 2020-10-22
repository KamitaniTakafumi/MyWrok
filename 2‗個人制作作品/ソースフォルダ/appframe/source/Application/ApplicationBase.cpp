
#include "../appframe.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// ��ʃ��[�h�̐ݒ�
	InitWnd(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, "�l�Q�[������");

	if (AppWindowed())
	{
		// �E�C���h�E���[�h�̕ύX
		if (!InitApp()) { return false; }
	}

	InitBlendState();

	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	SAFE_DELETE(_serverMode);
	
	ReleaseD3D();
	
	return true;
}


bool ApplicationBase::Input() {
	InitJoyPad(MAX_JOYSTICK_COUNT);
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
	HCls();
	_serverMode->Render();
	fps();
	wait_fanc();
	Flip();
	_serverMode->RenderFinish();
	return true;
}
