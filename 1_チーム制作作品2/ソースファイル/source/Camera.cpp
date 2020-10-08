/*
 * @file Camera.cpp
 * @brief カメラ処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "Camera.h"

struct CAMERA cv;	// カメラ情報

/*
 * カメラ初期化
 */
void InitCamera()	//	カメラ初期化
{
	cv.cvpos_x = 0.0f;
	cv.cvpos_y = 1400.0f;
	cv.cvpos_z = 650.0f;
	cv.cvangle_x = 0.90f;
	cv.cvangle_y = 3.15f;
	cv.cvangle_z = 0.0f;
	cv.pos = D3DXVECTOR3(cv.cvpos_x, cv.cvpos_y, cv.cvpos_z);
	cv.angle = D3DXVECTOR3(cv.cvangle_x, cv.cvangle_y, cv.cvangle_z);
}

void SetPosition(CAMERA *camera, D3DXVECTOR3 val)
{
	camera->position = val;
}
void SetCameraTarget(CAMERA *camera, D3DXVECTOR3 val)
{
	camera->target = val;
}
void SetRotation(CAMERA *camera, D3DXVECTOR3 val)
{
	D3DXMATRIX m;
	D3DXMatrixRotationYawPitchRoll(&m, val.y, val.x, val.z);

	SetCameraTarget(camera, camera->position + D3DXVECTOR3(m._31, m._32, m._33));
}

D3DXVECTOR3 GetForward(CAMERA *camera)
{
	return D3DXVECTOR3(camera->matView._13, camera->matView._23, camera->matView._33);
}
D3DXVECTOR3 GetRight(CAMERA *camera)
{
	return D3DXVECTOR3(camera->matView._11, camera->matView._21, camera->matView._31);
}

/*
 * カメラ更新
 */
void UpdateCamera(CAMERA *camera)
{
	D3DXMatrixLookAtLH(&camera->matView, &camera->position, &camera->target, &D3DXVECTOR3(0, 1, 0));
	gDevice->SetTransform(D3DTS_VIEW, &camera->matView);
}
