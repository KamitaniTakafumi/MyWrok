/*------------------------------------------------
*  @file game.cpp
*  @brief ゲーム本体処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ヘッダーファイルのインクルード
------------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"Item.h"
#include	"Material.h"
#include	"UI.h"
#include	"game.h"
#include	"preparation.h"
#include	"aliceattack.h"
#include	"enemy.h"
#include	"game_effect.h"
#include	"global.h"
#include	"HitJudgment.h"

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// 画像データ

int toge_bakudan;		// とげ爆弾
int kaen_bakudan;		// 火炎爆弾
int kori_bakudan;		// 氷爆弾
int kaminari_bakudan;	// 雷爆弾
int potion;				// ポーション
int naifu;				// ナイフ
int naifu_kaen;			// 火炎ナイフ
int naifu_kori;			// 氷ナイフ
int naifu_kaminari;		// 雷ナイフ

int kaenS_bakudan;		// 強火炎爆弾
int koriS_bakudan;		// 強氷爆弾
int kaminariS_bakudan;	// 強雷爆弾
int potionM;			// ハイポーション
int potionL;			// フルポーション
int naifu_kaenS;		// 強火炎ナイフ
int naifu_koriS;		// 強氷ナイフ
int naifu_kaminariS;	// 強雷ナイフ

int toge_bakudan2;		// とげ爆弾(アイテム欄)
int potion2;			// ポーション(アイテム欄)
int naifu2;				// ナイフ(アイテム欄)
int potionM2;			// ハイポーション(アイテム欄)

int cgcreateflare;		// クリエイトフレア
int cgPreparation;		// 調合成功

double	fAngle = 0;		// 角度

int createcount;		// 調合カウント
int createalpha;		// 調合α値

// アイテム情報
struct ITEM item[ITEM_NUMBER];
// 使用アイテム情報
struct USEITEM useit[USEITEM_MAX];
// 初調合情報
struct FIRSTCREATE fc[3];

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/

// 画像読み込み
void LoadCgItem() {
	toge_bakudan = LoadTexture("res/toge_bakudan.png");
	kaen_bakudan = LoadTexture("res/kaen_bakudan.png");
	kori_bakudan = LoadTexture("res/koori_bakudan.png");
	kaminari_bakudan = LoadTexture("res/kaminari_nakudan.png");
	potion = LoadTexture("res/potion.png");
	naifu = LoadTexture("res/naifu.png");
	naifu_kaen = LoadTexture("res/naifu_kaen.png");
	naifu_kori = LoadTexture("res/naifu_reitou.png");
	naifu_kaminari = LoadTexture("res/naifu_dengeki.png");

	kaenS_bakudan = LoadTexture("res/kaenS_bakudan.png");
	koriS_bakudan = LoadTexture("res/kooriS_bakudan.png");
	kaminariS_bakudan = LoadTexture("res/kaminariS_nakudan.png");
	potionM = LoadTexture("res/potionM.png");
	potionL = LoadTexture("res/fullpotion.png");
	naifu_kaenS = LoadTexture("res/naifu_kaenS.png");
	naifu_koriS = LoadTexture("res/naifu_reitouS.png");
	naifu_kaminariS = LoadTexture("res/naifu_dengekiS.png");

	cgtogenomi2 = LoadTexture("res/togenomi2.png");
	cgkaenseki2 = LoadTexture("res/kaenseki2.png");
	cghyoreseki2 = LoadTexture("res/koori2.png");
	cgraidenseki2 = LoadTexture("res/kaminari2.png");
	cgyakusou2 = LoadTexture("res/yakusou2.png");
	cgmizu2 = LoadTexture("res/mizu2.png");
	cgsurudoihahen2 = LoadTexture("res/togattanaihu2.png");
	cgchuwazai2 = LoadTexture("res/chuwazai2.png");

	toge_bakudan2 = LoadTexture("res/toge_bakudan2.png");
	potion2 = LoadTexture("res/potion2.png");
	naifu2 = LoadTexture("res/naifu2.png");
	potionM2 = LoadTexture("res/potionM2.png");

	cgcreateflare = LoadTexture("res/flare02.png");
	cgPreparation = LoadTexture("res/preparation.png");

	ButtonB = LoadTexture("res/B.png");
}

// アイテム情報初期化
void InitItem() {
	int i;

	for (i = 0; i < 16; i++) {
		item[i].number = 0;
	}

	i = 0;
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2)) {
		item[i].number = 5;
	}
	item[i].cg = toge_bakudan;
	item[i].w = 60;
	item[i].h = 60;

	i = 1;
	item[i].cg = kaen_bakudan;
	item[i].w = 60;
	item[i].h = 60;

	i = 2;
	item[i].cg = kori_bakudan;
	item[i].w = 60;
	item[i].h = 60;

	i = 3;
	item[i].cg = kaminari_bakudan;
	item[i].w = 60;
	item[i].h = 60;

	i = 4;
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2)) {
		item[i].number = 5;
	}
	item[i].cg = potion;
	item[i].w = 60;
	item[i].h = 60;

	i = 5;
	item[i].cg = potionM;
	item[i].w = 60;
	item[i].h = 60;

	i = 6;
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2)) {
		item[i].number = 5;
	}
	item[i].cg = naifu;
	item[i].w = 60;
	item[i].h = 60;

	i = 7;
	item[i].cg = naifu_kaen;
	item[i].w = 60;
	item[i].h = 60;

	i = 8;
	item[i].cg = naifu_kori;
	item[i].w = 60;
	item[i].h = 60;

	i = 9;
	item[i].cg = naifu_kaminari;
	item[i].w = 60;
	item[i].h = 60;

	i = 10;
	item[i].cg = kaenS_bakudan;
	item[i].w = 60;
	item[i].h = 60;

	i = 11;
	item[i].cg = koriS_bakudan;
	item[i].w = 60;
	item[i].h = 60;

	i = 12;
	item[i].cg = kaminariS_bakudan;
	item[i].w = 60;
	item[i].h = 60;

	i = 13;
	item[i].cg = potionL;
	item[i].w = 60;
	item[i].h = 60;

	i = 14;
	item[i].cg = naifu_kaenS;
	item[i].w = 60;
	item[i].h = 60;

	i = 15;
	item[i].cg = naifu_koriS;
	item[i].w = 60;
	item[i].h = 60;

	i = 16;
	item[i].cg = naifu_kaminariS;
	item[i].w = 60;
	item[i].h = 60;

}

// 使用アイテムの初期化
void InitUseItem() {
	int i;
	for (i = 0; i < USEITEM_MAX; i++) {
		useit[i].use = 0;
		useit[i].number = 0;
	}
	i = 0;
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2)) {
		useit[i].use = 1;
		useit[i].number = 5;
		useit[i].cg = item[0].cg;
	}
	useit[i].x = 800;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 180;

	i = 1;
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2)) {
		useit[i].use = 1;
		useit[i].number = 5;
		useit[i].cg = item[4].cg;
	}
	useit[i].x = 880;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 260;

	i = 2;
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2)) {
		useit[i].use = 1;
		useit[i].number = 5;
		useit[i].cg = item[6].cg;
	}
	useit[i].x = 960;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 340;

	i = 3;
	useit[i].x = 1040;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 420;

	i = 4;
	useit[i].x = 1120;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 180;

	i = 5;
	useit[i].x = 1200;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 260;

	i = 6;
	useit[i].x = 800;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 340;

	i = 7;
	useit[i].x = 880;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 420;

	i = 8;
	useit[i].x = 960;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 180;

	i = 9;
	useit[i].x = 1040;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 260;

	i = 10;
	useit[i].x = 1120;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 340;

	i = 11;
	useit[i].x = 1200;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 420;

	i = 12;
	useit[i].x = 800;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 180;

	i = 13;
	useit[i].x = 880;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 260;

	i = 14;
	useit[i].x = 960;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 340;

	i = 15;
	useit[i].x = 1040;
	useit[i].y = 640;
	useit[i].equipmentx = 390;
	useit[i].equipmenty = 420;

	i = 16;
	useit[i].x = 1120;
	useit[i].y = 640;
	useit[i].equipmentx = 150;
	useit[i].equipmenty = 180;

}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

/*
*  @brief 初めての調合設定
*  @param Mno1 調合アイテム１
*  @param Mno2 調合アイテム２
*  @param Mno3 調合アイテム３
*  @param itemno アイテム番号
*/
void InitFirstCreate(int Mno1, int Mno2, int  Mno3, int itemno) {
	// 初期化
	createcount = 0;
	createalpha = 0;

	// アイテム2個の調合
	if (firstcreate == 1) {
		fc[0].x = 520;
		fc[0].y = 350;
		fc[0].vx = 3.0;
		fc[0].use = 1;
		fc[0].no = itemno;

		fc[1].x = 700;
		fc[1].y = 350;
		fc[1].vx = 3.0;
		fc[1].use = 1;

		fc[2].use = 0;

		// 調合アイテムの画像設定
		for (int i = 0; i < 2; i++) {
			int j;
			if (i == 0) {
				j = Mno1;
			}
			else if (i == 1) {
				j = Mno2;
			}

			if (j == 0) {
				fc[i].cg = cgtogenomi2;
			}
			else if (j == 1) {
				fc[i].cg = cgkaenseki2;
			}
			else if (j == 2) {
				fc[i].cg = cghyoreseki2;
			}
			else if (j == 3) {
				fc[i].cg = cgraidenseki2;
			}
			else if (j == 4) {
				fc[i].cg = cgyakusou2;
			}
			else if (j == 5) {
				fc[i].cg = cgmizu2;
			}
			else if (j == 6) {
				fc[i].cg = cgsurudoihahen2;
			}
			else if (j == 7) {
				fc[i].cg = cgchuwazai2;
			}
			else if (j == 8) {
				fc[i].cg = toge_bakudan2;
			}
			else if (j == 9) {
				fc[i].cg = potion2;
			}
			else if (j == 10) {
				fc[i].cg = naifu2;
			}
			else if (j == 11) {
				fc[i].cg = potionM2;
			}
			else {
				fc[i].cg = 0;
			}
		}
	}
	// アイテム3個の調合
	if (firstcreate == 2) {
		fc[0].x = 520;
		fc[0].y = 370;
		fc[0].vx = 3.0;
		fc[0].vy = 2.0;
		fc[0].use = 1;
		fc[0].no = itemno;

		fc[1].x = 700;
		fc[1].y = 370;
		fc[1].vx = 3.0;
		fc[1].vy = 2.0;
		fc[1].use = 1;

		fc[2].x = 610;
		fc[2].y = 300;
		fc[2].vy = 3.0;
		fc[2].use = 1;

		// 調合アイテムの画像設定
		for (int i = 0; i < 3; i++) {
			int j;
			if (i == 0) {
				j = Mno1;
			}
			else if (i == 1) {
				j = Mno2;
			}
			else {
				j = Mno3;
			}

			if (j == 0) {
				fc[i].cg = cgtogenomi2;
			}
			else if (j == 1) {
				fc[i].cg = cgkaenseki2;
			}
			else if (j == 2) {
				fc[i].cg = cghyoreseki2;
			}
			else if (j == 3) {
				fc[i].cg = cgraidenseki2;
			}
			else if (j == 4) {
				fc[i].cg = cgyakusou2;
			}
			else if (j == 5) {
				fc[i].cg = cgmizu2;
			}
			else if (j == 6) {
				fc[i].cg = cgsurudoihahen2;
			}
			else if (j == 7) {
				fc[i].cg = cgchuwazai2;
			}
			else if (j == 8) {
				fc[i].cg = toge_bakudan2;
			}
			else if (j == 9) {
				fc[i].cg = potion2;
			}
			else if (j == 10) {
				fc[i].cg = naifu2;
			}
			else if (j == 11) {
				fc[i].cg = potionM2;
			}
			else {
				fc[i].cg = 0;
			}
		}
	}

}

