#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include    <stdint.h>
#include	"game.h"
#include	"global.h"
#include    "Material.h"
#include    "preparation.h"
#include	"alice.h"
#include	"Object.h"
#include	"enemy.h"
#include	"HitJudgment.h"
#include	"camera.h"
#include	"UI.h"
#include	"recipe.h"
#include	"Item.h"

// 画像データ
int cgtogenomi;
int cgkaenseki;
int cghyoreseki;
int cgraidenseki;
int cgyakusou;
int cgmizu;
int cgsurudoihahen;
int cgchuwazai;

int cgtogenomi2;
int cgkaenseki2;
int cghyoreseki2;
int cgraidenseki2;
int cgyakusou2;
int cgmizu2;
int cgsurudoihahen2;
int cgchuwazai2;

int toge_bakudan_kage;
int potion_kage;
int naifu_kage;
int potionM_kage;

int recipe;
int systemAlpha = 0;
int material_max = 0;

//素材情報
struct MATERIAL material[MATERIAL_NUMBER];
struct SYSTEM sy;

//画像読み込み
void LoadCgMaterial()
{
	cgtogenomi = LoadTexture("res/togenomi.png");
	cgkaenseki = LoadTexture("res/kaenseki.png");
	cghyoreseki = LoadTexture("res/koori.png");
	cgraidenseki = LoadTexture("res/kaminari.png");
	cgyakusou = LoadTexture("res/yakusou.png");
	cgmizu = LoadTexture("res/mizu.png");
	cgsurudoihahen = LoadTexture("res/togattanaihu.png");
	cgchuwazai = LoadTexture("res/chuwazai.png");

	cgtogenomi2 = LoadTexture("res/togenomi2.png");
	cgkaenseki2 = LoadTexture("res/kaenseki2.png");
	cghyoreseki2 = LoadTexture("res/koori2.png");
	cgraidenseki2 = LoadTexture("res/kaminari2.png");
	cgyakusou2 = LoadTexture("res/yakusou2.png");
	cgmizu2 = LoadTexture("res/mizu2.png");
	cgsurudoihahen2 = LoadTexture("res/togattanaihu2.png");
	cgchuwazai2 = LoadTexture("res/chuwazai2.png");

	toge_bakudan_kage = LoadTexture("res/toge_bakudan_kage.png");
	potion_kage = LoadTexture("res/potion_kage.png");
	naifu_kage = LoadTexture("res/naifu_kage.png");
	potionM_kage = LoadTexture("res/potionM_kage.png");

	recipe = LoadTexture("res/recipe.png");
}

//素材の初期化
void InitMaterial()
{
	int i;
	for (i = 0; i < MATERIAL_NUMBER; i++)
	{
		material[i].use = 0;
		material[i].use_recipe = 0;
		material[i].number = 0;
		if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2)) {
			material[i].number = 3;
		}
		//material[i].number = 20;		// 所持数最大(開発用)
	}
	i = 0;
	material[i].cg = cgtogenomi;

	i = 1;
	material[i].cg = cgkaenseki;

	i = 2; 
	material[i].cg = cghyoreseki;

	i = 3;
	material[i].cg = cgraidenseki;

	i = 4;
	material[i].cg = cgyakusou;

	i = 5;
	material[i].cg = cgmizu;

	i = 6;
	material[i].cg = cgsurudoihahen;
	
	for (i = 7; i < MATERIAL_NUMBER; i++) {
		material[i].cg = cgchuwazai;
		material[i].enpoz_x = 0;
		material[i].enpoz_y = 0;
		material[i].enemy_type = 0;
	}
}

// システムウィンドウの初期化
void InitSystem() {
	sy.use = 0;
	sy.drop_number = 0;
	sy.count = 0;
	sy.y = 0;
}

