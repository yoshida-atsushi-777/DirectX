//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#include "main.h"
#include "player.h"
#include "Input.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "fade.h"

//�}�N��
#define MAX_MAX (400.0f)//�ő�ł���
#define MAX_MIN (10.0f)//�ŏ���������

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTexturePlayer1 = NULL;     //�e�N�X�`��2�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer1 = NULL;//���_�o�b�t�@2�ւ̃|�C���^
Player g_player;                                 //���C���[�̏��

//�v���C���[�̏���������
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;                   //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`��2�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Player.png",      //�e�N�X�`���̃t�@�C����
		&g_pTexturePlayer1);


	//g_nCounterAnimPlayer1 = 0;                   //�J�E���^�[������������

	//g_nPatternAnimPlayer1 = 0;                   //�p�^�[��No.������������


	g_player.pos = D3DXVECTOR3(100.0f,360.0f,0.0f);//�ʒu������������

	g_player.move = D3DXVECTOR3(0.0f,0.0f,0.0f);  //�ړ��ʂ�����������

	g_player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f); //����������������A�����Z���i3�Ԗځj

	g_player.Bullet.x = 10.0f;

	g_player.Bullet.y = 10.0f;

	g_player.bUse = true;

	g_player.bDisp = true;

	g_player.nZanki = 3;

	g_player.bHit = false;

	g_player.nCntAnimState = 0;

	g_player.nLife = 5;

	//�Ίp���̒������Z�o����
	g_player.Length = sqrtf(50.0f * 50.0f + 100.0f * 100.0f) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_player.Angle = atan2f(HABA ,TAKASA);

	//���_�o�b�t�@2�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer1,
		NULL);

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�

	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y-60.0f, 0.0f);//pVtx[0].pos = D3DXVECTOR3(450.0f, 300.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y-60.0f, 0.0f);//pVtx[1].pos = D3DXVECTOR3(650.0f, 300.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y+60.0f, 0.0f);//pVtx[2].pos = D3DXVECTOR3(450.0f, 600.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y+60.0f, 0.0f);//pVtx[3].pos = D3DXVECTOR3(650.0f, 600.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//(u,v)
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//(u,v)
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//(u,v)

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer1->Unlock();
}
//�v���C���[�̏I������
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer1 != NULL)
	{
		g_pTexturePlayer1->Release();
		g_pTexturePlayer1 = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer1 != NULL)
	{
		g_pVtxBuffPlayer1->Release();
		g_pVtxBuffPlayer1 = NULL;
	}
}
//�v���C���[�̍X�V����
void UpdatePlayer(void)
{

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	if (g_player.bUse == true)
	{
		if (GetJoypadPress(JOYKEY_UP) == true)
		{//��L�[
			g_player.move.x += 0.0f;
			g_player.move.y -= 3.0f;
		}
		else if (GetJoypadPress(JOYKEY_DOWN) == true)
		{//���L�[
			g_player.move.x += 0.0f;
			g_player.move.y += 3.0f;

		}
		else if (GetJoypadPress(JOYKEY_LEFT) == true)
		{
			if (GetJoypadPress(JOYKEY_LEFT) == true && GetJoypadPress(JOYKEY_UP) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 3.0f;
			}
			else if (GetJoypadPress(JOYKEY_LEFT) == true && GetJoypadPress(JOYKEY_DOWN) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 3.0f;
			}
			else if (GetJoypadPress(JOYKEY_A) == true)
			{
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
			}
			else
			{
				//�ړ��ʂ��X�V�i�����j
				g_player.move.x -= 3.0f;
				g_player.move.y += 0.0f;
			}
		}
		else if (GetJoypadPress(JOYKEY_RIGHT) == true)
		{
			if (GetJoypadPress(JOYKEY_RIGHT) == true && GetJoypadPress(JOYKEY_UP) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 3.0f;
			}
			else if (GetJoypadPress(JOYKEY_RIGHT) == true && GetJoypadPress(JOYKEY_DOWN) == true)
			{
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 3.0f;
			}
			else
			{
				g_player.move.x += 3.0f;
				g_player.move.y += 0.0f;
			}
		}
		else if (GetJoypadPress(JOYKEY_START) == true)
		{

		}
		else if (GetJoypadPress(JOYKEY_A) == true)
		{
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
		}

		if (KeyboardRepeat(DIK_A) == true)
		{

			if (KeyboardRepeat(DIK_W) == true)
			{
				//�ړ��ʂ��X�V�i�����j
				g_player.move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.75f) * 3.0f;
				//W�L�[�������ꂽ�i���������j����Ɉړ�
				//g_player.pos.x += sinf(-D3DX_PI*0.75f) * g_player.move.x;//sinf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj
				//g_player.pos.y += cosf(-D3DX_PI*0.75f) * g_player.move.y;//cosf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj
			}
			else if (KeyboardRepeat(DIK_S) == true)
			{
				//�ړ��ʂ��X�V�i�����j
				g_player.move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(-D3DX_PI * 0.25f) * 3.0f;
				//S�L�[�������ꂽ�i���������j�����Ɉړ�
				//g_player.pos.x += sinf(-D3DX_PI*0.25f) * g_player.move.x;//sinf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj
				//g_player.pos.y += cosf(-D3DX_PI*0.25f) * g_player.move.y;//cosf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj

			}
			else if (KeyboardRepeat(DIK_LEFT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//�e�̐ݒ�
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z += 0.2f;
				}
				else
				{
					g_player.rot.z += 0.2f;
				}

			}
			else if (KeyboardRepeat(DIK_RIGHT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//�e�̐ݒ�
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z -= 0.2f;
				}
				else
				{
					g_player.rot.z -= 0.2f;
				}
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				//�ړ��ʂ��X�V�i�����j
				g_player.move.x -= 3.0f;
				g_player.move.y += 0.0f;
			}
			else
			{
				//�ړ��ʂ��X�V�i�����j
				g_player.move.x -= 3.0f;
				g_player.move.y += 0.0f;
				//A�L�[�������ꂽ���Ɉړ�
				//g_player.pos.x -= g_player.move.x;
			}



			//�ړ��ʂ��X�V�i�����j
			//g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
			//g_player.move.y += (0.0f - g_player.move.y) * 0.5f;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			//g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

			//�ʒu���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y - 60.0f, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y - 60.0f, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 100.0f, g_player.pos.y + 60.0f, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 100.0f, g_player.pos.y + 60.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			//g_pVtxBuffPlayer1->Unlock();
		}
		else if (KeyboardRepeat(DIK_D) == true)//|| KeyboardRelease(DIK_D)==true)
		{
			if (KeyboardRepeat(DIK_W) == true)
			{

				g_player.move.x += sinf(D3DX_PI * 0.75f) * 3.0f;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * 3.0f;
				//W�L�[�������ꂽ�i���������j�E��Ɉړ�
				//g_player.pos.x += sinf(D3DX_PI * 0.75f) * g_player.move.x;//sinf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj
				//g_player.pos.y += cosf(D3DX_PI * 0.75f) * g_player.move.y;//cosf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj


			}
			else if (KeyboardRepeat(DIK_S) == true)
			{
				g_player.move.x += sinf(D3DX_PI * 0.25f) * 3.0f;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * 3.0f;
				//S�L�[�������ꂽ�i���������j�E���Ɉړ�
				//g_player.pos.x += sinf(D3DX_PI*0.25f) * g_player.move.x;//sinf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj
				//g_player.pos.y += cosf(D3DX_PI*0.25f) * g_player.move.y;//cosf(�p�x[-3.14(������)~3.14�i�E���j])*�����i�ړ��ʁj

			}
			else if (KeyboardRepeat(DIK_LEFT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//�e�̐ݒ�
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z += 0.2f;
				}
				else
				{
					g_player.rot.z += 0.2f;
				}

			}
			else if (KeyboardRepeat(DIK_RIGHT) == true)
			{
				if (KeyboardTrigger(DIK_SPACE) == true)
				{//SPACE
					//�e�̐ݒ�
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
					g_player.rot.z -= 0.2f;
				}
				else
				{
					g_player.rot.z -= 0.2f;
				}
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.move.x += 3.0f;
				g_player.move.y += 0.0f;
			}
			else
			{
				g_player.move.x += 3.0f;
				g_player.move.y += 0.0f;
				//D�L�[�������ꂽ�E�Ɉړ�
				//g_player.pos.x += g_player.move.x;
			}

		}
		else if (KeyboardRepeat(DIK_W) == true)
		{
			if (KeyboardRepeat(DIK_S) == true)
			{
				//S�L�[�������ꂽ�i�ł���Ύ~�܂肽���j
				//g_player.pos.y -= 1.0f;
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.move.x += 0.0f;
				g_player.move.y -= 3.0f;
			}
			else
			{
				//W�L�[�������ꂽ��Ɉړ�
				g_player.move.x += 0.0f;
				g_player.move.y -= 3.0f;
			}

		}
		else if (KeyboardRepeat(DIK_S) == true)
		{
			if (KeyboardRepeat(DIK_W) == true)
			{
				//W�L�[�������ꂽ�i�ł���Ύ~�܂肽���j
			}
			else if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.move.x += 0.0f;
				g_player.move.y += 3.0f;
			}
			else
			{
				//S�L�[�������ꂽ���Ɉړ�
				g_player.move.x += 0.0f;
				g_player.move.y += 3.0f;

			}
		}
		else if (KeyboardRepeat(DIK_R) == true)
		{
			InitPlayer();
		}
		else if (KeyboardRepeat(DIK_LEFT) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.rot.z += 0.2f;
			}
			else
			{
				g_player.rot.z += 0.2f;
			}
		}
		else if (KeyboardRepeat(DIK_RIGHT) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				g_player.rot.z -= 0.2f;
			}
			else
			{
				g_player.rot.z -= 0.2f;
			}
		}
		else if (KeyboardRepeat(DIK_UP) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				if (g_player.Length <= MAX_MAX)
				{
					g_player.Length += 1.0f;
				}

			}
			else
			{
				if (g_player.Length <= MAX_MAX)
				{
					g_player.Length += 1.0f;
				}

			}
		}
		else if (KeyboardRepeat(DIK_DOWN) == true)
		{
			if (KeyboardTrigger(DIK_SPACE) == true)
			{//SPACE
				//�e�̐ݒ�
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 20.0f, 0.0f), BULLETTYPE_PLAYER);
				if (g_player.Length >= MAX_MIN)
				{
					g_player.Length -= 1.0f;
				}
			}
			else
			{
				if (g_player.Length >= MAX_MIN)
				{
					g_player.Length -= 1.0f;
				}

			}
		}
		else if (KeyboardTrigger(DIK_SPACE) == true)
		{//SPACE
			//�e�̐ݒ�
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.5) * 10.0f, cosf(g_player.rot.z + D3DX_PI * 0.5) * 10.0f, 0.0f), BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.45) * 15.0f, cosf(g_player.rot.z + D3DX_PI * 0.45) * 15.0f, 0.0f), BULLETTYPE_PLAYER);
			//SetBullet(g_player.pos, D3DXVECTOR3(sinf(g_player.rot.z + D3DX_PI * 0.55) * 15.0f, cosf(g_player.rot.z + D3DX_PI * 0.55) * 15.0f, 0.0f), BULLETTYPE_PLAYER);
		}
		//else if (KeyboardTrigger(DIK_1) == true)
		//{
		//	AddScore(200);
		//}

		if (g_player.bHit == true)
		{
			g_player.nCntAnimState++;//�J�E���^�[�����Z
		}
	}

	//�ʒu���X�V
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;

	//�ړ��ʂ��X�V�i�����j
	g_player.move.x += (0.0f - g_player.move.x) * 0.1f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.1f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	//if (g_player.nCntAnimState >= 5)
	//{
	//	//���_�J���[�̐ݒ�
	//	pVtx[0].col = D3DCOLOR_RGBA(255,255,255, 255);
	//	pVtx[1].col = D3DCOLOR_RGBA(255,255,255, 255);
	//	pVtx[2].col = D3DCOLOR_RGBA(255,255,255, 255);
	//	pVtx[3].col = D3DCOLOR_RGBA(255,255,255, 255);

	//	g_player.nCntAnimState = 0;
	//	g_player.bHit  = false;
	//}

	switch (g_player.state)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_NORMAL;
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		break;
	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{
			//���[�h��ݒ�i���U���g�j
			SetMode(MODE_RESULT_LOSE);

			return;
		}
		else
		{
			if (g_player.nCounterState <= 0)
			{
				g_player.state = PLAYERSTATE_NORMAL;
			}
		}
		break;
	}

	//�ʒu���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z + (-D3DX_PI + g_player.Angle)) * g_player.Length;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.Angle)) * g_player.Length;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f - g_player.Angle)) * g_player.Length;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (0.0f + g_player.Angle)) * g_player.Length;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer1->Unlock();

	//g_nCounterAnimPlayer1++;//�J�E���^�[�����Z
	//if (g_nCounterAnimPlayer1>=5)//(g_nCounterAnimPlayer1)%5==0)//��莞�Ԍo�߂���
	//{
	//	g_nCounterAnimPlayer1 = 0;//�J�E���^�[�������l�ɖ߂�

	//	g_nPatternAnimPlayer1++;// = (g_nPatternAnimPlayer1+1)%10; //�p�^�[�����X�V����
	//	
	//	if (g_nPatternAnimPlayer1>=10)//���p�^�[�����𒴂���
	//	{
	//		//g_nPatternAnimPlayer1 = g_nCounterAnimPlayer1 + 0.5f;;//�p�^�[��������������
	//		g_nPatternAnimPlayer1 = 0;
	//	}
	//	
	//	//�e�N�X�`�����W�̍X�V0.125

	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1/5) * 0.5f);//(u,v)
	//	pVtx[1].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f);//(u,v)
	//	pVtx[2].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)
	//	pVtx[3].tex = D3DXVECTOR2(g_nPatternAnimPlayer1 * 0.2f + 0.2f, g_nPatternAnimPlayer1 /5 * 0.5f +0.5f);//(g_nCounterAnimPlayer1 / 5) * 0.5f + 0.5f);//(u,v)

	//}

}
//�v���C���[�̕`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	if (g_player.bDisp == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[��
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer1, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		if (g_player.bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturePlayer1);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				0,                                     //�`�悷��ŏ��̒��_�C���f�b�N�X
				2);                                    //�`�悷��v���~�e�B�u��
		}

	}
}
Player* GetPlayer(void)
{
	return &g_player;//�v���C���[�̏���Ԃ�
}
void HitPlayer(int nDamage)//������͂�Ă�
{
	VERTEX_2D* pVtx;
	g_player.nLife -= nDamage;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)//����
	{
		//bakuhatu

		g_player.bUse = false;

		g_player.bDisp = false;

		g_player.nCntAnimState = PLAYERSTATE_DEATH;

		g_player.nCounterState = 60;

	}
	else//����łȂ�
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCounterState = 5;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0,0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0,0, 255);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer1->Unlock();

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffPlayer1->Lock(0, 0, (void**)&pVtx, 0);

	//if (g_player.nLife > 0)
	//{
	//	g_player.bHit = true;

	//	//���_�J���[�̐ݒ�
	//	pVtx[0].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//	pVtx[1].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//	pVtx[2].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//	pVtx[3].col = D3DCOLOR_RGBA(255, 0,0, 255);
	//}
	//else
	//{
	//	g_player.bUse = false;
	//}

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffPlayer1->Unlock();

}