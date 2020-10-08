/*
 * @file library.cpp
 * @brief ライブラリ処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include "FbxMesh.h"


#ifndef __IEXTREME_H__
#define __IEXTREME_H__

#define _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_DEPRECATE

#define OK					0	// 正常終了
#define ERRORCODE			-1	// エラー
#define ERR_NOHARDWARE		-2	// ハードウェアエラー
#define ERR_PAD				-3	// パッドエラー
#define ERR_CHAR			-4	// キャラクターエラー

#define SAFE_RELEASE(p)	{ if(p)	{ (p)->Release();(p)=NULL; } }
#define MODE_WINDOWED			0x0001							// ウィンドウモード指定

// キー定数
#define KEYIN_2					0x0001					// ２キーチェックマスク
#define KEYIN_DOWN				0x0001					// ↓キーチェックマスク
#define KEYIN_4					0x0002					// ４キーチェックマスク
#define KEYIN_LEFT				0x0002					// ←キーチェックマスク
#define KEYIN_6					0x0004					// ６キーチェックマスク
#define KEYIN_RIGHT				0x0004					// →キーチェックマスク
#define KEYIN_8					0x0008					// ８キーチェックマスク
#define KEYIN_UP				0x0008					// ↑キーチェックマスク
#define KEYIN_SPC				0x0010					// スペースチェックマスク
#define KEYIN_ESC				0x0020					// ｴｽｹｰﾌﾟチェックマスク
#define KEYIN_START				0x0020					// スタートキーチェックマスク
#define KEYIN_SFT				0x0040					// シフトチェックマスク
#define KEYIN_RET				0x0080					// リターンチェックマスク
#define KEYIN_Z					0x0100					// Ｚチェックマスク
#define KEYIN_X					0x0200					// Ｘチェックマスク
#define KEYIN_C					0x0400					// Ｃチェックマスク
#define KEYIN_A					0x0800					// Ａチェックマスク
#define KEYIN_S					0x1000					// Ｓチェックマスク
#define KEYIN_D					0x2000					// Ｄチェックマスク
#define KEYIN_Q					0x4000					// Ｑチェックマスク
#define KEYIN_W					0x8000					// Ｗチェックマスク

#define PICTURE_NAME_MAX 200		//画像ファイル名の最大文字数
#define PICTURE_MAX 2000			//画像読み込み最大数
#define PICTURE_BLOCK_MAX 2000		//画像登録最大数

#define PIC_HANDLE_HEAD 0x10000000	//ハンドルの頭
#define PICTURE_LR 0x00000002		//左右反転フラグ
#define PICTURE_UD 0x00000004		//上下反転フラグ

// 接続可能ジョイスティック数
#define MAX_JOYSTICK_COUNT	4

#define JOYSTICKID3 2
#define JOYSTICKID4 3

// ゲーム時間
#define GAME_TIME 120

#define MAX_POINT_NUM		640								// 描画最大点数
#define AM_MAX_RECT_NUM			( MAX_POINT_NUM / 2 )		// 描画最大長方形数

// 画面サイズ
#define DISP_W		1280
#define DISP_H		720

// ブレンドモード
#define DRAW_NOBLEND		0x0004	// ブレンドなし
#define DRAW_ALPHABLEND		0x0008	// アルファブレンディング
#define DRAW_ADDBLEND		0x0010	// 加算ブレンディング

extern D3DFORMAT	gScreenFormat;
extern int			gScreenWidth;
extern int			gScreenHeight;

extern IDirect3DDevice9*	gDevice;
extern HWND					gWindow;

bool InitD3D(HWND hWnd, bool bFullScreen);
void ReleaseD3D();
void BeginScene();
void EndScene();

/** ウインドウ作成
 disp_w, disp_h : 画面サイズ
 WindowName		: ウインドウの名前
*/
void InitWnd(HINSTANCE hInst, int disp_w, int disp_h, LPSTR WindowName);
bool InitApp();
void ReleaseFont();

// キー入力モード
enum PAD_NUMBER
{
	INPUT_MULT,
	INPUT_PAD1,
	INPUT_PAD2,
	INPUT_PAD3,
	INPUT_PAD4
};

struct JOYPAD
{									// ジョイパッド構造体
	UINT		uJoyID;											// ジョイスティックＩＤ
	BOOL		bValid;											// ジョイスティック有効か
	DWORD		nMinX, nMaxX;									// スティックの最大、最小値
	DWORD		nMinY, nMaxY;
	DWORD		nCenterX, nCenterY;								// 中央値
	DWORD		nLeft, nRight;									// 左右しきい値
	DWORD		nTop, nBottom;									// 上下しきい値
};

extern int CheckKey(int nInputMode);									// キーが押されているかチェック

/**
 *  1P～4Pまでのキー入力取得
 */
extern void InKey();

/*
 * コントローラーが接続されているかの確認
 */
extern bool ConnectionPad();

/**
 *  パッド初期化
 */
extern int InitJoyPad(int nMaxPadNum);								// パッド初期化

/**
 *  パッド使用終了
 */
extern int EndJoyPad(void);											// パッド使用終了

/**
 *  単体パッド入力付加
 */
extern int AddJoyInput(int nPadIndex, int nKeyState);				// 単体パッド入力付加
extern int gJoyPadNum;											// ジョイパッド数

extern int gKeyold1;
extern int gKey1;
extern int gTrg1;

extern int gKeyold2;
extern int gKey2;
extern int gTrg2;

extern int gKeyold3;
extern int gKey3;
extern int gTrg3;

extern int gKeyold4;
extern int gKey4;
extern int gTrg4;

/**
 *　文字列使用初期化
 */
extern int InitFont();

/**
 *　文字列描画
 *　@param	x,y		描画座標
 *　@param	color	色コード
 *　@param	fmt		文字列
 *　@param	...		(あるなら)表示したい変数など
 */
void DrawString(float x, float y, int color, const char *fmt, ...);

/**
 *　色コードの獲得
 *　@param	alpha	アルファ値、NULLを入れると自動的に255になる
 *　@param	red		赤の値
 *　@param	green	緑の値
 *　@param	blue	青の値
 *　@return	色コードを返す
 */
DWORD GetColor(int alpha, int red, int green, int blue);

// 画像情報構造体
struct KT_2DPIC_INFO {
	unsigned int					nLeft, nTop;					// 単位ピクチャ内での位置
	unsigned int					nWidth, nHeight;				// 幅・高さ
	unsigned int					nRealWidth, nRealHeight;		// 実際の（物理的な）幅・高さ
	IDirect3DTexture9* texture;							// テクスチャ
	HRESULT						hRes;
};

/*
 * 2Dグラフィックロード
 */
KT_2DPIC_INFO CreateTexture(const char *szFileName);

/*
 * テクスチャスプリット作成
 */
bool CreateSprit();

/*
 * リリーススプリット
 */
void RereaseSprit(IDirect3DTexture9* tex);

/*
 * テクスチャ描画
 */
void DrawTexture(float x, float y, KT_2DPIC_INFO* pic, IDirect3DTexture9* tex, int draw_mode);

// 2D頂点構造体
struct AM_2DVERTEX {
	float				x, y, z, rhw;							// 頂点座標
	DWORD				color;									// 頂点色
	float				tu, tv;									// テクスチャ座標
};

/**
 * 描画モード設定
 * @param draw_mode 描画モード
 * @param nParam	α値
 */
void SetDrawMode(int draw_mode, int nParam);

/*
 * 長方形の描画
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color);

#endif
