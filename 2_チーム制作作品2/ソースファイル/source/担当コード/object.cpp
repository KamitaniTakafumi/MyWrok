/*
 * @file object.cpp
 * @brief オブジェクト処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include "library.h"
#include "game.h"
#include "SceneMain.h"
#include "object.h"

FbxMeshKM* Object[4];// 読み込むオブジェクト
OBJECT Obj[MAX_OBJECT];// オブジェクト情報
GIMMICK Gim[MAX_GIMMICK];// ギミック情報

/*
 * オブジェクト初期化
 */
void InitObject()
{
	Object[OBJ_TREE] = new FbxMeshKM();
	Object[OBJ_TREE]->Create("Assets/object/kareki/kareki.fbx");
	Object[OBJ_TREE]->position = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_TREE]->rotation = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_TREE]->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Object[OBJ_TREE]->Update();

	Object[OBJ_WOOD] = new FbxMeshKM();
	Object[OBJ_WOOD]->Create("Assets/object/touboku/touboku.fbx");
	Object[OBJ_WOOD]->position = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_WOOD]->rotation = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_WOOD]->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Object[OBJ_WOOD]->Update();

	Object[OBJ_ROCK] = new FbxMeshKM();
	Object[OBJ_ROCK]->Create("Assets/object/iwa/iwa2.fbx");
	Object[OBJ_ROCK]->position = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_ROCK]->rotation = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_ROCK]->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Object[OBJ_ROCK]->Update();

	Object[OBJ_BOX] = new FbxMeshKM();
	Object[OBJ_BOX]->Create("Assets/object/kibako/kibako.fbx");
	Object[OBJ_BOX]->position = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_BOX]->rotation = D3DXVECTOR3(0, 0, 0);
	Object[OBJ_BOX]->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Object[OBJ_BOX]->Update();

	// 枯れ木
	Obj[0].Position = D3DXVECTOR3(400, 0, -300);
	Obj[0].obj_name = OBJ_TREE;
	Obj[0].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[0].use = 1;						// 0:未使用, 1:使用中
	Obj[0].Radius = 50.0f;				// 半径
	Obj[0].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[0].GetLimitCount = 1;			// ゲットできる上限

	Obj[1].Position = D3DXVECTOR3(0, 290, -1680);
	Obj[1].obj_name = OBJ_TREE;
	Obj[1].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[1].use = 1;						// 0:未使用, 1:使用中
	Obj[1].Radius = 50.0f;				// 半径
	Obj[1].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[1].GetLimitCount = 1;			// ゲットできる上限

	// 倒木
	Obj[2].Position = D3DXVECTOR3(-100, 0, -300);
	Obj[2].obj_name = OBJ_WOOD;
	Obj[2].Rotation = D3DXVECTOR3(0, -10, 0);
	Obj[2].use = 1;						// 0:未使用, 1:使用中
	Obj[2].Radius = 50.0f;				// 半径
	Obj[2].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[2].GetLimitCount = 3;			// ゲットできる上限

	Obj[3].Position = D3DXVECTOR3(720, 95, -830);
	Obj[3].obj_name = OBJ_WOOD;
	Obj[3].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[3].use = 1;						// 0:未使用, 1:使用中
	Obj[3].Radius = 50.0f;				// 半径
	Obj[3].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[3].GetLimitCount = 3;			// ゲットできる上限

	Obj[4].Position = D3DXVECTOR3(-720, 95, -810);
	Obj[4].obj_name = OBJ_WOOD;
	Obj[4].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[4].use = 1;						// 0:未使用, 1:使用中
	Obj[4].Radius = 50.0f;				// 半径
	Obj[4].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[4].GetLimitCount = 3;			// ゲットできる上限

	Obj[5].Position = D3DXVECTOR3(750, 190, -1000);
	Obj[5].obj_name = OBJ_WOOD;
	Obj[5].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[5].use = 1;						// 0:未使用, 1:使用中
	Obj[5].Radius = 50.0f;				// 半径
	Obj[5].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[5].GetLimitCount = 3;			// ゲットできる上限

	Obj[6].Position = D3DXVECTOR3(450, 290, -1650);
	Obj[6].obj_name = OBJ_WOOD;
	Obj[6].Rotation = D3DXVECTOR3(0, -10, 0);
	Obj[6].use = 1;						// 0:未使用, 1:使用中
	Obj[6].Radius = 50.0f;				// 半径
	Obj[6].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[6].GetLimitCount = 3;			// ゲットできる上限

	Obj[7].Position = D3DXVECTOR3(-860, 290, -1480);
	Obj[7].obj_name = OBJ_WOOD;
	Obj[7].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[7].use = 1;						// 0:未使用, 1:使用中
	Obj[7].Radius = 50.0f;				// 半径
	Obj[7].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[7].GetLimitCount = 3;			// ゲットできる上限

	// 岩
	Obj[8].Position = D3DXVECTOR3(-860, 0, -420);
	Obj[8].obj_name = OBJ_ROCK;
	Obj[8].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[8].use = 1;						// 0:未使用, 1:使用中
	Obj[8].Radius = 50.0f;				// 半径
	Obj[8].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[8].GetLimitCount = 3;			// ゲットできる上限

	Obj[9].Position = D3DXVECTOR3(1050, 95, -830);
	Obj[9].obj_name = OBJ_ROCK;
	Obj[9].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[9].use = 1;						// 0:未使用, 1:使用中
	Obj[9].Radius = 50.0f;				// 半径
	Obj[9].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[9].GetLimitCount = 3;			// ゲットできる上限

	Obj[10].Position = D3DXVECTOR3(-1050, 95, -760);
	Obj[10].obj_name = OBJ_ROCK;
	Obj[10].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[10].use = 1;						// 0:未使用, 1:使用中
	Obj[10].Radius = 50.0f;				// 半径
	Obj[10].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[10].GetLimitCount = 3;			// ゲットできる上限

	Obj[11].Position = D3DXVECTOR3(-160, 190, -1250);
	Obj[11].obj_name = OBJ_ROCK;
	Obj[11].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[11].use = 1;						// 0:未使用, 1:使用中
	Obj[11].Radius = 50.0f;				// 半径
	Obj[11].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[11].GetLimitCount = 3;			// ゲットできる上限

	Obj[12].Position = D3DXVECTOR3(900, 290, -1350);
	Obj[12].obj_name = OBJ_ROCK;
	Obj[12].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[12].use = 1;						// 0:未使用, 1:使用中
	Obj[12].Radius = 50.0f;				// 半径
	Obj[12].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[12].GetLimitCount = 3;			// ゲットできる上限

	Obj[13].Position = D3DXVECTOR3(-570, 290, -1320);
	Obj[13].obj_name = OBJ_ROCK;
	Obj[13].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[13].use = 1;						// 0:未使用, 1:使用中
	Obj[13].Radius = 50.0f;				// 半径
	Obj[13].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[13].GetLimitCount = 3;			// ゲットできる上限

	// 木箱
	Obj[14].Position = D3DXVECTOR3(-220, 95, -850);
	Obj[14].obj_name = OBJ_BOX;
	Obj[14].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[14].use = 1;						// 0:未使用, 1:使用中
	Obj[14].Radius = 70.0f;				// 半径
	Obj[14].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[14].GetLimitCount = 1;			// ゲットできる上限

	Obj[15].Position = D3DXVECTOR3(400, 190, -1100);
	Obj[15].obj_name = OBJ_BOX;
	Obj[15].Rotation = D3DXVECTOR3(0, 0, 0);
	Obj[15].use = 1;						// 0:未使用, 1:使用中
	Obj[15].Radius = 70.0f;				// 半径
	Obj[15].Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Obj[15].GetLimitCount = 1;			// ゲットできる上限

	// ギミック
	Gim[0].Position = D3DXVECTOR3(145, 0, -160);
	Gim[0].Radius = 60.0f;

	Gim[1].Position = D3DXVECTOR3(-635, 0, -435);
	Gim[1].Radius = 60.0f;
	Gim[2].Position = D3DXVECTOR3(-635, 100, -555);
	Gim[2].Radius = 60.0f;

	Gim[3].Position = D3DXVECTOR3(640, 0, -340);
	Gim[3].Radius = 60.0f;
	Gim[4].Position = D3DXVECTOR3(640, 100, -450);
	Gim[4].Radius = 60.0f;

	Gim[5].Position = D3DXVECTOR3(290, 100, -680);
	Gim[5].Radius = 20.0f;
	Gim[6].Position = D3DXVECTOR3(190, 100, -680);
	Gim[6].Radius = 20.0f;
	Gim[7].Position = D3DXVECTOR3(90, 100, -680);
	Gim[7].Radius = 20.0f;

	Gim[8].Position = D3DXVECTOR3(290, 190, -1060);
	Gim[8].Radius = 20.0f;
	Gim[9].Position = D3DXVECTOR3(190, 190, -1060);
	Gim[9].Radius = 20.0f;

	Gim[10].Position = D3DXVECTOR3(245, 290, -1415);
	Gim[10].Radius = 60.0f;

	Gim[11].Position = D3DXVECTOR3(-545, 290, -1710);
	Gim[11].Radius = 60.0f;
	Gim[12].Position = D3DXVECTOR3(-650, 290, -1710);
	Gim[12].Radius = 60.0f;

}

