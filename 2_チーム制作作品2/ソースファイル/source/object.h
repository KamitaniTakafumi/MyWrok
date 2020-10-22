#pragma once
/*
 * @file object.cpp
 * @brief オブジェクト処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#define MAX_OBJECT 16		// オブジェクト最大数
#define MAX_GIMMICK 13		// ギミック最大数

struct GIMMICK// ギミック構造体
{
	D3DXVECTOR3 Position;
	float Radius;
};

struct OBJECT// オブジェクト構造体
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	int use;
	float Radius;
	D3DXVECTOR3 Scale;
	int GetLimitCount;	// ゲットできる回数
	int obj_name;
	int ReGetTime;		// ゲットできるまでの時間
};

enum OBUJECT_NAME	// オブジェクト名
{
	OBJ_TREE,
	OBJ_WOOD,
	OBJ_ROCK,
	OBJ_BOX,
};

// オブジェクト情報
extern FbxMeshKM* Object[4];
extern OBJECT Obj[MAX_OBJECT];
// ギミック情報
extern GIMMICK Gim[MAX_GIMMICK];

/*
 * オブジェクト初期化
 */
void InitObject();
/*
 * オブジェクトリリース
 */
void ReleaseObject();
/*
 * オブジェクトリセット
 */
void ResetObject();
/*
 * オブジェクト描画
 */
void DrawObject();
