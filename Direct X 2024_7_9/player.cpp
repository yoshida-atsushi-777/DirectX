//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "player.h"
#include "Input.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "fade.h"

//マクロ
#define MAX_MAX (400.0f)//最大でかい
#define MAX_MIN (10.0f)//最小ちいさい

//グローバル
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;     //テクスチャ2へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer1 = NULL;//頂点バッファ2へのポインタ
Player g_player;                                 //レイヤーの情報

//プレイヤーの初期化処理
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;                   //デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ2の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Player.png",      //テクスチャのファイル名
		&g_pTexturePlayer1);


	//g_nCounterAnimPlayer1 = 0;                   //カウンターを初期化する

	//g_nPatternAnimPlayer1 = 0;                   //パターンNo.を初期化する


	g_player.pos = D3DXVECTOR3(100.0f,360.0f,0.0f);//位置を初期化する

	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);  //移動量を初期化する

	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f); //向きを初期化する、今回はZ軸（3番目）

	g_player.Bullet.x = 10.0f;

	g_player.Bullet.y = 10.0f;

	g_player.bUse = true;

	g_player.bDisp = true;

	g_player.nZanki = 3;

	g_player.bHit = false;

	g_player.nCntAnimState = 0;

	g_player.nLife = 5;

	//対角線の長さを算出する
	g_player.Length = sqrtf(50.0f * 50.0f + 100.0f * 100.0f) / 2.0f;

	//対角線の角度を算出する
	g_player.Angle = atan2f(HABA ,TAKASA);

	//頂点バッファ2の生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer1,
		NULL);

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定

	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y-60.0f, 0.0f);//pVtx[0].pos = D3DXVECTOR3(450.0f, 300.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y-60.0f, 0.0f);//pVtx[1].pos = D3DXVECTOR3(650.0f, 300.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y+60.0f, 0.0f);//pVtx[2].pos = D3DXVECTOR3(450.0f, 600.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y+60.0f, 0.0f);//pVtx[3].pos = D3DXVECTOR3(650.0f, 600.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer1->Unlock();
}
//プレイヤーの終了処理
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer1 != NULL)
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer1 != NULL)
	{
		g_pVtxBuffPlayer1->Release();
		g_pVtxBuffPlayer1 = NULL;
	}
}
//プレイヤーの更新処理
void UpdatePlayer(void)
{

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	if (g_player.bUse == true)
	{
		if (GetJoypadPress(JOYKEY_UP) == true)
		{//上キー
			g_player.move.x += 0.0f;
			g_player.move.y -= 3.0f;
		}
		else if (GetJoypadPress(JOYKEY_DOWN) == true)
		{//下キー
			g_player.move.x += 0.0f;
			g_player.move.y += 3.0f;

		}
		else if (GetJoypadPress(JOYKEY_LEFT) == true)
		{
			if (GetJoypadPress(JOYKEY_LEFT) == true && GetJoypadPress(JOYKEY_UP) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 3.0f;
			}
			else if (GetJoypadPress(JOYKEY_LEFT) == true && GetJoypadPress(JOYKEY_DOWN) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 3.0f;
			}
			else if (GetJoypadPress(JOYKEY_A) == true)
			{
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
			}
			else
			{
				//移動量を更新（増加）
				g_player.move.x -= 3.0f;
				g_player.move.y += 0.0f;
			}
		}
		else if (GetJoypadPress(JOYKEY_RIGHT) == true)
		{
			if (GetJoypadPress(JOYKEY_RIGHT) == true && GetJoypadPress(JOYKEY_UP) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 3.0f;
			}
			else if (GetJoypadPress(JOYKEY_RIGHT) == true && GetJoypadPress(JOYKEY_DOWN) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 3.0f;
			}
			else
			{
				g_player.move.x += 3.0f;
				g_player.move.y += 0.0f;
			}
		}
		else if (GetJoypadPress(JOYKEY_START) == true)
		{

		}
		else if (GetJoypadPress(JOYKEY_A) == true)
		{
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
		}

		if (KeyboardRepeat(DIK_A) == true)
		{

			if (KeyboardRepeat(DIK_W) == true)
			{
				//移動量を更新（増加）
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 3.0f;
				//Wキーが押された（同時押し）左上に移動
				//g_player.pos.x += sinf(-D3DX_PI*0.75f) * g_player.move.x;//sinf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）
				//g_player.pos.y += cosf(-D3DX_PI*0.75f) * g_player.move.y;//cosf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）
			}
			else if (KeyboardRepeat(DIK_S) == true)
			{
				//移動量を更新（増加）
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 3.0f;
				//Sキーが押された（同時押し）左下に移動
				//g_player.pos.x += sinf(-D3DX_PI*0.25f) * g_player.move.x;//sinf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）
				//g_player.pos.y += cosf(-D3DX_PI*0.25f) * g_player.move.y;//cosf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）

			}
			else if (KeyboardRepeat(DIK_LEFT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//弾の設定
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z += 0.2f;
				}
				else
				{
					g_player.rot.z += 0.2f;
				}

			}
			else if (KeyboardRepeat(DIK_RIGHT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//弾の設定
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z -= 0.2f;
				}
				else
				{
					g_player.rot.z -= 0.2f;
				}
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				//移動量を更新（増加）
				g_player.move.x -= 3.0f;
				g_player.move.y += 0.0f;
			}
			else
			{
				//移動量を更新（増加）
				g_player.move.x -= 3.0f;
				g_player.move.y += 0.0f;
				//Aキーが押された左に移動
				//g_player.pos.x -= g_player.move.x;
			}



			//移動量を更新（減衰）
			//g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
			//g_player.move.y += (0.0f - g_player.move.y) * 0.5f;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			//g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

			//位置座標の設定
			//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y - 60.0f, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y - 60.0f, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y + 60.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y + 60.0f, 0.0f);

			//頂点バッファをアンロックする
			//g_pVtxBuffPlayer1->Unlock();
		}
		else if (KeyboardRepeat(DIK_D) == true)//|| KeyboardRelease(DIK_D)==true)
		{
			if (KeyboardRepeat(DIK_W) == true)
			{

				g_player.move.x += sinf(D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 3.0f;
				//Wキーが押された（同時押し）右上に移動
				//g_player.pos.x += sinf(D3DX_PI * 0.75f) * g_player.move.x;//sinf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）
				//g_player.pos.y += cosf(D3DX_PI * 0.75f) * g_player.move.y;//cosf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）


			}
			else if (KeyboardRepeat(DIK_S) == true)
			{
				g_player.move.x += sinf(D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 3.0f;
				//Sキーが押された（同時押し）右下に移動
				//g_player.pos.x += sinf(D3DX_PI*0.25f) * g_player.move.x;//sinf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）
				//g_player.pos.y += cosf(D3DX_PI*0.25f) * g_player.move.y;//cosf(角度[-3.14(左周り)~3.14（右回り）])*長さ（移動量）

			}
			else if (KeyboardRepeat(DIK_LEFT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//弾の設定
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z += 0.2f;
				}
				else
				{
					g_player.rot.z += 0.2f;
				}

			}
			else if (KeyboardRepeat(DIK_RIGHT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//弾の設定
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z -= 0.2f;
				}
				else
				{
					g_player.rot.z -= 0.2f;
				}
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.move.x += 3.0f;
				g_player.move.y += 0.0f;
			}
			else
			{
				g_player.move.x += 3.0f;
				g_player.move.y += 0.0f;
				//Dキーが押された右に移動
				//g_player.pos.x += g_player.move.x;
			}

		}
		else if (KeyboardRepeat(DIK_W) == true)
		{
			if (KeyboardRepeat(DIK_S) == true)
			{
				//Sキーが押された（できれば止まりたい）
				//g_player.pos.y -= 1.0f;
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.move.x += 0.0f;
				g_player.move.y -= 3.0f;
			}
			else
			{
				//Wキーが押された上に移動
				g_player.move.x += 0.0f;
				g_player.move.y -= 3.0f;
			}

		}
		else if (KeyboardRepeat(DIK_S) == true)
		{
			if (KeyboardRepeat(DIK_W) == true)
			{
				//Wキーが押された（できれば止まりたい）
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.move.x += 0.0f;
				g_player.move.y += 3.0f;
			}
			else
			{
				//Sキーが押された下に移動
				g_player.move.x += 0.0f;
				g_player.move.y += 3.0f;

			}
		}
		else if (KeyboardRepeat(DIK_R) == true)
		{
			InitPlayer();
		}
		else if (KeyboardRepeat(DIK_LEFT) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.rot.z += 0.2f;
			}
			else
			{
				g_player.rot.z += 0.2f;
			}
		}
		else if (KeyboardRepeat(DIK_RIGHT) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.rot.z -= 0.2f;
			}
			else
			{
				g_player.rot.z -= 0.2f;
			}
		}
		else if (KeyboardRepeat(DIK_UP) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				if (g_player.Length <= MAX_MAX)
				{
					g_player.Length += 1.0f;
				}

			}
			else
			{
				if (g_player.Length <= MAX_MAX)
				{
					g_player.Length += 1.0f;
				}

			}
		}
		else if (KeyboardRepeat(DIK_DOWN) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//弾の設定
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				if (g_player.Length >= MAX_MIN)
				{
					g_player.Length -= 1.0f;
				}
			}
			else
			{
				if (g_player.Length >= MAX_MIN)
				{
					g_player.Length -= 1.0f;
				}

			}
		}
		else if (KeyboardTrigger(DIK_SPACE) == true)
		{//SPACE
			//弾の設定
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 10.0f, 0.0f), BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 15.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 15.0f, 0.0f), BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 15.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 15.0f, 0.0f), BULLETTYPE_PLAYER);
		}
		//else if (KeyboardTrigger(DIK_1) == true)
		//{
		//	AddScore(200);
		//}

		if (g_player.bHit == true)
		{
			g_player.nCntAnimState++;//カウンターを加算
		}
	}

	//位置を更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//移動量を更新（減衰）
	g_player.move.x += (0.0f - g_player.move.x) * 0.1f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.1f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	//if (g_player.nCntAnimState >= 5)
	//{
	//	//頂点カラーの設定
	//	pVtx[0].col = D3DCOLOR_RGBA(255,255,255, 255);
	//	pVtx[1].col = D3DCOLOR_RGBA(255,255,255, 255);
	//	pVtx[2].col = D3DCOLOR_RGBA(255,255,255, 255);
	//	pVtx[3].col = D3DCOLOR_RGBA(255,255,255, 255);

	//	g_player.nCntAnimState = 0;
	//	g_player.bHit  = false;
	//}

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//モードを設定（リザルト）
			SetMode(MODE_RESULT_LOSE);

			return;
		}
		else
		{
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
			}
		}
		break;
	}

	//位置座標の設定
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer1->Unlock();

	//g_nCounterAnimPlayer1++;//カウンターを加算
	//if (g_nCounterAnimPlayer1>=5)//(g_nCounterAnimPlayer1)%5==0)//一定時間経過した
	//{
	//	g_nCounterAnimPlayer1 = 0;//カウンターを初期値に戻す

	//	g_nPatternAnimPlayer1++;// = (g_nPatternAnimPlayer1+1)%10; //パターンを更新する
	//	
	//	if (g_nPatternAnimPlayer1>=10)//総パターン数を超えた
	//	{
	//		//g_nPatternAnimPlayer1 = g_nCounterAnimPlayer1 + 0.5f;;//パターンを初期化する
	//		g_nPatternAnimPlayer1 = 0;
	//	}
	//	
	//	//テクスチャ座標の更新0.125

	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1/5) * 0.5f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f);//(u,v)
	//	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)
	//	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)

	//}

}
//プレイヤーの描画処理
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//頂点バッファをデータストリーム
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer1, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_player.bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePlayer1);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				0,                                     //描画する最初の頂点インデックス
				2);                                    //描画するプリミティブ数
		}

	}
}
Player* GetPlayer(void)
{
	return &g_player;//プレイヤーの情報を返す
}
void HitPlayer(int nDamage)//あたりはんてぇ
{
	VERTEX_2D* pVtx;
	g_player.nLife -= nDamage;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)//死んだ
	{
		//bakuhatu

		g_player.bUse = false;

		g_player.bDisp = false;

		g_player.nCntAnimState = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;

	}
	else//死んでない
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 5;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0,0, 255);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer1->Unlock();

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	//if (g_player.nLife > 0)
	//{
	//	g_player.bHit = true;

	//	//頂点カラーの設定
	//	pVtx[0].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//	pVtx[1].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//	pVtx[2].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//	pVtx[3].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//}
	//else
	//{
	//	g_player.bUse = false;
	//}

	////頂点バッファをアンロックする
	//g_pVtxBuffPlayer1->Unlock();

}