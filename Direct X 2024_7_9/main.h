//---------------------------------------------------------
// 
// Author:Yoshida Atyushi
//---------------------------------------------------------

#ifndef _MAIN_H_//このマクロ定義がされてなかったら
#define _MAIN_H_//2重インクルード防止のマクロ定義

#include<windows.h>
#include"d3dx9.h"//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告対処用マクロ
#include"dinput.h"//入力処理に必要
#include"Xinput.h"//ジョイパッド処理に必要
#include"xaudio2.h"//サウンド処理に必要

//ライブラリに必要なリンク
#pragma comment(lib,"d3d9.lib")//描画処理に必要
#pragma comment(lib,"d3dx9.lib")//[d3dx9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//DirectXコンポーネント（部品）使用に必要
#pragma comment(lib,"winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要
#pragma comment(lib,"xinput.lib")//ジョイパッド処理に必要

//マクロ
#define CLASS_NAME "WindowClass"
#define WINDOW_NAME "DirectXの基本処理"
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)//頂点座標[2D]|頂点カラー//頂点フォーマット[2D]
#define ID_TIMER (122)//タイマーのID
#define TIMER_INTERVAL (1000/60)//タイマーの発生時間（ミリ秒）

//頂点情報[3D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float rhw;//座標変換用係数（1.0fで固定）
	D3DCOLOR col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

//画面(モード)の種類
typedef enum
{
	MODE_TITLE=0,//タイトル
	MODE_GAME,//ゲーム画面
	MODE_RESULT,//リザルト
	MODE_RESULT_LOSE,//リザルト(自機がやられた)
	MODE_MAX
}MODE;

//プロト
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void ToggleFullscreen(HWND hWnd);	// ウィンドウをフルスクリーンにする方法

#endif