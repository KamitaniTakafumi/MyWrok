/*
 * @file Texteru.cpp
 * @brief テクスチャ処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "Texture.h"
#include "library.h"
#include "game.h"
#include "SceneMain.h"
#include "player.h"

// 画像情報
KT_2DPIC_INFO texture[MAX_TEXTURE];		// 読み込むテクスチャ数
TEXTURE flag[MAX_FLAG];					// フラグ
TEXTURE mushroom[MAX_MUSHROOM];			// きのこ
TEXTURE goldapple[MAX_GOLDAPPLE];		// 金りんご
TEXTURE surprised[MAX_SURPRISED];		// ビックリマーク
TEXTURE question[MAX_QUESTION];			// はてなマーク
TLVERTX VertexDataTbl[4];				// 頂点情報配列

/*
 * テクスチャ読み込み
 */
void ReadTexture()
{
	// プレイヤーステータス
	texture[STATUS1] = CreateTexture("res/UI/status_base/player1.png");
	texture[STATUS2] = CreateTexture("res/UI/status_base/player2.png");
	texture[STATUS3] = CreateTexture("res/UI/status_base/player3.png");
	texture[STATUS4] = CreateTexture("res/UI/status_base/player4.png");

	// ポイント
	texture[POINT0] = CreateTexture("res/UI/point_number/point0.1.png");
	texture[POINT1] = CreateTexture("res/UI/point_number/point1.1.png");
	texture[POINT2] = CreateTexture("res/UI/point_number/point2.1.png");
	texture[POINT3] = CreateTexture("res/UI/point_number/point3.1.png");
	texture[POINT4] = CreateTexture("res/UI/point_number/point4.1.png");
	texture[POINT5] = CreateTexture("res/UI/point_number/point5.1.png");
	texture[POINT6] = CreateTexture("res/UI/point_number/point6.1.png");
	texture[POINT7] = CreateTexture("res/UI/point_number/point7.1.png");
	texture[POINT8] = CreateTexture("res/UI/point_number/point8.1.png");
	texture[POINT9] = CreateTexture("res/UI/point_number/point9.1.png");

	// 制限時間
	texture[TIMEBASE] = CreateTexture("res/time/time_base.png");
	texture[TIME0] = CreateTexture("res/time/time0.png");
	texture[TIME1] = CreateTexture("res/time/time1.png");
	texture[TIME2] = CreateTexture("res/time/time2.png");
	texture[TIME3] = CreateTexture("res/time/time3.png");
	texture[TIME4] = CreateTexture("res/time/time4.png");
	texture[TIME5] = CreateTexture("res/time/time5.png");
	texture[TIME6] = CreateTexture("res/time/time6.png");
	texture[TIME7] = CreateTexture("res/time/time7.png");
	texture[TIME8] = CreateTexture("res/time/time8.png");
	texture[TIME9] = CreateTexture("res/time/time9.png");

	// 死亡フラグ
	texture[FLAG1] = CreateTexture("res/charEvents/flag_red.png");
	texture[FLAG2] = CreateTexture("res/charEvents/flag_blue.png");
	texture[FLAG3] = CreateTexture("res/charEvents/flag_green.png");
	texture[FLAG4] = CreateTexture("res/charEvents/flag_purple.png");

	// ドロップアイテム
	texture[APPLE] = CreateTexture("Assets/object/dropitem/apple.png");
	texture[GOLDAPPLE] = CreateTexture("Assets/object/dropitem/goldapple.png");
	texture[MUSHROOM] = CreateTexture("Assets/object/dropitem/mushroom.png");

	// マーク
	texture[SURPRISED] = CreateTexture("res/charEvents/bikkuri.png");
	texture[QUESTION] = CreateTexture("res/charEvents/question.png");

	// アウトゲーム
	texture[TITLE] = CreateTexture("res/title/taitorurogo.png");
	texture[END] = CreateTexture("res/title/exit.png");
	texture[START] = CreateTexture("res/title/gamestart.png");
	texture[HAZIMERU] = CreateTexture("res/title/taitoru_hazimeru.png");
	texture[LOBBY] = CreateTexture("res/title/lobby.png");
	texture[RESULT] = CreateTexture("res/result/result.png");
	texture[LOAD] = CreateTexture("res/load/loading.png");
	texture[TITLELOGO] = CreateTexture("res/load/title_logo.png");
	texture[TEAMLOGO] = CreateTexture("res/load/team_logo.png");
	texture[POSE] = CreateTexture("res/pose/lobby.png");
	texture[BACK] = CreateTexture("res/pose/back.png");
	texture[TITLEBACK] = CreateTexture("res/pose/titleback.png");

	// 操作説明、合図
	texture[OPERATION] = CreateTexture("res/title/sousa.png");
	texture[OPERATION2] = CreateTexture("res/title/sousa2.png");
	texture[NEXT] = CreateTexture("res/title/next.png");
	texture[STARTSIGNAL] = CreateTexture("res/signal/startsignal.png");
	texture[ENDSIGNAL] = CreateTexture("res/signal/endsignal.png");

	CreateSprit();

	// 死亡フラグ
	flag[0].type = FLAG1;
	flag[0].Position = D3DXVECTOR3(0, 0, 0);
	flag[0].Radius = 30.0f;
	flag[0].use = 0;
	flag[1].type = FLAG2;
	flag[1].Position = D3DXVECTOR3(0, 0, 0);
	flag[1].Radius = 30.0f;
	flag[1].use = 0;
	flag[2].type = FLAG3;
	flag[2].Position = D3DXVECTOR3(0, 0, 0);
	flag[2].Radius = 30.0f;
	flag[2].use = 0;
	flag[3].type = FLAG4;
	flag[3].Position = D3DXVECTOR3(0, 0, 0);
	flag[3].Radius = 30.0f;
	flag[3].use = 0;

	// ドロップアイテム
	// キノコ(木)
	mushroom[0].type = MUSHROOM;
	mushroom[0].Position = D3DXVECTOR3(-190, 0, -270);
	mushroom[0].Radius = 30.0f;
	mushroom[0].use = 0; 
	mushroom[1].type = MUSHROOM;
	mushroom[1].Position = D3DXVECTOR3(-120, 0, -220);
	mushroom[1].Radius = 30.0f;
	mushroom[1].use = 0;
	mushroom[2].type = MUSHROOM;
	mushroom[2].Position = D3DXVECTOR3(-30, 0, -300);
	mushroom[2].Radius = 30.0f;
	mushroom[2].use = 0;

	mushroom[3].type = MUSHROOM;
	mushroom[3].Position = D3DXVECTOR3(860, 97, -840);
	mushroom[3].Radius = 30.0f;
	mushroom[3].use = 0;
	mushroom[4].type = MUSHROOM;
	mushroom[4].Position = D3DXVECTOR3(800, 97, -750);
	mushroom[4].Radius = 30.0f;
	mushroom[4].use = 0;
	mushroom[5].type = MUSHROOM;
	mushroom[5].Position = D3DXVECTOR3(620, 97, -720);
	mushroom[5].Radius = 30.0f;
	mushroom[5].use = 0;

	mushroom[6].type = MUSHROOM;
	mushroom[6].Position = D3DXVECTOR3(-600, 95, -690);
	mushroom[6].Radius = 30.0f;
	mushroom[6].use = 0;
	mushroom[7].type = MUSHROOM;
	mushroom[7].Position = D3DXVECTOR3(-720, 95, -690);
	mushroom[7].Radius = 30.0f;
	mushroom[7].use = 0;
	mushroom[8].type = MUSHROOM;
	mushroom[8].Position = D3DXVECTOR3(-820, 95, -690);
	mushroom[8].Radius = 30.0f;
	mushroom[8].use = 0;

	mushroom[9].type = MUSHROOM;
	mushroom[9].Position = D3DXVECTOR3(890, 190, -1000);
	mushroom[9].Radius = 30.0f;
	mushroom[9].use = 0;
	mushroom[10].type = MUSHROOM;
	mushroom[10].Position = D3DXVECTOR3(850, 190, -1100);
	mushroom[10].Radius = 30.0f;
	mushroom[10].use = 0;
	mushroom[11].type = MUSHROOM;
	mushroom[11].Position = D3DXVECTOR3(630, 190, -1000);
	mushroom[11].Radius = 30.0f;
	mushroom[11].use = 0;

	mushroom[12].type = MUSHROOM;
	mushroom[12].Position = D3DXVECTOR3(600, 290, -1650);
	mushroom[12].Radius = 30.0f;
	mushroom[12].use = 0;
	mushroom[13].type = MUSHROOM;
	mushroom[13].Position = D3DXVECTOR3(510, 290, -1400);
	mushroom[13].Radius = 30.0f;
	mushroom[13].use = 0;
	mushroom[14].type = MUSHROOM;
	mushroom[14].Position = D3DXVECTOR3(400, 290, -1450);
	mushroom[14].Radius = 30.0f;
	mushroom[14].use = 0;

	mushroom[15].type = MUSHROOM;
	mushroom[15].Position = D3DXVECTOR3(-720, 290, -1480);
	mushroom[15].Radius = 30.0f;
	mushroom[15].use = 0;
	mushroom[16].type = MUSHROOM;
	mushroom[16].Position = D3DXVECTOR3(-730, 290, -1370);
	mushroom[16].Radius = 30.0f;
	mushroom[16].use = 0;
	mushroom[17].type = MUSHROOM;
	mushroom[17].Position = D3DXVECTOR3(-870, 290, -1370);
	mushroom[17].Radius = 30.0f;
	mushroom[17].use = 0;

	// キノコ(岩)
	mushroom[18].type = MUSHROOM;
	mushroom[18].Position = D3DXVECTOR3(-760, 0, -320);
	mushroom[18].Radius = 30.0f;
	mushroom[18].use = 0;
	mushroom[19].type = MUSHROOM;
	mushroom[19].Position = D3DXVECTOR3(-930, 0, -470);
	mushroom[19].Radius = 30.0f;
	mushroom[19].use = 0;
	mushroom[20].type = MUSHROOM;
	mushroom[20].Position = D3DXVECTOR3(-920, 0, -370);
	mushroom[20].Radius = 30.0f;
	mushroom[20].use = 0;

	mushroom[21].type = MUSHROOM;
	mushroom[21].Position = D3DXVECTOR3(1060, 97, -710);
	mushroom[21].Radius = 30.0f;
	mushroom[21].use = 0;
	mushroom[22].type = MUSHROOM;
	mushroom[22].Position = D3DXVECTOR3(965, 97, -880);
	mushroom[22].Radius = 30.0f;
	mushroom[22].use = 0;
	mushroom[23].type = MUSHROOM;
	mushroom[23].Position = D3DXVECTOR3(950, 97, -720);
	mushroom[23].Radius = 30.0f;
	mushroom[23].use = 0;

	mushroom[24].type = MUSHROOM;
	mushroom[24].Position = D3DXVECTOR3(-950, 95, -790);
	mushroom[24].Radius = 30.0f;
	mushroom[24].use = 0;
	mushroom[25].type = MUSHROOM;
	mushroom[25].Position = D3DXVECTOR3(-950, 95, -620);
	mushroom[25].Radius = 30.0f;
	mushroom[25].use = 0;
	mushroom[26].type = MUSHROOM;
	mushroom[26].Position = D3DXVECTOR3(-1060, 95, -650);
	mushroom[26].Radius = 30.0f;
	mushroom[26].use = 0;

	mushroom[27].type = MUSHROOM;
	mushroom[27].Position = D3DXVECTOR3(-90, 190, -1120);
	mushroom[27].Radius = 30.0f;
	mushroom[27].use = 0;
	mushroom[28].type = MUSHROOM;
	mushroom[28].Position = D3DXVECTOR3(-240, 190, -1270);
	mushroom[28].Radius = 30.0f;
	mushroom[28].use = 0;
	mushroom[29].type = MUSHROOM;
	mushroom[29].Position = D3DXVECTOR3(-200, 190, -1130);
	mushroom[29].Radius = 30.0f;
	mushroom[29].use = 0;

	mushroom[30].type = MUSHROOM;
	mushroom[30].Position = D3DXVECTOR3(985, 290, -1320);
	mushroom[30].Radius = 30.0f;
	mushroom[30].use = 0;
	mushroom[31].type = MUSHROOM;
	mushroom[31].Position = D3DXVECTOR3(970, 290, -1440);
	mushroom[31].Radius = 30.0f;
	mushroom[31].use = 0;
	mushroom[32].type = MUSHROOM;
	mushroom[32].Position = D3DXVECTOR3(850, 290, -1440);
	mushroom[32].Radius = 30.0f;
	mushroom[32].use = 0;

	mushroom[33].type = MUSHROOM;
	mushroom[33].Position = D3DXVECTOR3(-500, 290, -1220);
	mushroom[33].Radius = 30.0f;
	mushroom[33].use = 0;
	mushroom[34].type = MUSHROOM;
	mushroom[34].Position = D3DXVECTOR3(-510, 290, -1370);
	mushroom[34].Radius = 30.0f;
	mushroom[34].use = 0;
	mushroom[35].type = MUSHROOM;
	mushroom[35].Position = D3DXVECTOR3(-610, 290, -1250);
	mushroom[35].Radius = 30.0f;
	mushroom[35].use = 0;

	// 金のリンゴ
	goldapple[0].type = GOLDAPPLE;
	goldapple[0].Position = D3DXVECTOR3(320, 0, -290);
	goldapple[0].Radius = 30.0f;
	goldapple[0].use = 0;

	goldapple[1].type = GOLDAPPLE;
	goldapple[1].Position = D3DXVECTOR3(-70, 290, -1550);
	goldapple[1].Radius = 30.0f;
	goldapple[1].use = 0;

	// ビックリマーク
	// オブジェクト(木)
	surprised[0].type = SURPRISED;
	surprised[0].use = 0;
	surprised[0].x = 670.0f;
	surprised[0].y = 360.0f;
	surprised[1].type = SURPRISED;
	surprised[1].use = 0;
	surprised[1].x = 370.0f;
	surprised[1].y = 190.0f;
	surprised[2].type = SURPRISED;
	surprised[2].use = 0;
	surprised[2].x = 870.0f;
	surprised[2].y = 200.0f;

	surprised[3].type = SURPRISED;
	surprised[3].use = 0;
	surprised[3].x = 370.0f;
	surprised[3].y = 120.0f;
	surprised[4].type = SURPRISED;
	surprised[4].use = 0;
	surprised[4].x = 490.0f;
	surprised[4].y = 0.0f;
	surprised[5].type = SURPRISED;
	surprised[5].use = 0;
	surprised[5].x = 880.0f;
	surprised[5].y = 1.0f;

	// オブジェクト(岩)
	surprised[6].type = SURPRISED;
	surprised[6].use = 0;
	surprised[6].x = 950.0f;
	surprised[6].y = 310.0f;
	surprised[7].type = SURPRISED;
	surprised[7].use = 0;
	surprised[7].x = 260.0f;
	surprised[7].y = 180.0f;
	surprised[8].type = SURPRISED;
	surprised[8].use = 0;
	surprised[8].x = 990.0f;
	surprised[8].y = 200.0f;

	surprised[9].type = SURPRISED;
	surprised[9].use = 0;
	surprised[9].x = 680.0f;
	surprised[9].y = 80.0f;
	surprised[10].type = SURPRISED;
	surprised[10].use = 0;
	surprised[10].x = 330.0f;
	surprised[10].y = 30.0f;
	surprised[11].type = SURPRISED;
	surprised[11].use = 0;
	surprised[11].x = 800.0f;
	surprised[11].y = 40.0f;

	// オブジェクト(枯れ木)
	surprised[12].type = SURPRISED;
	surprised[12].use = 0;
	surprised[12].x = 470.0f;
	surprised[12].y = 350.0f;
	surprised[13].type = SURPRISED;
	surprised[13].use = 0;
	surprised[13].x = 600.0f;
	surprised[13].y = 0.0f;

	// はてなマーク
	question[0].type = QUESTION;
	question[0].use = 0;
	question[0].x = 700;
	question[0].y = 180;
	question[1].type = QUESTION;
	question[1].use = 0;
	question[1].x = 490;
	question[1].y = 100;
}

