/**
 * @file Player.h
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"

namespace act {
	class Player
	{
	public:
		/**
		 * Playerコンストラクタ
		 */
		Player();

		/**
		 * Playerデストラクタ
		 */
		virtual ~Player();

		/**
		 * プレイヤー初期化
		 */
		bool Initialize();

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
		 * ゲッター(体力)
		 * @return 体力
		 */
		int GetHP() { return _life; }

		/**
		 * 当たり判定用のx座標取得
		 * @return x座標
		 */
		int GetCollPosX() { return _x + (_width / 2) - PLAYER_COLLISION; }

		/**
		 * 当たり判定用のy座標取得
		 * @return y座標
		 */
		int GetCollPosY() { return _y + (_height / 2); }

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
		 * セッター(体力)
		 * @return 体力-1
		 */
		int SetHP() { return _life--; }

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

		/**
		 * キャラの向き
		 */
		enum PlayerState
		{
			LOOK_RIGHT,
			LOOK_LEFT,
		};

		int _x, _y;				// x座標,y座標
		int _ghplayer[12];		// グラフィックハンドル格納用配列（プレイヤー）
		int _ghhp;				// グラフィックハンドル（ヒットポイント）
		int _suffix;			// 添え字番号
		int _width, _height;	// 画像幅
		int _life;				// 生きてるかどうかのフラグ
		int _charastate;		// キャラの状態
	};
}
