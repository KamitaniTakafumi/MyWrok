#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"global.h"
#include    "Object.h"
#include	"camera.h"
#include	"alice.h"

// �摜�f�[�^
int cgMaterial[2];
int cgMaterial_White[2];
int cgFukidashi;
int cgMfukidashi[2];

// �I�u�W�F�N�g���
struct OBJECT obj[OBJECT_MAX];
struct FUKIDASHI fk;

// �摜�̓ǂݍ���
void LoadCgObject()
{
	LoadBlkTexture("res/point.png", 40, 40, 2, 1, 2 * 1, cgMaterial);
	LoadBlkTexture("res/point_white.png", 40, 40, 2, 1, 2 * 1, cgMaterial_White);
	cgFukidashi = LoadTexture("res/fukidashi_btn.png");
}

void LoadCgFukidashi() {
	cgMfukidashi[0] = LoadTexture("res/Mfukidashi_1.png");
	cgMfukidashi[1] = LoadTexture("res/Mfukidashi_2.png");
}

void InitFukidashi() {
	fk.w = 40;
	fk.h = 40;
	switch (stateStage) {
	case STATE_EP1STAGE_2:
		fk.x = 40 * 45;
		fk.y = 40 * 1;
		break;
	case STATE_EP1STAGE_3:
		fk.x = 40 * 4;
		fk.y = 40 * 0;
		break;
	}
}

