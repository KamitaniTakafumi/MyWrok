#pragma once

// �萔�E�\���̒�`
struct MATERIAL
{
	int	use;
	int use_recipe;
	int	number;
	int	cg;
	int x, y;
	int	hit_x, hit_y, hit_w, hit_h;  //�����蔻��
	int enpoz_x, enpoz_y;
	int enemy_type;
};

struct SYSTEM {
	int use;
	int x, y;
	int w, h;
	int number;
	int systemtime;
	int drop_number;
	int count;
};

//
// �O���[�o���ϐ��錾
//
#define MATERIAL_NUMBER 30
#define MATERIAL_MAX 20

#define WINDOW_CHOGONAME_X 440   //����(������)��ʂ�x���W
#define WINDOW_CHOGONAME_Y 120   //����(������)��ʂ�y���W

#define WINDOW_CHOGO_X 80        //������ʂ�x���W
#define WINDOW_CHOGO_Y 160       //������ʂ�y���W

#define WINDOW_SOZAINAME_X 700   //����(�f��)��ʂ�x���W
#define WINDOW_SOZAINAME_Y 120   //����(�f��)��ʂ�y���W

#define WINDOW_SOZAI_X 700       //�f�މ�ʂ�x���W
#define WINDOW_SOZAI_Y 160       //�f�މ�ʂ�y���W

#define WINDOW_ITEMNAME_X 480
#define WINDOW_ITEMNAME_Y 120

#define WINDOW_ITEM_X 80
#define WINDOW_ITEM_Y 160

// �f�ޏ��
extern struct MATERIAL material[MATERIAL_NUMBER];
extern struct SYSTEM sy;

extern int cgtogenomi2;
extern int cgkaenseki2;
extern int cghyoreseki2;
extern int cgraidenseki2;
extern int cgyakusou2;
extern int cgmizu2;
extern int cgsurudoihahen2;
extern int cgchuwazai2;

extern int systemAlpha;
extern int material_max;

void LoadCgMaterial();

void InitMaterial();

void InitPoz();

void GetMaterial(int objectId, int materialId);

void DropMaterial();

void DropItem();

void DrawMaterial();