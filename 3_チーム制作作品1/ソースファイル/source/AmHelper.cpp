/*
** AMライブラリ ヘルパー
*/

#include	<Windows.h>
#include	<stdio.h>

#include	"amgame.h"
#include	"AmHelper.h"



// printf()的に DrawString()を使う関数
void DrawPrintf( int x, int y, int nColor, const char *fmt, ... ) {
	// printfのような、引数の数が確定していない場合、 ... という記述をする
	// これは va_list で取得できる
	// これらの仕組みを理解するのであれば vsprintf() について調べると良い

	// fmt 以下の引数から、sz[] に文字列を作り出す
	char sz[0xffff];		// 配列数が[0xffff]なのは、これくらいあれば足りるだろう的サイズ。もし溢れたら問題が出る。
	va_list list;
	va_start( list, fmt );
	vsprintf( sz, fmt, list );
	va_end( list );

	// 作り出した文字列 sz[] を使って画面に文字列を描画する
	DrawString( x, y, sz, nColor );

}



// 線の描画
// (x1,y1) - (x2,y2)
void DrawLine( int x1, int y1, int x2, int y2, int color ) {
	int x, y;
	// 線形補完をしつつ描画する
	// x, y の長い方をベースにループ
	if ( abs(x1-x2) > abs(y1-y2) ) {
		// xベース
		if ( x1 > x2 ) {
			x = x1; x1 = x2; x2 = x;
			y = y1; y1 = y2; y2 = y;
		}
		for ( x = 0; x <= x2 - x1; x++ ) {
			y = y1 + ( y2 - y1 ) * x / ( x2 - x1 );
			DrawPixel( x1 + x, y, color );
		}
	} else {
		// yベース
		if ( y1 > y2 ) {
			x = x1; x1 = x2; x2 = x;
			y = y1; y1 = y2; y2 = y;
		}
		for ( y = 0; y <= y2 - y1; y++ ) {
			x = x1 + ( x2 - x1 ) * y / ( y2 - y1 );
			DrawPixel( x, y1 + y, color );
		}
	}
}


// 円の描画
// 中心(x,y) 半径r
void DrawCircle( int x, int y, int r, int color ) {
	// プレゼンハムによる円描画
	int cx, cy, d;
	cx = 0;
    cy = r;
    d = 2 - 2 * r;

	// 開始点の描画
	DrawPixel(  cx + x,  cy + y, color );	//  (0, R);
    DrawPixel(  cx + x, -cy + y, color );	//  (0, -R);
    DrawPixel(  cy + x,  cx + y, color );	//  (R, 0);
    DrawPixel( -cy + x,  cx + y, color );	//  (-R, 0);

	// 90度ループ
	while (1) {
		if (d > -cy) {
			cy--;
			d += 1 - 2 * cy;
		}

		if (d <= cx) {
			cx++;
			d += 1 + 2 * cx;
		}

		if (!cy) break;    // 描画終了

		// 描画
		DrawPixel(  cx + x,  cy + y, color );	// 0～90度の間
		DrawPixel( -cx + x,  cy + y, color );	// 90～180度の間
		DrawPixel( -cx + x, -cy + y, color );	// 180～270度の間
		DrawPixel(  cx + x, -cy + y, color );	// 270～360度の間
	}
}

// 画面のキャプチャを正しく行う
// GetDispGraph()は座標位置がずれる問題有り
int		GetDispGraphToTexture(int hPicture) {
	POINT pt = { 0,0 };
	ClientToScreen(gg_hWindow, &pt);
	gg_piDispLocate.x = pt.x;
	gg_piDispLocate.y = pt.y;
	return GetDispGraph(hPicture);
}

