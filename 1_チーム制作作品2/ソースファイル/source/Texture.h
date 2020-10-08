#pragma once
/*
 * @file Texteru.cpp
 * @brief テクスチャ処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"

#define MAX_TEXTURE 51		// テクスチャの最大数
#define MAX_MUSHROOM 36		// キノコの最大数
#define MAX_GOLDAPPLE 2		// 金りんごの最大数
#define MAX_FLAG 4			// フラグの最大数
#define MAX_SURPRISED 14	// ビックリマークの最大数
#define MAX_QUESTION 2		// はてなマークの最大数

/*
*  テクスチャの種類
*/
enum TEXTURE_TYPE
{
	STATUS1,
	STATUS2,
	STATUS3,
	STATUS4,
	POINT0,
	POINT1,
	POINT2,
	POINT3,
	POINT4,
	POINT5,

	POINT6,
	POINT7,
	POINT8,
	POINT9,
	TIMEBASE,
	TIME0,
	TIME1,
	TIME2,
	TIME3,
	TIME4,

	TIME5,
	TIME6,
	TIME7,
	TIME8,
	TIME9,
	FLAG1,
	FLAG2,
	FLAG3,
	FLAG4,
	APPLE,

	GOLDAPPLE,
	MUSHROOM,
	SURPRISED,
	QUESTION,
	TITLE,
	END,
	START,
	HAZIMERU,
	LOBBY,
	RESULT,
	LOAD,
	TITLELOGO,
	TEAMLOGO,
	POSE,
	BACK,
	TITLEBACK,

	OPERATION,
	OPERATION2,
	NEXT,
	STARTSIGNAL,
	ENDSIGNAL,
};

/*
*  テクスチャの構造体
*/
struct TEXTURE
{
	TEXTURE_TYPE type;
	int use;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
	float Radius;
	float x, y;
};

/*
*  頂点データの構造体
*/
struct TLVERTX
{
	float x, y, z;	// 位置情報
	float rhw;		// 頂点変換値
	D3DCOLOR color;	// 頂点カラー
	float tu, tv;	// テクスチャ座標
};

extern TEXTURE flag[4];							// フラグ
extern TEXTURE mushroom[36];					// きのこ
extern TEXTURE goldapple[2];					// 金りんご
extern TEXTURE surprised[MAX_SURPRISED];		// ビックリマーク
extern TEXTURE question[MAX_QUESTION];			// はてなマーク

/*
 * テクスチャ読み込み
 */
void ReadTexture();

/*
 * テクスチャ初期化
 */
void ResetTexture();
/*
*  @brief フラグ描画
*  @param num プレイヤー識別番号
*/
void DropFlag(int num);

/*
 * フラグの描画
 */
void DrawFlag();

/*
 * マークの描画
 */
void DrawMark();
/*
*  @brief ポイント描画
*  @param x 座標
*  @param y 座標
*  @param point 試合ポイント
*/
void DrawEquipmentPoint(float x, float y, int point);
/*
*  @brief 時間描画
*  @param x 座標
*  @param y 座標
*  @param time 試合ポイント
*  @param zero 分と秒の区別
*/
void DrawEquipmentTime(float x, float y, int time, int zero);

/*
 * UI描画
 */
void DrawUI();
/*
*  @brief 試合のポイント描画
*  @param num プレイヤー識別番号
*  @param point 試合のポイント
*  @param mode ゲームモード
*/
void DrawPoint(int num, int point, int mode);
/*
*  @brief ヒットポイントの描画
*  @param num プレイヤー識別番号
*  @param hp ヒットポイント
*/
void DrawHitPoint(int num, int hp);
/*
*  @brief 試合時間の描画
*  @param minute 分
*  @param second 秒
*/
void DrawTime(int minute, int second);

/*
 * アイテム描画
 */
void DrawItem();

/*
 * アウトゲームの描画
 */
void DrawOutGame(float x, float y, int drawtype);

/*
 * 操作説明描画
 */
void DrawOperation(int drawtype);
