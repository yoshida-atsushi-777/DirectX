//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//�L�[�̎��
typedef enum
{
	JOYKEY_UP=0,//ue
	JOYKEY_DOWN,//sita
	JOYKEY_LEFT,//hidari
	JOYKEY_RIGHT,//migi
	JOYKEY_START,//�X�^�[�g�{�^��
	JOYKEY_BACK,//�o�b�N�{�^��
	JOYKEY_L3,//L3�{�^��
	JOYKEY_R3,//R3�{�^��
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

//�v���g
//�L�[�{�[�h
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);
//�R���g���[���[
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);

#endif