/*
 * テクスチャ初期化
 */
void ResetTexture()
{
	// 死亡フラグ
	flag[0].use = 0;
	flag[1].use = 0;
	flag[2].use = 0;
	flag[3].use = 0;

	// キノコ
	for (int i = 0; i < 36; i++)
	{
		mushroom[i].use = 0;
	}

	// 金のリンゴ
	goldapple[0].use = 0;
	goldapple[1].use = 0;

	// ビックリマーク
	for (int i = 0; i < MAX_SURPRISED; i++)
	{
		surprised[i].use = 0;
	}

	// はてなマーク
	for (int i = 0; i < 6; i++)
	{
		question[i].use = 0;
	}
}

/*
*  @brief 頂点データを格納する
*  @param *v 頂点データのポインタ
*  @param x1 頂点x座標
*  @param y1 頂点y座標
*  @param z1 頂点z座標
*  @param x2 頂点x座標
*  @param y2 頂点y座標
*  @param z2 頂点z座標
*/
void InitVertex(TLVERTX* v, float x1, float y1, float z1, float x2, float y2)
{
	//頂点配列をゼロクリア
	for (int i = 0; i < 4; i++)
	{
		v[i].x = 0.0f;
		v[i].y = 0.0f;
		v[i].z = 0.0f;
		v[i].rhw = 0.0f;
		v[i].color = D3DCOLOR_XRGB(0, 0, 0);
		v[i].tu = 0.0f;
		v[i].tv = 0.0f;
	}

	//---頂点Ａ１のデータ定義
	v[0].x = x1;                         // 頂点Ｘ座標
	v[0].y = y1;                         // 頂点Ｙ座標
	v[0].z = z1;                       // 頂点Ｚ座標
	v[0].rhw = 1.0f;                       // ２Ｄを扱うときの値
	v[0].tu = 0.0f;                       // テクスチャのＸ座標
	v[0].tv = 0.0f;                       // テクスチャのＹ座標
	v[0].color = D3DCOLOR_XRGB(255, 255, 255); // 頂点色
	//---頂点Ａ２のデータ定義
	v[1].x = x2;
	v[1].y = y1;
	v[1].z = z1;
	v[1].rhw = 1.0f;
	v[1].tu = 1.0f;
	v[1].tv = 0.0f;
	v[1].color = D3DCOLOR_XRGB(255, 255, 255);
	//---頂点Ａ３のデータ定義
	v[2].x = x2;
	v[2].y = y2;
	v[2].z = z1;
	v[2].rhw = 1.0f;
	v[2].tu = 1.0f;
	v[2].tv = 1.0f;
	v[2].color = D3DCOLOR_XRGB(255, 255, 255);
	//---頂点Ａ４のデータ定義
	v[3].x = x1;
	v[3].y = y2;
	v[3].z = z1;
	v[3].rhw = 1.0f;
	v[3].tu = 0.0f;
	v[3].tv = 1.0f;
	v[3].color = D3DCOLOR_XRGB(255, 255, 255);
}