/*
 * オブジェクトリリース
 */
void ReleaseObject()
{
	for (int i = 0; i < 4; i++)
	{
		delete Object[i];
	}
}

/*
 * オブジェクトリセット
 */
void ResetObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		Obj[i].use = 1;
	}
}

/*
 * オブジェクト描画
 */
void DrawObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (Obj[i].obj_name == OBJ_TREE)
		{
			Object[OBJ_TREE]->position = Obj[i].Position;
			Object[OBJ_TREE]->rotation = Obj[i].Rotation;
			Object[OBJ_TREE]->scale = Obj[i].Scale;
			Object[OBJ_TREE]->Update();
			Object[OBJ_TREE]->Render();
		}
		else if (Obj[i].obj_name == OBJ_WOOD)
		{
			Object[OBJ_WOOD]->position = Obj[i].Position;
			Object[OBJ_WOOD]->rotation = Obj[i].Rotation;
			Object[OBJ_WOOD]->scale = Obj[i].Scale;
			Object[OBJ_WOOD]->Update();
			Object[OBJ_WOOD]->Render();
		}
		else if (Obj[i].obj_name == OBJ_ROCK)
		{
			Object[OBJ_ROCK]->position = Obj[i].Position;
			Object[OBJ_ROCK]->rotation = Obj[i].Rotation;
			Object[OBJ_ROCK]->scale = Obj[i].Scale;
			Object[OBJ_ROCK]->Update();
			Object[OBJ_ROCK]->Render();
		}
		else if (Obj[i].obj_name == OBJ_BOX)
		{
			Object[OBJ_BOX]->position = Obj[i].Position;
			Object[OBJ_BOX]->rotation = Obj[i].Rotation;
			Object[OBJ_BOX]->scale = Obj[i].Scale;
			Object[OBJ_BOX]->Update();
			Object[OBJ_BOX]->Render();
		}
	}
}
