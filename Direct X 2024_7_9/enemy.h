#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//maku
#define MAX_ENEMY (128)//tekimax

//�G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//�ʏ�
	ENEMYSTATE_DAMAGE,//�_���[�W
	ENEMYSTATE_MAX
}ENEMYSTATE;

//�G�̎��
//typedef enum
//{
//	ENEMYTYPE_1=0,
//	ENEMYTYPE_2,
//	ENEMYTYPE_3,
//	ENEMYTYPE_MAX
//}ENEMYTYPE;

//kouzou
typedef struct
{
	D3DXVECTOR3 pos;//iti
	int nType;//syurui
	ENEMYSTATE state;//joutai
	int nCounterState;//joutaicounter
	int nLife;//tairyoku
	bool bUse;//siyou
	int BulletCounter;//�e�J�E���^�[
}Enemy;


//puroto
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
Enemy *GetEnemy(void);
void HitEnemy(int nCntEnemy, int nDamage);
int GetNumEnemy();

#endif // !_ENEMY_H_