/*
*  @brief フラグ描画
*  @param num プレイヤー識別番号
*/
void DropFlag(int num)
{
	if (num == 0)
	{
		flag[0].use = 1;
		flag[0].Position = Player[0]->position;
		InitVertex(VertexDataTbl, Player[0]->position.x, Player[0]->position.y + 50, Player[0]->position.z, Player[0]->position.x - 50, Player[0]->position.y);
	}
	else if (num == 1)
	{
		flag[1].use = 1;
		flag[1].Position = Player[1]->position;
		InitVertex(VertexDataTbl, Player[1]->position.x, Player[1]->position.y + 50, Player[1]->position.z, Player[1]->position.x - 50, Player[1]->position.y);
	}
	else if (num == 2)
	{
		flag[2].use = 1;
		flag[2].Position = Player[2]->position;
		InitVertex(VertexDataTbl, Player[2]->position.x, Player[2]->position.y + 50, Player[2]->position.z, Player[2]->position.x - 50, Player[2]->position.y);
	}
	else if (num == 3)
	{
		flag[3].use = 1;
		flag[3].Position = Player[3]->position;
		InitVertex(VertexDataTbl, Player[3]->position.x, Player[3]->position.y + 50, Player[3]->position.z, Player[3]->position.x - 50, Player[3]->position.y);
	}
}

