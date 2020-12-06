/**
 * @file library.cpp
 * @brief ライブラリ処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "library.h"

#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment(lib, "dinput8.lib")

/**
 * DirectX用旧関数エイリアス定義
 */
int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;
int (WINAPIV * _sscanf)(const char*, const char*, ...) = sscanf;
int (WINAPIV * __snprintf)(char *, size_t, const char*, ...) = _snprintf;
int (WINAPIV * _sprintf)(char*, const char*, ...) = sprintf;

LPDIRECT3D9				glpD3D;
D3DPRESENT_PARAMETERS	gD3Dpp;

/**
 * スクリーンパラメータ
 */
D3DFORMAT	gScreenFormat;
int			gScreenWidth;
int			gScreenHeight;

/**
 * ３Ｄデバイス
 */
IDirect3DDevice9*	gD3DDevice;

/**
 * デバイス初期化
 * @return 初期化できればtrue、できなければfalse
 */
bool InitD3D(HWND hWnd, bool bFullScreen) {
	//	スクリーンサイズ取得
	int	Width = 1280;
	int	Height = 720;

	// D3Dオブジェクトの作成
	glpD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// アダプタの現在のディスプレイ モードを取得する
	D3DDISPLAYMODE d3ddm;
	glpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS _d3dpp = {
	  640,480,
	  D3DFMT_A8R8G8B8,
	  0,
	  D3DMULTISAMPLE_NONE,
	  0,
	  D3DSWAPEFFECT_DISCARD,
	  hWnd,
	  false,
	  true,D3DFMT_D24S8,
	  0,
	  D3DPRESENT_RATE_DEFAULT,
	  D3DPRESENT_INTERVAL_DEFAULT };

	ZeroMemory(&gD3Dpp, sizeof(D3DPRESENT_PARAMETERS));
	gD3Dpp.Flags = 0;
	gD3Dpp.BackBufferHeight = Height;
	gD3Dpp.BackBufferWidth = Width;
	gD3Dpp.BackBufferCount = 1;

	gD3Dpp.hDeviceWindow = hWnd;

	gD3Dpp.EnableAutoDepthStencil = true;
	gD3Dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	gD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	gD3Dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	gD3Dpp.MultiSampleQuality = 0;

	if (bFullScreen) {
		gD3Dpp.Windowed = !bFullScreen;
		gD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		gD3Dpp.BackBufferFormat = d3ddm.Format;
		gD3Dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}
	else {
		gD3Dpp.Windowed = true;
		gD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		gD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}

	//	デバイス作成
	if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&gD3Dpp, &gD3DDevice))) 
	{
		if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&gD3Dpp, &gD3DDevice))) 
		{
			MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
			if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&gD3Dpp, &gD3DDevice))) 
			{
				if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&gD3Dpp, &gD3DDevice))) 
				{
					MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
					return false;
				}
			}
		}
	}

	//	グローバルパラメータ設定
	gScreenFormat = gD3Dpp.BackBufferFormat;
	gScreenWidth = gD3Dpp.BackBufferWidth;
	gScreenHeight = gD3Dpp.BackBufferHeight;

	return true;
}

/**
 * デバイス開放
 */
void ReleaseD3D() {
	gD3DDevice->Release(); gD3DDevice = NULL;
	glpD3D->Release(); glpD3D = NULL;
}

/**
 * シーン開始
 */
void BeginScene() {
	gD3DDevice->BeginScene();
}

/**
 * シーン終了
 */
void EndScene() {
	gD3DDevice->EndScene();
	if (FAILED(gD3DDevice->Present(NULL, NULL, NULL, NULL))) gD3DDevice->Reset(&gD3Dpp);
}


/**
 * Window作成
 */

// ウインドウハンドル
HWND gWindowHandle = NULL;

#ifdef _DEBUG
BOOL gFullScreen = FALSE;
#else
BOOL gFullScreen = TRUE;
#endif // _DEBUG

/**
 * ウィンドウプロシージャ
 */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY: PostQuitMessage(0); return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE: PostMessage(hWnd, WM_CLOSE, 0, 0); return 0;

		case WM_LBUTTONDOWN: break;

		case WM_RBUTTONDOWN: break;
		}

		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/**
 * ウインドウ作成
 * @param hInst インスタンスハンドル
 * @param disp_w, disp_h 画面サイズ
 * @param WindowName ウインドウの名前
 */
void InitWnd(HINSTANCE hInst, int disp_w, int disp_h, LPSTR WindowName) {
	// ウィンドウの初期化
	WNDCLASSEX wndclass;

	// 構造体サイズ
	wndclass.cbSize = sizeof(wndclass);

	/** ウインドウスタイル
	 CS_HREDRAW	横サイズが変わったときにウインドウ全体を再描画
	 CS_VREDRAW	縦サイズが...
	 */
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc = WindowProc;										// コールバック関数へのポインタ
	wndclass.cbClsExtra = 0;												// クラス構造体後ろの補足バイト数
	wndclass.cbWndExtra = 0;												// インスタンス後ろの補足バイト数
	wndclass.hInstance = hInst;												// ウインドウプロシージャがあるインスタンスハンドル
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);						// アイコンハンドル
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);							// マウスカーソルハンドル
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);			// ウインドウ背景色(黒)
	wndclass.lpszMenuName = NULL;											// デフォルトメニュー名
	wndclass.lpszClassName = WindowName;										// このウインドウクラスの名前
	wndclass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);						// 16*16の小アイコン
	// ウインドウクラス登録
	RegisterClassEx(&wndclass);

	// ウインドウ作成
	if (gFullScreen) {
		gWindowHandle = CreateWindow(WindowName,				// 登録したクラスの名前 
			WindowName,				// タイトルバーに表示する文字列
			WS_VISIBLE | WS_POPUP,	// ウインドウスタイル
			0, 0,					// ウインドウ座標
			disp_w, disp_h,			// ウインドウサイズ
			NULL,					// 親ウインドウのハンドル
			NULL,					// メニューハンドル(デフォ使うならNULL)
			hInst,					// ウインドウとかを作成するモジュールのインスタンスハンドル
			NULL);					// WM_CREATEでLPARAMに渡したい値(だいたいNULL)
	}
	else {
		gWindowHandle = CreateWindow(WindowName,
			WindowName,
			WS_OVERLAPPEDWINDOW,
			0, 0,
			disp_w, disp_h,
			NULL,
			NULL,
			hInst,
			NULL);
	}

	if (!gWindowHandle) { return; }

	// ウインドウの表示状態の設定
	ShowWindow(gWindowHandle, SW_SHOW);
	UpdateWindow(gWindowHandle);
}

// プロセス制御変数
BOOL							gEndFlag = false;			// 終了フラグ

BOOL							gSceneActive = false;		// シーンはアクティブか

/*
 * Windowsイベント処理
 */
int ProcessEvent(void) {
	int					nEventCnt;
	MSG					msg;

	if (gEndFlag) return false;							// すでに終了か

	nEventCnt = 0;
	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!GetMessage(&msg, NULL, 0, 0)) {
			gEndFlag = true;
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		nEventCnt++;
		if (nEventCnt >= MAX_EVENTS) break;
	}
	return true;
}

/**
 * 画面の更新
 */
int DispFlip(void) {
	D3DRASTER_STATUS			RasterData;

	if (gEndFlag) return DISPERROR;						// 終了か

	gD3DDevice->EndScene();
	gSceneActive = false;

	// ウィンドウモードならVBlank待ち
	if (!gFullScreen) {
		do {													// VBlankになるまで待つ
			if (!ProcessEvent()) break;					// とりあえずイベント処理
			gD3DDevice->GetRasterStatus(0, &RasterData);
		} while (!RasterData.InVBlank);
	}

	// 終わってなければ表示
	if (!gEndFlag) {
		gD3DDevice->Present(NULL, NULL, NULL, NULL);		// バックバッファの内容を表示
		gD3DDevice->BeginScene();							// シーン開始
		gSceneActive = true;
	}
	else { return DISPERROR; }

	return OK;
}

/**
 * アプリケーション初期化
 */
bool InitApp() {
	if (!ConnectionPad()) { return false; }

	if (!InitD3D(gWindowHandle, gFullScreen)) { return false; }

	if (!InitFont()) { return false; }

	return true;
}



/**
 * キー入力付加
 * @parme nKeyState キー入力状態
 */
int AddKeyInput(int nKeyState) {
	BYTE			cKeyBuf[256];

	GetKeyboardState(cKeyBuf);								// キーボード

	if ((cKeyBuf[VK_NUMPAD2] & 0x80) ||
		(cKeyBuf[VK_DOWN] & 0x80)) nKeyState |= KEYIN_DOWN;
	if ((cKeyBuf[VK_NUMPAD4] & 0x80) ||
		(cKeyBuf[VK_LEFT] & 0x80)) nKeyState |= KEYIN_LEFT;
	if ((cKeyBuf[VK_NUMPAD6] & 0x80) ||
		(cKeyBuf[VK_RIGHT] & 0x80)) nKeyState |= KEYIN_RIGHT;
	if ((cKeyBuf[VK_NUMPAD8] & 0x80) ||
		(cKeyBuf[VK_UP] & 0x80)) nKeyState |= KEYIN_UP;

	if ((cKeyBuf[VK_SPACE] & 0x80)) nKeyState |= KEYIN_SPC;
	if ((cKeyBuf[VK_ESCAPE] & 0x80)) nKeyState |= KEYIN_ESC;
	if ((cKeyBuf[VK_SHIFT] & 0x80)) nKeyState |= KEYIN_SFT;
	if ((cKeyBuf[VK_RETURN] & 0x80)) nKeyState |= KEYIN_RET;

	if ((cKeyBuf['Z'] & 0x80)) nKeyState |= KEYIN_Z;
	if ((cKeyBuf['X'] & 0x80)) nKeyState |= KEYIN_X;
	if ((cKeyBuf['C'] & 0x80)) nKeyState |= KEYIN_C;
	if ((cKeyBuf['A'] & 0x80)) nKeyState |= KEYIN_A;
	if ((cKeyBuf['S'] & 0x80)) nKeyState |= KEYIN_S;
	if ((cKeyBuf['D'] & 0x80)) nKeyState |= KEYIN_D;
	if ((cKeyBuf['Q'] & 0x80)) nKeyState |= KEYIN_Q;
	if ((cKeyBuf['W'] & 0x80)) nKeyState |= KEYIN_W;

	return nKeyState;
}

/**
 * キー判定
 * @parme nPushKey 押されたキー
 * @parme nJudgKey 判定したいキー
 */
bool KeyJudg(int nPushKey, int nJudgKey) {
	if (nPushKey & nJudgKey) return true;
	return false;
}

/**
 * パッド用グローバル変数
 */
int	gJoyPadNum = -1;			// ジョイパッド数
int	gMouseCursor = false;		// マウスカーソル

int gKeyOld1;
int gKey1;
int gTrg1;

int gKeyOld2;
int gKey2;
int gTrg2;

int gKeyOld3;
int gKey3;
int gTrg3;

int gKeyOld4;
int gKey4;
int gTrg4;

JOYPAD	gJoyPads[MAX_JOYSTICK_COUNT];		// ジョイパッド
UINT	gPadIDs[MAX_JOYSTICK_COUNT] = { JOYSTICKID1, JOYSTICKID2, JOYSTICKID3, JOYSTICKID4 };	// パッド番号配列

/**
 * 単体パッド入力付加
 * @parme nPadIndex パッドの番号(0～3)
 * @parme nPadState パッド入力状態
 */
