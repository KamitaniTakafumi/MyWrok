#pragma once

// 定数・構造体定義
struct RECIPE
{
	int use;
	int cg_none;
	int cg_one;
	int x, y;
	int w, h;
};

#define RECIPE_MAX 20

// レシピ情報
extern struct RECIPE re[RECIPE_MAX];

extern int GetRecipe;
extern int recipe1;
extern int recipe2;
extern int recipe3;
extern int on1;
extern int on2;
extern int on3;
extern int on4;
extern int on5;
extern int on6;

void LoadCgRecipe();

void InitRecipe();

void DrawRecipe();

void DrawGetRecipe();