/*
 * ポリゴン描画
 */
void DrawPorgon()
{
	// 描画するテクスチャをデバイスにセット
	gDevice->SetTexture(0, texture[FLAG1].texture);
	// 四角形ポリゴンをバックバッファに転送
	gDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, VertexDataTbl, sizeof(TLVERTX));
}

/*
 * フラグの描画
 */
void DrawFlag()
{
	// プレイヤー１のフラグ
	if (flag[0].use == 1)
	{
		DrawPorgon();
	}

	// プレイヤー２のフラグ
	if (flag[1].use == 1)
	{
		DrawPorgon();
	}

	// プレイヤー３のフラグ
	if (flag[2].use == 1)
	{
		DrawPorgon();
	}

	// プレイヤー４のフラグ
	if (flag[3].use == 1)
	{
		DrawPorgon();
	}
}

/*
 * マークの描画
 */
void DrawMark()
{
	// ビックリマーク
	for (int i = 0; i < MAX_SURPRISED; i++)
	{
		if (surprised[i].use == 1)
		{
			DrawTexture(surprised[i].x, surprised[i].y, &texture[SURPRISED], texture[SURPRISED].texture, DRAW_ALPHABLEND);
		}
	}
	// はてなマーク
	for (int i = 0; i < MAX_QUESTION; i++)
	{
		if (question[i].use == 1)
		{
			DrawTexture(question[i].x, question[i].y, &texture[QUESTION], texture[QUESTION].texture, DRAW_ALPHABLEND);
		}
	}
}

