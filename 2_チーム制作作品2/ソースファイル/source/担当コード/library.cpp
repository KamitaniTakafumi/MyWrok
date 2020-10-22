/*
 * @file library.cpp
 * @brief ���C�u��������
 * @author ��J���j
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
*	DirectX�p���֐��G�C���A�X��`
*/
int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;
int (WINAPIV * _sscanf)(const char*, const char*, ...) = sscanf;
int (WINAPIV * __snprintf)(char *, size_t, const char*, ...) = _snprintf;
int (WINAPIV * _sprintf)(char*, const char*, ...) = sprintf;

static HWND		hWnd;
LPDIRECT3D9				lpD3D;
D3DPRESENT_PARAMETERS	d3dpp;

/*
*	�X�N���[���p�����[�^
*/
D3DFORMAT	gScreenFormat;
int			gScreenWidth;
int			gScreenHeight;

/*
*	�R�c�f�o�C�X
*/
IDirect3DDevice9*	gDevice;
HWND				gWindow;

/*
 * ������
 */
bool InitD3D(HWND hWnd, bool bFullScreen)
{
	//	�X�N���[���T�C�Y�擾
	int	Width = 1280;
	int	Height = 720;

	// D3D�I�u�W�F�N�g�̍쐬
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// �A�_�v�^�̌��݂̃f�B�X�v���C ���[�h���擾����
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

	//	�f�o�C�X�쐬
	if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &gDevice))) {
		if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &gDevice))) {
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &gDevice))) {
				if (FAILED(lpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &gDevice))) {
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					return false;
				}
			}
		}
	}

	//	�O���[�o���p�����[�^�ݒ�
	gScreenFormat = d3dpp.BackBufferFormat;
	gScreenWidth = d3dpp.BackBufferWidth;
	gScreenHeight = d3dpp.BackBufferHeight;

	gWindow = hWnd;

	return true;
}

/*
 * �f�o�C�X�J��
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
*	Window�쐬
*/

// �E�C���h�E�n���h��
HWND gWindowHandle = NULL;

BOOL gFullScreen = TRUE;

/*
* �E�B���h�E�v���V�[�W��
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
* �E�C���h�E�쐬
* @param hInst �C���X�^���X�n���h��
* @param disp_w, disp_h ��ʃT�C�Y
* @param WindowName �E�C���h�E�̖��O
*/
void InitWnd(HINSTANCE hInst, int disp_w, int disp_h, LPSTR WindowName) {
	// �E�B���h�E�̏�����
	WNDCLASSEX wndclass;

	// �\���̃T�C�Y
	wndclass.cbSize = sizeof(wndclass);

	/** �E�C���h�E�X�^�C��
	 CS_HREDRAW	���T�C�Y���ς�����Ƃ��ɃE�C���h�E�S�̂��ĕ`��
	 CS_VREDRAW	�c�T�C�Y��...
	 */
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc = WindowProc;										// �R�[���o�b�N�֐��ւ̃|�C���^
	wndclass.cbClsExtra = 0;												// �N���X�\���̌��̕⑫�o�C�g��
	wndclass.cbWndExtra = 0;												// �C���X�^���X���̕⑫�o�C�g��
	wndclass.hInstance = hInst;												// �E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);						// �A�C�R���n���h��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);							// �}�E�X�J�[�\���n���h��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);			// �E�C���h�E�w�i�F(��)
	wndclass.lpszMenuName = NULL;											// �f�t�H���g���j���[��
	wndclass.lpszClassName = WindowName;										// ���̃E�C���h�E�N���X�̖��O
	wndclass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);						// 16*16�̏��A�C�R��
	// �E�C���h�E�N���X�o�^
	RegisterClassEx(&wndclass);

	// �E�C���h�E�쐬
	if (gFullScreen) {
		gWindowHandle = CreateWindow(WindowName,				// �o�^�����N���X�̖��O 
			WindowName,				// �^�C�g���o�[�ɕ\�����镶����
			WS_VISIBLE | WS_POPUP,	// �E�C���h�E�X�^�C��
			0, 0,					// �E�C���h�E���W
			disp_w, disp_h,			// �E�C���h�E�T�C�Y
			NULL,					// �e�E�C���h�E�̃n���h��
			NULL,					// ���j���[�n���h��(�f�t�H�g���Ȃ�NULL)
			hInst,					// �E�C���h�E�Ƃ����쐬���郂�W���[���̃C���X�^���X�n���h��
			NULL);					// WM_CREATE��LPARAM�ɓn�������l(��������NULL)
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

	// �E�C���h�E�̕\����Ԃ̐ݒ�
	ShowWindow(gWindowHandle, SW_SHOW);
	UpdateWindow(gWindowHandle);
}

