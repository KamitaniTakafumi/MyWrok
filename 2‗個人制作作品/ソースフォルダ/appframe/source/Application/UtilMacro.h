#define	SAFE_DELETE(x)	if(x){delete x;x=NULL;}

constexpr auto PLAYER_SPEED = 4;			// �v���C���[�̃X�s�[�h
constexpr auto PLAYER_HP = 3;

constexpr auto FRAME_NUM_PER_SEC = 60.0f;	// 1�b�Ԃ̃t���[����

constexpr auto ITEM_MAX = 100;				// �A�C�e���o���ő吔

constexpr auto PLAYER_COLLISION = 20;		//�v���C���[�����蔻��p���a
constexpr auto ITEM_COLLISION = 10;			//�A�C�e�������蔻��p���a

constexpr auto GAME_TIME = 120;				// �Q�[������
