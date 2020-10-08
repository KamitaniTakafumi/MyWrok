/*
 * @file library.cpp
 * @brief ライブラリ処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "FbxMesh.h"
#include "Framework.h"
#include "SceneMain.h"
#include "dslib.h"

#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment(lib, "dinput8.lib")

/*
*	DirectX用旧関数エイリアス定義
*/
int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;
int (WINAPIV * _sscanf)(const char*, const char*, ...) = sscanf;
int (WINAPIV * __snprintf)(char *, size_t, const char*, ...) = _snprintf;
int (WINAPIV * _sprintf)(char*, const char*, ...) = sprintf;

static HWND		hWnd;
LPDIRECT3D9				lpD3D;
D3DPRESENT_PARAMETERS	d3dpp;

/*
*	スクリーンパラメータ
*/
D3DFORMAT	gScreenFormat;
int			gScreenWidth;
int			gScreenHeight;

/*
*	３Ｄデバイス
*/
IDirect3DDevice9*	gDevice;
HWND				gWindow;

/*
 * 初期化
 */
bool InitD3D(HWND hWnd, bool bFullScreen)
{
	//	スクリーンサイズ取得
	int	Width = 1280;
	int	Height = 720;

	// D3Dオブジェクトの作成
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// アダプタの現在のディスプレイ モードを取得する
	D3DDISPLAYMODE d3ddm;
	lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

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

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Flags = 0;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferCount = 1;

	d3dpp.hDeviceWindow = hWnd;

	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	if (bFullScreen) {
		d3dpp.Windowed = !bFullScreen;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = d3ddm.Format;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}
	else {
		d3dpp.Windowed = true;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}

	//	デバイス作成
	if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &gDevice))) {
		if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &gDevice))) {
			MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
			if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &gDevice))) {
				if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &gDevice))) {
					MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
					return false;
				}
			}
		}
	}

	//	グローバルパラメータ設定
	gScreenFormat = d3dpp.BackBufferFormat;
	gScreenWidth = d3dpp.BackBufferWidth;
	gScreenHeight = d3dpp.BackBufferHeight;

	gWindow = hWnd;

	return true;
}

/*
 * デバイス開放
 */
void ReleaseD3D()
{
	gDevice->Release(); gDevice = NULL;
	lpD3D->Release(); lpD3D = NULL;
}

void BeginScene()
{
	gDevice->BeginScene();
}
void EndScene()
{
	gDevice->EndScene();
	if (FAILED(gDevice->Present(NULL, NULL, NULL, NULL))) gDevice->Reset(&d3dpp);
}


/*
*	Window作成
*/

// ウインドウハンドル
HWND gWindowHandle = NULL;

BOOL gFullScreen = TRUE;

/*
* ウィンドウプロシージャ
*/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY: PostQuitMessage(0); return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE: PostMessage(hWnd, WM_CLOSE, 0, 0); return 0;

		case WM_LBUTTONDOWN:
		{
			break;
		}
		case WM_RBUTTONDOWN:
		{
			break;
		}

		}

		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
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

/*
 * アプリケーション初期化
 */
bool InitApp()
{
	if (!InitD3D(gWindowHandle, gFullScreen)) { return false; }

	// メインフレームワーク初期化
	InitFramework(FPS_FLEX);

	// デバイスの環境設定
	InitDevice();

	if (!DSoundInit(gWindow, NULL)) {
		MessageBox(gWindow, "サウンドの初期化に失敗しました", "error", MB_OK);
	}

	return true;
}


int	gJoyPadNum = -1;				// ジョイパッド数
int	gMouseCursor = false;		// マウスカーソル

int gKeyold1;
int gKey1;
int gTrg1;

int gKeyold2;
int gKey2;
int gTrg2;

int gKeyold3;
int gKey3;
int gTrg3;

int gKeyold4;
int gKey4;
int gTrg4;

JOYPAD	gJoyPads[MAX_JOYSTICK_COUNT];		// ジョイパッド
UINT	gPadIDs[MAX_JOYSTICK_COUNT] = { JOYSTICKID1, JOYSTICKID2, JOYSTICKID3, JOYSTICKID4 };

