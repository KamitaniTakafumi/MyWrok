#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"global.h"
#include    "Object.h"
#include	"camera.h"
#include	"alice.h"

int cgHfukidashi[2];

// 画像の読み込み
void LoadCgFukidashi2() {
	cgHfukidashi[0] = LoadTexture("res/Hfukidashi_1.png");
	cgHfukidashi[1] = LoadTexture("res/Hfukidashi_2.png");
}

void InitFukidashi2() {
	fk.w = 40;
	fk.h = 40;
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		fk.x = 40 * 7;
		fk.y = 40 * 20;
		break;
	case STATE_EP2STAGE1_3:
		fk.x = 40 * 56;
		fk.y = 40 * 5;
		break;
	case STATE_EP2STAGE2_1:
		fk.x = 40 * 22;
		fk.y = 40 * 36;
		break;
	}
}

// オブジェクトの初期化
void InitObject2()
{
	int i;

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		if (bgstage2 == STATE_EP2STAGE1_2) {
			for (i = 0; i < 13; i++) {
				obj[i].use = 1;
				obj[i].x = 0;
				obj[i].y = 0;
				obj[i].w = 80;
				obj[i].h = 80;
				obj[i].hit_x = 0;
				obj[i].hit_y = 0;
				obj[i].hit_w = 0;
				obj[i].hit_h = 0;
				obj[i].gatherlimit = 3;
				obj[i].getwait = 0;
				obj[i].nogetwait = 0;
			}
			break;
		}
		if (bgstage2 == STATE_EP2STAGE2_1) {
			for (i = 0; i < 22; i++) {
				obj[i].use = 1;
				obj[i].x = 0;
				obj[i].y = 0;
				obj[i].w = 80;
				obj[i].h = 80;
				obj[i].hit_x = 0;
				obj[i].hit_y = 0;
				obj[i].hit_w = 0;
				obj[i].hit_h = 0;
				obj[i].gatherlimit = 3;
				obj[i].getwait = 0;
				obj[i].nogetwait = 0;
			}
			break;
		}
	case STATE_EP2STAGE1_2:
		if (bgstage2 == STATE_EP2STAGE1_1) {
			for (i = 0; i < 2; i++) {
				obj[i].use = 1;
				obj[i].x = 0;
				obj[i].y = 0;
				obj[i].w = 80;
				obj[i].h = 80;
				obj[i].hit_x = 0;
				obj[i].hit_y = 0;
				obj[i].hit_w = 0;
				obj[i].hit_h = 0;
				obj[i].gatherlimit = 3;
				obj[i].getwait = 0;
				obj[i].nogetwait = 0;
			}
			break;
		}
	case STATE_EP2STAGE1_3:
		if (bgstage2 == STATE_EP2STAGE2_1) {
			break;
		}
		if (bgstage2 == STATE_EP2STAGE2_2) {
			break;
		}
	case STATE_EP2STAGE2_1:
		if (bgstage2 == STATE_EP2STAGE1_1) {
			for (i = 0; i < 2; i++) {
				obj[i].use = 1;
				obj[i].x = 0;
				obj[i].y = 0;
				obj[i].w = 80;
				obj[i].h = 80;
				obj[i].hit_x = 0;
				obj[i].hit_y = 0;
				obj[i].hit_w = 0;
				obj[i].hit_h = 0;
				obj[i].gatherlimit = 3;
				obj[i].getwait = 0;
				obj[i].nogetwait = 0;
			}
			break;
		}
		if (bgstage2 == STATE_EP2STAGE2_2) {
			break;
		}
	case STATE_EP2STAGE_3:
		break;
	}

	switch (stateStage) {
	case STATE_EP2STAGE1_1:

		// タル
		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 63;
		obj[i].y = 40 * 54;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 吹き出し
		i = 1;
		obj[i].use = 0;

		// 吹き出し
		i = 2;
		obj[i].use = 0;

		break; 
	case STATE_EP2STAGE1_2:
		// 木
		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 45;
		obj[i].y = 40 * 47;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 1;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 55;
		obj[i].y = 40 * 34;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 2;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 4;
		obj[i].y = 40 * 29;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(赤)
		i = 3;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 54;
		obj[i].y = 40 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 4;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 25;
		obj[i].y = 40 * 31;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(青)
		i = 5;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 54;
		obj[i].y = 40 * 26;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 6;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 38;
		obj[i].y = 40 * 22;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(黄)
		i = 7;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 40;
		obj[i].y = 40 * 37;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 8;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 8;
		obj[i].y = 40 * 30;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 草
		i = 9;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 40;
		obj[i].y = 40 * 31;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 10;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 21;
		obj[i].y = 40 * 36;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 水
		i = 11;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 46;
		obj[i].y = 40 * 26;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// タル
		i = 12;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 50;
		obj[i].y = 40 * 14;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 吹き出し
		i = 13;
		obj[i].use = 0;

		// 吹き出し
		i = 14;
		obj[i].use = 0;

		break;
	case STATE_EP2STAGE1_3:
		// 木
		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 13;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(赤)
		i = 1;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 19;
		obj[i].y = 40 * 8;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(青)
		i = 2;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 25;
		obj[i].y = 40 * 8;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(黄)
		i = 3;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 31;
		obj[i].y = 40 * 8;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 草
		i = 4;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 19;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 水
		i = 5;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 12;
		obj[i].y = 40 * 9;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// タル
		i = 6;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 25;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 中和剤
		i = 7;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 31;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 吹き出し
		i = 8;
		obj[i].use = 0;

		// 吹き出し
		i = 9;
		obj[i].use = 0;

		break;
	case STATE_EP2STAGE2_1:
		// 木
		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 32;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(赤)
		i = 1;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 43;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(青)
		i = 2;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 43;
		obj[i].y = 40 * 7;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(黄)
		i = 3;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 43;
		obj[i].y = 40 * 11;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 草
		i = 4;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 38;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 水
		i = 5;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 42;
		obj[i].y = 40 * 15;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// タル
		i = 6;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 32;
		obj[i].y = 40 * 7;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 中和剤
		i = 7;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 38;
		obj[i].y = 40 * 7;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 吹き出し
		i = 8;
		obj[i].use = 0;

		// 吹き出し
		i = 9;
		obj[i].use = 0;

		break;
	case STATE_EP2STAGE2_2:
		// 木
		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 8;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(赤)
		i = 1;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 2;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(青)
		i = 2;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 2;
		obj[i].y = 40 * 7;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 岩(黄)
		i = 3;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 2;
		obj[i].y = 40 * 11;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 草
		i = 4;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 8;
		obj[i].y = 40 * 7;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 水
		i = 5;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 12;
		obj[i].y = 40 * 14;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// タル
		i = 6;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 8;
		obj[i].y = 40 * 11;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 中和剤
		i = 7;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 40 * 14;
		obj[i].y = 40 * 3;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// 吹き出し
		i = 8;
		obj[i].use = 0;

		// 吹き出し
		i = 9;
		obj[i].use = 0;

		break;
	}
}

