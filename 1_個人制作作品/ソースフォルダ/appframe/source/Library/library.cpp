/**
 * @file library.cpp
 * @brief ���C�u��������
 * @author ��J���j
 * @date 2020 / 08 / 25
 */

#include "library.h"

#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment(lib, "dinput8.lib")

/**
 * DirectX�p���֐��G�C���A�X��`
 */
int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;
int (WINAPIV * _sscanf)(const char*, const char*, ...) = sscanf;
int (WINAPIV * __snprintf)(char *, size_t, const char*, ...) = _snprintf;
int (WINAPIV * _sprintf)(char*, const char*, ...) = sprintf;

LPDIRECT3D9				glpD3D;
D3DPRESENT_PARAMETERS	gD3Dpp;

/**
 * �X�N���[���p�����[�^
 */
D3DFORMAT	gScreenFormat;
int			gScreenWidth;
int			gScreenHeight;

/**
 * �R�c�f�o�C�X
 */
IDirect3DDevice9*	gD3DDevice;

/**
 * �f�o�C�X������
 * @return �������ł����true�A�ł��Ȃ����false
 */
bool InitD3D(HWND hWnd, bool bFullScreen) {
	//	�X�N���[���T�C�Y�擾
	int	Width = 1280;
	int	Height = 720;

	// D3D�I�u�W�F�N�g�̍쐬
	glpD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// �A�_�v�^�̌��݂̃f�B�X�v���C ���[�h���擾����
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

	//	�f�o�C�X�쐬
	if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&gD3Dpp, &gD3DDevice))) 
	{
		if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&gD3Dpp, &gD3DDevice))) 
		{
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&gD3Dpp, &gD3DDevice))) 
			{
				if (FAILED(glpD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&gD3Dpp, &gD3DDevice))) 
				{
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					return false;
				}
			}
		}
	}

	//	�O���[�o���p�����[�^�ݒ�
	gScreenFormat = gD3Dpp.BackBufferFormat;
	gScreenWidth = gD3Dpp.BackBufferWidth;
	gScreenHeight = gD3Dpp.BackBufferHeight;

	return true;
}

/**
 * �f�o�C�X�J��
 */
void ReleaseD3D() {
	gD3DDevice->Release(); gD3DDevice = NULL;
	glpD3D->Release(); glpD3D = NULL;
}

/**
 * �V�[���J�n
 */
void BeginScene() {
	gD3DDevice->BeginScene();
}

/**
 * �V�[���I��
 */
void EndScene() {
	gD3DDevice->EndScene();
	if (FAILED(gD3DDevice->Present(NULL, NULL, NULL, NULL))) gD3DDevice->Reset(&gD3Dpp);
}


/**
 * Window�쐬
 */

// �E�C���h�E�n���h��
HWND gWindowHandle = NULL;

#ifdef _DEBUG
BOOL gFullScreen = FALSE;
#else
BOOL gFullScreen = TRUE;
#endif // _DEBUG

/**
 * �E�B���h�E�v���V�[�W��
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

// �v���Z�X����ϐ�
BOOL							gEndFlag = false;			// �I���t���O

BOOL							gSceneActive = false;		// �V�[���̓A�N�e�B�u��

/*
 * Windows�C�x���g����
 */
