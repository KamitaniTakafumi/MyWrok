#pragma once
/** 
 * @file  input_manager.h
 * �L�[���͊Ǘ�
 *
 * @date 2016-05-26
 * @version 3.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */

/**
 *  �L�[���͂��X�V����B
 */
void InputMgrUpdate();
/**
*	���y���~�߂�
*/
void StopAllEpisodeMusic();
/**
 *  �N���b�N���ꂽ�u�Ԃ𔻒肷��B
 *  @return �L�[����̗L��
 */
bool InputMgrIsClick();
/**
 *  EXIT�𔻒肷��B
 *  @return �L�[����̗L��
 */
bool InputMgrIsExit();