/*
*  @brief ポイント描画
*  @param x 座標
*  @param y 座標
*  @param point 試合ポイント
*/
void DrawEquipmentPoint(float x, float y, int point)
{
	int n, m;
	n = point;		// ポイントを代入
	m = 0;			// ０クリア
	if (n > 0)		// ポイントが０以上
	{
		for (int i = 0; n > 0; i++)		// ポイントが０以上の間繰り返す
		{
			m = n % 10;		// ポイントを10で割った余りを代入
			if (m == 0)
			{
				DrawTexture(x - i * 20, y, &texture[POINT0], texture[POINT0].texture, DRAW_ALPHABLEND);
			}
			else if (m == 1)
			{
				DrawTexture(x - i * 20, y, &texture[POINT1], texture[POINT1].texture, DRAW_ALPHABLEND);
			}
			else if (m == 2)
			{
				DrawTexture(x - i * 20, y, &texture[POINT2], texture[POINT2].texture, DRAW_ALPHABLEND);
			}
			else if (m == 3)
			{
				DrawTexture(x - i * 20, y, &texture[POINT3], texture[POINT3].texture, DRAW_ALPHABLEND);
			}
			else if (m == 4)
			{
				DrawTexture(x - i * 20, y, &texture[POINT4], texture[POINT4].texture, DRAW_ALPHABLEND);
			}
			else if (m == 5)
			{
				DrawTexture(x - i * 20, y, &texture[POINT5], texture[POINT5].texture, DRAW_ALPHABLEND);
			}
			else if (m == 6)
			{
				DrawTexture(x - i * 20, y, &texture[POINT6], texture[POINT6].texture, DRAW_ALPHABLEND);
			}
			else if (m == 7)
			{
				DrawTexture(x - i * 20, y, &texture[POINT7], texture[POINT7].texture, DRAW_ALPHABLEND);
			}
			else if (m == 8)
			{
				DrawTexture(x - i * 20, y, &texture[POINT8], texture[POINT8].texture, DRAW_ALPHABLEND);
			}
			else if (m == 9)
			{
				DrawTexture(x - i * 20, y, &texture[POINT9], texture[POINT9].texture, DRAW_ALPHABLEND);
			}
			n = n / 10;			// 桁数を減らす
		}
	}
	// 0描画
	else
	{
		DrawTexture(x, y, &texture[POINT0], texture[POINT0].texture, DRAW_ALPHABLEND);
	}
}