/*
 * �A�v���P�[�V����������
 */
bool InitApp()
{
	if (!InitD3D(gWindowHandle, gFullScreen)) { return false; }

	// ���C���t���[�����[�N������
	InitFramework(FPS_FLEX);

	// �f�o�C�X�̊��ݒ�
	InitDevice();

	if (!DSoundInit(gWindow, NULL)) {
		MessageBox(gWindow, "�T�E���h�̏������Ɏ��s���܂���", "error", MB_OK);
	}

	return true;
}


int	gJoyPadNum = -1;				// �W���C�p�b�h��
int	gMouseCursor = false;		// �}�E�X�J�[�\��

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

JOYPAD	gJoyPads[MAX_JOYSTICK_COUNT];		// �W���C�p�b�h
UINT	gPadIDs[MAX_JOYSTICK_COUNT] = { JOYSTICKID1, JOYSTICKID2, JOYSTICKID3, JOYSTICKID4 };

/**
 *  �P�̃p�b�h���͕t��
 */
extern int AddJoyInput(int nPadIndex, int nKeyState)
{
	JOYPAD						*pJoyPad;						// �p�b�h
	JOYINFOEX					jJoyInfo;						// �p�b�h���

	// �l�`�F�b�N�ƃp�b�h�擾
	if (nPadIndex < 0 || nPadIndex >= gJoyPadNum) return ERR_NOHARDWARE;
	pJoyPad = &gJoyPads[nPadIndex];

	if (pJoyPad->bValid)
	{									// �L����
		jJoyInfo.dwSize = sizeof(jJoyInfo);					// Joy�\���̃Z�b�g
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


// �L�[��������Ă��邩�`�F�b�N
int CheckKey(int nInputMode)
{
	int							i;
	int							nResult = 0;

	switch (nInputMode) {
		// �}���`�v������
	case INPUT_MULT:

		for (i = 0; i < gJoyPadNum; i++) {					// �p�b�h����
			nResult = AddJoyInput(i, nResult);
		}
		break;

			// �p�b�h1����
	case INPUT_PAD1:
		nResult = AddJoyInput(0, 0);
		break;

		// �p�b�h2����
	case INPUT_PAD2:
		nResult = AddJoyInput(1, 0);
		break;

		// �p�b�h1����
	case INPUT_PAD3:
		nResult = AddJoyInput(2, 0);
		break;

		// �p�b�h2����
	case INPUT_PAD4:
		nResult = AddJoyInput(3, 0);
		break;

		// �s������
	default:
		nResult = ERR_PAD;
		break;
	}


	return nResult;
}


/**
 *  �P�̃W���C�p�b�h������
 */
static int InitSinglePad(UINT nJoyID, JOYPAD *pJoyPad)
{
	JOYCAPS						jCaps;
	JOYINFOEX					jJoyInfo;
	int							nResult = ERR_NOHARDWARE;

	pJoyPad->bValid = false;									// �����ɂ��Ă���
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
		jJoyInfo.dwSize = sizeof(jJoyInfo);					// Joy�\���̃Z�b�g
		jJoyInfo.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(pJoyPad->uJoyID, &jJoyInfo) == JOYERR_NOERROR)
		{
			pJoyPad->bValid = TRUE;								// �p�b�h�L����
			nResult = OK;
		}
	}

	return nResult;
}

