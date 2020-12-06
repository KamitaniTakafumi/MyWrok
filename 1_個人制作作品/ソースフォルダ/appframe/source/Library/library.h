/**
 * @file library.cpp
 * @brief ライブラリ処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include <windows.h>
#include <d3dx9.h>
#include <dinput.h>
#include "../appframe.h"


#ifndef __IEXTREME_H__
#define __IEXTREME_H__

#define _CRT_SECURE_NO_WARNINGS
#define	_CRT_SECURE_NO_DEPRECATE

#define OK			1	// 正常終了
#define DISPERROR	-1	// 画面描画エラー
#define PADERROR	-2	// パッドエラー
#define BOXERROR	-3	// 矩形描画エラー
#define FONTERROR	-4	// フォントエラー
#define INPUTERROR	-5	// 入力エラー

//#define MODE_DEBUG	// デバッグモード

#define PICTURE_NAME_MAX	200		//画像ファイル名の最大文字数
#define PICTURE_MAX			2000	//画像読み込み最大数
#define PICTURE_BLOCK_MAX	2000	//画像登録最大数

#define MAX_POINT_NUM	640		// 描画最大点数
#define MAX_RECT_NUM	( MAX_POINT_NUM / 2 )	// 描画最大長方形数

#define MAX_JOYSTICK_COUNT	4	// 接続可能ジョイスティック数

#define JOYSTICKID3	2	// ジョイスティック3
#define JOYSTICKID4	3	// ジョイスティック4

// オブジェクトを安全に開放
#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}

// Windowサイズ
#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720

#define MAX_UNIT_PICTURES	2000	// 最大単位ピクチャ数
#define MAX_USER_PICTURES	5000	// 最大ユーザピクチャ数

#define MAX_EVENTS	10	// 最大一括処理イベント数

#define PIC2D_HANDLE_HEAD	0x10000000	// 2Dピクチャハンドルヘッダ

#define HANDLE_HEAD_MASK	0xff000000	// ハンドルヘッダマスク値

#define DRAWPIC_LR			0x0001	// 描画左右反転フラグ
#define DRAWPIC_PICALPHA	0x0002	// 絵のアルファ値でアルファブレンド
#define DRAWPIC_AVEALPHA	0x0004	// 平均アルファブレンド
#define DRAWPIC_ADDALPHA	0x0008	// 加算ブレンド

#define PICTURE_LR	0x0001	// 左右反転フラグ

#define DRAW_NOBLEND	0x0004	// ブレンドなし
#define DRAW_ALPHABLEND	0x0008	// アルファブレンディング
#define DRAW_ADDBLEND	0x0010	// 加算ブレンディング

#define MAX_BLEND_FACTOR	255	// ブレンドファクタ最大値
#define MAX_COLOR_FACTOR	255	// 色ファクタ最大値

#define D3DFVF_2DTEX	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	// 2Dテクスチャ頂点フォーマット

#define MAX_PICTURE_NAME	200	// 最大絵ファイル名長

// キー入力モード
#define INPUT_MULT			0	// マルチプレックス入力
#define INPUT_KEYBOARD		1	// キーボード入力
#define INPUT_PAD1			2	// パッド１入力
#define INPUT_PAD2			3	// パッド２入力
#define INPUT_PAD3			4	// パッド３入力
#define INPUT_PAD4			5	// パッド４入力

// キー定数
#define KEYIN_2			0x0001		// ２キーチェックマスク
#define KEYIN_DOWN		0x0001		// ↓キーチェックマスク
#define KEYIN_4			0x0002		// ４キーチェックマスク
#define KEYIN_LEFT		0x0002		// ←キーチェックマスク
#define KEYIN_6			0x0004		// ６キーチェックマスク
#define KEYIN_RIGHT		0x0004		// →キーチェックマスク
#define KEYIN_8			0x0008		// ８キーチェックマスク
#define KEYIN_UP		0x0008		// ↑キーチェックマスク
#define KEYIN_SPC		0x0010		// スペースチェックマスク
#define KEYIN_ESC		0x0020		// ｴｽｹｰﾌﾟチェックマスク
#define KEYIN_START		0x0020		// スタートキーチェックマスク
#define KEYIN_SFT		0x0040		// シフトチェックマスク
#define KEYIN_RET		0x0080		// リターンチェックマスク
#define KEYIN_Z			0x0100		// Ｚチェックマスク(パッドA)
#define KEYIN_X			0x0200		// Ｘチェックマスク(パッドB)
#define KEYIN_C			0x0400		// Ｃチェックマスク(パッドX)
#define KEYIN_A			0x0800		// Ａチェックマスク(パッドY)
#define KEYIN_S			0x1000		// Ｓチェックマスク(パッドLB)
#define KEYIN_D			0x2000		// Ｄチェックマスク(パッドRB)
#define KEYIN_Q			0x4000		// Ｑチェックマスク(パッドBACK)
#define KEYIN_W			0x8000		// Ｗチェックマスク(パッドSTART)

#define MAX_FPS		60	// 最大FPS
//#define DRAW_FPS		// FPS描画の有無


bool InitD3D(HWND hWnd, bool bFullScreen);
void ReleaseD3D();
void BeginScene();
void EndScene();

/** ウインドウ作成
 disp_w, disp_h : 画面サイズ
 WindowName		: ウインドウの名前
*/
void InitWnd(HINSTANCE hInst, int disp_w, int disp_h, LPSTR WindowName);
extern int ProcessEvent();
bool InitApp();
void ReleaseFont();



