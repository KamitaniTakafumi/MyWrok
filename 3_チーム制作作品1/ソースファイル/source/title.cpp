/*------------------------------------------------
*  @file title.cpp
*  @brief タイトル処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  ヘッダーファイルのインクルード
------------------------------------------------*/
#include	<Windows.h>
#include	<math.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"title.h"
#include	"script_parser.h"
#include	"episode1S.h"
#include	"episode2S.h"
#include	"episode1L.h"
#include	"episode2L.h"
#include	"global.h"
#include	"HitJudgment.h"
#include	"UI.h"

/*------------------------------------------------
*  定数定義
------------------------------------------------*/

#define	CURPOS_NUM			2	// カーソル位置の数
#define CUR_MOVE_FRAME		7	// カーソル移動の時間

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

// 画像データ
int cgTeamLogo;			// チームロゴ
int	cgTitle;			// タイトル
int cgTitleBg;			// 背景
int cgCursor;			// カーソル
int cgStartExit;		// スタート、イグジスト
int cgChapterselect;	// 一章、二章

int selectNumber;			// 選択回数
int selectMenu;				// タイトル選択
int selectEpisode;			// 章選択
float	xspan;				// 横揺れの幅
int curmove_start_count;	// カーソル移動開始時カウント
int curmove_start_pos_y;	// カーソル移動元
int curmove_end_pos_y;		// カーソル移動先
int keyflag;				// タイトルステート
double bi_alpha = 255;		// 透明度
double bo_alpha = 0;		// 透明度
int gCamViewX, gCamViewY;	// カメラ位置（画面左上）

// カーソル情報
struct CURSOR curpos;

/*-------------------------------------------------
*  初期化
-------------------------------------------------*/
// カーソル位置
int curpos_y_table[] = {
	500,
	600
};

// 初期設定
int intoTitle() {

	stateStage = STATE_TITLE;
	selectNumber = 1;
	selectMenu = 0;
	selectEpisode = 0;
	keyflag = 0;
	bi_alpha = 255;
	bo_alpha = 0;

	// カメラ初期化
	gCamViewX = 0;
	gCamViewY = TITLESIZE_H - DISP_H;

	return STATE_TITLE;
}

// 画像データのロード
void LoadCgTitle() {
	cgTeamLogo = LoadTexture("res/TeamLogo.png");
	cgTitle = LoadTexture("res/alche_title.png");
	cgTitleBg = LoadTexture("res/titleBg.png");
	cgCursor = LoadTexture("res/alche_title_icon.png");
	cgStartExit = LoadTexture("res/alche_start_exit.png");
	cgChapterselect = LoadTexture("res/alche_chapter.png");
}

// カーソル初期化
void cursorInit() {

	// カメラ初期化
	gCamViewX = 0;
	gCamViewY = TITLESIZE_H - DISP_H;

	// メニュー選択の初期化
	selectNumber = 1;
	selectMenu = 0;

	// カーソル位置の初期設定
	curpos.x = 510;
	curpos.y = curpos_y_table[selectMenu];
	xspan = 2;
	curmove_start_pos_y = curpos_y_table[selectMenu];
	curmove_end_pos_y = curpos_y_table[selectMenu];

	PlayMemLoop(bgmTitle);			  // BGM再生スタート
}

/*-------------------------------------------------
*  更新
-------------------------------------------------*/

// 減速移動
int LerpL(int cnt, int max, int start, int end) {
	int n;
	if (cnt >= max) {
		n = end;
	}
	else {
		n = start + (end - start) * (((max * 2 - cnt + 1) * cnt) / 2) / (((max + 1) * max) / 2);
	}
	return n;
}

