//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "enemy.h"
#include "bullet.h"
#include "sound.h"
#include "score.h"
#include "player.h"

//�}�N��
#define NUM_ENEMY (3)//�G�̎��

//gu-baru
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
Enemy g_aEnemy[MAX_ENEMY];
int g_nNumEnemy = 0;//�G�̑���

void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//�e�N�X�`���̓ǂݍ���4�̕�
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy.png",      //�e�N�X�`���̃t�@�C����
		&g_apTextureEnemy[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy1.png",      //�e�N�X�`���̃t�@�C����
		&g_apTextureEnemy[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enemy.png",      //�e�N�X�`���̃t�@�C����
		&g_apTextureEnemy[2]);

	g_nNumEnemy = 0;

	//�G�̏��̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].BulletCounter = 0;//�e�J�E���^�[
		g_aEnemy[nCntEnemy].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
		g_aEnemy[nCntEnemy].nCounterState = 0;
	}

	//���_�o�b�t�@�̐����E���_���W�̐ݒ�
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x - 25.0f, g_aEnemy[NUM_ENEMY].pos.y - 25.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x + 25.0f, g_aEnemy[NUM_ENEMY].pos.y - 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x - 25.0f, g_aEnemy[NUM_ENEMY].pos.y + 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[NUM_ENEMY].pos.x + 25.0f, g_aEnemy[NUM_ENEMY].pos.y + 25.0f, 0.0f);

		//�G�̏����ʒu
		//g_aEnemy[NUM_ENEMY].pos = D3DXVECTOR3(500.0f,500.0f,0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//0.0�`1.0�Őݒ�
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}
void UninitEnemy(void)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�e�N�X�`���̔j��

		//���_�o�b�t�@�̔j��
		//�e�N�X�`���̔j��
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
		//���_�o�b�t�@�̔j��
		if (g_pVtxBuffEnemy != NULL)
		{
			g_pVtxBuffEnemy->Release();
			g_pVtxBuffEnemy = NULL;
		}
		break;
	}
}
void UpdateEnemy(void)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nCntEnemy;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:

				g_aEnemy[nCntEnemy].BulletCounter++;//�J�E���^�[�����Z
				if (g_aEnemy[nCntEnemy].BulletCounter >= 45)//��莞�Ԍo�߂���
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-15.0f, 0.0f, 0.0f), BULLETTYPE_ENEMY);
					//SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(-15.0f, 0.0f, 0.0f), BULLETTYPE_ENEMY);
					g_aEnemy[nCntEnemy].BulletCounter = 0;//�J�E���^�[�������l�ɖ߂�
				}
				break;
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState<=0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//0.0�`1.0�Őݒ�
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				}
				break;
			}
		}					
		pVtx += 4;
	}					
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�g�p����Ă�
			int nType = g_aEnemy[nCntEnemy].nType;

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntEnemy*4,						   //�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									   //�`�悷��v���~�e�B�u��
		}
	}

}
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D* pVtx=0;//���_���ւ̃|�C���^
	int nCntEnemy;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�G�̏��̐ݒ�
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nLife = 3;
			//g_aEnemy[nCntEnemy].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
			
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30.0f, g_aEnemy[nCntEnemy].pos.y - 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30.0f, g_aEnemy[nCntEnemy].pos.y - 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30.0f, g_aEnemy[nCntEnemy].pos.y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30.0f, g_aEnemy[nCntEnemy].pos.y + 30.0f, 0.0f);
			
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);//0.0�`1.0�Őݒ�
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			g_aEnemy[nCntEnemy].BulletCounter = 0;
			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;//�G�̑����J�E���g�_�E��

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

}
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];//�G�̏��̐擪�A�h���X��Ԃ�
}
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx=0;//���_���ւ̃|�C���^

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{

		//�T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_EXPLOSION);
		//bakuhatu
		g_aEnemy[nCntEnemy].bUse = false;
		g_nNumEnemy--;//�G�̑����J�E���g�_�E��
		//�X�R�A�̉��Z
		AddScore(200);
		//if (g_nNumEnemy <= 0)
		//{
		//	//���[�h�ݒ�(���U���g)
		//	SetMode(MODE_RESULT);
		//}
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;
		
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * nCntEnemy;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);//0.0�`1.0�Őݒ�
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();

	}

}

int GetNumEnemy()
{
	return g_nNumEnemy;
}
