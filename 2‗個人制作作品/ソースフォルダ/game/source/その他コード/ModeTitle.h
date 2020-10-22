/**
 * @file ModeTitle.h
 * @brief タイトル処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"
#include "ModeGame.h"

namespace act {
	class ModeTitle : public ModeBase
	{
		typedef ModeBase base;
	public:
		/**
		 * インゲーム初期化
		 */
		virtual bool Initialize();

		/**
		 * インゲーム開放
		 */
		virtual bool Terminate();

		/**
		 * インゲーム処理
		 */
		virtual bool Process();

		/**
		 * インゲーム描画
		 */
		virtual bool Render();

	protected:
		int _bg;			// 背景
		int _start;			// スタート画像(キーボード)
		int _startpad;		// スタート画像(パッド)
		int _starttime;		// 開始時間
		int _stocktime;		// 経過時間
	};
}
