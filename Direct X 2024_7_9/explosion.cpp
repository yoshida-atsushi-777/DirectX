//#include "explosion.h"
//#include "player.h"
//#include "main.h"
//
////�}�N��
//#define MAX_EXPLOSION (512)//�����̍ő吔
//
////�����\���̂̒�`
//typedef struct
//{
//	D3DXVECTOR3 pos;//�ʒu
//	D3DXVECTOR3 col;//�F
//	int nCounterAnim;//�A�j���[�V�����J�E���^�[
//	int nPatternAnim;//�A�j���[�V�����p�^�[��No.
//	bool bUse;//�g�p���Ă��邩�ǂ���
//}Explosion;
//
////�O���[�o��
//LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;     //�e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//���_�o�b�t�@�ւ̃|�C���^
//Explosion g_aExplosion[MAX_EXPLOSION];//�e�̏��
//
////�����̏���������
//void InitExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntExplosion;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//	"data\\TEXTURE\\explosion.png",      //�e�N�X�`���̃t�@�C����
//	&g_pTextureExplosion);
//
//	//�����̏��̏�����
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aExplosion[nCntExplosion].col = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//		g_aExplosion[nCntExplosion].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
//	}
//	//���_�o�b�t�@�̐ݒ�
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL);
//
//	VERTEX_2D* pVtx;
//
//	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x-5.0f, g_aExplosion[nCntExplosion].pos.y-5.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x+5.0f, g_aExplosion[nCntExplosion].pos.y-5.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x-5.0f, g_aExplosion[nCntExplosion].pos.y + 5.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x+5.0f, g_aExplosion[nCntExplosion].pos.y + 5.0f, 0.0f);
//
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//
//		//���_�J���[�̐ݒ�
//		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f,1.0f);//0.0�`1.0�Őݒ�
//		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`��
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffExplosion->Unlock();
//}
//void UninitExplosion(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_pTextureExplosion != NULL)
//	{
//		g_pTextureExplosion->Release();
//		g_pTextureExplosion = NULL;
//	}
//
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffExplosion != NULL)
//	{
//		g_pVtxBuffExplosion->Release();
//		g_pVtxBuffExplosion = NULL;
//	}
//}
//void UpdatePlosion(void)
//{
//	int nCntExplosion;
//	VERTEX_2D* pVtx=0;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntExplosion].bUse == true)
//		{//�e���g�p����Ă���
//
//
//
//			g_aExplosion[nCntExplosion].nCounterAnim++;//�J�E���^�[�����Z
//			if (g_aExplosion[nCntExplosion].nCounterAnim>=8)//(g_aExplosion[MAX_EXPLOSION].nCounterAnim)%5==0)//��莞�Ԍo�߂���
//			{
//				g_aExplosion[nCntExplosion].nCounterAnim = 0;//�J�E���^�[�������l�ɖ߂�
//
//				g_aExplosion[nCntExplosion].nPatternAnim++;// = (g_nPatternAnimPlayer1+1)%10; //�p�^�[�����X�V����
//				
//				if (g_aExplosion[nCntExplosion].nPatternAnim>=10)//���p�^�[�����𒴂���
//				{
//					//g_nPatternAnimPlayer1 = g_nCounterAnimPlayer1 + 0.5f;;//�p�^�[��������������
//					g_aExplosion[nCntExplosion].nPatternAnim = 0;
//				}
//				
//			//	//�e�N�X�`�����W�̍X�V0.125
//			//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//				g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//			//	//�e�N�X�`�����W�̐ݒ�
//				pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1/5) * 0.5f);//(u,v)
//				pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f);//(u,v)
//				pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)
//				pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)
//
//				//���_�o�b�t�@���A�����b�N����
//				g_pVtxBuffExplosion->Unlock();
//			}
//
//			
//		}
//		if (g_aExplosion[MAX_EXPLOSION].nPatternAnim >= 8)//���p�^�[�����𒴂���
//		{
//			g_aExplosion[nCntExplosion].bUse = false;
//		}
//		//�e�N�X�`�����W�̍X�V
//
//		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffExplosion->Unlock();
//
//}
//void DrawExplosion(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
//	int nCntExplosion;
//	//VERTEX_2D* pVtx=0;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[��
//	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pTextureExplosion);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aBullet[nCntBullet].bUse == true)
//		{//�e���g�p����Ă���	
//			//�|���S���̕`��
//			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCntBullet*4 , 2);
//		}
//		
//	}
//}
////�e�̐ݒ菈��
//void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 col)
//{
//	int nCntExplosion;
//	VERTEX_2D* pVtx=0;
//	
//	//���b�N
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
//	{
//		if (g_aExplosion[nCntBullet].bUse == false)
//		{//�������g�p����Ă��Ȃ�
//			g_aBullet[nCntExplosion].pos = pos;
//			g_aBullet[nCntExplosion].nLife = 100;
//			g_aBullet[nCntExplosion].bUse = false;
//
//
//			//���_���W�̐ݒ�
//			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y - 5.0f, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 5.0f, g_aBullet[nCntBullet].pos.y + 5.0f, 0.0f);
//
//			//pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
//			//pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
//			//pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
//			//pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
//
//
//			g_aBullet[nCntBullet].move = move;
//			g_aBullet[nCntBullet].nLife = 100;
//			g_aBullet[nCntBullet].bUse = true;
//
//			break;
//		}
//		pVtx += 4;//���_�f�[�^�̃|�C���^���S���i�߂�
//
//	}
//
//	//�A�����b�N
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffBullet->Unlock();
//
//}