/**
 * @file Player.h
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"

namespace act {
	class Player {
	public:
		/**
		 * Playerコンストラクタ
		 */
		Player();

		/**
		 * Playerデストラクタ
		 */
		virtual ~Player() = default;

		/**
		 * プレイヤー初期化
		 */
		void Initialize();

		/**
		 * ゲッター(x座標)
		 * @return x座標
		 */
		int GetPosX() { return _PlayerX; }

		/**
		 * ゲッター(y座標)
		 * @return y座標
		 */
		int GetPosY() { return _PlayerY; }

		/**
		 * ゲッター(体力)
		 * @return 体力
		 */
		int GetHP() { return _Life; }

		/**
		 * 当たり判定用のx座標取得
		 * @return x座標
		 */
		int GetCollPosX() { return _PlayerX + (_PlayerWidth / 2) - PLAYER_COLLISION; }

		/**
		 * 当たり判定用のy座標取得
		 * @return y座標
		 */
		int GetCollPosY() { return _PlayerY + (_PlayerHeight / 2); }

		/**
		 * セッター(x座標)
		 * @param x x座標
		 * @return x座標
		 */
		int SetPosX(int x) { return _PlayerX = x; }

		/**
		 * セッター(y座標)
		 * @param y y座標
		 * @return y座標
		 */
		int SetPosY(int y) { return _PlayerY = y; }

		/**
		 * セッター(体力)
		 * @return 体力-1
		 */
		int SetHP() { return _Life--; }

		/**
		 * 移動処理
		 * @param key 押した瞬間の判定
		 * @param trg 押されっぱなしの判定
		 */
		void Move(int key, int trg);

		/**
		 * 描画処理
		 */
		void Draw();
	private:
		 // キャラの向き
		enum PlayerState {
			LOOK_RIGHT,
			LOOK_LEFT,
		};

		int _PlayerX, _PlayerY;				// x座標,y座標
		int _GhPlayer[12];					// グラフィックハンドル格納用配列（プレイヤー）
		int _Subscript;						// 添え字番号
		int _PlayerWidth, _PlayerHeight;	// 画像幅
		int _Life;							// 生きてるかどうかのフラグ
		int _CharaState;					// キャラの状態
	};
}