/*
*  @brief 時間描画
*  @param x 座標
*  @param y 座標
*  @param time 試合ポイント
*  @param zero 分と秒の区別
*/
void DrawEquipmentTime(float x, float y, int time, int zero)
{
	int n, m;
	n = time;		// 時間を代入
	m = 0;			// ゼロクリア
	if (n > 0)		// 時間が0以上だったら
	{
		for (int i = 0; n > 0; i++)		// 時間が０以上の間繰り返す
		{
			m = n % 10;			// 時間を割った余り
			if (m == 0)
			{
				DrawTexture(x - i * 25, y, &texture[TIME0], texture[TIME0].texture, DRAW_ALPHABLEND);
			}
			else if (m == 1)
			{
				DrawTexture(x - i * 25, y, &texture[TIME1], texture[TIME1].texture, DRAW_ALPHABLEND);
			}
			else if (m == 2)
			{
				DrawTexture(x - i * 25, y, &texture[TIME2], texture[TIME2].texture, DRAW_ALPHABLEND);
			}
			else if (m == 3)
			{
				DrawTexture(x - i * 25, y, &texture[TIME3], texture[TIME3].texture, DRAW_ALPHABLEND);
			}
			else if (m == 4)
			{
				DrawTexture(x - i * 25, y, &texture[TIME4], texture[TIME4].texture, DRAW_ALPHABLEND);
			}
			else if (m == 5)
			{
				DrawTexture(x - i * 25, y, &texture[TIME5], texture[TIME5].texture, DRAW_ALPHABLEND);
			}
			else if (m == 6)
			{
				DrawTexture(x - i * 25, y, &texture[TIME6], texture[TIME6].texture, DRAW_ALPHABLEND);
			}
			else if (m == 7)
			{
				DrawTexture(x - i * 25, y, &texture[TIME7], texture[TIME7].texture, DRAW_ALPHABLEND);
			}
			else if (m == 8)
			{
				DrawTexture(x - i * 25, y, &texture[TIME8], texture[TIME8].texture, DRAW_ALPHABLEND);
			}
			else if (m == 9)
			{
				DrawTexture(x - i * 25, y, &texture[TIME9], texture[TIME9].texture, DRAW_ALPHABLEND);
			}
			n = n / 10;			// 桁数を減らす
			// 時間が一桁の場合0を加えて揃える
			if (zero == 1 && i == 0 && n == 0)
			{
				DrawTexture(x - 25, y, &texture[TIME0], texture[TIME0].texture, DRAW_ALPHABLEND);
			}
		}
	}
	else
	{
		DrawTexture(x, y, &texture[TIME0], texture[TIME0].texture, DRAW_ALPHABLEND);
		if (zero == 1)
		{
			DrawTexture(x - 25, y, &texture[TIME0], texture[TIME0].texture, DRAW_ALPHABLEND);
		}
	}
}

/*
 * UI描画
 */
