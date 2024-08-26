#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

typedef enum
{
	GAMESTATE_NONE = 0,//�������Ă��Ȃ����
	GAMESTATE_NORMAL,//�ʏ��ԁi�Q�[���i�s���j
	GAMESTATE_END,//�I����ԁi�G�S�ŁA�v���C���[���A�^�C���I�[�o�[�Ȃǁj
	GAMESTATE_MAX
}GAMESTATE;

//�}�N��
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);


#endif // !1