
#include "../appframe.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// ‰æ–Êƒ‚[ƒh‚Ìİ’è
	InitWnd(hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, "ŒÂlƒQ[ƒ€§ì");	// ¦‚P

	if (AppWindowed())
	{
		// ƒEƒCƒ“ƒhƒEƒ‚[ƒh‚Ì•ÏX
		if (!InitApp()) { return false; }	// ¦‚P
	}

	InitBlendState();	// ¦‚P

	srand((unsigned int)time(NULL));

	// ƒ‚[ƒhƒT[ƒo‚Ì‰Šú‰»
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	SAFE_DELETE(_serverMode);
	
	ReleaseD3D();	// ¦‚P
	
	return true;
}


bool ApplicationBase::Input() {
	InitJoyPad(MAX_JOYSTICK_COUNT);		// ¦‚P
	// ƒL[‚Ì“ü—ÍAƒgƒŠƒK“ü—Í‚ğ“¾‚é
	int keyold = _key;
	_key = CheckKey(INPUT_MULT);
	// ƒL[‚ÌƒgƒŠƒKî•ñ¶¬i‰Ÿ‚µ‚½uŠÔ‚µ‚©”½‰‚µ‚È‚¢ƒL[î•ñj
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
	HCls();			// ¦‚P
	_serverMode->Render();
	fps();			// ¦‚P
	wait_fanc();	// ¦‚P
	Flip();			// ¦‚P
	_serverMode->RenderFinish();
	return true;
}
