/** 
 * @file  input_manager.cpp
 * キー入力管理
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
 *  キー入力設定用
 */
typedef enum {
  EXIT,     ///< エグジット
  CANCEL,   ///< キャンセル
  DECIDE,   ///< 決定
  MAX,      ///< 最大
} KEY_CONFIG;
/**
 *  キー入力設定用
 */
typedef struct {
	uint32_t fresh;   ///< 今回の入力
  uint32_t last;    ///< 前回の入力
  uint32_t trigger; ///< 押した時の入力
} INPUT_KEY;

/**
 *  キーが押されているか判定する。
 *
 *  @param key_name 判定するキー
 *  @return キー判定の有無
 */
static bool InputMgrIsKey(KEY_CONFIG key_name);
/**
 *  キーが押された瞬間を判定する。
 *
 *  @param key_name 判定するキー
 *  @return キー判定の有無
 */
static bool InputMgrIsKeyDown(KEY_CONFIG key_name);

/**
 *  キー入力
 */
static INPUT_KEY g_input_key = {0};
/**
 *  キー入力設定
 *
 *  ※KEY_CONFIGと並びを合わせる
 */
static uint32_t g_key_config[MAX] = {
  KEYIN_ESC,
  MOUSEKEY_RIGHT,
  MOUSEKEY_LEFT
};

/**
 *  キー入力を更新する。
 *
 *  毎フレームごとに呼び出すことでキー入力を更新します。
 */
void InputMgrUpdate() {
	INPUT_KEY* key = &g_input_key;
	// キー入力データの更新
	key->last = key->fresh;
	key->fresh = CheckKey(AMINPUT_MULT);
	key->trigger = key->fresh ^ key->last & key->fresh;
}
/**
 *  クリックされた瞬間を判定する。
 */
bool InputMgrIsClick() {
  return InputMgrIsKeyDown(DECIDE);
}
/**
 *  EXITを判定する。
 */
bool InputMgrIsExit() {
  return InputMgrIsKeyDown(EXIT);
}
/**
 *  キーが押されているか判定する。
 */
bool InputMgrIsKey(KEY_CONFIG key_name) {
  uint32_t key = g_key_config[key_name];
  return (g_input_key.fresh & key) ? true: false;
}
/**
 *  キーが押された瞬間を判定する。
 */
bool InputMgrIsKeyDown(KEY_CONFIG key_name) {
	uint32_t key = g_key_config[key_name];
	return (g_input_key.trigger & key) ? true : false;
}
/**
*	音楽を止める
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