void DrawUI()
{
	DrawTexture(20.0f, 585.0f, &texture[STATUS1], texture[STATUS1].texture, DRAW_ALPHABLEND);
	DrawTexture(290.0f, 585.0f, &texture[STATUS2], texture[STATUS2].texture, DRAW_ALPHABLEND);
	DrawTexture(740.0f, 585.0f, &texture[STATUS3], texture[STATUS3].texture, DRAW_ALPHABLEND);
	DrawTexture(1010.0f, 585.0f, &texture[STATUS4], texture[STATUS4].texture, DRAW_ALPHABLEND);

}

/*
*  @brief 試合のポイント描画
*  @param num プレイヤー識別番号
*  @param point 試合のポイント
*  @param mode ゲームモード
*/
void DrawPoint(int num, int point, int mode)
{
	// 試合中
	if (mode == GAME_IN)
	{
		// プレイヤー１
		if (num == 0)
		{
			DrawEquipmentPoint(144, 585, point);
		}
		// プレイヤー２
		else if (num == 1)
		{
			DrawEquipmentPoint(413, 585, point);
		}
		// プレイヤー３
		else if (num == 2)
		{
			DrawEquipmentPoint(862, 585, point);
		}
		// プレイヤー４
		else if (num == 3)
		{
			DrawEquipmentPoint(1131, 585, point);
		}
	}
	// リザルト
	if (mode == GAME_RESULT)
	{
		// プレイヤー１
		if (num == 0)
		{
			DrawEquipmentPoint(190, 360, point);
			DrawEquipmentPoint(190, 580, point);
		}
		// プレイヤー２
		else if (num == 1)
		{
			DrawEquipmentPoint(530, 360, point);
			DrawEquipmentPoint(530, 580, point);
		}
		// プレイヤー３
		else if (num == 2)
		{
			DrawEquipmentPoint(860, 360, point);
			DrawEquipmentPoint(860, 580, point);
		}
		// プレイヤー４
		else if (num == 3)
		{
			DrawEquipmentPoint(1190, 360, point);
			DrawEquipmentPoint(1190, 580, point);
		}
	}
}

/*
*  @brief ヒットポイントの描画
*  @param num プレイヤー識別番号
*  @param hp ヒットポイント
*/
void DrawHitPoint(int num, int hp)
{
	// プレイヤー１
	if (num == 0)
	{
		DrawEquipmentPoint(194, 635, hp);
	}
	// プレイヤー２
	else if (num == 1)
	{
		DrawEquipmentPoint(463, 635, hp);
	}
	// プレイヤー３
	else if (num == 2)
	{
		DrawEquipmentPoint(912, 635, hp);
	}
	// プレイヤー４
	else if (num == 3)
	{
		DrawEquipmentPoint(1181, 635, hp);
	}
}

/*
*  @brief 試合時間の描画
*  @param minute 分
*  @param second 秒
*/
void DrawTime(int minute, int second)
{
	DrawTexture(570, 565, &texture[TIMEBASE], texture[TIMEBASE].texture, DRAW_ALPHABLEND);
	DrawEquipmentTime(600, 600, minute, 0);
	DrawEquipmentTime(660, 600, second, 1);
}

/*
 * アイテム描画
 */
