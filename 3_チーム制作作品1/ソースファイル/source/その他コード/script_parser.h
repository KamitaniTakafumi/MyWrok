#pragma once
/**
 * @file  script_parser.h
 * C����v���O���~���O�F�X�N���v�g�\�����
 *
 * @date 2016-05-30
 * @version 1.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */
/**
 *  �X�N���v�g�̐���
 */
void ScriptCreate();
/**
 *  �X�N���v�g�̍X�V
 *
 *  @retval true �I��
 *          false ���s��
 */
bool ScriptUpdate();
/**
 *  �X�N���v�g�̕`��
 */
void ScriptRender();
/**
 *  �X�N���v�g�̔j��
 */
extern void ScriptDestroy();

void StoryFadeIn();
void StoryFadeOut();

extern int Endflag;