// �I�u�W�F�N�g�̏�����
void InitObject()
{
	int i;

	switch (stateStage) {
	case STATE_EP1STAGE:
		if (bgstage == STATE_EP1STAGE_2) {
			for (i = 0; i < 16; i++) {
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
	case STATE_EP1STAGE_2:
		if (bgstage == STATE_EP1STAGE) {
			for (i = 0; i < 8; i++) {
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
		if (bgstage == STATE_EP1STAGE_3) {
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
	case STATE_EP1STAGE_3:
		if (bgstage == STATE_EP1STAGE_2) {
			for (i = 0; i < 16; i++) {
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
	case STATE_EP1STAGE_4:
		if (bgstage == STATE_EP1STAGE_3) {
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
	}

	switch (stateStage) {
	case STATE_EP1STAGE:
		// ��
		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 160;
		obj[i].y = 720;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��(��)
		i = 1;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 280;
		obj[i].y = 240;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = 0;
		obj[i].hit_y = 40;
		obj[i].hit_w = 40;
		obj[i].hit_h = 10;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��(��)
		i = 2;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 440;
		obj[i].y = 520;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -10;
		obj[i].hit_y = 0;
		obj[i].hit_w = 10;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��(��)
		i = 3;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 600;
		obj[i].y = 200;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = 0;
		obj[i].hit_y = 40;
		obj[i].hit_w = 40;
		obj[i].hit_h = 10;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��
		i = 4;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 1000;
		obj[i].y = 240;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = -5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��
		i = 5;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 520;
		obj[i].y = 680;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -10;
		obj[i].hit_y = 0;
		obj[i].hit_w = 10;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// �^��
		i = 6;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 840;
		obj[i].y = 240;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = 0;
		obj[i].hit_y = 0;
		obj[i].hit_w = 50;
		obj[i].hit_h = 50;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// �����o��
		i = 7;
		obj[i].use = 0;

		// �����o��
		i = 8;
		obj[i].use = 0;

		break;
	case STATE_EP1STAGE_2:

		// ��

		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 10 * 40;
		obj[i].y = 33 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 8;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 29 * 40;
		obj[i].y = 19 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 9;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 19 * 40;
		obj[i].y = 13 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��i�ԁj

		i = 1;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 21 * 40;
		obj[i].y = 17 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 10;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 43 * 40;
		obj[i].y = 26 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��i���j
		i = 2;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 22 * 40;
		obj[i].y = 47 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 11;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 47 * 40;
		obj[i].y = 11 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��i���j

		i = 3;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 29 * 40;
		obj[i].y = 5 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 12;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 45 * 40;
		obj[i].y = 44 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��

		i = 4;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 4 * 40;
		obj[i].y = 39 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 13;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 36 * 40;
		obj[i].y = 40 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 14;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 56 * 40;
		obj[i].y = 5 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��

		i = 5;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 13 * 40;
		obj[i].y = 49 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = 0;
		obj[i].hit_y = -10;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// �M

		i = 6;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 8 * 40;
		obj[i].y = 39 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 7;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 60 * 40;
		obj[i].y = 5 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// �����o��
		i = 15;
		obj[i].use = 0;

		// �����o��
		i = 16;
		obj[i].use = 0;
		break;
	case STATE_EP1STAGE_3:

		// ��

		i = 0;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 18 * 40;
		obj[i].y = 8 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 8;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 31 * 40;
		obj[i].y = 50 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 9;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 65 * 40;
		obj[i].y = 39 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��i�ԁj

		i = 1;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 28 * 40;
		obj[i].y = 52 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 10;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 59 * 40;
		obj[i].y = 35 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 11;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 10 * 40;
		obj[i].y = 5 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��i���j
		i = 2;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 47 * 40;
		obj[i].y = 51 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 12;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 54 * 40;
		obj[i].y = 47 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 13;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 12 * 40;
		obj[i].y = 23 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��i���j

		i = 3;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 30 * 40;
		obj[i].y = 55 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 14;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 56 * 40;
		obj[i].y = 31 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;


		i = 15;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 14 * 40;
		obj[i].y = 7 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��

		i = 4;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 38 * 40;
		obj[i].y = 38 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 16;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 51 * 40;
		obj[i].y = 35 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 17;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 20 * 40;
		obj[i].y = 13 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// ��

		i = 5;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 48 * 40;
		obj[i].y = 54 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -20;
		obj[i].hit_y = -10;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 18;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 58 * 40;
		obj[i].y = 48 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = 0;
		obj[i].hit_y = -10;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 19;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 4 * 40;
		obj[i].y = 20 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = 0;
		obj[i].hit_y = -10;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// �M

		i = 6;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 2 * 40;
		obj[i].y = 14 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 20;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 41 * 40;
		obj[i].y = 39 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		i = 7;
		obj[i].use = 1;
		obj[i].cg = cgMaterial[2];
		obj[i].x = 50 * 40;
		obj[i].y = 39 * 40;
		obj[i].w = 80;
		obj[i].h = 80;
		obj[i].hit_x = -5;
		obj[i].hit_y = 5;
		obj[i].hit_w = 50;
		obj[i].hit_h = 40;
		obj[i].gatherlimit = 3;
		obj[i].getwait = 0;
		obj[i].nogetwait = 0;

		// �����o��
		i = 21;
		obj[i].use = 0;

		// �����o��
		i = 22;
		obj[i].use = 0;

		break;
	case STATE_EP1STAGE_4:
		break;
	}

}

// �I�u�W�F�N�g�ɐG�ꂽ�Ƃ��ɐ����o���̕\��
void TouchObject() {
	if ((gFrameCount % 60) < 50) {
		switch (stateStage) {
		case STATE_EP1STAGE:
			if ((obj[7].use == 1) || (obj[8].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		case STATE_EP1STAGE_2:
			if ((obj[15].use == 1) || (obj[16].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		case STATE_EP1STAGE_3:
			if ((obj[21].use == 1) || (obj[22].use == 1)) {
				if (gFrameWait == 0) {
					DrawMemTh(al.x + (al.w / 6) - cv.view_x, al.y - (al.h / 4) - cv.view_y, cgFukidashi);
				}
			}
			break;
		}
	}
}

// �č̎�ł���܂ł̑҂�����
void ReGetMaterialWait() {
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

void DrawFukidashi() {
	switch (stateStage) {
	case STATE_EP1STAGE_2:
		DrawMemTh(fk.x - cv.view_x, fk.y - cv.view_y, cgMfukidashi[(gFrameCount / 60) % 2]);
		break;
	case STATE_EP1STAGE_3:
		DrawMemTh(fk.x - cv.view_x, fk.y - cv.view_y, cgMfukidashi[(gFrameCount / 60) % 2]);
		break;
	}
}

// �I�u�W�F�N�g�̕`��
void DrawObject()
{
	int i;
	switch (stateStage) {
	case STATE_EP1STAGE:
		for (i = 0; i < 7; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	case STATE_EP1STAGE_2:
		for (i = 0; i < 15; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	case STATE_EP1STAGE_3:
		for (i = 0; i < 21; i++) {
			if (obj[i].use == 1) {
				DrawMemTh(obj[i].x - cv.view_x, obj[i].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);
			}
		}
		break;
	}
}
