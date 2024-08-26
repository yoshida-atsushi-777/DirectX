//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "enemy.h"
#include "bullet.h"
#include "sound.h"
#include "score.h"
#include "player.h"

//マクロ
#define NUM_ENEMY (3)//敵の種類

//gu-baru
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];
int g_nNumEnemy = 0;//敵の総数

void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;
	
	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//テクスチャの読み込み4体分
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy.png",      //テクスチャのファイル名
		&g_apTextureEnemy[0]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy1.png",      //テクスチャのファイル名
		&g_apTextureEnemy[1]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy.png",      //テクスチャのファイル名
		&g_apTextureEnemy[2]);

	g_nNumEnemy = 0;

	//敵の情報の初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].BulletCounter = 0;//弾カウンター
		g_aEnemy[nCntEnemy].bUse = false;//使用していない状態にする
		g_aEnemy[nCntEnemy].nCounterState = 0;
	}

	//頂点バッファの生成・頂点座標の設定
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x - 25.0f, g_aEnemy[NUM_ENEMY].pos.y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x + 25.0f, g_aEnemy[NUM_ENEMY].pos.y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x - 25.0f, g_aEnemy[NUM_ENEMY].pos.y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x + 25.0f, g_aEnemy[NUM_ENEMY].pos.y + 25.0f, 0.0f);

		//敵の初期位置
		//g_aEnemy[NUM_ENEMY].pos = D3DXVECTOR3(500.0f,500.0f,0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//0.0～1.0で設定
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

}
void UninitEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//テクスチャの破棄

		//頂点バッファの破棄
		//テクスチャの破棄
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
		//頂点バッファの破棄
		if (g_pVtxBuffEnemy != NULL)
		{
			g_pVtxBuffEnemy->Release();
			g_pVtxBuffEnemy = NULL;
		}
		break;
	}
}
void UpdateEnemy(void)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nCntEnemy;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:

				g_aEnemy[nCntEnemy].BulletCounter++;//カウンターを加算
				if (g_aEnemy[nCntEnemy].BulletCounter >= 45)//一定時間経過した
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-15.0f, 0.0f, 0.0f), BULLETTYPE_ENEMY);
					//SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-15.0f, 0.0f, 0.0f), BULLETTYPE_ENEMY);
					g_aEnemy[nCntEnemy].BulletCounter = 0;//カウンターを初期値に戻す
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState<=0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//0.0～1.0で設定
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				}
				break;
			}
		}					
		pVtx += 4;
	}					
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//使用されてる
			int nType = g_aEnemy[nCntEnemy].nType;

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntEnemy*4,						   //描画する最初の頂点インデックス
				2);									   //描画するプリミティブ数
		}
	}

}
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D* pVtx=0;//頂点情報へのポインタ
	int nCntEnemy;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//敵の情報の設定
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nLife = 3;
			//g_aEnemy[nCntEnemy].bUse = false;//使用していない状態にする
			
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30.0f, g_aEnemy[nCntEnemy].pos.y - 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30.0f, g_aEnemy[nCntEnemy].pos.y - 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30.0f, g_aEnemy[nCntEnemy].pos.y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30.0f, g_aEnemy[nCntEnemy].pos.y + 30.0f, 0.0f);
			
			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//0.0～1.0で設定
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			g_aEnemy[nCntEnemy].BulletCounter = 0;
			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;//敵の総数カウントダウン

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

}
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];//敵の情報の先頭アドレスを返す
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx=0;//頂点情報へのポインタ

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{

		//サウンドの再生
		PlaySound(SOUND_LABEL_EXPLOSION);
		//bakuhatu
		g_aEnemy[nCntEnemy].bUse = false;
		g_nNumEnemy--;//敵の総数カウントダウン
		//スコアの加算
		AddScore(200);
		//if (g_nNumEnemy <= 0)
		//{
		//	//モード設定(リザルト)
		//	SetMode(MODE_RESULT);
		//}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		
		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntEnemy;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//0.0～1.0で設定
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();

	}

}

int GetNumEnemy()
{
	return g_nNumEnemy;
}
