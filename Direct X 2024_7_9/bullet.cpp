//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "bullet.h"
#include "player.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"

//�}�N��
#define MAX_BULLET (512)//�e�̍ő吔 

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//�p�x
	int nLife;//����
	BULLETTYPE type;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
	float fAngle;//
	float fLength;//
}Bullet;

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];//�e�̏��

void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\Bullet1.png",      //�e�N�X�`���̃t�@�C����
	&g_pTextureBullet);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}
	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);//0.0�`1.0�Őݒ�
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_2D* pVtx=0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���


			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				Enemy* pEnemy;//�G�̏��ւ̃|�C���^
				int nCntEnemy;

				//�G�̎擾
				pEnemy = GetEnemy();

				//�����̃J�E���g�_�E��
				g_aBullet[nCntBullet].nLife -= 1;

				SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, g_aBullet[nCntBullet].nLife);
				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 5.0f, g_aBullet[nCntBullet].nLife);

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{//�v���C���[���g�p����Ă���
						if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x-50.0f && g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + 50.0f && g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y-50.0f&& g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + 50.0f)//�v���C���[�ƒe����������
						{
							//�����̐ݒ�
							//SetExplosion();//�ʒu,�F

							//�G�̃q�b�g����
							HitEnemy(nCntEnemy,1);

							//pEnemy->bUse = false;//�G���g�p���Ă��Ȃ���Ԃɂ���

							g_aBullet[nCntBullet].bUse = false;//�e���g�p���Ă��Ȃ���Ԃɂ���

						}
					}
				}

			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				Player* pPlayer;//�v���C���[�̏��ւ̃|�C���^

				//�v���C���[�̎擾
				pPlayer = GetPlayer();

				//�����̃J�E���g�_�E��
				g_aBullet[nCntBullet].nLife -= 2;

				//SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, g_aBullet[nCntBullet].nLife);

					if (pPlayer->bUse == true)
					{//�v���C���[���g�p����Ă���
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x-HABA
							&& g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + HABA
							&& g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - TAKASA
							&& g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + TAKASA)//�G�ƒe����������
						{
							//�����̐ݒ�
							//SetExplosion();//�ʒu,�F

							//pPlayer->bUse = false;//�G���g�p���Ă��Ȃ���Ԃɂ���
							HitPlayer(1);

							g_aBullet[nCntBullet].bUse = false;//�e���g�p���Ă��Ȃ���Ԃɂ���

						}
					}

			}

			//�e�̈ʒu�̍X�V
			//g_aBullet[nCntBullet].move.x += 1.0f;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);


			if (g_aBullet[nCntBullet].nLife<=0)//�������؂ꂽ
			{
				//�����̐ݒ�
				//SetExplosion(g_aBullet[nCntBullet].pos,D3DXVECTOR3(1.0f,1.0f,1.0f));


				g_aBullet[nCntBullet].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}

		}

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

}
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBullet;
	//VERTEX_2D* pVtx=0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���	
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBullet*4 , 2);
		}
		
	}
}
//�e�̐ݒ菈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_2D* pVtx=0;
	
	//���b�N
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = false;
			g_aBullet[nCntBullet].type = type;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 100;
			g_aBullet[nCntBullet].bUse = true;

			break;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�

	}

	//�A�����b�N
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();

}