//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "game.h"
#include "input.h"
#include "background.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "score.h"
#include "effect.h"

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureGame = { NULL };//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;//頂点バッファへのポインタ
GAMESTATE g_gameState=GAMESTATE_NONE;//ゲームの状態
int g_nCounterGameState = 0;//状態管理カウンター

void InitGame(void)
{
	//各種オブジェクトの初期化処理

	//背景の初期化処理
	InitBackGround();
	//プレイヤーの初期化処理
	InitPlayer();
	//弾の初期化処理
	InitBullet();
	//エフェクトの初期化
	InitEffect();
	//敵の初期化
	InitEnemy();

	InitScore();
	SetScore(0);

	SetEnemy(D3DXVECTOR3(1200.0f, 200.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(1200.0f, 500.0f, 0.0f), 0);

	g_gameState = GAMESTATE_NORMAL;//通常状態に設定
	g_nCounterGameState = 0;
}
void UninitGame(void)
{
	//各種オブジェクトの終了処理
	
	//背景の終了処理
	UninitBackGround();
	//プレイヤーの終了処理
	UninitPlayer();
	//弾の終了処理
	UninitBullet();
	//エフェクトの終了処理
	UninitEffect();
	//敵の終了処理
	UninitEnemy();
	//スコアの終了処理
	UninitScore();
}
void UpdateGame(void)
{
	int nNum;

	//各種オブジェクトの更新処理
	//背景の更新処理
	UpdateBackGround();
	//プレイヤーの更新処理
	UpdatePlayer();
	//敵の更新処理
	UpdateEnemy();
	//弾の更新処理
	UpdateBullet();
	//エフェクトの更新処理
	UpdateEffect();
	//スコアの更新処理
	UpdateScore();

	Player* pPlayer = GetPlayer();	
	nNum = GetNumEnemy();

	if (pPlayer->bUse == false || nNum <= 0)
	{
		//画面(モード)の設定
		g_gameState = GAMESTATE_END;
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://通常状態
		break;
	case GAMESTATE_END://終了状態
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60 && nNum <= 0)
		{
			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;//何もしていない状態に設定
			SetFade(MODE_RESULT);
			//画面(モード)の設定
			//SetMode(MODE_RESULT);
		}
		else if (g_nCounterGameState >= 60 && pPlayer->bUse == false)
		{
			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;//何もしていない状態に設定
			SetFade(MODE_RESULT_LOSE);
			//画面(モード)の設定
			//SetMode(MODE_RESULT);
		}
		break;
	}

}
void DrawGame(void)
{
	//各種オブジェクトの描画処理
	//背景の描画処理
	DrawBackGround();
	//弾の描画処理
	DrawBullet();
	//プレイヤーの描画処理
	DrawPlayer();
	//敵の描画処理
	DrawEnemy();
	//エフェクトの描画処理
	DrawEffect();
	//スコアの描画処理
	DrawScore();

}
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	//g_nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_gameState;
}