// 初めての調合
void FirstCreate() {
	// アイテム2個の調合
	if (firstcreate == 1) {
		// 調合開始
		if ((gFrameWait <= 250) & (gFrameWait >= 200)) {
			fc[0].x -= fc[0].vx;
			fc[1].x += fc[1].vx;
		}
		if (gFrameWait <= 190) {
			fc[0].vx += 0.5;
			fc[1].vx += 0.5;
			fc[0].x += fc[0].vx;
			fc[1].x -= fc[1].vx;
		}
		if ((fc[0].x >= 610) & (fc[1].x <= 610)) {
			fc[0].use = 0;
			fc[1].use = 0;
		}
		// 調合終了
		if ((gFrameWait < 300) && (gTrg & KEYIN_X)) {
			gFrameWait = 0;
			firstcreate = 0;
		}
	}
	// アイテム3個の調合
	if (firstcreate == 2) {
		// 調合開始
		if ((gFrameWait <= 250) & (gFrameWait >= 200)) {
			fc[0].x -= fc[0].vx;
			fc[0].y += fc[0].vy;
			fc[1].x += fc[1].vx;
			fc[1].y += fc[1].vy;
			fc[2].y -= fc[2].vy;
		}
		if (gFrameWait <= 190) {
			fc[0].vx += 0.5;
			fc[0].vy += 0.2;
			fc[1].vx += 0.5;
			fc[1].vy += 0.2;
			fc[2].vy += 0.5;
			fc[0].x += fc[0].vx;
			fc[0].y -= fc[0].vy;
			fc[1].x -= fc[1].vx;
			fc[1].y -= fc[1].vy;
			fc[2].y += fc[2].vy;
		}
		if ((fc[0].x >= 610) && (fc[1].x <= 610) && (fc[2].y >= 350)) {
			fc[0].use = 0;
			fc[1].use = 0;
			fc[2].use = 0;
		}
		// 調合終了
		if ((gFrameWait < 300) && (gTrg & KEYIN_X)) {
			gFrameWait = 0;
			firstcreate = 0;
		}
	}
}