// 中和剤位置リセット
void InitPoz() {
	int i;
	switch (stateStage) {
	case STATE_EP1STAGE:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP1STAGE_2:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP1STAGE_3:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP1STAGE_4:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP2STAGE1_1:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP2STAGE1_2:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP2STAGE1_3:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP2STAGE2_1:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	case STATE_EP2STAGE2_2:
		for (i = 7; i < MATERIAL_NUMBER; i++) {
			material[i].use = 0;
			material[i].use_recipe = 0;
			material[i].x = 0;
			material[i].y = 0;
			material[i].hit_x = 0;
			material[i].hit_y = 0;
			material[i].hit_w = 0;
			material[i].hit_h = 0;
		}
		break;
	default:
		break;
	}
}

// システムウィンドウ表示時間
void SystemWait() {
	if (sy.systemtime > 0) {
		sy.systemtime--;
		if (sy.systemtime <= 0) {
			sy.systemtime = 0;
			sy.use = 0;
		}
	}
}

// アイテムの入手
void GetMaterial(int objectId, int materialId)
{
	// Sキーでアイテム入手
	if (gTrg & KEYIN_X)
	{
		sy.count = 0;
		sy.y = 0;
		systemAlpha = 0;
		if (material[materialId].use == 0) {
			if ((material[materialId].number >= 0) &
				(material[materialId].number < MATERIAL_MAX))   // 素材を持っていない,最大数持っていない
			{
				if (obj[objectId].gatherlimit > 0) {
					// オブジェクトによってSEを変える
					switch (stateStage) {
					case STATE_EP1STAGE:
					case STATE_EP1STAGE_2:
					case STATE_EP1STAGE_3:
					case STATE_EP1STAGE_4:
					case STATE_EP2STAGE1_1:
					case STATE_EP2STAGE1_2:
						if ((materialId == 0) || (materialId == 4)) {
							PlayMemBack(seGetPlant);		// SE再生
						}
						else if ((materialId == 1) || (materialId == 2) || (materialId == 3)) {
							PlayMemBack(seGetRock);			// SE再生
						}
						else {
							PlayMemBack(seGetPickup);		// SE再生
						}
						break;
					case STATE_EP2STAGE1_3:
					case STATE_EP2STAGE2_1:
					case STATE_EP2STAGE2_2:
						if ((materialId == 0) || (materialId == 1) || (materialId == 2) || (materialId == 3) || (materialId == 4) || (materialId == 6) || (materialId == 7)) {
							PlayMemBack(seOpen);
						}
						else {
							PlayMemBack(seGetPickup);		// SE再生
						}
					}

					obj[objectId].gatherlimit--;				// 採取上限を減らす
					obj[objectId].nogetwait = 300;				// 採取していない
					if (material[materialId].number >= 19) {
						material[materialId].number += 1;
						sy.drop_number = 1;
					}
					else {
						material[materialId].number += 2;			    // 素材を2つゲット
						sy.drop_number = 2;
					}
					material[materialId].use = 1;					// 採取状態
					sy.use = 1;
					sy.number = materialId;
					sy.systemtime = 60;
					gFrameWait = 20;							// 待ち時間の設定
				}
				// アリスの向きのよって状態を変える
				if ((al.state == ALICE_STATE_UP) || (al.state == ALICE_STATE_IDLE_UP)) {
					al.state = ALICE_STATE_GATHERING_UP;
				}
				if ((al.state == ALICE_STATE_DOWN) || (al.state == ALICE_STATE_IDLE_DOWN)) {
					al.state = ALICE_STATE_GATHERING_DOWN;
				}
				if ((al.state == ALICE_STATE_RIGHT) || (al.state == ALICE_STATE_IDLE_RIGHT)) {
					al.state = ALICE_STATE_GATHERING_RIGHT;
				}
				if ((al.state == ALICE_STATE_LEFT) || (al.state == ALICE_STATE_IDLE_LEFT)) {
					al.state = ALICE_STATE_GATHERING_LEFT;
				}
			}
			else {
				gFrameWait = 30;
				material_max = 1;
			}
		}
	}
}

