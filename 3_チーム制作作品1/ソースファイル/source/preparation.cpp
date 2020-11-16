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

//�Q�[�����
int cgwindow_material;				// �E�B���h�E(�����f��)
int cgwindow_mix;					// �E�B���h�E(�������V�s)
int cgwindow_text_material;			// �E�B���h�E(�f��)
int cgwindow_text_mix;				// �E�B���h�E(������)
int cgSelect;						// �I����
int cgwindow_item;					// �E�B���h�E(�A�C�e��)
int cgwindow_text_item;				// �E�B���h�E(�A�C�e���e�L�X�g)
int cgPageSelect_right;				// 
int cgPageSelect_left;				// 
int cgwindow_log;					// 

int pickwait;						// �t���[������
int firstcreate;					// 

// �����q���
struct PREPARATION pre[PREPARATION_MAX];
struct SELECT sel;

//�摜�ǂݍ���
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

//�������̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
				//�I����̏�����
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
		//�I����̏�����
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
		//�I����̏�����
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

		//�I����̏�����
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

		//�I����̏�����
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

		//�I����̏�����
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

		//�I����̏�����
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

		//�I����̏�����
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

		//�I����̏�����
		InitSelect();
		break;
	case STATE_EP2STAGE_3:
		break;
	}
}

//�I����̏�����
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

