#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//�}�N��
#define MAX_NUM_SCORE (8)

//�v���g
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void SetScore(int nScore);
void AddScore(int nValue);
int ScoreCounter(int nScore);


#endif // !_SCORE_H_
