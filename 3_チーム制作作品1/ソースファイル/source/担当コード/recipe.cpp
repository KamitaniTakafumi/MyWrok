#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include    "recipe.h"
#include	"preparation.h"
#include	"global.h"
#include	"UI.h"
#include	"alice.h"
#include	"camera.h"
#include	"HitJudgment.h"

// 画像データ
int cgRecipe_1[2];
int cgRecipe_2[2];
int cgRecipe_3[2];
int cgRecipe_4[2];
int cgRecipe_5[2];
int cgRecipe_6[2];
int cgRecipe_7[2];
int cgRecipe_8[2];
int cgRecipe_9[2];

int cgRecipe_10[2];
int cgRecipe_11[2];
int cgRecipe_12[2];
int cgRecipe_13[2];
int cgRecipe_14[2];
int cgRecipe_15[2];
int cgRecipe_16[2];
int cgRecipe_17[2];

int cgRecipe_18;
int cgRecipe_19;

int cgwindow_recipe;
int cgflash;

int GetRecipe;
int recipe1;
int recipe2;
int recipe3;
int on1;
int on2;
int on3;
int on4;
int on5;
int on6;

// レシピ情報
struct RECIPE re[RECIPE_MAX];

// 画像読み込み
void LoadCgRecipe()
{
	cgRecipe_1[0] = LoadTexture("res/togeB_resipi_kage.png");
	cgRecipe_1[1] = LoadTexture("res/togeB_resipi.png");
	cgRecipe_2[0] = LoadTexture("res/kaenB_resipi_kage.png");
	cgRecipe_2[1] = LoadTexture("res/kaenB_resipi.png");
	cgRecipe_3[0] = LoadTexture("res/koriB_resipi_kage.png");
	cgRecipe_3[1] = LoadTexture("res/koriB_resipi.png");
	cgRecipe_4[0] = LoadTexture("res/kaminariB_resipi_kage.png");
	cgRecipe_4[1] = LoadTexture("res/kaminariB_resipi.png");
	cgRecipe_5[0] = LoadTexture("res/potion_resipi_kage.png");
	cgRecipe_5[1] = LoadTexture("res/potion_resipi.png");
	cgRecipe_6[0] = LoadTexture("res/potionM_resipi_kage.png");
	cgRecipe_6[1] = LoadTexture("res/potionM_resipi.png");
	cgRecipe_7[0] = LoadTexture("res/naifu_resipi_kage.png");
	cgRecipe_7[1] = LoadTexture("res/naifu_resipi.png");
	cgRecipe_8[0] = LoadTexture("res/naifu_kaen_resipi_kage.png");
	cgRecipe_8[1] = LoadTexture("res/naifu_kaen_resipi.png");
	cgRecipe_9[0] = LoadTexture("res/naifu_reitou_resipi_kage.png");
	cgRecipe_9[1] = LoadTexture("res/naifu_reitou_resipi.png");
	cgRecipe_10[0] = LoadTexture("res/naifu_dengeki_resipi_kage.png");
	cgRecipe_10[1] = LoadTexture("res/naifu_dengeki_resipi.png");

	cgRecipe_11[0] = LoadTexture("res/kaenBS_resipi_kage.png");
	cgRecipe_11[1] = LoadTexture("res/kaenBS_resipi.png");
	cgRecipe_12[0] = LoadTexture("res/koriBS_resipi_kage.png");
	cgRecipe_12[1] = LoadTexture("res/koriBS_resipi.png");
	cgRecipe_13[0] = LoadTexture("res/kaminariBS_resipi_kage.png");
	cgRecipe_13[1] = LoadTexture("res/kaminariBS_resipi.png");
	cgRecipe_14[0] = LoadTexture("res/potionL_resipi_kage.png");
	cgRecipe_14[1] = LoadTexture("res/potionL_resipi.png");
	cgRecipe_15[0] = LoadTexture("res/naifu_kaenS_resipi_kage.png");
	cgRecipe_15[1] = LoadTexture("res/naifu_kaenS_resipi.png");
	cgRecipe_16[0] = LoadTexture("res/naifu_reitouS_resipi_kage.png");
	cgRecipe_16[1] = LoadTexture("res/naifu_reitouS_resipi.png");
	cgRecipe_17[0] = LoadTexture("res/naifu_dengekiS_resipi_kage.png");
	cgRecipe_17[1] = LoadTexture("res/naifu_dengekiS_resipi.png");

	cgRecipe_18 = LoadTexture("res/recipi_hatena.png");
	cgRecipe_19 = LoadTexture("res/recipi_hatena2.png");

	cgwindow_recipe = LoadTexture("res/window_recipe.png");
	cgwindow_log = LoadTexture("res/window_system3.png");

	cgflash = LoadTexture("res/flash.png");
}

