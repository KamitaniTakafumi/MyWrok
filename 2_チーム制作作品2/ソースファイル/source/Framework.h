#pragma once
/*
 * @file Framework.cpp
 * @brief フレームワーク処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include	"library.h"
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#define	FPS_60		0	//	固定６０フレーム
#define	FPS_30		1	//	固定３０フレーム
#define	FPS_FLEX	2	//	可変フレーム

/*------------------------------------------------
*  フレームワーク構造体
------------------------------------------------*/
struct Framework
{
	int bRender;
	unsigned char FPSMode;		//	フレーム制御モード
	unsigned long dwGameFrame;	//	起動からのフレーム数
	unsigned long dwFrameTime;
	unsigned long dwFPS;			//	処理フレームレート
	unsigned long dwRenderFPS;	//	描画フレームレート
	unsigned long dwCurFrame;		//	処理カウンタ
	unsigned long dwRCurFrame;	//	描画カウンタ
};

// フレームワーク情報
extern struct Framework frm;

/*
*  @brief フレームワーク初期化
*  @param InitFPSMode FPSモード
*/
void InitFramework(int InitFPSMode);
// フレームワークアップデート
int UpdateFramework();
// フレームワーク描画
void RenderFramework();

#endif