int ProcessEvent(void) {
	int					nEventCnt;
	MSG					msg;

	if (gEndFlag) return false;							// ���łɏI����

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
 * ��ʂ̍X�V
 */
int DispFlip(void) {
	D3DRASTER_STATUS			RasterData;

	if (gEndFlag) return DISPERROR;						// �I����

	gD3DDevice->EndScene();
	gSceneActive = false;

	// �E�B���h�E���[�h�Ȃ�VBlank�҂�
	if (!gFullScreen) {
		do {													// VBlank�ɂȂ�܂ő҂�
			if (!ProcessEvent()) break;					// �Ƃ肠�����C�x���g����
			gD3DDevice->GetRasterStatus(0, &RasterData);
		} while (!RasterData.InVBlank);
	}

	// �I����ĂȂ���Ε\��
	if (!gEndFlag) {
		gD3DDevice->Present(NULL, NULL, NULL, NULL);		// �o�b�N�o�b�t�@�̓��e��\��
		gD3DDevice->BeginScene();							// �V�[���J�n
		gSceneActive = true;
	}
	else { return DISPERROR; }

	return OK;
}

/**
 * �A�v���P�[�V����������
 */
bool InitApp() {
	if (!ConnectionPad()) { return false; }

	if (!InitD3D(gWindowHandle, gFullScreen)) { return false; }

	if (!InitFont()) { return false; }

	return true;
}



/**
 * �L�[���͕t��
 * @parme nKeyState �L�[���͏��
 */
int AddKeyInput(int nKeyState) {
	BYTE			cKeyBuf[256];

	GetKeyboardState(cKeyBuf);								// �L�[�{�[�h

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
 * �L�[����
 * @parme nPushKey �����ꂽ�L�[
 * @parme nJudgKey ���肵�����L�[
 */
bool KeyJudg(int nPushKey, int nJudgKey) {
	if (nPushKey & nJudgKey) return true;
	return false;
}

/**
 * �p�b�h�p�O���[�o���ϐ�
 */
int	gJoyPadNum = -1;			// �W���C�p�b�h��
int	gMouseCursor = false;		// �}�E�X�J�[�\��

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

JOYPAD	gJoyPads[MAX_JOYSTICK_COUNT];		// �W���C�p�b�h
UINT	gPadIDs[MAX_JOYSTICK_COUNT] = { JOYSTICKID1, JOYSTICKID2, JOYSTICKID3, JOYSTICKID4 };	// �p�b�h�ԍ��z��

/**
 * �P�̃p�b�h���͕t��
 * @parme nPadIndex �p�b�h�̔ԍ�(0�`3)
 * @parme nPadState �p�b�h���͏��
 */
int AddJoyInput(int nPadIndex, int nPadState) {
	JOYPAD						*pJoyPad;						// �p�b�h
	JOYINFOEX					JoyInfo;						// �p�b�h���

	// �l�`�F�b�N�ƃp�b�h�擾
	if (nPadIndex < 0 || nPadIndex >= gJoyPadNum) return PADERROR;
	pJoyPad = &gJoyPads[nPadIndex];

	if (pJoyPad->bValid) {									// �L����
		JoyInfo.dwSize = sizeof(JoyInfo);					// Joy�\���̃Z�b�g
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
 * �p�b�h����
 * @parme nPushPad �����ꂽ�{�^��
 * @parme nJudgPad ���肵�����{�^��
 */
bool PadJudg(int nPushPad, int nJudgPad) {
	if (nPushPad & nJudgPad) return true;
	return false;
}

/**
 * �L�[��������Ă��邩�`�F�b�N
 * @parme nInputMode ���̓��[�h
 */
int CheckKey(int nInputMode) {
	int							i;
	int							nResult = 0;

	switch (nInputMode) {
		// �}���`�v������
	case INPUT_MULT:
		nResult = AddKeyInput(0);							// �L�[�{�[�h����

		for (i = 0; i < gJoyPadNum; i++) {					// �p�b�h����
			nResult = AddJoyInput(i, nResult);
		}
		break;

		// �L�[�{�[�h����
	case INPUT_KEYBOARD:
		nResult = AddKeyInput(0);
		break;

		// �p�b�h1����
	case INPUT_PAD1:
		nResult = AddJoyInput(0, 0);
		break;

		// �p�b�h2����
	case INPUT_PAD2:
		nResult = AddJoyInput(1, 0);
		break;

		// �p�b�h3����
	case INPUT_PAD3:
		nResult = AddJoyInput(2, 0);
		break;

		// �p�b�h4����
	case INPUT_PAD4:
		nResult = AddJoyInput(3, 0);
		break;

		// �s������
	default:
		nResult = INPUTERROR;
		break;
	}

	return nResult;
}


/**
 *  �P�̃W���C�p�b�h������
 */
static int InitSinglePad(UINT nJoyID, JOYPAD *pJoyPad) {
	JOYCAPS						jCaps;
	JOYINFOEX					jJoyInfo;
	int							nResult = PADERROR;

	pJoyPad->bValid = false;									// �����ɂ��Ă���
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
		jJoyInfo.dwSize = sizeof(jJoyInfo);					// Joy�\���̃Z�b�g
		jJoyInfo.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(pJoyPad->uJoyID, &jJoyInfo) == JOYERR_NOERROR) {
			pJoyPad->bValid = TRUE;								// �p�b�h�L����
			nResult = OK;
		}
	}

	return nResult;
}

/**
 *  �p�b�h�g�p�I��
 */
int EndJoyPad(void) {
	return OK;
}

/*
* �p�b�h������
* @param nMaxPadNum �p�b�h�̍ő吔
*/
int InitJoyPad(int nMaxPadNum) {
	int							i;
	int							nActivePadNum = 0;				// �A�N�e�B�u�ȃp�b�h��
	int							nResult;

	gJoyPadNum = 0;

	if (nMaxPadNum > MAX_JOYSTICK_COUNT) nMaxPadNum = MAX_JOYSTICK_COUNT;
	for (i = 0; i < nMaxPadNum; i++) {
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
	gKeyOld1 = gKey1;
	gKey1 = CheckKey(INPUT_PAD1);		//�L�[���͎擾
	gTrg1 = (gKey1 ^ gKeyOld1)& gKey1;	//�g���K�[�L�[���͎擾

	gKeyOld2 = gKey2;
	gKey2 = CheckKey(INPUT_PAD2);		//�L�[���͎擾
	gTrg2 = (gKey2 ^ gKeyOld2)& gKey2;	//�g���K�[�L�[���͎擾

	gKeyOld3 = gKey3;
	gKey3 = CheckKey(INPUT_PAD3);		//�L�[���͎擾
	gTrg3 = (gKey3 ^ gKeyOld3)& gKey3;	//�g���K�[�L�[���͎擾

	gKeyOld4 = gKey4;
	gKey4 = CheckKey(INPUT_PAD4);		//�L�[���͎擾
	gTrg4 = (gKey4 ^ gKeyOld4)& gKey4;	//�g���K�[�L�[���͎擾
}

/**
 * �p�b�h�̐ڑ��ݒ�
 */
bool ConnectionPad() {
	if (InitJoyPad(MAX_JOYSTICK_COUNT) <= 0) {
		int flag;
		flag = MessageBox(NULL, "�L�[�{�[�h����ŃQ�[�����J�n���܂����H", "�R���g���[���[�ݒ�", MB_YESNO);

		if (flag == IDNO) {
			MessageBox(NULL, "�R���g���[���[��ڑ����čċN�����Ă�������", "�R���g���[���[�ݒ�", NULL);
			return false;
		}
	}
	return true;
}



/**
 * �t�H���g�p�O���[�o���ϐ�
 */
LPD3DXFONT	gD3DFont = NULL;
int			gStringFontSize = -1;	// ������t�H���g�T�C�Y

/**
 * �����񏉊���
 */
int InitFont() {
	//�����񃌃��_�����O�̏�����
	if (FAILED(D3DXCreateFont(gD3DDevice, 0, 10, FW_REGULAR, NULL, false, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "�l�r �S�V�b�N", &gD3DFont)))
	{
		return FONTERROR;
	}

	return OK;
}

/**
 * ������J��
 */
void	ReleaseFont() {
	gD3DFont->Release();
}

/**
 * �F�R�[�h�̊l��
 * @param	alpha	�A���t�@�l�ANULL������Ǝ����I��255�ɂȂ�
 * @param	red		�Ԃ̒l
 * @param	green	�΂̒l
 * @param	blue	�̒l
 * @return	�F�R�[�h��Ԃ�
 */
DWORD GetColor(int alpha, int red, int green, int blue) {
	int result;

	// �K�萔�ȏ�or�K�萔�����Ȃ�Ζ߂�
	if (alpha == NULL) { alpha = 255; }
	if (alpha < 0) { alpha = 0; } else if (alpha > 255) { alpha = 255; }
	if (red < 0) { red = 0; } else if (red > 255) { red = 255; }
	if (green < 0) { green = 0; } else if (green > 255) { green = 255; }
	if (blue < 0) { blue = 0; } else if (blue > 255) { blue = 255; }

	result = static_cast<int>D3DCOLOR_ARGB(alpha, red, green, blue);

	return result;
}

/**
 * ������`��
 * @param x,y	�`����W
 * @param color	�F�R�[�h
 * @param fmt	������
 * @param ...	�\���������ϐ��Ȃ�
 */
void DrawString(float x, float y, int color, const char *fmt, ...) {
	int strlength;		// ������̒������i�[
	char sz[0xffff];	// �i�[�T�C�Y�B������ꂽ���肪�o��B

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
 * �摜�p�O���[�o���ϐ�
 */
int	gBitDepth = 32;			// �r�b�g�f�v�X

TEX_UNIT_PICTURE	gUnitPictureBuf[MAX_UNIT_PICTURES];		// �P�ʃs�N�`���o�b�t�@
int					gUnitPicNum = 0;						// �P�ʃs�N�`����
TEX_USER_PICTURE	gUserPictureBuf[MAX_USER_PICTURES];		// ���[�U�s�N�`���o�b�t�@
int					gUserPicNum = 0;						// ���[�U�s�N�`����

int	fg_nFrameCount = 0;		// �t���[���J�E���^

/**
 * 2D�O���t�B�b�N���[�h
 */
LPDIRECT3DTEXTURE9 Load2DGraph(char *szFileName, TEX_2DPIC_INFO *pPicInfo) {
	LPDIRECT3DTEXTURE9		p2dGraph = NULL;	// ���[�h�e�N�X�`��
	HRESULT					hRes;
	D3DXIMAGE_INFO			iiImageInfo;
	LPDIRECT3DSURFACE9		lpTopSurf;
	D3DSURFACE_DESC			ddSurfInfo;
	D3DFORMAT				dfTexFormat;		// �e�N�X�`���t�H�[�}�b�g
	D3DCOLOR				nColorKey;			// �J���[�L�[

	// �s�N�Z���t�H�[�}�b�g
	dfTexFormat = (gBitDepth == 32) ? D3DFMT_A8R8G8B8 : D3DFMT_A1R5G5B5;

	// �J���[�L�[����
	if (strstr(szFileName, ".bmp") || strstr(szFileName, ".BMP")) {	// �r�b�g�}�b�v�̏ꍇ
		nColorKey = 0xff000000;	// �r�b�g�}�b�v�Ȃ�J���[�L�[����
	}
	else {
		nColorKey = 0;			// �r�b�g�}�b�v�ȊO�Ȃ�J���[�L�[�Ȃ�
	}

	// �e�N�X�`�����[�h
	hRes = D3DXCreateTextureFromFileEx(gD3DDevice, (LPCSTR)szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		dfTexFormat, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		nColorKey, &iiImageInfo, NULL,
		&p2dGraph);

	if (FAILED(hRes)) return NULL;

	// �T�[�t�F�X���擾
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

// �V�K�P�ʃs�N�`��
static TEX_UNIT_PICTURE *MakeUnitPicture(LPDIRECT3DTEXTURE9 ppbPicture, 
	TEX_2DPIC_INFO *ppiPicInfo, char *szFileName)
{
	if (gUnitPicNum >= MAX_UNIT_PICTURES) return NULL;			// �󂫃`�F�b�N

	gUnitPictureBuf[gUnitPicNum].a2PicInfo = *ppiPicInfo;		// �G���
	gUnitPictureBuf[gUnitPicNum].pPicture = ppbPicture;			// �G�I�u�W�F�N�g
	strncpy(gUnitPictureBuf[gUnitPicNum].szFileName, szFileName, MAX_PICTURE_NAME - 1);	// �G�t�@�C����
	gUnitPictureBuf[gUnitPicNum].szFileName[MAX_PICTURE_NAME - 1] = 0;	// �t�@�C�����̏I�[���m���ɒu��
	gUnitPicNum++;

	return &gUnitPictureBuf[gUnitPicNum - 1];
}

// �V�K�G�n���h��
static int Make2DHandle(TEX_UNIT_PICTURE *pUnitPic, 
	int nLeft, int nTop, int nWidth, int nHeight, int bFlags)
{
	int	hPicture = PIC2D_HANDLE_HEAD;

	if (gUserPicNum >= MAX_USER_PICTURES) return NULL;	// �n���h���󂫃`�F�b�N

	gUserPictureBuf[gUserPicNum].pUnitPic = pUnitPic;
	gUserPictureBuf[gUserPicNum].nLeft = nLeft;
	gUserPictureBuf[gUserPicNum].nTop = nTop;
	gUserPictureBuf[gUserPicNum].nWidth = nWidth;
	gUserPictureBuf[gUserPicNum].nHeight = nHeight;
	gUserPictureBuf[gUserPicNum].bFlags = bFlags;
	gUserPicNum++;

	hPicture |= gUserPicNum - 1;	// �n���h������

	return hPicture;
}

// 2D�O���t�B�b�N���[�h
int LoadTexture(char *szFileName) {
	LPDIRECT3DTEXTURE9		ppbPicture;
	TEX_2DPIC_INFO			piPicInfo;
	TEX_UNIT_PICTURE		*pUnitPic;		// �P�ʃs�N�`��
	int						hPicture;		// �s�N�`���n���h��

	ppbPicture = Load2DGraph(szFileName, &piPicInfo);	// �O���t�B�b�N���[�h
	
	pUnitPic = MakeUnitPicture(ppbPicture, &piPicInfo, szFileName);	// �P�ʃs�N�`���o�^

	hPicture = Make2DHandle(pUnitPic, 0, 0, piPicInfo.nWidth, piPicInfo.nHeight, 0);	// �n���h���쐬

	return hPicture;
}

/**
 * �u���b�N��2D�O���t�B�b�N���[�h
 */
static int LoadBlockedTexture(char *szFileName, int nXSize, int nYSize,
	int nXNum, int nYNum, int nAllNum, int *phHandleBuf, int bFlags)
{
	int	i, j;
	int	x, y;		// �u���b�N�̍�����W
	int	nBlockNum;	// �u���b�N��
	LPDIRECT3DTEXTURE9		ppbPicture;
	TEX_2DPIC_INFO			piPicInfo;
	TEX_UNIT_PICTURE		*pUnitPic;	// �P�ʃs�N�`��

	ppbPicture = Load2DGraph(szFileName, &piPicInfo);	// �O���t�B�b�N���[�h
	
	pUnitPic = MakeUnitPicture(ppbPicture, &piPicInfo, szFileName);	// �P�ʃs�N�`���o�^

	nBlockNum = 0;	// �����u���b�N��
	y = 0;
	for (i = 0; i < nYNum; i++) {
		x = 0;
		for (j = 0; j < nXNum; j++) {
			// �u���b�N���G�̊O�Ɋ|����Ȃ�
			if (1) {
				*(phHandleBuf + nBlockNum) = Make2DHandle(pUnitPic, x, y, nXSize, nYSize, 0);	// �n���h���쐬
				nBlockNum++;
				if (bFlags & PICTURE_LR) {
					*(phHandleBuf + nBlockNum) = Make2DHandle(pUnitPic, x, y, nXSize, nYSize, PICTURE_LR);	// �n���h���쐬
					nBlockNum++;
				}
			}
			// �u���b�N���G�̊O�Ɋ|����
			else {
				// ���E���]���肩
				if (bFlags & PICTURE_LR) {
					*(phHandleBuf + nBlockNum) = *(phHandleBuf + nBlockNum - 2);	// �ӂ��O�R�s�[
					*(phHandleBuf + nBlockNum + 1) = *(phHandleBuf + nBlockNum - 1);	// �ӂ��O�R�s�[
					nBlockNum += 2;
				}
				else {
					*(phHandleBuf + nBlockNum) = *(phHandleBuf + nBlockNum - 1);	// �ЂƂO�R�s�[
					nBlockNum++;
				}
			}
			// �K�萔�܂ŒB���Ă���ΏI��
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
 * �u���b�N��2D�O���t�B�b�N���[�h(�Ăяo���p)
 */
int LoadBlkTexture(char *szFileName, int nXSize, int nYSize,
	int nXNum, int nYNum, int nAllNum, int *phHandleBuf) {
	return LoadBlockedTexture(szFileName, nXSize, nYSize,
		nXNum, nYNum, nAllNum, phHandleBuf, 0);
}

/**
 * 2D�O���t�B�b�N�J��
 */
int Release2DGraphs(void) {
	int	i;

	// �O���t�B�b�N�J��
	for (i = 0; i < gUnitPicNum; i++) {
		SAFE_RELEASE(gUnitPictureBuf[i].pPicture);
	}

	// �萔���Z�b�g
	gUnitPicNum = 0;	// �P�ʃs�N�`�����Z�b�g
	gUserPicNum = 0;	// ���[�U�[�s�N�`�����Z�b�g

	return OK;
}

static int BlendFactor;		// �u�����h�t�@�N�^

// �`���`�p���_
BOX_2DVERTEX	gDrawRect[4] = { {   0.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f },
								 { 640.0f,   0.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f },
								 {   0.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 0.0f, 1.0f },
								 { 640.0f, 480.0f, 0.0f, 1.0f, 0xffffffff, 1.0f, 1.0f } };

BLEND_STATE		gBlendState;	// ���݂̃u�����h�X�e�[�g

/**
 * �u�����h�t�@�N�^�Z�b�g
 */
static void SetBlendFactor(int nBlendFactor) {
	int	i;

	// �T�`���[�V����
	if (nBlendFactor < 0) nBlendFactor = 0;
	if (nBlendFactor > MAX_BLEND_FACTOR) nBlendFactor = MAX_BLEND_FACTOR;

	gBlendState.nBlendFactor = nBlendFactor;	// �u�����h�t�@�N�^�ۑ�

	// �`�撸�_�Z�b�g
	for (i = 0; i < 4; i++) {
		gDrawRect[i].color = (gDrawRect[0].color & 0x00ffffff) | (nBlendFactor << 24);
	}

}

/**
 * �u�����h�X�e�[�g������
 */
int InitBlendState(void) {
	// �A���t�@�u�����h�Ȃ�
	gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	gBlendState.nBlendMode = DRAW_NOBLEND;
	SetBlendFactor(MAX_BLEND_FACTOR);					// �u�����h�t�@�N�^�ő�
	gBlendState.nBrRed = 255;  gBlendState.nBrGreen = 255;  gBlendState.nBrBlue = 255;	// �`��F�͔�

	// �F����
	gD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// �A���t�@����
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// �e�N�Z���T���v���ݒ�
	gD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	gD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	// �e�N�X�`���N�����v
	gD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	gD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);


	return OK;
}

/**
 * 2D�O���t�B�b�N�@�e�N�X�`�����W�v�Z
 */
static int Calc2DUVCoord(float *du1, float *dv1, float *du2, float *dv2,
	int sx1, int sy1, int sx2, int sy2,
	TEX_2DPIC_INFO *pPicInfo)
{
	// u����
	// ���E���]�Ȃ�
	if (sx1 <= sx2) {
		*du1 = (float)(sx1 + 0.5f) / pPicInfo->nRealWidth;
		*du2 = (float)(sx2 /* + 0.5f*/) / pPicInfo->nRealWidth;
	}
	// ���E���]����
	else {
		*du1 = (float)(sx1 - 0.5f) / pPicInfo->nRealWidth;
		*du2 = (float)(sx2 /*  - 0.5f*/) / pPicInfo->nRealWidth;
	}

	// v����
	// ���E���]�Ȃ�
	if (sy1 <= sy2) {
		*dv1 = (float)(sy1 + 0.5f) / pPicInfo->nRealHeight;
		*dv2 = (float)(sy2 /*- 0.5f*/) / pPicInfo->nRealHeight;
	}
	// ���E���]����
	else {
		*dv1 = (float)(sy1 - 0.5f) / pPicInfo->nRealHeight;
		*dv2 = (float)(sy2 /*- 0.5f*/) / pPicInfo->nRealHeight;
	}

	return OK;
}

/**
 * 2D�O���t�B�b�N�`��i�`���Q�_�A�`�挳�Q�_�w��j
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
 * �`��F�Z�b�g
 */
int SetDrawColor(int nRed, int nGreen, int nBlue) {
	int							i;
	int							nCompositColor;	// �����ς݂̐F

	// �T�`���[�V����
	if (nRed < 0) nRed = 0;
	if (nRed > MAX_COLOR_FACTOR) nRed = MAX_COLOR_FACTOR;
	if (nGreen < 0) nGreen = 0;
	if (nGreen > MAX_COLOR_FACTOR) nGreen = MAX_COLOR_FACTOR;
	if (nBlue < 0) nBlue = 0;
	if (nBlue > MAX_COLOR_FACTOR) nBlue = MAX_COLOR_FACTOR;

	// �F���ۑ�
	gBlendState.nBrRed = nRed;
	gBlendState.nBrGreen = nGreen;
	gBlendState.nBrBlue = nBlue;

	nCompositColor = (nRed << 16) + (nGreen << 8) + nBlue;

	// �`�撸�_�Z�b�g
	for (i = 0; i < 4; i++) {
		gDrawRect[i].color = (gDrawRect[0].color & 0xff000000) | nCompositColor;
	}

	return OK;
}

/**
 * �u�����h�X�e�[�g�擾
 */
int GetBlendState(BLEND_STATE *pbsBlendFactor) {
	*pbsBlendFactor = gBlendState;

	return OK;
}

/**
 * �u�����h���[�h�ݒ�
 */
int SetBlendState(int nBlendCode, int nBlendFactor) {
	// �u�����h�Ȃ�
	if (nBlendCode == DRAW_NOBLEND) {
		if (gBlendState.nBlendMode != DRAW_NOBLEND) {
			gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			gBlendState.nBlendMode = DRAW_NOBLEND;
		}
		SetBlendFactor(255);	// �u�����h�t�@�N�^�ݒ�
	}

	// �A���t�@�u�����f�B���O
	if (nBlendCode == DRAW_ALPHABLEND) {
		if (gBlendState.nBlendMode != DRAW_ALPHABLEND) {
			if (gBlendState.nBlendMode == DRAW_NOBLEND)
				gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// �u�����h�n�e�e�Ȃ�n�m��
			gD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			gD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			gBlendState.nBlendMode = DRAW_ALPHABLEND;
		}
		SetBlendFactor(nBlendFactor);	// �u�����h�t�@�N�^�ݒ�
	}

	// ���Z�u�����f�B���O
	if (nBlendCode == DRAW_ADDBLEND) {
		if (gBlendState.nBlendMode != DRAW_ADDBLEND) {
			if (gBlendState.nBlendMode == DRAW_NOBLEND)
				gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// �u�����h�n�e�e�Ȃ�n�m��
			gD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			gD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			gBlendState.nBlendMode = DRAW_ADDBLEND;
		}
		SetBlendFactor(nBlendFactor);	// �u�����h�t�@�N�^�ݒ�
	}

	return OK;
}

/**
 * �u�����h�X�e�[�g���A
 */
int RestoreBlendState(BLEND_STATE *pbsRestoreBlend) {
	SetBlendState(pbsRestoreBlend->nBlendMode, pbsRestoreBlend->nBlendFactor);	// �u�����h�t�@�N�^�ݒ�
	// �K�v�Ȃ�F�t�@�N�^�ݒ�
	if (gBlendState.nBrRed != pbsRestoreBlend->nBrRed ||
		gBlendState.nBrGreen != pbsRestoreBlend->nBrGreen ||
		gBlendState.nBrBlue != pbsRestoreBlend->nBrBlue)
	{
		SetDrawColor(pbsRestoreBlend->nBrRed, pbsRestoreBlend->nBrGreen, pbsRestoreBlend->nBrBlue);
	}
	gBlendState = *pbsRestoreBlend;	// �u�����h�X�e�[�g�ۑ�

	return OK;
}

// �����t���`��
static int DrawPictureCond(int dx1, int dy1, int dx2, int dy2,
	int sx1, int sy1, int sx2, int sy2,
	LPDIRECT3DTEXTURE9 pPicture, TEX_2DPIC_INFO *pPicInfo, int bConds)
{
	int	nResult;				// ���U���g�R�[�h
	BLEND_STATE		bsBlendBuf;	// �u�����h�X�e�[�g�ޔ��ꏊ

	// �G�̃A���t�@�l�l����
	if (bConds & (DRAWPIC_PICALPHA | DRAWPIC_AVEALPHA | DRAWPIC_ADDALPHA)) {
		GetBlendState(&bsBlendBuf);	// �u�����h�X�e�[�g�擾
		if (bConds & DRAWPIC_ADDALPHA) {
			if (bConds & DRAWPIC_AVEALPHA) {
				SetBlendState(DRAW_ADDBLEND, MAX_BLEND_FACTOR / 2);		// ���Z�u�����h
			}
			else {
				SetBlendState(DRAW_ADDBLEND, MAX_BLEND_FACTOR);			// ���Z�u�����h
			}
		}
		else {
			if (bConds & DRAWPIC_AVEALPHA) {
				SetBlendState(DRAW_ALPHABLEND, MAX_BLEND_FACTOR / 2);		// �A���t�@�u�����h
			}
			else {
				SetBlendState(DRAW_ALPHABLEND, bsBlendBuf.nBlendFactor);	// �A���t�@�u�����h
			}
		}
	}

	// ���`��
	nResult = Draw2DGraph(dx1, dy1, dx2, dy2,
		sx1, sy1, sx2, sy2,
		pPicture, pPicInfo);

	// �G�̃A���t�@�l�l����
	if (bConds & (DRAWPIC_PICALPHA | DRAWPIC_AVEALPHA | DRAWPIC_ADDALPHA)) {
		RestoreBlendState(&bsBlendBuf);					// �u�����h�X�e�[�g���A
	}

	return nResult;
}

/**
 * �`�惂�[�h�̐ݒ�
 */
int SetDrawMode(int nDrawMode, int nParam) {
	// �u�����h���[�h
	if (nDrawMode & DRAW_NOBLEND) {							// �u�����h�Ȃ�
		SetBlendState(DRAW_NOBLEND, 0);
	}
	if (nDrawMode & DRAW_ALPHABLEND) {						// �A���t�@�u�����f�B���O
		SetBlendState(DRAW_ALPHABLEND, nParam);
	}
	if (nDrawMode & DRAW_ADDBLEND) {						// ���Z�u�����f�B���O
		SetBlendState(DRAW_ADDBLEND, nParam);
	}

	return OK;
}

/**
 * 2D�`��
 * @parme x x���W
 * @parme y y���W
 * @parme hPicture �`��摜
 */
int DrawMem(int x, int y, int hPicture) {
	int	nResult;					// ���U���g�R�[�h
	int	nUserPicLoc;				// ���[�U�[�G�ʒu
	TEX_USER_PICTURE *pupUserPic;	// ���[�U�[�G
	int	bDrawConds = 0;				// �`�����

	nUserPicLoc = hPicture & ~HANDLE_HEAD_MASK;	// �ʒu

	pupUserPic = &gUserPictureBuf[nUserPicLoc];

	nResult = DrawPictureCond(x, y, x + pupUserPic->nWidth, y + pupUserPic->nHeight,
		pupUserPic->nLeft, pupUserPic->nTop,
		pupUserPic->nLeft + pupUserPic->nWidth, pupUserPic->nTop + pupUserPic->nHeight,
		pupUserPic->pUnitPic->pPicture, &(pupUserPic->pUnitPic->a2PicInfo), bDrawConds);

	return nResult;
}

/**
 * �A���t�@�u�����h�t��2D�`��
 * @parme x x���W
 * @parme y y���W
 * @parme hPicture �`��摜
 */
int DrawMemTh(int x, int y, int hPicture) {
	int	nResult;						// ���U���g�R�[�h
	int	nUserPicLoc;					// ���[�U�[�G�ʒu
	TEX_USER_PICTURE *pupUserPic;		// ���[�U�[�G
	int	bDrawConds = DRAWPIC_PICALPHA;	// �`�����

	nUserPicLoc = hPicture & ~HANDLE_HEAD_MASK;	// �ʒu

	pupUserPic = &gUserPictureBuf[nUserPicLoc];

	nResult = DrawPictureCond(x, y, x + pupUserPic->nWidth, y + pupUserPic->nHeight,
		pupUserPic->nLeft, pupUserPic->nTop,
		pupUserPic->nLeft + pupUserPic->nWidth, pupUserPic->nTop + pupUserPic->nHeight,
		pupUserPic->pUnitPic->pPicture, &(pupUserPic->pUnitPic->a2PicInfo), bDrawConds);

	return nResult;
}

/**
 * �o�b�N�o�b�t�@�̃N���A
 */
int ClearBackBuffer(int r, int g, int b) {
	gD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(r, g, b), 1.0f, 0);

	return OK;
}

/**
 * ��ʃN���A
 */
int HCls(void) {
	int	nResult;	// ���U���g�R�[�h

	nResult = ClearBackBuffer(0, 0, 0);	// ��ʍX�V����

	return nResult;
}

/**
 * ��ʍX�V����
 */
int Flip(void) {
	int	nResult;	// ���U���g�R�[�h

	nResult = DispFlip();	// ��ʍX�V����

	fg_nFrameCount++;

	return nResult;
}

POINTVERTEX	gPointBuf[MAX_POINT_NUM];	// �|�C���g�o�b�t�@

/**
 * �F�̊|���Z�v�Z
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
 * �����`�̕`��
 */
int DrawRectangleArray(POINT_DATA *papPoints, int nRectNum) {
	int	i;
	int	nResult = OK;
	POINT_DATA *pPresPoint;	// ���݂̓_

	if (nRectNum > MAX_RECT_NUM) {
		nRectNum = MAX_RECT_NUM;
		nResult = BOXERROR;
	}

	gD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);	// �f�B�t���[�Y�F�̂�
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);	// �f�B�t���[�Y�A���t�@�̂�

	pPresPoint = papPoints;
	for (i = 0; i < nRectNum; i++) {
		// ����
		gPointBuf[0].x = (float)pPresPoint->x;
		gPointBuf[0].y = (float)pPresPoint->y;
		gPointBuf[0].z = (float)pPresPoint->z;
		gPointBuf[0].rhw = 1.0f;
		gPointBuf[0].color = GetModulateColor(pPresPoint->nColor, gDrawRect[0].color);

		// �E��
		gPointBuf[1] = gPointBuf[0];
		gPointBuf[1].x = (float)(pPresPoint + 1)->x;

		// ����
		gPointBuf[2].x = (float)pPresPoint->x;
		gPointBuf[2].y = (float)(pPresPoint + 1)->y;
		gPointBuf[2].z = (float)(pPresPoint + 1)->z;
		gPointBuf[2].rhw = 1.0f;
		gPointBuf[2].color = GetModulateColor((pPresPoint + 1)->nColor, gDrawRect[2].color);

		// �E��
		gPointBuf[3] = gPointBuf[2];
		gPointBuf[3].x = (float)(pPresPoint + 1)->x;

		// �`��
		gD3DDevice->SetFVF(D3DFVF_2DTEX);
		gD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, nRectNum * 2,
			gPointBuf, sizeof(POINTVERTEX));

		pPresPoint += 2;
	}

	gD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	// �e�N�X�`���F�����A
	gD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �e�N�X�`���A���t�@�����A

	return nResult;
}

/**
 * �����`�̕`��
 * @parme x1 �E��x���W
 * @parme y1 �E��y���W
 * @parme x2 ����x���W
 * @parme y2 ����y���W
 * @parme color �F�R�[�h
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color) {
	POINT_DATA apRectPoint[2];	// ����E�E���̓_

	// ����
	apRectPoint[0].x = x1;  apRectPoint[0].y = y1;  apRectPoint[0].z = 0;
	apRectPoint[0].nColor = color;

	// �E��
	apRectPoint[1].x = x2;  apRectPoint[1].y = y2;  apRectPoint[1].z = 0;
	apRectPoint[1].nColor = color;

	DrawRectangleArray(apRectPoint, 1);	// �`��

	return;
}



/**
 * FPS�p�O���[�o���ϐ�
 */
int gFpsCount = 0;

/**
 * FPS����
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
 * FPS�����ɂ���
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