// レシピ初期化
void InitRecipe()
{
	int i;

	GetRecipe = 0;
	recipe1 = 0;
	recipe2 = 0;
	recipe3 = 0;
	switch (bgstage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
		on1 = 0;
		on2 = 0;
		on3 = 0;
		break;
	case STATE_EP1STAGE_3:
		on3 = 0;
		break;
	}
	switch (bgstage2) {
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
		on4 = 0;
		on5 = 0;
		on6 = 0;
		break;
	case STATE_EP2STAGE2_1:
		on6 = 0;
		break;
	}

	for (i = 0; i < 17; i++) {
		re[i].use = 0;
		//re[i].use = 1;			// レシピの開放(開発用)
	}

	// 1ページ目
	i = 0;
	re[i].cg_none = cgRecipe_1[0];
	re[i].cg_one = cgRecipe_1[1];
	re[i].x = 140;
	re[i].y = 190;
	re[i].w = 400;
	re[i].h = 60;

	i = 1;
	re[i].cg_none = cgRecipe_2[0];
	re[i].cg_one = cgRecipe_2[1];
	re[i].x = 140;
	re[i].y = 270;
	re[i].w = 400;
	re[i].h = 60;

	i = 2;
	re[i].cg_none = cgRecipe_3[0];
	re[i].cg_one = cgRecipe_3[1];
	re[i].x = 140;
	re[i].y = 350;
	re[i].w = 400;
	re[i].h = 60;

	i = 3;
	re[i].cg_none = cgRecipe_4[0];
	re[i].cg_one = cgRecipe_4[1];
	re[i].x = 140;
	re[i].y = 430;
	re[i].w = 400;
	re[i].h = 60;

	i = 4;
	re[i].cg_none = cgRecipe_5[0];
	re[i].cg_one = cgRecipe_5[1];
	re[i].x = 140;
	re[i].y = 510;
	re[i].w = 400;
	re[i].h = 60;

	i = 5;
	re[i].cg_none = cgRecipe_6[0];
	re[i].cg_one = cgRecipe_6[1];
	re[i].x = 140;
	re[i].y = 590;
	re[i].w = 400;
	re[i].h = 60;

	// 2ページ目
	i = 6;
	re[i].cg_none = cgRecipe_7[0];
	re[i].cg_one = cgRecipe_7[1];
	re[i].x = 140;
	re[i].y = 190;
	re[i].w = 400;
	re[i].h = 60;

	i = 7;
	re[i].cg_none = cgRecipe_8[0];
	re[i].cg_one = cgRecipe_8[1];
	re[i].x = 140;
	re[i].y = 270;
	re[i].w = 400;
	re[i].h = 60;

	i = 8;
	re[i].cg_none = cgRecipe_9[0];
	re[i].cg_one = cgRecipe_9[1];
	re[i].x = 140;
	re[i].y = 350;
	re[i].w = 400;
	re[i].h = 60;

	i = 9;
	re[i].cg_none = cgRecipe_10[0];
	re[i].cg_one = cgRecipe_10[1];
	re[i].x = 140;
	re[i].y = 430;
	re[i].w = 400;
	re[i].h = 60;

	i = 10;
	re[i].cg_none = cgRecipe_11[0];
	re[i].cg_one = cgRecipe_11[1];
	re[i].x = 140;
	re[i].y = 510;
	re[i].w = 400;
	re[i].h = 60;

	i = 11;
	re[i].cg_none = cgRecipe_12[0];
	re[i].cg_one = cgRecipe_12[1];
	re[i].x = 140;
	re[i].y = 590;
	re[i].w = 400;
	re[i].h = 60;

	// 3ページ目
	i = 12;
	re[i].cg_none = cgRecipe_13[0];
	re[i].cg_one = cgRecipe_13[1];
	re[i].x = 140;
	re[i].y = 190;
	re[i].w = 400;
	re[i].h = 60;

	i = 13;
	re[i].cg_none = cgRecipe_14[0];
	re[i].cg_one = cgRecipe_14[1];
	re[i].x = 140;
	re[i].y = 270;
	re[i].w = 400;
	re[i].h = 60;

	i = 14;
	re[i].cg_none = cgRecipe_15[0];
	re[i].cg_one = cgRecipe_15[1];
	re[i].x = 140;
	re[i].y = 350;
	re[i].w = 400;
	re[i].h = 60;

	i = 15;
	re[i].cg_none = cgRecipe_16[0];
	re[i].cg_one = cgRecipe_16[1];
	re[i].x = 140;
	re[i].y = 430;
	re[i].w = 400;
	re[i].h = 60;

	i = 16;
	re[i].cg_none = cgRecipe_17[0];
	re[i].cg_one = cgRecipe_17[1];
	re[i].x = 140;
	re[i].y = 510;
	re[i].w = 400;
	re[i].h = 60;

}

