// 使いたい機能や命令にあわせて include を追加する
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"camera.h"
#include	"alice.h"
#include	"UI.h"
#include	"HitJudgment.h"
#include	"alice.h"
#include	"preparation.h"
#include	"recipe.h"
#include	"global.h"
#include	"Item.h"

// ゲーム情報
int cgItemText;
int cgItemColumn;
int cgFrame;
int cgHealth;
int cgLife[6];
int cgSystem;
int cgEquipment[1 * 10];
int cgEquipment2[1 * 10];
int cgMulti;
int cgMulti2;
int eqtbl[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int eqtbl2[] = { 0, 1 };
int healthAlpha = 255;
int cgDescription;
int ButtonB;
int ButtonA;
int ButtonY;
int ButtonX;
int ButtonRB;
int ButtonLB;
int cgSystemButton;

// UI情報
struct FRAME frm[FRAME_MAX];
struct HEART hrt[HP_MAX];
struct EQUIPMENT eq;
struct DESCRIPTION de;

// 画像読み込み
void LoadCgUi() {
	cgItemText = LoadTexture("res/window_text_item.png");
	cgItemColumn = LoadTexture("res/window_equipment.png");
	cgFrame = LoadTexture("res/frame.png");
	cgSystem = LoadTexture("res/window_system.png");
	LoadBlkTexture("res/number.png", 27, 60, 10, 1, 1 * 10, cgEquipment);
	cgMulti = LoadTexture("res/multi_symbol.png");
	LoadBlkTexture("res/number_2.png", 10, 20, 10, 1, 1 * 10, cgEquipment2);
	cgMulti2 = LoadTexture("res/multi_symbol_2.png");
	cgDescription = LoadTexture("res/description.png");
	ButtonB = LoadTexture("res/B.png");
	ButtonA = LoadTexture("res/A.png");
	ButtonY = LoadTexture("res/Y.png");
	ButtonX = LoadTexture("res/X.png");
	ButtonRB = LoadTexture("res/RB.png");
	ButtonLB = LoadTexture("res/LB.png");
	cgPageSelect_right = LoadTexture("res/page_icon_right.png");
	cgPageSelect_left = LoadTexture("res/page_icon_left.png");
	cgSystemButton = LoadTexture("res/window_system_button.png");
}

// 体力バーの画像読み込み、初期化
void LoadCgHealth() {
	int i;
	cgHealth = LoadTexture("res/hp.png");
	for (i = 0; i < 6; i++) {
		cgLife[i] = LoadTexture("res/heart.png");
	}

	// ハートの位置

	i = 0;
	hrt[i].use = 1;
	hrt[i].x = 140;
	hrt[i].y = 70;

	i = 1;
	hrt[i].use = 1;
	hrt[i].x = 177;
	hrt[i].y = 70;

	i = 2;
	hrt[i].use = 1;
	hrt[i].x = 214;
	hrt[i].y = 70;

	i = 3;
	hrt[i].use = 1;
	hrt[i].x = 251;
	hrt[i].y = 70;

	i = 4;
	hrt[i].use = 1;
	hrt[i].x = 288;
	hrt[i].y = 70;

	i = 5;
	hrt[i].use = 1;
	hrt[i].x = 325;
	hrt[i].y = 70;

}

// アイテムフレーム情報初期化
void InitItemColumn() {
	int i;
	i = 0;
	frm[i].cg = cgItemText;
	frm[i].x = 1150;
	frm[i].y = 590;

	i = 1;
	frm[i].cg = cgItemColumn;
	frm[i].x = 790;
	frm[i].y = 630;

	i = 2;
	frm[i].cg = cgFrame;
	frm[i].x = 790;
	frm[i].y = 630;
	frm[i].move = 0;
}

// 個数カウントの初期化
void InitEquipment() {
	eq.x = 0;
	eq.y = 0;
}

// アイテム説明欄の初期化
void InitDescription() {
	de.x = 700;
	de.y = 560;
}

//アイテム欄の枠の移動
void FrameControll() {
	if ((selectTrg == STATE_NONE) & (check == STATE_NONE) || (pick == STATE_ONE)) {
		if (gTrg & KEYIN_D) {
			PlayMemBack(seCursor);
			frm[2].x += 80;
		}
		if (gTrg & KEYIN_S) {
			PlayMemBack(seCursor);
			frm[2].x -= 80;
		}
		if (frm[2].x < 790) {
			if (frm[2].move == 0) {
				if ((useit[12].use == 1) || (useit[13].use == 1) || (useit[14].use == 1) || (useit[15].use == 1) || (useit[16].use == 1)) {
					frm[2].move = 2;
				}
				else if ((useit[6].use == 1) || (useit[7].use == 1) || (useit[8].use == 1) || (useit[9].use == 1) || (useit[10].use == 1) || (useit[11].use == 1)) {
						frm[2].move = 1;
				}
				else {
					frm[2].move = 0;
				}
			}
			else if (frm[2].move == 1) {
				if ((useit[0].use == 1) || (useit[1].use == 1) || (useit[2].use == 1) || (useit[3].use == 1) || (useit[4].use == 1) || (useit[5].use == 1)) {
					frm[2].move = 0;
				}
				else if ((useit[12].use == 1) || (useit[13].use == 1) || (useit[14].use == 1) || (useit[15].use == 1) || (useit[16].use == 1)) {
					frm[2].move = 2;
				}
				else {
					frm[2].move = 1;
				}
			}
			else if (frm[2].move == 2) {
				if ((useit[6].use == 1) || (useit[7].use == 1) || (useit[8].use == 1) || (useit[9].use == 1) || (useit[10].use == 1) || (useit[11].use == 1)) {
					frm[2].move = 1;
				}
				else if ((useit[0].use == 1) || (useit[1].use == 1) || (useit[2].use == 1) || (useit[3].use == 1) || (useit[4].use == 1) || (useit[5].use == 1)) {
					frm[2].move = 0;
				}
				else {
					frm[2].move = 2;
				}
			}
			frm[2].x = 1190;
		}
		if (frm[2].x > 1190) {
			if (frm[2].move == 0) {
				if ((useit[6].use == 1) || (useit[7].use == 1) || (useit[8].use == 1) || (useit[9].use == 1) || (useit[10].use == 1) || (useit[11].use == 1)) {
					frm[2].move = 1;
				}
				else if ((useit[12].use == 1) || (useit[13].use == 1) || (useit[14].use == 1) || (useit[15].use == 1) || (useit[16].use == 1)) {
					frm[2].move = 2;
				}
				else {
					frm[2].move = 0;
				}
			}
			else if (frm[2].move == 1) {
				if ((useit[12].use == 1) || (useit[13].use == 1) || (useit[14].use == 1) || (useit[15].use == 1) || (useit[16].use == 1)) {
					frm[2].move = 2;
				}
				else if ((useit[0].use == 1) || (useit[1].use == 1) || (useit[2].use == 1) || (useit[3].use == 1) || (useit[4].use == 1) || (useit[5].use == 1)) {
					frm[2].move = 0;
				}
				else {
					frm[2].move = 1;
				}
			}
			else if (frm[2].move == 2) {
				if ((useit[0].use == 1) || (useit[1].use == 1) || (useit[2].use == 1) || (useit[3].use == 1) || (useit[4].use == 1) || (useit[5].use == 1)) {
					frm[2].move = 0;
				}
				else if ((useit[6].use == 1) || (useit[7].use == 1) || (useit[8].use == 1) || (useit[9].use == 1) || (useit[10].use == 1) || (useit[11].use == 1)) {
					frm[2].move = 1;
				}
				else {
					frm[2].move = 2;
				}
			}
			frm[2].x = 790;
		}
	}
}

//アイテム欄描画
void DrawItemColumn() {
	int i;
	if (pick == STATE_ONE) {
		DrawTBox(0, 0, DISP_W, DISP_H, GetColor(0, 0, 0));
	}
	i = 0;
	SetDrawMode(AMDRAW_ALPHABLEND, healthAlpha);
	DrawMemTh(frm[i].x, frm[i].y, frm[i].cg);
	DrawMemTh(frm[i].x - 30, frm[i].y - 60, cgSystemButton);
	DrawMemTh(frm[i].x - 20, frm[i].y - 55, ButtonX);
	DrawString(frm[i].x + 15, frm[i].y - 45, "所持アイテム", GetColor(0, 0, 0));
	SetDrawMode(AMDRAW_NOBLEND, 0);

	i = 1;
	SetDrawMode(AMDRAW_ALPHABLEND, healthAlpha);
	DrawMemTh(frm[i].x, frm[i].y, frm[i].cg);
	DrawMemTh(frm[i].x, frm[i].y - 35, cgSystemButton);
	DrawMemTh(frm[i].x + 10, frm[i].y - 25, cgPageSelect_left);
	DrawMemTh(frm[i].x + 40, frm[i].y - 30, ButtonLB);
	DrawMemTh(frm[i].x + 80, frm[i].y - 30, ButtonRB);
	DrawMemTh(frm[i].x + 115, frm[i].y - 25, cgPageSelect_right);
	SetDrawMode(AMDRAW_NOBLEND, 0);

	i = 2;
	if (pick != STATE_ONE) {
		SetDrawMode(AMDRAW_ALPHABLEND, healthAlpha);
		DrawMemTh(frm[i].x, frm[i].y, frm[i].cg);
		SetDrawMode(AMDRAW_NOBLEND, 0);
	}
	else {
		if ((gFrameCount % 60) < 50) {
			SetDrawMode(AMDRAW_ALPHABLEND, healthAlpha);
			DrawMemTh(frm[i].x, frm[i].y, frm[i].cg);
			SetDrawMode(AMDRAW_NOBLEND, 0);
		}
	}

}

// 体力バー描画
void DrawAliceHealth() {
	int i;

	SetDrawMode(AMDRAW_ALPHABLEND, healthAlpha);
	DrawMemTh(0, 0, cgHealth);

	for (i = 0; i < HP_MAX; i++) {
		if (hrt[i].use == 1) {
			DrawMemTh(hrt[i].x, hrt[i].y, cgLife[i]);
		}

		if ((IsHitBox(
			al.x + al.hit_x, al.y + al.hit_y, al.hit_w, al.hit_h,
			0, 0, 500, 300)
			) ||
			IsHitBox(
				al.x + al.hit_x - cv.view_y, al.y + al.hit_y - cv.view_y, al.hit_w, al.hit_h,
				800, 640, DISP_W, DISP_H)) {
			healthAlpha = 60;
		}
		else {
			healthAlpha = 255;
		}

		// HP増減によるハートの描画数の変化
		// ここのコードは変わる可能性が高い
		if (al.hitpoint <= 0) {
			hrt[0].use = 0;
			hrt[1].use = 0;
			hrt[2].use = 0;
			hrt[3].use = 0;
			hrt[4].use = 0;
			hrt[5].use = 0;
		}
		if (al.hitpoint == 1) {
			hrt[0].use = 1;
			hrt[1].use = 0;
			hrt[2].use = 0;
			hrt[3].use = 0;
			hrt[4].use = 0;
			hrt[5].use = 0;
		}
		if (al.hitpoint == 2) {
			hrt[0].use = 1;
			hrt[1].use = 1;
			hrt[2].use = 0;
			hrt[3].use = 0;
			hrt[4].use = 0;
			hrt[5].use = 0;
		}
		if (al.hitpoint == 3) {
			hrt[0].use = 1;
			hrt[1].use = 1;
			hrt[2].use = 1;
			hrt[3].use = 0;
			hrt[4].use = 0;
			hrt[5].use = 0;
		}
		if (al.hitpoint == 4) {
			hrt[0].use = 1;
			hrt[1].use = 1;
			hrt[2].use = 1;
			hrt[3].use = 1;
			hrt[4].use = 0;
			hrt[5].use = 0;
		}
		if (al.hitpoint == 5) {
			hrt[0].use = 1;
			hrt[1].use = 1;
			hrt[2].use = 1;
			hrt[3].use = 1;
			hrt[4].use = 1;
			hrt[5].use = 0;
		}
		if (al.hitpoint == 6) {
			hrt[0].use = 1;
			hrt[1].use = 1;
			hrt[2].use = 1;
			hrt[3].use = 1;
			hrt[4].use = 1;
			hrt[5].use = 1;
		}
	}
	SetDrawMode(AMDRAW_NOBLEND, 0);
}

// 個数カウント描画
void DrawEquipment(int x, int y, int itemNumber) {
	if ((selectTrg == STATE_ONE) || (check == STATE_ONE)) {
		if (pick == STATE_NONE) {
			DrawMemTh(x, y, cgMulti);
			DrawMemTh(x + 30, y, cgEquipment[(itemNumber / 10) % 3]);
			DrawMemTh(x + 60, y, cgEquipment[(itemNumber / 1) % 10]);
		}
	}
}

void DrawItemEquipment(int x, int y, int itemNumber) {
	DrawMemTh(x + 30, y + 40, cgMulti2);
	DrawMemTh(x + 40, y + 40, cgEquipment2[(itemNumber / 10) % 2]);
	DrawMemTh(x + 50, y + 40, cgEquipment2[(itemNumber / 1) % 10]);
}

void DrawDescription() {
	int i;
	switch (stateStage) {
	case STATE_EP1STAGE:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "トゲ爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "無属性の爆弾、全モンスターに2ダメージ与える", GetColor(0, 0, 0));
				}
			}

			i = 4;
			if (re[i].y - 240 == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート1個分回復する", GetColor(0, 0, 0));
				}
			}
			i = 6;
			if (re[i].y + 160 == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "投げナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "全モンスターに1ダメージを与える", GetColor(0, 0, 0));
				}
			}
			break;
		}
	case STATE_EP1STAGE_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "トゲ爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "無属性の爆弾、全モンスターに2ダメージ与える", GetColor(0, 0, 0));
				}
			}
			i = 1;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "火炎爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性の爆弾、火属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 2;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷凍爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性の爆弾、氷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 3;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "雷電爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性の爆弾、雷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 4;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート1個分回復する", GetColor(0, 0, 0));
				}
			}
			i = 5;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ハイポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート3個分回復する", GetColor(0, 0, 0));
				}
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "投げナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "全モンスターに1ダメージを与える", GetColor(0, 0, 0));
				}
			}
		}
		break;
	case STATE_EP1STAGE_3:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "トゲ爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "無属性の爆弾、全モンスターに2ダメージ与える", GetColor(0, 0, 0));
				}
			}
			i = 1;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "火炎爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性の爆弾、火属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 2;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷凍爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性の爆弾、氷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 3;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "雷電爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性の爆弾、雷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 4;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート1個分回復する", GetColor(0, 0, 0));
				}
			}
			i = 5;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ハイポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート3個分回復する", GetColor(0, 0, 0));
				}
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "投げナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "全モンスターに1ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 7;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "火炎ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性のナイフ、火属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 8;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷凍ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性のナイフ、氷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 9;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "電撃ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性のナイフ、雷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
		}
		break;
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
		if (sel.page == 1) {
			i = 0;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "トゲ爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "無属性の爆弾、全モンスターに2ダメージ与える", GetColor(0, 0, 0));
				}
			}
			i = 1;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "火炎爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性の爆弾、火属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 2;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷凍爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性の爆弾、氷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 3;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "雷電爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性の爆弾、雷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 4;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート1個分回復する", GetColor(0, 0, 0));
				}
			}
			i = 5;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ハイポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート3個分回復する", GetColor(0, 0, 0));
				}
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "投げナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "全モンスターに1ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 7;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "火炎ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性のナイフ、火属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 8;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷凍ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性のナイフ、氷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 9;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "電撃ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性のナイフ、雷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 10;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "焼却爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性の爆弾、火属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 11;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷却爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性の爆弾、氷属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
		}
		if (sel.page == 3) {
			i = 12;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "雷撃爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性の爆弾、雷属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 13;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "フルポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力を完全回復する", GetColor(0, 0, 0));
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
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "トゲ爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "無属性の爆弾、全モンスターに2ダメージ与える", GetColor(0, 0, 0));
				}
			}
			i = 1;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "火炎爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性の爆弾、火属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 2;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷凍爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性の爆弾、氷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 3;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "雷電爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性の爆弾、雷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 4;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート1個分回復する", GetColor(0, 0, 0));
				}
			}
			i = 5;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "ハイポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力ゲージをハート3個分回復する", GetColor(0, 0, 0));
				}
			}
		}
		if (sel.page == 2) {
			i = 6;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "投げナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "全モンスターに1ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 7;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "火炎ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性のナイフ、火属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 8;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷凍ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性のナイフ、氷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 9;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "電撃ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性のナイフ、雷属性が弱点の敵に3ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 10;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "焼却爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性の爆弾、火属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 11;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷却爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性の爆弾、氷属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
		}
		if (sel.page == 3) {
			i = 12;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "雷撃爆弾", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性の爆弾、雷属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 13;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "フルポーション", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "体力を完全回復する", GetColor(0, 0, 0));
				}
			}
			i = 14;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "焼却ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "火属性のナイフ、火属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 15;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "冷却ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "氷属性のナイフ、氷属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
			i = 16;
			if (re[i].y == sel.y - 10) {
				if (re[i].use == 0) {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 50, de.y + 40, "???", GetColor(0, 0, 0));
				}
				else {
					DrawMemTh(de.x, de.y, cgDescription);
					DrawString(de.x + 20, de.y + 20, "雷撃ナイフ", GetColor(0, 0, 0));
					DrawString(de.x + 20, de.y + 40, "雷属性のナイフ、雷属性が弱点の敵に6ダメージを与える", GetColor(0, 0, 0));
				}
			}
		}
		break;
	}
}