#pragma once
/*
 * @file FbxMesh.cpp
 * @brief FBX処理
 * @author 上谷恭史
 * @date 2020 / 02 / 26
 */

#include <d3d9.h>
#include <d3dx9.h>
#include <map>

#include <fbxsdk.h>

/*------------------------------------------------
*  構造体定義
------------------------------------------------*/
class FbxMeshKM
{
protected:
	//	固定シェーダー用材質
	D3DMATERIAL9 material;

	//	頂点構造体（シェーダーと一致）
	struct PolygonVertex {
		float x, y, z;		// 座標
		float nx, ny, nz;	// 法線
		DWORD color;		// 頂点カラー
		float tu, tv;		// UV
	};

	int NumMesh;
	int NumVertices;	//全頂点数
	int NumFaces;		//全ポリゴン数
	PolygonVertex* Vertices;	//頂点
	PolygonVertex* VerticesSrc; //頂点元データ
	DWORD* Indices;		//三角形（頂点結び方）

	char FBXDir[128];
	int* MeshMaterial;
	int* MaterialFaces;
	IDirect3DTexture9** Textures;
	//IDirect3DTexture9** NTextures;

	//	ボーン関連
	struct BONE {
		char	Name[128];
		D3DXMATRIX	OffsetMatrix;
		D3DXMATRIX	transform;
	};
	int NumBone;
	BONE Bone[256];

	int FindBone(const char* name);
	void LoadBone(FbxMesh* mesh);
	void LoadMeshAnim(FbxMesh* mesh);

	//	ウェイト関連
	struct WEIGHT {
		int count;
		int bone[4];
		float weight[4];
	};
	WEIGHT* Weights;

	int StartFrame;
	void Skinning();	// ボーンによる変形

	static const int MOTION_MAX = 256;
	static const int BONE_MAX = 256;

	//	アニメーション
	struct Motion {
		int NumFrame;	// フレーム数	
		//D3DXMATRIX key[BONE_MAX][120];	// キーフレーム
		D3DXMATRIX* key[BONE_MAX];	// キーフレーム
	};
	// int MotionNo;

	int NumMotion;		// モーション数
	std::map<std::string, Motion> motion;	// モーションデータ
	void LoadKeyFrames(std::string name, int bone, FbxNode* bone_node);

	void Load(const char* filename);
	void LoadMaterial(int index, FbxSurfaceMaterial* material);

	void LoadPosition(FbxMesh* mesh);
	void LoadNormal(FbxMesh* mesh);
	void LoadUV(FbxMesh* mesh);
	void LoadVertexColor(FbxMesh* mesh);

	void OptimizeVertices();

public:
	FbxMeshKM();
	virtual ~FbxMeshKM();

	void Update();

	void Render();	//	描画

	void Play(std::string name) {
		MotionName = name;
		Frame = 0.0f;
	}
	void Animate(float sec);	// モーション再生

	void Create(const char* filename);
	void AddMotion(std::string name, const char* filename);

	//	posからvecにレイを発射 交点=out 面法線=normal
	//	当たらなければ-1がかえる
	int Raycast(const D3DXVECTOR3& pos, const D3DXVECTOR3& vec, float Dist, D3DXVECTOR3& out, D3DXVECTOR3& normal);
	int Raycast2(const D3DXVECTOR3& pos, const D3DXVECTOR3& vec, float Dist, D3DXVECTOR3& out, D3DXVECTOR3& normal);

	//	モーション情報
	float Frame;		// 現在のフレーム
	std::string MotionName;		// 現在のモーション

	// キャラ情報
	int padnumber;		// パッド振り分け
	int use;			// 使用有無
	float Radius;		// 半径
	int HitPoint;		// 体力
	int CharState;		// キャラのモーション管理
	int RespawnTime;	// リスポーンするまでの時間
	int DamageTime;		// 無敵時間
	int motionTime;		// モーション時間
	D3DXVECTOR3 OldPos;	// 1フレーム前のプレイヤーポジション
	int direction[4];	// 向き情報
	int AttackNum;	// 攻撃できる回数

	//	姿勢情報
	D3DXMATRIX transform;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
	//	ボーン行列取得
	D3DXMATRIX GetBoneMatrix(int bone) { return Bone[bone].transform; }

};
