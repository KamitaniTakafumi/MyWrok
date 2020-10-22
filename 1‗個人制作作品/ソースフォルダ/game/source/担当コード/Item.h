/**
 * @file Item.h
 * @brief アイテム処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"

namespace act {
	class Item
	{
	public:
		/**
		 * Itemコンストラクタ
		 */
		Item(int i);

		/**
		 * Itemデストラクタ
		 */
		virtual ~Item();

		/**
		 * ゲッター(x座標)
		 * @return x座標
		 */
		int GetPosX() { return _x; }

		/**
		 * ゲッター(y座標)
		 * @return y座標
		 */
		int GetPosY() { return _y; }

		/**
		 * ゲッター(フラグ)
		 * @return フラグ
		 */
		bool GetUseFlag() { return _use; }

		/**
		 * 当たり判定用のx座標取得
		 * @return x座標
		 */
		int GetCollPosX() { return _x + (_width / 2) - ITEM_COLLISION; }

		/**
		 * 当たり判定用のy座標取得
		 * @return y座標
		 */
		int GetCollPosY() { return _y + (_height / 2) - ITEM_COLLISION; }

		/**
		 * セッター(x座標)
		 * @param x x座標
		 * @return x座標
		 */
		int SetPosX(int x) { return _x = x; }

		/**
		 * セッター(y座標)
		 * @param y y座標
		 * @return y座標
		 */
		int SetPosY(int y) { return _y = y; }

		/**
		 * セッター(フラグ)
		 * @return フラグ
		 */
		bool SetUseFlag() { 
			if (_use == true) { _use = false; }
			return _use;
		}

		/**
		 * 移動処理
		 * @param i 添え字
		 * @return アイテムが使用状態ならtrue
		 */
		bool Move(int i);

		/**
		 * 描画処理
		 * @return アイテムが使用状態ならtrue
		 */
		bool Draw();
	private:
		/**
		 * フラグ処理
		 */
		void UseItem();
	private:
		enum ItemType {
			WHITE_JEWEL,
			GREEN_JEWEL,
			BLUE_JEWEL,
			RED_JEWEL,
			GOLD_JEWEL,
			BLACK_HEART,
		};

		int _x, _y;				// x座標,y座標
		int _ghitem[6];			// グラフィックハンドル格納用配列
		int _width, _height;	// 画像幅
		int _speed;				// 落下スピード
		int _itemtype;
		bool _use;				// 使っているかどうかのフラグ
	};
}