// �쐬�A�C�e���̑I��
void SelectItem()
{

	// ���ɓ���������
	float rad = ((float)gFrameCount * (sel.xspan)) * PI / 45;
	sel.x = sel.x + (int)(sin(rad) * sel.xspan);
	sel.page_left_x = sel.page_left_x + (int)(sin(rad) * sel.xspan);
	sel.page_right_x = sel.page_right_x - (int)(sin(rad) * sel.xspan);

	if (gFrameWait == 0) {
		switch (stateStage) {
		case STATE_EP1STAGE:
			// ���̈ړ�
			if (gTrg & KEYIN_DOWN)
			{
				PlayMemBack(seCursor);		// SE�Đ�
				sel.y += 80;
			}
			if (gTrg & KEYIN_UP)
			{
				PlayMemBack(seCursor);		// SE�Đ�
				sel.y -= 80;
			}
			// �������[�v����悤�ɂ���
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
			// ���̈ړ�
			if (gTrg & KEYIN_DOWN)
			{
				PlayMemBack(seCursor);		// SE�Đ�
				sel.y += 80;
			}
			if (gTrg & KEYIN_UP)
			{
				PlayMemBack(seCursor);		// SE�Đ�
				sel.y -= 80;
			}
			// �y�[�W�̈ړ�
			if (gTrg & KEYIN_RIGHT) {
				PlayMemBack(seCursor);		// SE�Đ�
				sel.page++;
			}
			if (gTrg & KEYIN_LEFT) {
				PlayMemBack(seCursor);		// SE�Đ�
				sel.page--;
			}

			// �������[�v����悤�ɂ���
			if ((sel.y + sel.h) > 670)
			{
				sel.y = 200;
			}
			if (sel.y < 190)
			{
				sel.y = 600;
			}
			// �y�[�W�̃��[�v
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
			// ���̈ړ�
			if (gTrg & KEYIN_DOWN)
			{
				PlayMemBack(seCursor);		// SE�Đ�
				sel.y += 80;
			}
			if (gTrg & KEYIN_UP)
			{
				PlayMemBack(seCursor);		// SE�Đ�
				sel.y -= 80;
			}
			// �y�[�W�̈ړ�
			if (gTrg & KEYIN_RIGHT) {
				PlayMemBack(seCursor);		// SE�Đ�
				sel.page++;
			}
			if (gTrg & KEYIN_LEFT) {
				PlayMemBack(seCursor);		// SE�Đ�
				sel.page--;
			}

			// �������[�v����悤�ɂ���
			if ((sel.y + sel.h) > 670)
			{
				sel.y = 200;
			}
			if (sel.y < 190)
			{
				sel.y = 600;
			}
			// �y�[�W�̃��[�v
			if (sel.page <= 0) {
				sel.page = 3;
			}
			if (sel.page >= 4) {
				sel.page = 1;
			}
			break;
		}
	}
	// �L�[���͂��ꂽ��
	if (gTrg & KEYIN_X) {
		// �A�C�e������
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

// �A�C�e������
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
			}

			i = 4;
			if (re[i].y - 240 == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
			}

			i = 6;
			if (re[i].y + 160 == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[6].number--;			// �f�ނ����炷(�s���j��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[6].number--;			// �f�ނ����炷(�s���j��)
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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

		// �Q�y�[�W��
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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

		// �Q�y�[�W��
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
			}

			i = 7;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[1].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[1].number--;			// �f�ނ����炷(�Ή���)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[2].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[2].number--;			// �f�ނ����炷(�Ή���)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[3].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[3].number--;			// �f�ނ����炷(�Ή���)
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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

		// �Q�y�[�W��
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
			}

			i = 7;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[1].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[1].number--;			// �f�ނ����炷(�Ή���)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[2].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[2].number--;			// �f�ނ����炷(�Ή���)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[3].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[3].number--;			// �f�ނ����炷(�Ή���)
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[1].number--;			// �f�ނ����炷(�Ƃ��̎�)
								material[7].number--;			// �f�ނ����炷(�Ή���)
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[1].number--;			// �f�ނ����炷(�Ƃ��̎�)
								material[7].number--;			// �f�ނ����炷(�Ή���)
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[2].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[2].number--;			// �f�ނ����炷(�Ƃ��̎�)
								material[7].number--;			// �f�ނ����炷(�Ή���)
								useit[l].number--;				// �f�ނ����炷()
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

		// 3�y�[�W��
		if (sel.page == 3) {
			i = 12;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[3].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[3].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[1].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(�Ƃ��̎�)
						material[1].number--;			// �f�ނ����炷(�Ή���)
						check_number = 0;
						break;
					}
				}
			}

			i = 1;
			if (re[i].y == sel.y - 10) {
				if (on1 == 1) {
					if (CheckItem(i) != -1) {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[1].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[1].number--;			// �f�ނ����炷(�Ή���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[2].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[2].number--;			// �f�ނ����炷(�X���)
							material[7].number--;			// �f�ނ����炷(���a��)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[3].number == 0) || (material[7].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[3].number--;			// �f�ނ����炷(���d��)
							material[7].number--;			// �f�ނ����炷(���a��)
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
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[4].number == 0) || (material[5].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[4].number--;			// �f�ނ����炷(��)
						material[5].number--;			// �f�ނ����炷(��)
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[5].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[5].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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

		// �Q�y�[�W��
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (CheckItem(i) != -1) {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
				else {
					// �f�ނ������Ă����琶���\
					j = check_number;
					// �f�ނ�����Ȃ�
					if ((material[0].number == 0) || (material[6].number == 0)) {
						for (int k = 0; k < PREPARATION_MAX; k++) {
							pre[k].use = 1;
						}
						gFrameWait = 60;
						check_number = 0;
						break;
					}
					// �A�C�e�����
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
						material[0].number--;			// �f�ނ����炷(��)
						material[6].number--;			// �f�ނ����炷(��)
						check_number = 0;
						break;
					}
				}
			}

			i = 7;
			if (re[i].y == sel.y - 10) {
				if (on3 == 1) {
					if (CheckItem(i) != -1) {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[1].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[1].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[1].number--;			// �f�ނ����炷(�Ή���)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[2].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[2].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[2].number--;			// �f�ނ����炷(�Ή���)
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
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[3].number--;			// �f�ނ����炷(�Ή���)
							check_number = 0;
							break;
						}
					}
					else {
						// �f�ނ������Ă����琶���\
						j = check_number;
						// �f�ނ�����Ȃ�
						if ((material[6].number == 0) || (material[3].number == 0)) {
							for (int k = 0; k < PREPARATION_MAX; k++) {
								pre[k].use = 1;
							}
							gFrameWait = 60;
							check_number = 0;
							break;
						}
						// �A�C�e�����
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
							material[6].number--;			// �f�ނ����炷(�Ƃ��̎�)
							material[3].number--;			// �f�ނ����炷(�Ή���)
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[1].number--;			// �f�ނ����炷(�Ƃ��̎�)
								material[7].number--;			// �f�ނ����炷(�Ή���)
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[1].number--;			// �f�ނ����炷(�Ƃ��̎�)
								material[7].number--;			// �f�ނ����炷(�Ή���)
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[2].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[2].number--;			// �f�ނ����炷(�Ƃ��̎�)
								material[7].number--;			// �f�ނ����炷(�Ή���)
								useit[l].number--;				// �f�ނ����炷()
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

		// 3�y�[�W��
		if (sel.page == 3) {
			i = 12;
			if (re[i].y == sel.y - 10) {
				if (on4 == 1) {
					if (CheckItem(i) != -1) {
						if (CheckItem_2(0) != -1) {
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[3].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[3].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if (material[7].number == 0) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[1].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[1].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[1].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[2].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[2].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[2].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[3].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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
							// �f�ނ������Ă����琶���\
							j = check_number;
							l = check_number2;
							// �f�ނ�����Ȃ�
							if ((material[3].number == 0) || (material[7].number == 0)) {
								for (int k = 0; k < PREPARATION_MAX; k++) {
									pre[k].use = 1;
								}
								gFrameWait = 60;
								check_number = 0;
								check_number2 = 0;
								break;
							}
							// �A�C�e�����
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
								material[3].number--;			// �f�ނ����炷()
								material[7].number--;			// �f�ނ����炷()
								useit[l].number--;				// �f�ނ����炷()
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

// �ύX�A�C�e���̑I��
void EquipmentItem() {
	// ���ɓ���������
	float rad = ((float)gFrameCount * (sel.xspan)) * PI / 45;
	sel.equipment_x = sel.equipment_x + (int)(sin(rad) * sel.xspan);

	// �A�C�e���ύX���͓������Ȃ��悤�ɂ���
	if (pick == STATE_NONE) {
		// ���̈ړ�
		if (gTrg & KEYIN_DOWN)
		{
			PlayMemBack(seCursor);		// SE�Đ�
			sel.equipment_y += 80;
		}
		if (gTrg & KEYIN_UP)
		{
			PlayMemBack(seCursor);		// SE�Đ�
			sel.equipment_y -= 80;
		}
		// �y�[�W�̈ړ�
		if (gTrg & KEYIN_RIGHT) {
			PlayMemBack(seCursor);		// SE�Đ�
			sel.equipment_x += 240;
			// �y�[�W�̈ړ�
			if (sel.equipment_x > 350) {
				PlayMemBack(seCursor);		// SE�Đ�
				sel.page++;
			}
		}
		if (gTrg & KEYIN_LEFT) {
			PlayMemBack(seCursor);		// SE�Đ�
			sel.equipment_x -= 240;
			// �y�[�W�̈ړ�
			if (sel.equipment_x < 70) {
				PlayMemBack(seCursor);		// SE�Đ�
				sel.page--;
			}
		}
		// �y�[�W�̃��[�v
		if (sel.page <= 0) {
			sel.page = 3;
		}
		if (sel.page >= 4) {
			sel.page = 1;
		}
	}
	// �������[�v����悤�ɂ���
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

	// �ύX���鎞�P�t���[���҂�(����ɕς��Ȃ��悤��)
	if (pick == STATE_NONE) {
		pickwait = 1;
	}
	if (gTrg & KEYIN_X) {
		if (sel.page == 1) {
			for (int i = 0; i < 8; i++) {
				// �I�񂾏ꏊ�ɃA�C�e���������
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
	// �A�C�e���̕ύX
	if (pick == STATE_ONE) {
		PickItem(sel.equipment_x, sel.equipment_y, pickwait);
		pickwait = 0;
	}
}

// ���̕`��
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

// �������̕`��
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
			// �����E�B���h�E�̕\��
			if ((pre[0].use == 0) || (pre[1].use == 0) || (pre[2].use == 0) || (pre[3].use == 0) || (pre[4].use == 0)){
				DrawTBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
				DrawMemTh(WINDOW_SOZAI_X, WINDOW_SOZAI_Y, cgwindow_material);       // �E�B���h�E(�����f��)
				DrawMemTh(WINDOW_CHOGO_X, WINDOW_CHOGO_Y, cgwindow_mix);            // �E�B���h�E(�������V�s)
				DrawMemTh(WINDOW_SOZAINAME_X, WINDOW_SOZAINAME_Y, cgwindow_text_material);  // �E�B���h�E(�f��)
				DrawMemTh(WINDOW_CHOGONAME_X, WINDOW_CHOGONAME_Y, cgwindow_text_mix);       // �E�B���h�E(������)
				DrawMemTh(700, 510, cgSystemButton);
				DrawMemTh(710, 515, ButtonB);
				DrawPrintf(745, 525, GetColor(0, 0, 0), "����");
				DrawMemTh(780, 515, ButtonA);
				DrawPrintf(815, 525, GetColor(0, 0, 0), "�߂�");
				DrawMaterial();
				DrawSelect();
				DrawRecipe();
			}
			// �E�B���h�E�\��(�f�ނ�����Ȃ��Ƃ�)
			else if ((pre[0].use == 1) || (pre[1].use == 1) || (pre[2].use == 1) || (pre[3].use == 1) || (pre[4].use == 1)) {
				DrawMemTh(400, 300, cgwindow_log);
				DrawString(510, 330, "�����f�ނ�����܂���", GetColor(0, 0, 0));
			}
			// �E�B���h�E�\��(�A�C�e��������܂Ŏ����Ă���Ƃ�)
			else if ((pre[0].use == 2) || (pre[1].use == 2) || (pre[2].use == 2) || (pre[3].use == 2) || (pre[4].use == 2)) {
				DrawMemTh(400, 300, cgwindow_log);
				DrawString(520, 330, "����ȏ㎝�Ă܂���", GetColor(0, 0, 0));
			}
			// �E�B���h�E�\��(���V�s�������Ă��Ȃ��Ƃ�)
			else if ((pre[0].use == 3) || (pre[1].use == 3) || (pre[2].use == 3) || (pre[3].use == 3) || (pre[4].use == 3)) {
				DrawMemTh(400, 300, cgwindow_log);
				DrawString(500, 330, "�܂����V�s�������Ă��Ȃ�", GetColor(0, 0, 0));
			}
		}
		// �����f�ރE�B���h�E�\��
		if (check == STATE_ONE) {
			if (pick == STATE_NONE) {
				DrawTBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
				DrawMemTh(WINDOW_SOZAI_X, WINDOW_SOZAI_Y, cgwindow_material);				// �E�B���h�E(�����f��)
				DrawMemTh(WINDOW_SOZAINAME_X, WINDOW_SOZAINAME_Y, cgwindow_text_material);  // �E�B���h�E(�f�ރe�L�X�g)
				DrawMemTh(WINDOW_ITEM_X, WINDOW_ITEM_Y, cgwindow_item);						// �E�B���h�E(�����A�C�e��)
				DrawMemTh(WINDOW_ITEMNAME_X, WINDOW_ITEMNAME_Y, cgwindow_text_item);		// �E�B���h�E(�A�C�e���e�L�X�g)
				DrawMemTh(700, 510, cgSystemButton);
				DrawMemTh(710, 515, ButtonB);
				DrawPrintf(745, 525, GetColor(0, 0, 0), "�ύX");
				DrawMemTh(780, 515, ButtonA);
				DrawPrintf(815, 525, GetColor(0, 0, 0), "�߂�");
			}
		}
	}
	if (material_max == 1) {
		DrawMemTh(400, 300, cgwindow_log);
		DrawString(520, 330, "����ȏ㎝�Ă܂���", GetColor(0, 0, 0));
	}
}