int AddJoyInput(int nPadIndex, int nPadState) {
	JOYPAD						*pJoyPad;						// パッド
	JOYINFOEX					JoyInfo;						// パッド情報

	// 値チェックとパッド取得
	if (nPadIndex < 0 || nPadIndex >= gJoyPadNum) return PADERROR;
	pJoyPad = &gJoyPads[nPadIndex];

	if (pJoyPad->bValid) {									// 有効か
		JoyInfo.dwSize = sizeof(JoyInfo);					// Joy構造体セット
		JoyInfo.dwFlags = JOY_RETURNALL;
		JoyInfo.dwXpos = pJoyPad->nCenterX;
		JoyInfo.dwYpos = pJoyPad->nCenterY;
		JoyInfo.dwButtons = 0;
		if (joyGetPosEx(pJoyPad->uJoyID, &JoyInfo) == JOYERR_NOERROR) {
			if (JoyInfo.dwYpos > pJoyPad->nBottom) nPadState |= KEYIN_2;
			if (JoyInfo.dwXpos < pJoyPad->nLeft) nPadState |= KEYIN_4;
			if (JoyInfo.dwXpos > pJoyPad->nRight) nPadState |= KEYIN_6;
			if (JoyInfo.dwYpos < pJoyPad->nTop) nPadState |= KEYIN_8;
			nPadState |= (JoyInfo.dwButtons & 0xff) << 8;
			if (JoyInfo.dwButtons & 0x100) nPadState |= KEYIN_ESC;
			if (JoyInfo.dwButtons & 0x200) nPadState |= KEYIN_SPC;
		}
	}
	return nPadState;
}

/**
 * パッド判定
 * @parme nPushPad 押されたボタン
 * @parme nJudgPad 判定したいボタン
 */
bool PadJudg(int nPushPad, int nJudgPad) {
	if (nPushPad & nJudgPad) return true;
	return false;
}

/**
 * キーが押されているかチェック
 * @parme nInputMode 入力モード
 */
int CheckKey(int nInputMode) {
	int							i;
	int							nResult = 0;

	switch (nInputMode) {
		// マルチプル入力
	case INPUT_MULT:
		nResult = AddKeyInput(0);							// キーボード入力

		for (i = 0; i < gJoyPadNum; i++) {					// パッド入力
			nResult = AddJoyInput(i, nResult);
		}
		break;

		// キーボード入力
	case INPUT_KEYBOARD:
		nResult = AddKeyInput(0);
		break;

		// パッド1入力
	case INPUT_PAD1:
		nResult = AddJoyInput(0, 0);
		break;

		// パッド2入力
	case INPUT_PAD2:
		nResult = AddJoyInput(1, 0);
		break;

		// パッド3入力
	case INPUT_PAD3:
		nResult = AddJoyInput(2, 0);
		break;

		// パッド4入力
	case INPUT_PAD4:
		nResult = AddJoyInput(3, 0);
		break;

		// 不正入力
	default:
		nResult = INPUTERROR;
		break;
	}

	return nResult;
}


/**
 *  単体ジョイパッド初期化
 */
static int InitSinglePad(UINT nJoyID, JOYPAD *pJoyPad) {
	JOYCAPS						jCaps;
	JOYINFOEX					jJoyInfo;
	int							nResult = PADERROR;

	pJoyPad->bValid = false;									// 無効にしておく
	if (joyGetDevCaps(nJoyID, &jCaps, sizeof(jCaps)) == JOYERR_NOERROR) {
		pJoyPad->uJoyID = nJoyID;
		pJoyPad->nMinX = jCaps.wXmin;  pJoyPad->nMaxX = jCaps.wXmax;
		pJoyPad->nMinY = jCaps.wYmin;  pJoyPad->nMaxY = jCaps.wYmax;
		pJoyPad->nCenterX = (jCaps.wXmax - jCaps.wXmin) / 2;
		pJoyPad->nCenterY = (jCaps.wYmax - jCaps.wYmin) / 2;
		pJoyPad->nLeft = (pJoyPad->nMaxX - pJoyPad->nMinX) / 3
			+ pJoyPad->nMinX;
		pJoyPad->nRight = ((pJoyPad->nMaxX - pJoyPad->nMinX) / 3) * 2
			+ pJoyPad->nMinX;
		pJoyPad->nTop = (pJoyPad->nMaxY - pJoyPad->nMinY) / 3
			+ pJoyPad->nMinY;
		pJoyPad->nBottom = ((pJoyPad->nMaxY - pJoyPad->nMinY) / 3) * 2
			+ pJoyPad->nMinY;
		jJoyInfo.dwSize = sizeof(jJoyInfo);					// Joy構造体セット
		jJoyInfo.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(pJoyPad->uJoyID, &jJoyInfo) == JOYERR_NOERROR) {
			pJoyPad->bValid = TRUE;								// パッド有効に
			nResult = OK;
		}
	}

	return nResult;
}

/**
 *  パッド使用終了
 */
int EndJoyPad(void) {
	return OK;
}

/*
* パッド初期化
* @param nMaxPadNum パッドの最大数
*/
int InitJoyPad(int nMaxPadNum) {
	int							i;
	int							nActivePadNum = 0;				// アクティブなパッド数
	int							nResult;

	gJoyPadNum = 0;

	if (nMaxPadNum > MAX_JOYSTICK_COUNT) nMaxPadNum = MAX_JOYSTICK_COUNT;
	for (i = 0; i < nMaxPadNum; i++) {
		nResult = InitSinglePad(gPadIDs[i], &gJoyPads[i]);	// パッド初期化
		if (nResult != OK) break;							// 無ければ終了
		nActivePadNum++;
	}

	gJoyPadNum = nActivePadNum;								// パッド数登録

	return nActivePadNum;
}

/**
 *  1P～4Pまでのキー入力取得
 */
