/**
 * @file Item.cpp
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "appframe.h"
#include "Item.h"

Item::Item(int i)
{
	_width = 40;
	_height = 40;

	_x = 0 + 20*i;
	_y = 0 - _height;

	if ((i >= 0) && (i < 10)) { _ghitem = LoadTexture("res/jewelWhite.png"); }
	else if ((i >= 10) && (i < 20)) { _ghitem = LoadTexture("res/jewelGreen.png"); }
	else if ((i >= 20) && (i < 30)) { _ghitem = LoadTexture("res/jewelBlue.png"); }
	else if ((i >= 30) && (i < 40)) { _ghitem = LoadTexture("res/jewelRed.png"); }
	else if ((i >= 40) && (i < 50)) { _ghitem = LoadTexture("res/jewelGold.png"); }
	else if ((i >= 50) && (i < 100)) { _ghitem = LoadTexture("res/heartB.png"); }

	_use = false;
}

Item::~Item()
{
}

bool Item::Move(int i)
{
	if ((gFpsCount % (int)FRAME_NUM_PER_SEC) == 0)
	{
		if (_use != false) {}
		else
		{
			// 乱数でアイテムの使用を決める
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

	if (_use != true) { return false; }
	else
	{
		_y = _y + 1;
		if (_y > WINDOW_HEIGHT)
		{
			_use = false;
		}
	}

	return true;
}

void Item::UseItem()
{
	_x = (rand() % WINDOW_WIDTH) - _width;
	_y = 0 - _height;
	_use = true;
}

bool Item::Draw()
{
	if (_use != true) { return false; }
	else
	{
		DrawMemTh(_x, _y, _ghitem);
#ifdef MODE_DEBUG
		DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (ITEM_COLLISION * 2), 
			GetCollPosY() + (ITEM_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif
	}

	return true;
}
