#define	SAFE_DELETE(x)	if(x){delete x;x=NULL;}

// ※１ ここから
#define PLAYER_SPEED 4			// プレイヤーのスピード
#define PLAYER_HP 3

#define FRAME_NUM_PER_SEC 60.0f	// 1秒間のフレーム数

#define ITEM_MAX 100			// アイテム出現最大数

//当たり判定用半径定義
#define PLAYER_COLLISION 20
#define ITEM_COLLISION 10

// ゲーム時間
#define GAME_TIME 120
// ※１ ここまで
