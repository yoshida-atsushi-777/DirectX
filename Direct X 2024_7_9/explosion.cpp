//#include "explosion.h"
//#include "player.h"
//#include "main.h"
//
////マクロ
//#define MAX_EXPLOSION (512)//爆発の最大数
//
////爆発構造体の定義
//typedef struct
//{
//	D3DXVECTOR3 pos;//位置
//	D3DXVECTOR3 col;//色
//	int nCounterAnim;//アニメーションカウンター
//	int nPatternAnim;//アニメーションパターンNo.
//	bool bUse;//使用しているかどうか
//}Explosion;
//
////グローバル
//LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;     //テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//頂点バッファへのポインタ
//Explosion g_aExplosion[MAX_EXPLOSION];//弾の情報
//
////爆発の初期化処理
//void InitExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntExplosion;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//	"data\\TEXTURE\\explosion.png",      //テクスチャのファイル名
//	&g_pTextureExplosion);
//
//	//爆発の情報の初期化
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aExplosion[nCntExplosion].col = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//		g_aExplosion[nCntExplosion].bUse = false;//使用していない状態にする
//	}
//	//頂点バッファの設定
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL);
//
//	VERTEX_2D* pVtx;
//
//	//頂点バッファをロックし、頂点データへのポインタを取得
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		//頂点座標の設定
//		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x-5.0f, g_aExplosion[nCntExplosion].pos.y-5.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x+5.0f, g_aExplosion[nCntExplosion].pos.y-5.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x-5.0f, g_aExplosion[nCntExplosion].pos.y + 5.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x+5.0f, g_aExplosion[nCntExplosion].pos.y + 5.0f, 0.0f);
//
//		//rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//頂点カラーの設定
//		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f,1.0f);//0.0～1.0で設定
//		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//
//		//テクスチャ
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;//頂点データのポインタを４つ分進める
//	}
//
//	//頂点バッファをアンロック
//	g_pVtxBuffExplosion->Unlock();
//}
//void UninitExplosion(void)
//{
//	//テクスチャの破棄
//	if (g_pTextureExplosion != NULL)
//	{
//		g_pTextureExplosion->Release();
//		g_pTextureExplosion = NULL;
//	}
//
//	//頂点バッファの破棄
//	if (g_pVtxBuffExplosion != NULL)
//	{
//		g_pVtxBuffExplosion->Release();
//		g_pVtxBuffExplosion = NULL;
//	}
//}
//void UpdatePlosion(void)
//{
//	int nCntExplosion;
//	VERTEX_2D* pVtx=0;
//
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntExplosion].bUse == true)
//		{//弾が使用されている
//
//
//
//			g_aExplosion[nCntExplosion].nCounterAnim++;//カウンターを加算
//			if (g_aExplosion[nCntExplosion].nCounterAnim>=8)//(g_aExplosion[MAX_EXPLOSION].nCounterAnim)%5==0)//一定時間経過した
//			{
//				g_aExplosion[nCntExplosion].nCounterAnim = 0;//カウンターを初期値に戻す
//
//				g_aExplosion[nCntExplosion].nPatternAnim++;// = (g_nPatternAnimPlayer1+1)%10; //パターンを更新する
//				
//				if (g_aExplosion[nCntExplosion].nPatternAnim>=10)//総パターン数を超えた
//				{
//					//g_nPatternAnimPlayer1 = g_nCounterAnimPlayer1 + 0.5f;;//パターンを初期化する
//					g_aExplosion[nCntExplosion].nPatternAnim = 0;
//				}
//				
//			//	//テクスチャ座標の更新0.125
//			//	//頂点バッファをロックし、頂点情報へのポインタを取得
//				g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//			//	//テクスチャ座標の設定
//				pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1/5) * 0.5f);//(u,v)
//				pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f);//(u,v)
//				pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)
//				pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)
//
//				//頂点バッファをアンロックする
//				g_pVtxBuffExplosion->Unlock();
//			}
//
//			
//		}
//		if (g_aExplosion[MAX_EXPLOSION].nPatternAnim >= 8)//総パターン数を超えた
//		{
//			g_aExplosion[nCntExplosion].bUse = false;
//		}
//		//テクスチャ座標の更新
//
//		pVtx += 4;//頂点データのポインタを４つ分進める
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffExplosion->Unlock();
//
//}
//void DrawExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
//	int nCntExplosion;
//	//VERTEX_2D* pVtx=0;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点バッファをデータストリーム
//	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャの設定
//	pDevice->SetTexture(0, g_pTextureExplosion);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aBullet[nCntBullet].bUse == true)
//		{//弾が使用されている	
//			//ポリゴンの描画
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBullet*4 , 2);
//		}
//		
//	}
//}
////弾の設定処理
//void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 col)
//{
//	int nCntExplosion;
//	VERTEX_2D* pVtx=0;
//	
//	//ロック
//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntBullet].bUse == false)
//		{//爆発が使用されていない
//			g_aBullet[nCntExplosion].pos = pos;
//			g_aBullet[nCntExplosion].nLife = 100;
//			g_aBullet[nCntExplosion].bUse = false;
//
//
//			//頂点座標の設定
//			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
//
//			//pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
//			//pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
//			//pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
//			//pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
//
//
//			g_aBullet[nCntBullet].move = move;
//			g_aBullet[nCntBullet].nLife = 100;
//			g_aBullet[nCntBullet].bUse = true;
//
//			break;
//		}
//		pVtx += 4;//頂点データのポインタを４つ分進める
//
//	}
//
//	//アンロック
//	//頂点バッファをアンロック
//	g_pVtxBuffBullet->Unlock();
//
//}