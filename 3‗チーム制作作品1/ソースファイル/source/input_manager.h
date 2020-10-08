#pragma once
/** 
 * @file  input_manager.h
 * キー入力管理
 *
 * @date 2016-05-26
 * @version 3.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */

/**
 *  キー入力を更新する。
 */
void InputMgrUpdate();
/**
*	音楽を止める
*/
void StopAllEpisodeMusic();
/**
 *  クリックされた瞬間を判定する。
 *  @return キー判定の有無
 */
bool InputMgrIsClick();
/**
 *  EXITを判定する。
 *  @return キー判定の有無
 */
bool InputMgrIsExit();
