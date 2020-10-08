#pragma once
/*
 * @file Camera.cpp
 * @brief �J��������
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include "library.h"

/*
*	�J�����\����
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
 * �J����������
 */
void InitCamera();

void SetPosition(CAMERA *camera, D3DXVECTOR3 val);
void SetCameraTarget(CAMERA *camera, D3DXVECTOR3 val);
void SetRotation(CAMERA *camera, D3DXVECTOR3 val);

D3DXVECTOR3 GetForward(CAMERA *camera);
D3DXVECTOR3 GetRight(CAMERA *camera);

/*
 * �J�����X�V
 */
void UpdateCamera(CAMERA *camera);