/*
*  @brief アイテムの入手
*  @param itemId アイテムの識別番号
*  @param itemNumber 所持アイテム数
*/
void GetItem(int itemId, int itemNumber)
{
	int i, j;
	// ゲットしたアイテムを持っているか
	for (j = 0; j < USEITEM_MAX; j++) {
		if (useit[j].cg == item[itemId].cg) {
			break;
		}
	}
	if ((useit[itemNumber].number >= 0) & (useit[itemNumber].number < ITEM_MAX)){   //アイテムを持っていない,最大数持っていない
		for (i = 0; i < USEITEM_MAX; i++) {
			// 同じアイテムを持っていたら
			if (j < USEITEM_MAX) {
				useit[j].number++;	// アイテムを増やす
				// とげ爆弾、ナイフ、ポーションをゲットしたらアイテム欄も増やす
				if (useit[j].cg == item[0].cg) {
					item[0].number++;
				}
				else if (useit[j].cg == item[4].cg) {
					item[4].number++;
				}
				else if (useit[j].cg == item[6].cg) {
					item[6].number++;
				}
				break;
			}
			// まだ持っていないアイテムなら
			if ((useit[i].use == 0) & (j >= USEITEM_MAX)) {
				useit[i].use = 1;				// アイテム欄に表示
				useit[i].number += 1;			// アイテムを一つゲットする
				useit[i].cg = item[itemId].cg;
				if (useit[i].cg == item[0].cg) {
					item[0].number++;
				}
				else if (useit[i].cg == item[4].cg) {
					item[4].number++;
				}
				else if (useit[i].cg == item[6].cg) {
					item[6].number++;
				}
				break;
			}
		}
	}
}