// 描画
void DrawRecipe()
{
	int i;
	switch (stateStage) {
	case STATE_EP1STAGE:
		if (sel.page == 1) {
			i = 0;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 4;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y - 240, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y - 240, re[i].cg_one);
			}

			i = 6;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y + 160, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y + 160, re[i].cg_one);
			}
		}
		DrawDescription();
		break;
	case STATE_EP1STAGE_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 1;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 2;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 3;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 4;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 5;
			if (on2 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}
		}
		DrawDescription();
		break;
	case STATE_EP1STAGE_3:
		if (sel.page == 1) {
			i = 0;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 1;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 2;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 3;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 4;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 5;
			if (on2 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 7;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 8;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 9;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
		}
		DrawDescription();
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 1;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 2;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 3;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 4;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 5;
			if (on2 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 7;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 8;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 9;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
			i = 10;
			if (on4 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}

			i = 11;
			if (on4 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}
		}
		if (sel.page == 3) {
			i = 12;
			if (on4 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}

			i = 13;
			if (on5 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
		}
		DrawDescription();
		break;
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 1;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 2;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 3;
			if (on1 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 4;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 5;
			if (on2 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].use == 0) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
			}
			if (re[i].use == 1) {
				DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
			}

			i = 7;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 8;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 9;
			if (on3 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}
			i = 10;
			if (on4 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}

			i = 11;
			if (on4 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}
		}
		if (sel.page == 3) {
			i = 12;
			if (on4 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}

			i = 13;
			if (on5 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_18);
			}

			i = 14;
			if (on6 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}

			i = 15;
			if (on6 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}

			i = 16;
			if (on6 == 1) {
				if (re[i].use == 0) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_none);
				}
				if (re[i].use == 1) {
					DrawMemTh(re[i].x, re[i].y, re[i].cg_one);
				}
			}
			else {
				DrawMemTh(re[i].x, re[i].y, cgRecipe_19);
			}
		}
		DrawDescription();
		break;
	}
	
}

void DrawGetRecipe() {
	switch (stateStage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
		if (GetRecipe == 1) {
			if (gFrameWait <= 120) {
				if (recipe1 == 1) {
					DrawMemTh(400, 200, cgwindow_recipe);
					DrawString(450, 250, "火炎爆弾のレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 300, "冷凍爆弾のレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 350, "雷電爆弾のレシピを手に入れた！", GetColor(0, 0, 0));
				}
				else if (recipe2 == 2) {
					DrawMemTh(400, 300, cgwindow_log);
					DrawString(450, 330, "ハイポーションのレシピを手に入れた！", GetColor(0, 0, 0));
				}
				else if (recipe3 == 3) {
					DrawMemTh(400, 200, cgwindow_recipe);
					DrawString(450, 250, "火炎ナイフのレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 300, "冷凍ナイフのレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 350, "雷電ナイフのレシピを手に入れた！", GetColor(0, 0, 0));
				}
				if (gFrameWait == 120) {
					PlayMemBack(seRecipe);		// SE再生(仕様によって変更)
				}
			}
			else {
				DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgflash);
				if (gFrameWait == 180) {
					PlayMemBack(seFlash);		// SE再生(仕様によって変更)
				}
			}
		}
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
		if (GetRecipe == 1) {
			if (gFrameWait <= 120) {
				if (recipe1 == 4) {
					DrawMemTh(400, 200, cgwindow_recipe);
					DrawString(450, 250, "焼却爆弾のレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 300, "冷却爆弾のレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 350, "雷撃爆弾のレシピを手に入れた！", GetColor(0, 0, 0));
				}
				else if (recipe2 == 5) {
					DrawMemTh(400, 300, cgwindow_log);
					DrawString(450, 330, "フルポーションのレシピを手に入れた！", GetColor(0, 0, 0));
				}
				else if (recipe3 == 6) {
					DrawMemTh(400, 200, cgwindow_recipe);
					DrawString(450, 250, "焼却ナイフのレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 300, "冷却ナイフのレシピを手に入れた！", GetColor(0, 0, 0));
					DrawString(450, 350, "雷撃ナイフのレシピを手に入れた！", GetColor(0, 0, 0));
				}
				if (gFrameWait == 120) {
					PlayMemBack(seRecipe);		// SE再生(仕様によって変更)
				}
			}
			else {
				DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgflash);
				if (gFrameWait == 180) {
					PlayMemBack(seFlash);		// SE再生(仕様によって変更)
				}
			}
		}
		break;
	}
}