/*------------------------------------------------
*  @file episode2L.cpp
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
#include	"mapdata_2.h"
#include	"episode2S3.h"
#include	"episode2S4.h"
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
#include	"end.h"
#include	"script_parser.h"

/*-------------------------------------------------
*  ������
-------------------------------------------------*/
// �摜�ǂݍ��݁A������
int IntoEpisode2L() {
	if (bgstage2 == STATE_EP2STAGE1_1) {
		if (bgstage == STATE_EP1STAGE_4) {
			required_count = 0;
			recipe1 = 0;
			recipe2 = 0;
			recipe3 = 0;
		}
	}

	LoadCgMapChip_2();		// �}�b�v�`�b�v
	LoadCgAlice2();         // �A���X
	LoadAttackEff();		// �U���G�t�F�N�g
	LoadCgHealth();			// �̗�
	LoadCgEnemy2();			// �G
	LoadCgEnemyAttack2();	// �G�U���G�t�F�N�g
	LoadCgPreparation();    // ������
	LoadCgMaterial();       // �f��
	LoadCgObject();         // �I�u�W�F�N�g
	LoadCgItem();
	LoadCgUi();				// UI
	LoadCgEffect();			// �G�t�F�N�g
	LoadCgFukidashi2();

	initblackin_ep2();		// �u���b�N�C��
	cameraInit();			// �J����
	InitAlice2();           // �v���C���[
	InitAttack();			// �U���G�t�F�N�g
	InitEnemy2();           // �G
	InitEnemyAttack2();		// �G�U���G�t�F�N�g
	InitItemColumn();       // �A�C�e���t���[��
	InitPreparation();      // ����
	InitObject2();          // �I�u�W�F�N�g
	InitItem();             // �A�C�e��
	InitMaterial();			// �f��
	InitUseItem();			// �g�p�A�C�e��
	InitSystem();			// �V�X�e���E�B���h�E
	InitEquipment();		// ���J�E���g
	InitEffect();			// �G�t�F�N�g
	InitFukidashi2(); 
	InitDescription();
	SetFontSize(14);		// �t�H���g�T�C�Y�̕ύX

	PlayMemLoop(bgmMap2);	// BGM�Đ��X�^�[�g

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

// �摜�ǂݍ��݁A������
int IntoEpisode2L_Re() {
	if (bgstage2 == STATE_EP2STAGE1_1) {
		if (bgstage == STATE_EP1STAGE_4) {
			required_count = 0;
			recipe1 = 0;
			recipe2 = 0;
			recipe3 = 0;
		}
	}

	LoadCgMapChip_2();		// �}�b�v�`�b�v
	LoadCgAlice2();         // �A���X
	LoadAttackEff();		// �U���G�t�F�N�g
	LoadCgHealth();			// �̗�
	LoadCgEnemy2();			// �G
	LoadCgEnemyAttack2();	// �G�U���G�t�F�N�g
	LoadCgPreparation();    // ������
	LoadCgMaterial();       // �f��
	LoadCgObject();         // �I�u�W�F�N�g
	LoadCgItem();
	LoadCgUi();				// UI
	LoadCgEffect();			// �G�t�F�N�g
	LoadCgFukidashi2();

	initblackin_ep2();		// �u���b�N�C��
	cameraInit();			// �J����
	InitAlice2();           // �v���C���[
	InitAttack();			// �U���G�t�F�N�g
	InitEnemy2();           // �G
	InitEnemyAttack2();		// �G�U���G�t�F�N�g
	InitItemColumn();       // �A�C�e���t���[��
	InitPreparation();      // ����
	InitObject2();          // �I�u�W�F�N�g
	InitItem();             // �A�C�e��
	InitUseItem();			// �g�p�A�C�e��
	InitSystem();			// �V�X�e���E�B���h�E
	InitEquipment();		// ���J�E���g
	InitEffect();			// �G�t�F�N�g
	InitFukidashi2();
	InitDescription();
	SetFontSize(14);		// �t�H���g�T�C�Y�̕ύX

	PlayMemLoop(bgmMap2);	// BGM�Đ��X�^�[�g

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

int IntoEpisode2L_3_1() {
	al.x = 40 * 18;
	al.y = 40 * 20;
	al.state = ALICE_STATE_IDLE_UP;
	InitEnemy2();
	InitPreparation();
	InitObject2();
	InitPoz();
	initblackin_ep2();
	releaseAlice2();
	SetFontSize(14);		// �t�H���g�T�C�Y�̕ύX
	PlayMemLoop(bgmBoss2);			  // BGM�Đ��X�^�[�g
	al.move = 0;

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

int IntoEpisode2L_3_2() {
	al.x = 40 * 18;
	al.y = 40 * 20;
	al.state = ALICE_STATE_IDLE_UP;
	PlayMemLoop(bgmBoss3);			  // BGM�Đ��X�^�[�g
	initblackin_ep2();
	InitEnemy2();
	SetFontSize(14);		// �t�H���g�T�C�Y�̕ύX

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

/*-------------------------------------------------
*  �X�V
-------------------------------------------------*/

// �҂�����
void FrameWait2() {
	int i;
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
			if (recipe1 == 4) {
				recipe1 = 0;
			}
			else if (recipe2 == 4) {
				recipe2 = 0;
			}
			else if (recipe1 == 5) {
				recipe1 = 0;
			}
			else if (recipe2 == 5) {
				recipe2 = 0;
			}
			else if (recipe1 == 6) {
				recipe1 = 0;
			}
			else if (recipe2 == 6) {
				recipe2 = 0;
			}
			else if (recipe3 == 6) {
				recipe3 = 0;
			}
		}
	}
}

// ���C���Q�[���̒��g(�X�e�[�W2)
int Episode2_Stage() {

	// �Q�[���I�[�o�[���������H
	if (gGameoverCount > 0)
	{
		StopPlayMem(seWalk2);
		gGameoverCount--;
		if (gGameoverCount == 0)
		{
			continueflag = 2;
			selectTrg = STATE_NONE;
			// �Q�[���I�[�o�[�ɂ���
			stateStage = GAME_OVER2;
			return GAME_OVER2;
		}
	}

	FrameWait2();			// �҂�����
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
	if ((gFrameWait == 0) & (attackCooltime == 0) && (clearwait == 0) && (wallwait == 0)) {
		cameraProcess();		// �J�����ړ�
		ControllAlice2();		// �A���X�ړ�
		FrameControll();		// �A�C�e���t���[���ړ�
	}

	// �G�ړ�
	EnemyMove2();

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
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
		HitCheckPlayerPreparation();
	}

	// �v���C���[�ƃI�u�W�F�N�g�̓����蔻��
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
	case STATE_EP2STAGE1_2:
	case STATE_EP2STAGE1_3:
	case STATE_EP2STAGE2_1:
	case STATE_EP2STAGE2_2:
		HitCheckPlayerObject();
	}

	// �ǂ�����
	wallbreak2();

	// �G�t�F�N�g����
	ProcessEffect();

	//���߂Ă̒���
	FirstCreate();

	if (wallwait <= 0) {
		// �����f�ށA�A�C�e���m�F��ʕ\��
		if (gTrg & KEYIN_C) {
			if (selectTrg == STATE_NONE) {
				StopPlayMem(seWalk2);
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
			// �n�[�g�̏���
			if (clearflag == 1) {
				StopPlayMem(seWalk2);
				clearflag = 2;
				StopPlayMem(bgmBoss2);
				stateStage = STATE_EP2STORY3;
				ScriptCreate();
				Skipflag4 = 0;
				initblackin_ep2s3();
				return STATE_EP2STORY3;
			}
			// �}�b�h�n�b�^�[
			else if (clearflag == 2) {
				clearflag = 3;
				StopPlayMem(seWalk2);
				StopPlayMem(bgmBoss3);
				stateStage = STATE_EP2STORY4;
				ScriptCreate();
				Skipflag7 = 0;
				initblackin_ep2s4();
				return STATE_EP2STORY4;
			}
		}
	}

	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		return STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		return STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		return STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		return STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		return STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		return STATE_EP2STAGE_3;
		break;
	}
}

