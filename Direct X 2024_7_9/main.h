//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#ifndef _MAIN_H_//���̃}�N����`������ĂȂ�������
#define _MAIN_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include<windows.h>
#include"d3dx9.h"//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)//�r���h���̌x���Ώ��p�}�N��
#include"dinput.h"//���͏����ɕK�v
#include"Xinput.h"//�W���C�p�b�h�����ɕK�v
#include"xaudio2.h"//�T�E���h�����ɕK�v

//���C�u�����ɕK�v�ȃ����N
#pragma comment(lib,"d3d9.lib")//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")//[d3dx9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")//�W���C�p�b�h�����ɕK�v

//�}�N��
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "DirectX�̊�{����"
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)//���_���W[2D]|���_�J���[//���_�t�H�[�}�b�g[2D]
#define ID_TIMER (122)//�^�C�}�[��ID
#define TIMER_INTERVAL (1000/60)//�^�C�}�[�̔������ԁi�~���b�j

//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float rhw;//���W�ϊ��p�W���i1.0f�ŌŒ�j
	D3DCOLOR col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE=0,//�^�C�g��
	MODE_GAME,//�Q�[�����
	MODE_RESULT,//���U���g
	MODE_RESULT_LOSE,//���U���g(���@�����ꂽ)
	MODE_MAX
}MODE;

//�v���g
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void ToggleFullscreen(HWND hWnd);	// �E�B���h�E���t���X�N���[���ɂ�����@

#endif