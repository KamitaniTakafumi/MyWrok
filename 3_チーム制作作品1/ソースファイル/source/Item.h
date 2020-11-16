#pragma once

struct ITEM {
	int cg;
	int w, h;
	int number;
};

struct USEITEM {
	int use;
	int x, y;
	int number;
	int cg;
	int equipmentx, equipmenty;
};

struct FIRSTCREATE {
	int x, y;
	float vx, vy;
	int cg;
	int use;
	int no;
};

#define ITEM_NUMBER 19
#define ITEM_MAX 10
#define USEITEM_MAX 20

extern struct ITEM item[ITEM_NUMBER];
extern struct USEITEM useit[USEITEM_MAX];
extern struct FIRSTCREATE fc[3];

extern int toge_bakudan;
extern int potion;
extern int naifu;
extern int potionM;

extern int createalpha;

void LoadCgItem();                         //ƒAƒCƒeƒ€
void InitItem();
void InitUseItem();
void InitFirstCreate(int Mno1, int Mno2, int Mno3, int itemno);

void FirstCreate();

void GetItem(int itemId, int itemNumber);
void GetItem2(int itemId, int itemNumber, int itemNumber2);

void PickItem(int x, int y, int wait);

void ItemDamage(int enemyId);

void DrawItem(int itemId);

void DrawEquipmentItem();

void DrawFirstCreate();