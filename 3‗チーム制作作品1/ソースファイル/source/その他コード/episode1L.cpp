/*------------------------------------------------
*  @file episode1L.cpp
*  @brief ���C���Q�[������
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �w�b�_�[�t�@�C���̃C���N���[�h
------------------------------------------------*/
#include	<Windows.h>
#include	"amgame.h"
#include	"AmHelper.h"

#include	"game.h"
#include	"alice.h"
#include	"aliceattack.h"
#include	"global.h"
#include	"title.h"
#include	"mapdata_1.h"
#include	"Object.h"
#include	"camera.h"
#include	"Object.h"
#include	"enemy.h"
#include	"preparation.h"
#include	"Item.h"
#include	"Material.h"
#include	"recipe.h"
#include	"HitJudgment.h"
#include	"UI.h"
#include	"enemyattack.h"
#include	"changeroom.h"
#include	"game_effect.h"
#include	"episode1S3.h"

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

// �摜�f�[�^

int cgOperation;		// �������

int OperationFlag;		// �t���O
int fadein, fadeout;	// �t�F�[�h�C���A�t�F�[�h�A�E�g

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
// �摜�ǂݍ��݁A������
int IntoEpisode1L() {
	// �X�e�[�W�̍ŏ�������������̏�����
	if (stateStage == STATE_EP1STAGE) {
		gFrameWait = 60;
		OperationFlag = 1;
		fadein = 255;
		fadeout = 0;
		cgOperation = LoadTexture("res/operation.png");
	}

	LoadAttackEff();		// �U���G�t�F�N�g
	LoadCgMapChip_1();		// �}�b�v�`�b�v
	LoadCgItem();           // �A�C�e��
	LoadCgAlice();          // �A���X
	LoadCgHealth();			// �̗�
	LoadCgEnemy();			// �G
	LoadCgEnemyAttack();	// �G�U���G�t�F�N�g
	LoadCgPreparation();    // ������
	LoadCgMaterial();       // �f��
	LoadCgObject();         // �I�u�W�F�N�g
	LoadCgRecipe();         // ���V�s
	LoadCgUi();				// UI
	LoadCgEffect();			// �G�t�F�N�g
	LoadCgFukidashi();		// �����o��(�}�[�W�}�^���S)

	initblackin_ep1();		// �u���b�N�C��
	cameraInit();			// �J����
	InitAlice();            // �v���C���[
	InitAttack();			// �U���G�t�F�N�g
	InitEnemy();            // �G
	InitEnemyAttack();		// �G�U���G�t�F�N�g
	InitItemColumn();       // �A�C�e���t���[��
	InitPreparation();      // ����
	InitObject();           // �I�u�W�F�N�g
	InitRecipe();           // ���V�s
	InitItem();             // �A�C�e��
	InitMaterial();			// �f��
	InitUseItem();			// �g�p�A�C�e��
	InitSystem();			// �V�X�e���E�B���h�E
	InitEquipment();		// ���J�E���g
	InitEffect();			// �G�t�F�N�g
	SetFontSize(14);		// �t�H���g�T�C�Y�̕ύX
	InitDescription();		// �A�C�e��������

	StopPlayMem(bgmOp01);	// BGM�Đ��X�g�b�v
	PlayMemLoop(bgmMap1);	// BGM�Đ��X�^�[�g

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

// �摜�ǂݍ��݁A������
int IntoEpisode1L_Re() {
	if (stateStage == STATE_EP1STAGE) {
		gFrameWait = 60;
		OperationFlag = 1;
		fadein = 255;
		fadeout = 0;
		cgOperation = LoadTexture("res/operation.png");
	}

	LoadAttackEff();		// �U���G�t�F�N�g
	LoadCgMapChip_1();		// �}�b�v�`�b�v
	LoadCgItem();           // �A�C�e��
	LoadCgAlice();          // �A���X
	LoadCgHealth();			// �̗�
	LoadCgEnemy();			// �G
	LoadCgEnemyAttack();	// �G�U���G�t�F�N�g
	LoadCgPreparation();    // ������
	LoadCgMaterial();       // �f��
	LoadCgObject();         // �I�u�W�F�N�g
	LoadCgRecipe();         // ���V�s
	LoadCgUi();				// UI
	LoadCgEffect();			// �G�t�F�N�g
	LoadCgFukidashi();		// �����o��(�}�[�W�}�^���S)

	initblackin_ep1();		// �u���b�N�C��
	cameraInit();			// �J����
	InitAlice();            // �v���C���[
	InitAttack();			// �U���G�t�F�N�g
	InitEnemy();            // �G
	InitEnemyAttack();		// �G�U���G�t�F�N�g
	InitItemColumn();       // �A�C�e���t���[��
	InitPreparation();      // ����
	InitObject();           // �I�u�W�F�N�g
	InitRecipe();           // ���V�s
	InitItem();             // �A�C�e��
	InitUseItem();			// �g�p�A�C�e��
	InitSystem();			// �V�X�e���E�B���h�E
	InitEquipment();		// ���J�E���g
	InitEffect();			// �G�t�F�N�g
	SetFontSize(14);		// �t�H���g�T�C�Y�̕ύX
	InitDescription();		// �A�C�e��������

	PlayMemLoop(bgmMap1);	// BGM�Đ��X�^�[�g

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

// �摜�ǂݍ��݁A������
int IntoEpisode1L_4() {
	stateStage = STATE_EP1STAGE_4;
	InitAlice();
	InitEnemy();
	InitPreparation();
	InitObject();
	InitPoz();
	initblackin_ep1();
	releaseAlice();
	SetFontSize(14);		// �t�H���g�T�C�Y�̕ύX
	PlayMemLoop(bgmBoss1);			  // BGM�Đ��X�^�[�g
	//InitUseItem();			// �v���[���p

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/

// �҂�����
void FrameWait() {
	int i, j;
	if (gFrameWait > 0) {
		gFrameWait--;
		for (i = 0; i < OBJECT_MAX; i++) {
			// �҂����Ԃ������Ȃ����瓮����悤�ɂ���
			if (gFrameWait == 0) {
				if (material[sy.number].use == 1) {
					material[sy.number].use = 0;
				}
				if (al.state == ALICE_STATE_GATHERING_UP) {
					al.state = ALICE_STATE_UP;
				}
				if (al.state == ALICE_STATE_GATHERING_DOWN) {
					al.state = ALICE_STATE_DOWN;
				}
				if (al.state == ALICE_STATE_GATHERING_RIGHT) {
					al.state = ALICE_STATE_RIGHT;
				}
				if (al.state == ALICE_STATE_GATHERING_LEFT) {
					al.state = ALICE_STATE_LEFT;
				}
			}
		}
		// �҂����Ԃ������Ȃ�����g����悤�ɂ���
		if (gFrameWait == 0) {
			// �����q
			pre[0].use = 0;
			pre[1].use = 0;
			pre[2].use = 0;
			pre[3].use = 0;

			gFrameWait = 0;		// �҂����Ԃ�0�ɂ���
			GetRecipe = 0;		// ���V�s���Q�b�g���I�����
			firstcreate = 0;	// �ŏ��̒������I�����
			material_max = 0;	// �A�C�e���ő�\��������
			// �G�����Ƃ������V�s������
			if (recipe1 == 1) {
				recipe1 = 0;
			}
			else if (recipe2 == 1) {
				recipe2 = 0;
			}
			else if (recipe1 == 2) {
				recipe1 = 0;
			}
			else if (recipe2 == 2) {
				recipe2 = 0;
			}
			else if (recipe1 == 3) {
				recipe1 = 0;
			}
			else if (recipe2 == 3) {
				recipe2 = 0;
			}
			else if (recipe3 == 3) {
				recipe3 = 0;
			}
		}
	}
}

// ���C���Q�[���̒��g
int Episode1_Stage() {

	// ��������̏���(�X�e�[�W�ŏ�����)
	if (stateStage == STATE_EP1STAGE) {
		if (OperationFlag == 1) {
			cameraProcess();		// �J�����ړ�
				if (gFrameWait > 0) {
					gFrameWait--;
				}
			if (gFrameWait <= 0) {
				if (gTrg & KEYIN_Z) {
					OperationFlag = 0;
				}
			}
			return STATE_EP1STAGE;
		}
	}

	// �Q�[���I�[�o�[���������H
	if (gGameoverCount > 0)
	{
		StopPlayMem(seWalk1);
		gGameoverCount--;
		if (gGameoverCount == 0)
		{
			continueflag = 1;
			selectTrg = STATE_NONE;
			// �Q�[���I�[�o�[�ɂ���
			stateStage = GAME_OVER;
			return GAME_OVER;
		}
	}

	FrameWait();			// �҂�����
	AttackCooltime();		// �U���N�[���^�C��(�v���C���[)
	ReGetMaterialWait();	// �ĂуA�C�e�����Q�b�g�ł���܂ł̎���
	EnemyAttackCooltime();	// �U���N�[���^�C��(�G)
	SystemWait();			// �V�X�e���E�B���h�E�̕\������

	// ������ʂ��J��
	if (selectTrg == STATE_ONE) {
		SelectItem();
	}

	DropItem();		// �A�C�e���̃h���b�v

	// �҂����Ԃ��Ȃ��ԓ�����
	if ((gFrameWait == 0) && (attackCooltime == 0) && (clearwait == 0) && (wallwait == 0)) {
		cameraProcess();		// �J�����ړ�
		ControllAlice();		// �A���X�ړ�
		FrameControll();		// �A�C�e���t���[���ړ�
	}

	// �G�ړ�
	EnemyMove();

	// �v���C���[�ƓG�̓����蔻��
	HitCheckPlayerEnemy();

	// �v���C���[�ƓG(�s���͈�)�̓����蔻��
	HitCheckPlayerEnemyRange();

	// �v���C���[�̍U���̓����蔻��
	HitCheckPlayerAttack();

	// �v���C���[�̃A�C�e���U���̓����蔻��
	HitCheckPlayerItemAttack();

	// �v���C���[�ƒ������̓����蔻��
	switch (stateStage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
		HitCheckPlayerPreparation();
	}
	
	// �v���C���[�ƃI�u�W�F�N�g�̓����蔻��
	switch(stateStage) {
	case STATE_EP1STAGE:
	case STATE_EP1STAGE_2:
	case STATE_EP1STAGE_3:
		HitCheckPlayerObject();
	}

	// �ǂ�����
	wallbreak();

	// �G�t�F�N�g����
	ProcessEffect();

	//���߂Ă̒���
	FirstCreate();

	if (wallwait <= 0) {
		// �����f�ށA�A�C�e���m�F��ʕ\��
		if (gTrg & KEYIN_C) {
			if (selectTrg == STATE_NONE) {
				StopPlayMem(seWalk1);
				PlayMemBack(seSelect);		// SE�Đ�
				check = STATE_ONE;
			}
		}

		// �����f�ށA�A�C�e���m�F��ʕ���
		if (gTrg & KEYIN_Z) {
			if (check == STATE_ONE) {
				if (pick == STATE_NONE) {
					PlayMemBack(seCancel);	// SE�Đ�
					check = STATE_NONE;
					InitSelect();
				}
			}
		}
	}

	// �A�C�e���̕ύX
	if (check == STATE_ONE) {
		EquipmentItem();
	}

	// �{�X��|����
	if (clearwait > 0) {
		clearwait--;
		if (clearwait == 0) {
			clearflag = 1;
			StopPlayMem(seWalk1);
			StopPlayMem(bgmBoss1);
			stateStage = STATE_EP1STORY3;
			return IntoEpisode1S3();
		}
	}

	switch (stateStage) {
	case STATE_EP1STAGE:
		return STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		return STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		return STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		return STATE_EP1STAGE_4;
		break;
	}
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/
void DrawEp1LProcess() {
	int i;

	// ��ʂ�����
	HCls();
	worldToView();

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// �}�b�v
	switch (stateStage) {
	case STATE_EP1STAGE:
		DrawMapChip_1();
		DrawObject();		// �I�u�W�F�N�g
		bgstage = STATE_EP1STAGE;
		break;
	case STATE_EP1STAGE_2:
		DrawMapChip_2();
		if (wallflag <= 0) {
			DrawMapChiplm_2();
			DrawFukidashi();
		}
		DrawObject ();		// �I�u�W�F�N�g
		bgstage = STATE_EP1STAGE_2;
		break;
	case STATE_EP1STAGE_3:
		DrawMapChip_3();
		if (wallflag <= 1) {
			DrawMapChiplm_3();
			DrawFukidashi();
		}
		DrawObject ();		// �I�u�W�F�N�g
		bgstage = STATE_EP1STAGE_3;
		break;
	case STATE_EP1STAGE_4:
		DrawMapChip_4();
		bgstage = STATE_EP1STAGE_4;
		break;
	case GAME_OVER:
		if (bgstage == STATE_EP1STAGE) {
			DrawMapChip_1();
			DrawObject();		// �I�u�W�F�N�g
		}
		else if (bgstage == STATE_EP1STAGE_2) {
			DrawMapChip_2();
			if (required_count < 2) {
				DrawMapChiplm_2();
			}
			DrawObject ();		// �I�u�W�F�N�g
		}
		else if (bgstage == STATE_EP1STAGE_3) {
			DrawMapChip_3();
			if (required_count < 4) {
				DrawMapChiplm_3();
			}
			DrawMapChiphd_3();
			DrawObject ();		// �I�u�W�F�N�g
		}
		else {
			DrawMapChip_4();
		}
		break;
	default:
		break;
	}
	
	// �h���b�v�A�C�e��
	DropMaterial();

	// �L�����N�^�[
	DrawAlice();
	
	// �G�U���G�t�F�N�g
	DrawEnemyAttack();

	//�G
	DrawEnemy();
	
	switch (stateStage) {
	case STATE_EP1STAGE:
		DrawMapChiphd_1();
		break;
	case STATE_EP1STAGE_2:
		DrawMapChiphd_2();
		break;
	case STATE_EP1STAGE_3:
		DrawMapChiphd_3();
		break;
	case STATE_EP1STAGE_4:
		DrawMapChiphd_4();
		break;

	}

	// �I�u�W�F�N�g�ɐG��Ă���
	switch (stateStage) {
	case STATE_EP1STAGE:
		if ((obj[7].use == 1) || (obj[8].use == 1)) {
			TouchObject();
		}
		break;
	case STATE_EP1STAGE_2:
		if ((obj[15].use == 1) || (obj[16].use == 1)) {
			TouchObject();
		}
		break;
	case STATE_EP1STAGE_3:
		if ((obj[21].use == 1) || (obj[22].use == 1)) {
			TouchObject();
		}
		break;
	}

	if (wallwait < 1) {
		if (firstcreate == 0) {
			// �A���X�̃q�b�g�|�C���g
			DrawAliceHealth();

			// �A�C�e��������
			DrawItemColumn();//�A�C�e���t���[��

			// �����A�C�e��
			if (frm[2].move == 0) {
				for (i = 0; i < 6; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//�A�C�e������ɓ��ꂽ
					}
				}
			}
			else if (frm[2].move == 1) {
				for (i = 6; i < 10; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//�A�C�e������ɓ��ꂽ
					}
				}
			}
		}
	}

	// �{�X�̃q�b�g�|�C���g
	DrawEnemyHitpoint();

	// �G�t�F�N�g
	DrawEffect();

	// �V�X�e���E�B���h�E
	DrawSystem();
	
	//������
	DrawPreparation();

	// �A�C�e��������
	if (check == STATE_ONE) {
		DrawEquipmentItem();
	}

	// �f��
	DrawMaterial();

	// ���V�s�̃Q�b�g
	DrawGetRecipe();
	
	// ���߂Ă̒���
	DrawFirstCreate();

	// �������
	if (stateStage == STATE_EP1STAGE) {
		if (gFrameWait <= 0) {
			if (fadeout < 0) {
				SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
				DrawMemTh(0, 0, cgOperation);
				DrawMemTh(1100, 680, ButtonB);
				SetDrawMode(AMDRAW_NOBLEND, 0);
			}
			else {
				SetDrawMode(AMDRAW_ALPHABLEND, fadeout);
				DrawMemTh(0, 0, cgOperation);
				DrawTBox(1100, 680, 1200, 710, GetColor(0, 0, 0));
				DrawMemTh(1100, 680, ButtonA);
				DrawPrintf(1140, 690, GetColor(0, 0, 0), "����");
				SetDrawMode(AMDRAW_NOBLEND, 0);
			}
		}
		operationfadeout();
	}

	blackfadein_ep1();	// �u���b�N�t�F�[�h�C��
	blackfadeout_ep1();	// �u���b�N�t�F�[�h�A�E�g

	Systemfadein_out();		// �f�ފl�����̃t�F�[�h�C���A�A�E�g
	FirstCreatefadein();	// �������̃t�F�[�h�C��

	// �X�e�[�W�p�[�g�̊�Flip����
	if ((stateStage == STATE_EP1STAGE) || (stateStage == STATE_EP1STAGE_2) || (stateStage == STATE_EP1STAGE_3) || (stateStage == STATE_EP1STAGE_4)) {
		Flip();
	}

}