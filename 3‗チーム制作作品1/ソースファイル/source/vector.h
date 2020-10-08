#pragma once
/* 
 * @file  vector.h
 * @brief 2D�x�N�g���̉��Z
 *
 * @date 2017-07-04
 * @version 4.0
 *
 * Copyright(C) Amusement Media Academy All rights Resved.
 */

#include <float.h>
#define _USE_MATH_DEFINES // math.h��M_PI���g�����߂ɕK�v
#include <math.h>

///< 2D�x�N�g��
typedef struct {
  double x;
  double y;
} Vector2, Point2;

/**
 *  �x�N�g���̐����ݒ�
 * 
 *	@param *out �x�N�g��
 *	@param x x����	
 *	@param y y����	
 *	@retval out �x�N�g��
 */
Vector2* SetVector(Vector2* out, double x, double y);
/**
 *  �x�N�g���̒萔�{
 * 
 *	@param *out �x�N�g���~�萔
 *	@param *v �x�N�g��
 *	@param t �萔	
 *	@retval out �x�N�g���~�萔
 */
Vector2* MulVector(Vector2* out, const Vector2* v1, double t);
/**
 *  �x�N�g���̉��@
 * 
 *	@param *out �x�N�g���P�{�x�N�g���Q
 *	@param *v1 �x�N�g���P
 *	@param *v2 �x�N�g���Q
 *	@retval out �x�N�g���P�{�x�N�g���Q
 */
Vector2* AddVector(Vector2* out, const Vector2* v1, const Vector2* v2);
/**
 *  �x�N�g���̌��@
 * 
 *	@param *out �x�N�g���P�]�x�N�g���Q
 *	@param *v1 �x�N�g���P
 *	@param *v2 �x�N�g���Q
 *	@retval out �x�N�g���P�]�x�N�g���Q
 */
Vector2* SubVector(Vector2* out, const Vector2* v1, const Vector2* v2);
/**
 *  �x�N�g���̉�]
 * 
 *	@param *out ��]��̃x�N�g��
 *	@param *v �x�N�g��
 *	@param angle ��]�p�x
 *	@retval out ��]��̃x�N�g��
 */
Vector2* RotVector(Vector2* out, const Vector2* v, double angle);
/**
 *  �x�N�g���̑傫��
 * 
 *	2D�x�N�g���̑傫�����v�Z����
 * 
 *	@param *v �x�N�g��	
 *	@retval norm �x�N�g���̑傫��
 */
double GetMagnitude(const Vector2* v);
/**
 *  �x�N�g���̐��K��
 * 
 *	2D�x�N�g���𐳋K�������x�N�g�����v�Z����
 * 
 *	@param *out ���K�������x�N�g��	
 *	@param *v ���K������x�N�g��	
 *	@retval out ���K�������x�N�g��
 */
Vector2* Normalize(Vector2* out, const Vector2* v);
/**	
 *  �x�N�g���̓���
 * 
 *	�Q��2D�x�N�g���̓��ς��v�Z����
 * 
 *	@param *v1 �x�N�g���P	
 *	@param *v2 �x�N�g���Q	
 *	@retval ���ρF�X�J��
 */
double DotProduct(const Vector2* v1, const Vector2* v2);
/**	
 *  �x�N�g���̊O��
 * 
 *	�Q��2D�x�N�g���̊O�ς��v�Z����
 * 
 *	@param *v1 �x�N�g���P	
 *	@param *v2 �x�N�g���Q	
 *	@retval �O�ρF�X�J��
 */
double CrossProduct(const Vector2* v1, const Vector2* v2);
/**	
 *  ���W�A������x�N�g���𓾂�
 * 
 *	���W�A������2D�x�N�g�����v�Z����
 * 
 *	@param *out �x�N�g��	
 *	@param *radian �p�x	
 *	@retval �x�N�g��
 */
Vector2* RadianToVector(Vector2* out, double radian);
/**
 *  �x�N�g�����烉�W�A���𓾂�
 *
 *	2D�x�N�g�����烉�W�A��(AMGGame������+90�x)���v�Z����
 *
 *	@param *v �x�N�g��
 *	@retval ���W�A��
 */
double VectorToRadian(Vector2* v);