void DrawItem()
{
	// 倒木１
	if (mushroom[0].use == 1)
	{
		DrawTexture(710, 390, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[1].use == 1)
	{
		DrawTexture(670, 410, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[2].use == 1)
	{
		DrawTexture(630, 380, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 倒木２
	if (mushroom[3].use == 1)
	{
		DrawTexture(320, 220, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[4].use == 1)
	{
		DrawTexture(340, 240, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[5].use == 1)
	{
		DrawTexture(400, 240, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 倒木３
	if (mushroom[6].use == 1)
	{
		DrawTexture(840, 240, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[7].use == 1)
	{
		DrawTexture(880, 240, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[8].use == 1)
	{
		DrawTexture(920, 240, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 倒木４
	if (mushroom[9].use == 1)
	{
		DrawTexture(320, 160, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[10].use == 1)
	{
		DrawTexture(340, 130, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[11].use == 1)
	{
		DrawTexture(420, 160, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 倒木５
	if (mushroom[12].use == 1)
	{
		DrawTexture(450, 10, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[13].use == 1)
	{
		DrawTexture(460, 50, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[14].use == 1)
	{
		DrawTexture(500, 40, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 倒木６
	if (mushroom[15].use == 1)
	{
		DrawTexture(830, 40, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[16].use == 1)
	{
		DrawTexture(860, 65, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[17].use == 1)
	{
		DrawTexture(900, 65, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}

	// 岩１
	if (mushroom[18].use == 1)
	{
		DrawTexture(930, 370, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[19].use == 1)
	{
		DrawTexture(970, 330, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[20].use == 1)
	{
		DrawTexture(975, 360, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 岩２
	if (mushroom[21].use == 1)
	{
		DrawTexture(240, 250, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[22].use == 1)
	{
		DrawTexture(290, 210, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[23].use == 1)
	{
		DrawTexture(280, 240, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 岩３
	if (mushroom[24].use == 1)
	{
		DrawTexture(960, 230, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[25].use == 1)
	{
		DrawTexture(970, 260, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[26].use == 1)
	{
		DrawTexture(1015, 265, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 岩４
	if (mushroom[27].use == 1)
	{
		DrawTexture(655, 130, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[28].use == 1)
	{
		DrawTexture(700, 105, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[29].use == 1)
	{
		DrawTexture(690, 125, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 岩５
	if (mushroom[30].use == 1)
	{
		DrawTexture(310, 70, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[31].use == 1)
	{
		DrawTexture(320, 40, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[32].use == 1)
	{
		DrawTexture(360, 50, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	// 岩６
	if (mushroom[33].use == 1)
	{
		DrawTexture(785, 85, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[34].use == 1)
	{
		DrawTexture(785, 60, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}
	if (mushroom[35].use == 1)
	{
		DrawTexture(820, 75, &texture[MUSHROOM], texture[MUSHROOM].texture, DRAW_ALPHABLEND);
	}

	// 枯れ木１
	if (goldapple[0].use == 1)
	{
		DrawTexture(490, 390, &texture[GOLDAPPLE], texture[GOLDAPPLE].texture, DRAW_ALPHABLEND);
	}
	if (goldapple[1].use == 1)
	{
		DrawTexture(640, 30, &texture[GOLDAPPLE], texture[GOLDAPPLE].texture, DRAW_ALPHABLEND);
	}

}

/*
 * アウトゲームの描画
 */
void DrawOutGame(float x, float y, int drawtype)
{
	if (drawtype == TITLE)
	{
		DrawTexture(x, y, &texture[TITLE], texture[TITLE].texture, DRAW_NOBLEND);		// タイトル背景
	}
	else if (drawtype == END)
	{
		DrawTexture(x, y, &texture[END], texture[END].texture, DRAW_ALPHABLEND);			// 看板(終わる)
	}
	else if (drawtype == START)
	{
		DrawTexture(x, y, &texture[START], texture[START].texture, DRAW_ALPHABLEND);		// 看板(プレイ)
	}
	else if (drawtype == HAZIMERU)
	{
		DrawTexture(x, y, &texture[HAZIMERU], texture[HAZIMERU].texture, DRAW_ALPHABLEND);	// 看板(始める)
	}
	else if (drawtype == LOBBY)
	{
		DrawTexture(x, y, &texture[LOBBY], texture[LOBBY].texture, DRAW_NOBLEND);		// ロビー背景
	}
	else if (drawtype == RESULT)
	{
		DrawTexture(x, y, &texture[RESULT], texture[RESULT].texture, DRAW_NOBLEND);		// ロビー背景
	}
	else if (drawtype == POSE)
	{
		DrawTexture(x, y, &texture[POSE], texture[POSE].texture, DRAW_NOBLEND);		// ロビー背景
	}
	else if (drawtype == BACK)
	{
		DrawTexture(x, y, &texture[BACK], texture[BACK].texture, DRAW_ALPHABLEND);		// ロビー背景
	}
	else if (drawtype == TITLEBACK)
	{
		DrawTexture(x, y, &texture[TITLEBACK], texture[TITLEBACK].texture, DRAW_ALPHABLEND);		// ロビー背景
	}
}

/*
 * 操作説明描画
 */
void DrawOperation(int drawtype)
{
	if (drawtype == OPERATION)
	{
		DrawTexture(0, 0, &texture[OPERATION], texture[OPERATION].texture, DRAW_NOBLEND);		// 操作説明１
	}
	if (drawtype == OPERATION2)
	{
		DrawTexture(0, 0, &texture[OPERATION2], texture[OPERATION2].texture, DRAW_NOBLEND);			// 操作説明１
	}
	if (drawtype == NEXT)
	{
		DrawTexture(1050, 640, &texture[NEXT], texture[NEXT].texture, DRAW_ALPHABLEND);				// 矢印
	}
	if (drawtype == STARTSIGNAL)
	{
		DrawTexture(0, 0, &texture[STARTSIGNAL], texture[STARTSIGNAL].texture, DRAW_ALPHABLEND);	// スタート合図
	}
	if (drawtype == ENDSIGNAL)
	{
		DrawTexture(0, 0, &texture[ENDSIGNAL], texture[ENDSIGNAL].texture, DRAW_ALPHABLEND);		// 終了合図
	}
}
