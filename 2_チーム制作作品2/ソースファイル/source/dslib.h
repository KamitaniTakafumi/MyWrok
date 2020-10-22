/*
 * @file dslib.cpp
 * @brief サウンド処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#ifndef __DSLIB_H__
#define	__DSLIB_H__

#define MAX_SE 9

extern int sndBgm;		// BGM
extern int sndTitle;	// タイトルBGM
extern int sndResult;	// リザルトBGM
extern int sndSe[MAX_SE];	// SE[MAX_SE]

/*
*  SEの種類
*/
enum SE_TYPE
{
	ATTACK,
	CANCEL,
	CRAFT,
	DIE,
	DECISION,
	ROCK,
	SELECT,
	WOOD,
	PICK,
};

// 初期化
BOOL DSoundInit( HWND hWnd, LPGUID lpGuid );

// 解放
BOOL DSoundRelease();

// サウンドの初期化
void InitSound();

/*
*  @brief SEスタート
*  @param type SEの識別タイプ
*/
void StartSE(int type);

// wavファイルの読み込み
enum {
	DSLF_FLG_DEFAULT = 0,
	DSLF_FLG_STATIC,
	DSLF_FLG_STREAM,
};
int DSoundLoadFile(
	LPSTR szFileName,		// ファイル名 or リソース
	int nChannel,			// 読み込みチャンネル番号(-1で空いてるチャンネルに追加)
	DWORD dwFlg				// フラグ DSLF_FLG_xxxx
);

// wavファイルの解放
BOOL DSoundReleaseChannel( int nChannel );

// 再生
BOOL DSoundPlay( int nChannel, BOOL bLoop );

// 停止
void DSoundStop( int nChannel );

// ボリュームセット
BOOL DSoundSetVolume( int nChannel,int nVolume );

// パンセット
BOOL DSoundSetPan( int nChannel, int nCmd );

// 再生中か？
BOOL DSoundIsStop( int nChannel );



#endif