// タイトル選択画面
int titleSelect() {
	/* タイトル選択画面の設定 */

	BgScroll();	// 背景を動かす

	float rad = ((float)gFrameCount * (xspan)) * PI / 45;
	curpos.x = curpos.x + (int)(sin(rad) * xspan);

	// 上、下に動かして選択 
	// 始めるかゲームを閉じるかを選択 
	if (selectNumber == 1) {
		int curpos_backup = selectMenu;
		if (gTrg & KEYIN_DOWN) {
			PlayMemBack(seCursor);
			selectMenu++;
		}
		if (gTrg & KEYIN_UP) {
			PlayMemBack(seCursor);
			selectMenu--;
		}

		selectMenu = (selectMenu + CURPOS_NUM) % CURPOS_NUM;

		if (curpos_backup != selectMenu) {
			// 移動が始まったのでアニメーション用の値をセットする
			curmove_start_count = gFrameCount;
			curmove_start_pos_y = curpos_y_table[curpos_backup];
			curmove_end_pos_y = curpos_y_table[selectMenu];
		}

		// カーソル位置計算
		curpos.y = LerpL(gFrameCount - curmove_start_count, CUR_MOVE_FRAME, curmove_start_pos_y, curmove_end_pos_y);

		if (gTrg & KEYIN_X) {
			PlayMemBack(seSelect);
			if (selectMenu == 0) {
				selectNumber = 2;	// 章選択に移る
				selectEpisode = 0;
				curpos.y = curpos_y_table[selectEpisode];
				curmove_start_pos_y = curpos_y_table[selectEpisode];
				curmove_end_pos_y = curpos_y_table[selectEpisode];
			}
			if (selectMenu == 1) {
				exit(0);			// 画面を閉じる
			}
		}
		return STATE_TITLE;
	}

	/* 章選択 */
	// 一章か二章を選ぶ
	if (selectNumber == 2) {
		int curpos_backup = selectEpisode;

		if (keyflag == 0) {
			if (gTrg & KEYIN_DOWN) {
				PlayMemBack(seCursor);
				selectEpisode++;
			}
			if (gTrg & KEYIN_UP) {
				PlayMemBack(seCursor);
				selectEpisode--;
			}
		}

		selectEpisode = (selectEpisode + CURPOS_NUM) % CURPOS_NUM;

		if (curpos_backup != selectEpisode) {
			// 移動が始まったのでアニメーション用の値をセットする
			curmove_start_count = gFrameCount;
			curmove_start_pos_y = curpos_y_table[curpos_backup];
			curmove_end_pos_y = curpos_y_table[selectEpisode];
		}

		// カーソル位置計算
		curpos.y = LerpL(gFrameCount - curmove_start_count, CUR_MOVE_FRAME, curmove_start_pos_y, curmove_end_pos_y);

		/* ステージ移動 */
		if (gTrg & KEYIN_X) {
			PlayMemBack(seSelect);
			if (keyflag == 0) {
				keyflag++;
			}
		}

		// 1章を選択
		if (selectEpisode == 0) {
			if (bo_alpha >= 255) {
				// BGM再生ストップ
				stateStage = STATE_EP1STORY;
				cursorInit();
				StopPlayMem(bgmTitle);
				ScriptDestroy();
				return IntoEpisode1S();		// ストーリーに飛ぶ
			}
		}
		// 2章を選択
		if (selectEpisode == 1) {
			if (clearflag < 1) {
				keyflag = 0;
			}
			else if (clearflag >= 1) {
				if (bo_alpha >= 255) {
					// BGM再生ストップ
					stateStage = STATE_EP2STORY;
					cursorInit();
					StopPlayMem(bgmTitle);
					return IntoEpisode2S();		// ストーリーに飛ぶ
				}
			}
		}

		// Escapeキーで前の選択に戻す
		if (gTrg & KEYIN_Z) {
			if (keyflag == 0) {
				PlayMemBack(seCancel);
				if (selectNumber == 2) {
					selectNumber = 1;
					selectMenu = 0;
					curpos.y = curpos_y_table[selectMenu];
					curmove_start_pos_y = curpos_y_table[selectMenu];
					curmove_end_pos_y = curpos_y_table[selectMenu];
				}
			}
		}
	}
	return STATE_TITLE;
}

/*------------------------------------------------------
*  描画
------------------------------------------------------*/

// タイトルの表示
void DrawTitle() {
	if (selectNumber == 1) {
		DrawMemTh(500, 460, cgStartExit);
	}
	if (selectNumber == 2) {
		DrawMemTh(500, 460, cgChapterselect);
	}
}

//	カーソルの表示
void DrawCursor() {
	DrawMemTh(curpos.x, curpos.y, cgCursor);
}

// 背景の表示
void DrawBg() {
	DrawMemTh(420, 80, cgTitle);
	DrawMemTh(DISP_W - 320, DISP_H - 160, cgTeamLogo);
}

// フェードイン
void blackfadein() {
	// 矩形

	SetDrawMode(AMDRAW_ALPHABLEND, bi_alpha);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (bi_alpha > 0) {
		bi_alpha -= 15;
	}
}

// フェードアウト
void blackfadeout() {
	// 矩形

	SetDrawMode(AMDRAW_ALPHABLEND, bo_alpha);
	DrawFBox(0, 0,
		1280, 720,
		GetColor(0, 0, 0));
	if (keyflag == 1) {
		if (bo_alpha < 255) {
			bo_alpha += 3;
		}
	}

}

// 背景処理
void BgScroll()
{
	gCamViewY -= SCROLL_SPEED;
}

// 背景描画
void DrawScrollBg()
{
	// 背景（チップとして同じ画像を並べて描画する）
	int x, y;
	for (y = 0; y < (TITLESIZE_H / BGSIZE_H) + 1; y++)
	{
		int pos_y = y * BGSIZE_H - gCamViewY;

		if (gCamViewY < 0) {
			gCamViewY = TITLESIZE_H - DISP_H;
		}

		// 画面内に画像範囲が入っているか確認（高速化用）
		if (0 <= pos_y + BGSIZE_H && pos_y < DISP_H)
		{
			for (x = 0; x < (TITLESIZE_W / BGSIZE_W) + 1; x++)
			{
				int pos_x = x * BGSIZE_W - gCamViewX;
				// 画面内に画像範囲が入っているか確認（高速化用）
				if (0 <= pos_x + BGSIZE_W && pos_x < DISP_W)
				{
					DrawMemTh(pos_x, pos_y, cgTitleBg);
				}
			}
		}
	}
}

// 描画
void DrawTitleProcess() {

	// 画面を消す
	HCls();

	//SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// 背景
	DrawScrollBg(); // タイトル背景がスクロールする

	// 画像 ////////////
	DrawBg();
	DrawTitle();	// タイトル画像
	DrawCursor();	// タイトルカーソル
	blackfadein();	// フェードイン
	blackfadeout();	// フェードアウト

	// 更新
	Flip();

}