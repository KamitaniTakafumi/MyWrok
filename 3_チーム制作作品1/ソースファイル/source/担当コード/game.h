/*------------------------------------------------
*  @file game.cpp
*  @brief �Q�[���{�̏���
*  @author ��J���j�A��������
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  �萔��`
------------------------------------------------*/

// ��ʃT�C�Y�̒萔
#define	DISP_W		(1280)
#define	DISP_H		(720)

#define STATE_NONE 0                 //�؂�ւ�
#define STATE_ONE 1                  //�؂�ւ�

/*-----------------------------------------------
* �O���[�o���ϐ��錾
-----------------------------------------------*/

extern int stateStage;
extern int gKey;			// �L�[���͂̏��
extern int gTrg;            // �g���K�[���͂̏��
extern int selectTrg;       // �L�[���͂̔���
extern int gFrameCount;		// ���t���[��+1����J�E���g
extern int gGameoverCount;	// �Q�[���I�[�o�[���̃J�E���g�_�E��
extern int gFrameWait;		// �s���������̃N�[���^�C��
extern int attackCooltime;  // �U���̃N�[���^�C��
extern int gGameoverCount;	// �Q�[���I�[�o�[���̃J�E���g�_�E��
extern int check;			// �L�[���͂̔���
extern int pick;			// �L�[���͂̔���
extern int bgstage;			// �Q�[���I�[�o�[���ɕ`�悷��X�e�[�W
extern int bgstage2;		// �Q�[���I�[�o�[���ɕ`�悷��X�e�[�W
extern int required_count;  // �i�ނ̂ɕK�v�ȓ|���G�̃J�E���g
extern int clearwait;		// �{�X��A�X�g�[���[�p�[�g�ւ̈ڍs����
extern int clearflag;		// �i�ނ��߂̃t���O�ϐ�
extern int check_number;	// �A�C�e���������Ă��邩�̃`�F�b�N�ϐ�
extern int check_number2;	// �A�C�e���������Ă��邩�̃`�F�b�N�ϐ��Q
extern int wallwait;		// �ǉ󂵑҂�����
extern int wallflag;		// �ǉ󂵃t���O
extern int continueflag;	// �R���e�B�j���[�t���O

/*-------------------------------------------------
*  �֐��錾
-------------------------------------------------*/

// �A�v���̏�����
// �N������1�񂾂����s�����
void AppInit();
// �A�v���̉��
// �I������1�񂾂����s�����
void AppRelease();
// �t���[�������F����
void FrameInput();
// �t���[�������F�v�Z
void FrameProcess();
// �t���[�������F�`��
void FrameDraw();
