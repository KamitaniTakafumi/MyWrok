#pragma once
/**
 * @file  script_parser.h
 * C言語プログラミング：スクリプト構文解析
 *
 * @date 2016-05-30
 * @version 1.0
 *
 * Copyright (C) Amusement Media Academy All rights Resved.
 */
/**
 *  スクリプトの生成
 */
void ScriptCreate();
/**
 *  スクリプトの更新
 *
 *  @retval true 終了
 *          false 実行中
 */
bool ScriptUpdate();
/**
 *  スクリプトの描画
 */
void ScriptRender();
/**
 *  スクリプトの破棄
 */
extern void ScriptDestroy();

void StoryFadeIn();
void StoryFadeOut();

extern int Endflag;