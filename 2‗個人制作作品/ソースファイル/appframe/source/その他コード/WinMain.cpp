/**
 * WinMain
 */

#include "../appframe.h"


/**
 * WinMain(). プログラム起動関数
 */
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	MSG		msg;	// メッセージ

	ApplicationBase *appBase = ApplicationBase::GetInstance();
	if (!appBase) { return 0; }

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}

	while (ProcessEvent()) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0)) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		appBase->Input();

		appBase->Process();

		appBase->Render();
	}

	appBase->Terminate();

	return 0;
}
