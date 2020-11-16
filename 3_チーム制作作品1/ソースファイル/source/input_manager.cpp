/** 
 * @file  input_manager.cpp
 * �L�[���͊Ǘ�
 *
 * @date 2016-05-26
 * @version 3.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */
#include "input_manager.h"
#include <stdint.h>
#include "HitJudgment.h"
#include "amgame.h"

/**
 *  �L�[���͐ݒ�p
 */
typedef enum {
  EXIT,     ///< �G�O�W�b�g
  CANCEL,   ///< �L�����Z��
  DECIDE,   ///< ����
  MAX,      ///< �ő�
} KEY_CONFIG;
/**
 *  �L�[���͐ݒ�p
 */
typedef struct {
	uint32_t fresh;   ///< ����̓���
  uint32_t last;    ///< �O��̓���
  uint32_t trigger; ///< ���������̓���
} INPUT_KEY;

/**
 *  �L�[��������Ă��邩���肷��B
 *
 *  @param key_name ���肷��L�[
 *  @return �L�[����̗L��
 */
static bool InputMgrIsKey(KEY_CONFIG key_name);
/**
 *  �L�[�������ꂽ�u�Ԃ𔻒肷��B
 *
 *  @param key_name ���肷��L�[
 *  @return �L�[����̗L��
 */
static bool InputMgrIsKeyDown(KEY_CONFIG key_name);

/**
 *  �L�[����
 */
static INPUT_KEY g_input_key = {0};
/**
 *  �L�[���͐ݒ�
 *
 *  ��KEY_CONFIG�ƕ��т����킹��
 */
static uint32_t g_key_config[MAX] = {
  KEYIN_ESC,
  MOUSEKEY_RIGHT,
  MOUSEKEY_LEFT
};

/**
 *  �L�[���͂��X�V����B
 *
 *  ���t���[�����ƂɌĂяo�����ƂŃL�[���͂��X�V���܂��B
 */
void InputMgrUpdate() {
	INPUT_KEY* key = &g_input_key;
	// �L�[���̓f�[�^�̍X�V
	key->last = key->fresh;
	key->fresh = CheckKey(AMINPUT_MULT);
	key->trigger = key->fresh ^ key->last & key->fresh;
}
/**
 *  �N���b�N���ꂽ�u�Ԃ𔻒肷��B
 */
bool InputMgrIsClick() {
  return InputMgrIsKeyDown(DECIDE);
}
/**
 *  EXIT�𔻒肷��B
 */
bool InputMgrIsExit() {
  return InputMgrIsKeyDown(EXIT);
}
/**
 *  �L�[��������Ă��邩���肷��B
 */
bool InputMgrIsKey(KEY_CONFIG key_name) {
  uint32_t key = g_key_config[key_name];
  return (g_input_key.fresh & key) ? true: false;
}
/**
 *  �L�[�������ꂽ�u�Ԃ𔻒肷��B
 */
bool InputMgrIsKeyDown(KEY_CONFIG key_name) {
	uint32_t key = g_key_config[key_name];
	return (g_input_key.trigger & key) ? true : false;
}
/**
*	���y���~�߂�
*/
void StopAllEpisodeMusic() {
	StopPlayMem(bgmOp01);
	StopPlayMem(bgmOp02);
	StopPlayMem(bgmOp03);
	StopPlayMem(I_home);
	StopPlayMem(DCF);
	StopPlayMem(Lucifer);
	StopPlayMem(cheshirebgm);
	StopPlayMem(Assault);
	StopPlayMem(Be_quiet);
	StopPlayMem(cheshirebgm2);
	StopPlayMem(loneliness);
	StopPlayMem(midnightmoon);
	StopPlayMem(queenbgm);
	StopPlayMem(queenbgm2);
	StopPlayMem(madhatterbgm);
	StopPlayMem(reddress);
	StopPlayMem(reunion);
	StopPlayMem(dustwall);
	StopPlayMem(farewell);
	StopPlayMem(Inherited_Hope);
}