/**
 *  �p�b�h�g�p�I��
 */
int EndJoyPad(void)
{
	return OK;
}

/*
* �p�b�h������
* @param nMaxPadNum �p�b�h�̍ő吔
*/
int InitJoyPad(int nMaxPadNum)
{
	int							i;
	int							nActivePadNum = 0;				// �A�N�e�B�u�ȃp�b�h��
	int							nResult;

	if (nMaxPadNum > MAX_JOYSTICK_COUNT) nMaxPadNum = MAX_JOYSTICK_COUNT;
	for (i = 0; i < nMaxPadNum; i++)
	{
		nResult = InitSinglePad(gPadIDs[i], &gJoyPads[i]);	// �p�b�h������
		if (nResult != OK) break;							// ������ΏI��
		nActivePadNum++;
	}

	gJoyPadNum = nActivePadNum;								// �p�b�h���o�^

	return nActivePadNum;
}

/**
 *  1P�`4P�܂ł̃L�[���͎擾
 */
void InKey()
{
	gKeyold1 = gKey1;
	gKey1 = CheckKey(INPUT_PAD1);						//�L�[���͎擾
	gTrg1 = (gKey1 ^ gKeyold1)& gKey1;				//�g���K�[�L�[���͎擾

	gKeyold2 = gKey2;
	gKey2 = CheckKey(INPUT_PAD2);						//�L�[���͎擾
	gTrg2 = (gKey2 ^ gKeyold2)& gKey2;				//�g���K�[�L�[���͎擾

	gKeyold3 = gKey3;
	gKey3 = CheckKey(INPUT_PAD3);						//�L�[���͎擾
	gTrg3 = (gKey3 ^ gKeyold3)& gKey3;				//�g���K�[�L�[���͎擾

	gKeyold4 = gKey4;
	gKey4 = CheckKey(INPUT_PAD4);						//�L�[���͎擾
	gTrg4 = (gKey4 ^ gKeyold4)& gKey4;				//�g���K�[�L�[���͎擾
}

/*
 * �R���g���[���[���ڑ�����Ă��邩�̊m�F
 */
bool ConnectionPad()
{
	if (InitJoyPad(MAX_JOYSTICK_COUNT) <= 0)
	{
		int flag;
		flag = MessageBox(NULL, "�R���g���[���[��1�ȏ㌩����܂���\n�N�����܂����H", "�R���g���[���[�ݒ�", MB_YESNO);
		if (flag == IDNO)
		{
			return false;
		}
	}
	return true;
}



LPD3DXFONT	d3dFont = NULL;
int			gStringFontSize = -1;				// ������t�H���g�T�C�Y

/**
 *�@������g�p������
 */
int InitFont() {
	//�����񃌃��_�����O�̏�����
	if (FAILED(D3DXCreateFont(gDevice, 0, 10, FW_REGULAR, NULL, false, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "�l�r �S�V�b�N", &d3dFont))) {
		return E_FAIL;
	}

	return S_OK;
}

/*
 * ������̊J��
 */
void	ReleaseFont()
{
	d3dFont->Release();
}

/**
 *�@�F�R�[�h�̊l��
 *�@@param	alpha	�A���t�@�l�ANULL������Ǝ����I��255�ɂȂ�
 *�@@param	red		�Ԃ̒l
 *�@@param	green	�΂̒l
 *�@@param	blue	�̒l
 *�@@return	�F�R�[�h��Ԃ�
 */
