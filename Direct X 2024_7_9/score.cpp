//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "score.h"

typedef struct
{
	bool buse;
	int nCountScoreCounter;
}Score;


//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureScore = { NULL };//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;//�X�R�A�̈ʒu
int g_nScore;//�X�R�A�̒l
Score g_aScore[MAX_NUM_SCORE];

void InitScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��1�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",//�e�N�X�`���̃t�@�C����
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(0.0f ,0.0f ,0.0f);

	g_nScore = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < 8; nCntScore++)
	{

		bool buse = true;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f + 30.0f , 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f, 30.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(900.0f + nCntScore * 30.0f + 30.0f, 30.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);//(u,v)

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();


}
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	{
	if (g_pTextureScore != NULL)
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��

	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

}
void UpdateScore(void)
{
	int nData;
	int nData1 = 0;

	nData = ScoreCounter(g_nScore);
	for (nData1 = 0; nData1 < MAX_NUM_SCORE; nData1++)
	{
		if (nData1 >= MAX_NUM_SCORE - nData)
		{
			g_aScore[nData1].buse = true;
		}
		else
		{
			g_aScore[nData1].buse = false;
		}
	}
}
void DrawScore(void)
{

	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[��
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		if (g_aScore[nCntScore].buse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureScore);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntScore * 4,						   //�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									   //�`�悷��v���~�e�B�u��
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//�ݒ菈��
void SetScore(int nScore)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int aPosTexU[MAX_NUM_SCORE];//�e���̐������i�[
	int n = 10000000;
	int n1 = 1000000;

	g_nScore = nScore;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		if (aPosTexU[nCntScore] == aPosTexU[0])
		{
			aPosTexU[0] = g_nScore / n;
		}
		else
		{
			aPosTexU[nCntScore] = g_nScore % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}


		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

}
void AddScore(int nValue)
{
	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
	int nCntScore;
	int aPosTexU[MAX_NUM_SCORE];//�e���̐������i�[
	int n = 10000000;
	int n1 = 1000000;
	
   	g_nScore += nValue;//�G���

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

   	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		aPosTexU[nCntScore] = 0;
		if (aPosTexU[nCntScore] == aPosTexU[0])
		{
			aPosTexU[0] = g_nScore / n;
		}
		else
		{
			aPosTexU[nCntScore] = g_nScore % n / n1;
			n = n / 10;
			n1 = n1 / 10;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 0.0f);//(u,v)
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCntScore]), 1.0f);//(u,v)

		pVtx += 4;

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

}
//=====================
//�X�R�A��0���J�E���g
//=====================
int  ScoreCounter(int nScore)
{
	int nNum = nScore;//�X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;//�X�R�A�̌���

	while (nNum != 0)//����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�(�O�܂�)
	{
		nNum /= 10;//nNum��10�Ŋ����Ă���
		nKeepNum++;//���������Z

	}
	if (nScore == 0)
	{
		//1���ڂ�0�������Ă���Ƃ�
		nKeepNum = 1;
	}
	return nKeepNum;//�X�R�A�̌�����Ԃ�
}