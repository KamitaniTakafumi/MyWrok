#pragma once
/* 
 * @file  vector.h
 * @brief 2Dベクトルの演算
 *
 * @date 2017-07-04
 * @version 4.0
 *
 * Copyright(C) Amusement Media Academy All rights Resved.
 */

#include <float.h>
#define _USE_MATH_DEFINES // math.hのM_PIを使うために必要
#include <math.h>

///< 2Dベクトル
typedef struct {
  double x;
  double y;
} Vector2, Point2;

/**
 *  ベクトルの成分設定
 * 
 *	@param *out ベクトル
 *	@param x x成分	
 *	@param y y成分	
 *	@retval out ベクトル
 */
Vector2* SetVector(Vector2* out, double x, double y);
/**
 *  ベクトルの定数倍
 * 
 *	@param *out ベクトル×定数
 *	@param *v ベクトル
 *	@param t 定数	
 *	@retval out ベクトル×定数
 */
Vector2* MulVector(Vector2* out, const Vector2* v1, double t);
/**
 *  ベクトルの加法
 * 
 *	@param *out ベクトル１＋ベクトル２
 *	@param *v1 ベクトル１
 *	@param *v2 ベクトル２
 *	@retval out ベクトル１＋ベクトル２
 */
Vector2* AddVector(Vector2* out, const Vector2* v1, const Vector2* v2);
/**
 *  ベクトルの減法
 * 
 *	@param *out ベクトル１‐ベクトル２
 *	@param *v1 ベクトル１
 *	@param *v2 ベクトル２
 *	@retval out ベクトル１‐ベクトル２
 */
Vector2* SubVector(Vector2* out, const Vector2* v1, const Vector2* v2);
/**
 *  ベクトルの回転
 * 
 *	@param *out 回転後のベクトル
 *	@param *v ベクトル
 *	@param angle 回転角度
 *	@retval out 回転後のベクトル
 */
Vector2* RotVector(Vector2* out, const Vector2* v, double angle);
/**
 *  ベクトルの大きさ
 * 
 *	2Dベクトルの大きさを計算する
 * 
 *	@param *v ベクトル	
 *	@retval norm ベクトルの大きさ
 */
double GetMagnitude(const Vector2* v);
/**
 *  ベクトルの正規化
 * 
 *	2Dベクトルを正規化したベクトルを計算する
 * 
 *	@param *out 正規化したベクトル	
 *	@param *v 正規化するベクトル	
 *	@retval out 正規化したベクトル
 */
Vector2* Normalize(Vector2* out, const Vector2* v);
/**	
 *  ベクトルの内積
 * 
 *	２つの2Dベクトルの内積を計算する
 * 
 *	@param *v1 ベクトル１	
 *	@param *v2 ベクトル２	
 *	@retval 内積：スカラ
 */
double DotProduct(const Vector2* v1, const Vector2* v2);
/**	
 *  ベクトルの外積
 * 
 *	２つの2Dベクトルの外積を計算する
 * 
 *	@param *v1 ベクトル１	
 *	@param *v2 ベクトル２	
 *	@retval 外積：スカラ
 */
double CrossProduct(const Vector2* v1, const Vector2* v2);
/**	
 *  ラジアンからベクトルを得る
 * 
 *	ラジアンから2Dベクトルを計算する
 * 
 *	@param *out ベクトル	
 *	@param *radian 角度	
 *	@retval ベクトル
 */
Vector2* RadianToVector(Vector2* out, double radian);
/**
 *  ベクトルからラジアンを得る
 *
 *	2Dベクトルからラジアン(AMGGame向けに+90度)を計算する
 *
 *	@param *v ベクトル
 *	@retval ラジアン
 */
double VectorToRadian(Vector2* v);
