#pragma once
/*
 * @file FbxMesh.cpp
 * @brief FBX����
 * @author ��J���j
 * @date 2020 / 02 / 26
 */

#include <d3d9.h>
#include <d3dx9.h>
#include <map>

#include <fbxsdk.h>

/*------------------------------------------------
*  �\���̒�`
------------------------------------------------*/
class FbxMeshKM
{
protected:
	//	�Œ�V�F�[�_�[�p�ގ�
	D3DMATERIAL9 material;

	//	���_�\���́i�V�F�[�_�[�ƈ�v�j
	struct PolygonVertex {
		float x, y, z;		// ���W
		float nx, ny, nz;	// �@��
		DWORD color;		// ���_�J���[
		float tu, tv;		// UV
	};

	int NumMesh;
	int NumVertices;	//�S���_��
	int NumFaces;		//�S�|���S����
	PolygonVertex* Vertices;	//���_
	PolygonVertex* VerticesSrc; //���_���f�[�^
	DWORD* Indices;		//�O�p�`�i���_���ѕ��j

	char FBXDir[128];
	int* MeshMaterial;
	int* MaterialFaces;
	IDirect3DTexture9** Textures;
	//IDirect3DTexture9** NTextures;

	//	�{�[���֘A
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

	//	�E�F�C�g�֘A
	struct WEIGHT {
		int count;
		int bone[4];
		float weight[4];
	};
	WEIGHT* Weights;

	int StartFrame;
	void Skinning();	// �{�[���ɂ��ό`

	static const int MOTION_MAX = 256;
	static const int BONE_MAX = 256;

	//	�A�j���[�V����
	struct Motion {
		int NumFrame;	// �t���[����	
		//D3DXMATRIX key[BONE_MAX][120];	// �L�[�t���[��
		D3DXMATRIX* key[BONE_MAX];	// �L�[�t���[��
	};
	// int MotionNo;

	int NumMotion;		// ���[�V������
	std::map<std::string, Motion> motion;	// ���[�V�����f�[�^
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

	void Render();	//	�`��

	void Play(std::string name) {
		MotionName = name;
		Frame = 0.0f;
	}
	void Animate(float sec);	// ���[�V�����Đ�

	void Create(const char* filename);
	void AddMotion(std::string name, const char* filename);

	//	pos����vec�Ƀ��C�𔭎� ��_=out �ʖ@��=normal
	//	������Ȃ����-1��������
	int Raycast(const D3DXVECTOR3& pos, const D3DXVECTOR3& vec, float Dist, D3DXVECTOR3& out, D3DXVECTOR3& normal);
	int Raycast2(const D3DXVECTOR3& pos, const D3DXVECTOR3& vec, float Dist, D3DXVECTOR3& out, D3DXVECTOR3& normal);

	//	���[�V�������
	float Frame;		// ���݂̃t���[��
	std::string MotionName;		// ���݂̃��[�V����

	// �L�������
	int padnumber;		// �p�b�h�U�蕪��
	int use;			// �g�p�L��
	float Radius;		// ���a
	int HitPoint;		// �̗�
	int CharState;		// �L�����̃��[�V�����Ǘ�
	int RespawnTime;	// ���X�|�[������܂ł̎���
	int DamageTime;		// ���G����
	int motionTime;		// ���[�V��������
	D3DXVECTOR3 OldPos;	// 1�t���[���O�̃v���C���[�|�W�V����
	int direction[4];	// �������
	int AttackNum;	// �U���ł����

	//	�p�����
	D3DXMATRIX transform;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
	//	�{�[���s��擾
	D3DXMATRIX GetBoneMatrix(int bone) { return Bone[bone].transform; }

};
