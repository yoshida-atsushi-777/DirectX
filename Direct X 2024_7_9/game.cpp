//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "game.h"
#include "input.h"
#include "background.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "score.h"
#include "effect.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureGame = { NULL };//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGame = NULL;//���_�o�b�t�@�ւ̃|�C���^
GAMESTATE g_gameState=GAMESTATE_NONE;//�Q�[���̏��
int g_nCounterGameState = 0;//��ԊǗ��J�E���^�[

void InitGame(void)
{
	//�e��I�u�W�F�N�g�̏���������

	//�w�i�̏���������
	InitBackGround();
	//�v���C���[�̏���������
	InitPlayer();
	//�e�̏���������
	InitBullet();
	//�G�t�F�N�g�̏�����
	InitEffect();
	//�G�̏�����
	InitEnemy();

	InitScore();
	SetScore(0);

	SetEnemy(D3DXVECTOR3(1200.0f, 200.0f, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(1200.0f, 500.0f, 0.0f), 0);

	g_gameState = GAMESTATE_NORMAL;//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;
}
void UninitGame(void)
{
	//�e��I�u�W�F�N�g�̏I������
	
	//�w�i�̏I������
	UninitBackGround();
	//�v���C���[�̏I������
	UninitPlayer();
	//�e�̏I������
	UninitBullet();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//�G�̏I������
	UninitEnemy();
	//�X�R�A�̏I������
	UninitScore();
}
void UpdateGame(void)
{
	int nNum;

	//�e��I�u�W�F�N�g�̍X�V����
	//�w�i�̍X�V����
	UpdateBackGround();
	//�v���C���[�̍X�V����
	UpdatePlayer();
	//�G�̍X�V����
	UpdateEnemy();
	//�e�̍X�V����
	UpdateBullet();
	//�G�t�F�N�g�̍X�V����
	UpdateEffect();
	//�X�R�A�̍X�V����
	UpdateScore();

	Player* pPlayer = GetPlayer();	
	nNum = GetNumEnemy();

	if (pPlayer->bUse == false || nNum <= 0)
	{
		//���(���[�h)�̐ݒ�
		g_gameState = GAMESTATE_END;
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;
	case GAMESTATE_END://�I�����
		g_nCounterGameState++;
		if (g_nCounterGameState >= 60 && nNum <= 0)
		{
			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
			SetFade(MODE_RESULT);
			//���(���[�h)�̐ݒ�
			//SetMode(MODE_RESULT);
		}
		else if (g_nCounterGameState >= 60 && pPlayer->bUse == false)
		{
			g_nCounterGameState = 0;

			g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
			SetFade(MODE_RESULT_LOSE);
			//���(���[�h)�̐ݒ�
			//SetMode(MODE_RESULT);
		}
		break;
	}

}
void DrawGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	//�w�i�̕`�揈��
	DrawBackGround();
	//�e�̕`�揈��
	DrawBullet();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//�G�̕`�揈��
	DrawEnemy();
	//�G�t�F�N�g�̕`�揈��
	DrawEffect();
	//�X�R�A�̕`�揈��
	DrawScore();

}
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	//g_nCounterGameState = 0;
}
GAMESTATE GetGameState(void)
{
	return g_gameState;
}