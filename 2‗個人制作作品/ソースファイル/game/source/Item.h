/**
 * @file Item.cpp
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#pragma once

class Item
{
public:
	Item(int i);
	virtual ~Item();

	int GetPosX() { return _x; }
	int GetPosY() { return _y; }
	bool GetUseFlag() { return _use; }

	// 当たり判定用のポジション取得
	int GetCollPosX() { return _x + (_width / 2) - ITEM_COLLISION; }
	int GetCollPosY() { return _y + (_height / 2) - ITEM_COLLISION; }

	int SetPosX(int x) { return _x = x; }
	int SetPosY(int y) { return _y = y; }
	bool SetUseFlag() { return _use = false; }

	bool Move(int i);
	bool Draw();
private:
	void UseItem();
private:
	int _x, _y;				// x座標,y座標
	int _ghitem;			// グラフィックハンドル格納用配列
	int _width, _height;	// 画像幅
	bool _use;				// 使っているかどうかのフラグ
};