// ドロップアイテムの座標決定
void DropMaterial() {
	int j;
	switch (stateStage) {
	case STATE_EP1STAGE:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤描画
			}
		}
		break;
	case STATE_EP1STAGE_2:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤
			}
			if (material[j].use_recipe == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, recipe);	//レシピ
			}
		}
		break;
	case STATE_EP1STAGE_3:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤
			}
			if (material[j].use_recipe == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, recipe);	//レシピ
			}
		}
		break;
	case STATE_EP2STAGE1_1:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤
			}
			if (material[j].use_recipe == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, recipe);	//レシピ
			}
		}
		break;
	case STATE_EP2STAGE1_2:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤
			}
			if (material[j].use_recipe == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, recipe);	//レシピ
			}
		}
		break;
	case STATE_EP2STAGE1_3:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤
			}
		}
		break;
	case STATE_EP2STAGE2_1:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤
			}
			if (material[j].use_recipe == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, recipe);	//レシピ
			}
		}
		break;
	case STATE_EP2STAGE2_2:
		for (j = 7; j < MATERIAL_NUMBER; j++) {
			if (material[j].use == 1) {
				material[j].x = material[j].enpoz_x, material[j].y = material[j].enpoz_y;
				material[j].hit_x = 5, material[j].hit_y = 5;
				material[j].hit_w = 30, material[j].hit_h = 30;
				DrawMemTh(material[j].x - cv.view_x, material[j].y - cv.view_y, cgMaterial[(gFrameCount / 20) % 2]);	//中和剤描画
			}
		}
		break;
	}
}

// 中和剤の入手
void DropItem() {
	int i;
	for (i = 7; i < MATERIAL_NUMBER; i++) {
		if (material[i].use == 1) {
			if (IsHitBox(al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				material[i].x + material[i].hit_x, material[i].y + material[i].hit_y, material[i].hit_w, material[i].hit_h) != 0) {
				if (gTrg & KEYIN_X) {
					if ((material[7].number >= 0) & (material[7].number < MATERIAL_MAX))   //アイテムを持っていない,最大数持っていない
					{
						// PlayMemBack(seGetWater);		// SE再生(仕様によって変更)
						PlayMemBack(seGetPickup);		// SE再生(仕様によって変更)
						if (material[7].number >= 19) {
							sy.drop_number = 1;
							material[7].number += sy.drop_number;
						}
						else {
							sy.drop_number = rand() % 2 + 2;
							material[7].number += sy.drop_number;        //アイテムを一つゲット
						}
						material[i].use = 0;			//表示を消す
						sy.use = 1;
						sy.number = 7;
						sy.systemtime = 60;
						if (material[7].number > MATERIAL_MAX) {
							material[7].number = 20;
						}
					}
					else {
						gFrameWait = 30;
						material_max = 1;
						break;
					}
				}
			}
		}
		if (material[i].use_recipe == 1) {
			if (IsHitBox(al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
				material[i].x + material[i].hit_x, material[i].y + material[i].hit_y, material[i].hit_w, material[i].hit_h) != 0) {
				if (gTrg & KEYIN_X) {
					gFrameWait = 180;
					GetRecipe = 1;
					material[i].use_recipe = 0;			//表示を消す
					if (recipe1 == 1) {
						on1 = 1;
						break;
					}
					else if (recipe2 == 2) {
						on2 = 1;
						break;
					}
					else if (recipe3 == 3) {
						on3 = 1;
						break;
					}
					if (recipe1 == 4) {
						on4 = 1;
						break;
					}
					else if (recipe2 == 5) {
						on5 = 1;
						break;
					}
					else if (recipe3 == 6) {
						on6 = 1;
						break;
					}
					break;
				}
			}
		}
	}
}

