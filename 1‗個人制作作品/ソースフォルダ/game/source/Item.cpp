/**
 * @file Item.cpp
 * @brief アイテム処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "Item.h"

namespace act {
	/**
	 * Itemコンストラクタ
	 * @param i 添え字
	 */
	Item::Item(int i)
	{
		_width = 40;
		_height = 40;

		_x = 0 + 20 * i;
		_y = 0 - _height;

		if ((i >= 0) && (i < 10)) { _itemtype = WHITE_JEWEL; }
		else if ((i >= 10) && (i < 20)) { _itemtype = GREEN_JEWEL; }
		else if ((i >= 20) && (i < 30)) { _itemtype = BLUE_JEWEL; }
		else if ((i >= 30) && (i < 40)) { _itemtype = RED_JEWEL; }
		else if ((i >= 40) && (i < 50)) { _itemtype = GOLD_JEWEL; }
		else if ((i >= 50) && (i < 100)) { _itemtype = BLACK_HEART; }

		_speed = 0;

		_use = false;

		// 画像読み込み
		_ghitem[0] = LoadTexture("res/jewelWhite.png");
		_ghitem[1] = LoadTexture("res/jewelGreen.png");
		_ghitem[2] = LoadTexture("res/jewelBlue.png");
		_ghitem[3] = LoadTexture("res/jewelRed.png");
		_ghitem[4] = LoadTexture("res/jewelGold.png");
		_ghitem[5] = LoadTexture("res/heartB.png");
	}

	/**
	 * Itemデストラクタ
	 */
	Item::~Item()
	{
	}

	/**
	 * 移動処理
	 * @param i 添え字
	 * @return アイテムが使用状態ならtrue
	 */
	bool Item::Move(int i)
	{
		// 一定間隔(60フレームに1回)で処理
		if ((gFpsCount % (int)FRAME_NUM_PER_SEC) == 0)
		{
			// アイテムが使用状態ならスルー
			if (_use != false) {}
			else
			{
				// 種類別に乱数でアイテムの使用を決める
				if ((i >= 0) && (i < 10))
				{
					if ((rand() % 100) < 30)
					{
						UseItem();
					}
				}
				else if ((i >= 10) && (i < 20))
				{
					if ((rand() % 100) < 25)
					{
						UseItem();
					}
				}
				else if ((i >= 20) && (i < 30))
				{
					if ((rand() % 100) < 20)
					{
						UseItem();
					}
				}
				else if ((i >= 30) && (i < 40))
				{
					if ((rand() % 100) < 15)
					{
						UseItem();
					}
				}
				else if ((i >= 40) && (i < 50))
				{
					if ((rand() % 100) < 10)
					{
						UseItem();
					}
				}
				else if ((i >= 50) && (i < 100))
				{
					if ((rand() % 100) < 20)
					{
						UseItem();
					}
				}
			}
		}

		// アイテムが使用状態でなければ処理を抜ける
		if (_use != true) { return false; }
		else
		{
			_y = _y + _speed;
			// 画面外に出たらフラグを戻す
			if (_y > WINDOW_HEIGHT)
			{
				_use = false;
			}
		}

		return true;
	}

	/**
	 * フラグ処理
	 */
	void Item::UseItem()
	{
		_x = (rand() % WINDOW_WIDTH) - _width;
		_y = 0 - _height;
		_speed = (rand() % 4) + 1;
		_use = true;
	}

	/**
	 * 描画処理
	 * @return アイテムが使用状態ならtrue
	 */
	bool Item::Draw()
	{
		if (_use != true) { return false; }
		else
		{
			if (_itemtype == WHITE_JEWEL) {
				DrawMemTh(_x, _y, _ghitem[0]);
			}
			else if (_itemtype == GREEN_JEWEL) {
				DrawMemTh(_x, _y, _ghitem[1]);
			}
			else if (_itemtype == BLUE_JEWEL) {
				DrawMemTh(_x, _y, _ghitem[2]);
			}
			else if (_itemtype == RED_JEWEL) {
				DrawMemTh(_x, _y, _ghitem[3]);
			}
			else if (_itemtype == GOLD_JEWEL) {
				DrawMemTh(_x, _y, _ghitem[4]);
			}
			else if (_itemtype == BLACK_HEART) {
				DrawMemTh(_x, _y, _ghitem[5]);
			}
#ifdef _DEBUG
			DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (ITEM_COLLISION * 2),
				GetCollPosY() + (ITEM_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif
		}

		return true;
	}
}
