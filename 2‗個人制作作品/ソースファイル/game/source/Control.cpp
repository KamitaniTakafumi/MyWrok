/**
 * @file Control.cpp
 * @brief ˆ—
 * @author ã’J‹±j
 * @date 2020 / 08 / 25
 */

#include "Control.h"

Control::Control()
{
	player = new Player;
	for (int i = 0; i < ITEM_MAX; i++)
	{
		item[i] = new Item(i);
	}
}

Control::~Control()
{
	delete player;
	for (int i = 0; i < ITEM_MAX; i++)
	{
		delete item[i];
	}
}

void Control::Move(int key, int trg)
{
	player->Move(key, trg);
	for (int i = 0; i < ITEM_MAX; i++)
	{
		item[i]->Move(i);
	}
}

void Control::GetPlayerPosition(double *x, double *y)
{
	double tempx, tempy;

	tempx = player->GetPosX();
	tempy = player->GetPosY();

	*x = tempx;
	*y = tempy;
}

void Control::GetItemPosition(int index, double *x, double *y)
{
	double tempx, tempy;
	//w’è‚µ‚½“Yš‚Ì“G‚ÌÀ•W‚ğæ“¾
	tempx = item[index]->GetPosX();
	tempy = item[index]->GetPosY();

	//‘ã“ü
	*x = tempx;
	*y = tempy;
}

bool Control::CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2)
{

	double hlength = c1 + c2;
	double xlength = cx1 - cx2;
	double ylength = cy1 - cy2;

	if (hlength*hlength >= xlength * xlength + ylength * ylength) {
		return true;
	}
	else {
		return false;
	}
}

void Control::CollisionAll()
{
	double px, py, ix, iy;
	//‘€ìƒLƒƒƒ‰‚ÆƒAƒCƒeƒ€‚Æ‚Ì“–‚½‚è”»’è
	for (int i = 0; i < ITEM_MAX; ++i) {
		if (item[i]->GetUseFlag() != true) { continue; }
		else
		{
			px = player->GetCollPosX();
			py = player->GetCollPosY();
			ix = item[i]->GetCollPosX();
			iy = item[i]->GetCollPosY();
			if (CircleCollision(PLAYER_COLLISION, ITEM_COLLISION, px, ix, py, iy))
			{
				item[i]->SetUseFlag();
				if (i >= 50 && i < 100) { player->SetHP(); }
			}
		}
	}
}

bool Control::CheckPlayerHP()
{
	if (player->GetHP() == 0)
	{
		return true;
	}

	return false;
}

void Control::Draw()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		item[i]->Draw();
	}
	player->Draw();
}
