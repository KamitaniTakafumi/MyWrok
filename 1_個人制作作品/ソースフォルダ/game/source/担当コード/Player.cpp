/**
 * @file Player.cpp
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "Player.h"
#include "Control.h"

namespace act {
	/**
	 * Playerコンストラクタ
	 */
	Player::Player()
	{
		//画像読み込み
		LoadBlkTexture("res/sample01.png", 80, 80, 3, 4, 12, _ghplayer);
		_ghhp = LoadTexture("res/heartP.png");
	}

	/**
	 * Playerデストラクタ
	 */
	Player::~Player()
	{
	}

	bool Player::Initialize()
	{
		_width = 80;
		_height = 80;
		_x = (WINDOW_WIDTH - _width) / 2;
		_y = WINDOW_HEIGHT - _height;
		_suffix = 6;

		_life = PLAYER_HP;

		_charastate = LOOK_RIGHT;
		return false;
	}

	/**
	 * 移動処理
	 * @param key 押した瞬間の判定
	 * @param trg 押されっぱなしの判定
	 */
	void Player::Move(int key, int trg)
	{
		// 移動処理
		if (KeyJudg(key, KEYIN_D) || PadJudg(key, KEYIN_RIGHT))
		{
			_x += PLAYER_SPEED;
			_charastate = LOOK_RIGHT;
		}
		if (KeyJudg(key, KEYIN_A) || PadJudg(key, KEYIN_LEFT))
		{
			_x -= PLAYER_SPEED;
			_charastate = LOOK_LEFT;
		}

		// 画面外判定
		if (_x < 0) { _x = 0; }
		if (_x > WINDOW_WIDTH - _width) { _x = WINDOW_WIDTH - _width; }

		// キャラの向きで添え字を変える
		if (_charastate == LOOK_RIGHT)
		{
			// 右向き
			if ((_suffix >= 3) && (_suffix < 6))
			{
				_suffix = 6;
			}
		}
		else if (_charastate == LOOK_LEFT)
		{
			// 左向き
			if ((_suffix >= 6) && (_suffix < 9))
			{
				_suffix = 3;
			}
		}

		// 時間で添え字を変える
		if ((gFpsCount % ((int)FRAME_NUM_PER_SEC / 2)) == 0)
		{
			_suffix++;	// 添え字を変える

			// キャラが右向き
			if (_charastate == LOOK_RIGHT)
			{
				// 添え字が範囲を越えたら戻す
				if (_suffix >= 9)
				{
					_suffix = 6;
				}
			}
			// キャラが左向き
			else if (_charastate == LOOK_LEFT)
			{
				// 添え字が範囲を越えたら戻す
				if (_suffix >= 6)
				{
					_suffix = 3;
				}
			}
		}

		SetPosX(_x);
	}

	/**
	 * 描画処理
	 */
	void Player::Draw()
	{
		// ライフが残っていればプレイヤー描画
		if (_life > 0)
		{
			DrawMemTh(_x, _y, _ghplayer[_suffix]);
		}
		// ライフ描画
		if (_life > 0)
		{
			DrawMemTh(0, 0, _ghhp);
		}
		if (_life > 1)
		{
			DrawMemTh(40, 0, _ghhp);
		}
		if (_life > 2)
		{
			DrawMemTh(80, 0, _ghhp);
		}
#ifdef _DEBUG
		DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (PLAYER_COLLISION * 2),
			GetCollPosY() + (PLAYER_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif // _DEBUG
	}
}
