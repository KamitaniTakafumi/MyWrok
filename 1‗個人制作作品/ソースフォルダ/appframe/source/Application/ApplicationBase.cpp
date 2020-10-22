
#include "../appframe.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// 画面モードの設定
	InitWnd(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, "個人ゲーム制作");

	if (AppWindowed())
	{
		// ウインドウモードの変更
		if (!InitApp()) { return false; }
	}

	InitBlendState();

	srand((unsigned int)time(NULL));

	// モードサーバの初期化
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
	// キーの入力、トリガ入力を得る
	int keyold = _key;
	_key = CheckKey(INPUT_MULT);
	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
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
