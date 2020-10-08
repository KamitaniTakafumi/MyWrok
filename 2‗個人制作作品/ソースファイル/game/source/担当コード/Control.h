/**
 * @file Control.cpp
 * @brief èàóù
 * @author è„íJã±éj
 * @date 2020 / 08 / 25
 */

#pragma once
#include "appframe.h"
#include "Player.h"
#include "Item.h"

class Control
{
private:
	Player* player;
	Item* item[ITEM_MAX];
public:
	Control();
	virtual ~Control();
	void Move(int key, int trg);
	void GetPlayerPosition(double *x, double *y);
	void GetItemPosition(int index, double *x, double *y);
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	void CollisionAll();
	bool CheckPlayerHP();
	void Draw();
	static Control& GetInstance() {
		static Control control;
		return control;
	}
protected:
};
