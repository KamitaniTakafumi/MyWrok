#ifndef __AMHELPER_H__
#define __AMHELPER_H__
/*
** AMライブラリ ヘルパー
*/


#include	<Windows.h>
#include	<stdio.h>
#include	"amgame.h"


// 一部warningを出さないようにする設定
#pragma warning(disable : 4996)



// printf()的に DrawString()を使う関数
void	DrawPrintf( int x, int y, int nColor, const char *fmt, ... );

// 線の描画
// (x1,y1) - (x2,y2)
void	DrawLine( int x1, int y1, int x2, int y2, int color );


// 円の描画
// 中心(x,y) 半径r
void	DrawCircle( int x, int y, int r, int color );


// 画面のキャプチャを正しく行う
// GetDispGraph()は座標位置がずれる問題有り
int		GetDispGraphToTexture(int hPicture);



#endif // !__AMHELPER_H__