void InKey()
{
	gKeyOld1 = gKey1;
	gKey1 = CheckKey(INPUT_PAD1);		//キー入力取得
	gTrg1 = (gKey1 ^ gKeyOld1)& gKey1;	//トリガーキー入力取得

	gKeyOld2 = gKey2;
	gKey2 = CheckKey(INPUT_PAD2);		//キー入力取得
	gTrg2 = (gKey2 ^ gKeyOld2)& gKey2;	//トリガーキー入力取得

	gKeyOld3 = gKey3;
	gKey3 = CheckKey(INPUT_PAD3);		//キー入力取得
	gTrg3 = (gKey3 ^ gKeyOld3)& gKey3;	//トリガーキー入力取得

	gKeyOld4 = gKey4;
	gKey4 = CheckKey(INPUT_PAD4);		//キー入力取得
	gTrg4 = (gKey4 ^ gKeyOld4)& gKey4;	//トリガーキー入力取得
}

/**
 * パッドの接続設定
 */
bool ConnectionPad() {
	if (InitJoyPad(MAX_JOYSTICK_COUNT) <= 0) {
		int flag;
		flag = MessageBox(NULL, "キーボード操作でゲームを開始しますか？", "コントローラー設定", MB_YESNO);

		if (flag == IDNO) {
			MessageBox(NULL, "コントローラーを接続して再起動してください", "コントローラー設定", NULL);
			return false;
		}
	}
	return true;
}



/**
 * フォント用グローバル変数
 */
LPD3DXFONT	gD3DFont = NULL;
int			gStringFontSize = -1;	// 文字列フォントサイズ

/**
 * 文字列初期化
 */
int InitFont() {
	//文字列レンダリングの初期化
	if (FAILED(D3DXCreateFont(gD3DDevice, 0, 10, FW_REGULAR, NULL, false, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &gD3DFont)))
	{
		return FONTERROR;
	}

	return OK;
}

/**
 * 文字列開放
 */
void	ReleaseFont() {
	gD3DFont->Release();
}

/**
 * 色コードの獲得
 * @param	alpha	アルファ値、NULLを入れると自動的に255になる
 * @param	red		赤の値
 * @param	green	緑の値
 * @param	blue	青の値
 * @return	色コードを返す
 */
DWORD GetColor(int alpha, int red, int green, int blue) {
	int result;

	// 規定数以上or規定数未満ならば戻す
	if (alpha == NULL) { alpha = 255; }
	if (alpha < 0) { alpha = 0; } else if (alpha > 255) { alpha = 255; }
	if (red < 0) { red = 0; } else if (red > 255) { red = 255; }
	if (green < 0) { green = 0; } else if (green > 255) { green = 255; }
	if (blue < 0) { blue = 0; } else if (blue > 255) { blue = 255; }

	result = static_cast<int>D3DCOLOR_ARGB(alpha, red, green, blue);

	return result;
}

/**
 * 文字列描画
 * @param x,y	描画座標
 * @param color	色コード
 * @param fmt	文字列
 * @param ...	表示したい変数など
 */
void DrawString(float x, float y, int color, const char *fmt, ...) {
	int strlength;		// 文字列の長さを格納
	char sz[0xffff];	// 格納サイズ。もし溢れたら問題が出る。

	strlength = (int)strlen(fmt);
	va_list list;
	va_start(list, fmt);
	vsprintf(sz, fmt, list);
	va_end(list);

	RECT rect = { (LONG)x, (LONG)y, (LONG)x + strlength * gStringFontSize, (LONG)y + gStringFontSize };
	gD3DFont->DrawText(NULL, sz, -1, &rect, DT_CALCRECT, NULL);
	gD3DFont->DrawText(NULL, sz, -1, &rect, DT_LEFT | DT_BOTTOM, color);
}


/**
 * 画像用グローバル変数
 */
int	gBitDepth = 32;			// ビットデプス

TEX_UNIT_PICTURE	gUnitPictureBuf[MAX_UNIT_PICTURES];		// 単位ピクチャバッファ
int					gUnitPicNum = 0;						// 単位ピクチャ数
TEX_USER_PICTURE	gUserPictureBuf[MAX_USER_PICTURES];		// ユーザピクチャバッファ
int					gUserPicNum = 0;						// ユーザピクチャ数

int	fg_nFrameCount = 0;		// フレームカウンタ

/**
 * 2Dグラフィックロード
 */
LPDIRECT3DTEXTURE9 Load2DGraph(char *szFileName, TEX_2DPIC_INFO *pPicInfo) {
	LPDIRECT3DTEXTURE9		p2dGraph = NULL;	// ロードテクスチャ
	HRESULT					hRes;
	D3DXIMAGE_INFO			iiImageInfo;
	LPDIRECT3DSURFACE9		lpTopSurf;
	D3DSURFACE_DESC			ddSurfInfo;
	D3DFORMAT				dfTexFormat;		// テクスチャフォーマット
	D3DCOLOR				nColorKey;			// カラーキー

	// ピクセルフォーマット
	dfTexFormat = (gBitDepth == 32) ? D3DFMT_A8R8G8B8 : D3DFMT_A1R5G5B5;

	// カラーキー処理
	if (strstr(szFileName, ".bmp") || strstr(szFileName, ".BMP")) {	// ビットマップの場合
		nColorKey = 0xff000000;	// ビットマップならカラーキーあり
	}
	else {
		nColorKey = 0;			// ビットマップ以外ならカラーキーなし
	}

	// テクスチャロード
	hRes = D3DXCreateTextureFromFileEx(gD3DDevice, (LPCSTR)szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		dfTexFormat, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		nColorKey, &iiImageInfo, NULL,
		&p2dGraph);

	if (FAILED(hRes)) return NULL;

	// サーフェス情報取得
	hRes = p2dGraph->GetSurfaceLevel(0, &lpTopSurf);
	if (FAILED(hRes)) return NULL;
	lpTopSurf->GetDesc(&ddSurfInfo);
	lpTopSurf->Release();

	pPicInfo->nWidth = iiImageInfo.Width;
	pPicInfo->nHeight = iiImageInfo.Height;
	pPicInfo->nRealWidth = ddSurfInfo.Width;
	pPicInfo->nRealHeight = ddSurfInfo.Height;
	
	return p2dGraph;
}

