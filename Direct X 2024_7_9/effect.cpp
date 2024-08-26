//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "effect.h"
#include "player.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"

//マクロ
#define MAX_EFFECT (4096)//弾の最大数 

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;//移動量
	float fRadius;
	int nLife;//寿命
	bool bUse;//使用しているかどうか
}Effect;

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;     //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];//弾の情報

void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\effect000.jpg",      //テクスチャのファイル名
	&g_pTextureEffect);

	//弾の情報の初期化
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.3f;
		g_aEffect[nCntEffect].nLife = 50;
		g_aEffect[nCntEffect].bUse = false;//使用していない状態にする
	}
	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f, g_aEffect[nCntEffect].pos.y - 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f, g_aEffect[nCntEffect].pos.y - 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f, g_aEffect[nCntEffect].pos.y + 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f, g_aEffect[nCntEffect].pos.y + 5.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//0.0～1.0で設定
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを４つ分進める

	}
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_2D* pVtx=0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//エフェクトが使用されている

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x-10.0f, g_aEffect[nCntEffect].pos.y - 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x+10.0f, g_aEffect[nCntEffect].pos.y - 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x-10.0f, g_aEffect[nCntEffect].pos.y + 10.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x+10.0f, g_aEffect[nCntEffect].pos.y + 10.0f, 0.0f);
			
			//寿命のカウントダウン
   			g_aEffect[nCntEffect].nLife -= 1;

			if (g_aEffect[nCntEffect].nLife<=0)//寿命が切れた
			{
				g_aEffect[nCntEffect].bUse = false;//使用してない状態にする
			}
		}
		pVtx += 4;//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();

}
//エフェクトの描画
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntEffect;
	//VERTEX_2D* pVtx=0;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEffect);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//弾が使用されている	
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntEffect*4 , 2);
		}
		
	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//エフェクトの設定処理
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_2D* pVtx=0;
	
	//ロック
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//弾が使用されていない
			g_aEffect[nCntEffect].fRadius = fRadius;

			g_aEffect[nCntEffect].pos = pos;
			
			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f+fRadius, g_aEffect[nCntEffect].pos.y - 5.0f+fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f-fRadius, g_aEffect[nCntEffect].pos.y - 5.0f+fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f+fRadius, g_aEffect[nCntEffect].pos.y + 5.0f-fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f-fRadius, g_aEffect[nCntEffect].pos.y + 5.0f-fRadius, 0.0f);
			
			g_aEffect[nCntEffect].col = col;

			//頂点カラーの設定
			pVtx[0].col = col;//0.0～1.0で設定
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			
			g_aEffect[nCntEffect].nLife = nLife;
			
			g_aEffect[nCntEffect].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//アンロック
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}