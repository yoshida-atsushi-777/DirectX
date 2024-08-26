//---------------------------------------------------------
// 
// Author:Yoshida Atsushi
//---------------------------------------------------------

#ifndef _PLAYER_H_//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_//�Q�d�C���N���[�h�h�~�̃}�N����`

#define HABA (70.0f)//��
#define TAKASA (50.0f)//����

//�v���C���[�̏��2024/08/26
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//�o����ԁi�_�Łj
	PLAYERSTATE_NORMAL,//�ʏ�
	PLAYERSTATE_DAMAGE,//�_���[�W
	PLAYERSTATE_DEATH,//���b
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�v���C���[�\����
typedef struct
{
	D3DXVECTOR3 pos;                         //�ʒu
	D3DXVECTOR3 move;                        //�ړ���
	PLAYERSTATE state;                       //�v���C���[�̏��
	int nCounterState;                       //��ԊǗ��J�E���^�[
	bool bDisp;                              //�\�����邩���Ȃ���
	D3DXVECTOR3 rot;						 //����
	D3DXVECTOR3 Bullet;						 //�e�̑���
	float Length;                           //�Ίp���̒���
	float Angle;                            //�Ίp���̊p�x
	bool bUse;
	bool bHit;                              //������͂�Ă�
	int nCntAnimState;                      //��Ԃ��J�E���g
	int nLife;                              //��
	int nZanki;                             //�c�@
}Player;

//�v���g
void InitBackGround(void);
void UninitBackGround(void);
void UpdateBackGround(void);
void DrawBackGround(void);
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
void HitPlayer(int nDamage);//������͂�Ă�


#endif