// 新規単位ピクチャ
static TEX_UNIT_PICTURE *MakeUnitPicture(LPDIRECT3DTEXTURE9 ppbPicture, 
	TEX_2DPIC_INFO *ppiPicInfo, char *szFileName)
{
	if (gUnitPicNum >= MAX_UNIT_PICTURES) return NULL;			// 空きチェック

	gUnitPictureBuf[gUnitPicNum].a2PicInfo = *ppiPicInfo;		// 絵情報
	gUnitPictureBuf[gUnitPicNum].pPicture = ppbPicture;			// 絵オブジェクト
	strncpy(gUnitPictureBuf[gUnitPicNum].szFileName, szFileName, MAX_PICTURE_NAME - 1);	// 絵ファイル名
	gUnitPictureBuf[gUnitPicNum].szFileName[MAX_PICTURE_NAME - 1] = 0;	// ファイル名の終端を確実に置く
	gUnitPicNum++;

	return &gUnitPictureBuf[gUnitPicNum - 1];
}

// 新規絵ハンドル
static int Make2DHandle(TEX_UNIT_PICTURE *pUnitPic, 
	int nLeft, int nTop, int nWidth, int nHeight, int bFlags)
{
	int	hPicture = PIC2D_HANDLE_HEAD;

	if (gUserPicNum >= MAX_USER_PICTURES) return NULL;	// ハンドル空きチェック

	gUserPictureBuf[gUserPicNum].pUnitPic = pUnitPic;
	gUserPictureBuf[gUserPicNum].nLeft = nLeft;
	gUserPictureBuf[gUserPicNum].nTop = nTop;
	gUserPictureBuf[gUserPicNum].nWidth = nWidth;
	gUserPictureBuf[gUserPicNum].nHeight = nHeight;
	gUserPictureBuf[gUserPicNum].bFlags = bFlags;
	gUserPicNum++;

	hPicture |= gUserPicNum - 1;	// ハンドル生成

	return hPicture;
}

// 2Dグラフィックロード
int LoadTexture(char *szFileName) {
	LPDIRECT3DTEXTURE9		ppbPicture;
	TEX_2DPIC_INFO			piPicInfo;
	TEX_UNIT_PICTURE		*pUnitPic;		// 単位ピクチャ
	int						hPicture;		// ピクチャハンドル

	ppbPicture = Load2DGraph(szFileName, &piPicInfo);	// グラフィックロード
	
	pUnitPic = MakeUnitPicture(ppbPicture, &piPicInfo, szFileName);	// 単位ピクチャ登録

	hPicture = Make2DHandle(pUnitPic, 0, 0, piPicInfo.nWidth, piPicInfo.nHeight, 0);	// ハンドル作成

	return hPicture;
}

/**
 * ブロック化2Dグラフィックロード
 */
static int LoadBlockedTexture(char *szFileName, int nXSize, int nYSize,
	int nXNum, int nYNum, int nAllNum, int *phHandleBuf, int bFlags)
{
	int	i, j;
	int	x, y;		// ブロックの左上座標
	int	nBlockNum;	// ブロック数
	LPDIRECT3DTEXTURE9		ppbPicture;
	TEX_2DPIC_INFO			piPicInfo;
	TEX_UNIT_PICTURE		*pUnitPic;	// 単位ピクチャ

	ppbPicture = Load2DGraph(szFileName, &piPicInfo);	// グラフィックロード
	
	pUnitPic = MakeUnitPicture(ppbPicture, &piPicInfo, szFileName);	// 単位ピクチャ登録

	nBlockNum = 0;	// 初期ブロック数
	y = 0;
	for (i = 0; i < nYNum; i++) {
		x = 0;
		for (j = 0; j < nXNum; j++) {
			// ブロックが絵の外に掛からない
			if (1) {
				*(phHandleBuf + nBlockNum) = Make2DHandle(pUnitPic, x, y, nXSize, nYSize, 0);	// ハンドル作成
				nBlockNum++;
				if (bFlags & PICTURE_LR) {
					*(phHandleBuf + nBlockNum) = Make2DHandle(pUnitPic, x, y, nXSize, nYSize, PICTURE_LR);	// ハンドル作成
					nBlockNum++;
				}
			}
			// ブロックが絵の外に掛かる
			else {
				// 左右反転ありか
				if (bFlags & PICTURE_LR) {
					*(phHandleBuf + nBlockNum) = *(phHandleBuf + nBlockNum - 2);	// ふたつ前コピー
					*(phHandleBuf + nBlockNum + 1) = *(phHandleBuf + nBlockNum - 1);	// ふたつ前コピー
					nBlockNum += 2;
				}
				else {
					*(phHandleBuf + nBlockNum) = *(phHandleBuf + nBlockNum - 1);	// ひとつ前コピー
					nBlockNum++;
				}
			}
			// 規定数まで達していれば終了
			if ((!(bFlags & PICTURE_LR) && nBlockNum >= nAllNum) ||
				((bFlags & PICTURE_LR) && nBlockNum >= nAllNum * 2)) {
				break;
			}
			x += nXSize;
		}
		y += nYSize;
	}

	return OK;
}

/**
 * ブロック化2Dグラフィックロード(呼び出し用)
 */
int LoadBlkTexture(char *szFileName, int nXSize, int nYSize,
	int nXNum, int nYNum, int nAllNum, int *phHandleBuf) {
	return LoadBlockedTexture(szFileName, nXSize, nYSize,
		nXNum, nYNum, nAllNum, phHandleBuf, 0);
}

/**
 * 2Dグラフィック開放
 */
int Release2DGraphs(void) {
	int	i;

	// グラフィック開放
	for (i = 0; i < gUnitPicNum; i++) {
		SAFE_RELEASE(gUnitPictureBuf[i].pPicture);
	}

	// 定数リセット
	gUnitPicNum = 0;	// 単位ピクチャリセット
	gUserPicNum = 0;	// ユーザーピクチャリセット

	return OK;
}

