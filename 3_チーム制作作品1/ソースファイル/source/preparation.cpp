#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include    <stdint.h>
#include	"game.h"
#include    "alice.h"
#include    "enemy.h"
#include    "HitJudgment.h"
#include    "preparation.h"
#include    "Material.h"
#include    "Object.h"
#include    "recipe.h"
#include	"Item.h"
#include	"camera.h"
#include	"global.h"
#include	"UI.h"

//ゲーム情報
int cgwindow_material;				// ウィンドウ(所持素材)
int cgwindow_mix;					// ウィンドウ(調合レシピ)
int cgwindow_text_material;			// ウィンドウ(素材)
int cgwindow_text_mix;				// ウィンドウ(調合釜)
int cgSelect;						// 選択矢印
int cgwindow_item;					// ウィンドウ(アイテム)
int cgwindow_text_item;				// ウィンドウ(アイテムテキスト)
int cgPageSelect_right;				// 
int cgPageSelect_left;				// 
int cgwindow_log;					// 

int pickwait;						// フレーム処理
int firstcreate;					// 

// 調合窯情報
struct PREPARATION pre[PREPARATION_MAX];
struct SELECT sel;

//画像読み込み
void LoadCgPreparation()
{
	cgwindow_material = LoadTexture("res/window_material.png");
	cgwindow_mix = LoadTexture("res/window_mix.png");
	cgwindow_text_material = LoadTexture("res/window_text_material.png");
	cgwindow_text_mix = LoadTexture("res/window_text_mix.png");
	cgSelect = LoadTexture("res/alche_title_icon.png");
	cgwindow_item = LoadTexture("res/window_material.png");
	cgwindow_text_item = LoadTexture("res/window_text_item.png");
	cgPageSelect_right = LoadTexture("res/page_icon_right.png");
	cgPageSelect_left = LoadTexture("res/page_icon_left.png");
	cgSystemButton = LoadTexture("res/window_system_button.png");
	ButtonB = LoadTexture("res/B.png");
	ButtonA = LoadTexture("res/A.png");
	cgwindow_log = LoadTexture("res/window_system3.png");
}

