/**
 * @file ApplicationMain.h
 * @brief アプリケーション処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "appframe.h"

namespace act {
	class ApplicationMain : public ApplicationBase {
		typedef ApplicationBase base;
	public:
		/**
		 * 起動時初期化
		 * @param hInstance インスタンスハンドル
		 */
		virtual bool Initialize(HINSTANCE hInstance);

		/**
		 * 解放
		 * @return 問題なければtrue
		 */
		virtual bool Terminate();

		/**
		 * キー入力
		 * @return 問題なければtrue
		 */
		virtual bool Input();

		/**
		 * フレーム処理
		 * @return 問題なければtrue
		 */
		virtual bool Process();

		/**
		 * 描画
		 * @return 問題なければtrue
		 */
		virtual bool Render();

		/**
		 * アプリケーションウィンドウ
		 * @return 問題なければtrue
		 */
		virtual bool AppWindowed() { return true; }

		/**
		 * ウィンドウサイズ(横幅)
		 * @return 1280
		 */
		virtual int DispSizeW() { return 1280; }

		/**
		 * ウィンドウサイズ(高さ)
		 * @return 720
		 */
		virtual int DispSizeH() { return 720; }

	protected:

	};
}