static int BlendFactor;		// ブレンドファクタ

// 描画矩形用頂点
BOX_2DVERTEX	gDrawRect[4] = { {   0.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
								 { 640.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
								 {   0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f },
								 { 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f } };

BLEND_STATE		gBlendState;	// 現在のブレンドステート

/**
 * ブレンドファクタセット
 */
static void SetBlendFactor(int nBlendFactor) {
	int	i;

	// サチレーション
	if (nBlendFactor < 0) nBlendFactor = 0;
	if (nBlendFactor > MAX_BLEND_FACTOR) nBlendFactor = MAX_BLEND_FACTOR;

	gBlendState.nBlendFactor = nBlendFactor;	// ブレンドファクタ保存

	// 描画頂点セット
	for (i = 0; i < 4; i++) {
		gDrawRect[i].color = (gDrawRect[0].color & 0x00ffffff) | (nBlendFactor << 24);
	}

}

/**
 * ブレンドステート初期化
 */
int InitBlendState(void) {
	// アルファブレンドなし
	gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	gBlendState.nBlendMode = DRAW_NOBLEND;
	SetBlendFactor(MAX_BLEND_FACTOR);					// ブレンドファクタ最大
	gBlendState.nBrRed = 255;  gBlendState.nBrGreen = 255;  gBlendState.nBrBlue = 255;	// 描画色は白

	// 色制御
	gD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// アルファ制御
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// テクセルサンプラ設定
	gD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	gD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	// テクスチャクランプ
	gD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	gD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);


	return OK;
}

/**
 * 2Dグラフィック　テクスチャ座標計算
 */
static int Calc2DUVCoord(float *du1, float *dv1, float *du2, float *dv2,
	int sx1, int sy1, int sx2, int sy2,
	TEX_2DPIC_INFO *pPicInfo)
{
	// u方向
	// 左右反転なし
	if (sx1 <= sx2) {
		*du1 = (float)(sx1 + 0.5f) / pPicInfo->nRealWidth;
		*du2 = (float)(sx2 /* + 0.5f*/) / pPicInfo->nRealWidth;
	}
	// 左右反転あり
	else {
		*du1 = (float)(sx1 - 0.5f) / pPicInfo->nRealWidth;
		*du2 = (float)(sx2 /*  - 0.5f*/) / pPicInfo->nRealWidth;
	}

	// v方向
	// 左右反転なし
	if (sy1 <= sy2) {
		*dv1 = (float)(sy1 + 0.5f) / pPicInfo->nRealHeight;
		*dv2 = (float)(sy2 /*- 0.5f*/) / pPicInfo->nRealHeight;
	}
	// 左右反転あり
	else {
		*dv1 = (float)(sy1 - 0.5f) / pPicInfo->nRealHeight;
		*dv2 = (float)(sy2 /*- 0.5f*/) / pPicInfo->nRealHeight;
	}

	return OK;
}

/**
 * 2Dグラフィック描画（描画先２点、描画元２点指定）
 */
int Draw2DGraph(int dx1, int dy1, int dx2, int dy2,
	int sx1, int sy1, int sx2, int sy2,
	LPDIRECT3DTEXTURE9 pPicture, TEX_2DPIC_INFO *pPicInfo)
{
	float						tu1, tv1, tu2, tv2;

	Calc2DUVCoord(&tu1, &tv1, &tu2, &tv2, sx1, sy1, sx2, sy2, pPicInfo);
	gDrawRect[0].x = (float)dx1;  gDrawRect[0].y = (float)dy1;  gDrawRect[0].tu = tu1;  gDrawRect[0].tv = tv1;
	gDrawRect[1].x = (float)dx2;  gDrawRect[1].y = (float)dy1;  gDrawRect[1].tu = tu2;  gDrawRect[1].tv = tv1;
	gDrawRect[2].x = (float)dx1;  gDrawRect[2].y = (float)dy2;  gDrawRect[2].tu = tu1;  gDrawRect[2].tv = tv2;
	gDrawRect[3].x = (float)dx2;  gDrawRect[3].y = (float)dy2;  gDrawRect[3].tu = tu2;  gDrawRect[3].tv = tv2;
	gD3DDevice->SetTexture(0, pPicture);
	gD3DDevice->SetFVF(D3DFVF_2DTEX);
	gD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, gDrawRect, sizeof(BOX_2DVERTEX));

	return OK;
}

/**
 * 描画色セット
 */
int SetDrawColor(int nRed, int nGreen, int nBlue) {
	int							i;
	int							nCompositColor;	// 合成済みの色

	// サチレーション
	if (nRed < 0) nRed = 0;
	if (nRed > MAX_COLOR_FACTOR) nRed = MAX_COLOR_FACTOR;
	if (nGreen < 0) nGreen = 0;
	if (nGreen > MAX_COLOR_FACTOR) nGreen = MAX_COLOR_FACTOR;
	if (nBlue < 0) nBlue = 0;
	if (nBlue > MAX_COLOR_FACTOR) nBlue = MAX_COLOR_FACTOR;

	// 色情報保存
	gBlendState.nBrRed = nRed;
	gBlendState.nBrGreen = nGreen;
	gBlendState.nBrBlue = nBlue;

	nCompositColor = (nRed << 16) + (nGreen << 8) + nBlue;

	// 描画頂点セット
	for (i = 0; i < 4; i++) {
		gDrawRect[i].color = (gDrawRect[0].color & 0xff000000) | nCompositColor;
	}

	return OK;
}

/**
 * ブレンドステート取得
 */
int GetBlendState(BLEND_STATE *pbsBlendFactor) {
	*pbsBlendFactor = gBlendState;

	return OK;
}

/**
 * ブレンドモード設定
 */