// ジョイパッド構造体
struct JOYPAD
{
	UINT		uJoyID;					// ジョイスティックＩＤ
	BOOL		bValid;					// ジョイスティック有効か
	DWORD		nMinX, nMaxX;			// スティックの最大、最小値
	DWORD		nMinY, nMaxY;
	DWORD		nCenterX, nCenterY;		// 中央値
	DWORD		nLeft, nRight;			// 左右しきい値
	DWORD		nTop, nBottom;			// 上下しきい値
};

extern int CheckKey(int nInputMode);	// キーが押されているかチェック
extern void InKey();
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

/**
 * キー判定
 * @parme nPushKey 押されたキー
 * @parme nJudgKey 判定したいキー
 */
extern bool KeyJudg(int nPushKey, int nJudgKey);

/**
 * パッド判定
 * @parme nPushPad 押されたボタン
 * @parme nJudgPad 判定したいボタン
 */
extern bool PadJudg(int nPushPad, int nJudgPad);

extern int gJoyPadNum;	// ジョイパッド数

/**
 * 文字列使用初期化
 */
extern int InitFont();

/**
 * 文字列描画
 * @param x,y	描画座標
 * @param color	色コード
 * @param fmt	文字列
 * @param ...	表示したい変数など
 */
extern void DrawString(float x, float y, int color, const char *fmt, ...);
DWORD GetColor(int alpha, int red, int green, int blue);


/**
 * 画像情報構造体
 */
struct TEX_2DPIC_INFO {
	int					nWidth, nHeight;						// 幅・高さ
	int					nRealWidth, nRealHeight;				// 実際の（物理的な）幅・高さ
	int					nBitDepth, nRealDepth;					// 元のビットデプスと実際のビットデプス
};

/**
 * 単位ピクチャ構造体
 */
struct TEX_UNIT_PICTURE {
	TEX_2DPIC_INFO				a2PicInfo;						// ピクチャ情報
	LPDIRECT3DTEXTURE9		pPicture;						// ピクチャ
	char						szFileName[PICTURE_NAME_MAX];	// ピクチャファイル名
};

/**
 * ユーザピクチャ構造体
 */
struct TEX_USER_PICTURE {
	TEX_UNIT_PICTURE				*pUnitPic;						// 単位ピクチャ
	int							nLeft, nTop;					// 単位ピクチャ内での位置
	int							nWidth, nHeight;				// 幅と高さ
	int							bFlags;							// 属性フラグ
};

extern int LoadTexture(char *szFileName);
extern int LoadBlkTexture(char *szFileName, int nXSize, int nYSize,
	int nXNum, int nYNum, int nAllNum, int *phHandleBuf);
extern int Release2DGraphs(void);
extern int InitBlendState(void);

/**
 * ブレンドステート構造体
 */
struct BLEND_STATE {
	int					nBlendMode;								// ブレンドモード
	int					nBlendFactor;							// ブレンドファクタ
	int					nBrRed, nBrGreen, nBrBlue;				// 緑・赤・青の明るさ
};

extern int SetDrawMode(int nDrawMode, int nParam);
extern int DrawMem(int x, int y, int hPicture);
extern int DrawMemTh(int x, int y, int hPicture);

extern int HCls(void);	// 画面クリア
extern int Flip(void);	// 画面更新処理

/**
 * 2D頂点構造体
 */
struct BOX_2DVERTEX {
	float	x, y, z, rhw;	// 頂点座標
	DWORD	color;			// 頂点色
	float	tu, tv;			// テクスチャ座標
};

/**
 * 点データ
 */
struct POINT_DATA {
	int				x, y, z;	// 座標
	unsigned int	nColor;		// 色
};

/**
 * 2D頂点構造体
 */
struct POINTVERTEX {
	float	x, y, z, rhw;	// 頂点座標
	int		color;			// 頂点色
};

/**
 * 長方形の描画
 * @parme x1 右上x座標
 * @parme y1 右上y座標
 * @parme x2 左下x座標
 * @parme y2 左下y座標
 * @parme color 色コード
 */
void DrawFBox(int x1, int y1, int x2, int y2, int color);


extern int gFpsCount;

extern void fps();
extern void wait_fanc();

#endif