/**
 *  単体パッド入力付加
 */
extern int AddJoyInput(int nPadIndex, int nKeyState)
{
	JOYPAD						*pJoyPad;						// パッド
	JOYINFOEX					jJoyInfo;						// パッド情報

	// 値チェックとパッド取得
	if (nPadIndex < 0 || nPadIndex >= gJoyPadNum) return ERR_NOHARDWARE;
	pJoyPad = &gJoyPads[nPadIndex];

	if (pJoyPad->bValid)
	{									// 有効か
		jJoyInfo.dwSize = sizeof(jJoyInfo);					// Joy構造体セット
		jJoyInfo.dwFlags = JOY_RETURNALL;
		jJoyInfo.dwXpos = pJoyPad->nCenterX;
		jJoyInfo.dwYpos = pJoyPad->nCenterY;
		jJoyInfo.dwButtons = 0;
		if (joyGetPosEx(pJoyPad->uJoyID, &jJoyInfo) == JOYERR_NOERROR)
		{
			if (jJoyInfo.dwYpos > pJoyPad->nBottom) nKeyState |= KEYIN_2;
			if (jJoyInfo.dwXpos < pJoyPad->nLeft) nKeyState |= KEYIN_4;
			if (jJoyInfo.dwXpos > pJoyPad->nRight) nKeyState |= KEYIN_6;
			if (jJoyInfo.dwYpos < pJoyPad->nTop) nKeyState |= KEYIN_8;
			nKeyState |= (jJoyInfo.dwButtons & 0xff) << 8;
			if (jJoyInfo.dwButtons & 0x100) nKeyState |= KEYIN_ESC;
			if (jJoyInfo.dwButtons & 0x200) nKeyState |= KEYIN_SPC;
		}
	}
	return nKeyState;
}


// キーが押されているかチェック
int CheckKey(int nInputMode)
{
	int							i;
	int							nResult = 0;

	switch (nInputMode) {
		// マルチプル入力
	case INPUT_MULT:

		for (i = 0; i < gJoyPadNum; i++) {					// パッド入力
			nResult = AddJoyInput(i, nResult);
		}
		break;

			// パッド1入力
	case INPUT_PAD1:
		nResult = AddJoyInput(0, 0);
		break;

		// パッド2入力
	case INPUT_PAD2:
		nResult = AddJoyInput(1, 0);
		break;

		// パッド1入力
	case INPUT_PAD3:
		nResult = AddJoyInput(2, 0);
		break;

		// パッド2入力
	case INPUT_PAD4:
		nResult = AddJoyInput(3, 0);
		break;

		// 不正入力
	default:
		nResult = ERR_PAD;
		break;
	}


	return nResult;
}


/**
 *  単体ジョイパッド初期化
 */
static int InitSinglePad(UINT nJoyID, JOYPAD *pJoyPad)
{
	JOYCAPS						jCaps;
	JOYINFOEX					jJoyInfo;
	int							nResult = ERR_NOHARDWARE;

	pJoyPad->bValid = false;									// 無効にしておく
	if (joyGetDevCaps(nJoyID, &jCaps, sizeof(jCaps))
		== JOYERR_NOERROR)
	{
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
		if (joyGetPosEx(pJoyPad->uJoyID, &jJoyInfo) == JOYERR_NOERROR)
		{
			pJoyPad->bValid = TRUE;								// パッド有効に
			nResult = OK;
		}
	}

	return nResult;
}

/**
 *  パッド使用終了
 */
int EndJoyPad(void)
{
	return OK;
}