int SetBlendState(int nBlendCode, int nBlendFactor) {
	// ブレンドなし
	if (nBlendCode == DRAW_NOBLEND) {
		if (gBlendState.nBlendMode != DRAW_NOBLEND) {
			gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			gBlendState.nBlendMode = DRAW_NOBLEND;
		}
		SetBlendFactor(255);	// ブレンドファクタ設定
	}

	// アルファブレンディング
	if (nBlendCode == DRAW_ALPHABLEND) {
		if (gBlendState.nBlendMode != DRAW_ALPHABLEND) {
			if (gBlendState.nBlendMode == DRAW_NOBLEND)
				gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// ブレンドＯＦＦならＯＮに
			gD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			gD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			gBlendState.nBlendMode = DRAW_ALPHABLEND;
		}
		SetBlendFactor(nBlendFactor);	// ブレンドファクタ設定
	}

	// 加算ブレンディング
	if (nBlendCode == DRAW_ADDBLEND) {
		if (gBlendState.nBlendMode != DRAW_ADDBLEND) {
			if (gBlendState.nBlendMode == DRAW_NOBLEND)
				gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// ブレンドＯＦＦならＯＮに
			gD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			gD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			gBlendState.nBlendMode = DRAW_ADDBLEND;
		}
		SetBlendFactor(nBlendFactor);	// ブレンドファクタ設定
	}

	return OK;
}

/**
 * ブレンドステート復帰
 */
int RestoreBlendState(BLEND_STATE *pbsRestoreBlend) {
	SetBlendState(pbsRestoreBlend->nBlendMode, pbsRestoreBlend->nBlendFactor);	// ブレンドファクタ設定
	// 必要なら色ファクタ設定
	if (gBlendState.nBrRed != pbsRestoreBlend->nBrRed ||
		gBlendState.nBrGreen != pbsRestoreBlend->nBrGreen ||
		gBlendState.nBrBlue != pbsRestoreBlend->nBrBlue)
	{
		SetDrawColor(pbsRestoreBlend->nBrRed, pbsRestoreBlend->nBrGreen, pbsRestoreBlend->nBrBlue);
	}
	gBlendState = *pbsRestoreBlend;	// ブレンドステート保存

	return OK;
}

// 条件付き描画
static int DrawPictureCond(int dx1, int dy1, int dx2, int dy2,
	int sx1, int sy1, int sx2, int sy2,
	LPDIRECT3DTEXTURE9 pPicture, TEX_2DPIC_INFO *pPicInfo, int bConds)
{
	int	nResult;				// リザルトコード
	BLEND_STATE		bsBlendBuf;	// ブレンドステート退避場所

	// 絵のアルファ値考慮か
	if (bConds & (DRAWPIC_PICALPHA | DRAWPIC_AVEALPHA | DRAWPIC_ADDALPHA)) {
		GetBlendState(&bsBlendBuf);	// ブレンドステート取得
		if (bConds & DRAWPIC_ADDALPHA) {
			if (bConds & DRAWPIC_AVEALPHA) {
				SetBlendState(DRAW_ADDBLEND, MAX_BLEND_FACTOR / 2);		// 加算ブレンド
			}
			else {
				SetBlendState(DRAW_ADDBLEND, MAX_BLEND_FACTOR);			// 加算ブレンド
			}
		}
		else {
			if (bConds & DRAWPIC_AVEALPHA) {
				SetBlendState(DRAW_ALPHABLEND, MAX_BLEND_FACTOR / 2);		// アルファブレンド
			}
			else {
				SetBlendState(DRAW_ALPHABLEND, bsBlendBuf.nBlendFactor);	// アルファブレンド
			}
		}
	}

	// 実描画
	nResult = Draw2DGraph(dx1, dy1, dx2, dy2,
		sx1, sy1, sx2, sy2,
		pPicture, pPicInfo);

	// 絵のアルファ値考慮か
	if (bConds & (DRAWPIC_PICALPHA | DRAWPIC_AVEALPHA | DRAWPIC_ADDALPHA)) {
		RestoreBlendState(&bsBlendBuf);					// ブレンドステート復帰
	}

	return nResult;
}

/**
 * 描画モードの設定
 */
int SetDrawMode(int nDrawMode, int nParam) {
	// ブレンドモード
	if (nDrawMode & DRAW_NOBLEND) {							// ブレンドなし
		SetBlendState(DRAW_NOBLEND, 0);
	}
	if (nDrawMode & DRAW_ALPHABLEND) {						// アルファブレンディング
		SetBlendState(DRAW_ALPHABLEND, nParam);
	}
	if (nDrawMode & DRAW_ADDBLEND) {						// 加算ブレンディング
		SetBlendState(DRAW_ADDBLEND, nParam);
	}

	return OK;
}

/**
 * 2D描画
 * @parme x x座標
 * @parme y y座標
 * @parme hPicture 描画画像
 */
int DrawMem(int x, int y, int hPicture) {
	int	nResult;					// リザルトコード
	int	nUserPicLoc;				// ユーザー絵位置
	TEX_USER_PICTURE *pupUserPic;	// ユーザー絵
	int	bDrawConds = 0;				// 描画条件

	nUserPicLoc = hPicture & ~HANDLE_HEAD_MASK;	// 位置

	pupUserPic = &gUserPictureBuf[nUserPicLoc];

	nResult = DrawPictureCond(x, y, x + pupUserPic->nWidth, y + pupUserPic->nHeight,
		pupUserPic->nLeft, pupUserPic->nTop,
		pupUserPic->nLeft + pupUserPic->nWidth, pupUserPic->nTop + pupUserPic->nHeight,
		pupUserPic->pUnitPic->pPicture, &(pupUserPic->pUnitPic->a2PicInfo), bDrawConds);

	return nResult;
}

/**
 * アルファブレンド付き2D描画
 * @parme x x座標
 * @parme y y座標
 * @parme hPicture 描画画像
 */
