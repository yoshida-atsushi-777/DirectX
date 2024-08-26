//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _PLAYER_H_//このマクロ定義がされてなかったら
#define _PLAYER_H_//２重インクルード防止のマクロ定義

#define HABA (70.0f)//幅
#define TAKASA (50.0f)//高さ

//プレイヤーの状態2024/08/26
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//出現状態（点滅）
	PLAYERSTATE_NORMAL,//通常
	PLAYERSTATE_DAMAGE,//ダメージ
	PLAYERSTATE_DEATH,//脂肪
	PLAYERSTATE_MAX
}PLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;                         //位置
	D3DXVECTOR3 move;                        //移動量
	PLAYERSTATE state;                       //プレイヤーの状態
	int nCounterState;                       //状態管理カウンター
	bool bDisp;                              //表示するかしないか
	D3DXVECTOR3 rot;						 //向き
	D3DXVECTOR3 Bullet;						 //弾の速さ
	float Length;                           //対角線の長さ
	float Angle;                            //対角線の角度
	bool bUse;
	bool bHit;                              //あたりはんてぇ
	int nCntAnimState;                      //状態をカウント
	int nLife;                              //命
	int nZanki;                             //残機
}Player;

//プロト
void InitBackGround(void);
void UninitBackGround(void);
void UpdateBackGround(void);
void DrawBackGround(void);
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);//あたりはんてぇ


#endif