//調合釜の初期化
void InitPreparation()
{
	firstcreate = 0;
	int i;

	switch (stateStage) {
	case STATE_EP1STAGE:
		if (bgstage == STATE_EP1STAGE_2) {
			for (i = 0; i < 2; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP1STAGE_2:
		if (bgstage == STATE_EP1STAGE) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
		if (bgstage == STATE_EP1STAGE_3) {
			for (i = 0; i < 3; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP1STAGE_3:
		if (bgstage == STATE_EP1STAGE_2) {
			for (i = 0; i < 2; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP1STAGE_4:
		if (bgstage == STATE_EP1STAGE_3) {
			for (i = 0; i < 3; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP2STAGE1_1:
		if (bgstage2 == STATE_EP2STAGE1_2) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
		if (bgstage2 == STATE_EP2STAGE2_1) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP2STAGE1_2:
		if (bgstage2 == STATE_EP2STAGE1_1) {
			for (i = 0; i < 2; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP2STAGE1_3:
		if (bgstage2 == STATE_EP2STAGE2_1) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
		if (bgstage2 == STATE_EP2STAGE2_2) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP2STAGE2_1:
		if (bgstage2 == STATE_EP2STAGE1_1) {
			for (i = 0; i < 2; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
		if (bgstage2 == STATE_EP2STAGE1_3) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP2STAGE2_2:
		if (bgstage2 == STATE_EP2STAGE1_3) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	case STATE_EP2STAGE_3:
		if (bgstage2 == STATE_EP2STAGE2_2) {
			for (i = 0; i < 1; i++) {
				pre[i].x = 0;
				pre[i].y = 0;
				pre[i].w = 40;
				pre[i].h = 40;
				pre[i].hit_x = 0;
				pre[i].hit_y = 0;
				pre[i].hit_w = 0;
				pre[i].hit_h = 0;
				pre[i].hit_range_x = -80;
				pre[i].hit_range_y = -80;
				pre[i].hit_range_w = 200;
				pre[i].hit_range_h = 200;
				pre[i].use = 0;
				//選択矢印の初期化
				InitSelect();
			}
			break;
		}
	}

	switch (stateStage) {
	case STATE_EP1STAGE:
		i = 0;
		pre[i].x = 2080;
		pre[i].y = 960;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;
		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP1STAGE_2:
		i = 0;
		pre[i].x = 40 * 6;
		pre[i].y = 40 * 42;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -120;
		pre[i].hit_range_y = -120;
		pre[i].hit_range_w = 280;
		pre[i].hit_range_h = 280;
		pre[i].use = 0;

		i = 1;
		pre[i].x = 40 * 58;
		pre[i].y = 40 * 8;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -120;
		pre[i].hit_range_y = -120;
		pre[i].hit_range_w = 280;
		pre[i].hit_range_h = 280;
		pre[i].use = 0;
		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP1STAGE_3:
		i = 0;
		pre[i].x = 40 * 43;
		pre[i].y = 40 * 41;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		i = 1;
		pre[i].x = 40 * 52;
		pre[i].y = 40 * 41;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		i = 2;
		pre[i].x = 40 * 4;
		pre[i].y = 40 * 16;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP2STAGE1_1:
		i = 0;
		pre[i].x = 40 * 63;
		pre[i].y = 40 * 65;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		i = 1;
		pre[i].x = 40 * 4;
		pre[i].y = 40 * 35;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP2STAGE1_2:
		i = 0;
		pre[i].x = 40 * 48;
		pre[i].y = 40 * 17;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP2STAGE1_3:
		i = 0;
		pre[i].x = 40 * 15;
		pre[i].y = 40 * 6;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP2STAGE2_1:
		i = 0;
		pre[i].x = 40 * 35;
		pre[i].y = 40 * 12;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP2STAGE2_2:
		i = 0;
		pre[i].x = 40 * 12;
		pre[i].y = 40 * 11;
		pre[i].w = 40;
		pre[i].h = 40;
		pre[i].hit_x = -5;
		pre[i].hit_y = -5;
		pre[i].hit_w = 50;
		pre[i].hit_h = 50;
		pre[i].hit_range_x = -80;
		pre[i].hit_range_y = -80;
		pre[i].hit_range_w = 200;
		pre[i].hit_range_h = 200;
		pre[i].use = 0;

		//選択矢印の初期化
		InitSelect();
		break;
	case STATE_EP2STAGE_3:
		break;
	}
}

//選択矢印の初期化
void InitSelect()
{
	sel.x = 100;
	sel.y = 200;
	sel.w = 40;
	sel.h = 40;
	sel.state = STATE_NONE;
	sel.xspan = 2;
	sel.page = 1;
	sel.equipment_x = 90;
	sel.equipment_y = 190;
	sel.page_left_x = 110;
	sel.page_left_y = 645;
	sel.page_right_x = 510;
	sel.page_right_y = 645;
	sel.page_number_x = 300;
	sel.page_number_y = 650;
	sel.page_number_x2 = 340;
	sel.page_number_y2 = 470;
}

// 作成アイテムの選択
void SelectItem()
{

	// 矢印に動きをつける
	float rad = ((float)gFrameCount * (sel.xspan)) * PI / 45;
	sel.x = sel.x + (int)(sin(rad) * sel.xspan);
	sel.page_left_x = sel.page_left_x + (int)(sin(rad) * sel.xspan);
	sel.page_right_x = sel.page_right_x - (int)(sin(rad) * sel.xspan);

	if (gFrameWait == 0) {
		switch (stateStage) {
		case STATE_EP1STAGE:
			// 矢印の移動
			if (gTrg & KEYIN_DOWN)
			{
				PlayMemBack(seCursor);		// SE再生
				sel.y += 80;
			}
			if (gTrg & KEYIN_UP)
			{
				PlayMemBack(seCursor);		// SE再生
				sel.y -= 80;
			}
			// 矢印をループするようにする
			if ((sel.y + sel.h) > 670)
			{
				sel.y = 200;
			}
			if (sel.y < 190)
			{
				sel.y = 600;
			}
			break;
		case STATE_EP1STAGE_2:
		case STATE_EP1STAGE_3:
		case STATE_EP1STAGE_4:
			// 矢印の移動
			if (gTrg & KEYIN_DOWN)
			{
				PlayMemBack(seCursor);		// SE再生
				sel.y += 80;
			}
			if (gTrg & KEYIN_UP)
			{
				PlayMemBack(seCursor);		// SE再生
				sel.y -= 80;
			}
			// ページの移動
			if (gTrg & KEYIN_RIGHT) {
				PlayMemBack(seCursor);		// SE再生
				sel.page++;
			}
			if (gTrg & KEYIN_LEFT) {
				PlayMemBack(seCursor);		// SE再生
				sel.page--;
			}

			// 矢印をループするようにする
			if ((sel.y + sel.h) > 670)
			{
				sel.y = 200;
			}
			if (sel.y < 190)
			{
				sel.y = 600;
			}
			// ページのループ
			if (sel.page <= 0) {
				sel.page = 2;
			}
			if (sel.page >= 3) {
				sel.page = 1;
			}
			break;
		case STATE_EP2STAGE1_1:
		case STATE_EP2STAGE1_2:
		case STATE_EP2STAGE1_3:
		case STATE_EP2STAGE2_1:
		case STATE_EP2STAGE2_2:
			// 矢印の移動
			if (gTrg & KEYIN_DOWN)
			{
				PlayMemBack(seCursor);		// SE再生
				sel.y += 80;
			}
			if (gTrg & KEYIN_UP)
			{
				PlayMemBack(seCursor);		// SE再生
				sel.y -= 80;
			}
			// ページの移動
			if (gTrg & KEYIN_RIGHT) {
				PlayMemBack(seCursor);		// SE再生
				sel.page++;
			}
			if (gTrg & KEYIN_LEFT) {
				PlayMemBack(seCursor);		// SE再生
				sel.page--;
			}

			// 矢印をループするようにする
			if ((sel.y + sel.h) > 670)
			{
				sel.y = 200;
			}
			if (sel.y < 190)
			{
				sel.y = 600;
			}
			// ページのループ
			if (sel.page <= 0) {
				sel.page = 3;
			}
			if (sel.page >= 4) {
				sel.page = 1;
			}
			break;
		}
	}
	// キー入力されたら
	if (gTrg & KEYIN_X) {
		// アイテム調合
		ItemCreate();
	}
}

int CheckItem(int i) {
	int j;

	for (j = 0; j < USEITEM_MAX; j++) {
		if (useit[j].cg == item[i].cg) {
			check_number = j;
			return j;
		}
		if ((useit[j].use == 0) & (check_number == 0)) {
			check_number = j;
		}
	}
	return -1;
}

int CheckItem_2(int i) {
	int j;

	for (j = 0; j < USEITEM_MAX; j++) {
		if (useit[j].cg == item[i].cg) {
			check_number2 = j;
			return j;
		}
	}
	return -1;
}

// アイテム生成
void ItemCreate()
{
	int i, j, l;
	if(firstcreate == 0){
	switch (stateStage) {
	case STATE_EP1STAGE:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 1, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
			}

			i = 4;
			if (re[i].y - 240 == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(4, 5, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 6;
			if (re[i].y + 160 == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[6].number--;			// 素材を減らす(鋭い破片)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 6, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[6].number--;			// 素材を減らす(鋭い破片)
						check_number = 0;
						break;
					}
				}
			}
		}
		break;
	case STATE_EP1STAGE_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 1, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(1, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 2;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(2, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 3;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(3, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 4;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(4, 5, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 5;
			if (re[i].y == sel.y - 10) {
				if (on2 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 1;
									InitFirstCreate(5, 9, -1, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

		}

		// ２ページ目
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 6, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}
		}
		break;
	case STATE_EP1STAGE_3:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 1, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(1, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 2;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(2, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 3;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(3, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 4;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(4, 5, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 5;
			if (re[i].y == sel.y - 10) {
				if (on2 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 1;
									InitFirstCreate(5, 9, -1, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

		}

		// ２ページ目
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 6, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 7;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[1].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 1, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[1].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 8;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[2].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[2].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[2].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 2, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[2].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 9;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[3].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[3].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[3].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 3, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[3].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}
		}
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 1, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(1, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 2;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(2, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 3;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(3, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 4;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(4, 5, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 5;
			if (re[i].y == sel.y - 10) {
				if (on2 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 1;
									InitFirstCreate(5, 9, -1, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

		}

		// ２ページ目
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 6, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 7;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[1].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 1, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[1].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 8;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[2].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[2].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[2].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 2, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[2].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 9;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[3].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[3].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[3].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 3, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[3].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 10;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[1].number--;			// 素材を減らす(とげの実)
								material[7].number--;			// 素材を減らす(火炎石)
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(1, 7, 8, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[1].number--;			// 素材を減らす(とげの実)
								material[7].number--;			// 素材を減らす(火炎石)
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 11;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[2].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(2, 7, 8, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[2].number--;			// 素材を減らす(とげの実)
								material[7].number--;			// 素材を減らす(火炎石)
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}


		}

		// 3ページ目
		if (sel.page == 3) {
			i = 12;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[3].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(3, 7, 8, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[3].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}
			i = 13;
			if (re[i].y == sel.y - 10) {
				if (on5 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(5) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[7].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[5].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(5) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[7].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 1;
									InitFirstCreate(7, 11, -1, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[5].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

		}
		break;
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 1, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(とげの実)
						material[1].number--;			// 素材を減らす(火炎石)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(1, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[1].number--;			// 素材を減らす(火炎石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 2;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(2, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[2].number--;			// 素材を減らす(氷冷石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 3;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(3, 7, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[3].number--;			// 素材を減らす(雷電石)
							material[7].number--;			// 素材を減らす(中和剤)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 4;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[4].number > 0) & (material[5].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(4, 5, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[4].number--;			// 素材を減らす(薬草)
						material[5].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 5;
			if (re[i].y == sel.y - 10) {
				if (on2 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(4) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[5].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 1;
									InitFirstCreate(5, 9, -1, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[5].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[4].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

		}

		// ２ページ目
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
				else {
					// 素材を持っていたら生成可能
					j = check_number;
					// 素材が足りない
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// アイテム上限
					else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
						useit[j].number = 10;
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 2;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					else if (((material[0].number > 0) & (material[6].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
						if (re[i].use == 0) {
							firstcreate = 1;
							InitFirstCreate(0, 6, -1, i);
							gFrameWait = 300;
						}
						PlayMemBack(seCreateItem);
						re[i].use = 1;
						GetItem(i, j);
						material[0].number--;			// 素材を減らす(薬草)
						material[6].number--;			// 素材を減らす(水)
						check_number = 0;
						break;
					}
				}
			}

			i = 7;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[1].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[1].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 1, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[1].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 8;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[2].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[2].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[2].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 2, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[2].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 9;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[3].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[3].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
					else {
						// 素材を持っていたら生成可能
						j = check_number;
						// 素材が足りない
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// アイテム上限
						else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
							useit[j].number = 10;
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 2;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						else if (((material[6].number > 0) & (material[3].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
							if (re[i].use == 0) {
								firstcreate = 1;
								InitFirstCreate(6, 3, -1, i);
								gFrameWait = 300;
							}
							PlayMemBack(seCreateItem);
							re[i].use = 1;
							GetItem(i, j);
							material[6].number--;			// 素材を減らす(とげの実)
							material[3].number--;			// 素材を減らす(火炎石)
							check_number = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 10;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[1].number--;			// 素材を減らす(とげの実)
								material[7].number--;			// 素材を減らす(火炎石)
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(1, 7, 8, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[1].number--;			// 素材を減らす(とげの実)
								material[7].number--;			// 素材を減らす(火炎石)
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 11;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(2, 7, 8, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[2].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(2, 7, 8, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[2].number--;			// 素材を減らす(とげの実)
								material[7].number--;			// 素材を減らす(火炎石)
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}


		}

		// 3ページ目
		if (sel.page == 3) {
			i = 12;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[3].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(0) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(3, 7, 8, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[3].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[0].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}
			i = 13;
			if (re[i].y == sel.y - 10) {
				if (on5 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(5) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[7].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[5].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(5) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if ((material[7].number > 0) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 1;
									InitFirstCreate(7, 11, -1, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[5].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 14;
			if (re[i].y == sel.y - 10) {
				if (on6 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(6) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[1].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[6].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(6) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[1].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(1, 7, 10, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[1].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[6].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 15;
			if (re[i].y == sel.y - 10) {
				if (on6 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(6) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[2].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[6].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(6) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[2].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(2, 7, 10, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[2].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[6].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}

			i = 16;
			if (re[i].y == sel.y - 10) {
				if (on6 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(6) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[3].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[6].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
					else {
						if (CheckItem_2(6) != -1) {
							// 素材を持っていたら生成可能
							j = check_number;
							l = check_number2;
							// 素材が足りない
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// アイテム上限
							else if ((useit[j].number > 9) & (useit[j].cg == item[i].cg)) {
								useit[j].number = 10;
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 2;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							else if (((material[3].number > 0) & (material[7].number > 0)) & ((useit[j].number >= 0) & (useit[j].number < ITEM_MAX))) {
								if (re[i].use == 0) {
									firstcreate = 2;
									InitFirstCreate(3, 7, 10, i);
									gFrameWait = 300;
								}
								PlayMemBack(seCreateItem);
								re[i].use = 1;
								material[3].number--;			// 素材を減らす()
								material[7].number--;			// 素材を減らす()
								useit[l].number--;				// 素材を減らす()
								item[6].number--;
								GetItem2(i, j, l);
								check_number = 0;
								check_number2 = 0;
								break;
							}
						}
						else {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							check_number2 = 0;
							break;
						}
					}
				}
				else {
					for (int k = 0; k < PREPARATION_MAX; k++) {
						pre[k].use = 3;
					}
					gFrameWait = 60;
				}
			}
		}
		break;
	}
	}
}

// 変更アイテムの選択
void EquipmentItem() {
	// 矢印に動きをつける
	float rad = ((float)gFrameCount * (sel.xspan)) * PI / 45;
	sel.equipment_x = sel.equipment_x + (int)(sin(rad) * sel.xspan);

	// アイテム変更中は動かさないようにする
	if (pick == STATE_NONE) {
		// 矢印の移動
		if (gTrg & KEYIN_DOWN)
		{
			PlayMemBack(seCursor);		// SE再生
			sel.equipment_y += 80;
		}
		if (gTrg & KEYIN_UP)
		{
			PlayMemBack(seCursor);		// SE再生
			sel.equipment_y -= 80;
		}
		// ページの移動
		if (gTrg & KEYIN_RIGHT) {
			PlayMemBack(seCursor);		// SE再生
			sel.equipment_x += 240;
			// ページの移動
			if (sel.equipment_x > 350) {
				PlayMemBack(seCursor);		// SE再生
				sel.page++;
			}
		}
		if (gTrg & KEYIN_LEFT) {
			PlayMemBack(seCursor);		// SE再生
			sel.equipment_x -= 240;
			// ページの移動
			if (sel.equipment_x < 70) {
				PlayMemBack(seCursor);		// SE再生
				sel.page--;
			}
		}
		// ページのループ
		if (sel.page <= 0) {
			sel.page = 3;
		}
		if (sel.page >= 4) {
			sel.page = 1;
		}
	}
	// 矢印をループするようにする
	if ((sel.equipment_y + sel.h) > 510)
	{
		sel.equipment_y = 190;
	}
	if (sel.equipment_y < 180)
	{
		sel.equipment_y = 430;
	}
	if (sel.equipment_x < 70) {
		sel.equipment_x = 330;
	}
	if (sel.equipment_x > 350) {
		sel.equipment_x = 90;
	}

	// 変更する時１フレーム待つ(勝手に変わらないように)
	if (pick == STATE_NONE) {
		pickwait = 1;
	}
	if (gTrg & KEYIN_X) {
		if (sel.page == 1) {
			for (int i = 0; i < 8; i++) {
				// 選んだ場所にアイテムがあれば
				if (useit[i].use != 0) {
					if ((sel.equipment_x < useit[i].equipmentx) & (sel.equipment_y - 10 == useit[i].equipmenty)) {
						pick = STATE_ONE;
						PlayMemBack(seSelect);
						break;
					}
				}
			}
		}
		if (sel.page == 2) {
			for (int i = 8; i < 16; i++) {
				if (useit[i].use != 0) {
					if ((sel.equipment_x < useit[i].equipmentx) & (sel.equipment_y - 10 == useit[i].equipmenty)) {
						pick = STATE_ONE;
						PlayMemBack(seSelect);
						break;
					}
				}
			}
		}
		if (sel.page == 3) {
			for (int i = 16; i < 17; i++) {
				if (useit[i].use != 0) {
					if ((sel.equipment_x < useit[i].equipmentx) & (sel.equipment_y - 10 == useit[i].equipmenty)) {
						pick = STATE_ONE;
						PlayMemBack(seSelect);
						break;
					}
				}
			}
		}
	}
	// アイテムの変更
	if (pick == STATE_ONE) {
		PickItem(sel.equipment_x, sel.equipment_y, pickwait);
		pickwait = 0;
	}
}

// 矢印の描画
void DrawSelect()
{
	if (selectTrg == STATE_ONE) {
		DrawMemTh(sel.x, sel.y, cgSelect);
		if (stateStage != STATE_EP1STAGE) {
			DrawMemTh(sel.page_left_x, sel.page_left_y, cgPageSelect_left);
			DrawMemTh(sel.page_right_x, sel.page_right_y, cgPageSelect_right);
		}
		switch (stateStage) {
		case STATE_EP1STAGE:
			if (sel.page == 1) {
				DrawPrintf(sel.page_number_x, sel.page_number_y, GetColor(0, 0, 0), "1/1");
			}
			break;
		case STATE_EP1STAGE_2:
		case STATE_EP1STAGE_3:
		case STATE_EP1STAGE_4:
			if (sel.page == 1) {
				DrawPrintf(sel.page_number_x, sel.page_number_y, GetColor(0, 0, 0), "1/2");
			}
			if (sel.page == 2) {
				DrawPrintf(sel.page_number_x, sel.page_number_y, GetColor(0, 0, 0), "2/2");
			}
			break;
		case STATE_EP2STAGE1_1:
		case STATE_EP2STAGE1_2:
		case STATE_EP2STAGE1_3:
		case STATE_EP2STAGE2_1:
		case STATE_EP2STAGE2_2:
			if (sel.page == 1) {
				DrawPrintf(sel.page_number_x, sel.page_number_y, GetColor(0, 0, 0), "1/3");
			}
			if (sel.page == 2) {
				DrawPrintf(sel.page_number_x, sel.page_number_y, GetColor(0, 0, 0), "2/3");
			}
			if (sel.page == 3) {
				DrawPrintf(sel.page_number_x, sel.page_number_y, GetColor(0, 0, 0), "3/3");
			}
			break;
		}
	}
	else if (check == STATE_ONE) {
		DrawMemTh(sel.equipment_x, sel.equipment_y, cgSelect);
		if (sel.page == 1) {
			DrawPrintf(sel.page_number_x2, sel.page_number_y2, GetColor(0, 0, 0), "1/3");
		}
		if (sel.page == 2) {
			DrawPrintf(sel.page_number_x2, sel.page_number_y2, GetColor(0, 0, 0), "2/3");
		}
		if (sel.page == 3) {
			DrawPrintf(sel.page_number_x2, sel.page_number_y2, GetColor(0, 0, 0), "3/3");
		}
	}
}

// 調合釜の描画
void DrawPreparation()
{
	switch (stateStage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
	case STATE_EP1STAGE_4:
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
	case STATE_EP2STAGE_3:
		if ((selectTrg == STATE_ONE) && (firstcreate != 1) && (firstcreate != 2)) {
			// 調合ウィンドウの表示
			if ((pre[0].use == 0) || (pre[1].use == 0) || (pre[2].use == 0) || (pre[3].use == 0) || (pre[4].use == 0)){
				DrawTBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
				DrawMemTh(WINDOW_SOZAI_X, WINDOW_SOZAI_Y, cgwindow_material);       // ウィンドウ(所持素材)
				DrawMemTh(WINDOW_CHOGO_X, WINDOW_CHOGO_Y, cgwindow_mix);            // ウィンドウ(調合レシピ)
				DrawMemTh(WINDOW_SOZAINAME_X, WINDOW_SOZAINAME_Y, cgwindow_text_material);  // ウィンドウ(素材)
				DrawMemTh(WINDOW_CHOGONAME_X, WINDOW_CHOGONAME_Y, cgwindow_text_mix);       // ウィンドウ(調合釜)
				DrawMemTh(700, 510, cgSystemButton);
				DrawMemTh(710, 515, ButtonB);
				DrawPrintf(745, 525, GetColor(0, 0, 0), "調合");
				DrawMemTh(780, 515, ButtonA);
				DrawPrintf(815, 525, GetColor(0, 0, 0), "戻る");
				DrawMaterial();
				DrawSelect();
				DrawRecipe();
			}
			// ウィンドウ表示(素材が足りないとき)
			else if ((pre[0].use == 1) || (pre[1].use == 1) || (pre[2].use == 1) || (pre[3].use == 1) || (pre[4].use == 1)) {
				DrawMemTh(400, 300, cgwindow_log);
				DrawString(510, 330, "調合素材が足りません", GetColor(0, 0, 0));
			}
			// ウィンドウ表示(アイテムを上限まで持っているとき)
			else if ((pre[0].use == 2) || (pre[1].use == 2) || (pre[2].use == 2) || (pre[3].use == 2) || (pre[4].use == 2)) {
				DrawMemTh(400, 300, cgwindow_log);
				DrawString(520, 330, "これ以上持てません", GetColor(0, 0, 0));
			}
			// ウィンドウ表示(レシピを持っていないとき)
			else if ((pre[0].use == 3) || (pre[1].use == 3) || (pre[2].use == 3) || (pre[3].use == 3) || (pre[4].use == 3)) {
				DrawMemTh(400, 300, cgwindow_log);
				DrawString(500, 330, "まだレシピを持っていない", GetColor(0, 0, 0));
			}
		}
		// 所持素材ウィンドウ表示
		if (check == STATE_ONE) {
			if (pick == STATE_NONE) {
				DrawTBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
				DrawMemTh(WINDOW_SOZAI_X, WINDOW_SOZAI_Y, cgwindow_material);				// ウィンドウ(所持素材)
				DrawMemTh(WINDOW_SOZAINAME_X, WINDOW_SOZAINAME_Y, cgwindow_text_material);  // ウィンドウ(素材テキスト)
				DrawMemTh(WINDOW_ITEM_X, WINDOW_ITEM_Y, cgwindow_item);						// ウィンドウ(所持アイテム)
				DrawMemTh(WINDOW_ITEMNAME_X, WINDOW_ITEMNAME_Y, cgwindow_text_item);		// ウィンドウ(アイテムテキスト)
				DrawMemTh(700, 510, cgSystemButton);
				DrawMemTh(710, 515, ButtonB);
				DrawPrintf(745, 525, GetColor(0, 0, 0), "変更");
				DrawMemTh(780, 515, ButtonA);
				DrawPrintf(815, 525, GetColor(0, 0, 0), "戻る");
			}
		}
	}
	if (material_max == 1) {
		DrawMemTh(400, 300, cgwindow_log);
		DrawString(520, 330, "これ以上持てません", GetColor(0, 0, 0));
	}
}