/*
* パッド初期化
* @param nMaxPadNum パッドの最大数
*/
int InitJoyPad(int nMaxPadNum)
{
	int							i;
	int							nActivePadNum = 0;				// アクティブなパッド数
	int							nResult;

	if (nMaxPadNum > MAX_JOYSTICK_COUNT) nMaxPadNum = MAX_JOYSTICK_COUNT;
	for (i = 0; i < nMaxPadNum; i++)
	{
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
	gKeyold1 = gKey1;
	gKey1 = CheckKey(INPUT_PAD1);						//キー入力取得
	gTrg1 = (gKey1 ^ gKeyold1)& gKey1;				//トリガーキー入力取得

	gKeyold2 = gKey2;
	gKey2 = CheckKey(INPUT_PAD2);						//キー入力取得
	gTrg2 = (gKey2 ^ gKeyold2)& gKey2;				//トリガーキー入力取得

	gKeyold3 = gKey3;
	gKey3 = CheckKey(INPUT_PAD3);						//キー入力取得
	gTrg3 = (gKey3 ^ gKeyold3)& gKey3;				//トリガーキー入力取得

	gKeyold4 = gKey4;
	gKey4 = CheckKey(INPUT_PAD4);						//キー入力取得
	gTrg4 = (gKey4 ^ gKeyold4)& gKey4;				//トリガーキー入力取得
}

/*
 * コントローラーが接続されているかの確認
 */
bool ConnectionPad()
{
	if (InitJoyPad(MAX_JOYSTICK_COUNT) <= 0)
	{
		int flag;
		flag = MessageBox(NULL, "コントローラーが1つ以上見つかりません\n起動しますか？", "コントローラー設定", MB_YESNO);
		if (flag == IDNO)
		{
			return false;
		}
	}
	return true;
}



LPD3DXFONT	d3dFont = NULL;
int			gStringFontSize = -1;				// 文字列フォントサイズ

/**
 *　文字列使用初期化
 */
int InitFont() {
	//文字列レンダリングの初期化
	if (FAILED(D3DXCreateFont(gDevice, 0, 10, FW_REGULAR, NULL, false, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &d3dFont))) {
		return E_FAIL;
	}

	return S_OK;
}

/*
 * 文字列の開放
 */
void	ReleaseFont()
{
	d3dFont->Release();
}

/**
 *　色コードの獲得
 *　@param	alpha	アルファ値、NULLを入れると自動的に255になる
 *　@param	red		赤の値
 *　@param	green	緑の値
 *　@param	blue	青の値
 *　@return	色コードを返す
 */
DWORD GetColor(int alpha, int red, int green, int blue) {
	// 規定数以上or規定数未満ならば戻す
	if (alpha == NULL) { alpha = 255; }
	if (alpha < 0) alpha = 0;  else if (alpha > 255) alpha = 255;
	if (red < 0) red = 0;  else if (red > 255) red = 255;
	if (green < 0) green = 0;  else if (green > 255) green = 255;
	if (blue < 0) blue = 0;  else if (blue > 255) blue = 255;

	return D3DCOLOR_ARGB(alpha, red, green, blue);
}

/**
 *　文字列描画
 *　@param	x,y		描画座標
 *　@param	color	色コード
 *　@param	fmt		文字列
 *　@param	...		(あるなら)表示したい変数など
 */
void DrawString(float x, float y, int color, const char *fmt, ...) {
	int strlength;		// 文字列の長さを格納
	char sz[0xffff];	// 格納サイズ。もし溢れたら問題が出る。

	strlength = (int)strlen(fmt);
	va_list list;
	va_start(list, fmt);
	vsprintf(sz, fmt, list);
	va_end(list);

	RECT rect = { x, y, x + strlength * gStringFontSize, y + gStringFontSize };
	d3dFont->DrawText(NULL, sz, -1, &rect, DT_CALCRECT, NULL);
	d3dFont->DrawText(NULL, sz, -1, &rect, DT_LEFT | DT_BOTTOM, color);
}



/*
 * 2Dグラフィックロード
 */
KT_2DPIC_INFO CreateTexture(const char *szFileName)
{
	D3DXIMAGE_INFO				iiImageInfo;
	LPDIRECT3DSURFACE9			lpTopSurf;
	D3DSURFACE_DESC				ddSurfInfo;
	D3DCOLOR					nColorKey;						// カラーキー
	KT_2DPIC_INFO				texture = { 0 };

	// カラーキー処理
	if (strstr(szFileName, ".bmp") || strstr(szFileName, ".BMP")) {	// ビットマップの場合
		nColorKey = 0xff000000;												// ビットマップならカラーキーあり
	}
	else {
		nColorKey = 0;														// ビットマップ以外ならカラーキーなし
	}

	// テクスチャロード
	texture.hRes = D3DXCreateTextureFromFileEx(gDevice, szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		nColorKey, &iiImageInfo, NULL, &texture.texture);

	if (FAILED(texture.hRes)) return texture;

	// サーフェス情報取得
	texture.hRes = texture.texture->GetSurfaceLevel(0, &lpTopSurf);
	if (FAILED(texture.hRes)) return texture;
	lpTopSurf->GetDesc(&ddSurfInfo);
	lpTopSurf->Release();

	texture.nWidth = iiImageInfo.Width;
	texture.nHeight = iiImageInfo.Height;
	texture.nRealWidth = ddSurfInfo.Width;
	texture.nRealHeight = ddSurfInfo.Height;

	return texture;
}

LPD3DXSPRITE       gSprite = NULL;
RECT rc;
D3DXVECTOR3 Center, Position;

/*
 * テクスチャスプリット作成
 */
bool CreateSprit()
{
	D3DXCreateSprite(gDevice, &gSprite);

	return true;
}

static int gBlendState;			//描画ブレンド状態
static int BlendFactor;		// ブレンドファクタ
#define MAX_BLEND_FACTOR		255								// ブレンドファクタ最大値

// 描画矩形用頂点
extern AM_2DVERTEX				gg_v2DrawRect[4] = { {   0.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
													 { 640.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
													 {   0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f },
													 { 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f } };


/*
 * ブレンドファクタセット
 * @param nParam	α値
 */
static void SetBlendFactor(int nBlendFactor)
{
	int							i;

	// サチレーション
	if (nBlendFactor < 0) nBlendFactor = 0;
	if (nBlendFactor > MAX_BLEND_FACTOR) nBlendFactor = MAX_BLEND_FACTOR;

	BlendFactor = nBlendFactor;				// ブレンドファクタ保存

	// 描画頂点セット
	for (i = 0; i < 4; i++) {
		gg_v2DrawRect[i].color = (gg_v2DrawRect[0].color & 0x00ffffff) | (nBlendFactor << 24);
	}

}

/**
 * ブレンドモード設定
 * @param blend_code ブレンドコード
 * @param nParam	α値
 */
void SetBlendState(int blend_code, int nBlendFactor) {
	if (blend_code == DRAW_NOBLEND)//ブレンドなし/デフォルト
	{
		gDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		SetBlendFactor(255);						// ブレンドファクタ設定
	}

	if (blend_code == DRAW_ALPHABLEND)//アルファブレンド
	{
		gDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		gDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		gDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		SetBlendFactor(nBlendFactor);						// ブレンドファクタ設定
	}

	if (blend_code == DRAW_ADDBLEND)//加算ブレンド
	{
		gDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		gDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		gDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		SetBlendFactor(nBlendFactor);						// ブレンドファクタ設定
	}

}

/**
 * 描画モード設定
 * @param draw_mode 描画モード
 * @param nParam	α値
 */
void SetDrawMode(int draw_mode, int nParam) {
	if (draw_mode & DRAW_NOBLEND) {
		SetBlendState(DRAW_NOBLEND, nParam);
	}
	if (draw_mode & DRAW_ALPHABLEND) {
		SetBlendState(DRAW_ALPHABLEND, nParam);
	}
	if (draw_mode & DRAW_ADDBLEND) {
		SetBlendState(DRAW_ADDBLEND, nParam);
	}
}

/*
 * テクスチャ描画
 */
void DrawTexture(float x, float y, KT_2DPIC_INFO* pic, IDirect3DTexture9* tex, int draw_mode)
{
	gSprite->Begin(NULL);
	rc.left = 0;
	rc.top = 0;
	rc.right = pic->nWidth;
	rc.bottom = pic->nHeight;

	Center.x = 0;
	Center.y = 0;
	Position.x = x;
	Position.y = y;

	SetDrawMode(draw_mode, 255);
	gSprite->Draw(tex, &rc, &Center, &Position, D3DCOLOR_ARGB(255, 255, 255, 255));

	gSprite->End();
}

/*
 * リリーススプリット
 */
void RereaseSprit(IDirect3DTexture9* tex)
{
	if (tex != NULL)
		tex->Release();

	if (gSprite != NULL)
		gSprite->Release();

}

// 点データ
struct POINT_DATA {
	int							x, y, z;						// 座標
	unsigned int				nColor;							// 色
};

// 2D頂点構造体
struct POINTVERTEX {
	float				x, y, z, rhw;							// 頂点座標
	int					color;									// 頂点色
};

#define D3DFVF_AMPOINT			( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )	// 2Dテクスチャ頂点フォーマット

// バッファ関係
POINTVERTEX					fg_apPointBuf[MAX_POINT_NUM];	// ポイントバッファ

/*
 * 色の掛け算計算
 */
static int GetModulateColor(int nColor1, int nColor2)
{
	int				nAlpha, nRed, nGreen, nBlue;

	nAlpha = (((nColor1 >> 24) & 0xff) * ((nColor2 >> 24) & 0xff)) / 0xff;
	nRed = (((nColor1 >> 16) & 0xff) * ((nColor2 >> 16) & 0xff)) / 0xff;
	nGreen = (((nColor1 >> 8) & 0xff) * ((nColor2 >> 8) & 0xff)) / 0xff;
	nBlue = (((nColor1) & 0xff) * ((nColor2) & 0xff)) / 0xff;

	return (nAlpha << 24) + (nRed << 16) + (nGreen << 8) + (nBlue);
}

/*
 * 長方形の描画
 */
extern int DrawRectangleArray(POINT_DATA *papPoints, int nRectNum)
{
	int							i;
	int							nResult = OK;
	POINT_DATA				*pPresPoint;					// 現在の点

	if (nRectNum > AM_MAX_RECT_NUM) {
		nRectNum = AM_MAX_RECT_NUM;
		nResult = ERRORCODE;
	}

	gDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);	// ディフューズ色のみ
	gDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);	// ディフューズアルファのみ

	pPresPoint = papPoints;
	for (i = 0; i < nRectNum; i++) {
		// 左上
		fg_apPointBuf[0].x = (float)pPresPoint->x;
		fg_apPointBuf[0].y = (float)pPresPoint->y;
		fg_apPointBuf[0].z = (float)pPresPoint->z;
		fg_apPointBuf[0].rhw = 1.0f;
		fg_apPointBuf[0].color = GetModulateColor(pPresPoint->nColor, gg_v2DrawRect[0].color);

		// 右上
		fg_apPointBuf[1] = fg_apPointBuf[0];
		fg_apPointBuf[1].x = (float)(pPresPoint + 1)->x;

		// 左下
		fg_apPointBuf[2].x = (float)pPresPoint->x;
		fg_apPointBuf[2].y = (float)(pPresPoint + 1)->y;
		fg_apPointBuf[2].z = (float)(pPresPoint + 1)->z;
		fg_apPointBuf[2].rhw = 1.0f;
		fg_apPointBuf[2].color = GetModulateColor((pPresPoint + 1)->nColor, gg_v2DrawRect[2].color);

		// 右下
		fg_apPointBuf[3] = fg_apPointBuf[2];
		fg_apPointBuf[3].x = (float)(pPresPoint + 1)->x;

		// 描画
		gDevice->SetFVF(D3DFVF_AMPOINT);
		gDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, nRectNum * 2,
			fg_apPointBuf, sizeof(POINTVERTEX));

		pPresPoint += 2;
	}

	gDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	// テクスチャ色も復帰
	gDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// テクスチャアルファも復帰

	return nResult;
}

/*
 * 長方形の描画
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color)
{
	POINT_DATA				apRectPoint[2];					// 左上・右下の点

	// 左上
	apRectPoint[0].x = x1;  apRectPoint[0].y = y1;  apRectPoint[0].z = 0;
	apRectPoint[0].nColor = color;

	// 右下
	apRectPoint[1].x = x2;  apRectPoint[1].y = y2;  apRectPoint[1].z = 0;
	apRectPoint[1].nColor = color;

	DrawRectangleArray(apRectPoint, 1);					// 描画

	return;
}
