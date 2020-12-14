/**
 * @file Item.cpp
 * @brief アイテム処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "appframe.h"
#include "Item.h"

namespace act {
	/**
	 * Itemコンストラクタ
	 */
	Item::Item() :
		_x(0), _y(0), _ghitem(0), _width(0), _height(0),
		_speed(0), _use(true), _ItemType(0) {
	}

	/**
	 * アイテム初期化
	 * @param i 添え字
	 */
	void Item::Initialize(int i) {
		_width = 40;
		_height = 40;

		_x = 0 + 20 * i;
		_y = 0 - _height;

		_speed = 0;

		// 画像読み込み
		// アイテム別に種類を決める
		if ((i >= 0) && (i < 10)) { 
			_ItemType = White;
			_ghitem = LoadTexture("res/jewelwhite.png");
		}
		else if ((i >= 10) && (i < 20)) {
			_ItemType = Green;
			_ghitem = LoadTexture("res/jewelgreen.png");
		}
		else if ((i >= 20) && (i < 30)) {
			_ItemType = Blue;
			_ghitem = LoadTexture("res/jewelblue.png");
		}
		else if ((i >= 30) && (i < 40)) {
			_ItemType = Red;
			_ghitem = LoadTexture("res/jewelred.png");
		}
		else if ((i >= 40) && (i < 50)) {
			_ItemType = Gold;
			_ghitem = LoadTexture("res/jewelgold.png");
		}
		else if ((i >= 50) && (i < 100)) {
			_ItemType = HeartBlack;
			_ghitem = LoadTexture("res/heartb.png");
		}

		_use = false;
	}

	/**
	 * 移動処理
	 * @param i 添え字
	 * @return アイテムが使用状態ならtrue
	 */
	bool Item::Move(int i) {
		// 一定間隔(60フレームに1回)で処理
		if ((gFpsCount % (int)FRAME_NUM_PER_SEC) == 0) {
			// アイテムが使用状態ならスルー
			if (_use != false) {}
			else {
				// 種類別に乱数でアイテムの使用を決める
				JudgmentItem();
			}
		}

		// アイテムが使用状態でなければ処理を抜ける
		if (_use != true) { return false; }
		else {
			_y = _y + _speed;
			// 画面外に出たらフラグを戻す
			if (_y > WINDOW_HEIGHT) {
				_use = false;
			}
		}

		return true;
	}

	/**
	 * フラグ処理
	 */
	void Item::UseItem() {
		_x = (rand() % WINDOW_WIDTH) - _width;
		_y = 0 - _height;
		_speed = (rand() % 4) + 1;
		_use = true;
	}

	/**
	 *  種類別のアイテム使用判定
	 */
	void Item::JudgmentItem() {
		int Probability = 0;	// アイテムの使用確率
		// 種類別に確率を決める
		switch (_ItemType) {
		case White:
			Probability = 30;
			break;
		case Green:
			Probability = 25;
			break;
		case Blue:
			Probability = 20;
			break;
		case Red:
			Probability = 15;
			break;
		case Gold:
			Probability = 10;
			break;
		case HeartBlack:
			Probability = 20;
			break;
		default:
			Probability = 0;
			break;
		}

		// 乱数より確率が大きければアイテムを使用
		if ((rand() % 100) < Probability) {
			UseItem();
		}
	}

	/**
	 * 描画処理
	 * @return アイテムが使用状態ならtrue
	 */
	bool Item::Draw() {
		if (_use != true) { return false; }
		else {
			DrawMemTh(_x, _y, _ghitem);
#ifdef _DEBUG
			DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (ITEM_COLLISION * 2),
				GetCollPosY() + (ITEM_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif
		}

		return true;
	}
}