//素材の表示
void DrawMaterial()
{
	// 調合窯を開いたとき、所持素材ウィンドウを開いたとき
	if ((selectTrg == STATE_ONE) && (firstcreate != 1) && (firstcreate != 2) || (check == STATE_ONE)) {
		if (pick == STATE_NONE) {
			if ((pre[0].use == 0) || (pre[1].use == 0) || (pre[2].use == 0) || (pre[3].use == 0) || (pre[4].use == 0)) {
				//DrawTBox(720, 180, 880, 240, GetColor(0, 0, 255));
				DrawMemTh(720, 180, cgtogenomi);
				DrawEquipment(780, 180, material[0].number);

				//DrawTBox(720, 260, 880, 320, GetColor(0, 0, 255));
				DrawMemTh(720, 260, cgkaenseki);
				DrawEquipment(780, 260, material[1].number);

				//DrawTBox(720, 340, 880, 400, GetColor(0, 0, 255));
				DrawMemTh(720, 340, cghyoreseki);
				DrawEquipment(780, 340, material[2].number);

				//DrawTBox(720, 420, 880, 480, GetColor(0, 0, 255));
				DrawMemTh(720, 420, cgraidenseki);
				DrawEquipment(780, 420, material[3].number);

				//DrawTBox(890, 180, 1050, 240, GetColor(0, 0, 255));
				DrawMemTh(890, 180, cgyakusou);
				DrawEquipment(950, 180, material[4].number);

				//DrawTBox(890, 260, 1050, 320, GetColor(0, 0, 255));
				DrawMemTh(890, 260, cgmizu);
				DrawEquipment(950, 260, material[5].number);

				//DrawTBox(890, 340, 1050, 400, GetColor(0, 0, 255));
				DrawMemTh(890, 340, cgsurudoihahen);
				DrawEquipment(950, 340, material[6].number);

				//DrawTBox(890, 420, 1050, 480, GetColor(0, 0, 255));
				DrawMemTh(890, 420, cgchuwazai);
				DrawEquipment(950, 420, material[7].number);
				
				if (re[0].use == 1) {
					//DrawTBox(1060, 180, 1220, 240, GetColor(0, 0, 255));
					DrawMemTh(1060, 180, toge_bakudan);
					DrawEquipment(1120, 180, item[0].number);
				}
				else {
					//DrawTBox(1060, 180, 1220, 240, GetColor(0, 0, 255));
					DrawMemTh(1060, 180, toge_bakudan_kage);
					DrawEquipment(1120, 180, item[0].number);
				}

				if (re[4].use == 1) {
					//DrawTBox(1060, 260, 1220, 320, GetColor(0, 0, 255));
					DrawMemTh(1060, 260, potion);
					DrawEquipment(1120, 260, item[4].number);
				}
				else {
					//DrawTBox(1060, 260, 1220, 320, GetColor(0, 0, 255));
					DrawMemTh(1060, 260, potion_kage);
					DrawEquipment(1120, 260, item[4].number);
				}

				if (re[6].use == 1) {
					//DrawTBox(1060, 340, 1220, 400, GetColor(0, 0, 255));
					DrawMemTh(1060, 340, naifu);
					DrawEquipment(1120, 340, item[6].number);
				}
				else {
					//DrawTBox(1060, 340, 1220, 400, GetColor(0, 0, 255));
					DrawMemTh(1060, 340, naifu_kage);
					DrawEquipment(1120, 340, item[6].number);
				}

				switch (stateStage) {
				case STATE_EP1STAGE:
				case STATE_EP1STAGE_2:
				case STATE_EP1STAGE_3:
				case STATE_EP1STAGE_4:
					if (on3 == 1) {
						if (re[5].use == 1) {
							//DrawTBox(1060, 420, 1220, 480, GetColor(0, 0, 255));
							DrawMemTh(1060, 420, potionM);
							DrawEquipment(1120, 420, item[5].number);
						}
						else {
							//DrawTBox(1060, 420, 1220, 480, GetColor(0, 0, 255));
							DrawMemTh(1060, 420, potionM_kage);
							DrawEquipment(1120, 420, item[5].number);
						}
					}
					break;
				case STATE_EP2STAGE1_1:
				case STATE_EP2STAGE1_2:
				case STATE_EP2STAGE1_3:
				case STATE_EP2STAGE2_1:
				case STATE_EP2STAGE2_2:
					DrawMemTh(1060, 180, toge_bakudan);
					DrawEquipment(1120, 180, item[0].number);

					DrawMemTh(1060, 260, potion);
					DrawEquipment(1120, 260, item[4].number);

					DrawMemTh(1060, 340, naifu);
					DrawEquipment(1120, 340, item[6].number);

					if (re[5].use == 1) {
						//DrawTBox(1060, 420, 1220, 480, GetColor(0, 0, 255));
						DrawMemTh(1060, 420, potionM);
						DrawEquipment(1120, 420, item[5].number);
					}
					else {
						//DrawTBox(1060, 420, 1220, 480, GetColor(0, 0, 255));
						DrawMemTh(1060, 420, potionM_kage);
						DrawEquipment(1120, 420, item[5].number);
					}
					break;
				}
			}
		}
	}
}