// アイテムの入手
void GetItem2(int itemId, int itemNumber, int itemNumber2)
{
	int i, j;
	for (j = 0; j < USEITEM_MAX; j++) {
		if (useit[j].cg == item[itemId].cg) {
			break;
		}
	}
	if ((useit[itemNumber].number >= 0) & (useit[itemNumber].number < ITEM_MAX)) {   //アイテムを持っていない,最大数持っていない
		for (i = 0; i < USEITEM_MAX; i++) {
			// 同じアイテムを持っていたら
			if (j < USEITEM_MAX) {
				if (useit[itemNumber2].number <= 0) {
					useit[itemNumber2].use = 0;
					useit[itemNumber2].cg = 0;
				}
				useit[j].number++;
				if (useit[j].cg == item[5].cg) {
					item[5].number++;
				}
				break;
			}
			// まだ持っていないアイテムなら
			if ((useit[i].use == 0) & (j >= USEITEM_MAX)) {
				if (useit[itemNumber2].number <= 0) {
					useit[itemNumber2].use = 0;
					useit[itemNumber2].cg = 0;
					i = itemNumber2;
				}
				useit[i].use = 1;
				useit[i].number += 1;            //アイテムを一つゲットする
				useit[i].cg = item[itemId].cg;
				if (useit[i].cg == item[5].cg) {
					item[5].number++;
				}
				break;
			}
		}
	}
}

