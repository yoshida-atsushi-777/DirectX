#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�e�̎��
typedef enum
{
	BULLETTYPE_PLAYER=0,//�v���C���[�̒e
	BULLETTYPE_ENEMY,//�G�̒e
	BULLETTYPE_MAX
}BULLETTYPE;

//�v���g
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move ,BULLETTYPE type);//, D3DXVECTOR3 rot, float fLength);//���ˈʒu�ƈړ���
#endif