int DrawMemTh(int x, int y, int hPicture) {
	int	nResult;						// リザルトコード
	int	nUserPicLoc;					// ユーザー絵位置
	TEX_USER_PICTURE *pupUserPic;		// ユーザー絵
	int	bDrawConds = DRAWPIC_PICALPHA;	// 描画条件

	nUserPicLoc = hPicture & ~HANDLE_HEAD_MASK;	// 位置

	pupUserPic = &gUserPictureBuf[nUserPicLoc];

	nResult = DrawPictureCond(x, y, x + pupUserPic->nWidth, y + pupUserPic->nHeight,
		pupUserPic->nLeft, pupUserPic->nTop,
		pupUserPic->nLeft + pupUserPic->nWidth, pupUserPic->nTop + pupUserPic->nHeight,
		pupUserPic->pUnitPic->pPicture, &(pupUserPic->pUnitPic->a2PicInfo), bDrawConds);

	return nResult;
}

/**
 * バックバッファのクリア
 */
int ClearBackBuffer(int r, int g, int b) {
	gD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(r, g, b), 1.0f, 0);

	return OK;
}

/**
 * 画面クリア
 */
int HCls(void) {
	int	nResult;	// リザルトコード

	nResult = ClearBackBuffer(0, 0, 0);	// 画面更新処理

	return nResult;
}

/**
 * 画面更新処理
 */
int Flip(void) {
	int	nResult;	// リザルトコード

	nResult = DispFlip();	// 画面更新処理

	fg_nFrameCount++;

	return nResult;
}

POINTVERTEX	gPointBuf[MAX_POINT_NUM];	// ポイントバッファ

/**
 * 色の掛け算計算
 */
static int GetModulateColor(int nColor1, int nColor2) {
	int	nAlpha, nRed, nGreen, nBlue;

	nAlpha = (((nColor1 >> 24) & 0xff) * ((nColor2 >> 24) & 0xff)) / 0xff;
	nRed = (((nColor1 >> 16) & 0xff) * ((nColor2 >> 16) & 0xff)) / 0xff;
	nGreen = (((nColor1 >> 8) & 0xff) * ((nColor2 >> 8) & 0xff)) / 0xff;
	nBlue = (((nColor1) & 0xff) * ((nColor2) & 0xff)) / 0xff;

	return (nAlpha << 24) + (nRed << 16) + (nGreen << 8) + (nBlue);
}

/**
 * 長方形の描画
 */
int DrawRectangleArray(POINT_DATA *papPoints, int nRectNum) {
	int	i;
	int	nResult = OK;
	POINT_DATA *pPresPoint;	// 現在の点

	if (nRectNum > MAX_RECT_NUM) {
		nRectNum = MAX_RECT_NUM;
		nResult = BOXERROR;
	}

	gD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);	// ディフューズ色のみ
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);	// ディフューズアルファのみ

	pPresPoint = papPoints;
	for (i = 0; i < nRectNum; i++) {
		// 左上
		gPointBuf[0].x = (float)pPresPoint->x;
		gPointBuf[0].y = (float)pPresPoint->y;
		gPointBuf[0].z = (float)pPresPoint->z;
		gPointBuf[0].rhw = 1.0f;
		gPointBuf[0].color = GetModulateColor(pPresPoint->nColor, gDrawRect[0].color);

		// 右上
		gPointBuf[1] = gPointBuf[0];
		gPointBuf[1].x = (float)(pPresPoint + 1)->x;

		// 左下
		gPointBuf[2].x = (float)pPresPoint->x;
		gPointBuf[2].y = (float)(pPresPoint + 1)->y;
		gPointBuf[2].z = (float)(pPresPoint + 1)->z;
		gPointBuf[2].rhw = 1.0f;
		gPointBuf[2].color = GetModulateColor((pPresPoint + 1)->nColor, gDrawRect[2].color);

		// 右下
		gPointBuf[3] = gPointBuf[2];
		gPointBuf[3].x = (float)(pPresPoint + 1)->x;

		// 描画
		gD3DDevice->SetFVF(D3DFVF_2DTEX);
		gD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, nRectNum * 2,
			gPointBuf, sizeof(POINTVERTEX));

		pPresPoint += 2;
	}

	gD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	// テクスチャ色も復帰
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// テクスチャアルファも復帰

	return nResult;
}

/**
 * 長方形の描画
 * @parme x1 右上x座標
 * @parme y1 右上y座標
 * @parme x2 左下x座標
 * @parme y2 左下y座標
 * @parme color 色コード
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color) {
	POINT_DATA apRectPoint[2];	// 左上・右下の点

	// 左上
	apRectPoint[0].x = x1;  apRectPoint[0].y = y1;  apRectPoint[0].z = 0;
	apRectPoint[0].nColor = color;

	// 右下
	apRectPoint[1].x = x2;  apRectPoint[1].y = y2;  apRectPoint[1].z = 0;
	apRectPoint[1].nColor = color;

	DrawRectangleArray(apRectPoint, 1);	// 描画

	return;
}



/**
 * FPS用グローバル変数
 */
int gFpsCount = 0;

/**
 * FPS処理
 */
void fps() {
	int i;
	int t = 0, ave = 0, f[MAX_FPS];

	gFpsCount++;

	f[gFpsCount % MAX_FPS] = timeGetTime() - t;
	t = timeGetTime();
	if (gFpsCount % MAX_FPS == MAX_FPS - 1) {
		ave = 0;
		for (i = 0; i < MAX_FPS; i++)
			ave += f[i];
		ave /= MAX_FPS;
	}
#ifdef DRAW_FPS
	if (ave != 0) {
		DrawString(0, 0, GetColor(NULL, 255, 255, 255), "%.1fFPS", 1000.0 / (double)ave);
		DrawString(0, 20, GetColor(NULL, 255, 255, 255), "%dms", ave);
	}
#endif // DRAW_FPS

	return;
}

/**
 * FPSを一定にする
 */
void wait_fanc() {
	int term, onefps;
	static int t = 0;
	onefps = (1 * 1000) / MAX_FPS;
	term = timeGetTime() - t;
	if (onefps - term > 0) { Sleep(onefps - term); }
	t = timeGetTime();
	return;
}