// アイテムの変更
void PickItem(int x, int y, int wait) {
	int i, j;
	int use_num = 0;
	int cg_num = 0;
	int number_num = 0;
	// アイテム変更の終了
	if (gTrg & KEYIN_Z) {
		pick = STATE_NONE;
	}
	// 1フレーム目は処理しないようにする
	if (wait <= 0) {
		if (gTrg & KEYIN_X) {
			// 変更したい場所を選ぶ
			if (frm[2].move == 0) {
				if (frm[2].x == 790) {
					i = 0;
				}
				else if (frm[2].x == 870) {
					i = 1;
				}
				else if (frm[2].x == 950) {
					i = 2;
				}
				else if (frm[2].x == 1030) {
					i = 3;
				}
				else if (frm[2].x == 1110) {
					i = 4;
				}
				else {
					i = 5;
				}
			}
			else if (frm[2].move == 1) {
				if (frm[2].x == 790) {
					i = 6;
				}
				else if (frm[2].x == 870) {
					i = 7;
				}
				else if (frm[2].x == 950) {
					i = 8;
				}
				else if (frm[2].x == 1030) {
					i = 9;
				}
				else if (frm[2].x == 1110) {
					i = 10;
				}
				else {
					i = 11;
				}
			}
			else if (frm[2].move == 2) {
				if (frm[2].x == 790) {
					i = 12;
				}
				else if (frm[2].x == 870) {
					i = 13;
				}
				else if (frm[2].x == 950) {
					i = 14;
				}
				else if (frm[2].x == 1030) {
					i = 15;
				}
				else if (frm[2].x == 1110) {
					i = 16;
				}
			}
			if (sel.page == 1) {
				for (j = 0; j < 8; j++) {
					if ((x < useit[j].equipmentx) & (y - 10 == useit[j].equipmenty)) {
						// 選んだ場所にアイテムがないとき
						if (useit[i].use == 0) {
							use_num = useit[i].use;
							cg_num = useit[i].cg;
							number_num = useit[i].number;
							useit[i].use = useit[j].use;
							useit[i].cg = useit[j].cg;
							useit[i].number = useit[j].number;
							useit[j].use = use_num;
							useit[j].cg = cg_num;
							useit[j].number = number_num;
						}
						// 選んだ場所にアイテムがあるとき
						else if (useit[i].use == 1) {
							cg_num = useit[i].cg;
							number_num = useit[i].number;
							useit[i].cg = useit[j].cg;
							useit[i].number = useit[j].number;
							useit[j].cg = cg_num;
							useit[j].number = number_num;
						}
						pick = STATE_NONE;			// 変更処理を終わる
						break;
					}
				}
			}
			if (sel.page == 2) {
				for (j = 8; j < 16; j++) {
					if ((x < useit[j].equipmentx) & (y - 10 == useit[j].equipmenty)) {
						// 選んだ場所にアイテムがないとき
						if (useit[i].use == 0) {
							use_num = useit[i].use;
							cg_num = useit[i].cg;
							number_num = useit[i].number;
							useit[i].use = useit[j].use;
							useit[i].cg = useit[j].cg;
							useit[i].number = useit[j].number;
							useit[j].use = use_num;
							useit[j].cg = cg_num;
							useit[j].number = number_num;
						}
						// 選んだ場所にアイテムがあるとき
						else if (useit[i].use == 1) {
							cg_num = useit[i].cg;
							number_num = useit[i].number;
							useit[i].cg = useit[j].cg;
							useit[i].number = useit[j].number;
							useit[j].cg = cg_num;
							useit[j].number = number_num;
						}
						pick = STATE_NONE;			// 変更処理を終わる
						break;
					}
				}
			}
			if (sel.page == 3) {
				for (j = 16; j < 24; j++) {
					if ((x < useit[j].equipmentx) & (y - 10 == useit[j].equipmenty)) {
						// 選んだ場所にアイテムがないとき
						if (useit[i].use == 0) {
							use_num = useit[i].use;
							cg_num = useit[i].cg;
							number_num = useit[i].number;
							useit[i].use = useit[j].use;
							useit[i].cg = useit[j].cg;
							useit[i].number = useit[j].number;
							useit[j].use = use_num;
							useit[j].cg = cg_num;
							useit[j].number = number_num;
						}
						// 選んだ場所にアイテムがあるとき
						else if (useit[i].use == 1) {
							cg_num = useit[i].cg;
							number_num = useit[i].number;
							useit[i].cg = useit[j].cg;
							useit[i].number = useit[j].number;
							useit[j].cg = cg_num;
							useit[j].number = number_num;
						}
						pick = STATE_NONE;			// 変更処理を終わる
						break;
					}
				}
			}
			PlayMemBack(seSelect);
		}
	}
}

