/* 
 * @file  vector.cpp
 * @brief 2D�x�N�g���̉��Z
 *
 * @date 2017-07-04
 * @version 4.0
 *
 * Copyright(C) Amusement Media Academy All rights Resved.
 */

#include "vector.h"

// �x�N�g���̐����ݒ�
Vector2* SetVector(Vector2* out, double x, double y) {
  out->x = x;
  out->y = y;
  return out;
}

// �x�N�g���̒萔�{
Vector2* MulVector(Vector2* out, const Vector2* v, double t) {
  out->x = v->x * t;
  out->y = v->y * t;
  return out;
}

// �x�N�g���̉��@
Vector2* AddVector(Vector2* out, const Vector2* v1, const Vector2* v2) {
  out->x = v1->x + v2->x;
  out->y = v1->y + v2->y;
  return out;
}

// �x�N�g���̌��@
Vector2* SubVector(Vector2* out, const Vector2* v1, const Vector2* v2) {
  out->x = v1->x - v2->x;
  out->y = v1->y - v2->y;
  return out;
}

// �x�N�g���̉�]
Vector2* RotVector(Vector2* out, const Vector2* v, double angle) {
  out->x = v->x * cos(angle) - v->y * sin(angle);
  out->y = v->x * sin(angle) + v->y * cos(angle);
  return out;
}

// �x�N�g���̑傫��
double GetMagnitude(const Vector2* v) {
  // �x�N�g���̃m����(�����E�傫��)�����߂�
  double norm = v->x * v->x + v->y * v->y;
  norm = sqrt(norm);
  return norm;
}

// �x�N�g���̐��K��
Vector2* Normalize(Vector2* out, const Vector2* v) {
  // �x�N�g���̃m����(�����E�傫��)�����߂�
  double norm = v->x * v->x + v->y * v->y;
  // �덷�����Ȃ�[���Ƃ݂Ȃ��B
  if (fabs(norm) < DBL_EPSILON) {
    out->x = 0.0f;
    out->y = 0.0f;
  } else {
    // �ȉ�����Z�ŏ������邽��
    norm = 1.0 / sqrt(norm);
    // ���K������F�傫�����P�ɂ���
    out->x = v->x * norm;
    out->y = v->y * norm;
  }
  return out;
}

// �x�N�g���̓���
// v1�v2 = |v1||v2|cos�� = v1x * v2x + v1y * v2y
double DotProduct(const Vector2* v1, const Vector2* v2) {
  return v1->x * v2->x + v1->y * v2->y;
}

// �x�N�g���̊O��
// v1�~v2 = |v1||v2|sin�� = v1x * v2y - v1y * v2x
double CrossProduct(const Vector2* v1, const Vector2* v2) {
  return v1->x * v2->y - v1->y * v2->x;
}

// ���W�A������x�N�g���𓾂�
Vector2* RadianToVector(Vector2* out, double radian) {
  out->x = sin(radian);
  out->y = -cos(radian);
  return out;
}

// �x�N�g�����烉�W�A���𓾂�
double VectorToRadian(Vector2* v) {
  return atan2(v->y, v->x) + M_PI_2;  // AMGame���C�u����������+90�x
}