/*------------------------------------------------------
*  �`��
------------------------------------------------------*/
void DrawEp2LProcess() {

	int i;

	// ��ʂ�����
	HCls();
	worldToView();

	SetDrawArea(0, 0, 1280, 720);
	SetDrawMode(AMDRAW_NOBLEND, 0);
	SetDrawMode(AMDRAW_NEAREST, 0);

	// �}�b�v
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		DrawMapChip_2_1_1();
		if (wallflag <= 2) {
			DrawMapChiplm_2_1_1();
			DrawFukidashi2();
		}
		DrawObject2();		// �I�u�W�F�N�g
		bgstage2 = STATE_EP2STAGE1_1;
		break;
	case STATE_EP2STAGE1_2:
		DrawMapChip_2_1_2();
		DrawObject2();		// �I�u�W�F�N�g
		bgstage2 = STATE_EP2STAGE1_2;
		break;
	case STATE_EP2STAGE1_3:
		DrawMapChip_2_1_3();
		if (wallflag <= 4) {
			DrawMapChiplm_2_1_3();
			DrawFukidashi2();
		}
		DrawObject2();		// �I�u�W�F�N�g
		bgstage2 = STATE_EP2STAGE1_3;
		break;
	case STATE_EP2STAGE2_1:
		DrawMapChip_2_2_1();
		if (wallflag <= 3) {
			DrawMapChiplm_2_2_1();
			DrawFukidashi2();
		}
		DrawObject2();		// �I�u�W�F�N�g
		bgstage2 = STATE_EP2STAGE2_1;
		break;
	case STATE_EP2STAGE2_2:
		DrawMapChip_2_2_2();
		DrawObject2();		// �I�u�W�F�N�g
		bgstage2 = STATE_EP2STAGE2_2;
		break;
	case STATE_EP2STAGE_3:
		DrawMapChip_2_3();
		bgstage2 = STATE_EP2STAGE_3;
		break;
	case GAME_OVER2:
		if (bgstage2 == STATE_EP2STAGE1_1) {
			DrawMapChip_2_1_1();
			if (wallflag <= 2) {
				DrawMapChiplm_2_1_1();
			}
			DrawObject2();		// �I�u�W�F�N�g
		}
		else if (bgstage2 == STATE_EP2STAGE1_2) {
			DrawMapChip_2_1_2();
			DrawObject2();		// �I�u�W�F�N�g
		}
		else if (bgstage2 == STATE_EP2STAGE1_3) {
			DrawMapChip_2_1_3();
			if (wallflag <= 4) {
				DrawMapChiplm_2_1_3();
			}
			DrawObject2();		// �I�u�W�F�N�g
		}
		else if (bgstage2 == STATE_EP2STAGE2_1) {
			DrawMapChip_2_2_1();
			if (wallflag <= 3) {
				DrawMapChiplm_2_2_1();
			}
			DrawObject2();		// �I�u�W�F�N�g
		}
		else if (bgstage2 == STATE_EP2STAGE2_2) {
			DrawMapChip_2_2_2();
			DrawObject2();		// �I�u�W�F�N�g
		}
		else {
			DrawMapChip_2_3();
		}
		break;
	default:
		break;
	}

	// �h���b�v�A�C�e��
	DropMaterial();

	// �L�����N�^�[
	DrawAlice2();

	// �G�U���G�t�F�N�g
	DrawEnemyAttack2();

	//�G
	DrawEnemy2();

	// �}�b�v�̉e�ɂȂ镔��
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		DrawMapChiphd_2_1_1();
		break;
	case STATE_EP2STAGE1_2:
		DrawMapChiphd_2_1_2();
		break;
	case STATE_EP2STAGE1_3:
		DrawMapChiphd_2_1_3();
		break;
	case STATE_EP2STAGE2_1:
		DrawMapChiphd_2_2_1();
		break;
	case STATE_EP2STAGE2_2:
		break;
	case STATE_EP2STAGE_3:
		DrawMapChiphd_2_3();
		break;
	}

	// �I�u�W�F�N�g�ɐG��Ă���
	switch (stateStage) {
	case STATE_EP2STAGE1_1:
		if ((obj[1].use == 1) || (obj[2].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE1_2:
		if ((obj[13].use == 1) || (obj[14].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE1_3:
		if ((obj[8].use == 1) || (obj[9].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE2_1:
		if ((obj[8].use == 1) || (obj[9].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE2_2:
		if ((obj[8].use == 1) || (obj[9].use == 1)) {
			TouchObject2();
		}
		break;
	case STATE_EP2STAGE_3:
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
				for (i = 6; i < 12; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//�A�C�e������ɓ��ꂽ
					}
				}
			}
			else if (frm[2].move == 2) {
				for (i = 12; i < 17; i++) {
					if (useit[i].use == 1) {
						DrawItem(i);			//�A�C�e������ɓ��ꂽ
					}
				}
			}
		}
	}

	// �{�X�̃q�b�g�|�C���g
	DrawEnemyHitpoint2();

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

	blackfadein_ep2();	// �u���b�N�t�F�[�h�C��
	blackfadeout_ep2();	// �u���b�N�t�F�[�h�A�E�g

	Systemfadein_out();		// �f�ފl�����̃t�F�[�h�C���A�A�E�g
	FirstCreatefadein();	// �������̃t�F�[�h�C��

	// �X�e�[�W�p�[�g�̊�Flip����
	if ((stateStage == STATE_EP2STAGE1_1) || (stateStage == STATE_EP2STAGE1_2) || (stateStage == STATE_EP2STAGE1_3) || (stateStage == STATE_EP2STAGE2_1) || (stateStage == STATE_EP2STAGE2_2) || (stateStage == STATE_EP2STAGE_3)) {
		Flip();
	}

}