// アイテムダメージの計算
void ItemDamage(int enemyId) {
	switch (stateStage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
	case STATE_EP1STAGE_4:
		// 芋虫
		if (en[enemyId].entype == ENEMY_CATERPILLAR) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_point = 3;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_point = 3;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_point = 3;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
		}
		// マタンゴ
		if (en[enemyId].entype == ENEMY_MATANGO) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
		}
		// マージマタンゴ
		if (en[enemyId].entype == ENEMY_MERGE_MATANGO) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
		}
		// 狼
		if (en[enemyId].entype == ENEMY_WOLF) {
			// トゲ爆弾、火炎爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
		}
		// マッドハッター
		if (en[enemyId].entype == ENEMY_MAD_HATTER) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
		}
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
	case STATE_EP2STAGE_3:
		// トランプ兵(ハート)
		if (en[enemyId].entype == ENEMY_HEART) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 焼却爆弾
			if (atkit.item_no == 10) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却爆弾
			if (atkit.item_no == 11) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 雷撃爆弾
			if (atkit.item_no == 12) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 焼却ナイフ
			if (atkit.item_no == 14) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却ナイフ
			if (atkit.item_no == 15) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 雷撃ナイフ
			if (atkit.item_no == 16) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
		}
		// トランプ兵(ダイヤ)
		if (en[enemyId].entype == ENEMY_DIA) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 焼却爆弾
			if (atkit.item_no == 10) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却爆弾
			if (atkit.item_no == 11) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃爆弾
			if (atkit.item_no == 12) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 焼却ナイフ
			if (atkit.item_no == 14) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却ナイフ
			if (atkit.item_no == 15) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃ナイフ
			if (atkit.item_no == 16) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
		}
		// トランプ兵(クローバー)
		if (en[enemyId].entype == ENEMY_CLOVER) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 焼却爆弾
			if (atkit.item_no == 10) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 冷却爆弾
			if (atkit.item_no == 11) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃爆弾
			if (atkit.item_no == 12) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 焼却ナイフ
			if (atkit.item_no == 14) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 冷却ナイフ
			if (atkit.item_no == 15) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃ナイフ
			if (atkit.item_no == 16) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
		}
		// トランプ兵(スペード)
		if (en[enemyId].entype == ENEMY_SPADE) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 焼却爆弾
			if (atkit.item_no == 10) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 冷却爆弾
			if (atkit.item_no == 11) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃爆弾
			if (atkit.item_no == 12) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 焼却ナイフ
			if (atkit.item_no == 14) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 冷却ナイフ
			if (atkit.item_no == 15) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃ナイフ
			if (atkit.item_no == 16) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
		}
		// ハートの女王
		if (en[enemyId].entype == ENEMY_QUEEN) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 焼却爆弾
			if (atkit.item_no == 10) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却爆弾
			if (atkit.item_no == 11) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 雷撃爆弾
			if (atkit.item_no == 12) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 焼却ナイフ
			if (atkit.item_no == 14) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却ナイフ
			if (atkit.item_no == 15) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 雷撃ナイフ
			if (atkit.item_no == 16) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
		}
		// マッドハッター
		if (en[enemyId].entype == ENEMY_MAD_HATTER2) {
			// トゲ爆弾
			if (atkit.item_no == 0) {
				en[enemyId].hp -= 2;		// ダメージ２
				en[enemyId].damage_point = 2;
			}
			// 火炎爆弾
			if (atkit.item_no == 1) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷爆弾
			if (atkit.item_no == 2) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電爆弾
			if (atkit.item_no == 3) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// ナイフ
			if (atkit.item_no == 6) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_point = 1;
			}
			// 火炎ナイフ
			if (atkit.item_no == 7) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 氷冷ナイフ
			if (atkit.item_no == 8) {
				en[enemyId].hp -= 1;		// ダメージ１
				en[enemyId].damage_critical_point = 1;
			}
			// 雷電ナイフ
			if (atkit.item_no == 9) {
				en[enemyId].hp -= 3;		// ダメージ３
				en[enemyId].damage_critical_point = 3;
			}
			// 焼却爆弾
			if (atkit.item_no == 10) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却爆弾
			if (atkit.item_no == 11) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃爆弾
			if (atkit.item_no == 12) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
			// 焼却ナイフ
			if (atkit.item_no == 14) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 冷却ナイフ
			if (atkit.item_no == 15) {
				en[enemyId].hp -= 2;		// ダメージ2
				en[enemyId].damage_critical_point = 2;
			}
			// 雷撃ナイフ
			if (atkit.item_no == 16) {
				en[enemyId].hp -= 6;		// ダメージ６
				en[enemyId].damage_critical_point = 6;
			}
		}
	}
	
	if (en[enemyId].damage_point != 0) {
		PutEffect(EFFECTTYPE_DAMAGE, en[enemyId].x + (en[enemyId].w / 6), en[enemyId].y - (en[enemyId].h / 4), enemyId);
	}
	if (en[enemyId].damage_critical_point != 0) {
		PutEffect(EFFECTTYPE_CRITICAL, en[enemyId].x + (en[enemyId].w / 6), en[enemyId].y - (en[enemyId].h / 4), enemyId);
	}
}

