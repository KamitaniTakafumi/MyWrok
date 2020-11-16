/*------------------------------------------------
*  @file game.cpp
*  @brief ゲーム本体処理
*  @author 上谷恭史、高橋賢太
*  @date 2019/10/26
------------------------------------------------*/

/*------------------------------------------------
*  定数定義
------------------------------------------------*/

// 画面サイズの定数
#define	DISP_W		(1280)
#define	DISP_H		(720)

#define STATE_NONE 0                 //切り替え
#define STATE_ONE 1                  //切り替え

/*-----------------------------------------------
* グローバル変数宣言
-----------------------------------------------*/

extern int stateStage;
extern int gKey;			// キー入力の情報
extern int gTrg;            // トリガー入力の情報
extern int selectTrg;       // キー入力の判定
extern int gFrameCount;		// 毎フレーム+1するカウント
extern int gGameoverCount;	// ゲームオーバー時のカウントダウン
extern int gFrameWait;		// 行動した時のクールタイム
extern int attackCooltime;  // 攻撃のクールタイム
extern int gGameoverCount;	// ゲームオーバー時のカウントダウン
extern int check;			// キー入力の判定
extern int pick;			// キー入力の判定
extern int bgstage;			// ゲームオーバー時に描画するステージ
extern int bgstage2;		// ゲームオーバー時に描画するステージ
extern int required_count;  // 進むのに必要な倒す敵のカウント
extern int clearwait;		// ボス後、ストーリーパートへの移行時間
extern int clearflag;		// 進むためのフラグ変数
extern int check_number;	// アイテムを持っているかのチェック変数
extern int check_number2;	// アイテムを持っているかのチェック変数２
extern int wallwait;		// 壁壊し待ち時間
extern int wallflag;		// 壁壊しフラグ
extern int continueflag;	// コンティニューフラグ

/*-------------------------------------------------
*  関数宣言
-------------------------------------------------*/

// アプリの初期化
// 起動時に1回だけ実行される
void AppInit();
// アプリの解放
// 終了時に1回だけ実行される
void AppRelease();
// フレーム処理：入力
void FrameInput();
// フレーム処理：計算
void FrameProcess();
// フレーム処理：描画
void FrameDraw();