DWORD GetColor(int alpha, int red, int green, int blue) {
	// �K�萔�ȏ�or�K�萔�����Ȃ�Ζ߂�
	if (alpha == NULL) { alpha = 255; }
	if (alpha < 0) alpha = 0;  else if (alpha > 255) alpha = 255;
	if (red < 0) red = 0;  else if (red > 255) red = 255;
	if (green < 0) green = 0;  else if (green > 255) green = 255;
	if (blue < 0) blue = 0;  else if (blue > 255) blue = 255;

	return D3DCOLOR_ARGB(alpha, red, green, blue);
}

/**
 *�@������`��
 *�@@param	x,y		�`����W
 *�@@param	color	�F�R�[�h
 *�@@param	fmt		������
 *�@@param	...		(����Ȃ�)�\���������ϐ��Ȃ�
 */
void DrawString(float x, float y, int color, const char *fmt, ...) {
	int strlength;		// ������̒������i�[
	char sz[0xffff];	// �i�[�T�C�Y�B������ꂽ���肪�o��B

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
 * 2D�O���t�B�b�N���[�h
 */
KT_2DPIC_INFO CreateTexture(const char *szFileName)
{
	D3DXIMAGE_INFO				iiImageInfo;
	LPDIRECT3DSURFACE9			lpTopSurf;
	D3DSURFACE_DESC				ddSurfInfo;
	D3DCOLOR					nColorKey;						// �J���[�L�[
	KT_2DPIC_INFO				texture = { 0 };

	// �J���[�L�[����
	if (strstr(szFileName, ".bmp") || strstr(szFileName, ".BMP")) {	// �r�b�g�}�b�v�̏ꍇ
		nColorKey = 0xff000000;												// �r�b�g�}�b�v�Ȃ�J���[�L�[����
	}
	else {
		nColorKey = 0;														// �r�b�g�}�b�v�ȊO�Ȃ�J���[�L�[�Ȃ�
	}

	// �e�N�X�`�����[�h
	texture.hRes = D3DXCreateTextureFromFileEx(gDevice, szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		nColorKey, &iiImageInfo, NULL, &texture.texture);

	if (FAILED(texture.hRes)) return texture;

	// �T�[�t�F�X���擾
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
 * �e�N�X�`���X�v���b�g�쐬
 */
bool CreateSprit()
{
	D3DXCreateSprite(gDevice, &gSprite);

	return true;
}

static int gBlendState;			//�`��u�����h���
static int BlendFactor;		// �u�����h�t�@�N�^
#define MAX_BLEND_FACTOR		255								// �u�����h�t�@�N�^�ő�l

// �`���`�p���_
extern AM_2DVERTEX				gg_v2DrawRect[4] = { {   0.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
													 { 640.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
													 {   0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f },
													 { 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f } };


/*
 * �u�����h�t�@�N�^�Z�b�g
 * @param nParam	���l
 */
static void SetBlendFactor(int nBlendFactor)
{
	int							i;

	// �T�`���[�V����
	if (nBlendFactor < 0) nBlendFactor = 0;
	if (nBlendFactor > MAX_BLEND_FACTOR) nBlendFactor = MAX_BLEND_FACTOR;

	BlendFactor = nBlendFactor;				// �u�����h�t�@�N�^�ۑ�

	// �`�撸�_�Z�b�g
	for (i = 0; i < 4; i++) {
		gg_v2DrawRect[i].color = (gg_v2DrawRect[0].color & 0x00ffffff) | (nBlendFactor << 24);
	}

}

/**
 * �u�����h���[�h�ݒ�
 * @param blend_code �u�����h�R�[�h
 * @param nParam	���l
 */
void SetBlendState(int blend_code, int nBlendFactor) {
	if (blend_code == DRAW_NOBLEND)//�u�����h�Ȃ�/�f�t�H���g
	{
		gDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		SetBlendFactor(255);						// �u�����h�t�@�N�^�ݒ�
	}

	if (blend_code == DRAW_ALPHABLEND)//�A���t�@�u�����h
	{
		gDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		gDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		gDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		SetBlendFactor(nBlendFactor);						// �u�����h�t�@�N�^�ݒ�
	}

	if (blend_code == DRAW_ADDBLEND)//���Z�u�����h
	{
		gDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		gDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		gDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		SetBlendFactor(nBlendFactor);						// �u�����h�t�@�N�^�ݒ�
	}

}

/**
 * �`�惂�[�h�ݒ�
 * @param draw_mode �`�惂�[�h
 * @param nParam	���l
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
 * �e�N�X�`���`��
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
 * �����[�X�X�v���b�g
 */
void RereaseSprit(IDirect3DTexture9* tex)
{
	if (tex != NULL)
		tex->Release();

	if (gSprite != NULL)
		gSprite->Release();

}

// �_�f�[�^
struct POINT_DATA {
	int							x, y, z;						// ���W
	unsigned int				nColor;							// �F
};

// 2D���_�\����
struct POINTVERTEX {
	float				x, y, z, rhw;							// ���_���W
	int					color;									// ���_�F
};

#define D3DFVF_AMPOINT			( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )	// 2D�e�N�X�`�����_�t�H�[�}�b�g

// �o�b�t�@�֌W
POINTVERTEX					fg_apPointBuf[MAX_POINT_NUM];	// �|�C���g�o�b�t�@

/*
 * �F�̊|���Z�v�Z
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
 * �����`�̕`��
 */
extern int DrawRectangleArray(POINT_DATA *papPoints, int nRectNum)
{
	int							i;
	int							nResult = OK;
	POINT_DATA				*pPresPoint;					// ���݂̓_

	if (nRectNum > AM_MAX_RECT_NUM) {
		nRectNum = AM_MAX_RECT_NUM;
		nResult = ERRORCODE;
	}

	gDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);	// �f�B�t���[�Y�F�̂�
	gDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);	// �f�B�t���[�Y�A���t�@�̂�

	pPresPoint = papPoints;
	for (i = 0; i < nRectNum; i++) {
		// ����
		fg_apPointBuf[0].x = (float)pPresPoint->x;
		fg_apPointBuf[0].y = (float)pPresPoint->y;
		fg_apPointBuf[0].z = (float)pPresPoint->z;
		fg_apPointBuf[0].rhw = 1.0f;
		fg_apPointBuf[0].color = GetModulateColor(pPresPoint->nColor, gg_v2DrawRect[0].color);

		// �E��
		fg_apPointBuf[1] = fg_apPointBuf[0];
		fg_apPointBuf[1].x = (float)(pPresPoint + 1)->x;

		// ����
		fg_apPointBuf[2].x = (float)pPresPoint->x;
		fg_apPointBuf[2].y = (float)(pPresPoint + 1)->y;
		fg_apPointBuf[2].z = (float)(pPresPoint + 1)->z;
		fg_apPointBuf[2].rhw = 1.0f;
		fg_apPointBuf[2].color = GetModulateColor((pPresPoint + 1)->nColor, gg_v2DrawRect[2].color);

		// �E��
		fg_apPointBuf[3] = fg_apPointBuf[2];
		fg_apPointBuf[3].x = (float)(pPresPoint + 1)->x;

		// �`��
		gDevice->SetFVF(D3DFVF_AMPOINT);
		gDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, nRectNum * 2,
			fg_apPointBuf, sizeof(POINTVERTEX));

		pPresPoint += 2;
	}

	gDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	// �e�N�X�`���F�����A
	gDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �e�N�X�`���A���t�@�����A

	return nResult;
}

/*
 * �����`�̕`��
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color)
{
	POINT_DATA				apRectPoint[2];					// ����E�E���̓_

	// ����
	apRectPoint[0].x = x1;  apRectPoint[0].y = y1;  apRectPoint[0].z = 0;
	apRectPoint[0].nColor = color;

	// �E��
	apRectPoint[1].x = x2;  apRectPoint[1].y = y2;  apRectPoint[1].z = 0;
	apRectPoint[1].nColor = color;

	DrawRectangleArray(apRectPoint, 1);					// �`��

	return;
}