void DrawFirstCreate() {
	if ((firstcreate == 1) || (firstcreate == 2)) {
		DrawTBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
		for (int i = 0; i < 3; i++) {
			if (fc[i].use == 1) {
				DrawMemTh(fc[i].x, fc[i].y, fc[i].cg);
			}
		}
		if ((fc[0].use == 0) & (fc[1].use == 0) & (fc[2].use == 0)) {
			if (createcount <= 30) {
				createcount += 2;
			}
			SetDrawArea(0, 0, 1280, 720);
			SetDrawMode(AMDRAW_ADDBLEND, 255);
			SetDrawMode(AMDRAW_BILINEAR, 0);
			DrawMemRot(62, 62, 640, 360, fAngle, 3.0, cgcreateflare);
			fAngle += PI / 100.0;
			DrawMemThExp(640 - createcount, 360 - createcount, 640 + createcount, 360 + createcount, item[fc[0].no].cg);
			SetDrawMode(AMDRAW_ADDBLEND, createalpha);
			DrawMemTh(280, 100 - createcount, cgPreparation);
			SetDrawMode(AMDRAW_BILINEAR, 0);
		}
		DrawTBox(1100, 680, 1200, 710, GetColor(255, 255, 255));
		DrawMemTh(1100, 680, ButtonB);
		DrawPrintf(1140, 690, GetColor(0, 0, 0), "スキップ");
	}
}

//アイテムの表示
void DrawItem(int itemId) {
	SetDrawMode(AMDRAW_ALPHABLEND, healthAlpha);
	DrawMemTh(useit[itemId].x, useit[itemId].y, useit[itemId].cg);
	DrawItemEquipment(useit[itemId].x, useit[itemId].y, useit[itemId].number);
	SetDrawMode(AMDRAW_NOBLEND, 0);
}

// アイテム所持数の表示
void DrawEquipmentItem() {
	int i;
	if ((pick != STATE_ONE) && (firstcreate != 1) && (firstcreate != 2)) {
		DrawSelect();
		if (sel.page == 1) {
			for (i = 0; i < 8; i++) {
				if (useit[i].use == 1) {
					DrawMemTh(useit[i].equipmentx, useit[i].equipmenty, useit[i].cg);
					DrawEquipment(useit[i].equipmentx + 60, useit[i].equipmenty, useit[i].number);
				}
			}
		}
		if (sel.page == 2) {
			for (i = 8; i < 16; i++) {
				if (useit[i].use == 1) {
					DrawMemTh(useit[i].equipmentx, useit[i].equipmenty, useit[i].cg);
					DrawEquipment(useit[i].equipmentx + 60, useit[i].equipmenty, useit[i].number);
				}
			}
		}
		if (sel.page == 3) {
			for (i = 16; i < 24; i++) {
				if (useit[i].use == 1) {
					DrawMemTh(useit[i].equipmentx, useit[i].equipmenty, useit[i].cg);
					DrawEquipment(useit[i].equipmentx + 60, useit[i].equipmenty, useit[i].number);
				}
			}
		}
	}
}
