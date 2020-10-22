#pragma once
/*
 * @file CollsionDetection.cpp
 * @brief 当たり判定処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "Texture.h"
#include "object.h"

/*
 * キャラ同士の衝突検出
 * @param pThingA プレイヤー
 * @param pThingB オブジェクト
 */
BOOL Collision(FbxMeshKM* pThingA, OBJECT pThingB);
/*
 * キャラとテクスチャの衝突検出
 * @param pThingA プレイヤー１
 * @param pThingB テクスチャ
 */
BOOL Collision2(FbxMeshKM* pThingA, TEXTURE* pThingB);
/*
 * キャラ同士の衝突検出
 * @param pThingA プレイヤー１
 * @param pThingB プレイヤー２
 */
BOOL Collision4(FbxMeshKM* pThingA, FbxMeshKM* pThingB);
/*
 * ギミックとの当たり判定
 * @param i プレイヤーの識別番号
 * @param type プレイヤーの状態
 */
bool PlayerGimmickHit(int i, int type);
/*
 * プレイヤーとFBXとの当たり判定
 * @param num プレイヤーの識別番号
 * @param *point ポイントのポインタ
 * @param g_key プレイヤーのボタン判定
 * @param g_trg プレイヤーのボタン判定
 */
int CollsionDetection(int num, int* point, int g_key, int g_trg);
/*
 * 武器持ちプレイヤーとFBXとの当たり判定
 * @param num プレイヤーの識別番号
 * @param *point ポイントのポインタ
 * @param g_key プレイヤーのボタン判定
 * @param g_trg プレイヤーのボタン判定
 */
int CollsionDetectionWeapon(int num, int* point, int g_key, int g_trg);