// オブジェクトに触れたときに吹き出しの表示
void TouchObject2() {
	if ((gFrameCount % 60) < 50) {
		switch (stateStage) {
		case STATE_EP2STAGE1_1:
			if ((obj[1].use == 1) || (obj[2].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		case STATE_EP2STAGE1_2:
			if ((obj[13].use == 1) || (obj[14].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		case STATE_EP2STAGE1_3:
			if ((obj[8].use == 1) || (obj[9].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		case STATE_EP2STAGE2_1:
			if ((obj[8].use == 1) || (obj[9].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		case STATE_EP2STAGE2_2:
			if ((obj[8].use == 1) || (obj[9].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		case STATE_EP2STAGE_3:
			break;
		}
	}
}

// 再採取できるまでの待ち時間
void ReGetMaterialWait2() {
	int i;
	for (i = 0; i < OBJECT_MAX; i++) {
		if (obj[i].getwait > 0) {
			obj[i].getwait--;
			if (obj[i].getwait <= 0) {
				obj[i].gatherlimit = 3;
				obj[i].use = 1;
				obj[i].getwait = 0;
			}
		}
		if (obj[i].nogetwait > 0) {
			obj[i].nogetwait--;
			if (obj[i].nogetwait <= 0) {
				obj[i].gatherlimit = 3;
			}
		}
	}
}

void DrawFukidashi2() {
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		DrawMemTh(fk.x - cv.view_x, fk.y - cv.view_y, cgHfukidashi[(gFrameCount / 60) % 2]);
		break;
	case STATE_EP2STAGE1_3:
		DrawMemTh(fk.x - cv.view_x, fk.y - cv.view_y, cgHfukidashi[(gFrameCount / 60) % 2]);
		break;
	case STATE_EP2STAGE2_1:
		DrawMemTh(fk.x - cv.view_x, fk.y - cv.view_y, cgHfukidashi[(gFrameCount / 60) % 2]);
		break;
	}
}

// オブジェクトの描画
void DrawObject2()
{
	int i;
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		for (i = 0; i < 1; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	case STATE_EP2STAGE1_2:
		for (i = 0; i < 13; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	case STATE_EP2STAGE1_3:
		for (i = 0; i < 8; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	case STATE_EP2STAGE2_1:
		for (i = 0; i < 8; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	case STATE_EP2STAGE2_2:
		for (i = 0; i < 8; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	case STATE_EP2STAGE_3:
		break;
	}
}
