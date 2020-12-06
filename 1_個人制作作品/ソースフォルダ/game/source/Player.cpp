/**
 * @file Player.cpp
 * @brief 処理
 * @author 上谷恭史
 * @date 2020 / 08 / 25
 */

#include "Player.h"
#include "Control.h"

namespace act {
	/**
	 * Playerコンストラクタ
	 */
	Player::Player() :
		_PlayerX(0), _PlayerY(0), _GhPlayer{ 0 }, _Subscript(0),
		_PlayerWidth(0), _PlayerHeight(0), _Life(0), _CharaState(0)	{
	}

	/**
	 * プレイヤー初期化
	 */
	void Player::Initialize() {
		_PlayerWidth = 80;
		_PlayerHeight = 80;
		_PlayerX = (WINDOW_WIDTH - _PlayerWidth) / 2;
		_PlayerY = WINDOW_HEIGHT - _PlayerHeight;
		_Subscript = 6;

		_Life = PLAYER_HP;

		//画像読み込み
		LoadBlkTexture("res/sample01.png", 80, 80, 3, 4, 12, _GhPlayer);
		
		_CharaState = LOOK_RIGHT;
	}

	/**
	 * 移動処理
	 * @param key 押した瞬間の判定
	 * @param trg 押されっぱなしの判定
	 */
	void Player::Move(int key, int trg) {
		// 移動処理
		if (KeyJudg(key, KEYIN_D) || PadJudg(key, KEYIN_RIGHT)) {
			_PlayerX += PLAYER_SPEED;
			_CharaState = LOOK_RIGHT;
		}
		if (KeyJudg(key, KEYIN_A) || PadJudg(key, KEYIN_LEFT)) {
			_PlayerX -= PLAYER_SPEED;
			_CharaState = LOOK_LEFT;
		}

		// 画面外判定
		if (_PlayerX < 0) { _PlayerX = 0; }
		if (_PlayerX > WINDOW_WIDTH - _PlayerWidth) { _PlayerX = WINDOW_WIDTH - _PlayerWidth; }

		// キャラの向きで添え字を変える
		// 右向き
		if (_CharaState == LOOK_RIGHT) {
			if ((_Subscript >= 3) && (_Subscript < 6)) {
				_Subscript = 6;
			}
		}
		// 左向き
		else if (_CharaState == LOOK_LEFT) {
			if ((_Subscript >= 6) && (_Subscript < 9)) {
				_Subscript = 3;
			}
		}

		// 時間で添え字を変える
		if ((gFpsCount % ((int)FRAME_NUM_PER_SEC / 2)) == 0) {
			_Subscript++;	// 添え字を変える

			// キャラが右向き
			if (_CharaState == LOOK_RIGHT) {
				// 添え字が範囲を越えたら戻す
				if (_Subscript >= 9) {
					_Subscript = 6;
				}
			}
			// キャラが左向き
			else if (_CharaState == LOOK_LEFT) {
				// 添え字が範囲を越えたら戻す
				if (_Subscript >= 6) {
					_Subscript = 3;
				}
			}
		}

		SetPosX(_PlayerX);
	}

	/**
	 * 描画処理
	 */
	void Player::Draw() {
		// ライフが残っていればプレイヤー描画
		if (_Life > 0) {
			DrawMemTh(_PlayerX, _PlayerY, _GhPlayer[_Subscript]);
		}
#ifdef _DEBUG
		DrawFBox(GetCollPosX(), GetCollPosY(), GetCollPosX() + (PLAYER_COLLISION * 2),
			GetCollPosY() + (PLAYER_COLLISION * 2), GetColor(NULL, 255, 0, 0));
#endif // _DEBUG
	}
}
