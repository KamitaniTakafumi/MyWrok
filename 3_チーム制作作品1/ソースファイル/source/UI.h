#pragma once
//
// íËêîÅEç\ë¢ëÃíËã`
//
struct FRAME {
	int cg;
	int x, y;
	int w, h;
	int move;
};

struct HEART {
	int use;
	int x, y;
};

struct EQUIPMENT {
	int x, y;
};

struct DESCRIPTION {
	int x, y;
};

#define FRAME_MAX 3
#define	HP_MAX 6

extern struct FRAME frm[FRAME_MAX];
extern struct HEART hrt[HP_MAX];
extern struct EQUIPMENT eq;
extern struct DESCRIPTION de;

extern int healthAlpha;
extern int ButtonB;
extern int ButtonA;
extern int ButtonY;
extern int ButtonX;
extern int ButtonRB;
extern int ButtonLB;
extern int cgSystemButton;

void LoadCgUi();

void LoadCgHealth();

void InitItemColumn();

void InitSystem();

void InitEquipment();

void InitDescription();

void FrameControll();

void SystemWait();

void DrawAliceHealth();

void DrawItemColumn();

void DrawSystem();

void DrawEquipment(int x, int y, int itemNumber);
void DrawItemEquipment(int x, int y, int itemNumber);

void DrawDescription();