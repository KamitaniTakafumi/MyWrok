#define	SAFE_DELETE(x)	if(x){delete x;x=NULL;}

constexpr auto PLAYER_SPEED = 4;			// プレイヤーのスピード
constexpr auto PLAYER_HP = 3;

constexpr auto FRAME_NUM_PER_SEC = 60.0f;	// 1秒間のフレーム数

constexpr auto ITEM_MAX = 100;				// アイテム出現最大数

constexpr auto PLAYER_COLLISION = 20;		//プレイヤー当たり判定用半径
constexpr auto ITEM_COLLISION = 10;			//アイテム当たり判定用半径

constexpr auto GAME_TIME = 120;				// ゲーム時間
