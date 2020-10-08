/**
 * @file Player.cpp
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#pragma once

/**
 * キャラの向き
 */
enum PlayerState
{
	LOOK_RIGHT,
	LOOK_LEFT,
};

class Player
{
public:
	Player();
	virtual ~Player();

	int GetPosX() { return _x; }
	int GetPosY() { return _y; }
	int GetHP() { return _life; }

	// 当たり判定用のポジション取得
	int GetCollPosX() { return _x + (_width / 2) - PLAYER_COLLISION; }
	int GetCollPosY() { return _y + (_height / 2); }
	
	int SetPosX(int x) { return _x = x; }
	int SetPosY(int y) { return _y = y; }
	int SetHP() { return _life--; }

	void Move(int key, int trg);
	void Draw();
private:
	int _x, _y;				// x座標,y座標
	int _graphnum;			// 分割画像数
	int _ghplayer[12];		// グラフィックハンドル格納用配列（プレイヤー）
	int _ghhp;				// グラフィックハンドル（ヒットポイント）
	int _suffix;			// 添え字番号
	int _width, _height;	// 画像幅
	int _life;				// 生きてるかどうかのフラグ
	int _charastate;		// キャラの状態
};
