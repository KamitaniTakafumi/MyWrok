#pragma once
/*
 * @file Camera.cpp
 * @brief カメラ処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"

/*
*	カメラ構造体
*/
struct CAMERA
{
	D3DXVECTOR3 position;					
	D3DXVECTOR3 target;						 
	D3DXMATRIX matView;						 
	D3DXVECTOR3 pos;						 
	D3DXVECTOR3 angle;						 
	float cvpos_x, cvpos_y, cvpos_z;
	float cvangle_x, cvangle_y, cvangle_z;	 
};

extern struct CAMERA cv;

/*
 * カメラ初期化
 */
void InitCamera();

void SetPosition(CAMERA *camera, D3DXVECTOR3 val);
void SetCameraTarget(CAMERA *camera, D3DXVECTOR3 val);
void SetRotation(CAMERA *camera, D3DXVECTOR3 val);

D3DXVECTOR3 GetForward(CAMERA *camera);
D3DXVECTOR3 GetRight(CAMERA *camera);

/*
 * カメラ更新
 */
void UpdateCamera(CAMERA *camera);
