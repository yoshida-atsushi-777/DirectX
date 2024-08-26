//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "effect.h"
#include "player.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "sound.h"

//�}�N��
#define MAX_EFFECT (4096)//�e�̍ő吔 

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;//�ړ���
	float fRadius;
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
}Effect;

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;     //�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];//�e�̏��

void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\effect000.jpg",      //�e�N�X�`���̃t�@�C����
	&g_pTextureEffect);

	//�e�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 0.3f;
		g_aEffect[nCntEffect].nLife = 50;
		g_aEffect[nCntEffect].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}
	//���_�o�b�t�@�̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL);

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f, g_aEffect[nCntEffect].pos.y - 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f, g_aEffect[nCntEffect].pos.y - 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f, g_aEffect[nCntEffect].pos.y + 5.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f, g_aEffect[nCntEffect].pos.y + 5.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//0.0�`1.0�Őݒ�
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_2D* pVtx=0;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x-10.0f, g_aEffect[nCntEffect].pos.y - 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x+10.0f, g_aEffect[nCntEffect].pos.y - 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x-10.0f, g_aEffect[nCntEffect].pos.y + 10.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x+10.0f, g_aEffect[nCntEffect].pos.y + 10.0f, 0.0f);
			
			//�����̃J�E���g�_�E��
   			g_aEffect[nCntEffect].nLife -= 1;

			if (g_aEffect[nCntEffect].nLife<=0)//�������؂ꂽ
			{
				g_aEffect[nCntEffect].bUse = false;//�g�p���ĂȂ���Ԃɂ���
			}
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

}
//�G�t�F�N�g�̕`��
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntEffect;
	//VERTEX_2D* pVtx=0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�e���g�p����Ă���	
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntEffect*4 , 2);
		}
		
	}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
//�G�t�F�N�g�̐ݒ菈��
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_2D* pVtx=0;
	
	//���b�N
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aEffect[nCntEffect].fRadius = fRadius;

			g_aEffect[nCntEffect].pos = pos;
			
			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f+fRadius, g_aEffect[nCntEffect].pos.y - 5.0f+fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f-fRadius, g_aEffect[nCntEffect].pos.y - 5.0f+fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 5.0f+fRadius, g_aEffect[nCntEffect].pos.y + 5.0f-fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 5.0f-fRadius, g_aEffect[nCntEffect].pos.y + 5.0f-fRadius, 0.0f);
			
			g_aEffect[nCntEffect].col = col;

			//���_�J���[�̐ݒ�
			pVtx[0].col = col;//0.0�`1.0�Őݒ�
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			
			g_aEffect[nCntEffect].nLife = nLife;
			
			g_aEffect[nCntEffect].bUse = true;

			break;
		}
		pVtx += 4;
	}

	//�A�����b�N
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}