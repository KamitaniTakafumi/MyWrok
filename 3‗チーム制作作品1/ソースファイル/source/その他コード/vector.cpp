/* 
 * @file  vector.cpp
 * @brief 2Dベクトルの演算
 *
 * @date 2017-07-04
 * @version 4.0
 *
 * Copyright(C) Amusement Media Academy All rights Resved.
 */

#include "vector.h"

// ベクトルの成分設定
Vector2* SetVector(Vector2* out, double x, double y) {
  out->x = x;
  out->y = y;
  return out;
}

// ベクトルの定数倍
Vector2* MulVector(Vector2* out, const Vector2* v, double t) {
  out->x = v->x * t;
  out->y = v->y * t;
  return out;
}

// ベクトルの加法
Vector2* AddVector(Vector2* out, const Vector2* v1, const Vector2* v2) {
  out->x = v1->x + v2->x;
  out->y = v1->y + v2->y;
  return out;
}

// ベクトルの減法
Vector2* SubVector(Vector2* out, const Vector2* v1, const Vector2* v2) {
  out->x = v1->x - v2->x;
  out->y = v1->y - v2->y;
  return out;
}

// ベクトルの回転
Vector2* RotVector(Vector2* out, const Vector2* v, double angle) {
  out->x = v->x * cos(angle) - v->y * sin(angle);
  out->y = v->x * sin(angle) + v->y * cos(angle);
  return out;
}

// ベクトルの大きさ
double GetMagnitude(const Vector2* v) {
  // ベクトルのノルム(長さ・大きさ)を求める
  double norm = v->x * v->x + v->y * v->y;
  norm = sqrt(norm);
  return norm;
}

// ベクトルの正規化
Vector2* Normalize(Vector2* out, const Vector2* v) {
  // ベクトルのノルム(長さ・大きさ)を求める
  double norm = v->x * v->x + v->y * v->y;
  // 誤差未満ならゼロとみなす。
  if (fabs(norm) < DBL_EPSILON) {
    out->x = 0.0f;
    out->y = 0.0f;
  } else {
    // 以下を乗算で処理するため
    norm = 1.0 / sqrt(norm);
    // 正規化する：大きさを１にする
    out->x = v->x * norm;
    out->y = v->y * norm;
  }
  return out;
}

// ベクトルの内積
// v1･v2 = |v1||v2|cosθ = v1x * v2x + v1y * v2y
double DotProduct(const Vector2* v1, const Vector2* v2) {
  return v1->x * v2->x + v1->y * v2->y;
}

// ベクトルの外積
// v1×v2 = |v1||v2|sinθ = v1x * v2y - v1y * v2x
double CrossProduct(const Vector2* v1, const Vector2* v2) {
  return v1->x * v2->y - v1->y * v2->x;
}

// ラジアンからベクトルを得る
Vector2* RadianToVector(Vector2* out, double radian) {
  out->x = sin(radian);
  out->y = -cos(radian);
  return out;
}

// ベクトルからラジアンを得る
double VectorToRadian(Vector2* v) {
  return atan2(v->y, v->x) + M_PI_2;  // AMGameライブラリ向けに+90度
}
