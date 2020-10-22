/**
 * @file Control.h
 * @brief コントロール処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"
#include "Player.h"
#include "Item.h"

namespace act {
	class Control
	{
	private:
		std::unique_ptr<Player> player;
		Item* item[ITEM_MAX];
	public:
		/**
		 * コントロールコンストラクタ
		 */
		Control();

		/**
		 * コントロールデストラクタ
		 */
		virtual ~Control();

		/**
		 * コントロール初期化
		 */
		bool Initialize();

		/**
		 * 移動処理
		 * @param key 押された瞬間の判定
		 * @param trg 押されっぱなしの判定
		 */
		void Move(int key, int trg);

		/**
		 * ゲッター(プレイヤー座標)
		 * @param x プレイヤーx座標
		 * @param y プレイヤーy座標
		 */
		void GetPlayerPosition(double* x, double* y);

		/**
		 * ゲッター(アイテム座標)
		 * @param index 添え字
		 * @param x アイテムx座標
		 * @param y アイテムy座標
		 */
		void GetItemPosition(int index, double* x, double* y);

		/**
		 * 全ての当たり判定
		 */
		void CollisionAll();

		/**
		 * プレイヤーの体力チェック
		 */
		bool CheckPlayerHP();

		/**
		 * 描画処理
		 */
		void Draw();
	private:
		/**
		 * オブジェクト１とオブジェクト２の当たり判定
		 * @param c1 半径１
		 * @param c2 半径２
		 * @param cx1 x座標１
		 * @param cx2 x座標２
		 * @param cy1 y座標１
		 * @param cy2 y座標２
		 */
		bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	protected:
	};
}
