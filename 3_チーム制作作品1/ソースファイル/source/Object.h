#pragma once

// 定数・構造体定義
struct OBJECT
{
	int use;
	int cg;
	int x, y;
	int	w, h;
	int	hit_x, hit_y, hit_w, hit_h;
	int gatherlimit;
	int getwait;
	int nogetwait;
};

struct FUKIDASHI {
	int x, y;
	int w, h;
};

#define OBJECT_MAX 30

extern struct OBJECT obj[OBJECT_MAX];
extern struct FUKIDASHI fk;

// 画像データ
extern int cgMaterial[2];
extern int cgMaterial_White[2];
extern int cgFukidashi;

void LoadCgObject();
void LoadCgFukidashi();
void LoadCgFukidashi2();

void InitObject();
void InitObject2();
void InitFukidashi();
void InitFukidashi2();

void HitCheckPlayerObject();

void TouchObject();
void TouchObject2();

void ReGetMaterialWait();
void ReGetMaterialWait2();

void DrawObject();
void DrawObject2();
void DrawFukidashi();
void DrawFukidashi2();