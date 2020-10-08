#pragma once
//
// ’è”E\‘¢‘Ì’è‹`
//
struct PREPARATION {
	int x, y;
	int	w, h;
	int	hit_x, hit_y, hit_w, hit_h;
	int	hit_range_x, hit_range_y, hit_range_w, hit_range_h;  //“–‚½‚è”»’è(“G‚Ì“ü‚ê‚È‚¢”ÍˆÍ)
	int use;
};

#define PREPARATION_MAX 5

struct SELECT {
	int x, y;
	int w, h;
	int state;
	float xspan;
	int page;
	int equipment_x, equipment_y;
	int page_right_x, page_right_y;
	int page_left_x, page_left_y;
	int page_number_x, page_number_y;
	int page_number_x2, page_number_y2;
};

extern struct PREPARATION pre[PREPARATION_MAX];

extern struct SELECT sel;

extern int cgPageSelect_right;	// 
extern int cgPageSelect_left;	// 
extern int cgwindow_log;		// 

extern int firstcreate;			// 

void LoadCgPreparation();

void InitPreparation();

void InitSelect();

void SelectItem();

void ItemCreate();

void EquipmentItem();

void DrawSelect();

void DrawPreparation();
