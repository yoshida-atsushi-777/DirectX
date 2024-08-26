//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "bullet.h"
#include "player.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"

//マクロ
#define MAX_BULLET (512)//弾の最大数 

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 rot;//角度
	int nLife;//寿命
	BULLETTYPE type;//種類
	bool bUse;//使用しているかどうか
	float fAngle;//
	float fLength;//
}Bullet;

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];//弾の情報

void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\Bullet1.png",      //テクスチャのファイル名
	&g_pTextureBullet);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;//使用していない状態にする
	}
	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);//0.0～1.0で設定
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める

	}
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D* pVtx=0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている


			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				Enemy* pEnemy;//敵の情報へのポインタ
				int nCntEnemy;

				//敵の取得
				pEnemy = GetEnemy();

				//寿命のカウントダウン
				g_aBullet[nCntBullet].nLife -= 1;

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, g_aBullet[nCntBullet].nLife);
				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, g_aBullet[nCntBullet].nLife);

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{//プレイヤーが使用されている
						if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x-50.0f && g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + 50.0f && g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y-50.0f&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + 50.0f)//プレイヤーと弾が当たった
						{
							//爆発の設定
							//SetExplosion();//位置,色

							//敵のヒット処理
							HitEnemy(nCntEnemy,1);

							//pEnemy->bUse = false;//敵を使用していない状態にする

							g_aBullet[nCntBullet].bUse = false;//弾を使用していない状態にする

						}
					}
				}

			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				Player* pPlayer;//プレイヤーの情報へのポインタ

				//プレイヤーの取得
				pPlayer = GetPlayer();

				//寿命のカウントダウン
				g_aBullet[nCntBullet].nLife -= 2;

				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, g_aBullet[nCntBullet].nLife);

					if (pPlayer->bUse == true)
					{//プレイヤーが使用されている
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x-HABA
							&& g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + HABA
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - TAKASA
							&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + TAKASA)//敵と弾が当たった
						{
							//爆発の設定
							//SetExplosion();//位置,色

							//pPlayer->bUse = false;//敵を使用していない状態にする
							HitPlayer(1);

							g_aBullet[nCntBullet].bUse = false;//弾を使用していない状態にする

						}
					}

			}

			//弾の位置の更新
			//g_aBullet[nCntBullet].move.x += 1.0f;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);


			if (g_aBullet[nCntBullet].nLife<=0)//寿命が切れた
			{
				//爆発の設定
				//SetExplosion(g_aBullet[nCntBullet].pos,D3DXVECTOR3(1.0f,1.0f,1.0f));


				g_aBullet[nCntBullet].bUse = false;//使用してない状態にする
			}

		}

		pVtx += 4;//頂点データのポインタを４つ分進める

	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

}
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBullet;
	//VERTEX_2D* pVtx=0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている	
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBullet*4 , 2);
		}
		
	}
}
//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D* pVtx=0;
	
	//ロック
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = false;
			g_aBullet[nCntBullet].type = type;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;

			break;
		}
		pVtx += 4;//頂点データのポインタを４つ分進める

	}

	//アンロック
	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();

}