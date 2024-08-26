//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//キーの種類
typedef enum
{
	JOYKEY_UP=0,//ue
	JOYKEY_DOWN,//sita
	JOYKEY_LEFT,//hidari
	JOYKEY_RIGHT,//migi
	JOYKEY_START,//スタートボタン
	JOYKEY_BACK,//バックボタン
	JOYKEY_L3,//L3ボタン
	JOYKEY_R3,//R3ボタン
	JOYKEY_L1,//
	JOYKEY_R1,//
	JOYKEY_L2,//
	JOYKEY_R2,//
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX
}JOYKEY;

//プロト
//キーボード
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);
//コントローラー
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);

#endif