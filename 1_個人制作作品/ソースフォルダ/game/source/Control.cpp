/**
 * @file Control.cpp
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "Control.h"

namespace act {
	/**
	 * コントロールコンストラクタ
	 */
	Control::Control()
	{
		
	}

	/**
	 * コントロールデストラクタ
	 */
	Control::~Control()
	{
		
	}

	/**
	 * コントロール初期化
	 */
	bool Control::Initialize()
	{
		player = std::make_unique<Player>();
		player->Initialize();

		for (int i = 0; i < ITEM_MAX; i++)
		{
			auto item = std::make_shared<Item>(i);
			itemvec.push_back(item);
			itemvec[i]->Initialize(i);
		}

		return true;
	}

	/**
	 * 移動処理
	 * @param key 押された瞬間の判定
	 * @param trg 押されっぱなしの判定
	 */
	void Control::Move(int key, int trg)
	{
		player->Move(key, trg);

		for (int i = 0; i < ITEM_MAX; i++)
		{
			itemvec[i]->Move(i);
		}
	}

	/**
	 * ゲッター(プレイヤー座標)
	 * @param x プレイヤーx座標
	 * @param y プレイヤーy座標
	 */
	void Control::GetPlayerPosition(double* x, double* y)
	{
		double tempx, tempy;

		tempx = player->GetPosX();
		tempy = player->GetPosY();

		*x = tempx;
		*y = tempy;
	}

	/**
	 * ゲッター(アイテム座標)
	 * @param index 添え字
	 * @param x アイテムx座標
	 * @param y アイテムy座標
	 */
	void Control::GetItemPosition(int index, double* x, double* y)
	{
		double tempx, tempy;
		//指定した添字の敵の座標を取得
		tempx = itemvec[index]->GetPosX();
		tempy = itemvec[index]->GetPosY();

		//代入
		*x = tempx;
		*y = tempy;
	}

	/**
	 * オブジェクト１とオブジェクト２の当たり判定
	 * @param c1 半径１
	 * @param c2 半径２
	 * @param cx1 x座標１
	 * @param cx2 x座標２
	 * @param cy1 y座標１
	 * @param cy2 y座標２
	 */
	bool Control::CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2)
	{

		double hlength = c1 + c2;
		double xlength = cx1 - cx2;
		double ylength = cy1 - cy2;

		if (hlength * hlength >= xlength * xlength + ylength * ylength) {
			return true;
		}
		else {
			return false;
		}
	}

	/**
	 * 全ての当たり判定
	 */
	void Control::CollisionAll()
	{
		double px, py, ix, iy;
		//操作キャラとアイテムとの当たり判定
		for (int i = 0; i < ITEM_MAX; ++i) {
			if (itemvec[i]->GetUseFlag() != true) { continue; }
			else
			{
				px = player->GetCollPosX();
				py = player->GetCollPosY();
				ix = itemvec[i]->GetCollPosX();
				iy = itemvec[i]->GetCollPosY();
				if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy))
				{
					itemvec[i]->SetUseFlag();
					if (i >= 50 && i < 100) { player->SetHP(); }
				}
			}
		}
	}

	/**
	 * プレイヤーの体力チェック
	 */
	bool Control::CheckPlayerHP()
	{
		if (player->GetHP() == 0)
		{
			return true;
		}

		return false;
	}

	/**
	 * 描画処理
	 */
	void Control::Draw()
	{
		for (int i = 0; i < ITEM_MAX; i++)
		{
			itemvec[i]->Draw();
		}
		player->Draw();
	}
}
