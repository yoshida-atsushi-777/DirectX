#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//�v���g
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col  ,float fRadius,int nLife);//, D3DXVECTOR3 rot, float fLength);//���ˈʒu�ƈړ���
#endif