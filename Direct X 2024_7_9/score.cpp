//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "score.h"

typedef struct
{
	bool buse;
	int nCountScoreCounter;
}Score;


//グローバル
LPDIRECT3DTEXTURE9 g_pTextureScore = { NULL };//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//頂点バッファへのポインタ
D3DXVECTOR3 g_posScore;//スコアの位置
int g_nScore;//スコアの値
Score g_aScore[MAX_NUM_SCORE];

void InitScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ1の読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",//テクスチャのファイル名
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(0.0f ,0.0f ,0.0f);

	g_nScore = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{

		bool buse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f + 30.0f , 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f, 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f + 30.0f, 30.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);//(u,v)

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();


}
void UninitScore(void)
{
	//テクスチャの破棄
	{
	if (g_pTextureScore != NULL)
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄

	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

}
void UpdateScore(void)
{
	int nData;
	int nData1 = 0;

	nData = ScoreCounter(g_nScore);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aScore[nData1].buse = true;
		}
		else
		{
			g_aScore[nData1].buse = false;
		}
	}
}
void DrawScore(void)
{

	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリーム
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		if (g_aScore[nCntScore].buse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureScore);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntScore * 4,						   //描画する最初の頂点インデックス
				2);									   //描画するプリミティブ数
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//設定処理
void SetScore(int nScore)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int aPosTexU[MAX_NUM_SCORE];//各桁の数字を格納
	int n = 10000000;
	int n1 = 1000000;

	g_nScore = nScore;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		if (aPosTexU[nCntScore] == aPosTexU[0])
		{
			aPosTexU[0] = g_nScore / n;
		}
		else
		{
			aPosTexU[nCntScore] = g_nScore % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}


		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

}
void AddScore(int nValue)
{
	VERTEX_2D* pVtx = 0;//頂点情報へのポインタ
	int nCntScore;
	int aPosTexU[MAX_NUM_SCORE];//各桁の数字を格納
	int n = 10000000;
	int n1 = 1000000;
	
   	g_nScore += nValue;//敵一体

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

   	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		aPosTexU[nCntScore] = 0;
		if (aPosTexU[nCntScore] == aPosTexU[0])
		{
			aPosTexU[0] = g_nScore / n;
		}
		else
		{
			aPosTexU[nCntScore] = g_nScore % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)

		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

}
//=====================
//スコアの0をカウント
//=====================
int  ScoreCounter(int nScore)
{
	int nNum = nScore;//スコアの０の部分をカウント
	int nKeepNum = 0;//スコアの桁数

	while (nNum != 0)//割り切れなくなるまで繰り返す(０まで)
	{
		nNum /= 10;//nNumを10で割っていく
		nKeepNum++;//桁数を加算

	}
	if (nScore == 0)
	{
		//1桁目に0が入っているとき
		nKeepNum = 1;
	}
	return nKeepNum;//スコアの桁数を返す
}