// システムウィンドウ描画
void DrawSystem() {
	SetDrawMode(AMDRAW_ALPHABLEND, systemAlpha);
	if ((sy.use == 1) || (systemAlpha > 0)) {
		if (sy.number == 0) {
			if (sy.count <= 29) {
				sy.count += 2;
			}
			if (sy.drop_number == 1) {
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgtogenomi2);
			}
			else {
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgtogenomi2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgtogenomi2);
			}
		}
		else if (sy.number == 1) {
			if (sy.count <= 29) {
				sy.count += 2;
			}
			if (sy.drop_number == 1) {
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgkaenseki2);
			}
			else {
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgkaenseki2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgkaenseki2);
			}
		}
		else if (sy.number == 2) {
			if (sy.count <= 29) {
				sy.count += 2;
			}
			if (sy.drop_number == 1) {
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cghyoreseki2);
			}
			else {
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cghyoreseki2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cghyoreseki2);
			}
		}
		else if (sy.number == 3) {
			if (sy.count <= 29) {
				sy.count += 2;
			}
			if (sy.drop_number == 1) {
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgraidenseki2);
			}
			else {
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgraidenseki2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgraidenseki2);
			}
		}
		else if (sy.number == 4) {
			if (sy.count <= 29) {
				sy.count += 2;
			}
			if (sy.drop_number == 1) {
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgyakusou2);
			}
			else {
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgyakusou2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgyakusou2);
			}
		}
		else if (sy.number == 5) {
			if (sy.count <= 29) {
				sy.count += 2;
			}
			if (sy.drop_number == 1) {
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgmizu2);
			}
			else {
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgmizu2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgmizu2);
			}
		}
		else if (sy.number == 6) {
			if (sy.count <= 29) {
				sy.count += 2;
			}
			if (sy.drop_number == 1) {
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgsurudoihahen2);
			}
			else {
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgsurudoihahen2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgsurudoihahen2);
			}
		}
		else {
			if ((sy.number == 7) & (sy.drop_number == 2)) {
				if (sy.count <= 29) {
					sy.count += 2;
				}
				DrawMemThExp(al.x - 10 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 10 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgchuwazai2);
				DrawMemThExp(al.x + 50 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 50 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgchuwazai2);
			}
			else if ((sy.number == 7) & (sy.drop_number == 3)) {
				if (sy.count <= 29) {
					sy.count += 2;
				}
				DrawMemThExp(al.x - 40 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x - 40 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgchuwazai2);
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgchuwazai2);
				DrawMemThExp(al.x + 80 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 80 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgchuwazai2);
			}
			else if ((sy.number == 7) & (sy.drop_number == 1)) {
				if (sy.count <= 29) {
					sy.count += 2;
				}
				DrawMemThExp(al.x + 20 - sy.count - cv.view_x, al.y - (al.h / 4) - sy.count - cv.view_y,
					al.x + 20 + sy.count - cv.view_x, al.y - (al.h / 4) + sy.count - cv.view_y, cgchuwazai2);
			}
		}
	}
	else {
		sy.count = 0;
		sy.y = 0;
	}
	SetDrawMode(AMDRAW_NOBLEND, 0);
}
